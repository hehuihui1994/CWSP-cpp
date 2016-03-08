/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#include "StrFun.h"

namespace cwsp
{
    void TrimLine(string & line)
    {
        line.erase(0,line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n")+1); 
    }
}