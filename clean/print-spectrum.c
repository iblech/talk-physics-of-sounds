/* This program reads a certain amount of sound data (samples) and outputs its
 * spectrum, that is a list of frequency/intensity pairs.
 *
 * Compile with
 *
 *     gcc -Wall -std=c99 -O2 -o print-spectrum print-spectrum.c -lfftw
 *
 * and make sure that the header files for fftw are installed (package
 * libfftw3-dev on Debian-based distributions).
 *
 * Usage:
 *
 *     arecord -t raw -fS32_LE -r44100 | ./print-spectrum 44100 11025
 *
 * The first argument specifies the bitrate, the second argument how many
 * samples should be read from STDIN.
 */

#include <stdint.h>
#include <stdlib.h>
#include <fftw3.h>
#include <math.h>

void read_samples(const int num_samples, double samples[num_samples]) {
    int32_t input[num_samples];

    if(fread(input, sizeof(int32_t), num_samples, stdin) != num_samples) {
        fprintf(stderr, "Couldn't read all input samples.\n");
        exit(1);
    }

    for(int j = 0; j < num_samples; j++) {
        samples[j] = input[j];
    }
}

int main(const int argc, const char* const argv[]) {
    // bitrate
    const int sampling_frequency = argc >= 2 ? atoi(argv[1]) : 44100;

    // number of samples to read
    const int num_samples        = argc >= 3 ? atoi(argv[2]) : sampling_frequency;

    // number of distinct frequencies a Fourier transform can detect
    const int num_frequencies    = num_samples / 2 + 1;

    double samples[num_samples];  // input samples
    read_samples(num_samples, samples);

    fftw_complex out[num_frequencies];  // frequency coefficients
    fftw_plan    plan;

    plan = fftw_plan_dft_r2c_1d(num_samples, samples, out, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);

    for(int i = 0; i < num_frequencies; i++) {
        printf("%d\t%.0f\n", i * sampling_frequency / num_samples,
            sqrt(out[i][0]*out[i][0] + out[i][1]*out[i][1]));
    }

    return 0;
}
