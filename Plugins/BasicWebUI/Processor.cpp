#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include "Editor.h"

class WebUIPlugin : public PluginHelpers::ProcessorBase
{
public:
    void processBlock(juce::AudioBuffer<float>& buffer,
                      juce::MidiBuffer& midiMessages) override
    {
        juce::ignoreUnused(midiMessages);
        buffer.clear();
    }

    juce::AudioProcessorEditor* createEditor() override { return new Editor(*this); }
};

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WebUIPlugin();
}
