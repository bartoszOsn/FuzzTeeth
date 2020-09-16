/*
  ==============================================================================

    ParameterFloatControl.cpp
    Created: 16 Sep 2020 7:32:35pm
    Author:  cokol

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ParameterFloatControl.h"


ParameterFloatControl::ParameterFloatControl(juce::RangedAudioParameter*)
{
}

ParameterFloatControl::~ParameterFloatControl()
{
}

void ParameterFloatControl::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("ParameterFloatControl", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void ParameterFloatControl::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
