.default: all

all: ppd

clean:
	rm -rf pdd *.o *.dSYM

ppd: Coin.o Node.o LinkedList.o pdd.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
