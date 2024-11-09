#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    wiimotes = wiiuse_init(maxWiiMotes);
    
    connectButton.setButtonText("Connect");
    connectButton.addListener(this);
    addAndMakeVisible(connectButton);
    
    setSize(600, 400);
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setFont(juce::FontOptions(16.0f));
    g.setColour(juce::Colours::white);
    g.drawText(juce::String(numConnected) + " controllers connected", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    connectButton.setBounds(getWidth() / 2 - 75, getHeight() / 2 - + 30, 150, 20);
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if(button == &connectButton && wiimotes)
    {
        connectButton.setButtonText("Connecting");
        
        numConnected = wiiuse_find(wiimotes, maxWiiMotes, 1);
        
        repaint();
    }
}
