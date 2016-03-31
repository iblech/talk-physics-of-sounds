#include <fftw3.h>
#include <sndfile.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define SAMPLING_FREQUENCY 88200
#define NUM_BLOCKS         40
#define SAMPLES_PER_BLOCK  (SAMPLING_FREQUENCY / NUM_BLOCKS)
#define NUM_FREQUENCIES    (SAMPLES_PER_BLOCK / 2 + 1)

struct peak {
    int ix;
    double value;
};

struct peak find_peak(double xs[], int len, double upper_limit) {
    double max = -INFINITY;
    int    ix  = -1;
    for(int j = 0; j < len; j++) {
        if(xs[j] > max && xs[j] < upper_limit) {
            max = xs[j];
            ix  = j;
        }
    }

    struct peak p = { ix, max };
    return p;
}

void print_dominant(double xs[], int len) {
    double upper_limit = INFINITY;
    for(int i = 0; i < 20; i++) {
        struct peak p = find_peak(xs, len, upper_limit);
        int freq = NUM_BLOCKS * p.ix;
        if(freq >= 2000 && freq <= 15000)
            printf("%d@%.1e ", freq, p.value);
        upper_limit = p.value;
    }
    printf("\n");
}

double       samples[SAMPLES_PER_BLOCK];
fftw_complex out[NUM_FREQUENCIES];
fftw_plan    plan;

long         input[SAMPLES_PER_BLOCK];

void process_piece(double* xs) {
    /*
    for(int j = 0; j < SAMPLES_PER_BLOCK; j++) {
        int32_t sample;
        int byte1 = fgetc(stdin);
        int byte2 = fgetc(stdin);
        int byte3 = fgetc(stdin);
        int byte4 = fgetc(stdin);
        sample = byte1 + (byte2 << 8) + (byte3 << 16) + (byte4 << 24);
        samples[j] = sample / 111111111;
    }*/
    if(fread(input, sizeof(long), SAMPLES_PER_BLOCK, stdin) != SAMPLES_PER_BLOCK) {
        fprintf(stderr, "End of input of input error.\n");
        exit(1);
    }

    for(int j = 0; j < SAMPLES_PER_BLOCK; j++) {
        samples[j] = input[j];
    }

    fftw_execute(plan);

    for(int i = 0; i < NUM_FREQUENCIES; i++) {
        xs[i] = sqrt(out[i][0]*out[i][0] + out[i][1]*out[i][1]);
    }
}

int main(int argc, char* argv[]) {
    double xs[NUM_FREQUENCIES];

    plan = fftw_plan_dft_r2c_1d(SAMPLES_PER_BLOCK, samples, out, FFTW_ESTIMATE);

    while(1) {
        process_piece(xs);

        print_dominant(xs, NUM_FREQUENCIES);
        fflush(stdout);
    }

    fftw_destroy_plan(plan);

    return 0;
}

    /*
    for(int i = 0; i < N / 2; i++) {
        printf("%i\t%f\n", i, xs[i]);
    }
    */
