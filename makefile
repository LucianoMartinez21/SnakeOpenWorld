# Makefile

CC      = g++
TARGET  = app
SRC     = source/*.cpp
LIBS    = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
#
#(Working Debuger) -O2 -fsanitize=thread -lraylib
#-O2 -fsanitize=address,undefined -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
#(No optimization) -g -O0 -lraylib
#(recomended by raylib) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)
