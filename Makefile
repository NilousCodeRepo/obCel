SRC_DIR = src
OBJ_DIR = obj
RES_DIR = res
GLFW_DIR = $(RES_DIR)/glfw-3.4

CC = gcc

CFLAGS = -std=c23 -Wall -Wextra -ggdb
CFLAGS += -I$(RES_DIR)

LDFLAGS = -L$(GLFW_DIR)/build/src/
LDLIBS = -l:libglfw3.a -lm -lGL

# every .c file in SRC_DIR and subdirs
SOURCES = $(shell find $(SRC_DIR) -name '*.c')

# substitution: src/%.c becomes obj/%.o
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# only these sources include core.h, which pulls in glfw3.h
GLFW_SOURCES := $(SRC_DIR)/main.c $(SRC_DIR)/core.c
GLFW_OBJECTS := $(GLFW_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# only these objects get the GLFW include path
$(GLFW_OBJECTS): CFLAGS += -I$(GLFW_DIR)/include

EXECUTABLE = obCel

all: $(EXECUTABLE)

# do not recompile if there is change in timestamp of OBJ_DIR by prerequisites order-only
$(EXECUTABLE): $(OBJECTS) | $(OBJ_DIR)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# $@ = name of target
# $^ = all prerequisites

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
# create dirs if not exist with same name of src/dirs
# $< = only first prerequisite

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

.PHONY: all clean

# include the generated header dependencies
-include $(OBJECTS:.o=.d)

