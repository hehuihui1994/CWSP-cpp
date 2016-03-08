/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#include "SegFeat.h"

namespace cwsp
{
    SegFeat::SegFeat()
    {
        _unigram = new Vocab;
        _bigram = new Vocab;
        _trigram = new Vocab;
        _modifiable = true;
    }
    
    SegFeat::~SegFeat()
    {
        delete _unigram;
        delete _bigram;
        delete _trigram;
        // delete _dict_feat;
    }
    
    int SegFeat::GetUnigramIndex(const char *feat)
    {
        return _unigram->GetIndex(feat);
    }

    int SegFeat::GetBigramIndex(const char *feat)
    {
        return _bigram->GetIndex(feat);
    }

    int SegFeat::GetTrigramIndex(const char *feat)
    {
        return _trigram->GetIndex(feat);
    }

    bool SegFeat::LoadFeatureFile(const char *FeatureFileName)
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

    bool SegFeat::SaveFeatureFile()
    {
        if( ( _unigram==NULL ) || (_unigram->size()<=0) )
        {
            cerr<<"\nDoes not have any feature in Unigram."<<endl;
            return false;
        }
        if( ( _bigram==NULL ) || (_bigram->size()<=0) )
        {
            cerr<<"\nDoes not have any feature in Bigram."<<endl;
            return false;
        }
        if( ( _trigram==NULL ) || (_trigram->size()<=0) )
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
        string unigramSize = toString(_unigram->size()) + '\n';
        string unigramHeader = "#UnigramFeature\n"; 
        fwrite(unigramHeader.data(), unigramHeader.length(), 1, FeatureFile);
        fwrite(unigramSize.data(), unigramSize.length(), 1, FeatureFile);
        _unigram->WriteVocabText(FeatureFile);

        // write bigram feature
        string bigramSize = toString(_bigram->size()) + '\n';
        string bigramHeader = "#BigramFeature\n"; 
        fwrite(bigramHeader.data(), bigramHeader.length(), 1, FeatureFile);
        fwrite(bigramSize.data(), bigramSize.length(), 1, FeatureFile);
        _bigram->WriteVocabText(FeatureFile);

        // write trigram feature
        string trigramSize = toString(_trigram->size()) + '\n';
        string trigramHeader = "#TrigramFeature\n"; 
        fwrite(trigramHeader.data(), trigramHeader.length(), 1, FeatureFile);
        fwrite(trigramSize.data(), trigramSize.length(), 1, FeatureFile);
        _trigram->WriteVocabText(FeatureFile);

        fclose(FeatureFile);
        return true;
    }

    bool SegFeat::ReadFile(const char* FileName)
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
        delete this->_unigram;
        delete this->_bigram;
        delete this->_trigram;
        this->_bigram = new Vocab;
        this->_unigram = new Vocab;
        this->_trigram = new Vocab;

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
            this->_unigram->InserWordAndIndex(feat, index);
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
            this->_bigram->InserWordAndIndex(feat, index);
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
            this->_trigram->InserWordAndIndex(feat, index);
        }
        fin.close();
        return true;
    }

    bool SegFeat::ReadBinaryFile(const char* FileName)
    {
        FILE * FeatureFile;
        FeatureFile = fopen(FileName, "rb");
        if( !FeatureFile )
        {
            cerr<<"\nCan not open the Feature model file: "<<FileName<<endl;
            return false;
        }
        char headBuf[UNIGRAM_LEN_MAX];
        fread(&headBuf, g_Header_Len, 1, FeatureFile);
        string header = string(headBuf, g_Header_Len);

		delete this->_unigram;
        delete this->_bigram;
        delete this->_trigram;
        this->_bigram = new Vocab;
        this->_unigram = new Vocab;
        this->_trigram = new Vocab;

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
            this->_unigram->InserWordAndIndex(word, index);
        }

        fread(&bigramSize, sizeof(int), 1, FeatureFile);
        for (int i=0; i<bigramSize; i++)
        {
            fread(&unit, sizeof(int), 1, FeatureFile);
            char buf[UNIGRAM_LEN_MAX];
            fread((void*)&buf, unit, 1, FeatureFile);
            word = string(buf, unit);
            fread(&index, sizeof(int), 1, FeatureFile);
            this->_bigram->InserWordAndIndex(word, index);
        }

        fread(&trigramSize, sizeof(int), 1, FeatureFile);
        for (int i=0; i<trigramSize; i++)
        {
            fread(&unit, sizeof(int), 1, FeatureFile);
            char buf[UNIGRAM_LEN_MAX];
            fread((void*)&buf, unit, 1, FeatureFile);
            word = string(buf, unit);
            fread(&index, sizeof(int), 1, FeatureFile);
            this->_trigram->InserWordAndIndex(word, index);
        }
        fclose(FeatureFile);
        return true;
    }

    bool SegFeat::ConvertToBinaryFile(const char* InputFileName, const char* OutputFileName)
    {
        if (!ReadFile(InputFileName)) return false;
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
        int unigramSize = this->_unigram->size();
        fwrite(&unigramSize, sizeof(int), 1, bin_lm_file);
        this->_unigram->WriteVocabIndex(bin_lm_file);

        int bigramSize = this->_bigram->size();
        fwrite(&bigramSize, sizeof(int), 1, bin_lm_file);
        this->_bigram->WriteVocabIndex(bin_lm_file);

        int trigramSize = this->_trigram->size();
        fwrite(&trigramSize, sizeof(int), 1, bin_lm_file);
        this->_trigram->WriteVocabIndex(bin_lm_file);

        fclose(str_lm_file);
        fclose(bin_lm_file);
        return true;
    }

    vector<string> SegFeat::SplitString(string terms_str, string spliting_tag)
    {
        vector<string> feat_vec;
        size_t term_beg_pos = 0;
        size_t term_end_pos = 0;
        while ((term_end_pos = terms_str.find_first_of(spliting_tag, term_beg_pos)) != string::npos) {
            if (term_end_pos > term_beg_pos) {
                string term_str = terms_str.substr(term_beg_pos, term_end_pos - term_beg_pos);
                feat_vec.push_back(term_str);
            }
            term_beg_pos = term_end_pos + 1;
        }
        if (term_beg_pos < terms_str.size()) {
            string end_str = terms_str.substr(term_beg_pos);
            feat_vec.push_back(end_str);
        }
        return feat_vec;
    }
}