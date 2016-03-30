#!/usr/bin/perl
# arecord -r44100 -f S32_LE -t raw 2>/dev/null | ./fourier2 | ./decode-without-leader.pl 950 1305 1717 2123 3000 2>/dev/null

use warnings;
use strict;

use constant EPS => 20;

my $leader = $ARGV[0];
my @detect = @ARGV;

$|++;

sub hear { split /\s+/, scalar <STDIN> }

sub contains {
    my ($needle, @haystack) = @_;

    for my $f (@haystack) {
        if(abs($needle - $f) < EPS) {
            return 1;
        }
    }

    return;
}

print STDERR "/"  until contains($leader, hear());
#print STDERR "\\" while contains($leader, hear());
#hear();
hear() for 1..11;
print STDERR "\n";

my $num = 0;
while(1) {
    my @freq = hear();
    print STDERR "@freq\n";

#   last if contains($leader, @freq);

    my $data = 0;
    for(my $i = 0; $i < @detect; $i++) {
        if(contains($detect[$i], @freq)) {
            print STDERR "*";
            $data += 1 << $i;
        } else {
            print STDERR ".";
        }
    }

    print STDERR "\n";

    print chr(65 + $data) if $num % 10 == 5;

    $num++;
}
