#pragma once

namespace tremolo {
struct Parameters { // create parameter, add it to processor, store reference in "gain/rate/bypass/etc."
  explicit Parameters(juce::AudioProcessor&);

  juce::AudioParameterFloat& gain;
  juce::AudioParameterFloat& rate;
  juce::AudioParameterBool& bypassed;
  juce::AudioParameterChoice& waveform;
  juce::AudioParameterFloat& modulationDepth;
  juce::AudioParameterChoice& looks;

  // avoid accidental copies (dangling references) by using declare noncopyable below
  JUCE_DECLARE_NON_COPYABLE(Parameters)
  JUCE_DECLARE_NON_MOVEABLE(Parameters)

};
}  // namespace tremolo
