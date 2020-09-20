#pragma once

#include <JuceHeader.h>
#include "waveShaper.h"
#include "CallbackManager.h"

///<summary>Distorts audio.</summary>
class FuzzTeethAudioProcessor  : public juce::AudioProcessor
{
public:
	//============= Parameters =============

	//----- Master -----

	juce::AudioParameterFloat* masterInput;
	juce::AudioParameterFloat* masterOutput;
	juce::AudioParameterFloat* masterGateTreshold;
	juce::AudioParameterFloat* masterLowPass;

	//----- Teeth -----

	juce::AudioParameterFloat* teethSize;
	juce::AudioParameterFloat* teethFrequency;
	juce::AudioParameterFloat* teethLowPass;
	juce::AudioParameterFloat* teethSkew;

	//----- Saturation -----

	juce::AudioParameterFloat* saturationGain;
	juce::AudioParameterFloat* saturationClip;

    FuzzTeethAudioProcessor();
    ~FuzzTeethAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	WaveShaper* getWaveShaper() { return &waveShaper; }

private:
	CallbackManager callbackManager;

	const int sampleNumber = 512;
	WaveShaper waveShaper;

	juce::dsp::WaveShaper<float, std::function<float(float)>> dspWaveShaper;

	void initParameters();
	void initMasterParameters();
	void initTeethParameters();
	void initSaturationParameters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FuzzTeethAudioProcessor)
};
