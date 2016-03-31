#!/usr/bin/perl
# echo -n ABAHHGAFEADCEB | perl % 950 1305 1717 2123 3000 | aplay -c 1 -f S32_LE -r44100

use constant DURATION => 0.2;

my @freqs  = @ARGV;

my $is_first = 1;
my $is_last;
sub next_data {
    if($is_first) {
        $is_first = 0;
        return 1;
    }

    read(STDIN, my $char, 1) == 1 or return;
    return ord($char) - 65;
}

while(1) {
    defined(my $data = next_data()) or last;

    my @bits;
    for(my $i = 0; $i < @freqs; $i++) {
        if($data % 2 == 1) {
            push @bits, 1;
            $data--;
        } else {
            push @bits, 0;
        }
        $data /= 2;
    }

    for (my $t = 0; $t < DURATION; $t += 1.0/176400) {
        my $sample;
        for(my $i = 0; $i < @freqs; $i++) {
            $sample += ($freqs[$i] < 400 ? 5 : 1) * sin($freqs[$i] * 2 * 3.141592 * $t)
                if $bits[$i];
        }

        my $lambda = $t / DURATION;
        my $amplitude =
            $lambda <= 0.05 ? 20 * $lambda :
            $lambda <= 0.95 ? 1 : 20 * (1-$lambda);

        print pack "l", 300000000 * $amplitude * $sample;
    }

    last if $is_last;
}
