#include "yaml/yaml.hpp"

#include <fstream>
#include <string>

#include "gtest/gtest.h"

class YamlTest : public testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
  pessum::yaml::Node y1_;
};

TEST_F(YamlTest, DefaultConstructor) {
  EXPECT_EQ(y1_.valid(), false);
  EXPECT_EQ(y1_.sub_nodes_.size(), 0);
}

TEST_F(YamlTest, PushBackValue) {
  y1_.push_back(2017);
  y1_.push_back(3.1415);
  y1_.push_back(std::string("String"));
  y1_.push_back("const char*");
  y1_.push_back(true);
  EXPECT_EQ(y1_[0].Int(), 2017);
  EXPECT_EQ(y1_[1].Double(), 3.1415);
  EXPECT_EQ(y1_[2].String(), std::string("String"));
  EXPECT_EQ(y1_[3].String(), "const char*");
  EXPECT_EQ(y1_[4].Bool(), true);
}
