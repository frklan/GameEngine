target = ge
src = $(wildcard src/Game/*.cpp) \
	$(wildcard src/Game/GameObjects/*cpp) \
	$(wildcard src/Game/GameObjects/Player/*cpp) \
	$(wildcard src/Game/GameObjects/DebugView/*cpp) \
	$(wildcard src/Game/GameObjects/Gui/*cpp) \
	$(wildcard src/Game/GameObjects/IntroGraphics/*cpp) \
	$(wildcard src/Game/GameObjects/GameOfLife/*cpp) \
	$(wildcard src/Game/Scenes/*cpp) \
	$(wildcard src/GameEngine/*.cpp) \
	$(wildcard src/lib/imgui/*.cpp) \
	$(wildcard src/lib/imgui-sfml/*.cpp)
	
obj = $(src:.cpp=.o) 

version = $(shell git describe --tags --always --dirty)

PREFIX ?= /usr/local
CXX ?= clang++

LDFLAGS = -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -framework OpenGL
CXXFLAGS += -g -Wall -std=c++17 -Isrc/lib 

$(target): $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS)

.PHONY: clean
clean:
	rm -rf $(obj) $(target)