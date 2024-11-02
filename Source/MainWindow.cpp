/*
  ==============================================================================

    MainWindow.cpp
    Created: 2 Nov 2024 12:48:59pm
    Author:  Max Walley

  ==============================================================================
*/

#include "MainWindow.h"

//==============================================================================
MainWindow::MainWindow(juce::String name)  : juce::DocumentWindow(name, juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId), DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);
    setVisible (true);
}

void MainWindow::closeButtonPressed()
{
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}
