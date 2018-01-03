#INC_DIR = include

all: hw7

run: clean utIterator
	./utIterator

hw7: mainIterator.o list.o struct.o  term.o
ifeq (${OS}, Windows_NT)
		g++ -o hw7 mainIterator.o list.o struct.o term.o -lgtest
else
		g++ -o hw7 mainIterator.o list.o struct.o term.o -lgtest -lpthread
endif

mainHw.o: mainHw.cpp utIterator.h term.h atom.h number.h variable.h struct.h list.h node.h iterator.h

term.o: term.cpp term.h iterator.h
		g++ -std=gnu++0x -c term.cpp

struct.o: struct.cpp struct.h
		g++ -std=gnu++0x -c struct.cpp

list.o: list.cpp list.h
		g++ -std=gnu++0x -c list.cpp

utMigrate: mainMigrate.o term.o struct.o list.o
		g++ -o utMigrate mainMigrate.o term.o struct.o list.o -lgtest -lpthread
mainMigrate.o: mainMigrate.cpp utTerm.h utAtom.h utNumber.h utVariable.h utStruct.h utList.h
		g++ -std=gnu++0x -c mainMigrate.cpp

utFunctions: mainFunctions.o term.o struct.o list.o
		g++ -o utFunctions mainFunctions.o term.o struct.o list.o -lgtest -lpthread
mainFunctions.o: mainFunctions.cpp utScanner.h utParser.h
		g++ -std=gnu++0x -c mainFunctions.cpp


utTerm: mainTerm.o term.o
ifeq (${OS}, Windows_NT)
		g++ -o utTerm mainTerm.o term.o -lgtest
else
		g++ -o utTerm mainTerm.o term.o -lgtest -lpthread
endif
mainTerm.o: mainTerm.cpp utTerm.h
		g++ -std=gnu++0x -c mainTerm.cpp

utAtom: mainAtom.o term.o
ifeq (${OS}, Windows_NT)
		g++ -o utAtom mainAtom.o term.o -lgtest
else
		g++ -o utAtom mainAtom.o term.o -lgtest -lpthread
endif
mainAtom.o: mainAtom.cpp utAtom.h
		g++ -std=gnu++0x -c mainAtom.cpp

utVariable: mainVariable.o term.o struct.o
ifeq (${OS}, Windows_NT)
		g++ -o utVariable mainVariable.o term.o struct.o -lgtest
else
		g++ -o utVariable mainVariable.o term.o struct.o -lgtest -lpthread
endif
mainVariable.o: mainVariable.cpp utVariable.h
		g++ -std=gnu++0x -c mainVariable.cpp

utNumber: mainNumber.o
ifeq (${OS}, Windows_NT)
		g++ -o utNumber mainNumber.o -lgtest
else
		g++ -o utNumber mainNumber.o -lgtest -lpthread
endif
mainNumber.o: mainNumber.cpp utNumber.h
		g++ -std=gnu++0x -c mainNumber.cpp

utStruct: mainStruct.o term.o struct.o
ifeq (${OS}, Windows_NT)
		g++ -o utStruct mainStruct.o term.o struct.o -lgtest
else
		g++ -o utStruct mainStruct.o term.o struct.o -lgtest -lpthread
endif
mainStruct.o: mainStruct.cpp utStruct.h
		g++ -std=gnu++0x -c mainStruct.cpp

utList: mainList.o term.o struct.o list.o
ifeq (${OS}, Windows_NT)
		g++ -o utList mainList.o term.o struct.o list.o -lgtest
else
		g++ -o utList mainList.o term.o struct.o list.o -lgtest -lpthread
endif
mainList.o: mainList.cpp utList.h
		g++ -std=gnu++0x -c mainList.cpp

utScanner: mainScanner.o
ifeq (${OS}, Windows_NT)
	g++ -o utScanner mainScanner.o -lgtest
else	
	g++ -o utScanner mainScanner.o -lgtest -lpthread
endif
mainScanner.o: mainScanner.cpp utScanner.h
		g++ -std=c++11 -c mainScanner.cpp

utParser: mainParser.o term.o struct.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o utParser mainParser.o term.o struct.o list.o -lgtest
else	
	g++ -o utParser mainParser.o term.o struct.o list.o -lgtest -lpthread
endif
mainParser.o: mainParser.cpp term.h atom.h number.h variable.h struct.h scanner.h parser.h utParser.h
		g++ -std=c++11 -c mainParser.cpp

utIterator: mainIterator.o list.o struct.o  term.o
	g++ -o utIterator mainIterator.o list.o struct.o term.o -lgtest -lpthread
mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=gnu++0x -c mainIterator.cpp

utExp: mainExp.o term.o struct.o list.o atom.h struct.h variable.h parser.h scanner.h
	g++ -o utExp mainExp.o term.o struct.o list.o -lgtest -lpthread
mainExp.o: mainExp.cpp utExp.h atom.h struct.h variable.h parser.h scanner.h
	g++ -std=gnu++0x -c mainExp.cpp

clean:	
ifeq (${OS}, Windows_NT)
		del *.o *.exe
else
		rm -f *.o *.gch ut*[!.h] hw*
endif
