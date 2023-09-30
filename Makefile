PROG = mon_programme
CXX = g++
CXXFLAGS = -Wall -O2 -Ilib/world -Ilib/player
SDL_CFLAGS = $(shell sdl2-config --cflags) $(shell pkg-config SDL2_image --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs) $(shell pkg-config SDL2_image --libs)
TMXLITE_LDFLAGS = -L/home/matt/tmxlite/build/ -ltmxlite # Replace with the actual path and library name
SRCS = main.cpp lib/world/world.cpp lib/player/player.cpp lib/display/display.cpp lib/sprites/sprite.cpp lib/maps/maps.cpp lib/maps/assets.cpp
OBJS = $(SRCS:.cpp=.o)

$(PROG): $(OBJS)
	$(CXX) -g $(CXXFLAGS) $(SDL_CFLAGS) -o $(PROG) $(OBJS) $(SDL_LDFLAGS) $(TMXLITE_LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(PROG)

.PHONY: clean

run: $(PROG)
	./$(PROG)

default: $(PROG)
