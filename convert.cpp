/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.
* Copyright (C) 2016 Shenghuan He
* Contact: heshenghuan328@gmail.com

* Permission to use, copy, modify, and distribute this software for
* any non-commercial purpose is hereby granted without fee, provided
* that the above copyright notice appear in all copies and that both
* that copyright notice. 
* It is provided "as is" without express or implied warranty.
*********************************************************************/

#include "SegFeat.h"
#include "SegVocab.h"
#include "SegProb.h"
#include "SegDict.h"
#include "CharType.h"
#include "Config.h"
using namespace std;

int main(int argc, char *argv[])
{
    cerr << cwsp::g_copyright << endl;

#ifdef WIN32
    string _datapath = "model\\";
#else
    string _datapath = "model/";
#endif

    cwsp::CharType myCharType;
    myCharType.Convert2Binary();

    string featfile = _datapath + "Feat";
    string probfile = _datapath + "Prob";
    string dictfile = _datapath + "Dict";
    string binaryFeat = _datapath + "Feat.bin";
    string binaryProb = _datapath + "Prob.bin";
    string binaryDict = _datapath + "Dict.bin";

    cerr << "Convert txt to binary......\n" << endl;
    cwsp::SegFeat myFeat;
    cwsp::SegProb myProb;
    cwsp::SegDict myDict;
    if(myFeat.ConvertToBinaryFile(featfile.c_str(), binaryFeat.c_str())){
        cerr << "Feature file convertion is finished.\n" << endl;
    }
    else
    {
        cerr << "Error! Failed to convert Feature file to binary.\n"<<endl;
    }

    if(myProb.ConvertToBinaryFile(probfile.c_str(), binaryProb.c_str())){
        cerr << "Probability file convertion is finished.\n" << endl;
    }
    else
    {
        cerr << "Error! Failed to convert Probability file to binary.\n"<<endl;
    }

    if(myDict.ConvertToBinaryFile(dictfile.c_str(), binaryDict.c_str())){
        cerr << "Dictionary file convertion is finished.\n" << endl;
    }
    else
    {
        cerr << "Error! Failed to convert Dictionary file to binary.\n"<<endl;
    }
    cerr << "\n\nConvertion is finished." << endl;
    return 0;
}