/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#ifndef SEGFEAT_H_
#define SEGFEAT_H_

#include "Config.h"
#include "SegVocab.h"

namespace cwsp
{
    class Feat
    {
    public:
        Feat();
        ~Feat();
        int GetUnigramIndics(const char *feat);  //get unigram feat's index
        int GetBigramIndics(const char *feat);   //get bigram feat's index
        int GetTrigramIndics(const char *feat);  //get trigram feat's index
        int GetUnigramLen()
        {
            return _unigram->size();
        }
        int GetBigramLen()
        {
            return _bigram->size();
        }
        int GetTrigramLen()
        {
            return _trigram->size();
        }

        void InsertUnigramFeat(const char *feat);
        void InsertBigramFeat(const char *feat);
        void InsertTrigramFeat(const char *feat);
    private:
        Vocab *_unigram;
        Vocab *_bigram;
        Vocab *_trigram;
        map<string, pair<int, char>> _dict_feat;
        typedef map<string, pair<int, char>>::iterator _Str2PairMapIter;

        bool _modifiable;
    };
}