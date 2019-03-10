#include <gtest/gtest.h>
#include <vector>
#include<iostream>
#include "../src/Qlearner.hpp"

TEST(test_Qlearner,test_constuctors){

  Qlearner q= Qlearner();  //create new Q-learner and initialize it's values
  q.fillR({{0,0},{-1,100}});
  q.fillQ({{0,0,-1,100},{0,0,-1,100},{-1,-1,-1,-1},{0,0,-1,100}});
  q.initParameter(0.1,0.9,4,3);
  q.initBlocked({2});
 //test constructors and get -methods
  EXPECT_EQ(q.alphaOut(),0.1);
  EXPECT_EQ(q.gammaOut(),0.9);
  EXPECT_EQ(q.statesOut(),4);
  EXPECT_EQ(q.endStateOut(),3);
  EXPECT_EQ(q.blockedOut(),(std::vector<int>{2}));
  EXPECT_EQ(q.outQ(),(std::vector<std::vector<double>>{{0,0,-1,100},{0,0,-1,100},{-1,-1,-1,-1},{0,0,-1,100}}));
  EXPECT_EQ(q.outR(),(std::vector<std::vector<int>>{{0,0},{-1,100}}));
  Qlearner q2= Qlearner(q);
  EXPECT_EQ(q2.alphaOut(),0.1);
  EXPECT_EQ(q2.gammaOut(),0.9);
  EXPECT_EQ(q2.statesOut(),4);
  EXPECT_EQ(q2.endStateOut(),3);
  EXPECT_EQ(q2.blockedOut(),(std::vector<int>{2}));
  EXPECT_EQ(q2.outQ(),(std::vector<std::vector<double>>{{0,0,-1,100},{0,0,-1,100},{-1,-1,-1,-1},{0,0,-1,100}}));
  EXPECT_EQ(q2.outR(),(std::vector<std::vector<int>>{{0,0},{-1,100}}));
}

TEST(test_Qlearner,test_funcions){
 //test functions
  Qlearner a= Qlearner();
  a.fillR({{0,-1,-1,100},{-1,-1,-1,-1},{-1,-1,-1,-1},{0,-1,-1,100}});
  a.fillQ({{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}});
  a.initParameter(1,0,4,3);
  a.initBlocked({1,2});
  a.learnQfrom(0,1);
;

  EXPECT_EQ(a.outQ(),(std::vector<std::vector<double>>{{0,0,0,100.0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}));
  EXPECT_EQ(a.walkQfromVector(0),(std::vector<int>{0,3,3}));
}
