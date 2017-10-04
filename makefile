INC_DIR = include

#all: hw1

#hw1: main.o Shapes.o Media.o Sort.o
#ifeq (${OS}, Windows_NT)
#	g++ -o hw1 main.o Shapes.o Media.o Sort.o -lgtest
#else
#	g++ -o hw1 main.o Shapes.o Media.o Sort.o -lgtest -lpthread
#endif
	

#Shapes.o: $(INC_DIR)/Shapes.h Shapes.cpp
#	g++ -std=gnu++0x -c Shapes.cpp
#Media.o: $(INC_DIR)/Media.h Media.cpp
#	g++ -std=gnu++0x -c Media.cpp
#Sort.o: $(INC_DIR)/Sort.h Sort.cpp
#	g++ -std=gnu++0x -c Sort.cpp
#main.o: main.cpp utSort.h 
#	g++ -std=gnu++0x -c main.cpp

#Number.o: Number.h Number.cpp
#	g++ -std=gnu++0x -c Number.cpp
#Variable.o: Variable.h Variable.cpp
#	g++ -std=gnu++0x -c Variable.cpp

Atom.o: $(INC_DIR)/atom.h atom.cpp
		g++ -std=gnu++0x -o Atom.o -c atom.cpp
Variable.o: $(INC_DIR)/variable.h variable.cpp
		g++ -std=gnu++0x -o Variable.o -c variable.cpp
Number.o: $(INC_DIR)/number.h number.cpp
		g++ -std=gnu++0x -o Number.o -c number.cpp

mainAtom.o: mainAtom.cpp utAtom.h
		g++ -std=c++11 -c mainAtom.cpp
utAtom: mainAtom.o Atom.o Variable.o Number.o
		g++ -o utAtom mainAtom.o Atom.o Variable.o Number.o -lgtest -lpthread

mainVariable.o: mainVariable.cpp utVariable.h
		g++ -std=c++11 -c mainVariable.cpp
utVariable: mainVariable.o Variable.o Number.o Atom.o
		g++ -o utVariable mainVariable.o Variable.o Number.o Atom.o -lgtest -lpthread

mainNumber.o: mainNumber.cpp utNumber.h
		g++ -std=c++11 -c mainNumber.cpp
utNumber: mainNumber.o Number.o Atom.o Variable.o
		g++ -o utNumber mainNumber.o Number.o Atom.o Variable.o -lgtest -lpthread

mainTerm.o: mainTerm.cpp utTerm.h
		g++ -std=c++11 -c mainTerm.cpp
utTerm: mainTerm.o Atom.o Variable.o Number.o
		g++ -o utTerm mainTerm.o Atom.o Variable.o Number.o -lgtest -lpthread


clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o utTerm utAtom utNumber utVariable
endif
