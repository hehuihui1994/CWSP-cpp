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
    // t.LoadFeatureFile(featFile.c_str());
    // t.LoadProbFile(probFile.c_str());
    cout<<"read corpus file..."<<endl;
    cout<<t.TrainSegFile(corpus.c_str())<<endl;
    t.PrintInfo();
    
    cout<<"\nMaking train data..."<<endl;
    t.MakeTrainData(corpus.c_str(), outfile.c_str());
    cout<<"Finished."<<endl;

    /* SegDict test 
    cout<<"SegDict test\n";
    cwsp::SegDict dict("data/Dict");
    pair<int, string> ans;
    ans = dict.GetDictInfo(" ");
    cout<<"  "<<ans.first<<" "<<ans.second<<endl;
    dict.SaveDictFile();*/

    /* SegFeat test
    cout<<"SegFeat test"<<endl;
    cwsp::SegFeat testFeat;
    std::cout<<testFeat.UnigramLen()<<endl;
    std::cout<<testFeat.BigramLen()<<endl;
    std::cout<<testFeat.TrigramLen()<<endl;

    string filename = "data/Feature";
    testFeat.LoadFeatureFile(filename.c_str());
    cout<<"After loading:"<<endl;
    std::cout<<testFeat.UnigramLen()<<endl;
    std::cout<<testFeat.BigramLen()<<endl;
    std::cout<<testFeat.TrigramLen()<<endl;
    testFeat.SaveFeatureFile();

    std::cout<<"test convert"<<endl;
    filename = "model/Feature";
    string out = "data/outtest";
    cout<<"CONVERTING..."<<endl;
    testFeat.ConvertToBinaryFile(filename.c_str(), out.c_str());
    cout<<"Finished."<<endl;

    cwsp::SegFeat testFeat1;
    cout<<"another test case:"<<endl;
    std::cout<<testFeat1.UnigramLen()<<endl;
    std::cout<<testFeat1.BigramLen()<<endl;
    std::cout<<testFeat1.TrigramLen()<<endl;

    testFeat1.LoadFeatureFile(out.c_str());
    cout<<"After load binary file:"<<endl;
    std::cout<<testFeat1.UnigramLen()<<endl;
    std::cout<<testFeat1.BigramLen()<<endl;
    std::cout<<testFeat1.TrigramLen()<<endl;
    testFeat1.SaveFeatureFile();*/


    /* SegProb test
    cout<<"SegProb Test:"<<endl;
    cwsp::SegProb testProb;
	string file = argv[1];
	testProb.LoadProbFile(file.c_str());
    // testProb.CalcAllProb();

	for(int i=0;i<4;i++)
    {
		cout<<testProb.GetInitProb(i);
        cout<<endl;
    }

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<testProb.GetTransProb(i,j)<<" ";
        }
        cout<<endl;
    }*/
	/*
    // testProb.SaveProbFile();
	testProb.ConvertToBinaryFile("model/Prob","data/Prob.bin");
	cwsp::SegProb testProb1;
	testProb1.LoadProbFile("data/Prob.bin");
	for(int i=0;i<4;i++)
    {
		cout<<testProb1.GetInitProb(i);
        cout<<endl;
    }

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<testProb1.GetTransProb(i,j)<<" ";
        }
        cout<<endl;
    }
	*/
	return 1;
}
