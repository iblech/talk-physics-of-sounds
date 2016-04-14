#!/bin/bash

bitrate=${1:-44100}
samples_to_show=${2:-2205}
samples_to_skip=${3:-8820}

arecord -f S32_LE -r $bitrate -t raw | {
    cat <<EOF
set grid
set format y ""
set yrange [-0.5:0.5]

plot 0
EOF

    sleep 5  # give gnuplot time to start

    while :; do
        echo "plot '-' w l t '$(date +%H:%M:%S.%N)'"
        dd count=$samples_to_show bs=4 2>/dev/null | ./raw2human
        echo e
        dd count=$samples_to_skip bs=4 &>/dev/null
    done
} | gnuplot -noraise
