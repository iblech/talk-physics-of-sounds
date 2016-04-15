#!/bin/bash

./raw2human | awk "{
    i++;
    print(\$1 * sin(2*3.1415926535897*$1*i/8000));
}"
