#pragma once

#include <JuceHeader.h>

///<summary>Component for controling value of AudioParameterFloat</summary>
class ParameterFloatControl  : public juce::Component
{
public:
    ParameterFloatControl(juce::RangedAudioParameter*);

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	///<summary>Parameter that slider from that component is attached to.</summary>
	juce::RangedAudioParameter* parameter;
	///<summary>Slider that has parameter attached to it.</summary>
	juce::Slider slider;
	///<summary>Object which attaches parameter to slider</summary>
	juce::SliderParameterAttachment attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterFloatControl)
};
