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
}

void Panel::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void Panel::resized()
{
	int size = sections.size();
	auto bounds = getLocalBounds();
	for (int i = 0; i < size; i++)
	{
		auto section = sections.getUnchecked(i);
		section.setBoundsRelative(0.0f, bounds.getHeight() / size * i, 1.0f, bounds.getHeight() / size);

	}
}
