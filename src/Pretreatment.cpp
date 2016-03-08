/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

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
    }

    Pretreatment::~Pretreatment()
    {
        delete _features;
        delete _probs;
		delete _dict;
		delete _char_type;
    }

	bool Pretreatment::LoadDictFile(const char * DictFileName)
	{
		return _dict->LoadDictFile(DictFileName);
	}

	bool Pretreatment::LoadCharFile(bool is_bin)
	{
		return _char_type->Initialize(is_bin);
	}

    bool Pretreatment::TrainSegFile(const char * FileName)
    {
        ifstream fin;
        fin.open(FileName);
        if (!fin.is_open())
        {
            cerr << "###########################################" << endl;
            cerr << "Open " << FileName<< " error!" << endl;
            cerr << "###########################################" << endl;
            return false;
        }
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
        while (is >> word)
        {
            vector<string> myCharVec;
            for (size_t i = 0; i < word.length();)
            {
                string character = word.substr(i, 1);
                if (character.at(0) < 0)
                {
                    character = word.substr(i, 2);
                    i += 2;
                }
                else
                {
                    i++;
                }
                myCharVec.push_back(character);
                charVec.push_back(character);
            }

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

	void Pretreatment::GenerateFeats(vector<string> charVec, vector<string> tagVec, vector<vector<string> > &featsVec)
	{
		featsVec.clear();
		for (size_t i = 2; i<charVec.size()-2;i++)
		{
			vector<string> feat;
			string feature;

			// C-2
			feature = "" + charVec.at(i-2);
			feat.push_back(feature);
			// C-1
			feature = "" + charVec.at(i-1);
			feat.push_back(feature);
			// C0
			feature = "" + charVec.at(i);
			feat.push_back(feature);
			// C1
			feature = "" + charVec.at(i+1);
			feat.push_back(feature);
			// C2
			feature = "" + charVec.at(i+2);
			feat.push_back(feature);

			// C-2C-1
			feature = "" + charVec.at(i-2) + charVec.at(i-1);
			feat.push_back(feature);
			// C-1C0
			feature = "" + charVec.at(i-1) + charVec.at(i);
			feat.push_back(feature);
			// C0C1
			feature = "" + charVec.at(i) + charVec.at(i+1);
			feat.push_back(feature);
			// C1C2
			feature = "" + charVec.at(i+1) + charVec.at(i+2);
			feat.push_back(feature);

			// C-1C1
			feature = "" + charVec.at(i-1) + charVec.at(i+1);
			feat.push_back(feature);

			/* dict features */
			//get MWL, t0
			pair<int, string> ans = _dict->GetDictInfo(charVec.at(i).c_str());
			/*
			those dict features
			*/

			/* type features */
			
			featsVec.push_back(feat);
		}
	}
}