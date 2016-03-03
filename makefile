CXX ?= g++
CFLAGS = -Wall -Wconversion -O3 -fPIC -lstdc++

test : src/SegFeat.o
	$(CXX) $(CFLAGS) -I./include test.cpp src/SegFeat.o -o test -lm

src/SegFeat.o : src/SegFeat.cpp src/SegVocab.o
	cd src; $(CXX) $(CFLAGS) -I../include -c SegFeat.cpp SegVocab.o -o SegFeat.o -lm

src/SegVocab.o : src/SegVocab.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegVocab.cpp -o SegVocab.o 

clean:
	rm -rf *.o *.a
	cd src; rm -f *.a *.o
	cd model; rm -rf *
