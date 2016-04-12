#!/bin/bash

bitrate=${1:-44100}
samples_per_block=${2:-11025}
max_freq=${3:-1000}
min_freq=${4:-0}

{
    cat <<EOF
set grid
set format y ""
set xrange [$min_freq:$max_freq]
set yrange [0:1e12]

plot 0
EOF

    sleep 5  # give gnuplot time to start

    arecord -f S32_LE -r $bitrate -t raw | ./watch-spectrum $bitrate $samples_per_block $max_freq $min_freq
} >/dev/null # | /usr/bin/gnuplot -noraise
