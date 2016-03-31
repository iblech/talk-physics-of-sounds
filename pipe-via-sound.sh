#!/bin/bash

aplay -f S32_LE -r${1:-44100} < /dev/stdin &

arecord -f S32_LE -r ${2:-44100} -t raw
