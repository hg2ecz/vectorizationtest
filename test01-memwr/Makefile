CC=gcc

#CFLAGS=-Wall -Ofast -march=native
#CFLAGS=-Wall -O3 -march=native
#CFLAGS=-Wall -O2 -march=native -ffast-math
#CFLAGS=-Wall -O2 -march=native -ftree-vectorize
#CFLAGS=-Wall -O2 -march=native -ftree-vectorize -ffast-math
#CFLAGS=-Wall -O2 -march=native -funroll-all-loops -ftree-vectorize -ffast-math

#CFLAGS=-Wall -Ofast -march=native -funroll-all-loops
CFLAGS=-Wall -O2 -march=native -funroll-all-loops -ftree-vectorize -ffast-math

CFLAGS+=-DITERNUM=1
LDFLAGS=

OBJS=blockwr.o benchmark.o
TARGET=benchmark

all: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

test:
	./$(TARGET)
