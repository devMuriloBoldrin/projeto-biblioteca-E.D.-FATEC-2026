CC = gcc
CFLAGS = -Wall -Iinclude

SRCS = src/main.c src/livro.c src/lista.c src/fila.c src/pilha.c src/bst.c src/grafo.c src/ordenacao.c
OBJS = $(SRCS:.c=.o)
TARGET = biblioteca

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)