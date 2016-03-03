/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#include "SegFeat.h"

namespace cwsp
{
    Feat::Feat()
    {
        _unigram = NULL;
        _bigram = NULL;
        _trigram = NULL;
        _dict_feat_len = _dict_feat.size();
        _modifiable = true;
    }
    
    Feat::~Feat()
    {
        delete _unigram;
        delete _bigram;
        delete _trigram;
        delete _dict_feat;
    }
    
    int Feat::GetUnigramIndex(const char *feat)
    {
        return _unigram->GetIndex(feat);
    }

    int Feat::GetBigramIndex(const char *feat)
    {
        return _bigram->GetIndex(feat);
    }

    int Feat::GetTrigramIndex(const char *feat)
    {
        return _trigram->GetIndex(feat);
    }

    int Feat::GetDictInfo(const char *feat)
    {
        _Str2PairMapIter it = _dict_feat.find(feat);

        if( it != _dict_feat.end() )
            return (*it).second;
        else
            return make_pair(1, 'S');
    }

    bool Feat::LoadFeatureFile(const char *FeatureFileName)
    {
        FILE * FeatureFile;
        FeatureFile = fopen(FeatureFileName, "rb");
        if( !FeatureFile )
        {
            cerr<<"\nCan not open the Feature Model File: "<<FeatureFileName<<endl;
            return false;
        }
        char headBuf[UNIGRAM_LEN_MAX];
        fread(&headBuf, g_Header_Len, 1, FeatureFile);
        fclose(FeatureFile);
        string header = string(headBuf, g_Header_Len);
        if (header == g_Model_Header)
        {
            return ReadBinaryFile(FeatureFileName);
        }
        else
        {
            return ReadFile(FeatureFileName);
        }
    }

    bool Feat::SaveFeatureFile()
    {
        if( ( _unigram==NULL ) || (_unigram.size()<=0) )
        {
            cerr<<"\nDoes not have any feature in Unigram."<<endl;
            return false;
        }
        if( ( _bigram==NULL ) || (_bigram.size()<=0) )
        {
            cerr<<"\nDoes not have any feature in Bigram."<<endl;
            return false;
        }
        if( ( _trigram==NULL ) || (_trigram.size()<=0) )
        {
            cerr<<"\nDoes not have any feature in Trigram."<<endl;
            return false;
        }
#ifdef WIN32
        string _datapath = "model\\";
#else
        string _datapath = "model/";
#endif
        string FileName = _datapath + "Feature";
        FILE * FeatureFile;
        FeatureFile = fopen(FileName.c_str(), "w");
        
        // write unigram feature
        string unigramSize = toString(_unigram.size()) + '\n';
        string unigramHeader = "#UnigramFeature\n"; 
        fwrite(unigramHeader.data(), unigramHeader.length(), 1, FeatureFile);
        fwrite(unigramHSize.data(), unigramSize.length(), 1, FeatureFile);
        _unigram->WriteVocabText(FeatureFile);

        // write bigram feature
        string bigramSize = toString(_bigram.size()) + '\n';
        string bigramHeader = "#BigramFeature\n"; 
        fwrite(bigramHeader.data(), bigramHeader.length(), 1, FeatureFile);
        fwrite(bigramHSize.data(), bigramSize.length(), 1, FeatureFile);
        _bigram->WriteVocabText(FeatureFile);

        // write trigram feature
        string trigramSize = toString(_trigram.size()) + '\n';
        string trigramHeader = "#TrigramFeature\n"; 
        fwrite(trigramHeader.data(), trigramHeader.length(), 1, FeatureFile);
        fwrite(trigramHSize.data(), trigramSize.length(), 1, FeatureFile);
        _trigram->WriteVocabText(FeatureFile);

        fclose(FeatureFile);
        return true;
    }

    bool ReadFile(const char* FileName)
    {
        ifstream fin;
        fin.open(FileName);
        if( !fin.is_open() )
        {
            cerr<<"\nCan not open the Feature model file: "<<FileName<<endl;
            return false;
        }

        string myTextLine;
        vector<string> tmp;
        delete _unigram;
        delete _bigram;
        delete _trigram;
        _bigram = new Vocab;
        _unigram = new Vocab;
        _trigram = new Vocab;

        getline(fin, myTextLine);  // skip the first line

        getline(fin, myTextLine);
        int unigramSize = fromString<int>(myTextLine);
        for(int i=0; i<unigramSize; i++)
        {
            getline(fin, myTextLine);
            TrimLine(myTextLine);
            tmp = SplitString(myTextLine, " ");
            string feat = tmp.front();
            int index = fromString<int>(tmp.back());
            _unigram->InserWordAndIndex(feat, index);
        }

        getline(fin, myTextLine);
        getline(fin, myTextLine);
        int bigramSize = fromString<int>(myTextLine);
        for(int i=0; i<bigramSize; i++)
        {
            getline(fin, myTextLine);
            TrimLine(myTextLine);
            tmp = SplitString(myTextLine, " ");
            string feat = tmp.front();
            int index = fromString<int>(tmp.back());
            _bigram->InserWordAndIndex(feat, index);
        }

        getline(fin, myTextLine);
        getline(fin, myTextLine);
        int trigramSize = fromString<int>(myTextLine);
        for(int i=0; i<trigramSize; i++)
        {
            getline(fin, myTextLine);
            TrimLine(myTextLine);
            tmp = SplitString(myTextLine, " ");
            string feat = tmp.front();
            int index = fromString<int>(tmp.back());
            _trigram->InserWordAndIndex(feat, index);
        }
        fin.close();
        std::cout<<"\nUnigram feature: "<<_unigram.size()<<endl
                 <<"Bigram feature:  "<<_bigram.size()<<endl
                 <<"Trigram feature: "<<_trigram.size()<<endl;
        return true;
    }

    bool ReadBinaryFile(const char* FileName)
    {
        FILE * FeatureFile;
        FeatureFile = fopen(FileName, "rb");
        if( !FeatureFile )
        {
            cerr<<"\nCan not open the Feature model file: "<<FileName<<endl;
            return false;
        }
        char headBuf[UNIGRAM_LEN_MAX];
        fread(&headBuf, g_Header_Len, 1, NgramFile);
        string header = string(headBuf, g_Header_Len);

        int unigramSize, bigramSize, trigramSize;
        fread(&unigramSize, sizeof(int), 1, FeatureFile);
        int index, unit;
        string word;
        for (int i=0; i<unigramSize; i++)
        {
            fread(&unit, sizeof(int), 1, FeatureFile);
            char buf[UNIGRAM_LEN_MAX];
            fread((void*)&buf, unit, 1, FeatureFile);
            word = string(buf, unit);
            fread(&index, sizeof(int), 1, FeatureFile);
            _unigram->InserWordAndIndex(word, index);
        }

        fread(&bigramSize, sizeof(int), 1, FeatureFile);
        for (int i=0; i<bigramSize; i++)
        {
            fread(&unit, sizeof(int), 1, FeatureFile);
            char buf[UNIGRAM_LEN_MAX];
            fread((void*)&buf, unit, 1, FeatureFile);
            word = string(buf, unit);
            fread(&index, sizeof(int), 1, FeatureFile);
            _bigram->InserWordAndIndex(word, index);
        }

        fread(&trigramSize, sizeof(int), 1, FeatureFile);
        for (int i=0; i<trigramSize; i++)
        {
            fread(&unit, sizeof(int), 1, FeatureFile);
            char buf[UNIGRAM_LEN_MAX];
            fread((void*)&buf, unit, 1, FeatureFile);
            word = string(buf, unit);
            fread(&index, sizeof(int), 1, FeatureFile);
            _trigram->InserWordAndIndex(word, index);
        }
        fclose(FeatureFile);
        return true;
    }

    bool Feat::ConvertToBinaryFile(const char* InputFileName, const char* OutputFileName)
    {
        if !(ReadFile(InputFileName)) return false;
        std::cout<<"Load text Feature file finished."<<endl;
        FILE* str_lm_file;
        FILE* bin_lm_file;
        str_lm_file=fopen(InputFileName,"r");
        if( !str_lm_file )
        {
            cerr<<"Can not open the Language Model File: "<<InputFileName<<endl;
            return false;
        }
        bin_lm_file=fopen(OutputFileName,"wb");
        fwrite(g_Model_Header.data(), g_Header_Len, 1, bin_lm_file);
        int unigramSize = _unigram->size();
        fwrite(&unigramSize, sizeof(int), 1, bin_lm_file);
        _unigram->WriteVocabIndex(bin_lm_file);

        int bigramSize = _bigram->size();
        fwrite(&bigramSize, sizeof(int), 1, bin_lm_file);
        _bigram->WriteVocabIndex(bin_lm_file);

        int trigramSize = _trigram->size();
        fwrite(&trigramSize, sizeof(int), 1, bin_lm_file);
        _trigram->WriteVocabIndex(bin_lm_file);

        fclose(str_lm_file);
        fclose(bin_lm_file);
        return true;
    }
}