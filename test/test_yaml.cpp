#include "yaml/yaml.hpp"

#include <fstream>
#include <string>

#include "gtest/gtest.h"

class YamlTest : public testing::Test {
 protected:
  virtual void SetUp() {
    y2_["a"] = 2017;
    y2_["b"] = 3.1415;
    y2_["c"] = std::string("string");
    y2_["d"] = "const char*";
    y2_["e"] = true;
    y2_["list"][0] = 0;
    y2_["list"][1] = 1;
    y2_["list"][2] = 2;
    y2_["list"][3]["sub-dic"]["a"] = 1;
    y2_["list"][3]["sub-dic"]["b"] = 1604;
    y2_["list"][4]["sub-list"][0] = "sub-list-0";
    y2_["list"][4]["sub-list"][1] = 4061;
    y2_["f"]["int"] = 1998;
    y2_["f"]["double"] = 19.98;
    y2_["f"]["string"] = "1998";
    y2_["f"]["bool"] = false;
  }
  virtual void TearDown() {}
  pessum::yaml::Node y1_, y2_;
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

TEST_F(YamlTest, Conversion) {
  EXPECT_EQ(y2_["a"].Int(), 2017);
  EXPECT_EQ(y2_["b"].Double(), 3.1415);
  EXPECT_EQ(y2_["c"].String(), "string");
  EXPECT_EQ(y2_["d"].String(), "const char*");
  EXPECT_EQ(y2_["e"].Bool(), true);
}

TEST_F(YamlTest, Type) {
  EXPECT_EQ(y2_.type(), pessum::yaml::DICTIONARY);
  EXPECT_EQ(y2_["a"].type(), pessum::yaml::INT);
  EXPECT_EQ(y2_["b"].type(), pessum::yaml::DOUBLE);
  EXPECT_EQ(y2_["c"].type(), pessum::yaml::STRING);
  EXPECT_EQ(y2_["d"].type(), pessum::yaml::STRING);
  EXPECT_EQ(y2_["e"].type(), pessum::yaml::BOOL);
  EXPECT_EQ(y2_["list"].type(), pessum::yaml::LIST);
  EXPECT_EQ(y2_["list"][0].type(), pessum::yaml::INT);
}

TEST_F(YamlTest, Size) {
  EXPECT_EQ(y2_.size(), 7);
  EXPECT_EQ(y2_["a"].size(), 0);
  EXPECT_EQ(y2_["list"].size(), 5);
}

TEST_F(YamlTest, Find) {
  EXPECT_EQ(y2_.find("list"), y2_["list"]);
  EXPECT_EQ(y2_.find("f.int"), 1998);
  EXPECT_EQ(y2_("list.sub-dic.b"), 1604);
  EXPECT_EQ(y2_.find("list.4.sub-list.1"), 4061);
}

TEST_F(YamlTest, GetString) {
  std::string y2_str = y2_.GetString();
  std::string match =
      "a: 2017\n"
      "b: 3.1415\n"
      "c: string\n"
      "d: const char*\n"
      "e: True\n"
      "f: \n"
      "  bool: False\n"
      "  double: 19.98\n"
      "  int: 1998\n"
      "  string: 1998\n"
      "list: \n"
      "  - 0\n"
      "  - 1\n"
      "  - 2\n"
      "  - sub-dic: \n"
      "    a: 1\n"
      "    b: 1604\n"
      "  - sub-list: \n"
      "    - sub-list-0\n"
      "    - 4061";
  EXPECT_EQ(y2_str, match);
}
