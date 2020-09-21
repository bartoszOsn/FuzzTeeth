#include "ParameterFloatControl.h"

///<summary>Constructor</summary>
///<param name="parameter">Pointer to parameter that will be atatched to slider in this component.</param>
ParameterFloatControl::ParameterFloatControl(juce::RangedAudioParameter* parameter)
	: slider(juce::Slider::RotaryHorizontalVerticalDrag, juce::Slider::NoTextBox),
	attachment(*parameter, slider)
{
	this->parameter = parameter;
	
	slider.addListener(this);
	slider.setNumDecimalPlacesToDisplay(0);
	slider.setTextValueSuffix(" " + parameter->label);
	addAndMakeVisible(slider);

	setTooltip(parameter->getName(100));
}

///<summary>Renders parameter label and value.</summary>
void ParameterFloatControl::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
	g.drawFittedText(parameter->getName(100), getLocalBounds().toFloat().getProportion(juce::Rectangle<float>(0.5f, 0.0f, 0.5f, 0.75f)).toNearestInt(),
		juce::Justification::topLeft, 3, 1.0f);
	
	g.setFont(11.0f);
	g.drawText (getValueText(), getLocalBounds().toFloat().getProportion(juce::Rectangle<float>(0.5f, 0.5f, 0.5f, 0.5f)),
                juce::Justification::centredLeft, true);
}

///<summary>Called by JUCE when this component is resized.</summary>
void ParameterFloatControl::resized()
{
	slider.setBoundsRelative(0.0f, 0.0f, 0.5f, 1.0f);
}

///<summary>Callback registered to Slider which is invoked when value of slider changed.</summary>
void ParameterFloatControl::sliderValueChanged(juce::Slider* slider)
{
	repaint();
}

///<summary>Returns text which will be displayed next to slider, as its current value.</summary>
juce::String ParameterFloatControl::getValueText()
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << slider.getValue() << " " << parameter->getLabel();
	return stream.str();
}
