CC=gcc
CFLAGS=-Wall -O2 -std=c99

BIN=raw2human human2raw generate-sines print-spectrum watch-spectrum

.PHONY: clean all

all: $(BIN)

raw2human: raw2human.c
	$(CC) $(CFLAGS) -o $@ $<

human2raw: human2raw.c
	$(CC) $(CFLAGS) -o $@ $<

print-spectrum: print-spectrum.c
	$(CC) $(CFLAGS) -o $@ $< -lfftw3

watch-spectrum: watch-spectrum.c
	$(CC) $(CFLAGS) -o $@ $< -lfftw3

generate-sines: generate-sines.c
	$(CC) $(CFLAGS) -o $@ $< -lm

clean:
	rm -f $(BIN)
