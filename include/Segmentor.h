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
        bool Initialize(bool is_char_bin, string dictfile, string &featfile, string &probfile);
        bool Initialize();
        void SegSentence(string & inputSen, string & outputSen);
        void SegFile(string inputfile, string outputfile);
        // void SetAlpha(double & myAlpha);
    private:
        // bool CheckMerge(deque<int> & x, deque<int> & y);
        // bool CheckEqual(deque<int> & x, deque<int> & y);
        // void RenewLattice(vector<string> & charSeq);
        void SplitLine(string &line, vector<string> &charVec);
        void GenerateFeats(vector<string> charVec, vector<vector<string> > &featsVec);
        void Feature2vec(vector<vector<string> > feats, vector<vector<string> > &featsVec);
        void GetEmitProb(vector<vector<string> > featsVec, vector<vector<double> > &emit_prob);
        void Viterbi(vector<vector<string> > &myFeatsVec, vector<string> &tagVec);
        void Tag2Word(vector<string> charVec, vector<string> tagVec, string &line);
        string GetTag(int index);
    private:
        SegFeat *_features;
        SegProb *_probs;
        SegDict *_dict;
        CharType *_char_type;

        bool is_initial;
    };
}


#endif