#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[]) {
    int32_t sample;
    while(fread(&sample, sizeof(sample), 1, stdin) == 1) {
        printf("%f\n", (double)(sample) / INT32_MAX);
    }
}
