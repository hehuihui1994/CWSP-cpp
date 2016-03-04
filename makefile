CXX ?= g++
CFLAGS = -Wall -Wconversion -O3 -fPIC
TARGET = test

$(TARGET) : test.o src/SegFeat.o src/SegVocab.o src/SegProb.o
	$(CXX) $(CFLAGS) -o test test.o src/SegFeat.o src/SegVocab.o src/SegProb.o

test.o : test.cpp
	$(CXX) $(CFLAGS) -I./include -c test.cpp

src/SegFeat.o : src/SegFeat.cpp
	cd src; $(CXX) $(CFLAGS) -I../include  -c SegFeat.cpp -o SegFeat.o

src/SegVocab.o : src/SegVocab.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegVocab.cpp -o SegVocab.o 

src/SegProb.o : src/SegProb.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegProb.cpp -o SegProb.o

clean:
	rm -rf *.o *.a $(TARGET)
	cd src; rm -f *.a *.o
