.PHONY: clean all

BIN = \
	cliente                     \
	serverEjemplo				 \
SRC = $(BIN:=.c)

.c:
	$(CC) -D_POSIX_C_SOURCE=200809L -std c++11 -pthread $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

all: $(BIN)

clean:
	rm -f $(BIN)