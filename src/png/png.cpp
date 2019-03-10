#include "lodepng.h"
#include "png.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

/*
 * Load PNG file from disk to memory first, then decode to raw pixels in memory.
 * Returns a tuple, which has three different members:
 * First: A 1D vector of raw pixel data, which has four falues for each pixel(RGBA)
 * Second: the height of the image
 * Third: the width of the image
*/
std::tuple< std::vector<unsigned char>, int, int > decodePng(const char* filename)
{
	std::vector<unsigned char> png;
	std::vector<unsigned char> image;
	unsigned width, height;

	unsigned error = lodepng::load_file(png, filename);
	if(!error) {
		error = lodepng::decode(image, width, height, png);
	}

	if(error) {
		std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	}
	std::tuple< std::vector<unsigned char>, int, int > ret_triple = std::make_tuple( image, height, width );
	return ret_triple;
}

/*
 * Transform the png file into usable pixel data, in our case, the map to be drawn and used for Q and R matrices.
 * Returns a tuple, which has three different members:
 * First: XY-coordinates of the map: everything is either -1(Wall), 0(path), or 100(goal)
 * Second: Returns the height of the map
 * Third: Returns the width of the map 
*/
std::tuple< std::vector< std::vector<int> >, int, int > pngToPixels(const char* filename)
{
	std::tuple< std::vector<unsigned char>, int, int > image = decodePng(filename);

	int height = std::get<1>(image);
	int width = std::get<2>(image);
	std::vector<unsigned char> im = std::get<0>(image);

	std::vector<std::vector<int> > raw_map;

	for(int y = 0; y < height; y++) {
		std::vector<int> temp;
		for(int x = 0; x < width; x++) {

			if( (int)im[4*width*y + 4*x + 0] == 255 &&
				(int)im[4*width*y + 4*x + 1] == 255 &&
				(int)im[4*width*y + 4*x + 2] == 255 &&
				(int)im[4*width*y + 4*x + 3] == 255 ) {
					temp.push_back(0);
				}
			else if( (int)im[4*width*y + 4*x + 0] == 255 &&
				(int)im[4*width*y + 4*x + 1] == 0 &&
				(int)im[4*width*y + 4*x + 2] == 0 &&
				(int)im[4*width*y + 4*x + 3] == 255 ) {
					temp.push_back(100);
				}
			else {
				temp.push_back(-1);
			}
		}
		raw_map.push_back(temp);
	}
	std::tuple< std::vector< std::vector<int> >, int, int > ret_tuple = std::make_tuple(raw_map, height, width);
	return ret_tuple;
}

void printPixels(int height, int width, std::vector< std::vector<int> > pixels)
{
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			std::cout << std::setw(4) << pixels[y][x];
			}
		std::cout << std::endl;
	}
}
/*Function to transform pixels matrix to R matrix. By default there are more blocked (-1) states than available (0) states.
  Therefore, row vector with default value blocked (-1) is used.*/
std::vector< std::vector <int> > pngToR (int height, int width, std::vector<std::vector<int>> pixels) {
	std::vector<std::vector<int>> R;
	for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				std::vector<std::vector<int>> dir = {{j,i+1},{j+1,i+1},{1+j,i},{1+j,i-1},{j,i-1},{j-1,i-1},{j-1,i},{j-1,i+1}}; //vector containing all possible directions
				std::vector<int> row;																																													 //to traverse the pixels matrix. They are stored
				for (int size = 0; size < height * width; size++) {																														 //as dynamic co-ordinates rather than a direction pair.
					row.push_back(-1);																																													 //This makes the iteration through the pixels matrix easier
			}
					for (int k = 0; k < 8; k++) {
						if (pixels[j][i] == -1) {  //if in non-accesible "square", break and try next "direction"
							break;
						}
						int x = dir[k][1], y = dir[k][0];
						if ((j == 0) && (i == 0)) {   // check if in N-W corner, if yes, append only certain states to row
							if (k < 3) {								// this is done to avoid reading from uninitialized memory
							row[width*(y)+x] = pixels[y][x];
							}
						}
						else if ((j == 0) && (i == width -1)) { // check if in N-E corner, if yes, append only certain states to row
							if ((k > 1) && (k < 5)) {
								row[width*(y)+x] = pixels[y][x];
							}
						}
						else if ((i == 0) && (j == height - 1)) { // check if in S-W corner, if yes, append only certain states to row
								if ((k == 6) || (k == 7) || (k == 0)) {
									row[width*(y)+x] = pixels[y][x];
								}
						}
						else if ((i == width - 1) && (j == height - 1)) { // check if in S-E corner, if yes, append only certain atates to row
							if ((k == 4) || (k==5) || (k==6)) {
								row[width*(y)+x] = pixels[y][x];
							}
						}
						else {
							if ((x > -1) && (x < width) && (y > -1) && (y < height)) { // else if not in corners, and coordinates are within bounds
								row[width*(y)+x] = pixels[y][x];												 // append states in row
							}
						}
					}
					R.push_back(row); //finally append row to R
			}
	}
	return R;
}


//Function finds states with value -1 and finishing point
std::tuple< std::vector<int >,int,int > findStates(std::vector< std::vector<int> > R){
  std::vector<int> blocked;
  int finish;
  int index = 0; //index of found state
  for(auto i : R){
    for(auto j: i){
      if(j==-1){
				blocked.push_back(index);
      }
      else if(j==100){ //if finish state is found
				finish=index;  //set the finish point as index
      }
      index++;
    }
  }
  std::tuple< std::vector<int >,int,int > states = std::make_tuple(blocked, finish,index);
  return states;


}
