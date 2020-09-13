#pragma once

#include <JuceHeader.h>

///<summary>
///This component creates knobs and checkboxes in flexbox
///</summary>
class GroupedControlsComponent  : public juce::Component
{
public:
	/// <summary>This structure holds data about slider</summary>
	struct SliderData
	{
	public:
		typedef std::function<void(float)> ChangeEvent;

		std::string name;
		std::string labelText;
		double minValue;
		double maxValue;
		double defaultValue;
		double step;
		ChangeEvent onValueChange;

		SliderData(std::string name, std::string labelText, double minValue, double maxValue, double defaultValue, ChangeEvent onValueChange, float step = 0.0f);
	};

    GroupedControlsComponent(std::string label, SliderData sliders[], int sliderCount, float size);
    ~GroupedControlsComponent() override;

    void resized() override;

private:
	juce::FlexBox flexbox;
	juce::GroupComponent group;

	int knobCount;
	juce::Slider** knobs;
	juce::Label** knobLabels;

	void initKnobs(SliderData sliders[], int sliderCount, float size);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GroupedControlsComponent)
};
