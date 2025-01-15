#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <BinaryData.h>

using juce::WebBrowserComponent;
using Options = WebBrowserComponent::Options;

struct RawData
{
    const char* data = nullptr;
    int size = 0;
};

static RawData getRawResource(const juce::String& name)
{
    using namespace BinaryData;

    for (int index = 0; index < namedResourceListSize; ++index)
    {
        if (juce::String(originalFilenames[index]) == name)
        {
            RawData data;
            data.data = getNamedResource(namedResourceList[index], data.size);
            return data;
        }
    }

    return {};
}

static WebBrowserComponent::Resource getWebResource(const juce::String& name,
                                                    const juce::String& type)
{
    auto rawResource = getRawResource(name);


    WebBrowserComponent::Resource res;

    res.data.resize((size_t) rawResource.size);
    for (int index = 0; index < rawResource.size; ++index)
        res.data[(size_t)index] = static_cast<std::byte>(rawResource.data[index]);

    res.mimeType = "text/" + type;

    return res;
}
static std::optional<WebBrowserComponent::Resource> getResource(const juce::String& name)
{
    if (name == "/")
        return getWebResource("index.html", "html");

    if (name.contains("js"))
        return getWebResource("main.js", "javascript");

    return {};
}

static Options getOptions()
{
    return Options()
        .withBackend(Options::Backend::webview2)
        .withNativeIntegrationEnabled()
        .withResourceProvider(getResource);
}

struct WebEditor : WebBrowserComponent
{
    WebEditor()
        : WebBrowserComponent(getOptions())
    {
        goToURL(getResourceProviderRoot());
    }
};

struct Editor : juce::AudioProcessorEditor
{
    Editor(juce::AudioProcessor& processorToUse)
        : AudioProcessorEditor(processorToUse)
    {
        addAndMakeVisible(browser);
        setResizable(true, true);
        setSize(400, 400);
    }

    void resized() override { browser.setBounds(getLocalBounds()); }
    WebEditor browser;
};