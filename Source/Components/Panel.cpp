/*
  ==============================================================================

    Panel.cpp
    Created: 17 Sep 2020 7:37:26am
    Author:  cokol

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Panel.h"

//==============================================================================
Panel::Panel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Panel::~Panel()
{
	for (auto ptr : sections)
	{
		delete ptr;
	}
	for (auto ptr : components)
	{
		delete ptr;
	}
}

void Panel::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void Panel::resized()
{
	int size = sections.size();
	auto bounds = getLocalBounds();
	float sectionHeight = bounds.getHeight() / (float)size;
	for (int i = 0; i < size; i++)
	{
		auto section = sections.getUnchecked(i);
		auto sectionBounds = bounds.withY(sectionHeight * i).withHeight(sectionHeight);
		section->setBounds(sectionBounds);
		auto children = section->getChildren();
		for (int j = 0; j < children.size(); j++)
		{
			auto child = children.getUnchecked(j);
			child->setBounds(sectionBounds.withX(sectionHeight * 2 * j).withWidth(sectionHeight * 2));
		}
	}
}

void Panel::addSection(juce::String name)
{
	juce::GroupComponent* group = new juce::GroupComponent({}, name);
	sections.add(group);
}

void Panel::addSlider(juce::RangedAudioParameter* parameter, int sectionIndex)
{
	ParameterFloatControl* control = new ParameterFloatControl(parameter);
	sections[sectionIndex]->addAndMakeVisible(control);
	components.add(control);
}

void Panel::addButton(juce::RangedAudioParameter* parameter, int sectionIndex)
{
	//TODO: implement ParameterBoolControl and this method.
}
