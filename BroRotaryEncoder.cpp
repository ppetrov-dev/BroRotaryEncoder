#include "BroRotaryEncoder.h"
#include "BroEncoderButtonStates.h"

BroRotaryEncoder::BroRotaryEncoder(byte pinClk, byte pinDt, byte pinSw, bool isActiveLow, bool isPullupActive)
	: BroSimpleRotaryEncoder(pinClk, pinDt), _pinSw(pinSw), _isPullupActive(isPullupActive)
{
	_buttonPressedValue = isActiveLow ? LOW : HIGH;
}
BroRotaryEncoder::BroRotaryEncoder(byte pinClk, byte pinDt, byte pinSw)
	: BroRotaryEncoder(pinClk, pinDt, pinSw, true, true)
{
}
BroRotaryEncoder::~BroRotaryEncoder()
{
	DisposeStateIfNotNull();
}
void BroRotaryEncoder::Init()
{
	BroSimpleRotaryEncoder::Init();
	pinMode(_pinSw, _isPullupActive ? INPUT_PULLUP : INPUT);
	Reset();
}
void BroRotaryEncoder::Reset()
{
	BroSimpleRotaryEncoder::Reset();
	_startTime = 0;
	_stopTime = 0;
	TransitionTo(new BroEncoderNormalState());
}
void BroRotaryEncoder::SetDebounceTicks(unsigned long milliseconds)
{
	_debounceTicks = milliseconds;
}
void BroRotaryEncoder::SetClickTicks(unsigned long milliseconds)
{
	_clickTicks = milliseconds;
}
void BroRotaryEncoder::SetPressTicks(unsigned long milliseconds)
{
	_pressTicks = milliseconds;
}
void BroRotaryEncoder::AttachOnLeftHoldTurn(void (*newFunction)())
{
	_onLeftHoldTurnCallbackFunc = newFunction;
}
void BroRotaryEncoder::AttachOnRightHoldTurn(void (*newFunction)())
{
	_onRightHoldTurnCallbackFunc = newFunction;
}
void BroRotaryEncoder::AttachOnClick(void (*newFunction)())
{
	_onClickCallbackFunc = newFunction;
}
void BroRotaryEncoder::AttachOnDoubleClick(void (*newFunction)())
{
	_onDoubleClickCallbackFunc = newFunction;
}
void BroRotaryEncoder::AttachOnLongPressStart(void (*newFunction)())
{
	_onLongPressStartCallbackFunc = newFunction;
}
void BroRotaryEncoder::AttachOnLongPressStop(void (*newFunction)())
{
	_onLongPressStopCallbackFunc = newFunction;
}
int BroRotaryEncoder::GetLastPressedTicks()
{
	return _stopTime - _startTime;
}
void BroRotaryEncoder::DisposeStateIfNotNull()
{
	if (_buttonState == nullptr)
		return;
	delete _buttonState;
}
void BroRotaryEncoder::TransitionTo(BroEncoderStateBase *state)
{
	DisposeStateIfNotNull();
	_buttonState = state;
	if (_buttonState == nullptr)
		return;
	_buttonState->SetContext(this);
}
EventHandler BroRotaryEncoder::GetEventHandlerToExecute(const bool &isButtonPressed)
{
	if (_broSequenceCombiner.IsLeftTurn())
		return isButtonPressed ? _onLeftHoldTurnCallbackFunc : _onLeftTurnCallbackFunc;
	else if (_broSequenceCombiner.IsRightTurn())
		return isButtonPressed ? _onRightHoldTurnCallbackFunc : _onRightTurnCallbackFunc;

	return nullptr;
}
void BroRotaryEncoder::Tick()
{
	auto isButtonPressed = digitalRead(_pinSw) == _buttonPressedValue;
	auto currenMillis = millis();

	_buttonState->Tick(isButtonPressed, currenMillis);

	auto twisterState = BroSimpleRotaryEncoder::ReadState();
	_broSequenceCombiner.EnqueueIfNeeded(twisterState);

	if (_broSequenceCombiner.IsCompleted())
	{
		auto action = GetEventHandlerToExecute(isButtonPressed);
		if (action != nullptr)
		{
			_buttonState->Drop(isButtonPressed);
			action();
		}
		_broSequenceCombiner.Reset();
	}
	else
		_buttonState->RaiseEventIfNeeded();
}
