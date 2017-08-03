#ifndef _STOCHASTIC_EXOGENOUS_STATE_H_
#define _STOCHASTIC_EXOGENOUS_STATE_H_

#include <memory>

namespace genericdp {
template <class T> class StochasticExogenousState : public ExogenousState<T> {
public:
  ExogenousState(std::unique_ptr<ExogenousState<T>> state, double prob)
      : state_(std::move(state)), probability_(prob) {}

  virtual T GetState() const override { return state_->GetState(); }

  virtual std::unique_ptr<ExogenousState<T>> Clone() const override {
    return std::make_unique<StochasticExogenousState>(state_->Clone(),
                                                      probability_);
  };

  virtual std::string GetString() const override {
    return std::to_string(probability_) + ", " + state_->GetString();
  }
  virtual std::string GetHeader() const override {
    return std::string("Probability") + ", " + state_->GetHeader()
  }

  double GetProbability const { return probability_; }

private:
  std::unique_ptr<ExogenousState<T>> state_;
  double probability_;
};
} // namespace genericdp
#endif // _STOCHASTIC_EXOGENOUS_STATE_H_
