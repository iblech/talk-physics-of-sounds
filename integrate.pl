#!/usr/bin/perl

use warnings;
use strict;

my $max = $ARGV[0];

my $formula = $ARGV[1] || "sin(t)";
$formula =~ s/\bt\b/\$_[0]/g;
$formula =~ s/\bpi\b/3.14159265358979323846264338327950288419716939937510/g;

my $fun = eval "sub { $formula }";

my $accum = 0;

for(my $t = 0; $t < $max; $t++) {
  my $f = $fun->($t);
  $accum += $f;
  printf "%f\t%f\t%f\n", $t, $f, $accum;
}
