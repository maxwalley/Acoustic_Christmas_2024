/*
  ==============================================================================

    AcousticChristmas2024App.h
    Created: 2 Nov 2024 12:38:46pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VideoProcessor.h"

//==============================================================================
class AcousticChristmas2024App  : public juce::JUCEApplication
{
public:
    AcousticChristmas2024App() {}
    ~AcousticChristmas2024App() override {}

    const juce::String getApplicationName() override;
    const juce::String getApplicationVersion() override;
    
    bool moreThanOneInstanceAllowed() override;

    void initialise(const juce::String& commandLine) override;
    void shutdown() override;
    void systemRequestedQuit() override;

private:
    std::unique_ptr<VideoProcessor> videoMan;
};
