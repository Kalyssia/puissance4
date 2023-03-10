CC=gcc
LD=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LDFLAGS=
GTKFLAGS=`pkg-config --cflags --libs gtk+-2.0`
DOXYGEN=doxygen

all: puissance4

puissance4: main.o controller.o view.o model.o ai.o interface.o
	$(LD) -o puissance4 main.o view.o controller.o model.o ai.o interface.o $(LDFLAGS) $(GTKFLAGS)
	mv puissance4 ../

main.o: main.c view.h controller.h model.h interface.h
	$(CC) -c main.c -o main.o $(CFLAGS) $(GTKFLAGS)

ai.o: ai.h ai.c model.h
	$(CC) -c ai.c -o ai.o $(CFLAGS) $(GTKFLAGS)

interface.o: interface.h interface.c
	$(CC) -c interface.c -o interface.o $(CFLAGS) $(GTKFLAGS)

model.o: model.h model.c ai.h
	$(CC) -c model.c -o model.o $(CFLAGS) $(GTKFLAGS)

view.o: view.h view.c controller.h model.h
	$(CC) -c view.c -o view.o $(CFLAGS) $(GTKFLAGS)

controller.o: controller.h controller.c view.h model.h
	$(CC) -c controller.c -o controller.o $(CFLAGS) $(GTKFLAGS)	

doc: 
	$(DOXYGEN)

clean:
	rm -f *.o
