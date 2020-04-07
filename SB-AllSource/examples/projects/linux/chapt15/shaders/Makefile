MAIN = shaders
LIBDIRS = -L /usr/local/lib
INCDIRS = -I /usr/include -I /usr/local/include/GL -I ../../../../src/shared -I/usr/include/GL -I../../../../../../contrib/imgui/
SRCPATH = ../../../../src/chapt15/$(MAIN)/
SHAREDPATH = ../../../../src/shared/

IMGUI_SRC = ../../../../../../contrib/imgui//imgui.cpp ../../../../../../contrib/imgui//imgui_demo.cpp ../../../../../../contrib/imgui//imgui_draw.cpp ../../../../../../contrib/imgui/imgui_impl_glut.cpp ../../../../../../contrib/imgui//imgui_widgets.cpp ../../../../../../contrib/imgui//imgui_impl_opengl3.cpp

CC = gcc
CFLAGS = $(COMPILERFLAGS) -g $(INCDIRS) -DGL_GLEXT_PROTOTYPES  -lstdc++
LIBS = -lglut -lGL -lGLU -lm

prog : $(MAIN)

$(MAIN).o : $(SRCPATH)$(MAIN).cpp

math3d.o : $(SHAREDPATH)math3d.cpp

gltools.o : $(SHAREDPATH)gltools.cpp

$(MAIN) : $(MAIN).o gltools.o math3d.o
	$(CC) $(CFLAGS) -o $(MAIN) $(LIBDIRS)  $(IMGUI_SRC) $(SRCPATH)$(MAIN).cpp $(SHAREDPATH)math3d.cpp $(SHAREDPATH)gltools.cpp $(SHAREDPATH)GLee.c $(LIBS)

clean:
	rm -f *.o
