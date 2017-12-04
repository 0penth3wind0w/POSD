#INC_DIR = include

all: run

run: clean hw6
	./hw6

hw6: mainHw.o
ifeq (${OS}, Windows_NT)
		g++ -o hw6 mainHw.o -lgtest
else
		g++ -o hw6 mainHw.o -lgtest -lpthread
endif
mainHw.o: mainHw.cpp utParser.h term.h atom.h number.h variable.h struct.h list.h node.h
		g++ -std=gnu++0x -c mainHw.cpp

utAtom: mainAtom.o
ifeq (${OS}, Windows_NT)
		g++ -o utAtom mainAtom.o -lgtest
else
		g++ -o utAtom mainAtom.o -lgtest -lpthread
endif
mainAtom.o: mainAtom.cpp utAtom.h
		g++ -std=gnu++0x -c mainAtom.cpp

utVariable: mainVariable.o
ifeq (${OS}, Windows_NT)
		g++ -o utVariable mainVariable.o -lgtest
else
		g++ -o utVariable mainVariable.o -lgtest -lpthread
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

utTerm: mainTerm.o
ifeq (${OS}, Windows_NT)
		g++ -o utTerm mainTerm.o -lgtest
else
		g++ -o utTerm mainTerm.o -lgtest -lpthread
endif
mainTerm.o: mainTerm.cpp utTerm.h
		g++ -std=gnu++0x -c mainTerm.cpp

utStruct: mainStruct.o
ifeq (${OS}, Windows_NT)
		g++ -o utStruct mainStruct.o -lgtest
else
		g++ -o utStruct mainStruct.o -lgtest -lpthread
endif
mainStruct.o: mainStruct.cpp utStruct.h
		g++ -std=gnu++0x -c mainStruct.cpp

utList: mainList.o
ifeq (${OS}, Windows_NT)
		g++ -o utList mainList.o -lgtest
else
		g++ -o utList mainList.o -lgtest -lpthread
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

utParser: mainParser.o
ifeq (${OS}, Windows_NT)
	g++ -o utParser mainParser.o -lgtest
else	
	g++ -o utParser mainParser.o -lgtest -lpthread
endif
mainParser.o: mainParser.cpp term.h atom.h number.h variable.h struct.h scanner.h parser.h utParser.h
		g++ -std=c++11 -c mainParser.cpp


clean:	
ifeq (${OS}, Windows_NT)
		del *.o *.exe
else
		rm -f *.o ut*[!.h] hw*
endif
