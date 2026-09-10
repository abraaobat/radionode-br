#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>

#include "ptt_safety.h"

using radionode::PttSafety;
using radionode::PttState;

void test_normal_key_and_release() {
  PttSafety ptt(30'000);
  assert(ptt.state() == PttState::Idle);
  assert(ptt.request_key(1'000));
  assert(ptt.output_keyed());
  assert(!ptt.tick(30'999));
  ptt.release();
  assert(!ptt.output_keyed());
  assert(ptt.state() == PttState::Idle);
}

void test_timeout_dekeys_and_latches_fault() {
  PttSafety ptt(10'000);
  assert(ptt.request_key(5'000));
  assert(!ptt.tick(14'999));
  assert(ptt.tick(15'000));
  assert(!ptt.output_keyed());
  assert(ptt.fault_latched());
  assert(!ptt.request_key(15'001));

  assert(ptt.clear_fault());
  assert(ptt.state() == PttState::Idle);
  assert(ptt.request_key(16'000));
  assert(ptt.output_keyed());
}

void test_release_does_not_clear_latched_fault() {
  PttSafety ptt(1'000);
  assert(ptt.request_key(0));
  assert(ptt.tick(1'000));
  ptt.release();
  assert(ptt.fault_latched());
}

void test_repeated_key_is_idempotent() {
  PttSafety ptt(5'000);
  assert(ptt.request_key(100));
  assert(ptt.request_key(4'000));
  // A repeated request must not reset the original timeout window.
  assert(ptt.tick(5'100));
  assert(ptt.fault_latched());
}

void test_millis_wraparound() {
  PttSafety ptt(1'000);
  const std::uint32_t near_wrap = std::numeric_limits<std::uint32_t>::max() - 499;
  assert(ptt.request_key(near_wrap));
  assert(!ptt.tick(499));
  assert(ptt.tick(500));
  assert(ptt.fault_latched());
}

int main() {
  test_normal_key_and_release();
  test_timeout_dekeys_and_latches_fault();
  test_release_does_not_clear_latched_fault();
  test_repeated_key_is_idempotent();
  test_millis_wraparound();
  std::cout << "PTT fail-safe native tests: PASS\n";
  return 0;
}
