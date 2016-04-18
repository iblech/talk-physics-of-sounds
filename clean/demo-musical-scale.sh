#!/bin/bash

< /dev/urandom hexdump -v -e '/1 "%u\n"' | awk '{
    split("0,2,4,5,7,9,11,12", scale, ",");
    for(i = 0; i < 4000; i++) {
        print(sin(2 * 3.141592 * 440 * 2**(scale[$1 % 8] / 12) * i / 8000));
    }
}' | ./human2raw | aplay -r8000 -f S32_LE
