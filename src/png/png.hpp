#ifndef PNG_HH
#define PNG_HH
#include <tuple>
#include <vector>


std::tuple< std::vector< std::vector<int> >, int, int > pngToPixels(const char* filename);

void printPixels(int height, int width, std::vector< std::vector<int> > pixels);

std::vector< std::vector <int> > pngToR (int height, int width, std::vector<std::vector<int>> pixels);

std::tuple< std::vector<int >,int,int > findStates(std::vector< std::vector<int> > R);


#endif
