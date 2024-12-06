CC = gcc
CFLAGS = -Wall -Werror -g
TARGET = zkl

SRC = src/main.c src/frontend/lexer.c src/frontend/parser.c \
      src/ir/ir_generator.c src/backend/constraint_compiler.c \
      src/utils/file_io.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)
