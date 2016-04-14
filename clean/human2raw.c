#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
    double sample;
    while(scanf("%lf\n", &sample) == 1) {
        int32_t sample_ = sample * INT32_MAX;
        if(fwrite(&sample_, sizeof(sample_), 1, stdout) != 1) {
            fprintf(stderr, "Couldn't write sample, exiting.\n");
            exit(1);
        }
    }
}
