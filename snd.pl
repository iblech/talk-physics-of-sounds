#!/usr/bin/perl
# http://blog.robertelder.org/bash-one-liner-compose-music/
# perl snd.pl | aplay -c 2 -f S32_LE -r16000

for (my $i = 0; $i < 100; $i += 1.0/16000) {
  print pack "l", 500000000*(sin(440*3.1415926535*$i));
}
