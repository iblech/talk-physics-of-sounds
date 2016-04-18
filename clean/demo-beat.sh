#!/bin/bash

./generate-sines 44100 441000 440 440.5 | aplay -r44100 -fS32_LE
