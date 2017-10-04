INC_DIR = include

all: hw2

hw2: mainTerm.o Atom.o Variable.o Number.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o Atom.o Variable.o Number.o -lgtest
else
	g++ -o hw2 mainTerm.o Atom.o Variable.o Number.o -lgtest -lpthread
endif

Atom.o: $(INC_DIR)/atom.h atom.cpp
		g++ --std=c++11 -o Atom.o -c atom.cpp
Variable.o: $(INC_DIR)/variable.h variable.cpp
		g++ --std=c++11 -o Variable.o -c variable.cpp
Number.o: $(INC_DIR)/number.h number.cpp
		g++ --std=c++11 -o Number.o -c number.cpp

mainAtom.o: mainAtom.cpp utAtom.h
		g++ --std=c++11 -c mainAtom.cpp
utAtom: mainAtom.o Atom.o Variable.o Number.o
ifeq (${OS}, Windows_NT)
	g++ -o utAtom mainAtom.o Atom.o Variable.o Number.o -lgtest
else
	g++ -o utAtom mainAtom.o Atom.o Variable.o Number.o -lgtest -lpthread
endif

mainVariable.o: mainVariable.cpp utVariable.h
		g++ --std=c++11 -c mainVariable.cpp
utVariable: mainVariable.o Variable.o Number.o Atom.o
ifeq (${OS}, Windows_NT)
	g++ -o utVariable mainVariable.o Variable.o Number.o Atom.o -lgtest
else
	g++ -o utVariable mainVariable.o Variable.o Number.o Atom.o -lgtest -lpthread
endif

mainNumber.o: mainNumber.cpp utNumber.h
		g++ --std=c++11 -c mainNumber.cpp
utNumber: mainNumber.o Number.o Atom.o Variable.o
ifeq (${OS}, Windows_NT)
	g++ -o utNumber mainNumber.o Number.o Atom.o Variable.o -lgtest
else
	g++ -o utNumber mainNumber.o Number.o Atom.o Variable.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utTerm.h
		g++ --std=c++11 -c mainTerm.cpp
utTerm: mainTerm.o Atom.o Variable.o Number.o
ifeq (${OS}, Windows_NT)
		g++ -o utTerm mainTerm.o Atom.o Variable.o Number.o -lgtest
else
	g++ -o utTerm mainTerm.o Atom.o Variable.o Number.o -lgtest -lpthread
endif

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o utTerm utAtom utNumber utVariable hw2
endif
