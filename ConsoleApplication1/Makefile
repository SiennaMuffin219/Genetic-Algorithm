AlgoGen: ConsoleApplication1.o pch.o
	g++ -std=c++11 -Wall -o AlgoGen ConsoleApplication1.o pch.o matrix.o Digit.o Individual.o AG.o ArgsParser.o

ConsoleApplication1.o: ConsoleApplication1.cpp pch.h
	g++ -std=c++11 -Wall -c ConsoleApplication1.cpp

pch.o: pch.cpp pch.h matrix.o Digit.o Individual.o AG.o ArgsParser.o
	g++ -std=c++11 -Wall -c pch.cpp

matrix.o: matrix.cpp matrix.h
	g++ -std=c++11 -Wall -c matrix.cpp

Digit.o: Digit.cpp Digit.h matrix.o
	g++ -std=c++11 -Wall -c Digit.cpp

Individual.o: Individual.cpp Individual.h matrix.o
	g++ -std=c++11 -Wall -c Individual.cpp

AG.o: AG.cpp AG.h Individual.o Digit.o matrix.o
	g++ -std=c++11 -Wall -c AG.cpp

ArgsParser.o: ArgsParser.cpp ArgsParser.h
	g++ -std=c++11 -Wall -c ArgsParser.cpp
