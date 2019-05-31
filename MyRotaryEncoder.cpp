#include "MyRotaryEncoder.h"

MyRotaryEncoder::MyRotaryEncoder(byte pinClk, byte pinDt, byte pinSw)
	: _encoder(pinClk, pinDt, pinSw)
{
}

void MyRotaryEncoder::SetEncoderType(bool isDefaultEncoderType = false)
{
	_encoder.setType(isDefaultEncoderType);
}
void MyRotaryEncoder::SetEncoderDirection(bool isReversedEncoderDirection = false)
{
	_encoder.setDirection(isReversedEncoderDirection);
}

void MyRotaryEncoder::AttachOnLeftTurn(callbackFunction newFunction)
{
	_onLeftTurnCallbackFunc = newFunction;
}

void MyRotaryEncoder::AttachOnRightTurn(callbackFunction newFunction)
{
	_onRightTurnCallbackFunc = newFunction;
}

void MyRotaryEncoder::AttachOnLeftHoldTurn(callbackFunction newFunction)
{
	_onLeftHoldTurnCallbackFunc = newFunction;
}

void MyRotaryEncoder::AttachOnRightHoldTurn(callbackFunction newFunction)
{
	_onRightHoldTurnCallbackFunc = newFunction;
}
void MyRotaryEncoder::AttachOnClick(callbackFunction newFunction)
{
	_onClickCallbackFunc = newFunction;
}
bool MyRotaryEncoder::IsHolded()
{
	return _encoder.isPress();
}
void MyRotaryEncoder::Tick()
{
	_encoder.tick();

	if (_encoder.isRight() && _onRightTurnCallbackFunc != NULL)
		_onRightTurnCallbackFunc();

	if (_encoder.isLeft() && _onLeftTurnCallbackFunc != NULL)
		_onLeftTurnCallbackFunc();

	if (_encoder.isRightH() && _onRightHoldTurnCallbackFunc != NULL)
		_onRightHoldTurnCallbackFunc();

	if (_encoder.isLeftH() && _onLeftHoldTurnCallbackFunc != NULL)
		_onLeftHoldTurnCallbackFunc();

	if (_encoder.isClick() && _onClickCallbackFunc != NULL)
		_onClickCallbackFunc();
}
