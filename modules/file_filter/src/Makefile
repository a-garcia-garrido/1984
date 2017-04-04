
TARGET = service

CC = gcc #compilador

#Los directorios no pueden llevar un espacio antes del comentario, para concatenarlos.
IDIR = include#"include directory"

DDIR = ../dist#"declared directory"


CFLAGS = -g -I./$(IDIR) #-DNDEBUG #la indicacion del lincado

LDFLAGS = -ldl #parametro ldl

DEPS = $(wildcard $(IDIR)/*.h) #dependencias

OBJS = service.o filter.o stack.o gsystem.o #los objetos a lincar

MODS = image_filter.o #modulos
#OBJS = $(patsubst %.cpp, %.o,  $(wildcard *.cpp))

.PHONY: clean dist all #reglas tontorronas. No comprueba los timestamp para ver si hay que hacerlas o no.

all: $(TARGET) $(MODS) #Hacer el ejecutable y los modulos

$(TARGET): $(OBJS) #la regla target depende de los objetos
	$(CC) $(CFLAGS) -Wl,-export-dynamic -o $@ $^ $(LDFLAGS) #comando para lincar los objetos con la libretias

image_filter.o: image_filter.cpp $(DEPS) #la regla image_filter depende de image_filter.cpp y las dependencias
	g++ $(CFLAGS) -fPIC --shared $< -o image_filter.so -ldl #comando compilar el modulo

%.o: %.cpp $(DEPS) # la regla %.o depende de %.cpp y las dependencias
	$(CC) $(CFLAGS) -c $< #comando compilar todos los objetos



clean:
	$(RM) *~ *.o #borrar todos los .o y las copias de seguridad del gedit

dist: all clean
	mv $(TARGET) $(DDIR) #mover el objetivo a la carpeta dist
	mv *.so $(DDIR)/modules #mover el modulo a la carpea modules
