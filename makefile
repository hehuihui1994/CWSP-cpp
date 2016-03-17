CXX ?= g++
CFLAGS = -Wall -Wconversion -O3 -fPIC
OBJ = src/CharType.o src/SegDict.o src/SegFeat.o src/SegVocab.o src/SegProb.o src/StrFun.o src/Segmentor.o src/MultiPerceptron.o src/Pretreatment.o

all: cwsp_train cwsp_seg convert
	rm -rf *.o *.a
.PHONY: all

test: test.o $(OBJ)
	$(CXX) $(CFLAGS) -o test test.o $(OBJ)
	rm -rf test.o

test.o: test.cpp
	$(CXX) $(CFLAGS) -I./include -c test.cpp

convert: convert.o $(OBJ)
	$(CXX) $(CFLAGS) -o convert convert.o $(OBJ)

convert.o: convert.cpp
	$(CXX) $(CFLAGS) -I./include -c convert.cpp

cwsp_train: cwsp_train.o $(OBJ) 
	$(CXX) $(CFLAGS) -o cwsp_train cwsp_train.o $(OBJ)

cwsp_train.o: cwsp_train.cpp
	$(CXX) $(CFLAGS) -I./include -c cwsp_train.cpp

cwsp_seg: cwsp_seg.o $(OBJ)
	$(CXX) $(CFLAGS) -o cwsp_seg cwsp_seg.o $(OBJ)

cwsp_seg.o: cwsp_seg.cpp
	$(CXX) $(CFLAGS) -I./include -c cwsp_seg.cpp

src/CharType.o: src/CharType.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c CharType.cpp -o CharType.o

src/SegDict.o: src/SegDict.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegDict.cpp -o SegDict.o 

src/SegFeat.o: src/SegFeat.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegFeat.cpp -o SegFeat.o

src/SegVocab.o: src/SegVocab.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegVocab.cpp -o SegVocab.o 

src/SegProb.o: src/SegProb.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c SegProb.cpp -o SegProb.o

src/StrFun.o: src/StrFun.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c StrFun.cpp -o StrFun.o

src/MultiPerceptron.o: src/MultiPerceptron.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c MultiPerceptron.cpp -o MultiPerceptron.o

src/Pretreatment.o: src/Pretreatment.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c Pretreatment.cpp -o Pretreatment.o

src/Segmentor.o: src/Segmentor.cpp
	cd src; $(CXX) $(CFLAGS) -I../include -c Segmentor.cpp -o Segmentor.o

clean:
	rm -rf *.o *.a
	cd src; rm -f *.a *.o
	cd data; rm -rf train

cleanall:
	rm -rf cwsp_train cwsp_seg convert
	rm -rf *.o *.a
	cd src; rm -f *.a *.o
	cd data; rm -rf train
