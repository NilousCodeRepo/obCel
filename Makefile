SRC_DIR = src
OBJ_DIR = obj
RES_DIR = res
GLFW_DIR = $(RES_DIR)/glfw-3.4

CC = gcc

CFLAGS = -std=c23 -Wall -Wextra
# += = append
CFLAGS += -I$(RES_DIR)
#exclude all the contents in glfw3-4 and then add only what i need, -path checks if dir wiith 'name' exists -prune ignores it if it exists
CFLAGS += $(addprefix -I,$(shell find $(RES_DIR) -path '$(GLFW_DIR)' -prune))
CFLAGS += -I$(GLFW_DIR)/include

LDFLAGS = -L$(GLFW_DIR)/build/src/
LDLIBS = -l:libglfw3.a -lm

#every file.c in SRC_DIR and subdirs
SOURCES = $(shell find $(SRC_DIR) -name '*.c')

#substitution, find patter src/*.c in it and substitute it with obj/*.o one at a time(%)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXECUTABLE = obCel

all: $(EXECUTABLE)

#do not recompile if there is change in timestamp of OBJ_DIR by prerequisites order-only
$(EXECUTABLE): $(OBJECTS) | $(OBJ_DIR)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	
#$@ = name of target 
#$^ = all prerequisites

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
#create dirs if not exist with same name of src/dirs
#$< = only first prerequisite

clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)

.PHONY: all clean
