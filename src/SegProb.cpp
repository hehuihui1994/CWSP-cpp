/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#include "SegProb.h"

namespace cwsp
{
    SegProb::SegProb()
    {
        _init_prob = new vector<double>;
        _trans_prob = new vector< vector<double> >;

        for(int i=0; i<4; i++)
        {
            _init_prob->push_back(0.0);
            vector<double> tmp (4, 0.0);
            _trans_prob->push_back(tmp);
        }
    }

    SegProb::~SegProb()
    {   
        _init_prob->clear();
        _trans_prob->clear();
        delete _init_prob;
        delete _trans_prob;
    }

    void SegProb::InitProbCount(int tag)
    {
        if (this->_init_prob == NULL)
        {
            cerr<<"Fatal Error, there is no _init_prob!"<<endl;
            return;
        }
        if (tag < g_tagIdLbound || tag > g_tagIdRbound)
        {
            cerr<<"Error, given tag beyond the range of 4-tag-system!"<<endl;
            return;
        }
        (this->_init_prob->at(tag))++;
        return;
    }

    void SegProb::TransProbCount(int s, int d)
    {
        if (this->_trans_prob == NULL)
        {
            cerr<<"Fatal Error, there is no _trans_prob!"<<endl;
            return;
        }
        if (s < g_tagIdLbound || s > g_tagIdRbound || d < g_tagIdLbound|| d > g_tagIdRbound)
        {
            cerr<<"Error, given tag beyond the range of 4-tag-system!"<<endl;
            return;
        }
        (this->_trans_prob->at(s).at(d))++;
        return;
    }

    bool SegProb::CalcAllProb()
    {
        double init_sum = 0.0;
        vector<double> trans_sum (4, 0.0);

        for (int i=0; i<4; i++)
        {
            init_sum += this->_init_prob->at(i);
            for(int j=0;j<4;j++)
                trans_sum[i] += this->_trans_prob->at(i).at(j);
        }

        for (int i=0;i<4;i++)
        {
            this->_init_prob->at(i) /= init_sum;
            for(int j=0;j<4;j++)
                this->_trans_prob->at(i).at(j) /= trans_sum[i];
        }

        for (int i=0;i<4;i++)
        {
            if (this->_init_prob->at(i) != 0.0)
                this->_init_prob->at(i) = log(this->_init_prob->at(i));
            else 
                this->_init_prob->at(i) = LogP_Zero;
            for(int j=0;j<4;j++)
            {
                if (this->_trans_prob->at(i).at(j) != 0.0)
                    this->_trans_prob->at(i).at(j) = log(this->_trans_prob->at(i).at(j));
                else 
                    this->_trans_prob->at(i).at(j) = LogP_Zero;
            }
        }
        return true;
    }

    double SegProb::GetInitProb(int tag)
    {
        if (this->_init_prob == NULL)
        {
            cerr<<"Fatal Error, there is no _init_prob!"<<endl;
            return 0.0;
        }
        if (tag < g_tagIdLbound || tag > g_tagIdRbound)
        {
            cerr<<"Error, given tag beyond the range of 4-tag-system!"<<endl;
            return 0.0;
        }
        return this->_init_prob->at(tag);
    }

    double SegProb::GetTransProb(int s, int d)
    {
        if (this->_trans_prob == NULL)
        {
            cerr<<"Fatal Error, there is no _trans_prob!"<<endl;
            return 0.0;
        }
        if (s < g_tagIdLbound || s > g_tagIdRbound || d < g_tagIdLbound|| d > g_tagIdRbound)
        {
            cerr<<"Error, given tag beyond the range of 4-tag-system!"<<endl;
            return 0.0;
        }
        return this->_trans_prob->at(s).at(d);
    }

    bool SegProb::LoadProbFile(const char *FileName)
    {

    }

    bool SegProb::SaveProbFile()
    {
        if (this->_init_prob == NULL || this->_trans_prob == NULL)
        {
            cerr<<"\nDoes not have any probability information."<<endl;
            return false;
        }
#ifdef WIN32
        string _datapath = "model\\";
#else
        string _datapath = "model/";
#endif
        string FileName = _datapath + "Prob";
        FILE * ProbFile;
        ProbFile = fopen(FileName.c_str(), "w");

        // write init prob
        string Header = "#InitProb\n"; 
        fwrite(Header.data(), Header.length(), 1, ProbFile);
        for(int i=0;i<4;i++)
        {
            string prob;
            if (_init_prob->at(i) == LogP_Zero)
                prob = "-Inf\n";
            else
                prob = toString(_init_prob->at(i)) + "\n";
            fwrite(prob.data(), prob.length(), 1, ProbFile);
        }

        Header = "#TransProb\n";
        fwrite(Header.data(), Header.length(), 1, ProbFile);
        for(int i=0;i<4;i++)
        {
            string prob = "";
            for(int j=0;j<4;j++)
            {
                if (_trans_prob->at(i).at(j) == LogP_Zero)
                    prob += "-Inf ";
                else
                    prob += toString(_trans_prob->at(i).at(j)) + " ";
            }
            prob += "\n";
            fwrite(prob.data(), prob.length(), 1, ProbFile);
        }
        return true;
    }

    bool SegProb::ConvertToBinaryFile(const char* InputFileName, const char* OutputFileName)
    {

    }

    bool SegProb::ReadFile(const char *FileName)
    {

    }

    bool SegProb::ReadBinaryFile(const char *FileName)
    {

    }
}