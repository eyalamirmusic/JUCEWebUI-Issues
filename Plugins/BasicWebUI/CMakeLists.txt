project(BasicWebUI VERSION 0.0.1)

set (BaseTargetName BasicWebUI)

juce_add_plugin("${BaseTargetName}"
        COMPANY_NAME "TestWebUI"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS FALSE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_MANUFACTURER_CODE TWui
        PLUGIN_CODE Wbui
        FORMATS AU VST3 Standalone
        PRODUCT_NAME "Basic Web UI"
        NEEDS_WEBVIEW2 TRUE)

target_sources(${BaseTargetName} PRIVATE Processor.cpp)

target_compile_definitions(${BaseTargetName}
        PUBLIC
        JUCE_WEB_BROWSER=1
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_USE_WIN_WEBVIEW2_WITH_STATIC_LINKING=1)

juce_add_binary_data(${BaseTargetName}_Binaries SOURCES
        JS/index.html)

target_link_libraries(${BaseTargetName} PRIVATE
        shared_plugin_helpers
        juce_audio_utils
        juce_gui_extra
        ${BaseTargetName}_Binaries
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags)
