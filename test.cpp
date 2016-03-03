#include "SegFeat.h"
#include "SegVocab.h"
#include <string>

int main()
{
    std::cout<<"test"<<endl;
    cwsp::Feat testFeat;
    std::cout<<testFeat.UnigramLen()<<endl;
    std::cout<<testFeat.BigramLen()<<endl;
    std::cout<<testFeat.TrigramLen()<<endl;

    string filename = "./data/Feature";
    testFeat.LoadFeatureFile(filename.c_str());
    std::cout<<testFeat.UnigramLen()<<endl;
    std::cout<<testFeat.BigramLen()<<endl;
    std::cout<<testFeat.TrigramLen()<<endl;
    testFeat.SaveFeatureFile();

    std::cout<<"test convert"<<endl;
    filename = "./model/Feature";
    string out = "./data/outtest";
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
}