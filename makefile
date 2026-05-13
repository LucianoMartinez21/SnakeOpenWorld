# Makefile

CC      = g++
TARGET  = app
SRC     = source/*.cpp
LIBS    = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
