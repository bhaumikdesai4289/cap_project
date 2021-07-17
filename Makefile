IDIR =inc
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =lib

LIBS=-lpcap

_DEPS = cap_common.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = cap_common.o main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

pcap_stats: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
		rm -f $(ODIR)/*.o pcap_stats
