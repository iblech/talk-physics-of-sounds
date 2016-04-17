#!/bin/bash

delay=${1:-2}
bitrate=${2:-8000}

arecord -t raw -fU8 -r$bitrate | {
    sleep $delay
    aplay -fU8 -r$bitrate
}

# The low quality settings are needed such that the kernel pipe buffer is not
# exceeded. This would block arecord from further recording. A more robust
# alternative is the following instead of sleep $delay:
#
#     dd count=1 bs=$((bitrate*delay)) | perl -we 'local $/; my $data = <>; print $data'
