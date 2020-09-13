#include <JuceHeader.h>
#include "GroupedControlsComponent.h"

#include <iostream>

GroupedControlsComponent::SliderData::SliderData(std::string name, std::string labelText, double minValue, double maxValue, double defaultValue, ChangeEvent onValueChange, float step)
{
	this->name = name;
	this->labelText = labelText;
	this->minValue = minValue;
	this->maxValue = maxValue;
	this->defaultValue = defaultValue;
	this->onValueChange = onValueChange;
	this->step = step;
}

GroupedControlsComponent::GroupedControlsComponent(std::string label, SliderData sliders[], int sliderCount, float size)
	: flexbox(juce::FlexBox::Direction::row, juce::FlexBox::Wrap::wrap, juce::FlexBox::AlignContent::center, juce::FlexBox::AlignItems::flexStart, juce::FlexBox::JustifyContent::center),
	group("group", label)
{
	initKnobs(sliders, sliderCount, size);
	addAndMakeVisible(group);
}

GroupedControlsComponent::~GroupedControlsComponent()
{
	for (int i = 0; i < this->knobCount; i++)
	{
		delete this->knobs[i];
		delete this->knobLabels[i];
	}
	delete this->knobs;
	delete this->knobLabels;
}

///<summary>This function is called when component is resized</summary>
void GroupedControlsComponent::resized()
{
	group.setBounds(getLocalBounds());
	flexbox.performLayout(group.getLocalBounds().toFloat());
}

///<summary>This function initializes sliders</summary>
void GroupedControlsComponent::initKnobs(SliderData sliders[], int sliderCount, float size)
{
	this->knobs = new juce::Slider * [sliderCount];
	this->knobLabels = new juce::Label * [sliderCount];
	this->knobCount = sliderCount;

	for (int i = 0; i < sliderCount; i++)
	{
		juce::Label* label = new juce::Label(sliders[i].name, sliders[i].labelText);
		juce::Slider* knob = new juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag, juce::Slider::TextEntryBoxPosition::NoTextBox);

		this->knobs[i] = knob;
		this->knobLabels[i] = label;

		group.addAndMakeVisible(label);
		label->setJustificationType(juce::Justification::centred);
		label->attachToComponent(knob, false);
		auto slider = sliders[i];
		knob->setRange(slider.minValue, slider.maxValue, slider.step);
		knob->setValue(slider.defaultValue);
		knob->setDoubleClickReturnValue(true, slider.defaultValue);
		knob->setNumDecimalPlacesToDisplay(2);
		knob->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 20);
		knob->onValueChange = [knob, slider, i] {
			if (slider.onValueChange != nullptr)
			{
				std::cout << &(slider);
				slider.onValueChange(knob->getValue());
				
			}
		};
		group.addAndMakeVisible(knob);

		flexbox.items.add(juce::FlexItem(size, size, *knob).withMargin(juce::FlexItem::Margin(35, 10, 10, 10)));
	}
}