#include "CallbackManager.h"

///<summary>
///Constructor.
///See <seealso cref="CallbackManager::create" />
///</summary>
Callback::Callback(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged)
{
	this->valueChanged = valueChanged;
	this->gestureChanged = gestureChanged;
}

///<summary>implementation of <see cref="juce::AudioParameterFloat::Listener::parameterValueChanged" />.</summary>
void Callback::parameterValueChanged(int parameterIndex, float newValue)
{
	if (valueChanged)
	{
		valueChanged(parameterIndex, newValue);
	}
}

///<summary>implementation of <see cref="juce::AudioParameterFloat::Listener::parameterGestureChanged" />.</summary>
void Callback::parameterGestureChanged(int parameterIndex, bool gestureIsStarting)
{
	if (gestureChanged)
	{
		gestureChanged(parameterIndex, gestureIsStarting);
	}
}

///<summary>Destructor</summary>
///<remarks>Deletes all <see cref="Callback" /> objects created by <see cref="CallbackManager::create" /></remarks>
CallbackManager::~CallbackManager()
{
	for (Callback*& clb : callbacks)
	{
		delete clb;
	}
}

///<summary>Creates object which can be used as argument by <see cref="juce::AudioParameterFloat::addListener" />
///<remarks>Returned object will be alive as long as <c>this*</c> is.</remarks>
///<param name="valueChanged">Functor which will be called by <see cref="Callback::parameterValueChanged" />.</param>
///<param name="gestureChanged">Functor which will be called by <see cref="Callback::parameterGestureChanged" />.</param>
Callback* CallbackManager::create(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged)
{
	Callback* clb = new Callback(valueChanged, gestureChanged);
	callbacks.add(clb);
	return clb;
}
