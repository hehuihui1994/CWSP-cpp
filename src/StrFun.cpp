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

#include "StrFun.h"

namespace cwsp
{
    void TrimLine(string & line)
    {
        line.erase(0,line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n")+1); 
    }
}