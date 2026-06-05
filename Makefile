CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2

all: order_book

order_book: main.cpp src/order_book.cpp
	$(CXX) $(CXXFLAGS) main.cpp \
	src/order_book.cpp -o order_book

clean:
	rm -f order_book
