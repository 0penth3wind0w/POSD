hw8: mainHW.o atom.o struct.o list.o
ifeq (${OS}, Windows_NT)
		g++ -o hw8 mainHW.o atom.o struct.o list.o -lgtest
else
		g++ -o hw8 mainHW.o atom.o struct.o list.o -lgtest -lpthread
endif
mainHW.o: mainHW.cpp expression.h exception.h
	g++ -std=c++11 -c mainHW.cpp

all: clean hw8

atom.o: atom.cpp atom.h variable.h
		g++ -std=c++11 -c atom.cpp
list.o:list.cpp list.h
		g++ -std=c++11 -c list.cpp
struct.o:struct.cpp struct.h
		g++ -std=c++11 -c struct.cpp
shell.o:shell.cpp parser.h scanner.h
		g++ -std=c++11 -c shell.cpp

utAtom: mainAtom.o list.o atom.o struct.o
		g++ -o utAtom mainAtom.o atom.o list.o struct.o  -lgtest -lpthread
mainAtom.o: mainAtom.cpp utList.h utAtom.h atom.h utStruct.h struct.h
		g++ -std=c++11 -c mainAtom.cpp
utVariable: mainVariable.o atom.o struct.o
		g++ -o utVariable mainVariable.o atom.o struct.o -lgtest -lpthread
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=c++11 -c mainVariable.cpp

#exp: mainExp.o
#	g++ -o exp mainExp.o -lgtest -lpthread
#mainExp.o: mainExp.cpp exp.h global.h
#	g++ -std=c++11 -c mainExp.cpp

utScanner: mainScanner.o atom.o list.o struct.o scanner.h utScanner.h utParser.h parser.h
	g++ -o utScanner mainScanner.o atom.o list.o struct.o -lgtest -lpthread
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h utExp.h
		g++ -std=c++11 -c mainScanner.cpp
utIterator: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
	g++ -o utIterator mainIterator.o atom.o list.o struct.o -lgtest -lpthread
mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=c++11 -c mainIterator.cpp

#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=c++11 -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=c++11 -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=c++11 -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=c++11 -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=c++11 -c list.cpp

utException: mainException.o atom.o struct.o list.o
	g++ -o utException mainException.o atom.o struct.o list.o -lgtest -lpthread
mainException.o: mainException.cpp exception.h
	g++ -std=c++11 -c mainException.cpp

utExpression: mainExpression.o atom.o struct.o list.o
	g++ -o utExpression mainExpression.o atom.o struct.o list.o -lgtest -lpthread
mainExpression.o: mainExpression.cpp expression.h
	g++ -std=c++11 -c mainExpression.cpp

Shell: shell.o atom.o struct.o list.o parser.h scanner.h exp.h variable.h utParser.h
ifeq (${OS}, Windows_NT) 
	g++ -o Shell shell.o atom.o struct.o list.o -lgtest
else
	g++ -o Shell shell.o atom.o struct.o list.o -lgtest -lpthread
endif

clean:
	rm -f *.o *.gch ut*[!.h] hw* Shell
stat:
	wc *.h *.cpp
