# created with the help of chatgpt (never worked with makefiles before)

SRC_DIR := src
BUILD_DIR := build

SOURCE	= $(wildcard $(SRC_DIR)/*.cpp)
OBJS	= $(SOURCE:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
HEADER	= 
OUT	= benchmarks
CXX	 = g++
CXXFLAGS = -g -c -Wall -std=c++20 -MMD -MP 
LFLAGS	 = 

.PHONY: all
all: $(OUT)

$(OUT): $(OBJS)
	$(CXX) -g $(OBJS) -o $@ $(LFLAGS)

# C++
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp	
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR) $(OUT)

-include $(OBJS:.o=.d)

run: $(OUT)
	./$(OUT)
