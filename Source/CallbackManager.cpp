#include "CallbackManager.h"

Callback::Callback(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged)
{
	this->valueChanged = valueChanged;
	this->gestureChanged = gestureChanged;
}

void Callback::parameterValueChanged(int parameterIndex, float newValue)
{
	if (valueChanged)
	{
		valueChanged(parameterIndex, newValue);
	}
}

void Callback::parameterGestureChanged(int parameterIndex, bool gestureIsStarting)
{
	if (gestureChanged)
	{
		gestureChanged(parameterIndex, gestureIsStarting);
	}
}

CallbackManager::~CallbackManager()
{
	for (Callback*& clb : callbacks)
	{
		delete clb;
	}
}

Callback* CallbackManager::create(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged)
{
	Callback* clb = new Callback(valueChanged, gestureChanged);
	callbacks.add(clb);
	return clb;
}
