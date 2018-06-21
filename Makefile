P_NAME	= drawn_combat

CFLAGS  = -Wall -I. `sdl-config --cflags`
LDFLAGS = `sdl-config --libs` -lSDL_image -lSDL_gfx
OBJECTS = obj/main.o obj/txt_draw.o obj/lib_gfx.o obj/menu.o obj/level.o
LEVELS  = obj/levels/frog.o obj/levels/throw_stones.o obj/levels/rocket_flight.o

#build whole game
game: linux

#main game
linux: obj $(OBJECTS) $(LEVELS) $(P_NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) $(LEVELS) -o $(P_NAME)/$(P_NAME)

#objects
obj/main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o obj/main.o

obj/txt_draw.o: txt_draw.h txt_draw.c
	$(CC) $(CFLAGS) -c txt_draw.c -o obj/txt_draw.o

obj/lib_gfx.o: lib_gfx.h lib_gfx.c
	$(CC) $(CFLAGS) -c lib_gfx.c -o obj/lib_gfx.o

obj/menu.o: menu.h menu.c
	$(CC) $(CFLAGS) -c menu.c -o obj/menu.o

obj/level.o: level.h level.c
	$(CC) $(CFLAGS) -c level.c -o obj/level.o

#levels
obj/levels/frog.o: level.h levels/frog.c
	$(CC) $(CFLAGS) -c levels/frog.c -o obj/levels/frog.o

obj/levels/throw_stones.o: level.h levels/throw_stones.c
	$(CC) $(CFLAGS) -c levels/throw_stones.c -o obj/levels/throw_stones.o

obj/levels/rocket_flight.o: level.h levels/rocket_flight.c
	$(CC) $(CFLAGS) -c levels/rocket_flight.c -o obj/levels/rocket_flight.o

#for develop and test run
run: linux
	cd $(P_NAME) && ./$(P_NAME)

#additional stuff
release: game
	zip -9 -r $(P_NAME).zip $(P_NAME)

obj:
	mkdir obj
	mkdir obj/levels

clean:
	rm -rf $(P_NAME)/$(P_NAME)
	rm -rf obj
