# generated using https://solver.assistedcoding.eu/makefilegen because I have no idea about makefiles

OBJS	= main.o graphreader.o ak.o
SOURCE	= main.cpp graphreader.cpp ak.cpp
DEPENDS = $(patsubst %.cpp,%.d,$(SOURCE))
HEADER	= 
OUT	= benchmarks
CXX	 = g++
FLAGS	 = -g -c -Wall -std=c++20 -MMD -MP -I/Users/noel/anaconda3/include/python3.11 
LFLAGS	 =

all: $(OBJS)
	$(CXX) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CXX) $(FLAGS) main.cpp 

graphreader.o: io/graphreader.cpp
	$(CXX) $(FLAGS) io/graphreader.cpp 

ak.o: io/ak.cpp
	$(CXX) $(FLAGS) io/ak.cpp

clean:
	rm -f $(OBJS) $(OUT) $(DEPENDS)

-include $(DEPENDS)

run: $(OUT)
	./$(OUT)
