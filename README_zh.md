# CWSP-cpp

------

## 简介

> CWSP是一个中文分词工具。它使用了多类感知器作为模型进行训练，并用维特比算法进行解码工作。使用C++编程实现。



## 数据格式

CWSP-cpp目前仅支持UTF-8格式文件。

预处理工作将会产生特征文件和感知器训练所需的训练数据。需要注意的是，预处理程序仅能处理半角空格，如果您的文件中包含全角空格请替换它们为半角空格。

分词器使用多类感知器程序生成的模型文件进行分词工作。

## 安装

使用`make`命令可以很容易的进行安装。但请确保所有源文件都存在。

## 使用方法

### 训练

使用命令 `cwsp_train`训练一个分词器：

```shell
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
```

`cwsp_train`命令需要指定外部字典文件的路径（默认使用model/Dict文件），它将会在训练结束之后生成两个文件，分别为Feat和Prob文件。

“Feat”文件是一张查找表，用于字符特征到特征向量的映射。“Prob”文件是预处理工作产生的概率信息统计结果，将在解码工作中被使用。

### 分词

使用命令 `cwsp_segs`使用分词器进行分词：

```shell
USAGE: cwsp_seg [options] <model_file> <corpus_file> <seged_file>
OPTIONS:
	    -h            -> help

    	[Resources file configuration]
        -b [0,1]      -> 0: CharType resource file is a text file
	                  -> 1: CharType resource file is a binary file (default)
    	-d <dict>     -> Dictionary file (default: model\Dict)
        -f <feat>     -> Feature file (default: model\Feat)
	    -p <prob>     -> Probability file (default: model\Prob)
```

## 资源文件

### /data目录下

字符类别文件：

```
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
```

如上所示，所有上述文件都是CharType模型的资源文件，将用于产生给定字符的特征。每个文件都包含一个特定类别的中文字符。例如“年”、“月”、“日”等属于中文中的“Date”类别。

名为“binarySource”的文件是CharType模型所需资源文件的二进制打包文件，它包含了CharType需要的所有类别的字符信息。

### /model目录下

Dict文件、 Feat文件和Prob文件：

```
.
├── model
│   ├── Dict
│   ├── Feat
│   └── Prob
```

Dict文件存储了CWSP所需的额外字典信息。它应该在训练开始前就给出。

Feat和Prob文件是CWSP训练期间产生的模型文件。

## 更新日志

- 2016-08-22 版本 1.0.3
  - MultiPerceptron现在已经支持模型文件的二进制格式或文本格式读写。
- 2016-08-09 版本 1.0.2
  - 添加了两个用于语料文件格式转换的脚本。
- 2016-04-19 版本 1.0.1
  - 修复了一个bug，该bug导致训练中间数据被保存为文本文件。现在中间训练数据仅存在于内存中。
- 2016-04-07 版本 1.0.0
  - 初始版本，CWSP，基于多类感知器算法的中文分词器。