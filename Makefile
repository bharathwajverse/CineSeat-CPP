CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./include
LDFLAGS = -L./lib -llibmysql

SRCS = src/main.cpp src/database.cpp
TARGET = cineseat.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	del /f /q $(TARGET) 2>nul || rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
