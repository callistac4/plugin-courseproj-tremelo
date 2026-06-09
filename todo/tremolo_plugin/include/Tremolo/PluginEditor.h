#pragma once

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);
  ~PluginEditor() override;

  void resized() override;


private:
  juce::ImageComponent background;
  juce::ImageComponent logo;

  juce::ComboBox waveformComboBox;
  juce::ComboBoxParameterAttachment waveformAttachment;
  juce::Label waveformLabel{"waveform label", "Waveform"};

  CustomSlider rateSlider;
  juce::SliderParameterAttachment rateAttachment;
  juce::Label rateLabel{"rate label", "Modulation Rate"};

  CustomSlider depthSlider;
  juce::SliderParameterAttachment depthAttachment;
  juce::Label depthLabel{"depth label", "Modulation Depth"};

  juce::Slider lfoCurveWidthSlider;
  LfoVisualizer lfoVisualizer;

  juce::ToggleButton bypassButton{"BYPASSED"};
  juce::ButtonParameterAttachment bypassAttachment;

  juce::ComboBox lookAndFeelComboBox;
  juce::ComboBoxParameterAttachment lookAndFeelAttachment;

  juce::LookAndFeel_V1 lookAndFeel_V1;
  juce::LookAndFeel_V2 lookAndFeel_V2;
  juce::LookAndFeel_V3 lookAndFeel_V3;
  juce::LookAndFeel_V4 lookAndFeel_V4;
  CustomLookAndFeel lookAndFeel;

  std::array<juce::LookAndFeel*, 5> lookAndFeels {
      &lookAndFeel_V1,
      &lookAndFeel_V2,
      &lookAndFeel_V3,
      &lookAndFeel_V4,
      &lookAndFeel
  };

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
