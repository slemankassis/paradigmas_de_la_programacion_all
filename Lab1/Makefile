BIN = bin
SRC = src
rm = rm

CC = gcc
LINKER = gcc -o
CFLAGS = -Wall -Werror -Wno-missing-field-initializers -Wno-unused-parameter -Wextra -pedantic -std=c99 -g

val = valgrind --leak-check=full --show-reachable=yes ./bin/main

SOURCES  := $(wildcard $(SRC)/*.c)
INCLUDES := $(wildcard $(SRC)/*.h)
OBJECTS  := $(SOURCES:$(SRC)/%.c=$(SRC)/%.o)


$(BIN)/main: $(OBJECTS)
	@mkdir -p $(BIN)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(SRC)/%.o : $(SRC)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	@$(rm) $(SRC)/*.o
	@$(rm) $(BIN)/main

valgrind:
	@$(val) $(BIN)

