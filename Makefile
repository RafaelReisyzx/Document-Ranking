# Compilador correto
CC := gcc  # Para código C

# Flags de compilação e linking
CFLAGS := -Wall -Wextra -Werror
LDFLAGS := -lm  # Biblioteca matemática

# Diretórios de build e objetos
BUILD := ./build
OBJ_DIR := $(BUILD)/objects
APP_DIR := $(BUILD)/

# Nome do binário
TARGET := app

# Diretórios de inclusão
INCLUDE := -Iinclude/

# Arquivos fonte
SRC := $(wildcard src/*.c)

# Objetos gerados a partir dos arquivos fonte
OBJECTS := $(SRC:%.c=$(OBJ_DIR)/%.o)

# Regras principais
all: build $(APP_DIR)/$(TARGET)

# Regra para compilar arquivos fonte
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

# Regra para linkar objetos em um executável
$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(@) $(OBJECTS) $(LDFLAGS)

# Outras regras
.PHONY: all build clean debug release run

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CFLAGS += -DDEBUG -g
debug: all

release: CFLAGS += -O3
release: all

clean:
	@rm -rvf $(OBJ_DIR)/*.o
	@rm -rvf $(APP_DIR)/$(TARGET)

run: all
	./$(APP_DIR)/$(TARGET)
