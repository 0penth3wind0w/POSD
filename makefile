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


mainAtom.o: mainAtom.cpp utAtom.h atom.h
		g++ -std=c++11 -c mainAtom.cpp
utAtom: mainAtom.o
		g++ -o utAtom mainAtom.o -lgtest -lpthread

mainVariable.o: mainVariable.cpp utVariable.h Variable.h
		g++ -std=c++11 -c mainVariable.cpp
utVariable: mainVariable.o
		g++ -o utVariable mainVariable.o -lgtest -lpthread

mainNumber.o: mainNumber.cpp utNumber.h Number.h
		g++ -std=c++11 -c mainNumber.cpp
utNumber: mainNumber.o
		g++ -o utNumber mainNumber.o -lgtest -lpthread

mainTerm.o: mainTerm.cpp utTerm.h Number.h
		g++ -std=c++11 -c mainTerm.cpp
utTerm: mainTerm.o
		g++ -o utTerm mainTerm.o -lgtest -lpthread


clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o utTerm utAtom utNumber utVariable
endif
