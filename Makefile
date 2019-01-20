target = ge
src = $(wildcard src/Game/*.cpp) \
	$(wildcard src/Game/GameObjects/*cpp) \
	$(wildcard src/Game/GameObjects/Player/*cpp) \
	$(wildcard src/Game/GameObjects/DebugView/*cpp) \
	$(wildcard src/Game/Scenes/*cpp) \
	$(wildcard src/GameEngine/*.cpp)
		
obj = $(src:.cpp=.o) 

version = $(shell git describe --tags --always --dirty)

ifndef PREFIX
	PREFIX = /usr/local
endif

ifndef CXX
  CXX = clang++
endif

LDFLAGS = -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window -framework OpenGL
CXXFLAGS = -g -Wall -std=c++17

$(target): $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS)

.PHONY: clean
clean:
	rm -rf $(obj) $(target)