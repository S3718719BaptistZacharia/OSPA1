.default: all

all: Task1Filter Task2 Task3 Task4

clean:
	rm -rf Task1Filter Task2 Task3 Task4 *.o *.dSYM

Task1Filter: Task1Filter.o 
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

Task2: Task2.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

Task3: Task3.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

Task4: Task4.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
