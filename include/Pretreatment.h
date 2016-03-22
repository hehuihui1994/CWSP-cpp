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
#include "MultiPerceptron.h"

namespace cwsp
{
    class Pretreatment
    {
    public:
        Pretreatment();
        ~Pretreatment();
		bool LoadDictFile(const char *DictFileName);
		bool LoadCharFile(bool is_bin);
        bool TrainSegFile(const char *FileName);
        bool MakeTrainData(const char *corpus, vector<feature> &samp_feat_vec, vector<int> &samp_class_vec);
        bool SaveFeatureFile()
        {
            return _features->SaveFeatureFile();
        }
        bool SaveProbFile()
        {
            return _probs->SaveProbFile();
        }

        bool LoadFeatureFile(const char *FileName)
        {
            if (_features->LoadFeatureFile(FileName))
            {
                is_out_ready = true;
                return true;
            }
            else{
                is_out_ready = false;
                return false;
            }
        }
        bool LoadProbFile(const char *FileName)
        {
            if (_probs->LoadProbFile(FileName))
            {
                is_out_ready = true;
                return true;
            }
            else{
                is_out_ready = false;
                return false;
            }
        }

        void PrintInfo()
        {
            int unigramlen = _features->UnigramLen();
            int bigramlen = _features->BigramLen();
            int trigramlen = _features->TrigramLen();
            int dictlen = _features->DictFeatLen();
            std::cout<< "\nFeatures statistic\n"
                     << "Unigram feat size:   "<<unigramlen<<endl
                     << "Bigram feat size:    "<<bigramlen<<endl
                     << "Trigram feat size:   "<<trigramlen<<endl
                     << "DictFeat size:       "<<dictlen<<endl;
            int featSize = unigramlen*5 + bigramlen*4 + trigramlen + 4*dictlen + TYPE_FEAT_SIZE + CNAME_FEAT_SIZE + FNAME_FEAT_SIZE;
            std::cout<< "Feature size:        "<<featSize<<endl;
        }

    private:
        // This function processes strings like "我 爱 北京 天安门 。"
        void SplitLine(string &line, vector<string> &charVec, vector<string> &tagVec);
		void GenerateFeats(vector<string> charVec, vector<vector<string> > &featsVec);
        void Feature2vec(vector<vector<string> > feats, vector<vector<string> > &featsVec);
    private:
        SegFeat *_features;
        SegProb *_probs;
		SegDict *_dict;
        CharType *_char_type;
        map<string, int> *tag2index;

        bool is_dict_ready;
        bool is_char_ready;
        bool is_out_ready;
    };
}

#endif