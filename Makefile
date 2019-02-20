#
# Makefile
# Project_1:
# Files included in project: simulator.cpp simulator.h
# Author: Demonna Wade

CXX = g++
LD = g++
CXXFLAGS = -g -pthread -std=c++11
LDFLAGS = -g -pthread

#
# Any libraries we might need.
#
LIBRARYS = -lpthread

simulator: simulator.o process.o thread.o
	${LD} ${LDFLAGS} simulator.o process.o thread.o -o $@ ${LIBRARYS}

simulator.o : simulator.cpp simulator.h
	${CXX} -c ${CXXFLAGS} -o $@ $<

process.o : process.cpp process.h
	${CXX} -c ${CXXFLAGS} -o $@ $<

thread.o : thread.cpp thread.h
	${CXX} -c ${CXXFLAGS} -o $@ $<


#
# Please remember not to submit objects or binarys.
#
clean:
	rm -f core simulator.o thread.o process.o simulator

#
# This might work to create the submission tarball in the formal I asked for.
#
submit:
	rm -f core Project_1 simulator simulator.o process.o thread.o
	mkdir "dwade-D1"
	cp Makefile README.txt *.h *.cpp "dwade-D1"
	tar cf "dwade-D1".tar "dwade-D1"
