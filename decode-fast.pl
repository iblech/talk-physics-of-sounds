#!/usr/bin/perl

use strict;

use constant EPS => 1;  # gibt eh keinen Unterschied zwischen allen Werten < 40

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
hear() for 1..8;
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
    if($num % 8 == 4) {
        print chr(65 + $data);
        print STDERR "\n";
    }

    $num++;
}
