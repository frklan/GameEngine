target = ge
src = $(wildcard src/Game/*.cpp) \
	$(wildcard src/GameEngine/*cpp) \
	$(wildcard src/Game/Scenes/Common/DebugView/*cpp) \
	$(wildcard src/Game/Scenes/Game/*cpp) \
	$(wildcard src/Game/Scenes/Test/*cpp) \
	$(wildcard src/Game/Scenes/Intro/*cpp) \
	$(wildcard src/lib/eventbus/src/eventbus/*.cpp) \
	$(wildcard src/lib/imgui/*.cpp) \
	$(wildcard src/lib/imgui-sfml/*.cpp)
	
obj = $(src:.cpp=.o) 

version = $(shell git describe --tags --always --dirty)

PREFIX ?= /usr/local
CXX ?= clang++

LDFLAGS = -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -framework OpenGL
CXXFLAGS += -g -Wall -std=c++17 -Isrc/lib -Isrc/GameEngine -Isrc/lib/eventbus/src/eventbus

$(target): $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS)

.PHONY: clean
clean:
	rm -rf $(obj) $(target)