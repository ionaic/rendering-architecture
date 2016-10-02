CC=g++
SOURCE=camera.cpp scene.cpp shader.cpp mesh.cpp rawmesh.cpp meshloader.cpp errors.cpp base.cpp main.cpp # source files
HEADER=# header files
LIBRARIES=glfw3 glew
LFlAGS=-lglm
CFLAGS=-std=c++11
TARGET=teapot # output executable
TEAPOT_FILE=wt_teapot.obj # teapot obj file

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) `pkg-config --cflags $(LIBRARIES)` -o $(TARGET) $(SOURCE) $(LFLAGS) `pkg-config --static --libs $(LIBRARIES)`

.DBG:
	$(eval CFLAGS+=-g)

debug: .DBG $(TARGET)

clean:
	rm $(TARGET)

run: $(TARGET)
	./$(TARGET) $(TEAPOT_FILE)
