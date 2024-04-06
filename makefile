SRC_DIR := src
OBJ_DIR := .cache
TARGET := LOTE

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
LIBS := $(wildcard dependecies/*.so)

CXX := g++
CXXFLAGS := -g -fPIC -I include -export-dynamic -I/usr/include/qt6

build: source
	g++ -o $(TARGET) $(OBJS) $(LIBS) -DQT_WIDGETS_LIB -lQt6Widgets -lQt6Core

run : build 
	./$(TARGET)

valgrind : build
	valgrind ./$(TARGET)

source: $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm $(OBJS)

.PHONY: all clean inst source
