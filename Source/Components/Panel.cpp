#include <JuceHeader.h>
#include "Panel.h"

///<summary>Destructor</summary>
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

///<summary>Clears background</summary>
void Panel::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
	g.setColour(juce::Colours::green);
	g.drawRect(getLocalBounds(), 3.0f);
}

///<summary>Called by JUCE when component is resized.</summary>
///<remarks>Sets bounds for sections and and their children.</remarks>
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

///<summary>Adds section</summary>
///<remarks>After adding all sections, sliders and buttons you should call <see cref="Panel::resized" /></remarks>
///<param name="name">Text that will be written over section, label</param>
void Panel::addSection(juce::String name)
{
	juce::GroupComponent* group = new juce::GroupComponent({}, name);
	addAndMakeVisible(group);
	sections.add(group);
}

///<summary>Adds ParameterFloatControl to section.</summary>
///<param name="parameter">parameter that will be attached to ParameterFloatControl.</param>
///<param name="sectionIndex">index of section that this ParameterFloatControl will be attached to.</param>
///<remarks>After adding all sections, sliders and buttons you should call <see cref="Panel::resized" /></remarks>
void Panel::addSlider(juce::RangedAudioParameter* parameter, int sectionIndex)
{
	ParameterFloatControl* control = new ParameterFloatControl(parameter);
	sections[sectionIndex]->addAndMakeVisible(control);
	components.add(control);
}

///<summary>Adds ParameterBoolControl to section.</summary>
///<param name="parameter">parameter that will be attached to ParameterBoolControl.</param>
///<param name="sectionIndex">index of section that this ParameterBoolControl will be attached to.</param>
///<remarks>After adding all sections, sliders and buttons you should call <see cref="Panel::resized" /></remarks>
void Panel::addButton(juce::RangedAudioParameter* parameter, int sectionIndex)
{
	//TODO: implement ParameterBoolControl and this method.
}
