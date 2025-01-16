#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <BinaryData.h>

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

static juce::WebBrowserComponent::Resource getWebResource(const juce::String& name,
                                                    const juce::String& type)
{
    auto rawResource = getRawResource(name);

    juce::WebBrowserComponent::Resource res;

    res.data.resize((size_t) rawResource.size);
    for (int index = 0; index < rawResource.size; ++index)
        res.data[(size_t) index] = static_cast<std::byte>(rawResource.data[index]);

    res.mimeType = type;

    return res;
}
