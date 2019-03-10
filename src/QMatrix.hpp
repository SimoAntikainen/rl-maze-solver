#ifndef QMTRX_HH
#define QMTRX_HH
#include <vector>
#include <tuple>
#include "png/png.hpp"
#include "config_reader.hpp"

//Definition of QMatrix class. This class encapsulates Q,R, and pixel matrices for
//a certain .png-file. Parameters for height, width and numerous other important Parameters
//are stored in this class


class QMatrix{
private:
  std::vector<std::vector<double>> Q;
  std::vector< std::vector<int> > R;
  std::tuple<std::vector< std::vector<int>>, int, int> map_data;
  std::tuple< std::vector<int>, int, int> stations;
  int startState;
public:
  QMatrix();
  ~QMatrix();
  std::vector<std::vector<double>> getQMatrix();
  std::vector< std::vector<int> > getRMatrix();
  std::vector<int> getBlocked() ;
  int getFinishingPoint();
  int getCountOfPixels();
  std::vector< std::vector<int>> getPixels() ;
  int getHeight();
  int getWidth();
  int getStartState();
  void operator=(std::vector<std::vector<double>> matrix);


};
#endif
