TARGET = Sort

.PHONY: all clean install uninstall

all: $(TARGET)

clean:
	del /Q $(TARGET) *.o

main.o: main.c
	gcc -c -o main.o main.c

input.o: input.c
	gcc -c -o input.o input.c

sorting.o: sorting.c
	gcc -c -o sorting.o sorting.c

queue_operations.o: queue_operations.c
	gcc -c -o queue_operations.o queue_operations.c

output.o: output.c
	gcc -c -o output.o output.c

$(TARGET): main.o input.o sorting.o queue_operations.o output.o
	gcc -o $(TARGET) main.o input.o sorting.o queue_operations.o output.o

uninstall:
	del C:\PROGRAMS\codebl\sorting\$(TARGET).exe