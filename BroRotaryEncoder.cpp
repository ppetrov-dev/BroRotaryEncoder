#include "BroRotaryEncoder.h"

BroRotaryEncoder::BroRotaryEncoder(byte pinClk, byte pinDt, byte pinSw, bool isActiveLow, bool isPullupActive)
	: BroSimpleRotaryEncoder(pinClk, pinDt), _pinSw(pinSw)
{
	_buttonPressedValue = isActiveLow ? LOW : HIGH;

	if (isPullupActive)
		pinMode(_pinSw, INPUT_PULLUP);
	else
		pinMode(_pinSw, INPUT);
}
BroRotaryEncoder::BroRotaryEncoder(byte pinClk, byte pinDt, byte pinSw)
	: BroRotaryEncoder(pinClk, pinDt, pinSw, true, true)
{
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
void BroRotaryEncoder::Reset()
{
	_buttonState = BroEncoderButtonState::Normal;
	_startTime = 0;
	_stopTime = 0;
}
int BroRotaryEncoder::GetLastPressedTicks()
{
	return _stopTime - _startTime;
}
void BroRotaryEncoder::RaiseLeftHoldTurnIfNotNull(void)
{
	if (_onLeftHoldTurnCallbackFunc != nullptr)
		_onLeftHoldTurnCallbackFunc();
}
void BroRotaryEncoder::RaiseRightHoldTurnIfNotNull(void)
{
	if (_onRightHoldTurnCallbackFunc != nullptr)
		_onRightHoldTurnCallbackFunc();
}
void BroRotaryEncoder::SetButtonState(const bool &isButtonPressed)
{
	unsigned long currenMillis = millis();

	if (_buttonState == BroEncoderButtonState::Normal && isButtonPressed)
	{
		_buttonState = BroEncoderButtonState::SingleClickCandidateState;
		_startTime = currenMillis;
		return;
	}

	if (_buttonState == BroEncoderButtonState::SingleClickCandidateState)
	{
		if (!isButtonPressed && (currenMillis - _startTime) < _debounceTicks)
			_buttonState = BroEncoderButtonState::Normal;
		else if (!isButtonPressed)
		{
			_buttonState = BroEncoderButtonState::SingleClickState;
			_stopTime = currenMillis;
		}
		else if (isButtonPressed && (currenMillis - _startTime) > _pressTicks)
		{
			_stopTime = currenMillis;
			_buttonState = BroEncoderButtonState::LongPressCandidateState;
		}
		return;
	}

	if (_buttonState == BroEncoderButtonState::SingleClickState)
	{
		if ((_onDoubleClickCallbackFunc == nullptr) || currenMillis - _startTime > _clickTicks)
			_buttonState = BroEncoderButtonState::SingleClickedState;
		else if (isButtonPressed && currenMillis - _stopTime > _debounceTicks)
		{
			_buttonState = BroEncoderButtonState::DoubleClickCandidateState;
			_startTime = currenMillis;
		}
		return;
	}

	if (_buttonState == BroEncoderButtonState::DoubleClickCandidateState && currenMillis - _startTime > _debounceTicks)
	{
		_stopTime = currenMillis;
		_startTime = currenMillis;
		_buttonState = BroEncoderButtonState::DoubleClickingState;
		return;
	}

	if (_buttonState == BroEncoderButtonState::DoubleClickedState)
	{
		if (isButtonPressed && currenMillis - _startTime > _pressTicks)
			_buttonState = BroEncoderButtonState::LongPressCandidateState;
		else if (!isButtonPressed)
			_buttonState = BroEncoderButtonState::Normal;
		return;
	}

	if (_buttonState == BroEncoderButtonState::LongPressStartedState && !isButtonPressed)
	{
		_stopTime = currenMillis;
		_buttonState = BroEncoderButtonState::LongPressStoppedState;
		return;
	}
}
void BroRotaryEncoder::RaiseButtonsEvents(void)
{
	switch (_buttonState)
	{
	case LongPressCandidateState:
		if (_onLongPressStartCallbackFunc != nullptr)
			_onLongPressStartCallbackFunc();
		_buttonState = BroEncoderButtonState::LongPressStartedState;
		break;
	case SingleClickedState:
		if (_onClickCallbackFunc != nullptr)
			_onClickCallbackFunc();
		_buttonState = BroEncoderButtonState::Normal;
		break;
	case DoubleClickingState:
		if (_onDoubleClickCallbackFunc != nullptr)
			_onDoubleClickCallbackFunc();
		_buttonState = BroEncoderButtonState::DoubleClickedState;
		break;
	case LongPressStoppedState:
		if (_onLongPressStopCallbackFunc != nullptr)
			_onLongPressStopCallbackFunc();
		_buttonState = BroEncoderButtonState::Normal;
		break;
	default:
		break;
	}
}
void BroRotaryEncoder::RaiseTwisterEvents(const bool &isButtonPressed)
{
	if (isButtonPressed)
	{
		if (_broSequenceCombiner.IsLeftTurn())
			RaiseLeftHoldTurnIfNotNull();
		else if (_broSequenceCombiner.IsRightTurn())
			RaiseRightHoldTurnIfNotNull();
	}
	else
	{
		if (_broSequenceCombiner.IsLeftTurn())
			RaiseLeftTurnIfNotNull();
		else if (_broSequenceCombiner.IsRightTurn())
			RaiseRightTurnIfNotNull();
	}
	_broSequenceCombiner.Reset();
}
void BroRotaryEncoder::Tick()
{
	auto isButtonPressed = digitalRead(_pinSw) == _buttonPressedValue;
	SetButtonState(isButtonPressed);

	auto twisterState = BroSimpleRotaryEncoder::ReadState();
	_broSequenceCombiner.EnqueueIfNeeded(twisterState);

	if (_broSequenceCombiner.IsCompleted())
		RaiseTwisterEvents(isButtonPressed);
	else
		RaiseButtonsEvents();
}
