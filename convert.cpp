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

void print_help() {
    cout << cwsp::g_copyright
        << "\n\nNAME\n"
        << "    convert -- convert model & src file of CWSP from text to binary file\n"
        << "USAGE: \n"
        << "    convert [-Ac][-dfpm file]\n"
        << "OPTIONS:\n"
        << "     -h    Print help infomation\n\n"
        << "     -A    Convert all the model & src file with default path. Include: \n"
        << "           CharType(./data/*), Feat(./model/Feat), Prob(./model/Prob), Dict\n"
        << "           (./model/Dict) and Model(./model/Model). And also you can use \n"
        << "           following command [-dfpm file] to give a specified file.\n\n"
        << "     -c    Convert all the CharType files under './data/'\n\n"
        << "     -d    Convert Dict file from the specified file(default: ./model/Dict)\n\n"
        << "     -f    Convert Feat file from the specified file(default: ./model/Feat)\n\n"
        << "     -p    Convert Prob file from the specified file(default: ./model/Prob)\n\n"
        << "     -m    Convert MultiPerceptron Model file from the specified file(default:\n"
        << "           ./model/Model)\n"
        << endl;
}

void read_parameters(int argc, char *argv[], bool *All, bool *c, bool *d,
                     string &dictfile, bool *f, string &featfile, bool *p,
                     string &probfile, bool *m, string &modelfile) {
    int i;
    for (i = 1; (i<argc) && (argv[i])[0]=='-'; i++) {
        switch ((argv[i])[1]) {
            case 'h':
                print_help();
                exit(0);
            case 'A':
                *All = true;
                break;
            case 'c':
                *c = true;
                break;
            case 'd':
                *d = true;
                if(i+1<argc && argv[i+1][0] != '-') {
                    dictfile.clear();
                    dictfile = string(argv[++i]);
                }
                break;
            case 'f':
                *f = true;
                if(i+1<argc && argv[i+1][0] != '-') {
                    featfile.clear();
                    featfile = string(argv[++i]);
                }
                break;
            case 'p':
                *p = true;
                if(i+1<argc && argv[i+1][0] != '-') {
                    probfile.clear();
                    probfile = string(argv[++i]);
                }
                break;
            case 'm':
                *m = true;
                if(i+1<argc && argv[i+1][0] != '-') {
                    modelfile.clear();
                    modelfile = string(argv[++i]);
                }
                break;
            default:
                cout << "Unrecognized option: " << argv[i] << "!" << endl;
                print_help();
                exit(0);
        }
    }
}

bool CharTypeConvert(){
    cwsp::CharType myCharType;
    // this func has no return value while it should have return a bool
    // so need change the CharType.Convert2Binary() func
    myCharType.Convert2Binary();
}

int main(int argc, char *argv[])
{
    // cerr << cwsp::g_copyright << endl;

#ifdef WIN32
    string _modelpath = "model\\";
#else
    string _modelpath = "model/";
#endif

    // cwsp::CharType myCharType;
    // myCharType.Convert2Binary();

    string featfile = _modelpath + "Feat";
    string probfile = _modelpath + "Prob";
    string dictfile = _modelpath + "Dict";
    string modelfile = _modelpath + "Model";
    string binaryFeat = _modelpath + "Feat.bin";
    string binaryProb = _modelpath + "Prob.bin";
    string binaryDict = _modelpath + "Dict.bin";
    string binaryModel = _modelpath + "Model.bin";

    bool A = false,c = false,d = false,f = false,p = false,m = false;
    // print_help();
    // cerr << "Convert txt to binary......\n" << endl;
    // cwsp::SegFeat myFeat;
    // cwsp::SegProb myProb;
    // cwsp::SegDict myDict;
    // if(myFeat.ConvertToBinaryFile(featfile.c_str(), binaryFeat.c_str())){
    //     cerr << "Feature file conversion is finished.\n" << endl;
    // }
    // else
    // {
    //     cerr << "Error! Failed to convert Feature file to binary.\n"<<endl;
    // }

    // if(myProb.ConvertToBinaryFile(probfile.c_str(), binaryProb.c_str())){
    //     cerr << "Probability file conversion is finished.\n" << endl;
    // }
    // else
    // {
    //     cerr << "Error! Failed to convert Probability file to binary.\n"<<endl;
    // }

    // if(myDict.ConvertToBinaryFile(dictfile.c_str(), binaryDict.c_str())){
    //     cerr << "Dictionary file conversion is finished.\n" << endl;
    // }
    // else
    // {
    //     cerr << "Error! Failed to convert Dictionary file to binary.\n"<<endl;
    // }
    // cerr << "\n\nConversion is finished." << endl;
    return 0;
}