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
CPPFLAGS :=  -Iinclude -MMD -MP -g -I$(LIB_DIR)/spdlog/include -std=c++20
CFLAGS   :=  -Wall -std=c++20 -I/usr/local/include -I$(LIB_DIR)/spdlog/include 
#LDFLAGS  := -Llib/spdlog -L/usr/local/lib 
LDFLAGS  := -Llib/spdlog -L~/~/opt/x-tools/armv8-rpi3-linux-gnueabihf/armv8-rpi3-linux-gnueabihf/sysroot/usr/local/
#LDLIBS   := -lm -lgpiodcxx -lstdc++fs -lpthread -lspdlog
LDLIBS   := -lm -lstdc++fs -lspdlog -lpthread

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

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

install:
	sudo rpi_cc bash -c 'cp -r include /usr/include/effectControl'
#	mkdir -p /usr/include/effectControl
#	cp -r include /usr/include/effectControl

