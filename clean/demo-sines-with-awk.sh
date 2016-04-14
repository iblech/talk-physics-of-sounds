#!/bin/bash

awk '{
    for(i = 0; i < 8000; i++) {
        print(sin(2 * 3.141592 * 440 * i / 8000));
    }
}' | ./human2raw | aplay -r8000 -f S32_LE
