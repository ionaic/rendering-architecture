CC=g++
SOURCE=errors.cpp base.cpp # source files
HEADER=# header files
LIBRARIES=glfw3 glew
TARGET=teapot # output executable

$(TARGET):
	$(CC) -g `pkg-config --cflags $(LIBRARIES)` -o $(TARGET) $(SOURCE) `pkg-config --static --libs $(LIBRARIES)`

clean:
	rm $(TARGET)
