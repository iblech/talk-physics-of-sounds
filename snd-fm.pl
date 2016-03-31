#!/usr/bin/perl

my $PI = 3.1415926535897932;

for (my $i = 0; $i < 10; $i += 1.0/44100) {
  print pack "l", 500000000*(
     sin(2 * $PI * (2400 * $i - 400 * cos(2 * $PI * 2 * $i) / (2 * $PI * 2)))
  );
}
