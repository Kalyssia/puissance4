CC=gcc
LD=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LDFLAGS=
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
DOXYGEN=doxygen

all: puissance4 doc

puissance4:
	cd source; make all

doc: 
	cd source; make doc

open:
	cd doc; xdg-open index.html

.PHONY: rapport
rapport:
	cd rapport; make rapport

clean:
	cd source; make clean
	rm -f puissance4
	rm -r doc
	clear
