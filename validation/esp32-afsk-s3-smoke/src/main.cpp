#include <Arduino.h>
#include <AfskDemodulator.h>
#include <AfskModulator.h>

namespace {
volatile size_t received_frames = 0;
volatile size_t generated_samples = 0;

void on_packet(const uint8_t *frame, size_t length) {
  (void)frame;
  if (length > 0) {
    ++received_frames;
  }
}

void on_tx_samples(const float *samples, size_t count) {
  (void)samples;
  generated_samples += count;
}

AfskDemodulator demodulator(48000, 2, on_packet);
AfskModulator modulator(48000, on_tx_samples);
}  // namespace

void setup() {
  Serial.begin(115200);

  // Compile-time/API smoke exercise only. No GPIO, PTT or RF is touched.
  int16_t silence[32] = {};
  demodulator.processSamples(silence, 32);
  demodulator.flush();

  const uint8_t frame[] = {0x82, 0xA0, 0xA4, 0xA6};
  float scratch[256] = {};
  modulator.modulate(frame, sizeof(frame), scratch, 256);
}

void loop() {
  delay(1000);
}
