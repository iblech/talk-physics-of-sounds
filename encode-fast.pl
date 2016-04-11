#!/usr/bin/perl

use warnings;
use strict;

use constant SAMPLING_RATE     => 88200;
use constant BLOCKS_PER_SECOND => 5;
use constant SAMPLES_PER_BLOCK => SAMPLING_RATE / BLOCKS_PER_SECOND;

{
    my $num_packet = 0;
    sub next_data {
        $num_packet++;

        return 0 if $num_packet <= 4;
        return 1 if $num_packet == 5;

        read(STDIN, my $char, 1) == 1 or return;
        return ord($char) - 65;
    }
}

sub sum { my $s = 0; $s += $_ for @_; $s }

sub calc_output { scalar `./generate-sine @{[ join " ", 1000000000, SAMPLING_RATE, SAMPLES_PER_BLOCK, @_ ]}` }

sub binary {
    my $data = shift;
    my @bits;

    while($data > 0) {
        if($data % 2 == 1) {
            push @bits, 1;
            $data--;
        } else {
            push @bits, 0;
        }
        $data /= 2;
    }

    return @bits;
}

my @freqs = @ARGV;

my @output;
for my $data (0 .. 2**@freqs - 1) {
    my @bits = binary($data);

    push @output, calc_output(map { $freqs[$_] } grep { $bits[$_] } 0..$#bits);
}

while(1) {
    defined(my $data = next_data()) or last;

    print $output[$data];
}
