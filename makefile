SFMLFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin


EXE := $(BIN_DIR)/DIVEUP

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXXFLAGS := -Iinclude/ -MMD $(SFMLFLAGS) -MP
CFLAGS := -Wall
LDFLAGS := -Llib/
LDLIBS := 

.PHONY: all clean
all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) -o $@ $^ $(SFMLFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) :
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR) $(BIN_DIR)

-include $(OBJ:.o=.d)
