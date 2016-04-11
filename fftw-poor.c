#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SAMPLING_FREQUENCY 8000
#define PI                 3.14159265358979323846264338327950288419716939937510
#define NUM_SAMPLES        8000

int main(int argc, char* argv[]) {
    uint32_t input[NUM_SAMPLES];
    if(fread(input, sizeof(int32_t), NUM_SAMPLES, stdin) != NUM_SAMPLES) {
        exit(0);
    }

    double samples[NUM_SAMPLES];
    for(int i = 0; i < NUM_SAMPLES; i++) {
        samples[i] = input[i];
        samples[i] /= INT32_MAX;
    }

    for(double freq = 0; freq < 1000; freq += 1) {
        double sum = 0;

        for(double phase = 0; phase < 2*PI; phase += 0.1) {
            double accum = 0;
            for(int i = 0; i < NUM_SAMPLES; i++) {
                accum += samples[i] * sin(2*PI*freq*i/SAMPLING_FREQUENCY + phase);
            }
            sum += abs(accum);
        }

        printf("%f\t%f\n", freq, sum / (2*PI/0.1));
        fflush(stdout);
    }
}
