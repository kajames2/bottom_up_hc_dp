#include "linear_degeneration.h"
#include "health_state.h"
#include <gtest/gtest.h>

class LinearDegenerationTest : public ::testing::Test {
public:
  LinearDegenerationTest()
      : period_(0)
      , degen_() {}

protected:
  virtual void SetUp() {
    period_ = 4;
    degen_ = std::make_unique<healthcare::LinearDegeneration>(3,10);
  }
  
  int period_;
  std::unique_ptr<healthcare::LinearDegeneration> degen_;
};

TEST_F(LinearDegenerationTest, GetDegeneration) {
  ASSERT_EQ(22, degen_->GetDegeneration(period_));
}
