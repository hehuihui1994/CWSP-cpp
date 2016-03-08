/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#ifndef SEGDICT_H_
#define SEGDICT_H_

#include "Config.h"
#include "StrFun.h"

namespace cwsp
{
    class SegDict
    {
    public:
        SegDict(const char *DictFileName);
        SegDict();
        ~SegDict();

        pair<int, string> GetDictInfo(const char *feat);       // get dictionary feat info
        int size();
        bool LoadDictFile(const char *DictFileName);
        bool SaveDictFile();
    private:
        map<string, pair<int, string> > *_dict;
        typedef map<string, pair<int, string> >::iterator _Str2PairMapIter;
    };
}

#endif