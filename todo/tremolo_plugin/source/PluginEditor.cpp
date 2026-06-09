// #include "libs/googletest/googletest/include/gtest/internal/gtest-internal.h"

namespace tremolo {
    // pass address of the processor instance to the AudioProcessorEditor parent class
PluginEditor::PluginEditor(PluginProcessor& p) :
  AudioProcessorEditor(&p),
  waveformAttachment{p.getParameterRefs().waveform, waveformComboBox},
  rateAttachment{p.getParameterRefs().rate, rateSlider},
  depthAttachment{p.getParameterRefs().modulationDepth, depthSlider},
  bypassAttachment{p.getParameterRefs().bypassed, bypassButton},
  lookAndFeelAttachment{p.getParameterRefs().looks, lookAndFeelComboBox} {

  // pass image data to the background and logo
  background.setImage(juce::ImageCache::getFromMemory(assets::Background_png, assets::Background_pngSize));
  logo.setImage(juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));
  addAndMakeVisible(background);
  addAndMakeVisible(logo);

  // pass data to waveform combo box
  waveformComboBox.addItemList(p.getParameterRefs().waveform.choices, 1);
  waveformAttachment.sendInitialUpdate();
  addAndMakeVisible(waveformComboBox);
  addAndMakeVisible(waveformLabel);

  // pass data to bypass button
  bypassButton.onClick = [this] {
    bypassButton.setButtonText(bypassButton.getToggleState() ? "Bypassed" : "Off");
  };
  bypassButton.onClick();
  addAndMakeVisible(bypassButton);

  // pass data to modulation rate slider
  rateSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  rateSlider.setPopupDisplayEnabled(true, true, this);
  rateSlider.setTextValueSuffix(" Hz");
  addAndMakeVisible(rateSlider);
  rateLabel.setJustificationType(juce::Justification::centred);
  rateLabel.setInterceptsMouseClicks(false, false);
  addAndMakeVisible(rateLabel);

  // pass data to modulation depth slider
  depthSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
  depthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
  depthSlider.setPopupDisplayEnabled(true, true, this);
  addAndMakeVisible(depthSlider);
  depthLabel.setJustificationType(juce::Justification::centred);
  depthLabel.setInterceptsMouseClicks(false, false);
  addAndMakeVisible(depthLabel);

  // pass data to lfo visualizer and width slider
  addAndMakeVisible(lfoVisualizer);
  lfoCurveWidthSlider.setRange(0, 10, 1);
  lfoCurveWidthSlider.onValueChange = [this] {
    const auto newWidth = static_cast<float> (lfoCurveWidthSlider.getValue());
    lfoVisualizer.setStrokeWidth(newWidth);
    };
  addAndMakeVisible(lfoCurveWidthSlider);

  // pass data to look and feel combo box
  lookAndFeelComboBox.addItemList(p.getParameterRefs().looks.choices, 1);
  lookAndFeelComboBox.onChange = [this] {
    const auto selectedId = lookAndFeelComboBox.getSelectedId() - 1;

    if (selectedId >= 0 && selectedId < static_cast<int>(lookAndFeels.size())) {
    setLookAndFeel(lookAndFeels[selectedId]);
  }
  };
  lookAndFeelAttachment.sendInitialUpdate();
  addAndMakeVisible(lookAndFeelComboBox);




  // before the constructor has finished, set the editor's size
  setSize(540, 300);
}
  PluginEditor::~PluginEditor() {
  setLookAndFeel(nullptr);
}

// call whenever a components size is changed so that we know where to position child components
void PluginEditor::resized() {

  auto bounds = getLocalBounds();

  background.setBounds(0, 0, 540, 270);
  logo.setBounds({16, 16, 105, 24}); // manually set size in logical pixels

  lfoVisualizer.setBounds({18, 149, 504, 92});

  waveformComboBox.setBounds(16, 66, 132, 28);
  auto waveformLabelBounds = waveformComboBox.getBounds();
  waveformLabelBounds.setY(waveformComboBox.getY() - 22);
  waveformLabelBounds.setHeight(20);
  waveformLabel.setBounds(waveformLabelBounds);


  bypassButton.setBounds({392, 66, 132, 28});

  auto rateSliderBounds = bounds;
  rateSliderBounds.setSize(static_cast<int>(bounds.getWidth() / 3.5),
                         static_cast<int>(bounds.getHeight() / 3.5));
  rateSliderBounds.setCentre({220, 90});
  rateSlider.setBounds(rateSliderBounds);
  auto rateLabelBounds = rateSliderBounds;
  rateLabelBounds.setY(waveformComboBox.getY() - 22);
  rateLabelBounds.setHeight(20);
  rateLabel.setBounds(rateLabelBounds);

  auto depthBounds = rateSliderBounds.translated(110, 0);
  depthSlider.setBounds(depthBounds);
  auto depthLabelBounds = depthBounds;
  depthLabelBounds.setY(waveformComboBox.getY() - 22);
  depthLabelBounds.setHeight(20);
  depthLabel.setBounds(depthLabelBounds);


  lfoCurveWidthSlider.setBounds(5, 270, 270, 30);
  lookAndFeelComboBox.setBounds({275, 270, 265, 30});


}
}  // namespace tremolo
