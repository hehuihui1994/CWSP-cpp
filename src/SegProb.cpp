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
		FILE * ProbFile;
		ProbFile = fopen(FileName, "rb");
		if (!ProbFile)
		{
			cerr<<"\nCan not open the Probability info file: "<<FileName<<endl;
			return false;
		}
		char headBuf[UNIGRAM_LEN_MAX];
		fread(&headBuf, g_Header_Len, 1, ProbFile);
		fclose(ProbFile);
		string header = string(headBuf, g_Header_Len);
		if (header == g_Model_Header)
		{
			return ReadBinaryFile(FileName);
		}
		else
		{
			return ReadFile(FileName);
		}
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
		std::cout<<"file path: "<<_datapath<<endl;
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
		if (!ReadFile(InputFileName)) return false;
        std::cout<<"Load text Probability file finished."<<endl;
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
        int initProbSzie = (int)this->_init_prob->size();
        fwrite(&initProbSzie, sizeof(int), 1, bin_lm_file);
        for(int i=0; i<4; i++)
		{
			fwrite(&this->_init_prob->at(i), sizeof(double), 1, bin_lm_file);
		}

        int transProbSize = (int)this->_trans_prob->size();
        fwrite(&transProbSize, sizeof(int), 1, bin_lm_file);
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
			{
				fwrite(&this->_trans_prob->at(i).at(j), sizeof(double), 1, bin_lm_file);
			}
		}
        fclose(str_lm_file);
        fclose(bin_lm_file);
		std::cout<<"Convert to binary file finished!"<<endl;
        return true;
    }

    bool SegProb::ReadFile(const char *FileName)
    {
		ifstream fin;
        fin.open(FileName);
        if( !fin.is_open() )
        {
            cerr<<"\nCan not open the Probability info file: "<<FileName<<endl;
            return false;
        }

        string myTextLine;
        vector<string> tmp;
        delete this->_init_prob;
		delete this->_trans_prob;
        this->_init_prob = new vector<double>;
        this-> _trans_prob = new vector< vector<double> >;

        getline(fin, myTextLine);  // skip the first line
        for(int i=0; i<4; i++)
        {
            getline(fin, myTextLine);
            TrimLine(myTextLine);
			double prob;
			if (myTextLine != "-Inf")
			{
				prob = fromString<double>(myTextLine);
				this->_init_prob->push_back(prob);
			}
			else
			{
				this->_init_prob->push_back(LogP_Zero);
			}
        }

        getline(fin, myTextLine);
        //int bigramSize = fromString<int>(myTextLine);
        for(int i=0; i<4; i++)
        {
            getline(fin, myTextLine);
            TrimLine(myTextLine);
            tmp = SplitString(myTextLine, " ");
			vector<double> probs;
			for(int j=0; j<4; j++)
			{
				if (tmp[j] != "-Inf")
				{
					double prob = fromString<double>(tmp[j]);
					probs.push_back(prob);
				}
				else
				{
					probs.push_back(LogP_Zero);
				}
			}
            //int index = fromString<int>(tmp.back());
			this->_trans_prob->push_back(probs);
        }
        return true;
    }

    bool SegProb::ReadBinaryFile(const char *FileName)
    {
		FILE * probFile;
        probFile = fopen(FileName, "rb");
        if( !probFile )
        {
            cerr<<"\nCan not open the Probability info file: "<<FileName<<endl;
            return false;
        }
        char headBuf[UNIGRAM_LEN_MAX];
        fread(&headBuf, g_Header_Len, 1, probFile);
        string header = string(headBuf, g_Header_Len);
		delete this->_init_prob;
		delete this->_trans_prob;
        this->_init_prob = new vector<double>;
        this-> _trans_prob = new vector< vector<double> >;

		int initProbSize, transProbSize;
		fread(&initProbSize, sizeof(int), 1, probFile);
		for(int i=0; i<4; i++)
		{
			double prob;
			fread(&prob, sizeof(double), 1,probFile);
			this->_init_prob->push_back(prob);
		}

		fread(&transProbSize, sizeof(int), 1, probFile);
		for(int i=0; i<4; i++)
		{
			vector<double> probs;
			for(int j=0; j<4; j++)
			{
				double prob;
				fread(&prob, sizeof(double), 1,probFile);
				probs.push_back(prob);
			}
			this->_trans_prob->push_back(probs);
		}
		return true;
    }

	void SegProb::TrimLine(string & line)
    {
        line.erase(0,line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n")+1); 
    }

    vector<string> SegProb::SplitString(string terms_str, string spliting_tag)
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