#include "BroRotaryEncoder.h"

BroRotaryEncoder::BroRotaryEncoder(byte pinClk, byte pinDt, byte pinSw)
	: _pinClk(pinClk), _pinDt(pinDt), _pinSw(pinSw)
{
	pinMode(_pinClk, INPUT);
	pinMode(_pinDt, INPUT);
	pinMode(_pinSw, INPUT_PULLUP);
}

void BroRotaryEncoder::AttachOnLeftTurn(callback newFunction)
{
	_onLeftTurnCallbackFunc = newFunction;
}

void BroRotaryEncoder::AttachOnRightTurn(callback newFunction)
{
	_onRightTurnCallbackFunc = newFunction;
}

void BroRotaryEncoder::AttachOnLeftHoldTurn(callback newFunction)
{
	_onLeftHoldTurnCallbackFunc = newFunction;
}

void BroRotaryEncoder::AttachOnRightHoldTurn(callback newFunction)
{
	_onRightHoldTurnCallbackFunc = newFunction;
}
void BroRotaryEncoder::AttachOnClick(callback newFunction)
{
	_onClickCallbackFunc = newFunction;
}
void BroRotaryEncoder::AttachOnDoubleClick(callback newFunction)
{
	_onDoubleClickCallbackFunc = newFunction;
}
void BroRotaryEncoder::AttachOnPressStart(callback newFunction)
{
	_onPressStartCallbackFunc = newFunction;
}
void BroRotaryEncoder::AttachOnPressStop(callback newFunction)
{
	_onPressStopCallbackFunc = newFunction;
}

unsigned char BroRotaryEncoder::ReadTwisterState()
{
	return digitalRead(_pinClk) | (digitalRead(_pinDt) << 1);
}
bool BroRotaryEncoder::WasLeftTurn()
{
	if (_currentTwisterState != BroRotaryEncoderState::LeftTurn)
		return false;

	_currentTwisterState = BroRotaryEncoderState::Normal;
	return true;
}
bool BroRotaryEncoder::WasRightTurn()
{
	if (_currentTwisterState != BroRotaryEncoderState::RightTurn)
		return false;

	_currentTwisterState = BroRotaryEncoderState::Normal;
	return true;
}
bool BroRotaryEncoder::WasLeftHoldTurn()
{
	if (_currentTwisterState != BroRotaryEncoderState::LeftHoldTurn)
		return false;
	_currentTwisterState = BroRotaryEncoderState::Normal;
	return true;
}
bool BroRotaryEncoder::WasRightHoldTurn()
{
	if (_currentTwisterState != BroRotaryEncoderState::RightHoldTurn)
		return false;
	_currentTwisterState = BroRotaryEncoderState::Normal;
	return true;
}
bool BroRotaryEncoder::WasHolded()
{
	if (_flags.hold_flag && _flags.isHolded_f)
	{
		_flags.isHolded_f = false;
		return true;
	}
	return false;
}
bool BroRotaryEncoder::WasSingleClicked()
{
	if (!_flags.isSingle_f)
		return false;
	_flags.isSingle_f = false;
	_flags.isDouble_f = false;
	return true;
}
bool BroRotaryEncoder::WasDoubleClicked()
{
	if (!_flags.isDouble_f)
		return false;
	_flags.isDouble_f = false;
	_flags.isSingle_f = false;
	return true;
}
void BroRotaryEncoder::ObserveButtonEvents(unsigned long &currentMillis)
{
	auto debounceDelta = currentMillis - _lastTimestampInMilliseconds;
	_wasButtonPressed = !digitalRead(_pinSw);

	if (_wasButtonPressed && !_flags.butt_flag && (debounceDelta > ButtonDebounceInMilliseconds))
	{
		_flags.butt_flag = true;
		_flags.turn_flag = false;
		_lastTimestampInMilliseconds = currentMillis;
		debounceDelta = 0;
		_flags.isPress_f = true;
		_flags.isHolded_f = true;
		_flags.doubleAllow = true;
	}
	if (!_wasButtonPressed && _flags.butt_flag && (debounceDelta > ButtonDebounceInMilliseconds))
	{
		if (!_flags.turn_flag && !_flags.hold_flag)
		{
			_flags.turn_flag = false;
			_flags.isRelease_f = true;
		}
		_flags.butt_flag = false;
		_lastTimestampInMilliseconds = currentMillis;
		debounceDelta = 0;
		_flags.hold_flag = false;

		if (_flags.doubleAllow && !_flags.doubleFlag)
		{
			_flags.doubleFlag = true;
			_flags.countFlag = false;
		}
		else
			_flags.countFlag = true;
	}
	if (_flags.doubleFlag && debounceDelta > ButtonDoubleClickTimeoutInMilliseconds)
	{
		if (!_flags.turn_flag)
		{
			if (!_flags.countFlag)
				_flags.isSingle_f = true;
			else
				_flags.isDouble_f = true;
		}
		_flags.doubleFlag = false;
	}
	if (_flags.butt_flag && debounceDelta > ButtonHoldTimeoutInMilliseconds && !_flags.turn_flag)
	{
		if (_wasButtonPressed)
		{
			_flags.hold_flag = true;
			_flags.isRelease_f = false;
			_flags.doubleAllow = false;
		}
		else
		{
			_flags.butt_flag = false;
			_flags.hold_flag = false;
			_lastTimestampInMilliseconds = currentMillis;
		}
	}
}
void BroRotaryEncoder::ObserveTwisterEvents(unsigned long &currentMillis)
{
	uint8_t state = ReadTwisterState();

	if (state != _previosTwisterState)
	{
		_currentTwisterState = BroRotaryEncoderState::Normal;
		if (_flags.rst_flag)
		{
			if (state == 3)
			{
				_flags.rst_flag = 0;
				_currentTwisterState = (BroRotaryEncoderState)(3 - _previosTwisterState);
			}
			else if (state == 0)
			{
				_flags.rst_flag = 0;
				_currentTwisterState = _previosTwisterState;
			}
		}
		if (state == 0)
		{
			_flags.rst_flag = 1;
		}

		if (_currentTwisterState != BroRotaryEncoderState::Normal)
		{
			_flags.isTurn_f = true;
			if (_wasButtonPressed)
				_currentTwisterState = (BroRotaryEncoderState)(_currentTwisterState + BroRotaryEncoderState::RightTurn);
		}
		_previosTwisterState = (BroRotaryEncoderState)state;
		_flags.turn_flag = true;
		_lastTimestampInMilliseconds = currentMillis;
	}
}
void BroRotaryEncoder::Tick()
{
	auto currentMillis = millis();

	ObserveButtonEvents(currentMillis);
	ObserveTwisterEvents(currentMillis);

	if (WasRightTurn() && _onRightTurnCallbackFunc != nullptr)
		_onRightTurnCallbackFunc();

	if (WasLeftTurn() && _onLeftTurnCallbackFunc != nullptr)
		_onLeftTurnCallbackFunc();

	if (WasRightHoldTurn() && _onRightHoldTurnCallbackFunc != nullptr)
		_onRightHoldTurnCallbackFunc();

	if (WasLeftHoldTurn() && _onLeftHoldTurnCallbackFunc != nullptr)
		_onLeftHoldTurnCallbackFunc();

	if (WasSingleClicked() && _onClickCallbackFunc != nullptr)
		_onClickCallbackFunc();

	if (WasDoubleClicked() && _onDoubleClickCallbackFunc != nullptr)
		_onDoubleClickCallbackFunc();

	if (WasHolded() && _onPressStartCallbackFunc != nullptr)
	{
		_wasHoldStarted = true;
		_onPressStartCallbackFunc();
	}

	if (_wasHoldStarted && !_wasButtonPressed && _onPressStopCallbackFunc != nullptr)
	{
		_wasHoldStarted = false;
		_onPressStopCallbackFunc();
	}
}
