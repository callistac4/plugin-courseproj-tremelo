#pragma once

namespace tremolo {
    class CustomSlider : public juce::Slider {
        void paint (juce::Graphics& g) override {
            auto sliderPos = (float) valueToProportionOfLength(getValue());
            jassert(sliderPos >= 0.0f && sliderPos <= 1.0f);

            const auto rotaryParams = getRotaryParameters();
            const auto rotaryStartAngle = rotaryParams.startAngleRadians;
            const auto rotaryEndAngle = rotaryParams.endAngleRadians;

            auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

            auto bounds = getLocalBounds().toFloat().reduced(12.0f);
            auto size = juce::jmin(bounds.getWidth(), bounds.getHeight());
            auto squareBounds = bounds.withSizeKeepingCentre(size, size);
            juce::Path backgroundPie;
            backgroundPie.addPieSegment(squareBounds, rotaryStartAngle, rotaryEndAngle, 0.3f);

            auto pieGradient = juce::ColourGradient::vertical(juce::Colour{0xFFFEDF4},
                juce::Colour{0xFFF8EDFF}, bounds);
            pieGradient.addColour(0.4f, juce::Colour{0xFFFFEDFD});
            pieGradient.isRadial = true;
            pieGradient.multiplyOpacity(0.3f);
            g.setGradientFill(pieGradient);
            g.fillPath(backgroundPie);


            if (isEnabled())
            {
                juce::Path valueArc;
                juce::Path pie;
                valueArc.addArc(squareBounds.getX(), squareBounds.getY(),
                    squareBounds.getWidth(), squareBounds.getHeight(),
                    rotaryStartAngle, toAngle, true);

                pie.addPieSegment(squareBounds, rotaryStartAngle, toAngle, 0);
                pieGradient.multiplyOpacity(0.5f);
                g.setGradientFill(pieGradient);
                g.fillPath(pie);

                g.setColour (juce::Colours::lavenderblush);
                g.strokePath(valueArc, juce::PathStrokeType(6.f));

            }
        }
    };
}