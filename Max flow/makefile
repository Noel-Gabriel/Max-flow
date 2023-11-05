# generated using https://solver.assistedcoding.eu/makefilegen because I have no idea about makefiles

OBJS	= main.o graphreader.o ak.o
SOURCE	= main.cpp io/graphreader.cpp io/ak.cpp
DEPENDS = $(patsubst %.cpp,%.d,$(SOURCE))
HEADER	= 
OUT	= benchmarks
CC	 = g++
FLAGS	 = -g -c -Wall -std=c++20 -MMD -MP
LFLAGS	 = -std=c++20 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

graphreader.o: io/graphreader.cpp
	$(CC) $(FLAGS) io/graphreader.cpp 

ak.o: io/ak.cpp
	$(CC) $(FLAGS) io/ak.cpp

clean:
	rm -f $(OBJS) $(OUT) $(DEPENDS)

-include $(DEPENDS)

run: $(OUT)
	./$(OUT)
