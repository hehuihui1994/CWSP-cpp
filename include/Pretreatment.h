/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#ifndef PRETREATMENT_H_
#define PRETREATMENT_H_

#include "Config.h"
#include "CharType.h"
#include "SegFeat.h"
#include "SegProb.h"

namespace cwsp
{
    class Pretreatment
    {
    public:
        Pretreatment();
        ~Pretreatment();
        bool TrainSegFile(const char * FileName);
        bool SaveFeatureFile()
        {
            return _features->SaveFeatureFile();
        }
        bool SaveProbFile()
        {
            return _probs->SaveProbFile();
        }

    private:
        // This function processes strings like "我 爱 北京 天安门 。"
        void SplitLine(string &line, vector<string> &charVec, vector<string> &tagVec);
    private:
        SegFeat *_features;
        SegProb *_probs;
        // CharType *_type_feats;
    };
}


#endif