#include "SegFeat.h"
#include "SegVocab.h"
#include "SegProb.h"
#include "SegDict.h"
#include "Pretreatment.h"
#include "MultiPerceptron.h"
#include "Config.h"
#include <string>
using namespace std;

void print_help() {
    cout << cwsp::g_copyright
        << "usage: cwsp_train [options] corpus_file model_file\n\n"
        << "options: -h        -> help\n\n"
        << "related resources file configuration:\n"
        << "         -b [0,1]  -> 0: CharType resource file is a text file\n"
        << "                   -> 1: CharType resource file is a binary file (default)\n"
        << "         -d dict   -> Dictionary file (default:model\\Dict.bin)\n"
        // << "         -f feat   -> Feature file (default:model\\Feat.bin)\n"
        // << "         -p prob   -> Probability file (default:model\\Prob.bin)\n"
        << "         -o path   -> Path to save training data file for MultiPerceptron (default:data\\train)"

        << "\nTraining parameters:\n"
        << "         -n int    -> maximal iteration loops (default 200)\n"
        << "         -m double -> minimal loss value decrease (default 1e-03)\n"
        << "         -r [0,1]  -> 0: training model by SGD optimization (default)\n"
        << "                   -> 1: Gradient Descent optimization"     
        << "         -l float  -> learning rate (default 1.0)\n"
        << "         -a        -> 0: final weight (default)\n"
        << "                   -> 1: average weights of all iteration loops\n"
        // << "         -u [0,1]  -> 0: initial training model (default)\n"
        // << "                   -> 1: updating model (pre_model_file is needed)\n" 
        << endl;
}

void read_parameters(int argc, char *argv[], char *corpus_file, char *model_file, 
                        int *max_loop, double *loss_thrd, float *learn_rate, int *optim, 
                        int *avg, bool &is_bin, string &dictfile, string &trainfile) {
    // set default options
#ifdef WIN32
    string _modelpath = "model\\";
    string _datapath = "data\\";
#else
    string _modelpath = "model/"
    string _datapath = "data/";
#endif
    is_bin = true;
    dictfile = _modelpath + "Dict.bin";
    trainfile = _datapath + "train";

    *max_loop = 200;
    *loss_thrd = 1e-3;
    *learn_rate = 1.0;
    *optim = 0;
    *avg = 0;
    // *update = 0;
    int i;
    for (i = 1; (i<argc) && (argv[i])[0]=='-'; i++) {
        switch ((argv[i])[1]) {
            case 'b':
                is_bin = atoi(argv[++i])?true:false;
                break;
            case 'd':
                dictfile.clear();
                dictfile = string(argv[++i]);
                break;
            case 'o':
                trainfile.clear();
                trainfile = string(argv[++i]);
                break;
            case 'h':
                print_help();
                exit(0);
            case 'n':
                *max_loop = atoi(argv[++i]);
                break;
            case 'm':
                *loss_thrd = atof(argv[++i]);
                break;
            case 'l':
                *learn_rate = (float)atof(argv[++i]);
                break;
            case 'r':
                *optim = atoi(argv[++i]);
                break;
            case 'a':
                *avg = atoi(argv[++i]);
                break;
            // case 'u':
            //     *update = atoi(argv[++i]);
            //     break;
            default:
                cout << "Unrecognized option: " << argv[i] << "!" << endl;
                print_help();
                exit(0);
        }
    }
    
    if ((i+1)>=argc) {
        cout << "Not enough parameters!" << endl;
        print_help();
        exit(0);
    }
    strcpy (corpus_file, argv[i]);
    strcpy (model_file, argv[i+1]);
    // if (*update) {
    //     if ((i+2)>=argc) {
    //         cout << "Previous model file is needed in update mode!" << endl;
    //         print_help();
    //         exit(0);
    //     }
    //     strcpy (pre_model_file, argv[i+2]);
    // }
}

int cwsp_train(int argc, char *argv[])
{
    char corpus_file[LINE_LEN_MAX];
    char model_file[LINE_LEN_MAX];
    int max_loop;
    double loss_thrd;
    float learn_rate;
    int optim;
    int avg;
    bool is_bin; 
    string dictfile;
    string trainfile;
    read_parameters(argc, argv, corpus_file, model_file, &max_loop, &loss_thrd, &learn_rate, &optim, &avg, is_bin, dictfile, trainfile);

    string corpus = string(corpus_file);
    string model = string(model_file);
    cwsp::Pretreatment t;
    t.LoadCharFile(is_bin);
    t.LoadDictFile(dictfile.c_str());
    cout<<"\n\nReading corpus file..."<<endl;
    t.TrainSegFile(corpus.c_str()); // TrainSegFile will save Prob & Feat.
    t.PrintInfo();

    cout<<"\nMaking train data..."<<endl;
    t.MakeTrainData(corpus.c_str(), trainfile.c_str());
    cout<<"Finished."<<endl;

    cout<<"\n********************Train********************\n"<<endl;
    cwsp::MultiPerceptron mp;
    mp.load_training_file(trainfile);
    mp.init_omega();
    if (optim) {
        mp.train_batch(max_loop, loss_thrd, learn_rate, avg);       
    }
    else {
        mp.train_SGD(max_loop, loss_thrd, learn_rate, avg);
    }
    mp.save_model(model);
    return 1;
}

int main(int argc, char *argv[])
{
    return cwsp_train(argc, argv);
}