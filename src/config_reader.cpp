#include "config_reader.hpp"
#include "configException.hpp"
#include <sstream>
#include <fstream>


Config::Config() {                   //default constructor of config reader -class
	std::string line,line2;            // Opens "config.txt", if such file is present,
	std::ifstream conf("config.txt");  // and reads the parameters from said file.
  if ((conf.fail())||(conf.bad()))
    throw configIOException();
  while (std::getline(conf,line)) {
		std::istringstream iss(line);
		std::getline(iss,line2,'=');
		std::getline(iss,line2);
		params.push_back(line2);
	}
  alpha = std::stod(params[1]);
  gamma = std::stod(params[2]);
  if ((alpha > 1.0)||(alpha < 0.0))
    throw invalidDoubleException();
  if ((gamma > 1.0)||(gamma < 0.0))
    throw invalidDoubleException();
  numIter = std::stoi(params[0]);
  pngFile = params[3];
  if(params[4] == "true") {
    readQ = true;
    qReadfile = params[5];
  }
  if(params[6] == "true") {
    saveQ = true;
    qSavefile = params[7];
  }
  if (params[8] == "true") {
    setState = true;
    startState = std::stoi(params[9]);
  }
  if (params[10]=="true"){
    keepLearning=true;
  }
  numIterNew = std::stoi(params[11]);
}

std::vector<std::vector<double>> Config::Q_read(int height, int width) {
  std::vector<std::vector<double>> Q;   // Q_read reads Q matrices saved in same
  int size = height*width;              // format as Q_save method uses (doubles
  std::string line, line2;              // separated by ';'). The first line contains
  std::ifstream Qfile(qReadfile);       // the png dimensions, which must match with
  if ((Qfile.fail())||(Qfile.bad()))    //current png dimensions. This is because the R-matrix
    throw readerIOException();          //and Q-matrix need to be of same dimensions.
	std::getline(Qfile,line);
	usedIters = std::stoi(line);
	std::getline(Qfile,line,';');
  std::getline(Qfile,line2);
  if ((std::stoi(line) == height) && (std::stoi(line2) == width)) {
    for (int i = 0; i < size; i++) {
      std::vector<double> row;
      for (int j = 0; j < size; j++) {
        if (j == size - 1) {
          std::getline(Qfile, line);
          row.push_back(std::stod(line));
        }
        else {
          std::getline(Qfile, line,';');
          row.push_back(std::stod(line));
        }
      }
      Q.push_back(row);
    }
    Qfile.close();
    return Q;
  }
  else {
    Qfile.close();
    throw invalidHeightWidthException();
  }
}

void Config::Q_write(int iterations,int height,int width,std::vector<std::vector<double>> Q) {
  std::ofstream Qfile(qSavefile);
	Qfile << iterations << std::endl;
	Qfile << height << ";" << width << std::endl;       //Q_write methods writes Q
  for (unsigned int i = 0; i < Q.size(); i++) {       //matrix in given format to disk
    for (unsigned int j = 0; j < Q.size(); j++) {     //note: first line is always the dimensions of
      if (j == (Q.size() - 1)) {                      //the current png. file (e.g 50x50 pixels)!
        Qfile << Q[i][j] << std::endl;
      }
      else {
        Qfile << Q[i][j] << ';';
      }
    }
  }
  Qfile.close();
}
/* IMPLEMENTATION OF GETTERS, MEMBERS OF CONFIG CLASS */
std::vector<std::string> Config::getParams() {
  return params;
}

std::string Config::getPng() {
  return pngFile;
}

std::string Config::getQRead() {
  return qReadfile;
}

std::string Config::getQSave() {
  return qSavefile;
}

int Config::getStartState() {
  return startState;
}

int Config::getNewIterCnt() {
	return numIterNew;
}

int Config::getIterCnt() {
  return numIter;
}

double Config::getAlpha() {
  return alpha;
}

double Config::getGamma() {
  return gamma;
}

bool Config::getSaveState() {
  return saveQ;
}

bool Config::getReadState() {
  return readQ;
}

bool Config::setStartState() {
  return setState;
}
bool Config::getKeep(){
  return keepLearning;
}

int Config::getUsedIters() {
	return usedIters;
}
