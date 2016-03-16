CXX ?= g++
CFLAGS = -Wall -Wconversion -O3 -fPIC
OBJ = src/CharType.o src/SegDict.o src/SegFeat.o src/SegVocab.o src/SegProb.o src/StrFun.o

all: cwsp_train convert
	rm -rf *.o *.a
	cd src; rm -f *.a *.o
.PHONY: all

convert: convert.o $(OBJ)
	$(CXX) $(CFLAGS) -o convert convert.o $(OBJ)

convert.o: convert.cpp
	$(CXX) $(CFLAGS) -I./include -c convert.cpp

cwsp_train: cwsp_train.o src/MultiPerceptron.o src/Pretreatment.o $(OBJ) 
	$(CXX) $(CFLAGS) -o cwsp_train cwsp_train.o src/MultiPerceptron.o src/Pretreatment.o $(OBJ)

cwsp_train.o: cwsp_train.cpp
	$(CXX) $(CFLAGS) -I./include -c cwsp_train.cpp

src/CharType.o : src/CharType.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c CharType.cpp -o CharType.o

src/Pretreatment.o : src/Pretreatment.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c Pretreatment.cpp -o Pretreatment.o

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

src/MultiPerceptron.o : src/MultiPerceptron.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c MultiPerceptron.cpp -o MultiPerceptron.o

clean:
	rm -rf *.o *.a
	cd src; rm -f *.a *.o
	cd data; rm -rf train

cleanall:
	rm -rf cwsp_train convert
	rm -rf *.o *.a
	cd src; rm -f *.a *.o
	cd data; rm -rf train
