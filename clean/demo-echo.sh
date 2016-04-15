#!/bin/bash

{
    dd if=/dev/zero bs=4 count=$((44100*2));
    arecord -t raw -fS32_LE -r44100;
} | aplay -fS32_LE -r44100
