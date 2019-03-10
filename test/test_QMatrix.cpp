#include <gtest/gtest.h>
#include <vector>
#include "../src/QMatrix.hpp"
#include "../src/config_reader.hpp"



TEST(test_QMatrix, test_constuctor){
  QMatrix Q=QMatrix(); //init new QMatrix instance
  int starting=Q.getStartState();
  EXPECT_EQ(starting,0);  //test various methods of the class
  EXPECT_EQ(Q.getWidth(),4);
  EXPECT_EQ(Q.getHeight(),4);
  EXPECT_EQ(Q.getCountOfPixels(),16);
  EXPECT_EQ(Q.getFinishingPoint(),15);
  EXPECT_EQ(Q.getBlocked(),(std::vector<int>{5,6,9,13}));
  EXPECT_EQ(Q.getPixels(),(std::vector<std::vector<int>>{{0,0,0,0},{0,-1,-1,0},{0,-1,0,0},{0,-1,0,100}}));

  Q={{0,0,0,0},{-1,-1,-1,-1}};
  EXPECT_EQ(Q.getQMatrix(),(std::vector<std::vector<double>>{{0,0,0,0},{-1,-1,-1,-1}}));
}
