#!/usr/bin/perl
# http://blog.robertelder.org/bash-one-liner-compose-music/
# perl snd.pl | aplay -c 2 -f S32_LE -r16000

sub max { $_[0] >= $_[1] ? $_[0] : $_[1] }

for (my $i = 0; $i < 100; $i += 1.0/16000) {
  print pack "l", 500000000*(
#    sin((440)*3.14159*$i) +
#    0.2*sin((880)*3.14159*$i) +
#    0.4*sin((800*2)*3.14159*$i) +
#   ($i*16000 % 120 <= 17 ? sin(440*3.14159*$i) : 0) +
    #sin((440)*3.1415926535*log($i+1)) +
    sin((440 + (($i*$i)%100)) * 3.141592 * $i) +
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
