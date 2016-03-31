#!/usr/bin/perl

use warnings;
use strict;

sub parse {
    open my $fh, "<", $_[0] or die;
    <$fh> =~ /^P6$/ or die;
    <$fh> =~ /(\d+) (\d+)$/ or die;
    my ($width, $height) = ($1, $2);
    <$fh> =~ /^255$/ or die;
    binmode $fh;

    local $/;
    my $data = <$fh>;
    return ($width, $height, $data);
}

my ($width, $height, $image1) = parse($ARGV[0]);
my (undef,  undef,   $image2) = parse($ARGV[1]);

my ($avgx, $avgy) = (0,0);
my $matches = 0;

for my $pos (0..$width*$height-1) {
    my ($r1,$g1,$b1) = unpack "%C%C%C", substr $image1, 3*$pos, 3;
    my ($r2,$g2,$b2) = unpack "%C%C%C", substr $image2, 3*$pos, 3;

    my ($x, $y) = ($pos % $width, int($pos / $width));
    if(abs($b1 - $b2) > 40) {
        $avgx += $x;
        $avgy += $y;
        $matches++;
    }

    $pos++;
}

$avgx /= $matches;
$avgy /= $matches;

print "%d\t%d\n", $avgx, $avgy;
