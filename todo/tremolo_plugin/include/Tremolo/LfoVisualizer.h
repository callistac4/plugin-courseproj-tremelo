namespace tremolo {
    class LfoVisualizer : public juce::Component {
    public:
        using LfoWaveform = Tremolo::LfoWaveform;

        void setLfoWaveform(LfoWaveform waveform) { //switch LFO shape
            jassert(waveform == LfoWaveform::sine || waveform == LfoWaveform::triangle);
            if (currentLfo != waveform) {
                currentLfo = waveform;
                repaint();
            }
        }

        void paint(juce::Graphics& g) override {
            g.setColour(juce::Colours::lavenderblush);

            const auto index = juce::toUnderlyingType(currentLfo);
            g.strokePath(shapes[index], juce::PathStrokeType{strokeWidth});
        }

        void resized() override {
            for (auto& shape : shapes) {shape.clear();}

            auto& sine = shapes[juce::toUnderlyingType(LfoWaveform::sine)];
            auto& triangle = shapes[juce::toUnderlyingType(LfoWaveform::triangle)];

            const int strokeWidthInt = static_cast<int> (strokeWidth);
            const auto halfHeight = static_cast<float>(getHeight()) * 0.5f;
            const auto amplitude = halfHeight - strokeWidth/2;

            sine.startNewSubPath(0.f, halfHeight);
            triangle.startNewSubPath(0.f, halfHeight);

            for (const auto x : std::views::iota(0 - strokeWidthInt, getWidth() + strokeWidthInt)) {
                const auto xFloat = static_cast<float>(x);

                const auto sineY = std::sin(0.1f * xFloat) * amplitude + halfHeight;
                sine.lineTo(xFloat, sineY);

                const auto triY = Tremolo::triangle(0.1f * xFloat) * amplitude + halfHeight;
                triangle.lineTo(xFloat, triY);
            }
        }

        void setStrokeWidth(float newWidth) {
            newWidth = juce::jlimit(0.0f, 10.0f, newWidth);

           if (std::abs(strokeWidth - newWidth) > 0.001f) {
                strokeWidth = newWidth;
                resized();
                repaint();
            }
        }

    private:
        LfoWaveform currentLfo = LfoWaveform::sine;
        std::array<juce::Path, 2> shapes;
        float strokeWidth = 4.0f;
    };
}
