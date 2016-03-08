CXX ?= g++
CFLAGS = -Wall -Wconversion -O3 -fPIC
TARGET = test
OBJ = test.o src/SegDict.o src/SegFeat.o src/SegVocab.o src/SegProb.o src/StrFun.o

$(TARGET) : $(OBJ) 
	$(CXX) $(CFLAGS) -o test $(OBJ)

test.o : test.cpp
	$(CXX) $(CFLAGS) -I./include -c test.cpp

src/SegDict.o : src/SegDict.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegDict.cpp -o SegDict.o 

src/SegFeat.o : src/SegFeat.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegFeat.cpp -o SegFeat.o

src/SegVocab.o : src/SegVocab.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegVocab.cpp -o SegVocab.o 

src/SegProb.o : src/SegProb.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegProb.cpp -o SegProb.o

src/StrFun.o : src/StrFun.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c StrFun.cpp -o StrFun.o

clean:
	rm -rf *.o *.a $(TARGET)
	cd src; rm -f *.a *.o
