#!/usr/bin/perl
# http://blog.robertelder.org/bash-one-liner-compose-music/
# perl snd.pl | aplay -c 1 -f S32_LE -r44100

sub max { $_[0] >= $_[1] ? $_[0] : $_[1] }

my @phase;
#push @phase, 10*rand() for 0..7;

for (my $i = 0; $i < 10; $i += 1.0/44100) {
  print pack "l", 500000000*(
     sin(($ARGV[0])*2*3.14159*($i + $phase[0])) +
     sin(($ARGV[1])*2*3.14159*($i + $phase[1])) +
     sin(($ARGV[2])*2*3.14159*($i + $phase[2])) +
     sin(($ARGV[3])*2*3.14159*($i + $phase[3])) +
     sin(($ARGV[4])*2*3.14159*($i + $phase[4])) +
     sin(($ARGV[5])*2*3.14159*($i + $phase[5])) +
     sin(($ARGV[6])*2*3.14159*($i + $phase[6])) +
     sin(($ARGV[7])*2*3.14159*($i + $phase[7])) +
     ($ARGV[8] ? 0.1*rand() : 0) +
#    0.2*sin((880)*3.14159*$i) +
#    0.4*sin((800*2)*3.14159*$i) +
#   ($i*16000 % 120 <= 17 ? sin(440*3.14159*$i) : 0) +
    #sin((440)*3.1415926535*log($i+1)) +
#   sin((440 + (($i*$i)%100)) * 3.141592 * $i) +
    0
  );
}


# $i**5 liefert "Schallplattenquietschen"
# (($i*16000) % 8 < 4 ? 1 : -1) Piepton
# sin((440 + sin($i*1000)) * 3.141592 * $i) und 10000, 100000 usw. krass

# http://waitbutwhy.com/2016/03/sound.html
# Star Trek vs. Battlestar Galactica/Firefly: Weltraumschießereien

# http://synthesizeracademy.com/noise/

# https://github.com/spell-music/csound-expression
# https://homepages.abdn.ac.uk/mth192/pages/html/maths-music.html

# xwd | aplay -r$((44100*4)) -f S16_LE -c2
