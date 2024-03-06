CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -std=c++23 -march=native -O3 -Wno-deprecated-enum-enum-conversion
NCURSES_LIBS := -lncurses
OPENCV_LIBS := `pkg-config --cflags --libs opencv`

TARGET := hangman

SRC := src/main.cpp src/menu.cpp src/helper.cpp src/game.cpp src/message_box.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(NCURSES_LIBS) $(OPENCV_LIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(OPENCV_LIBS)

clean:
	rm -f $(TARGET) $(OBJ)
