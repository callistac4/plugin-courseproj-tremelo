namespace tremolo {
    namespace {
        struct SerializableParameters {
            float rate;
            float gain;
            bool bypass;
            juce::String waveform;
            float modulationDepth;

            static constexpr auto marshallingVersion = 1;

            template <typename Archive, typename T>
            static void serialise(Archive& archive, T& t) {
               using namespace juce;

                if (archive.getVersion() != 1) { return; }

                std::string pluginName = TREMOLO_PLUGIN_NAME;
                archive(named("pluginName", pluginName));

                if (pluginName != TREMOLO_PLUGIN_NAME) { return; }

                archive(named("modulationRateHz", t.rate), named("bypassed", t.bypass),
                    named("modulationWaveform", t.waveform), named("gain", t.gain),
                    named("modulationDepth", t.modulationDepth));

            }
        };
        SerializableParameters from(const tremolo::Parameters& parameters) {
            return {
                .rate = parameters.rate.get(),
                .gain = parameters.gain.get(),
                .bypass = parameters.bypassed.get(),
                .waveform = parameters.waveform.getCurrentChoiceName(),
                .modulationDepth = parameters.modulationDepth.get(),
            };
        }
    }

void JsonSerializer::serialize(const Parameters& parameters, juce::OutputStream& output) {
        const auto parametersToSerialize = from(parameters);
        const auto json = juce::ToVar::convert(parametersToSerialize);
        if (!json.has_value()) { return; }
        juce::JSON::writeToStream(output, *json,
            juce::JSON::FormatOptions{}.withSpacing(juce::JSON::Spacing::multiLine).withMaxDecimalPlaces(2));
}

juce::Result JsonSerializer::deserialize(juce::InputStream& input, Parameters& parameters) {
        juce::var parsedResult;
        const auto result = juce::JSON::parse(input.readEntireStreamAsString(), parsedResult);
        if (result.failed()) { return result; }

        const auto parsedParameters = juce::FromVar::convert<SerializableParameters>(parsedResult);
        if (!parsedParameters.has_value()) {
            return juce::Result::fail("failed to parse parameters from JSON representation");
        }

        // check if inputs is valid
        const auto modulationWaveformIndex = parameters.waveform.choices.indexOf(parsedParameters->waveform);
        if (modulationWaveformIndex < 0) {
            return juce::Result::fail("failed to find waveform index in JSON representation" +
                parameters.waveform.choices.joinIntoString(", "));
        }
        parameters.waveform = modulationWaveformIndex;
        parameters.rate = parsedParameters->rate;
        parameters.bypassed = parsedParameters->bypass;
        parameters.gain = parsedParameters->gain;
        parameters.modulationDepth = parsedParameters->modulationDepth;

        return juce::Result::ok();
}
}  // namespace tremolo
