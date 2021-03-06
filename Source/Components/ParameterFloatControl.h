#pragma once

#include <sstream>
#include <JuceHeader.h>


///<summary>Component for controling value of AudioParameterFloat</summary>
class ParameterFloatControl  : public juce::Component, juce::Slider::Listener, juce::SettableTooltipClient
{
public:
    ParameterFloatControl(juce::RangedAudioParameter*);

    void paint (juce::Graphics&) override;
    void resized() override;

	void sliderValueChanged(juce::Slider* slider) override;

private:
	///<summary>Parameter that slider from that component is attached to.</summary>
	juce::RangedAudioParameter* parameter;
	///<summary>Slider that has parameter attached to it.</summary>
	juce::Slider slider;
	///<summary>Object which attaches parameter to slider</summary>
	juce::SliderParameterAttachment attachment;

	juce::String getValueText();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterFloatControl)
};
