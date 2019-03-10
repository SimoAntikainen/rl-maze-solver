#ifndef CFG_HH
#define CFG_HH
#include <vector>
#include <string>



class Config {  // class for reading the 'config.txt' -file. This file contains
public:         // different parameters on how to execute the program.
  Config();
  std::vector<std::string> getParams();
  std::vector<std::vector<double>> Q_read(int height, int width);
  void Q_write(int iterations,int height, int width,std::vector<std::vector<double>> Q);
  std::string getPng();
  std::string getQSave();
  std::string getQRead();
  int getIterCnt();
  int getNewIterCnt();
  int getUsedIters();
  int getStartState();
  double getAlpha();
  double getGamma();
  bool getReadState();
  bool getSaveState();
  bool setStartState();
  bool getKeep();
private:
  std::vector<std::string> params;            // Config data is first stored as a
  std::string pngFile, qSavefile, qReadfile;  // vector of std::strings. After the whole
  int numIter, startState, numIterNew, usedIters = 0;                    //  file is read, they are stored in individual
  double gamma, alpha;                        //  variables for easier access and handling
  bool saveQ = false, readQ = false, setState = false,keepLearning=false;
};
#endif
