/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#ifndef PRETREATMENT_H_
#define PRETREATMENT_H_

#include "Config.h"
#include "CharType.h"
#include "SegFeat.h"
#include "SegProb.h"
#include "SegDict.h"

#define TYPE_FEAT_SIZE 216
#define CNAME_FEAT_TYPE 216
#define FNAME_FEAT_TYPE 8

namespace cwsp
{
    class Pretreatment
    {
    public:
        Pretreatment();
        ~Pretreatment();
		bool LoadDictFile(const char * DictFileName);
		bool LoadCharFile(bool is_bin);
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
		void GenerateFeats(vector<string> charVec, vector<string> tagVec, vector<vector<string> > &featsVec);
        vector<string> SplitString(string terms_str, string spliting_tag);
    private:
        SegFeat *_features;
        SegProb *_probs;
		SegDict *_dict;
        CharType *_char_type;
    };
}

#endif