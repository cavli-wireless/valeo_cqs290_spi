# To assist in cross-compiling
CC=gcc
AR=ar
RANLIB=ranlib
LDFLAGS=

BIN_NAME=cavli-hello

all:
	$(CC) $(CFLAGS) $(LDFLAGS) -O3 -Wall -o $(BIN_NAME) -I. -I inc -DHAVE_CONFIG_H  \
	main.c \
	src/hello.c \
	src/cavli_log.c

clean:
	rm $(BIN_NAME)
