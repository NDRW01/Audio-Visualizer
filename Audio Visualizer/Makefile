# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

CC = gcc
CFLAGS = -Wall

# SFML and other libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Output binary
TARGET = a.AudioVisualizer

# Source files
CPP_SRCS = src/main.cpp \
           src/AudioManager.cpp \
           src/Visualizer.cpp \
           src/UIManager.cpp \
           src/EffectsMenu.cpp \
           src/SimpleFFT.cpp \

C_SRCS = src/kiss_fft.c \
         src/tinyfiledialogs.c

# Object files
CPP_OBJS = $(CPP_SRCS:.cpp=.o)
C_OBJS = $(C_SRCS:.c=.o)
OBJS = $(CPP_OBJS) $(C_OBJS)

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Compile C++ files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build
clean:
	rm -f src/*.o $(TARGET)

