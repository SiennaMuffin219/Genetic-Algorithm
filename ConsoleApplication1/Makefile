ConsoleApllication1: ConsoleApplication1.o pch.o
	g++ -o ConsoleApplication1 ConsoleApplication1.o pch.o matrix.o Digit.o Individual.o AG.o ArgsParser.o

ConsoleApplication1.o: ConsoleApplication1.cpp pch.h
	g++ -Wall -c ConsoleApplication1.cpp

pch.o: pch.cpp pch.h matrix.o Digit.o Individual.o AG.o ArgsParser.o
	g++ -Wall -c pch.cpp

matrix.o: matrix.cpp matrix.h
	g++ -Wall -c matrix.cpp

Digit.o: Digit.cpp Digit.h matrix.o
	g++ -Wall -c Digit.cpp

Individual.o: Individual.cpp Individual.h matrix.o
	g++ -Wall -c Individual.cpp

AG.o: AG.cpp AG.h Individual.o Digit.o matrix.o
	g++ -Wall -c AG.cpp

ArgsParser.o: ArgsParser.cpp ArgsParser.h
	g++ -Wall -c ArgsParser.cpp