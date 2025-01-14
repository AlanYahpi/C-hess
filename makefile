CC = gcc
FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Iinclude -g
TARGET = main


SOURCES = $(wildcard *.c)
OBJS = $(SOURCES:.c=.o)


all : $(TARGET)


#Link objets
$(TARGET): $(SOURCES)
	$(CC) -o $@ $^ $(FLAGS)

src/%.o: src/%.c 
	$(CC) -c -o $@ $< $(FLAGS) 

clean : 
	rm -rf $(TARGET)

run : $(TARGET) 
	./$(TARGET)

dev : 
	$(MAKE) clean
	$(MAKE) all
	$(MAKE) run 
	$(MAKE) clean
