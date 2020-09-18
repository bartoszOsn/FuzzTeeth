#pragma once

#include <JuceHeader.h>

class Callback;

class CallbackManager
{
public:
	~CallbackManager();
	Callback* create(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged = nullptr);

private:
	juce::Array<Callback*> callbacks;
};

class Callback : juce::AudioParameterFloat::Listener
{
public:
	void parameterValueChanged(int parameterIndex, float newValue) override;
	void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override;
	friend Callback* CallbackManager::create(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged);
private:
	Callback(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged);
	std::function<void(int, float)> valueChanged;
	std::function<void(int, bool)> gestureChanged;
};