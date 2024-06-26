CXX := g++
CXXFLAGS := -Wall -Werror -Wextra -std=c++23 -march=native -O3 -Wno-deprecated-enum-enum-conversion -Wno-stringop-overflow
NCURSES_LIBS := -lncurses
OPENCV_LIBS := `pkg-config --cflags --libs opencv`
MINIAUDIO_LIBS := -ldl -lpthread -lm

TARGET := hangman

SRC := src/main.cpp src/menu.cpp src/helper.cpp src/game.cpp src/message_box.cpp src/audio.cpp
OBJ := $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(NCURSES_LIBS) $(OPENCV_LIBS) $(MINIAUDIO_LIBS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(OPENCV_LIBS) $(MINIAUDIO_LIBS)

format:
	clang-format -style=Microsoft -i src/*.cpp include/audio.hpp include/game.hpp include/helper.hpp include/menu.hpp include/message_box.hpp

clean:
	rm -f $(TARGET) $(OBJ)
