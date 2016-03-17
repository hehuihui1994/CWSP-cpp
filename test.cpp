#include "SegFeat.h"
#include "SegVocab.h"
#include "SegProb.h"
#include "SegDict.h"
#include "Pretreatment.h"
#include "Config.h"
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    /* Pretreatment test */
    cout<<"Pretreatment test"<<endl;
    cwsp::Pretreatment t;
    t.LoadCharFile(false);
    t.LoadDictFile("model/Dict");
    // string featFile = argv[1];
    // string probFile = argv[2];
    string corpus = argv[1];
    string outfile = argv[2];
    // cout<<"Loading model..."<<endl;
    t.LoadFeatureFile("model/Feat");
    t.LoadProbFile("model/Prob");
    //cout<<"read corpus file..."<<endl;
    //cout<<t.TrainSegFile(corpus.c_str())<<endl;
    t.PrintInfo();
    
    cout<<"\nMaking train data..."<<endl;
    t.MakeTrainData(corpus.c_str(), outfile.c_str());
    cout<<"Finished."<<endl;
	return 1;
}
