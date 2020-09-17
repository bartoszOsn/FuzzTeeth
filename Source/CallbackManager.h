#pragma once

#include <JuceHeader.h>

class CallbackManager
{
public:
	class Callback : juce::AudioParameterFloat::Listener
	{
	public:
		Callback(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged);
		void parameterValueChanged(int parameterIndex, float newValue) override;
		void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override;
	private:
		std::function<void(int, float)> valueChanged;
		std::function<void(int, bool)> gestureChanged;
	};
	Callback create(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged);

private:
	juce::Array<Callback*
};