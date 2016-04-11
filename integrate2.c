#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SAMPLING_FREQUENCY 8000
#define PI                 3.14159265358979323846264338327950288419716939937510

double freq  = 440;
double phase = 0;

double multiplier(double t) { return sin(2*PI*freq*t/8000 + phase); }

int main(int argc, char* argv[]) {
    if(argc > 1) freq  = atof(argv[1]);
    if(argc > 2) phase = atof(argv[2]);

    double accum = 0;

    int t = 0;

    while(1) {
        int32_t sample;
        if(fread(&sample, sizeof(int32_t), 1, stdin) != 1) {
            exit(0);
        }

        double y = sample;
        // y += 3000000000;
        y /= INT32_MAX;
        y *= multiplier(t);
        accum += y;
        t++;

        printf("%d\t%f\t%f\n", t, y, accum);
    }
}
