/*
  ==============================================================================

    ParameterFloatControl.cpp
    Created: 16 Sep 2020 7:32:35pm
    Author:  cokol

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ParameterFloatControl.h"

///<summary>Constructor</summary>
///<param name="parameter">Pointer to parameter that will be atatched to slider in this component.</param>
ParameterFloatControl::ParameterFloatControl(juce::RangedAudioParameter* parameter)
	: slider(juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox),
	attachment(*parameter, slider)
{
	this->parameter = parameter;
}

///<summary>Renders parameter label and value.<summary>
void ParameterFloatControl::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
	g.drawText(parameter->getName(100), getLocalBounds().toFloat().getProportion(juce::Rectangle<float>(0.5f, 0.0f, 0.5f, 0.5f)),
		juce::Justification::topLeft, true);
	
	g.setFont(11.0f);
	g.drawText (slider.getTextFromValue(slider.getValue()), getLocalBounds().toFloat().getProportion(juce::Rectangle<float>(0.5f, 0.5f, 0.5f, 0.5f)),
                juce::Justification::topLeft, true);
}

///<summary>Called by JUCE when this component is resized.</summary>
void ParameterFloatControl::resized()
{
	slider.setBoundsRelative(0.0f, 0.0f, 0.5f, 1.0f);
}
