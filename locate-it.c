/* gonzo code */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define WIDTH   320
#define HEIGHT  240
#define BUFSIZE (WIDTH * HEIGHT * 3)

#define DISTSQ(r1,g1,b1, r2,g2,b2) ( \
    abs(r1-r2)*abs(r1-r2) + \
    abs(g1-g2)*abs(g1-g2) + \
    abs(b1-b2)*abs(b1-b2))

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
    unsigned char *oldimage = malloc(WIDTH*HEIGHT*3);
    unsigned char *newimage = malloc(WIDTH*HEIGHT*3);

    unsigned int c = 0;

    printf("P5\n320 240\n255\n");

    while(1) {
        c++;
        memcpy(oldimage, newimage, BUFSIZE);
        read_frame(newimage);

        if(c == 1) continue;

        unsigned long sumx = 0, sumy = 0;
        unsigned int matches = 0;

        unsigned int max = 0;

        for(unsigned int i = 0; i < WIDTH * HEIGHT; i++) {
            unsigned char r1 = oldimage[3*i+0], g1 = oldimage[3*i+1], b1 = oldimage[3*i+2];
            unsigned char r2 = newimage[3*i+0], g2 = newimage[3*i+1], b2 = newimage[3*i+2];

            unsigned int x = i % WIDTH, y = i / WIDTH;
            if(DISTSQ(r1,g1,b1, r2,g2,b2) > max)
                max = DISTSQ(r1,g1,b1, r2,g2,b2);
            if((int)r1 + (int)g1 + (int)b1 < 180) {
                //printf("%c\n", DISTSQ(r1,g1,b1, r2,g2,b2) / 500);
                //printf("%d", c);
                sumx += x;
                sumy += y;
                matches++;
            }

            if(c == 6) {
                printf("%c", ((int)r1 + (int)g1 + (int)b1 < 180) ? 250 : 0);
            }
        }

        if(c == 6) {
            fflush(stdout);
        }

        if(matches) {
            unsigned int x = sumx / matches;
            unsigned int y = sumy / matches;
            char cmd[100];
            sprintf(cmd, "xdotool windowmove 0x2800001 %d %d", 400 + WIDTH - x, y);
            fprintf(stderr, "%d %d\n", x, y);
            system(cmd);
        }
    }
}
