#pragma once

#include <JuceHeader.h>

class Callback;

///<summary>Class which manages instances of <see cref="Callback" />.</summary>
///<remarks>Instances of <see cref="Callback" /> created by this object will be alive as long, as this object will be.</remarks>
class CallbackManager
{
public:
	~CallbackManager();
	Callback* create(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged = nullptr);

private:
	///<summary>Holds all instances of <see cref="Callback" /> created by this object</summary>
	juce::Array<Callback*> callbacks;
};

///<summary>It is wrapper around <see cref="juce::AudioParameterFloat::Listener" /> which allows usage of lambdas and std::function.</summary>
class Callback : public juce::AudioProcessorParameter::Listener
{
public:
	void parameterValueChanged(int parameterIndex, float newValue) override;
	void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override;
	friend Callback* CallbackManager::create(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged);
private:
	Callback(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged);

	///<summary>Function to be called by <see cref="Callback::parameterValueChanged" />.<summary>
	std::function<void(int, float)> valueChanged;
	///<summary>Function to be called by <see cref="Callback::parameterGestureChanged" />.<summary>
	std::function<void(int, bool)> gestureChanged;
};