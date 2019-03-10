#include <gtest/gtest.h>
#include <tuple>
#include <vector>
#include "../src/png/png.hpp"
#include "../src/config_reader.hpp"


TEST(test_png,test_functions){
  Config c =Config();
  int height=4; //create paramaters for imaginary .png-file
  int width=4;
  std::vector<std::vector<int>> pixels={{0,0,0,0},{0,-1,-1,0},{0,-1,0,0},{0,-1,0,100}}; //create pixels vector
  std::vector<int>blocked={5,6,9,13}; //create corresponding blocked states
  int finish=15; //finishing point
  int states=16; //number of states
  std::tuple< std::vector< int >, int, int > R_data = std::make_tuple(blocked,finish,states); //equal to findStates return value
  std::vector<std::vector<int>> R1={{-1,0,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{0,-1,0,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,0,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,0,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1},{0,0,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,0,0,-1,-1,-1,-1,-1,-1,0,0,-1,-1,-1,-1},{-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,0,100},{-1,-1,-1,-1,-1,-1,-1,0,-1,-1,0,-1,-1,-1,0,100},{-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,-1,-1,-1,100},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,-1,-1,0,-1}};
  // R1 is equal to the return value of pngToR for this particular instance
  std::tuple< std::vector< std::vector<int> >, int, int > png_R = std::make_tuple(pixels, height, width); //equal to return value of pngToPixels
  EXPECT_EQ(pngToR(height,width,pixels),R1);
  EXPECT_EQ(pngToPixels(c.getPng().c_str()),png_R); // test whether pngToPixels works properly
  EXPECT_EQ(findStates(pixels),R_data); //test whether findStates works properly
  }
