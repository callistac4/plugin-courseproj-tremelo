#pragma once

namespace tremolo {
class Tremolo {
public:
  enum class LfoWaveform : size_t {
    sine = 0,
    triangle = 1,
  };

  static float triangle(float phase) {
    const auto ft = phase / juce::MathConstants<float>::twoPi;
    return 4.f * std::abs(ft-std::floor(ft+0.5f))-1.f;
  }


  Tremolo() {
    for (auto& lfo : lfos) {
      lfo.setFrequency(5.f, true); // 5 Hz, allow frequency to change immediately
    }
  }

  void prepare(double sampleRate, int expectedMaxFramesPerBlock) {
    const juce::dsp::ProcessSpec processSpec {
      .sampleRate = sampleRate,
      .maximumBlockSize = static_cast<juce::uint32>(expectedMaxFramesPerBlock),
      .numChannels = 1u,
    };
    for (auto& lfo : lfos) {
      lfo.prepare(processSpec);
    }
  }

  void setLfoWaveform(LfoWaveform waveform) { //switch LFO shape
    jassert(waveform == LfoWaveform::sine || waveform == LfoWaveform::triangle);
    lfoToSet = waveform;
  }

  void setModulationRate(float rateHz) {
    for (auto& lfo : lfos) {
      lfo.setFrequency(rateHz);
    }
  }

  void setModulationDepth(float newModulationDepth) {
    modulationDepth = juce::jlimit(0.0f, 1.0f, newModulationDepth);
  }


  void process(juce::AudioBuffer<float>& buffer) noexcept {
    updateLfoWaveform(); // implement setLfoWaveform between process blocks
    // frame-wise processing
    for (const auto frameIndex : std::views::iota(0, buffer.getNumSamples())) {
      const auto lfoValue = getNextLfoValue(); //generate LFO value
      const auto modulationValue = (modulationDepth * lfoValue) + 1.f;

      // for each channel sample in the frame (channel index) currently being processed
      for (const auto channelIndex :
           std::views::iota(0, buffer.getNumChannels())) {
        // get the input sample
        const auto inputSample = buffer.getSample(channelIndex, frameIndex);

        // modulate the sample by the modulation value
        const auto outputSample = inputSample * modulationValue;

        // set the output sample
        buffer.setSample(channelIndex, frameIndex, outputSample);
      }

    }
  }

  void reset() noexcept {
    for (auto& lfo : lfos) {
      lfo.reset();
    }
  }

private:

  float getNextLfoValue() {
    return lfos[juce::toUnderlyingType(currentLfo)].processSample(0.f);
  }
  float modulationDepth = 0.4f;

  std::array<juce::dsp::Oscillator<float>, 2u> lfos {
    juce::dsp::Oscillator<float>{[](auto phase) {return std::sin(phase);}},
    juce::dsp::Oscillator<float>{triangle},
    };

  void updateLfoWaveform() {  // implement LFO waveform change, call at the beginning of procces function
    if (currentLfo != lfoToSet) {
      currentLfo = lfoToSet;
    }
  }

  LfoWaveform currentLfo = LfoWaveform::sine; // currently active oscillator, default to sine
  LfoWaveform lfoToSet = currentLfo;
};
}  // namespace tremolo
