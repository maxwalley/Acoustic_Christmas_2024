/*
  ==============================================================================

    AcousticChristmas2024App.cpp
    Created: 2 Nov 2024 12:38:46pm
    Author:  Max Walley

  ==============================================================================
*/

#include "AcousticChristmas2024App.h"

//==============================================================================
const juce::String AcousticChristmas2024App::getApplicationName()
{        
    return "Acoustic Christmas 2024";
}
    
const juce::String AcousticChristmas2024App::getApplicationVersion()
{
    return ProjectInfo::versionString;
}
    
bool AcousticChristmas2024App::moreThanOneInstanceAllowed()
{
    return true;
}

void AcousticChristmas2024App::initialise(const juce::String& commandLine)
{
    videoMan = std::make_unique<VideoProcessor>();
}

void AcousticChristmas2024App::shutdown()
{
    videoMan.reset();
}

void AcousticChristmas2024App::systemRequestedQuit()
{
    quit();
}
