CC=g++
SOURCE=mesh.cpp scene.cpp shader.cpp camera.cpp rawmesh.cpp meshloader.cpp errors.cpp base.cpp main.cpp # source files
HEADER=# header files
LIBRARIES=glfw3 glew
LFlAGS=-lglm
TARGET=teapot # output executable
TEAPOT_FILE=wt_teapot.obj # teapot obj file

all: $(TARGET)

$(TARGET):
	$(CC) -g `pkg-config --cflags $(LIBRARIES)` -o $(TARGET) $(SOURCE) $(LFLAGS) `pkg-config --static --libs $(LIBRARIES)`

clean:
	rm $(TARGET)

run: $(TARGET)
	./$(TARGET) $(TEAPOT_FILE)
