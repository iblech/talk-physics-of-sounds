/* gonzo code */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define WIDTH   320
#define HEIGHT  240
#define BUFSIZE (WIDTH * HEIGHT * 3)

void read_frame(unsigned char *buf) {
    ssize_t bytes_read = 0;

    while(bytes_read < BUFSIZE) {
        ssize_t new_bytes = read(STDIN_FILENO, buf, BUFSIZE);
        if(new_bytes == 0) {
            printf("Error.\n");
            exit(1);
        }

        bytes_read += new_bytes;
        buf        += new_bytes;
    }
}

int main(int argc, char *argv[]) {
    unsigned char *image = malloc(BUFSIZE);

    unsigned int x = 0;

    while(1) {
        read_frame(image);

        unsigned long sumr = 0, sumg = 0, sumb = 0;

        for(unsigned int i = 0; i < WIDTH * HEIGHT; i++) {
            sumr += image[3*i + 0];
            sumg += image[3*i + 1];
            sumb += image[3*i + 2];
        }

        unsigned int avgr = sumr / (WIDTH * HEIGHT);
        unsigned int avgg = sumg / (WIDTH * HEIGHT);
        unsigned int avgb = sumb / (WIDTH * HEIGHT);
        char cmd[100];
        x += avgr > 170 ? 10 : -10;
        sprintf(cmd, "xdotool windowmove 0x2400001 %d 200", 400 + x);
        system(cmd);
        printf("%d\t%d\t%d\n", avgr, avgg, avgb);
    }
}
