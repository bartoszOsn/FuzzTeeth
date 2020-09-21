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
	delete graphs;
	delete panel;
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
	auto graphsBounds = bounds.removeFromBottom(bounds.getWidth() / 2);
	auto panelBounds = bounds;
	panelBounds.reduceIfPartlyContainedIn(graphsBounds);

	graphs->setBounds(graphsBounds);
	panel->setBounds(panelBounds);
}

///<summary>
/// Initialises controls.
/// </summary>
/// <remarks>
/// This method is called only once, in the window constructor.
/// </remarks>
void FuzzTeethAudioProcessorEditor::initControls()
{
	initGraphs();
	initPanel();
}

///<summary>Initialises graph</summary>
void FuzzTeethAudioProcessorEditor::initGraphs()
{
	this->graphs = new GraphsComponent();
	this->graphs->setWaveShaper(((FuzzTeethAudioProcessor&)processor).getWaveShaper());
	this->addAndMakeVisible(graphs);
}

///<summary>Initialises <see cref="FuzzTeethAudioProcessorEditor::panel" /></summary>
void FuzzTeethAudioProcessorEditor::initPanel()
{
	this->panel = new Panel();
	this->panel->addSection("Master");
	this->panel->addSection("Teeth");
	this->panel->addSection("Saturation");

	this->panel->addSlider(audioProcessor.masterInput, 0);
	this->panel->addSlider(audioProcessor.masterOutput, 0);
	this->panel->addSlider(audioProcessor.masterGateTreshold, 0);
	this->panel->addSlider(audioProcessor.masterLowPass, 0);

	this->panel->addSlider(audioProcessor.teethSize, 1);
	this->panel->addSlider(audioProcessor.teethFrequency, 1);
	this->panel->addSlider(audioProcessor.teethLowPass, 1);
	this->panel->addSlider(audioProcessor.teethSkew, 1);

	this->panel->addSlider(audioProcessor.saturationGain, 2);
	this->panel->addSlider(audioProcessor.saturationClip, 2);

	this->addAndMakeVisible(panel);
}
