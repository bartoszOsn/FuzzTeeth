/*
  ==============================================================================

    CallbackManager.cpp
    Created: 17 Sep 2020 12:17:54pm
    Author:  cokol

  ==============================================================================
*/

#include "CallbackManager.h"

CallbackManager::Callback::Callback(std::function<void(int, float)> valueChanged, std::function<void(int, bool)> gestureChanged)
{
}

void CallbackManager::Callback::parameterValueChanged(int parameterIndex, float newValue)
{
}

void CallbackManager::Callback::parameterGestureChanged(int parameterIndex, bool gestureIsStarting)
{
}
