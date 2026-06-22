# Slot Engine

A high‑performance, thread‑safe slot machine engine written in C++17. It handles reel spinning, symbol matching, Wild and Scatter evaluation, and Free Spins. Designed to be used as a standalone library or as a Git submodule in larger projects (e.g., Monte Carlo RTP simulators).

---

## Features

- **Configurable reels** – each reel can have a custom symbol strip.
- **Flexible paylines** – supports 10, 20 or 40 lines, with arbitrary row patterns.
- **Symbol types**:
  - Standard symbols (`A`, `K`, `Q`, `J`, `10`, `9`, `8`, `7`, `6`, `5`)
  - **Wild** – substitutes any standard symbol to complete winning combinations.
  - **Scatter** – pays anywhere on the screen (not tied to paylines) and can trigger Free Spins.
- **Free Spins** – triggered by 3+ Scatter symbols; winnings during free spins are multiplied.
- **PayTable** – define payout values for 3, 4 or 5 matching symbols.
- **Thread‑safe `SpinEngine`** – performs stateless spins; ideal for parallel simulations.
- **High‑level `SlotEngine`** – manages RNG and configuration, offers a simple `Spin()` API.
- **Namespace isolation** – all symbols and classes are inside `namespace SlotEngine`.

---

## Requirements

- C++17 compiler (GCC 7+, Clang 6+, MSVC 2017+)
- CMake 3.16 or higher
- No external dependencies (only the C++ standard library)

---

## Building

```bash
git clone https://github.com/Dzekanaa/slot-engine.git
cd slot-engine
mkdir build && cd build
cmake ..
make -j$(nproc)
```

This builds the static library `libslot_engine.a` and optionally the test executable `slot_engine_tests` (if `BUILD_TESTS` is ON).

---

## Usage

### As a standalone library

```cpp
#include <slot_engine.h>

using namespace SlotEngine;

int main() {
    // Create a default configuration (20 paylines, classic reels)
    GameConfig config = GameConfig::CreateClassicConfig();
    
    // Create the engine
    auto engine = CreateSlotEngine(config);
    
    // Perform one spin
    SpinResult result = engine->Spin();
    
    std::cout << "Total win: " << result.totalWin << "\n";
    std::cout << "Base game win: " << result.baseGameWin << "\n";
    std::cout << "Scatter win: " << result.scatterWin << "\n";
    if (result.triggeredFreeSpins)
        std::cout << "Free spins triggered! (" << result.freeSpinsAwarded << " spins)\n";
    
    return 0;
}
```

### Custom configuration

```cpp
GameConfig config(20);  // 20 paylines

// Set custom reels
std::vector<Symbol> reelStrip = {
    Symbol::A, Symbol::K, Symbol::Q, Symbol::J, Symbol::Ten,
    Symbol::Nine, Symbol::Eight, Symbol::Seven, Symbol::Six,
    Symbol::Five, Symbol::Wild
};
config.reels = {
    Reel(reelStrip), Reel(reelStrip), Reel(reelStrip),
    Reel(reelStrip), Reel(reelStrip)
};

// Custom paytable
config.paytable.SetPayout(Symbol::A, 50, 200, 1000);
config.paytable.SetPayout(Symbol::K, 30, 150, 750);
config.paytable.SetPayout(Symbol::Scatter, 10, 50, 250);

auto engine = CreateSlotEngine(config);
```

### Using as a submodule

In your parent project’s `CMakeLists.txt`:

```cmake
add_subdirectory(slot-engine)
target_link_libraries(your_app PRIVATE slot_engine)
target_include_directories(your_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/slot-engine/include)
```

Then include with `#include <slot_engine.h>`.

---

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────┐
│                       SlotEngine                            │
│  - Owns RNG (std::mt19937)                                 │
│  - Manages GameConfig                                      │
│  - Provides Spin()                                         │
└───────────────────────────┬─────────────────────────────────┘
                            │ delegates
┌───────────────────────────▼─────────────────────────────────┐
│                       SpinEngine                            │
│  - Stateless, thread‑safe                                  │
│  - Takes an RNG reference                                  │
│  - Performs the actual spin logic                          │
└───────────────────────────┬─────────────────────────────────┘
                            │ uses
┌───────────────────────────▼─────────────────────────────────┐
│                       WinEvaluator                          │
│  - Evaluates paylines                                      │
│  - Handles Wild substitution                               │
│  - Counts Scatter symbols across the screen                │
│  - Returns WinningLine list                                │
└─────────────────────────────────────────────────────────────┘
```

### Key Classes

| Class          | Purpose |
|----------------|---------|
| `Symbol`       | Enum of all possible symbols (including `Wild` and `Scatter`). |
| `Reel`         | Represents a reel strip; provides `GetSymbol(index)`. |
| `Payline`      | Simple vector of row indices (one per reel). |
| `PayTable`     | Maps `(Symbol, count)` → payout amount. |
| `GameConfig`   | Holds reels, paylines, paytable, and flags (enable/disable features). |
| `SpinEngine`   | Core logic: generate random symbols, evaluate wins, handle free spins. |
| `SlotEngine`   | High‑level API with internal RNG and state management. |
| `WinEvaluator` | Static methods that evaluate a `Screen` against the config. |
| `SpinResult`   | Contains total win, breakdown (base/scatter/bonus), and free‑spin info. |

---

## How Wild and Scatter Work

- **Wild** (`Symbol::Wild`)  
  - Substitutes for any standard symbol on a payline.  
  - Does not have its own payout – it only helps complete combinations.  
  - If all symbols on a payline are Wild, no payout is awarded (no base symbol).

- **Scatter** (`Symbol::Scatter`)  
  - Pays **regardless of position** – the total number of Scatters on the entire visible screen is counted.  
  - Payouts are defined in the PayTable for 3, 4 or 5 Scatters.  
  - If `enableFreeSpins` is `true`, 3+ Scatters also trigger Free Spins (10 for 3, 15 for 4, 20 for 5).  
  - Scatter symbols are **ignored** in regular payline evaluation.

- **Free Spins**  
  - Activated by Scatters.  
  - During Free Spins, all wins are multiplied by 2.  
  - Free spins **do not** retrigger additional free spins (prevents infinite loops).  
  - Winnings from Free Spins are accumulated in `SpinResult::bonusWin`.

---

## Configuration Presets

The `GameConfig` class provides factory methods:

- `CreateClassicConfig()` – classic 5‑reel setup with balanced payouts.
- `CreateHighVolatilityConfig()` – higher payouts for rare symbols, lower for common ones.
- `CreateLowVolatilityConfig()` – narrower payout differences.

You can also build your own config by modifying the `reels`, `paylines`, and `paytable` members directly.

---

## Thread Safety

- `SpinEngine::PerformSpin(std::mt19937&)` is thread‑safe **as long as each thread uses its own RNG instance**.
- `SlotEngine::Spin()` is **not** thread‑safe (internal RNG is shared). For parallel simulations, instantiate one `SlotEngine` per thread or use `SpinEngine` directly with thread‑local RNGs.

---

## Testing

Run the built‑in test executable:

```bash
./slot_engine_tests
```

It verifies:
- Reel rotation and symbol retrieval
- Payline evaluation with and without Wilds
- Scatter counting and free‑spin triggering
- Paytable lookups

---

## License

This project is provided for educational purposes. Use it freely in your own projects.

---

## Repository

[https://github.com/Dzekanaa/slot-engine](https://github.com/Dzekanaa/slot-engine)
