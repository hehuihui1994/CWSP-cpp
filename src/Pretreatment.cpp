/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.
* Copyright (C) 2016 Shenghuan He
* Contact: heshenghuan328@gmail.com

* Permission to use, copy, modify, and distribute this software for
* any non-commercial purpose is hereby granted without fee, provided
* that the above copyright notice appear in all copies and that both
* that copyright notice. 
* It is provided "as is" without express or implied warranty.
*********************************************************************/

#include "Pretreatment.h"

namespace cwsp
{
    Pretreatment::Pretreatment()
    {
        _features = new SegFeat;
        _probs = new SegProb;
		_dict = new SegDict;
		_char_type = new CharType;
        tag2index = new map<string, int>;

        is_dict_ready = false;
        is_char_ready = false;
        is_out_ready = false;

        tag2index->insert(make_pair("B", 0));
        tag2index->insert(make_pair("M", 1));
        tag2index->insert(make_pair("E", 2));
        tag2index->insert(make_pair("S", 3));
    }

    Pretreatment::~Pretreatment()
    {
        delete _features;
        delete _probs;
		delete _dict;
		delete _char_type;
        delete tag2index;
    }

	bool Pretreatment::LoadDictFile(const char * DictFileName)
	{
        is_dict_ready = _dict->LoadDictFile(DictFileName);
		return is_dict_ready;
	}

	bool Pretreatment::LoadCharFile(bool is_bin)
	{
        is_char_ready = _char_type->Initialize(is_bin);
		return is_char_ready;
	}

    bool Pretreatment::TrainSegFile(const char * FileName)
    {
        ifstream fin;
        fin.open(FileName);
        if (!fin.is_open())
        {
            cerr << "\nPretreatment ERROR" << endl;
            cerr << "Open " << FileName<< " error!" << endl;
            return false;
        }

        if(!is_dict_ready || !is_char_ready)
        {
            cerr << "\nPretreatment ERROR" << endl;
            cerr << "SegDict or CharType not ready for Training SegFile!" <<endl;
            return false;
        }

        int numIndex = 0;
        while(!fin.eof())
        {
            string myTextLine;
            getline(fin, myTextLine);
            TrimLine(myTextLine);
            if(myTextLine.length()==0)
            {
                continue; // skip the empty line
            }
            numIndex ++;
            if (numIndex%100 == 0)
            {
                std::cout << ".";
                std::cout.flush();
                if (numIndex%5000 == 0)
                {
                    std::cout << "\t" << numIndex << " sentences" << endl;
                }
            }
            vector<string> charVec, tagVec;
            SplitLine(myTextLine, charVec, tagVec);

            _probs->InitProbCount(tag2index->at(tagVec.at(2)));
            // trans tag prob
            for(size_t i=2; i<tagVec.size()-3; i++)
            {
                int s = tag2index->at(tagVec.at(i));
                int d = tag2index->at(tagVec.at(i+1));
                _probs->TransProbCount(s, d);
            }

            vector<vector<string> > featurCont;
            GenerateFeats(charVec, featurCont);
            for(size_t i=0; i<featurCont.size();i++)
            {
                for(size_t j=1;j<featurCont.at(i).size()-3;j++)
                {
                    if (j<6)
                    {
                        _features->InsertUnigramFeat(featurCont.at(i).at(j).c_str());
                    }
                    else if (j < 10)
                    {
                        _features->InsertBigramFeat(featurCont.at(i).at(j).c_str());
                    }
                    else if (j < 11)
                    {
                        _features->InsertTrigramFeat(featurCont.at(i).at(j).c_str());
                    }
                    else if (j < 15)
                    {
                        _features->InsertDictFeat(featurCont.at(i).at(j).c_str());
                    }
                    else
                    {
                        /* type features */
                        // T(-1)T(0)T(1), N(-1)N(0)N(1), F(-1)F(0)F(1) do not need to insert
                        continue;
                    }
                }
            }
        }
        fin.close();
        std::cout << endl;
        std::cout << numIndex << " sentences in total.\n" << endl;
        is_out_ready = true;
        bool flag = true;
        if (!_probs->CalcAllProb()) flag = false;
        if (!_features->SaveFeatureFile()) flag = false;
        if (!_probs->SaveProbFile()) flag = false;
        return flag;
    }

    bool Pretreatment::MakeTrainData(const char *corpus, vector<feature> &samp_feat_vec, vector<int> &samp_class_vec)
    {
        if(!is_out_ready)
        {
            cerr<< "Not ready to make training data."<<endl;
            return false;
        }

        ifstream fin;
        fin.open(corpus);
        if (!fin.is_open())
        {
            cerr << "\nPretreatment ERROR" << endl;
            cerr << "Open " << corpus << " error!" << endl;
            return false;
        }

        if(!is_dict_ready || !is_char_ready)
        {
            cerr << "\nPretreatment ERROR" << endl;
            cerr << "SegDict or CharType not ready for Training SegFile!" <<endl;
            return false;
        }
        int numIndex = 0;
        // ofstream outfile;
        // outfile.open("data/train");
        while(!fin.eof())
        {
            string myTextLine;
            getline(fin, myTextLine);
            TrimLine(myTextLine);
            if(myTextLine.length()==0)
            {
                continue; // skip the empty line
            }
            numIndex ++;
            if (numIndex%100 == 0)
            {
                std::cout << ".";
                std::cout.flush();
                if (numIndex%5000 == 0)
                {
                    std::cout << "\t" << numIndex << " samples" << endl;
                }
            }
            vector<string> charVec, tagVec;
            SplitLine(myTextLine, charVec, tagVec);
            vector<vector<string> > featurCont;
            GenerateFeats(charVec, featurCont);
            vector<vector<string> > featsVec;
            Feature2vec(featurCont, featsVec);
            for (size_t i=0; i<featsVec.size(); i++)
            {
                samp_class_vec.push_back(tag2index->at(tagVec.at(i+2)));
                // outfile << tag2index->at(tagVec.at(i+2)) << '\t';
                feature samp_feat;
                for (auto it : featsVec.at(i)) // size_t j=0; j<featsVec.at(i).size(); j++)
                {
                    size_t feat_pos = it.find_first_of(":");
                    int feat_id = atoi(it.substr(0, feat_pos).c_str());
                    float feat_value = (float)atof(it.substr(feat_pos+1).c_str());
                    if (feat_value != 0) {
                        samp_feat.id_vec.push_back(feat_id);
                        samp_feat.value_vec.push_back(feat_value);
                    }
                    // outfile << it <<' ';
                }
                // outfile<<'\n';
                samp_feat_vec.push_back(samp_feat);
            }
        }
        fin.close();
        // outfile.close();
        std::cout << endl;
        std::cout << numIndex << " samples in total." << endl;
        //outfile.clear();
        return true;
    }

    void Pretreatment::SplitLine(string &line, vector<string> &charVec, vector<string> &tagVec)
    {
        charVec.clear();
        tagVec.clear();

        charVec.push_back("B_1");
        tagVec.push_back("B_1");

        charVec.push_back("B_0");
        tagVec.push_back("B_0");

        string word;
        istringstream is(line.c_str());
        // std::cout<<"line: "<<line<<endl;
        while (is >> word)
        {
            // std::cout<<"word: "<<word<<"\nSplited: ";
            vector<string> myCharVec;
            for (size_t i = 0; i < word.length();)
            {
                string character = word.substr(i, 1);
                if (character.at(0)<0)
                {
                    character = word.substr(i, 2);
                    if (character == "·")
                    {
                        i += 2;
                    }
                    else
                    {
                        character = word.substr(i, 3);
                        i += 3;
                    }
                }
                else
                {
                    i++;
                }
                // std::cout<<character<<'/';
                myCharVec.push_back(character);
                charVec.push_back(character);
            }
            // std::cout<<endl;

            size_t n = myCharVec.size();

            if (n == 1)
            {
                tagVec.push_back("S");
            }
            else if (n == 2)
            {
                tagVec.push_back("B");
                tagVec.push_back("E");
            }
            else
            {
                tagVec.push_back("B");
                for (size_t j = 0; j < n-2; j ++)
                {
                    tagVec.push_back("M");
                }
                tagVec.push_back("E");
            }
        }

        charVec.push_back("E_0");
        tagVec.push_back("E_0");

        charVec.push_back("E_1");
        tagVec.push_back("E_1");
        return;
    }

	void Pretreatment::GenerateFeats(vector<string> charVec, vector<vector<string> > &featsVec)
	{
		featsVec.clear();
		for (size_t i = 2; i<charVec.size()-2;i++)
		{
			vector<string> feat;
			string feature;

            // Pu(0) 0
            feature = toString(_char_type->GetPuncType(charVec.at(i)));
            feat.push_back(feature);

			// C-2 1
			feature = charVec.at(i-2);
			feat.push_back(feature);
			// C-1 2
			feature = charVec.at(i-1);
			feat.push_back(feature);
			// C0 3
			feature = charVec.at(i);
			feat.push_back(feature);
			// C1 4
			feature = charVec.at(i+1);
			feat.push_back(feature);
			// C2 5
			feature = charVec.at(i+2);
			feat.push_back(feature);

			// C-2C-1 6
			feature = charVec.at(i-2) + charVec.at(i-1);
			feat.push_back(feature);
			// C-1C0 7
			feature = charVec.at(i-1) + charVec.at(i);
			feat.push_back(feature);
			// C0C1 8
			feature = charVec.at(i) + charVec.at(i+1);
			feat.push_back(feature);
			// C1C2 9
			feature = charVec.at(i+1) + charVec.at(i+2);
			feat.push_back(feature);

			// C-1C1 10
			feature = charVec.at(i-1) + charVec.at(i+1);
			feat.push_back(feature);

			/* dict features */
			//get MWL, t0
			pair<int, string> ans = _dict->GetDictInfo(charVec.at(i).c_str());
			// MWL+t0 11
            feature = toString(ans.first) + ans.second;
            feat.push_back(feature);
            // C-1+t0 12
            feature = charVec.at(i-1) + ans.second;
            feat.push_back(feature);
            // C0+t0 13
            feature = charVec.at(i) + ans.second;
            feat.push_back(feature);
            // C1+t0 14
            feature = charVec.at(i+1) + ans.second;
            feat.push_back(feature);

			/* type features */
			//T(-1)T(0)T(1) 15
            int index;
            index = 1 + _char_type->GetCharType(charVec.at(i-1));
            index += 6 * _char_type->GetCharType(charVec.at(i));
            index += 36 * _char_type->GetCharType(charVec.at(i+1));
			feat.push_back(toString(index));

            //N(-1)N(0)N(1) 16
            index = 1 + _char_type->GetCNameType(charVec.at(i-1));
            index += 6 * _char_type->GetCNameType(charVec.at(i));
            index += 36 * _char_type->GetCNameType(charVec.at(i+1));
            feat.push_back(toString(index));

            //F(-1)F(0)F(1) 17
            index = 1 + _char_type->GetFNameType(charVec.at(i-1));
            index += 2 * _char_type->GetFNameType(charVec.at(i));
            index += 4 * _char_type->GetFNameType(charVec.at(i+1));
            feat.push_back(toString(index));

            featsVec.push_back(feat);
		}
	}

    void Pretreatment::Feature2vec(vector<vector<string> > feats, vector<vector<string> > &featsVec)
    {
        int unigramlen = _features->UnigramLen();
        int bigramlen = _features->BigramLen();
        int trigramlen = _features->TrigramLen();
        int dictlen = _features->DictFeatLen();
        for(size_t i=0; i<feats.size();i++)
        {
            vector<string> featVec;
            if (feats.at(i).at(0) == "1")
            {
                featVec.push_back("0:1.0");
            }
            for(size_t j=1;j<feats.at(i).size();j++)
            {
                if (j<6)
                {
                    int index = _features->GetUnigramIndex(feats.at(i).at(j).c_str());
                    index += (j-1)*unigramlen;
                    featVec.push_back(toString(index) + ":1.0");       
                }
                else if (j < 10)
                {
                    int index = _features->GetBigramIndex(feats.at(i).at(j).c_str());
                    index += 5 * unigramlen + (j-6) * bigramlen;
                    featVec.push_back(toString(index) + ":1.0");
                }
                else if (j < 11)
                {
                    int index = _features->GetTrigramIndex(feats.at(i).at(j).c_str());
                    index += 5 * unigramlen + 4 * bigramlen;
                    featVec.push_back(toString(index) + ":1.0");
                }
                else if (j < 15)
                {
                    int index = _features->GetDictIndex(feats.at(i).at(j).c_str());
                    index += 5 *unigramlen + 4*bigramlen + trigramlen + (j-11)*dictlen;
                    featVec.push_back(toString(index) + ":1.0");
                }
                else if (j==15)
                {
                    int index = fromString<int>(feats.at(i).at(j));
                    index += 5*unigramlen + 4*bigramlen + trigramlen + 4*dictlen;
                    featVec.push_back(toString(index) + ":1.0");
                }
                else if (j==16)
                {
                    int index = fromString<int>(feats.at(i).at(j));
                    index += 5*unigramlen + 4*bigramlen + trigramlen + 4*dictlen + TYPE_FEAT_SIZE;
                    featVec.push_back(toString(index) + ":1.0");
                }
                else if (j==17)
                {
                    int index = fromString<int>(feats.at(i).at(j));
                    index += 5*unigramlen + 4*bigramlen + trigramlen + 4*dictlen + TYPE_FEAT_SIZE + CNAME_FEAT_SIZE;
                    featVec.push_back(toString(index) + ":1.0");
                }
            }
            featsVec.push_back(featVec);
        }
        return ;
    }
}