CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC = src/main.cpp
TARGET = cineseat.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	del /f /q $(TARGET) 2>nul || rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
