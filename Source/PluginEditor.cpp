#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <iostream>

///<summary>Creates editor.</summary>
FuzzTeethAudioProcessorEditor::FuzzTeethAudioProcessorEditor (FuzzTeethAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
	setResizable(true, true);
	initControls();
	setSize(600, 560);
	
	this->setResizeLimits(290, 405, INT_MAX, INT_MAX);

	audioProcessor.getWaveShaper()->setChangeEvent([this] {repaint(); });
}

///<summary>Destructor</summary>
FuzzTeethAudioProcessorEditor::~FuzzTeethAudioProcessorEditor()
{
	delete teethGroup;
	delete saturationGroup;
	delete graphs;
}

/// <summary>
/// This method is called when window is resized.
/// </summary>
void FuzzTeethAudioProcessorEditor::resized()
{
	setLayout(getBounds().reduced(10));
}

///<summary>Gives editor info about level of currently played audio</summary>
///<param name="level">Level of currently played audio, in range [0, 1].</param>
void FuzzTeethAudioProcessorEditor::setLevel(float level)
{
	if (graphs != nullptr)
	{
		graphs->setLevel(level);
	}
}

/// <summary>
/// this function position all the controls.
/// </summary>
/// <param name="bounds">Window bounds.</param>
void FuzzTeethAudioProcessorEditor::setLayout(juce::Rectangle<int> bounds)
{
	flexbox.performLayout(bounds);
}

///<summary>
/// Initialises controls.
/// </summary>
/// <remarks>
/// This method is called only once, in the window constructor.
/// </remarks>
void FuzzTeethAudioProcessorEditor::initControls()
{
	initFlexbox();
	initGroups();
	initGraphs();
}

/// <summary>This function sets up a flexbox object.</summary>
/// <remarks>It is called only once.</remarks>
void FuzzTeethAudioProcessorEditor::initFlexbox()
{
	flexbox.alignContent = juce::FlexBox::AlignContent::stretch;
	flexbox.flexDirection = juce::FlexBox::Direction::column;
	flexbox.alignItems = juce::FlexBox::AlignItems::stretch;
}

/// <summary> This function initializes GroupedControlsComponent objects</summary>
/// <remarks>It is called only once.</remarks>
void FuzzTeethAudioProcessorEditor::initGroups()
{
	WaveShaper* waveShaper = audioProcessor.getWaveShaper();
	GroupedControlsComponent::SliderData teethSliders[]
	{
		GroupedControlsComponent::SliderData("teethSize", "Size", -0.3f, 0.3f, 0.05f, [waveShaper](float v){ waveShaper->setTeethSize(v); }),
		GroupedControlsComponent::SliderData("teethFrequency", "Frequency", 1.0f, 10.0f, 3.0f, [waveShaper](float v) { waveShaper->setTeethFrequency(v); }, 1.0f),
		GroupedControlsComponent::SliderData("teethLowPass", "Low Pass", 0.45f, 1.0f, 1.0f, [waveShaper, this](float v) { waveShaper->setTeethLowPassFrequency(v); }),
		GroupedControlsComponent::SliderData("teethSkew", "Skew", 0.0f, 1.0f, 0.0f, [waveShaper, this](float v) { waveShaper->setTeethSkew(v); })
	};

	GroupedControlsComponent::SliderData saturationSliders[]
	{
		GroupedControlsComponent::SliderData("saturationGain", "Gain", 0, 10, 1, [waveShaper](float v) { waveShaper->setSaturationGain(v); }),
		GroupedControlsComponent::SliderData("saturationClip", "Clip", 0.01f, 1, 1, [waveShaper](float v) { waveShaper->setSaturationClip(v); })
	};

	//initializing groups
	teethGroup = new GroupedControlsComponent("Teeth", teethSliders, 4, 70);
	saturationGroup = new GroupedControlsComponent("Saturation", saturationSliders, 2, 70);

	//adding to flexbox
	juce::FlexItem teethItem;
	juce::FlexItem saturationItem;

	teethItem.associatedComponent = teethGroup;
	teethItem.minHeight = 120;

	saturationItem.associatedComponent = saturationGroup;
	saturationItem.minHeight = 120;

	flexbox.items.add(teethItem);
	flexbox.items.add(saturationItem);

	this->addAndMakeVisible(teethGroup);
	this->addAndMakeVisible(saturationGroup);
}

///<summary>Initialises graph</summary>
void FuzzTeethAudioProcessorEditor::initGraphs()
{
	this->graphs = new GraphsComponent();
	this->graphs->setWaveShaper(((FuzzTeethAudioProcessor&)processor).getWaveShaper());
	flexbox.items.add(juce::FlexItem(*graphs).withMinHeight(50).withFlex(1, 1, 1));
	this->addAndMakeVisible(graphs);
}