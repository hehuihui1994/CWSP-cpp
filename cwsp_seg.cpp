#include "Segmentor.h"
#include "Config.h"
#include <string>
using namespace std;

void print_help() {
    cout << cwsp::g_copyright
        << "\n\nUSAGE: cwsp_seg [options] <model_file> <corpus_file> <seged_file>\n"
        << "OPTIONS:\n"
        << "        -h            -> help\n\n"
        << "        [Resources file configuration]\n"
        << "        -b [0,1]      -> 0: CharType resource file is a text file\n"
        << "                      -> 1: CharType resource file is a binary file (default)\n"
        << "        -d <dict>     -> Dictionary file (default: model\\Dict)\n"
        << "        -f <feat>     -> Feature file (default: model\\Feat)\n"
        << "        -p <prob>     -> Probability file (default: model\\Prob)\n"
        << endl;
}

void read_parameters(int argc, char *argv[], string &model_file, string &corpus_file, string &seged_file,
                        bool &is_bin, string &dictfile, string &featfile, string &probfile)
{
    // set default options
#ifdef WIN32
    string _modelpath = "model\\";
    // string _datapath = "data\\";
#else
    string _modelpath = "model/";
    // string _datapath = "data/";
#endif
    is_bin = true;
    dictfile = _modelpath + "Dict";
    featfile = _modelpath + "Feat";
    probfile = _modelpath + "Prob";

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
            case 'f':
                featfile.clear();
                featfile = string(argv[++i]);
                break;
            case 'h':
                print_help();
                exit(0);
            case 'p':
                probfile.clear();
                probfile = string(argv[++i]);
                break;
            default:
                cout << "Unrecognized option: " << argv[i] << "!" << endl;
                print_help();
                exit(0);
        }
    }
    
    if ((i+2)>=argc) {
        cout << "Not enough parameters!" << endl;
        print_help();
        exit(0);
    }
    model_file = string(argv[i]);
    corpus_file = string(argv[i+1]);
    seged_file = string(argv[i+2]);
}

int cwsp_seg(int argc, char *argv[])
{
    string corpus_file;
    string model_file;
    string seged_file;
    bool is_bin; 
    string dictfile;
    string featfile;
    string probfile;
    read_parameters(argc, argv, model_file, corpus_file, seged_file, is_bin, dictfile, featfile, probfile);

    cout << cwsp::g_copyright<<endl;
    cwsp::Segmentor t;
    if (!t.Initialize(is_bin, dictfile, featfile, probfile, model_file))
    {
        exit(0);
    }

    t.SegFile(corpus_file, seged_file);
    return 1;
}

int main(int argc, char *argv[])
{
    return cwsp_seg(argc, argv);
}