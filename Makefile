CPP=c++
CPPFLAGS=-std=c++11 -I/usr/local/include/opencv4 -lopencv_core -lopencv_video -lopencv_videoio -lopencv_imgcodecs
SRC=src

all:
	mkdir -p bin
	$(CPP) $(CPPFLAGS) -o bin/out $(SRC)/main.cpp

.PHONY: clean
clean:
	rm -rf bin/
