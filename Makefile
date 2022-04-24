CC=gcc  #compiler
TARGET=main #target file name
 
all:
	$(CC) *.c -o $(TARGET)
	./$(TARGET)
clean:
	rm $(TARGET)
