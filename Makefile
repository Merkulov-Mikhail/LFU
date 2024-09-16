
ifeq ($(origin CC),default)
	CC = g++
endif

BUILD_DIR ?= build
SRC = ./source
INC = ./include
CPP_SRC = main.cpp
CPP_INC = $(INC)/cache.h
CPP_OBJ = $(addprefix $(BUILD_DIR)/,$(CPP_SRC:.cpp=.o))
override CFLAGS += -I$(INC)

.PHONY: all
all: main.exe


main.exe: $(CPP_OBJ)
	$(CC) $^ -o $@

$(CPP_OBJ): $(BUILD_DIR)/%.o : $(SRC)/%.cpp $(CPP_INC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
