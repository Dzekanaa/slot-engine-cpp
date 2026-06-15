#include "../include/slot_engine.h"
#include "../include/spin_engine.h"
#include <random>

namespace SlotEngine {

struct SlotEngineImpl::Impl {
  GameConfig config;
  SpinEngine spinEngine;
  std::mt19937 rng;

  Impl(const GameConfig &cfg)
      : config(cfg), spinEngine(cfg), rng(std::random_device{}()) {}
};

SlotEngineImpl::SlotEngineImpl(const GameConfig &config)
    : pImpl(std::make_unique<Impl>(config)) {}

SlotEngineImpl::~SlotEngineImpl() = default;

SpinResult SlotEngineImpl::Spin() {
  return pImpl->spinEngine.PerformSpin(pImpl->rng);
}

const GameConfig &SlotEngineImpl::GetConfig() const { return pImpl->config; }

void SlotEngineImpl::SetConfig(const GameConfig &config) {
  pImpl->config = config;
  pImpl->spinEngine = SpinEngine(config);
}

void SlotEngineImpl::Reset() {
  pImpl->rng = std::mt19937(std::random_device{}());
}

std::unique_ptr<ISlotEngine> CreateSlotEngine(const GameConfig &config) {
  return std::make_unique<SlotEngineImpl>(config);
}

} // namespace SlotEngine
