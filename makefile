#INC_DIR = include

#all: hw3

hw3: mainHw3.o
ifeq (${OS}, Windows_NT)
		g++ -o hw3 mainHw3.o -lgtest
else
		g++ -o hw3 mainHw3.o -lgtest -lpthread
endif
mainHw3.o: mainHw3.cpp utVariable.h utStruct.h
		g++ -std=gnu++0x -c mainHw3.cpp


mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h
		g++ -std=gnu++0x -c mainAtom.cpp
utAtom: mainAtom.o
ifeq (${OS}, Windows_NT)
		g++ -o utAtom mainAtom.o -lgtest
else
		g++ -o utAtom mainAtom.o -lgtest -lpthread
endif

mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=gnu++0x -c mainVariable.cpp
utVariable: mainVariable.o
ifeq (${OS}, Windows_NT)
		g++ -o utVariable mainVariable.o -lgtest
else
		g++ -o utVariable mainVariable.o -lgtest -lpthread
endif

mainNumber.o: mainNumber.cpp utNumber.h number.h
		g++ -std=gnu++0x -c mainNumber.cpp
utNumber: mainNumber.o
ifeq (${OS}, Windows_NT)
		g++ -o utNumber mainNumber.o -lgtest
else
		g++ -o utNumber mainNumber.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utTerm.h
		g++ -std=gnu++0x -c mainTerm.cpp
utTerm: mainTerm.o
ifeq (${OS}, Windows_NT)
		g++ -o utTerm mainTerm.o -lgtest
else
		g++ -o utTerm mainTerm.o -lgtest -lpthread
endif

mainStruct.o: mainStruct.cpp utStruct.h atom.h number.h variable.h struct.h
		g++ -std=gnu++0x -c mainStruct.cpp
utStruct: mainStruct.o
ifeq (${OS}, Windows_NT)
		g++ -o utStruct mainStruct.o -lgtest
else
		g++ -o utStruct mainStruct.o -lgtest -lpthread
endif

clean:	
ifeq (${OS}, Windows_NT)
		del *.o *.exe
else
		rm -f *.o ut*[!.h] hw*
endif
