#pragma once

#include "Resources.h"

using juce::WebBrowserComponent;
using Options = WebBrowserComponent::Options;


static std::optional<WebBrowserComponent::Resource> getResource(const juce::String& name)
{
    if (name == "/")
        return getWebResource("index.html", "text/html");

    return {};
}

static Options::WinWebView2 getWinOptions()
{
    using juce::File;
    auto tempDir = File::getSpecialLocation(File::tempDirectory);

    return Options::WinWebView2().withUserDataFolder(tempDir);
}

static Options getOptions()
{
    return Options()
        .withBackend(Options::Backend::webview2)
        .withNativeIntegrationEnabled()
        .withResourceProvider(getResource)
        .withWinWebView2Options(getWinOptions());
}

struct WebEditor : WebBrowserComponent
{
    WebEditor()
        : WebBrowserComponent(getOptions())
    {
        evaluateJavascript("console.log('hello');");
        emitEventIfBrowserIsVisible("hey", "hello");
        goToURL(getResourceProviderRoot());
    }
};

struct Editor : juce::AudioProcessorEditor
{
    Editor(juce::AudioProcessor& processorToUse)
        :AudioProcessorEditor(processorToUse)
    {
        addAndMakeVisible(browser);
        setResizable(true, true);
        setSize(400, 400);
    }

    void resized() override { browser.setBounds(getLocalBounds()); }

    WebEditor browser;
};
