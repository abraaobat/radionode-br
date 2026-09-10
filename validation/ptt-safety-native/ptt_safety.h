#pragma once

#include <cstdint>

namespace radionode {

enum class PttState : std::uint8_t {
  Idle,
  Keyed,
  FaultLatched,
};

// Platform-neutral PTT safety state machine.
//
// This class never drives GPIO. Firmware adapters may map `output_keyed()` to
// a physical PTT output only after the state transition has been accepted.
// A maximum-TX timeout always de-keys and latches a fault; an explicit
// `clear_fault()` is required before another transmission can start.
class PttSafety {
 public:
  explicit constexpr PttSafety(std::uint32_t max_tx_ms) : max_tx_ms_(max_tx_ms) {}

  constexpr bool request_key(std::uint32_t now_ms) {
    if (state_ == PttState::FaultLatched) return false;
    if (state_ == PttState::Keyed) return true;

    keyed_at_ms_ = now_ms;
    state_ = PttState::Keyed;
    return true;
  }

  constexpr void release() {
    if (state_ == PttState::Keyed) state_ = PttState::Idle;
  }

  // Returns true only when this tick caused a timeout transition.
  constexpr bool tick(std::uint32_t now_ms) {
    if (state_ != PttState::Keyed) return false;

    // Unsigned subtraction intentionally handles the normal uint32_t millis()
    // wraparound semantics used by embedded targets.
    const std::uint32_t elapsed = now_ms - keyed_at_ms_;
    if (elapsed < max_tx_ms_) return false;

    state_ = PttState::FaultLatched;
    return true;
  }

  constexpr bool clear_fault() {
    if (state_ != PttState::FaultLatched) return false;
    state_ = PttState::Idle;
    return true;
  }

  [[nodiscard]] constexpr bool output_keyed() const {
    return state_ == PttState::Keyed;
  }

  [[nodiscard]] constexpr bool fault_latched() const {
    return state_ == PttState::FaultLatched;
  }

  [[nodiscard]] constexpr PttState state() const { return state_; }
  [[nodiscard]] constexpr std::uint32_t max_tx_ms() const { return max_tx_ms_; }
  [[nodiscard]] constexpr std::uint32_t keyed_at_ms() const { return keyed_at_ms_; }

 private:
  std::uint32_t max_tx_ms_;
  std::uint32_t keyed_at_ms_ = 0;
  PttState state_ = PttState::Idle;
};

}  // namespace radionode
