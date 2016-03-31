#!/usr/bin/perl

use warnings;
use strict;

my $i = 0;

while(<>) {
    print "$i\t$_\n" for split /\s+/;
    $i++;
}
