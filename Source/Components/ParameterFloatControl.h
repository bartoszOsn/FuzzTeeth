#pragma once

#include <JuceHeader.h>

///<summary>Component for controling value of AudioParameterFloat</summary>
class ParameterFloatControl  : public juce::Component
{
public:
    ParameterFloatControl(juce::RangedAudioParameter*);
    ~ParameterFloatControl() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	juce::Slider slider;
	juce::SliderParameterAttachment attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterFloatControl)
};
