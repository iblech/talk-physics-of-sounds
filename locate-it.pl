#!/usr/bin/perl

use warnings;
use strict;

my $width  = 320;
my $height = 240;

my $oldimage;
my $newimage;

$|++;

while(1) {
    $oldimage = $newimage;
    read(STDIN, $newimage, $width * $height * 3) == $width * $height * 3 or die;
    next unless defined $oldimage;

    print ".\n";

    my ($sumx, $sumy) = (0,0);
    my $matches = 0;

    for my $pos (0..$width*$height-1) {
        my ($r1,$g1,$b1) = unpack "%C%C%C", substr $oldimage, 3*$pos, 3;
        my ($r2,$g2,$b2) = unpack "%C%C%C", substr $newimage, 3*$pos, 3;

        my ($x, $y) = ($pos % $width, int($pos / $width));
        if(abs($b1 - $b2) > 40) {
            $sumx += $x;
            $sumy += $y;
            $matches++;
        }

        $pos++;
    }

    printf "%d\t%d\n", $sumx / $matches, $sumy / $matches
        if $matches;
}
