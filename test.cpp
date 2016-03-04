#include "SegFeat.h"
#include "SegVocab.h"
#include "SegProb.h"
#include <string>
using namespace std;

int main()
{
    /* SegFeat test*/
    // std::cout<<"test"<<endl;
    // cwsp::Feat testFeat;
    // std::cout<<testFeat.UnigramLen()<<endl;
    // std::cout<<testFeat.BigramLen()<<endl;
    // std::cout<<testFeat.TrigramLen()<<endl;

    // string filename = "./data/Feature";
    // testFeat.LoadFeatureFile(filename.c_str());
    // std::cout<<testFeat.UnigramLen()<<endl;
    // std::cout<<testFeat.BigramLen()<<endl;
    // std::cout<<testFeat.TrigramLen()<<endl;
    // testFeat.SaveFeatureFile();

    // std::cout<<"test convert"<<endl;
    // filename = "./model/Feature";
    // string out = "./data/outtest";
    // testFeat.ConvertToBinaryFile(filename.c_str(), out.c_str());

    // cwsp::Feat testFeat1;
    // std::cout<<testFeat1.UnigramLen()<<endl;
    // std::cout<<testFeat1.BigramLen()<<endl;
    // std::cout<<testFeat1.TrigramLen()<<endl;

    // testFeat1.LoadFeatureFile(out.c_str());
    // std::cout<<testFeat1.UnigramLen()<<endl;
    // std::cout<<testFeat1.BigramLen()<<endl;
    // std::cout<<testFeat1.TrigramLen()<<endl;
    // testFeat1.SaveFeatureFile();


    /* SegProb test*/
    cout<<"SegProb Test:"<<endl;
    cwsp::SegProb testProb;

    int i=10;
    while(i--){
        testProb.InitProbCount(0);
        testProb.InitProbCount(3);
    };
    
    i=10;
    while(i--){
        testProb.InitProbCount(3); 
    };

    i=100;
    while(i--)
    {
        testProb.TransProbCount(0,1);
        testProb.TransProbCount(1,2);
        testProb.TransProbCount(2,0);
        testProb.TransProbCount(0,3);
        testProb.TransProbCount(3,0);
        testProb.TransProbCount(3,3);
    };

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<testProb.GetTransProb(i,j)<<" ";
        }
        cout<<endl;
    }
    
    testProb.CalcAllProb();
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            cout<<testProb.GetTransProb(i,j)<<" ";
        }
        cout<<endl;
    }
    testProb.SaveProbFile();

}