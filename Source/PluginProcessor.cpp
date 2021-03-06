#include "PluginProcessor.h"
#include "PluginEditor.h"

///<summary>Creates processor.</summary>
FuzzTeethAudioProcessor::FuzzTeethAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	initChain();
	initParameters();
}

///<summary>Destructor.</summary>
FuzzTeethAudioProcessor::~FuzzTeethAudioProcessor()
{ 
}

///<summary>Returns name of plugin</summary>
///<returns>Returns "FuzzTeeth"</returns>
const juce::String FuzzTeethAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

///<summary>Returns true if plugin accepts midi, otherwise false</summary>
///<returns>Returns false</returns>
bool FuzzTeethAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

///<summary>Returns true if plugin produces midi, otherwise false</summary>
///<returns>Returns false</returns>
bool FuzzTeethAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

///<summary>Is this effect a midi effect?</summary>
///<returns>returns false</returns>
bool FuzzTeethAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

///<summary>Describes how long plugin should work after audio ends.</summary>
///<remarks>
///For example, reverb produces sound even some time after audio stops playing.
///This plugin ends output in the same moment, that audio ends.
///</remarks>
///<returns>Returns 0.0</returns>
double FuzzTeethAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

///<summary>Returns number of programs, in some DAWs called "presets"</summary>
int FuzzTeethAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

///<summary>Returns current program/preset index.</summary>
int FuzzTeethAudioProcessor::getCurrentProgram()
{
    return 0;
}

///<summary>Sets current program.</summary>
///<param name="index">index of the program that should be set as current.</param>
void FuzzTeethAudioProcessor::setCurrentProgram (int index)
{
	//TODO: implement.
}

///<summary>Returns program name.</summary>
///<param name="index">index of program thats name should be returned</param>
const juce::String FuzzTeethAudioProcessor::getProgramName (int index)
{
    return {};
}

///<summary>Changes programs name</summary>
///<param name="index">index of program thats name should be changed</param>
///<param name="newName">New name</param>
void FuzzTeethAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

///<summary>JUCE call this method before playing</summary>
///<remarks>It should be used for initialisation</remarks>
void FuzzTeethAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	juce::dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.numChannels = getNumInputChannels();
	spec.maximumBlockSize = samplesPerBlock;
	dspWaveShaper.get()->prepare(spec);
	dspGate.get()->prepare(spec);
	dspInput.get()->prepare(spec);
	dspLowPass.get()->prepare(spec);
	dspOutput.get()->prepare(spec);
}

///<summary>JUCE calls this method when playback stops.</summary>
///<remarks>It should be used to free up spare memory, etc.</remarks>
void FuzzTeethAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FuzzTeethAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FuzzTeethAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	if (shouldUpdateLowPass)
	{
		UpdateLowPass();
	}

	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();


    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
	int numberSamples = buffer.getNumSamples();
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
		/*for (int i = 0; i < sampleNumber; i++)
		{
			channelData[i] = waveShaper.processSample(channelData[i]);
		}*/
    }
	juce::dsp::AudioBlock<float> ab(buffer);
	juce::dsp::ProcessContextReplacing<float> ctx(ab);

	dspInput.get()->process(ctx);
	dspGate.get()->process(ctx);

	if (hasEditor())
	{
		FuzzTeethAudioProcessorEditor* editor = ((FuzzTeethAudioProcessorEditor*)getActiveEditor());
		if (editor != nullptr)
		{
			editor->setLevel(buffer.getMagnitude(0, buffer.getNumSamples()));
		}
	}

	dspWaveShaper.get()->process(ctx);
	dspLowPass.get()->process(ctx);
	dspOutput.get()->process(ctx);
}

//==============================================================================
bool FuzzTeethAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FuzzTeethAudioProcessor::createEditor()
{
    return new FuzzTeethAudioProcessorEditor (*this);
}

//==============================================================================
void FuzzTeethAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
	auto parameters = getParameters();
	juce::Array<float> data;
	for (auto& parameter : parameters)
	{
		data.add(parameter->getValue());
	}
	destData.append(data.getRawDataPointer(), sizeof(float) * data.size());
}

void FuzzTeethAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	float* floatData = (float*)data;
	int size = sizeInBytes / sizeof(float);
	auto parameters = getParameters();
	if (size != parameters.size())
	{
		throw new std::invalid_argument("Size of data is different tha it should be.");
	}
	for (int i = 0; i < size; i++)
	{
		parameters[i]->setValueNotifyingHost(floatData[i]);
	}
}

void FuzzTeethAudioProcessor::initParameters()
{
	initMasterParameters();
	initTeethParameters();
	initSaturationParameters();

}

void FuzzTeethAudioProcessor::initMasterParameters()
{
	masterInput = new juce::AudioParameterFloat(
		"masterInput",
		"Input",
		juce::NormalisableRange<float>(-20.0f, 20.0f),
		0.0f,
		"dB"
	);
	masterOutput = new juce::AudioParameterFloat(
		"masterOutput",
		"Output",
		juce::NormalisableRange<float>(-20.0f, 20.0f),
		0.0f,
		"dB"
	);
	masterGateTreshold = new juce::AudioParameterFloat(
		"masterGateTreshold",
		"Gate Treshold",
		juce::NormalisableRange<float>(-100.0f, 0.0f),
		-100.0f,
		"dB"
	);
	masterLowPass = new juce::AudioParameterFloat(
		"masterLowPass",
		"Low Pass",
		juce::NormalisableRange<float>(20.0f, 20000.0f),
		20000.0f,
		"Hz"
	);

	masterInput->addListener(callbackManager.create([this](int i, float value) {dspInput.get()->setGainDecibels(*masterInput); }));
	masterOutput->addListener(callbackManager.create([this](int i, float value) {dspOutput.get()->setGainDecibels(*masterOutput); }));
	masterGateTreshold->addListener(callbackManager.create([this](int i, float value) {dspGate.get()->setThreshold(*masterGateTreshold); }));
	masterLowPass->addListener(callbackManager.create([this](int i, float value) {setLowPass(*masterLowPass); }));

	dspInput.get()->setGainDecibels(*masterInput);
	dspOutput.get()->setGainDecibels(*masterOutput);
	dspGate.get()->setThreshold(*masterGateTreshold);
	setLowPass(*masterLowPass);

	addParameter(masterInput);
	addParameter(masterOutput);
	addParameter(masterGateTreshold);
	addParameter(masterLowPass);
}

void FuzzTeethAudioProcessor::initTeethParameters()
{
	teethSize = new juce::AudioParameterFloat(
		"teethSize",
		"Teeth Size",
		juce::NormalisableRange<float>(-0.3f, 0.3f),
		0.0f
	);
	teethFrequency = new juce::AudioParameterFloat(
		"teethFrequency",
		"Teeth Frequency",
		juce::NormalisableRange<float>(1.0f, 10.0f),
		2.0f
	);
	teethLowPass = new juce::AudioParameterFloat(
		"teethLowPass",
		"Teeth Low Pass",
		juce::NormalisableRange<float>(0.45f, 1.0f),
		1.0f
	);
	teethSkew = new juce::AudioParameterFloat(
		"teethSkew",
		"Teeth Skew",
		juce::NormalisableRange<float>(0.0f, 1.0f),
		0.0f
	);

	teethSize->addListener(callbackManager.create([this](int i, float value) {waveShaper.setTeethSize(*teethSize); }));
	teethFrequency->addListener(callbackManager.create([this](int i, float value) {waveShaper.setTeethFrequency(*teethFrequency); }));
	teethLowPass->addListener(callbackManager.create([this](int i, float value) {waveShaper.setTeethLowPassFrequency(*teethLowPass); }));
	teethSkew->addListener(callbackManager.create([this](int i, float value) {waveShaper.setTeethSkew(*teethSkew); }));

	waveShaper.setTeethSize(*teethSize);
	waveShaper.setTeethFrequency(*teethFrequency);
	waveShaper.setTeethLowPassFrequency(*teethLowPass);
	waveShaper.setTeethSkew(*teethSkew);

	addParameter(teethSize);
	addParameter(teethFrequency);
	addParameter(teethLowPass);
	addParameter(teethSkew);
}

void FuzzTeethAudioProcessor::initSaturationParameters()
{
	saturationGain = new juce::AudioParameterFloat(
		"saturationGain",
		"Saturation Gain",
		juce::NormalisableRange<float>(0.0f, 10.0f),
		0.0f
	);
	saturationClip = new juce::AudioParameterFloat(
		"saturationClip",
		"Saturation Clip",
		juce::NormalisableRange<float>(0.0f, 1.0f),
		1.0f
	);

	saturationGain->addListener(callbackManager.create([this](int i, float value) {waveShaper.setSaturationGain(*saturationGain); }));
	saturationClip->addListener(callbackManager.create([this](int i, float value) {waveShaper.setSaturationClip(*saturationClip); }));

	waveShaper.setSaturationGain(*saturationGain);
	waveShaper.setSaturationClip(*saturationClip);

	addParameter(saturationGain);
	addParameter(saturationClip);
}

void FuzzTeethAudioProcessor::initChain()
{
	dspInput.reset(new juce::dsp::Gain<float>());
	dspOutput.reset(new juce::dsp::Gain<float>());
	dspGate.reset(new juce::dsp::NoiseGate<float>());
	dspLowPass.reset(new juce::dsp::ProcessorDuplicator< juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float> >());
	dspWaveShaper.reset(new juce::dsp::WaveShaper<float, std::function<float(float)>>());

	waveShaper.initialise(sampleNumber);
	dspWaveShaper->functionToUse = [this](float x) {return this->waveShaper.processSample(x); };

	dspGate->setRatio(1000);
	dspGate->setAttack(10.0f);
	dspGate->setRelease(60.0f);
}

void FuzzTeethAudioProcessor::setLowPass(float f)
{
	lowPassFrequency = f;
	shouldUpdateLowPass = true;
}

void FuzzTeethAudioProcessor::UpdateLowPass()
{
	auto sampleRate = getSampleRate();
	*dspLowPass.get()->state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, lowPassFrequency);
	shouldUpdateLowPass = false;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FuzzTeethAudioProcessor();
}
