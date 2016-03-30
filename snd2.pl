#!/usr/bin/perl
# echo -n ABAHHGAFEADCEB | perl % 1305 1717 2123 3000 | aplay -c 1 -f S32_LE -r44100

sub max { $_[0] >= $_[1] ? $_[0] : $_[1] }

my @freqs  = @ARGV;

my $is_first = 1;
my $is_last;
sub next_data {
    if($is_first) {
        $is_first = 0;
        return 1;
    }

    read(STDIN, my $char, 1) == 1 or do { $is_last = 1; return 1 };
    return 2 * (ord($char) - 65);
}

while(1) {
    my $data = next_data;

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

    for (my $t = 0; $t < 1; $t += 1.0/44100) {
        my $sample;
        for(my $i = 0; $i < @freqs; $i++) {
            $sample += sin($freqs[$i] * 2 * 3.141592 * $t)
                if $bits[$i];
        }

        print pack "l", 500000000 * $sample;
    }

    last if $is_last;
}
