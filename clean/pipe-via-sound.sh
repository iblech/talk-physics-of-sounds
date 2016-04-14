#!/bin/bash
#
# This script acts like a noisy "cat": It plays the sound data given on STDIN
# and outputs to STDOUT whatever the microphone records.
#
# Example usage:
#
#     ./generate-sine 8000 440 | ./pipe-via-sound.sh 8000 44100 | ./print-spectrum 44100
#
# The first parameter specifies the input bitrate, the second the output
# bitrate. Both default to 44100. An optional third parameter specifies how
# many seconds to record. If it isn't given, no limit is imposed.

aplay -f S32_LE -r${1:-44100} < /dev/stdin &

if [ -n "$3" ]; then
    arecord -f S32_LE -r ${2:-44100} -t raw -d "$3"
else
    arecord -f S32_LE -r ${2:-44100} -t raw
fi
