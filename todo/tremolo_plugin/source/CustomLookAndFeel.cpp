namespace tremolo {
    namespace {
        void drawIt(juce::Graphics& g, juce::ColourGradient buttonGradient,
            const float opacity, const juce::Rectangle<int> bounds, const float cornerSize) {
            buttonGradient.multiplyOpacity(opacity);
            g.setGradientFill(buttonGradient);
            g.fillRoundedRectangle(bounds.toFloat(), cornerSize);
        }
    }



    void CustomLookAndFeel::drawToggleButton(juce::Graphics& g, juce::ToggleButton& button,
        bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) {

        const auto backgroundBounds = button.getLocalBounds().reduced(2);
        const auto bounds = backgroundBounds.reduced(2);

        auto backgroundButtonGradient = juce::ColourGradient::vertical(juce::Colour{0xFF22232C},
            juce::Colour{0xFF263235}, backgroundBounds);
        backgroundButtonGradient.addColour(0.3f, juce::Colour{0xFF303538});
        drawIt(g, backgroundButtonGradient, 1.0f, backgroundBounds, 6.f);

        float opacity = 1.0f;
        if (shouldDrawButtonAsHighlighted) {opacity = 0.7f;};

        if (button.getToggleState()) {
            auto buttonGradient = juce::ColourGradient::vertical(juce::Colour{0xFFFF901A},
                juce::Colour{0xFFFFC300}, bounds);
            drawIt(g, buttonGradient, opacity, bounds, 4.f);
            g.setColour(juce::Colour{0xFF501A0B});
        }
        else {
            auto buttonGradient = juce::ColourGradient::vertical(juce::Colour{0xFF4A7090},
                juce::Colour{0xFF324258}, bounds);
            buttonGradient.addColour(0.73, juce::Colour{0xFF315160});
            drawIt(g, buttonGradient, opacity, bounds, 4.f);
            g.setColour(juce::Colour{0xFFDDECFF});
        }

        g.drawText(button.getButtonText(), bounds, juce::Justification::centred, false);

    }

}  // namespace tremolo
