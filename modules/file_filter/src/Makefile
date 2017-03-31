TARGET = service

CC = g++
CFLAGS = -g -I../include #-DNDEBUG
LDFLAGS = -ldl

IDIR = ../include
DDIR = ../dist

DEPS = $(wildcard $(IDIR)/*.h)
OBJS = service.o filter.o stack.o gsystem.o
MODS = image_filter.o
#OBJS = $(patsubst %.cpp, %.o,  $(wildcard *.cpp))

.PHONY: clean dist all

all: $(TARGET) $(MODS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -Wl,-export-dynamic -o $@ $^ $(LDFLAGS)

image_filter.o: image_filter.cpp $(DEPS)
	g++ -fPIC --shared $< -o image_filter.so -ldl

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<



clean:
	$(RM) *.o

dist: all clean
	mv $(TARGET) $(DDIR)
	mv *.so $(DDIR)/modules

