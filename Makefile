# Generic Makefile 
#Based on answer from https://stackoverflow.com/questions/30573481/how-to-write-a-makefile-with-separate-source-and-header-directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
LIB_DIR := ./lib

EXE := $(BIN_DIR)/effectControl
LIB_NAME := $(BIN_DIR)/libeffectControl.a
SRC := $(wildcard $(SRC_DIR)/*.cpp)
C_SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(C_SRC:.c=.o) $(SRC:.cpp=.o)
LIB_OBJ := $(filter-out src/main.o,$(OBJ))
CPPFLAGS := -Iinclude -MMD -MP -g
CFLAGS   := -Wall -std=c++17 -I/usr/local/include -I$(LIB_DIR)/spdlog/include
LDFLAGS  := -Llib/spdlog -L/usr/local/lib 
LDLIBS   := -lm -lgpiodcxx -lstdc++fs -lpthread -lspdlog

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	g++ $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

lib: $(LIB_OBJ)
	ar rvs $(LIB_NAME) $(LIB_OBJ)
	ranlib $(LIB_NAME)
clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
	rm $(SRC_DIR)/*.o
	rm $(SRC_DIR)/*.d

cleanlib:
	rm $(LIB_NAME)
-include $(OBJ:.o=.d)
