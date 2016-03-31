#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PI 3.141592653589793238462643383279

int main(int argc, char* argv[]) {
    int BASE          = atoi(argv[1]);
    int SAMPLING_RATE = atoi(argv[2]);
    int NUM_SAMPLES   = atoi(argv[3]);

    fprintf(stderr, "sampling rate %d, number of samples %d, number of frequencies %d: ", SAMPLING_RATE, NUM_SAMPLES, argc - 4);

    double frequencies[argc - 4];
    for(int j = 0; j < argc - 4; j++) {
        frequencies[j] = atoi(argv[4 + j]);
        fprintf(stderr, "%d ", atoi(argv[4 + j]));
    }
    fprintf(stderr, "\n");

    for(int i = 0; i < NUM_SAMPLES; i++) {
        double sample = 0;
        for(int j = 0; j < argc - 4; j++) {
            sample += sin(2 * PI * frequencies[j] * i / SAMPLING_RATE);
        }

        double lambda = (double)i / NUM_SAMPLES;
        double amplitude =
            lambda <= 0.01 ? 100 * lambda :
            lambda <= 0.99 ? 1 : 100 * (1-lambda);

        uint32_t s = BASE * amplitude * sample;
        fwrite(&s, sizeof(s), 1, stdout);
    }
}
