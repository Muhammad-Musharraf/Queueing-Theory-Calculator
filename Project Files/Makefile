CXX      = i686-w64-mingw32-g++
CXXFLAGS = -O2 -std=c++17 -mwindows
TARGET   = QueueCalc.exe
SOURCES  = main.cpp gui_splash.cpp gui_main.cpp queueing.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) -lcomctl32

clean:
	rm -f $(TARGET)
