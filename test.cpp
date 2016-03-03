#include "Config.h"
#include "SegFeat.h"

int main()
{
    cwsp::Feat testFeat;
    std::cout<<testFeat.UnigramLen()<<endl;
    std::cout<<testFeat.BigramLen()<<endl;
    std::cout<<testFeat.TrigramLen()<<endl;
}