#pragma once
#include "game_config.h"
#include "spin_result.h"
#include <memory>

namespace SlotEngine {

/**
 * @brief Abstract interface for a slot machine engine.
 *
 * Defines the core operations required for any slot engine implementation,
 * including spinning, configuration management, and reset functionality.
 */
class ISlotEngine {
public:
  virtual ~ISlotEngine() = default;

  /**
   * @brief Performs a single spin of the slot machine.
   *
   * @return Result of the spin including wins and triggered features.
   */
  virtual SpinResult Spin() = 0;

  /**
   * @brief Returns the current game configuration.
   *
   * @return Constant reference to the active GameConfig.
   */
  virtual const GameConfig &GetConfig() const = 0;

  /**
   * @brief Sets a new game configuration.
   *
   * @param config New configuration to apply.
   */
  virtual void SetConfig(const GameConfig &config) = 0;

  /**
   * @brief Resets the engine to its initial state.
   */
  virtual void Reset() = 0;
};

/**
 * @brief Concrete implementation of the slot engine.
 *
 * SlotEngineImpl provides the full implementation of ISlotEngine,
 * using the PImpl pattern to hide internal details and reduce compile-time
 * dependencies.
 */
class SlotEngineImpl : public ISlotEngine {
public:
  /**
   * @brief Constructs the slot engine with a given configuration.
   *
   * @param config Initial game configuration.
   */
  explicit SlotEngineImpl(const GameConfig &config);

  ~SlotEngineImpl();

  SpinResult Spin() override;
  const GameConfig &GetConfig() const override;
  void SetConfig(const GameConfig &config) override;
  void Reset() override;

private:
  /// @brief Private implementation (PImpl idiom).
  struct Impl;
  std::unique_ptr<Impl> pImpl;
};

/**
 * @brief Creates a slot engine instance.
 *
 * Factory function that hides the concrete implementation and returns
 * a polymorphic interface pointer.
 *
 * @param config Optional game configuration (default constructed if not
 * provided).
 * @return Unique pointer to an ISlotEngine instance.
 */
std::unique_ptr<ISlotEngine>
CreateSlotEngine(const GameConfig &config = GameConfig());

} // namespace SlotEngine
