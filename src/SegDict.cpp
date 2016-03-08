/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#include "SegDict.h"

namespace cwsp
{
    SegDict::SegDict(const char *DictFileName)
    {
        _dict = new map<string, pair<int, string> >;
        LoadDictFile(DictFileName);
    }

    SegDict::SegDict()
    {
        _dict =new map<string, pair<int, string> >;
    }

    SegDict::~SegDict()
    {
        delete _dict;
    }

    pair<int, string> SegDict::GetDictInfo(const char *feat)
    {
        _Str2PairMapIter it = _dict->find(feat);

        if( it != _dict->end() )
            return it->second;
        else
            return make_pair(1, "S");
    }

    int SegDict::size()
    {
        return _dict->size();
    }

    bool SegDict::LoadDictFile(const char *DictFileName)
    {
        ifstream fin;
        fin.open(DictFileName);
        if ( !fin.is_open())
        {
            cerr<<"\nCan not open the Dictionary file: "<<DictFileName<<endl;
            return false;
        }

        delete _dict;
        _dict = new map<string, pair<int, string> >;

        string myTextLine;
        getline(fin, myTextLine);
        getline(fin, myTextLine);
        int dictSize = fromString<int>(myTextLine);
        for(int i=0; i<dictSize; i++)
        {
            getline(fin, myTextLine);
            TrimLine(myTextLine);
            istringstream is(myTextLine.c_str());
            string word, mwl, tag;
            is >> word;
            is >> mwl;
            is >> tag;
            pair<int, string> tmp = make_pair(fromString<int>(mwl), tag);
            _dict->insert(make_pair(word, tmp));
        }
        return true;
    }
    bool SegDict::SaveDictFile(){
        if (_dict == NULL || _dict->size()==0)
        {
            cerr<<"\nDoes not have any Dictionary information."<<endl;
            return false;
        }
#ifdef WIN32
        string _datapath = "model\\";
#else
        string _datapath = "model/";
#endif
        string FileName = _datapath + "Dict";
        FILE * DictFile = fopen(FileName.c_str(), "w");

        string Header = "#DictFile\n";
        fwrite(Header.data(), Header.length(), 1, DictFile);
        string dictSize = toString(_dict->size()) + "\n";
        fwrite(dictSize.data(), dictSize.length(), 1, DictFile);
        _Str2PairMapIter it;
        for(it = _dict->begin(); it!=_dict->end(); it++)
        {
            string line = it->first + " ";
            line += toString(it->second.first) + " " + it->second.second + "\n";
            fwrite(line.data(), line.length(), 1, DictFile);           
        }
        return true;
    }
}