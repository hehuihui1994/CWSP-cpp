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
    }

    Pretreatment::~Pretreatment()
    {
        delete _features;
        delete _probs;
    }

    bool Pretreatment::TrainSegFile(const char * FileName)
    {
        ifstream fin;
        fin.open(FileName);
        if (!fin.is_open())
        {
            cerr << "###########################################" << endl;
            cerr << "Open " << inputfile << " error!" << endl;
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
}