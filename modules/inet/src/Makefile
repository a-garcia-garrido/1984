CC = g++

CFLAGS  = -g
LDFLAGS = -lpng

KEEPER_OBJS = server.o
SHOOTER_OBJS = image_file.o client.o
DEPS = image_file.h

all: photo_keeper photo_shooter

check: all
	./photo_keeper  2>&1 >/dev/null | grep "photo_keeper up and running"
	./photo_shooter 2>&1 >/dev/null | grep "photo_shooter running"

photo_keeper: $(KEEPER_OBJS)
	$(CC) $(CFLAGS) -o $@ $(KEEPER_OBJS)

photo_shooter: $(SHOOTER_OBJS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $(SHOOTER_OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $<

clean:
	-rm photo_keeper photo_shooter *.o

.PHONY: all clean check
