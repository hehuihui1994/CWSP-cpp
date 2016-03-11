/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#ifndef SEGMENTOR_H_
#define SEGMENTOR_H_

#include "Config.h"
#include "StrFun.h"
#include "CharType.h"
#include "SegFeat.h"
#include "SegProb.h"
#include "SegDict.h"

namespace cwsp
{
    class Segmentor
    {
    public:
        Segmentor();
        ~Segmentor();
        bool Initialize();
        void SegSentence(string & inputSen, string & outputSen);
        void SegFile(string inputfile, string outputfile);
        void SetAlpha(double & myAlpha);
    private:
        // bool CheckMerge(deque<int> & x, deque<int> & y);
        // bool CheckEqual(deque<int> & x, deque<int> & y);
        // void RenewLattice(vector<string> & charSeq);
        void Viterbi(vector<string> & myCharVec, string & segResult);
        void GetTagIndex();
    private:
        SegFeat *_features;
        SegProb *_probs;
        SegDict *_dict;
        CharType *_char_type;
    };
}


#endif