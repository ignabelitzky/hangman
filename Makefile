CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -pedantic -std=c++23 -march=native -O2
NCURSES_LIBS := -lncurses

TARGET := hangman

SRC := src/main.cpp src/menu.cpp src/helper.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(NCURSES_LIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -f $(TARGET) $(OBJ)