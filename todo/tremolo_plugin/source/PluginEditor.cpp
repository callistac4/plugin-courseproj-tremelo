namespace tremolo {
    // pass address of the processor instance to the AudioProcessorEditor parent class
PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p) {

    // pass image data to the background and logo
    background.setImage(juce::ImageCache::getFromMemory(
      assets::Background_png, assets::Background_pngSize));
    logo.setImage(
      juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));
    juce::Path sine;


    // establish parent-child relationships to ensure these are displayed
  addAndMakeVisible(background);
  addAndMakeVisible(logo);
  addAndMakeVisible(lfoVisualizer);


  // before the constructor has finished,  set the editor's size
  setSize(540, 270);
}

// call whenever a components size is changed so that we know where to position child components
void PluginEditor::resized() {

  const auto bounds = getLocalBounds();
  // DBG("x: " << bounds.getX() << " y: " << bounds.getY() << "width: " << bounds.getWidth() << " height: " << bounds.getHeight());
  DBG(bounds.toString());

  background.setBounds(bounds); // match editor size

  logo.setBounds({16, 16, 105, 24}); // manually set size in logical pixels
  lfoVisualizer.setBounds({18, 149, 504, 92});
  lfoVisualizer.resized();



}
}  // namespace tremolo
