#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_audio_utils/juce_audio_utils.h>

using juce::WebBrowserComponent;
using Options = WebBrowserComponent::Options;

static Options getOptions()
{
    return Options()
        .withBackend(Options::Backend::webview2)
        .withNativeIntegrationEnabled();
}

struct Editor : juce::AudioProcessorEditor
{
    Editor(juce::AudioProcessor& processorToUse)
        : AudioProcessorEditor(processorToUse)
    {
        addAndMakeVisible(browser);
        browser.goToURL("https://www.google.com");
        setResizable(true, true);
        setSize(400, 400);
    }

    void resized() override { browser.setBounds(getLocalBounds()); }
    WebBrowserComponent browser {getOptions()};
};