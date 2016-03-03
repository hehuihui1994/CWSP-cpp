/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#ifndef SEGFEAT_H_
#define SEGFEAT_H_

#include "Config.h"
// #include "StrFun.h"
#include "SegVocab.h"

namespace cwsp
{
    class Feat
    {
    public:
        Feat();
        ~Feat();
        int GetUnigramIndex(const char *feat);  // get unigram feat's index
        int GetBigramIndex(const char *feat);   // get bigram feat's index
        int GetTrigramIndex(const char *feat);  // get trigram feat's index
        pair<int, char> GetDictInfo(const char *feat);       // get dictionary feat info
        int UnigramLen()
        {
            return _unigram->size();
        }
        int BigramLen()
        {
            return _bigram->size();
        }
        int TrigramLen()
        {
            return _trigram->size();
        }
        int DictLen()
        {
            return (int)_dict_feat_len;
        }

        bool InsertUnigramFeat(const char *feat);
        bool InsertBigramFeat(const char *feat);
        bool InsertTrigramFeat(const char *feat);

        bool LoadFeatureFile(const char *UnigramFileName);
        bool SaveFeatureFile();
        bool ConvertToBinaryFile(const char* InputFileName, const char* OutputFileName);

    private:
        bool ReadFile(const char* FileName);
        bool ReadBinaryFile(const char* FileName);
        void TrimLine(string & line);
        vector<string> SplitString(string terms_str, string spliting_tag);
    private:
        Vocab *_unigram;
        Vocab *_bigram;
        Vocab *_trigram;
        map<string, pair<int, char> > _dict_feat;
        size_t _dict_feat_len;
        typedef map<string, pair<int, char> >::iterator _Str2PairMapIter;

        bool _modifiable;    // if _modifiable is "false", you cannot insert, load from file...
    };
}

#endif