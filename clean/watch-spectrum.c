/* This program continuously reads data and outputs suitable Gnuplot commands
 * for plotting the spectrum of each block.
 *
 * Compile with
 *
 *     gcc -Wall -std=c99 -O2 -o watch-spectrum watch-spectrum.c -lfftw
 *
 * and make sure that the header files for fftw are installed (package
 * libfftw3-dev on Debian-based distributions).
 *
 * For an example usage, see watch-spectrum.sh.
 *
 * The first argument specifies the bitrate, the second argument how many
 * samples should constitute a single block.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <fftw3.h>

struct pair { int a; double b; };

// Insert a pair into a descendingly sorted array of items, pushing values which
// are too small out of the array.
void tally(const int n, struct pair tops[n], const struct pair x) {
    for(int i = 0; i < n; i++) {
        if(x.b >= tops[i].b) {
            for(int j = n; j > i; j--) {
                tops[j] = tops[j - 1];
            }
            tops[i] = x;
            break;
        }
    }
}

int32_t*      input;     // input samples as 32-bit integers
double*       samples;   // input samples as double's
fftw_plan     plan;
fftw_complex* out;       // frequency coefficients
struct pair*  spectrum;

// Read a block of samples from STDIN and calculate its Fourier transform.
//
// Touches the global arrays input, samples, and out.
// The useful result is in the array spectrum.
void read_samples(const int num_samples, const int sampling_frequency) {
    if(fread(input, sizeof(int32_t), num_samples, stdin) != num_samples) {
        fprintf(stderr, "Couldn't read all input samples.\n");
        exit(1);
    }

    for(int j = 0; j < num_samples; j++) {
        samples[j] = input[j];
    }

    fftw_execute(plan);

    for(int i = 0; i < num_samples / 2 + 1; i++) {
        spectrum[i].a = i * sampling_frequency / num_samples;
        spectrum[i].b = sqrt(out[i][0]*out[i][0] + out[i][1]*out[i][1]);
    }
}

int main(const int argc, const char* const argv[]) {
    // bitrate
    const int sampling_frequency = argc >= 2 ? atoi(argv[1]) : 44100;

    // number of samples to read
    const int num_samples        = argc >= 3 ? atoi(argv[2]) : sampling_frequency;

    // cutoff frequencies
    const int max_frequency      = argc >= 4 ? atoi(argv[3]) : sampling_frequency;
    const int min_frequency      = argc >= 5 ? atoi(argv[4]) : 0;

    // number of distinct frequencies a Fourier transform can detect
    const int num_frequencies    = num_samples / 2 + 1;

    input    = malloc(num_samples * sizeof(*input));
    samples  = malloc(num_samples * sizeof(*samples));
    out      = malloc(num_samples * sizeof(*out));
    spectrum = malloc(num_samples * sizeof(*spectrum));
    if(input == NULL || samples == NULL || out == NULL || spectrum == NULL) {
        fprintf(stderr, "Couldn't allocate sufficient memory.\n");
        exit(1);
    }

    plan = fftw_plan_dft_r2c_1d(num_samples, samples, out, FFTW_ESTIMATE);

    int count = 0;

    while(1) {
        read_samples(num_samples, sampling_frequency);

        #define NUM_LEADERS 5
        struct pair tops[NUM_LEADERS] = {{0,0}};

        printf("plot '-' w l t '%d'\n", count);
        for(int i = 0; i < num_frequencies; i++) {
            if(min_frequency <= spectrum[i].a && spectrum[i].a <= max_frequency) {
                printf("%d\t%.0f\n", spectrum[i].a, spectrum[i].b);
                tally(NUM_LEADERS, tops, spectrum[i]);
            }
        }
        printf("e\n");
        fflush(stdout);

        fprintf(stderr, "\033[H\033[JMost intense frequencies:\n");
        for(int i = 0; i < NUM_LEADERS; i++) {
            fprintf(stderr, "%5d: %15.0f\n", tops[i].a, tops[i].b);
        }

        #define WINDOW 20
        fprintf(stderr, "Peaks: ");
        for(int i = WINDOW; i < num_frequencies - WINDOW - 1; i++) {
            double sum = 0;
            for(int j = i - WINDOW; j <= i + WINDOW; j++) {
                if(j == i) continue;
                sum += spectrum[j].b;
            }
            double avg = sum / (2*WINDOW);
            if(spectrum[i].b > 2 * spectrum[i-1].b && spectrum[i].b > 2 * spectrum[i+1].b && spectrum[i].b > 5 * avg) {
                fprintf(stderr, "%d ", spectrum[i].a);
            }
        }
        fprintf(stderr, "\n");

        count++;
    }

    // never reached
    fftw_destroy_plan(plan);
    free(input);
    free(samples);
    free(out);
    free(spectrum);

    return 0;
}
