#include "log.hpp"
#include <gtest/gtest.h>

TEST(LogTest, SuccessLog) {
  EXPECT_EQ(pessum::global_logs.size(), 0);
  pessum::Log(pessum::SUCCESS, "Success log test", "LogTest/SuccessLog");
  EXPECT_EQ(pessum::global_logs.size(), 1);
}
