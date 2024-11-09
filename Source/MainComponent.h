#pragma once

#include <JuceHeader.h>
#include "wiiuse.h"

//==============================================================================
class MainComponent  : public juce::Component,
                       public juce::Button::Listener
{
public:
    MainComponent();
    ~MainComponent() override {};

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void buttonClicked(juce::Button* button) override;
    
    static constexpr int maxWiiMotes = 4;
    wiimote** wiimotes = nullptr;
    int numConnected = 0;
    
    juce::TextButton connectButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
