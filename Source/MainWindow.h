/*
  ==============================================================================

    MainWindow.h
    Created: 2 Nov 2024 12:48:59pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
class MainWindow  : public juce::DocumentWindow
{
public:
    MainWindow(juce::String name);
    ~MainWindow() override {}
    
    void closeButtonPressed() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};
