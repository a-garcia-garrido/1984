CC = g++

IDIR = ./include
DDIR = ../dist

CFLAGS = -g
LDFLAGS = -I $(IDIR) -I /usr/include/opencv2 -L /usr/lib/x86_64-linux-gnu/
LDLIBS =  -lopencv_core -lopencv_contrib

M01 = recognizer
M01_OBJS = recognizer.o

MODULES = $(M01)


$(M01): $(M01_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $(CFLAGS) $(LDFLAGS) -o $@ $<

.PHONY: clean dist

clean:
	$(RM) *.o

dist: $(MODULES) clean
	mv $(MODULES) $(DDIR)
