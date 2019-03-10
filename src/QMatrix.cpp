#include "QMatrix.hpp"
#include <algorithm>
#include "iterator"
#include<ctime>

QMatrix::QMatrix(){ //default constructor of QMatrix class
  Config c;
  map_data = pngToPixels(c.getPng().c_str());
  std::vector< std::vector<int>> pixels = std::get<0>(map_data);
  int height = std::get<1>(map_data);
  int width  = std::get<2>(map_data);
  R = pngToR(height, width, pixels);
  std::vector<std::vector<double>> matrix(R.size(), std::vector<double>(R[0].size()));
  Q=matrix;
  stations=findStates(pixels);

  std::srand(std::time(0));
  if (c.setStartState()) {
	startState=c.getStartState();
  }
  else {
    int size = height * width;
    int state = rand() % size;
    std::vector<int> blocked = std::get<0>(stations);
    while ((std::find(blocked.begin(), blocked.end(), state) != blocked.end())) {
      state = rand() % size;
    }
    startState=state;
	}
}


QMatrix::~QMatrix(){} //default destructor of QMatrix class

/* Getter implemented below: */

std::vector<std::vector<double>> QMatrix::getQMatrix(){
  return Q;
}

std::vector< std::vector<int> > QMatrix::getRMatrix(){
  return R;
}

std::vector<int> QMatrix::getBlocked(){ //return all blocked states (see png.cpp)
  return std::get<0>(stations);
}
int QMatrix::getFinishingPoint(){ //return goal (100) state
  return std::get<1>(stations);
}

int QMatrix::getCountOfPixels(){
  return std::get<2>(stations);
}

std::vector< std::vector<int>> QMatrix::getPixels(){ //returns pixel-matrix
  return std::get<0>(map_data);
}

int QMatrix::getHeight(){  //height and width are that of the .png file. e.g. 50 x 50 pixels
  return std::get<1>(map_data); //Q and R are (height*width) x (height*width) matrices, e.g 2500 x 2500
}

int QMatrix::getWidth(){
  return std::get<2>(map_data);
}

int QMatrix::getStartState(){ //return starting point, if predefined.
  return startState;
}

void QMatrix::operator=(std::vector<std::vector<double>> matrix){ // Assign Q-matrix
  Q=matrix;                                                       // through assignment
}
