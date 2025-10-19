CXX = g++
CXXFLAGS = -std=c++17 -I.
LDFLAGS = -lssl -lcrypto
SRC = main.cpp block.cpp blockchain.cpp token.cpp dsl.cpp transaction.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = blockchain

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
