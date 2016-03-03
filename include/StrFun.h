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
}

#endif


