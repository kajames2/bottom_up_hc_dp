#include "endogenous_state.h"
#include "result_to_endogenous_adapter.h"
#include "result_to_endogenous_adapter_factory.h"
#include "period_result.h"
#include "period_result_factory.h"
#include "health_state.h"
#include "investment.h"
#include "regeneration.h"
#include "consumption.h"

#include <gtest/gtest.h>
#include <memory>

class ResultToEndogenousAdapterFactoryTest : public ::testing::Test {
public:
  ResultToEndogenousAdapterFactoryTest() {}

protected:
  class MockConsumption : public healthcare::Consumption {
  public:
    MockConsumption() {}
    virtual double GetLifeEnjoyment(int li, int health) const override {
      return 2 * li + health;
    }
  };

  class MockRegeneration : public healthcare::Regeneration {
  public:
    MockRegeneration() {}
    virtual int GetHealthRegained(int hi, int health) const override {
      return hi;
    }
  };

  virtual void SetUp() {
    state_ = healthcare::HealthState(1, 50, 45, 10);
    investment_ = healthcare::Investment(20, 10);
    std::shared_ptr<const MockRegeneration> regen = std::make_shared<const MockRegeneration>();
    std::shared_ptr<const MockConsumption> consumption = std::make_shared<const MockConsumption>();
    result_fact_ = std::make_unique<healthcare::PeriodResultFactory>(regen, consumption);
    adapter_fact_ = std::make_unique<healthcaredp::ResultToEndogenousAdapterFactory>(*result_fact_);
  }
  
  healthcare::HealthState state_;
  healthcare::Investment investment_;
  std::unique_ptr<healthcare::PeriodResultFactory> result_fact_;
  std::unique_ptr<healthcaredp::ResultToEndogenousAdapterFactory> adapter_fact_;
};

TEST_F(ResultToEndogenousAdapterFactoryTest, SameAsPeriodFactoryTest) {
  auto end_state = adapter_fact_->GetEndogenousResult(state_, investment_);
  healthcare::PeriodResult end_result = result_fact_->GetPeriodResult(state_, investment_); 
  ASSERT_EQ(end_result.state, end_state->GetState());
  ASSERT_EQ(end_result.enjoyment, end_state->GetValue());
  ASSERT_EQ(adapter_fact_->GetHealthRegained(state_, investment_), result_fact_->GetHealthRegained(state_, investment_));
}
