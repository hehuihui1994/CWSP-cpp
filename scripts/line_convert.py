#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on 14:27:56 2016-08-09

@author: heshenghuan (heshenghuan@sina.com)
http://github.com/heshenghuan
"""

import codecs
import sys


def character_tagging(input_file, output_file):
    input_data = codecs.open(input_file, 'r', 'utf-8')
    output_data = codecs.open(output_file, 'w', 'utf-8')
    for line in input_data.readlines():
        word_list = line.strip().split()
        for word in word_list:
            if len(word) == 1:
                output_data.write(word + " S\n")
            else:
                output_data.write(word[0] + " B\n")
                for w in word[1:len(word) - 1]:
                    output_data.write(w + " M\n")
                output_data.write(word[len(word) - 1] + " E\n")
        output_data.write("\n")
    input_data.close()
    output_data.close()


def usage():
    print "Convertion Python script for lines to (char tag) pairs."
    print "Please make sure the format of source is correct."
    print "This script only has simple conversion function,",
    print "and CANNOT detect wrong input.\n"
    print "Usage: python line_convert.py SOURCE OUTPUT"
    print "       SOURCE the file you want to convert"
    print "       OUTPUT the path of output file"

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print "ERROR! Not enough parameters!\n"
        usage()
        sys.exit()
    character_tagging(sys.argv[1], sys.argv[2])
