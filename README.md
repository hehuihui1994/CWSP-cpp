# CWSP-cpp

----

## Introduction

> CWSP is a Chinese word segmentation toolkit. It used MultiPerceptron algorithm to train model and the Viterbi algorithm to do decode work. Implemented by c++.



## Data format

CWSP-cpp, now, only support UTF-8 file.

Pretreatment will generates feature list and training data for multiPerceptron. **AND Pretreatment program only can handle with half-width space.**

Segmentor use the model file which generate by MultiPerceptron to do segmenetation work.

## Installation

It is easy to type `make`. And make sure all the source code files exist.

## Usage

### Training a segmentor

Use command `cwsp_train` to train a segmentor:

	USAGE: cwsp_train [options] <corpus_file> <model_file>
	OPTIONS:
    	    -h            -> help
	
    	    [Resources file configuration]
        	-b [0,1]      -> 0: CharType resource file is a text file
            	          -> 1: CharType resource file is a binary file (default)
	        -d <dict>     -> Dictionary file (default: model\Dict)


    	    [Training parameters]
        	-n int        -> maximal iteration loops (default 200)
	        -m double     -> minimal loss value decrease (default 1e-03)
    	    -r [0,1]      -> 0: training model by SGD optimization (default)
        	              -> 1: Gradient Descent optimization
	        -l float      -> learning rate (default 1.0)
    	    -a            -> 0: final weight (default)
        	              -> 1: average weights of all iteration loops

The `cwsp_train` command need a extra dictionary file which is default given by path(model/Dict), and it will generate two files named Feat and Prob. 

File "Feat" is a lookup table for characeter feature to feature vector. And file "Prob" is probability information statistic generate by Pretreatment process, it will be used to decode.

### Segmentation

Use command `cwsp_seg` to do segmentation work:

	USAGE: cwsp_seg [options] <model_file> <corpus_file> <seged_file>
	OPTIONS:
    	    -h            -> help

        	[Resources file configuration]
	        -b [0,1]      -> 0: CharType resource file is a text file
    	                  -> 1: CharType resource file is a binary file (default)
        	-d <dict>     -> Dictionary file (default: model\Dict)
	        -f <feat>     -> Feature file (default: model\Feat)
    	    -p <prob>     -> Probability file (default: model\Prob)
    	    
## Resource file

### Under /data

CharType resource files:

	.
	├── data
	│   ├── ANum
	│   ├── CFamilyName
	│   ├── CGivenName
	│   ├── CNum1
	│   ├── CNum2
	│   ├── Date
	│   ├── EChar
	│   ├── ForeignName
	│   ├── Punc
	│   └── binarySource

All these files are the resources for CharType module, which used to generate features for given character. Each file includes a certain kind of Chinese characters. For example, "年", "月" and "日" are belong to the "Date" type in Chinese.

And the file "binarySource" is a binary resource file for CharType, it includes all types of character CharType needs.

### Under /model

Dict, Feat, and Prob:

	.
	├── model
	│   ├── Dict
	│   ├── Feat
	│   └── Prob
	
Dict stores dictionary informations for CWSP. And it should be given before start training a segmentor.

Feat & Prob are model files generated by CWSP during training processing.