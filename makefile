CXX ?= g++
CFLAGS = -Wall -Wconversion -O3 -fPIC

test : test.o src/SegFeat.o src/SegVocab.o
	$(CXX) $(CFLAGS) -o test test.o src/SegFeat.o src/SegVocab.o

test.o : test.cpp
	$(CXX) $(CFLAGS) -I./include -c test.cpp

src/SegFeat.o : src/SegFeat.cpp
	cd src; $(CXX) $(CFLAGS) -I../include  -c SegFeat.cpp -o SegFeat.o

src/SegVocab.o : src/SegVocab.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegVocab.cpp -o SegVocab.o 

clean:
	rm -rf *.o *.a
	cd src; rm -f *.a *.o
	#cd model; rm -rf *
