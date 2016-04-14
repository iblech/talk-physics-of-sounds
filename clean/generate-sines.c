#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PI 3.14159265358979323846264338327950288419716939937510

int main(int argc, char* argv[]) {
    int sampling_rate = argc >= 2 ? atoi(argv[1]) : 44100;
    int num_samples   = argc >= 3 ? atoi(argv[2]) : 44100;
    int num_freqs     = argc - 3;

    fprintf(stderr, "sampling rate %d, number of samples %d, number of frequencies %d: ",
        sampling_rate, num_samples, num_freqs);

    double frequencies[num_freqs];
    for(int j = 0; j < num_freqs; j++) {
        frequencies[j] = atof(argv[3 + j]);
        fprintf(stderr, "%.0f ", frequencies[j]);
    }
    fprintf(stderr, "\n");

    for(int i = 0; i < num_samples; i++) {
        double sample = 0;
        for(int j = 0; j < num_freqs; j++) {
            sample += sin(2 * PI * frequencies[j] * i / sampling_rate);
        }

        double lambda = (double)i / num_samples;
        double amplitude =
            lambda <= 0.05 ? 20 * lambda :
            lambda <= 0.95 ? 1 : 20 * (1-lambda);

        int32_t s = num_freqs == 0 ? 0 : amplitude * sample / num_freqs * INT32_MAX;
        fwrite(&s, sizeof(s), 1, stdout);
    }
}
