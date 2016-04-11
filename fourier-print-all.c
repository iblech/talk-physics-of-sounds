#include <fftw3.h>
#include <sndfile.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define SAMPLING_FREQUENCY 176400
#define NUM_BLOCKS         1
#define SAMPLES_PER_BLOCK  (SAMPLING_FREQUENCY / NUM_BLOCKS)
#define NUM_FREQUENCIES    (SAMPLES_PER_BLOCK / 2 + 1)

double       samples[SAMPLES_PER_BLOCK];
fftw_complex out[NUM_FREQUENCIES];
fftw_plan    plan;
long         input[SAMPLES_PER_BLOCK];

void process_piece(double* xs) {
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

    for(int j = 0; j < NUM_BLOCKS; j++) {
        process_piece(xs);
    }

    for(int i = 0; i < NUM_FREQUENCIES; i++) {
        printf("%d\t%f\n", i * NUM_BLOCKS, xs[i]);
    }

    fftw_destroy_plan(plan);

    return 0;
}

    /*
    for(int i = 0; i < N / 2; i++) {
        printf("%i\t%f\n", i, xs[i]);
    }
    */
