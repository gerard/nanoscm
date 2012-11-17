CFLAGS=-Wall -g -DNDEBUG
BINARY=nanoscm

$(BINARY): main.o sym.o
	$(CC) $^ -o $@
main.o: sym.c stack.h
sym.o: sym.h sym.c logging.h

test: $(BINARY)
	@for t in t/*.sh; do    \
		echo -n "$$t: ";    \
		./$$t ./$(BINARY);  \
	done;

clean:
	rm -f *.o nanoscm
