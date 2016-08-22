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
#include "MultiPerceptron.h"
#include "Config.h"
using namespace std;

void print_help() {
    cout << cwsp::g_copyright
        << "\n\nNAME\n"
        << "    convert -- convert model & src file of CWSP from text to binary file\n"
        << "USAGE: \n"
        << "    convert [-A] [-c][-dfpm file]\n"
        << "OPTIONS:\n"
        << "     -h    Print help infomation\n\n"
        << "     -A    Convert all the model & src file with default path. Include: \n"
        << "           CharType(./data/*), Feat(./model/Feat), Prob(./model/Prob), Dict\n"
        << "           (./model/Dict) and Model(./model/Model). And also you can use \n"
        << "           following command [-dfpm file] to give a specified file.\n\n"
        << "     Following command can be used to convert a specified model file.\n"
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
    return true;
}

bool SegFeatConvert(string featfile, string binaryFeat){
    cwsp::SegFeat myFeat;
    return myFeat.ConvertToBinaryFile(featfile.c_str(), binaryFeat.c_str());
}

bool SegDictConvert(string dictfile, string binaryDict) {
    cwsp::SegDict myDict;
    return myDict.ConvertToBinaryFile(dictfile.c_str(), binaryDict.c_str());
}

bool SegProbConvert(string probfile, string binaryProb) {
    cwsp::SegProb myProb;
    return myProb.ConvertToBinaryFile(probfile.c_str(), binaryProb.c_str());
}

bool MultiPerceptronConvert(string modelfile, string binaryModel) {
    cwsp::MultiPerceptron myPercp;
    return myPercp.ConvertToBinaryFile(modelfile, binaryModel);
}

int convert(int argc, char *argv[])
{
#ifdef WIN32
    string _modelpath = "model\\";
#else
    string _modelpath = "model/";
#endif

    string featfile = _modelpath + "Feat";
    string probfile = _modelpath + "Prob";
    string dictfile = _modelpath + "Dict";
    string modelfile = _modelpath + "Model";

    bool A = false,c = false,d = false,f = false,p = false,m = false;
    read_parameters(argc, argv, &A, &c, &d, dictfile, &f, featfile, &p, probfile, &m, modelfile);

    string binaryFeat = featfile + ".bin";
    string binaryProb = probfile + ".bin";
    string binaryDict = dictfile + ".bin";
    string binaryModel = modelfile + ".bin";

    if(!(A||c||d||f||p||m)){
        cerr << "Not enough parameters!" << endl;
        print_help();
        exit(0);
    }

    if(A||c){
        if(CharTypeConvert())
            cerr << "CharType file conversion is finished.\n" << endl;
        else
            cerr << "Error! Failed to convert CharType file to binary.\n" << endl;
    }
    if(A||d){
        if(SegDictConvert(dictfile, binaryDict))
            cerr << "Dictionary file conversion is finished.\n" << endl;
        else
            cerr << "Error! Failed to convert Dictionary file to binary.\n"<<endl;
    }
    if(A||f){
        if(SegFeatConvert(featfile, binaryFeat))
            cerr << "Feature file conversion is finished.\n" << endl;
        else
            cerr << "Error! Failed to convert Feature file to binary.\n"<<endl;
    }
    if(A||p){
        if(SegProbConvert(probfile, binaryProb))
            cerr << "Probability file conversion is finished.\n" << endl;
        else
            cerr << "Error! Failed to convert Probability file to binary.\n"<<endl;
    }
    if(A||m){
        if(MultiPerceptronConvert(modelfile, binaryModel))
            cerr << "MultiPerceptron model file conversion is finished.\n" << endl;
        else
            cerr << "Error! Failed to convert MultiPerceptron model file to binary.\n"<<endl;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    return convert(argc, argv);
}