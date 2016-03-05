#include "SegFeat.h"
#include "SegVocab.h"
#include "SegProb.h"
#include <string>
using namespace std;

int main()
{
    /* SegFeat test
    std::cout<<"test"<<endl;
    cwsp::Feat testFeat;
    std::cout<<testFeat.UnigramLen()<<endl;
    std::cout<<testFeat.BigramLen()<<endl;
    std::cout<<testFeat.TrigramLen()<<endl;

    string filename = "data\\Feature";
    testFeat.LoadFeatureFile(filename.c_str());
    std::cout<<testFeat.UnigramLen()<<endl;
    std::cout<<testFeat.BigramLen()<<endl;
    std::cout<<testFeat.TrigramLen()<<endl;
    testFeat.SaveFeatureFile();

    std::cout<<"test convert"<<endl;
    filename = "model\\Feature";
    string out = "data\\outtest";
    testFeat.ConvertToBinaryFile(filename.c_str(), out.c_str());

    cwsp::Feat testFeat1;
    std::cout<<testFeat1.UnigramLen()<<endl;
    std::cout<<testFeat1.BigramLen()<<endl;
    std::cout<<testFeat1.TrigramLen()<<endl;

    testFeat1.LoadFeatureFile(out.c_str());
    std::cout<<testFeat1.UnigramLen()<<endl;
    std::cout<<testFeat1.BigramLen()<<endl;
    std::cout<<testFeat1.TrigramLen()<<endl;
    testFeat1.SaveFeatureFile();
	*/


    /* SegProb test*/
    cout<<"SegProb Test:"<<endl;
    cwsp::SegProb testProb;
	testProb.LoadProbFile("model\\Prob");
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
    }
    // testProb.SaveProbFile();
	testProb.ConvertToBinaryFile("model\\Prob","data\\Prob.bin");
	cwsp::SegProb testProb1;
	testProb1.LoadProbFile("data\\Prob.bin");
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
	return 1;
}