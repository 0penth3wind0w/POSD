#INC_DIR = include

#all: hw3

atom.o: atom.h atom.cpp
		g++ -std=gnu++0x -c atom.cpp
variable.o: variable.h variable.cpp
		g++ -std=gnu++0x -c variable.cpp
number.o: number.h number.cpp
		g++ -std=gnu++0x -c number.cpp
struct.o: struct.h struct.cpp
		g++ -std=gnu++0x -c struct.cpp

mainAtom.o: mainAtom.cpp utAtom.h
		g++ -std=gnu++0x -c mainAtom.cpp
utAtom: mainAtom.o atom.o variable.o number.o
ifeq (${OS}, Windows_NT)
		g++ -o utAtom mainAtom.o atom.o variable.o number.o -lgtest
else
		g++ -o utAtom mainAtom.o atom.o variable.o number.o -lgtest -lpthread
endif

mainVariable.o: mainVariable.cpp utVariable.h
		g++ -std=gnu++0x -c mainVariable.cpp
utVariable: mainVariable.o variable.o number.o atom.o struct.o
ifeq (${OS}, Windows_NT)
		g++ -o utVariable mainVariable.o variable.o number.o atom.o struct.o -lgtest
else
		g++ -o utVariable mainVariable.o variable.o number.o atom.o struct.o -lgtest -lpthread
endif

mainNumber.o: mainNumber.cpp utNumber.h
		g++ -std=gnu++0x -c mainNumber.cpp
utNumber: mainNumber.o number.o atom.o variable.o
ifeq (${OS}, Windows_NT)
		g++ -o utNumber mainNumber.o number.o atom.o variable.o -lgtest
else
		g++ -o utNumber mainNumber.o number.o atom.o variable.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utTerm.h
		g++ -std=gnu++0x -c mainTerm.cpp
utTerm: mainTerm.o atom.o variable.o number.o
ifeq (${OS}, Windows_NT)
		g++ -o hw2 mainTerm.o atom.o variable.o number.o -lgtest
else
		g++ -o hw2 mainTerm.o atom.o variable.o number.o -lgtest -lpthread
endif

mainStruct.o: mainStruct.cpp utStruct.h
		g++ -std=gnu++0x -c mainTerm.cpp
utStruct: mainStruct.o atom.o variable.o number.o
ifeq (${OS}, Windows_NT)
		g++ -o hw2 mainStruct.o atom.o variable.o number.o struct.o -lgtest
else
		g++ -o hw2 mainStruct.o atom.o variable.o number.o struct.o -lgtest -lpthread
endif

clean:	
ifeq (${OS}, Windows_NT)
		del *.o *.exe
else
		rm -f *.o utTerm utAtom utNumber utVariable hw2
endif
