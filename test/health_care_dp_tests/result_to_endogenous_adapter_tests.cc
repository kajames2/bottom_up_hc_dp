#include "endogenous_state.h"
#include "result_to_endogenous_adapter.h"
#include "period_result.h"
#include "health_state.h"
#include "investment.h"

#include <gtest/gtest.h>
#include <memory>

class ResultToEndogenousAdapterTest : public ::testing::Test {
public:
  ResultToEndogenousAdapterTest() {}

protected:
  virtual void SetUp() {
    state_ = healthcare::HealthState(1, 50, 45, 10);
    healthcare::Investment investment(20, 10);
    life_enjoyment_ = 50;
    healthcare::PeriodResult result(state_, investment, life_enjoyment_);
    end_state_ = std::make_unique<healthcaredp::ResultToEndogenousAdapter>(result);
  }
  healthcare::HealthState state_;
  int life_enjoyment_;
  std::unique_ptr<genericdp::EndogenousState<healthcare::HealthState>> end_state_;
};

TEST_F(ResultToEndogenousAdapterTest, GetState) {
  ASSERT_EQ(state_, end_state_->GetState());
}

TEST_F(ResultToEndogenousAdapterTest, GetValue) {
  ASSERT_EQ(life_enjoyment_, end_state_->GetValue());
}
