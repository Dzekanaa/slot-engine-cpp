#pragma once
#include "game_config.h"
#include "spin_result.h"
#include <memory>

namespace SlotEngine {

class ISlotEngine {
public:
  virtual ~ISlotEngine() = default;
  virtual SpinResult Spin() = 0;
  virtual const GameConfig &GetConfig() const = 0;
  virtual void SetConfig(const GameConfig &config) = 0;
  virtual void Reset() = 0;
};

class SlotEngineImpl : public ISlotEngine {
public:
  explicit SlotEngineImpl(const GameConfig &config);
  ~SlotEngineImpl();

  SpinResult Spin() override;
  const GameConfig &GetConfig() const override;
  void SetConfig(const GameConfig &config) override;
  void Reset() override;

private:
  struct Impl;
  std::unique_ptr<Impl> pImpl;
};

// Factory funkcija
std::unique_ptr<ISlotEngine>
CreateSlotEngine(const GameConfig &config = GameConfig());

} // namespace SlotEngine
