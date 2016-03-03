/********************************************************************
* cwsp: Chinese Word Segmentation Toolkit used multi-perceptron.

*********************************************************************/

#ifndef STR_FUN_H_
#define STR_FUN_H_

#include "Config.h"

namespace cwsp
{
    template <class T> std::string toString(const T& a)
    {
        std::ostringstream ost;
        ost << a;
        return ost.str();
    }

    template<typename T>T fromString( const std::string& s)
    {
        std::istringstream is(s);
        T t;
        is >> t;
        return t;
    }

    void TrimLine(string & line)
    {
        line.erase(0,line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n")+1); 
    }

    vector<string> SplitString(string terms_str, string spliting_tag)
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

#endif


