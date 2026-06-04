
namespace tremolo {
  // create modulation rate parameter
  namespace {
    auto& addParameterToProcessor(juce::AudioProcessor& processor, auto parameter) {
      auto& result = *parameter;                        // dereferences the pointer and stores a reference to the actual parameter object
      processor.addParameter(parameter.release());      // gives ownership of parameter to the JUCE processor
      return result;                                    // returns a reference to the parameter
    }

    juce::AudioParameterFloat& createModulationRateParameter(juce::AudioProcessor& processor) {
      constexpr auto versionHint = 1;
      return addParameterToProcessor(processor, std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"modulation.rate", versionHint},
        "Modulation rate",
        juce::NormalisableRange<float>{0.1f, 20.f, 0.01f, 0.4f},
        5.f,
        juce::AudioParameterFloatAttributes{}.withLabel("Hz")));
    }
    // create gain parameter
    juce::AudioParameterFloat& createGainParameter(juce::AudioProcessor& processor) {
        constexpr auto versionHint = 1;
        return addParameterToProcessor(processor, std::make_unique<juce::AudioParameterFloat>(
          juce::ParameterID{"gain", versionHint},
          "Gain",
          juce::NormalisableRange<float>{-12.f, 12.f, 0.01f, 1.f},
          0.f,
          juce::AudioParameterFloatAttributes{}.withLabel("dB")
          .withStringFromValueFunction([](float value, int) {
            return juce::String(value, 1);})
          ));
      }
    // create bypass parameter
    juce::AudioParameterBool& createBypassParameter(juce::AudioProcessor& processor) {
      constexpr auto versionHint = 1;
      return addParameterToProcessor(processor, std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{"bypassed", versionHint}, "Bypass", false));
    }
    //create waveform parameter
    juce::AudioParameterChoice& createWaveformParameter(juce::AudioProcessor& processor) {
      constexpr auto versionHint = 1;
      return addParameterToProcessor(processor, std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{"waveform", versionHint},
        "Modulation Waveform",
        juce::StringArray{"Sine", "Triangle"},
        0));
    }
    }

  Parameters::Parameters(juce::AudioProcessor &processor) // constructor using a member initializer list
    : gain{createGainParameter(processor)},
      rate{createModulationRateParameter(processor)},
      bypassed{createBypassParameter(processor)},
      waveform{createWaveformParameter(processor)} {}
}  // namespace tremolo
