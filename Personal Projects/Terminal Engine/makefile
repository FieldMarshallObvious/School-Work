IDIR=include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm -lncurses -lpthread

_DEPS=defs.h Vector2.h Vector3.h Vector4.h Matrix22.h Matrix33.h Matrix44.h Quaternion.h GenMath.h Rasterizer.h Framebuffer.h Camera.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o Vector2.o Vector3.o Vector4.o Matrix22.o Matrix33.o Matrix44.o Quaternion.o GenMath.o Rasterizer.o Framebuffer.o Camera.o
OBJ=$(patsubst %, $(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clear:
	rm -f $(ODIR)/*.0 *~ core $(INCDIR)/*~

run: all
	./all