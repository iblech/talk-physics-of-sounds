#!/bin/bash

arecord -t raw -fS32_LE -r44100 | aplay -fS32_LE -r44100
