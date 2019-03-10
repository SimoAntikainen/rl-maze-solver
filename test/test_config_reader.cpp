#include<gtest/gtest.h>
#include<vector>
#include<string>
#include<iostream>
#include "../src/config_reader.hpp"


TEST(test_config_reader, get_functions){ // Tests for Config-class and it's methods
  Config c = Config();
  EXPECT_EQ(c.getIterCnt(),10);
  EXPECT_EQ(c.getPng(),"4x4.png");
  EXPECT_EQ(c.getStartState(),0);
  EXPECT_EQ(c.getAlpha(),1);
  EXPECT_EQ(c.getGamma(),0);
  EXPECT_EQ(c.getReadState(),true);
  EXPECT_EQ(c.getSaveState(),true);
  EXPECT_EQ(c.getKeep(),false);
  EXPECT_EQ(c.getQSave(),"save.txt");
  EXPECT_EQ(c.getQRead(),"load.txt");
  EXPECT_EQ(c.getNewIterCnt(),25);
}
