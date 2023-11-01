# generated using https://solver.assistedcoding.eu/makefilegen because I have no idea about makefiles

OBJS	= main.o graphreader.o
SOURCE	= main.cpp io/graphreader.cpp
HEADER	= 
OUT	= benchmarks
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++20
LFLAGS	 = -std=c++20

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

graphreader.o: io/graphreader.cpp
	$(CC) $(FLAGS) io/graphreader.cpp 

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
