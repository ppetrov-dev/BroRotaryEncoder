#include "BroSequenceCombiner.h"

BroSequenceCombiner::BroSequenceCombiner(void)
{
    Reset();
}
void BroSequenceCombiner::MoveNext(void)
{
    _index++;
    if (_index == BroSequenceCombinerSize)
        _index = 0;
}
void BroSequenceCombiner::MovePrevious(int &index)
{
    index--;
    if (index < 0)
        index = BroSequenceCombinerSize - 1;
}

void BroSequenceCombiner::MovePrevious(void)
{
    MovePrevious(_index);
}
bool BroSequenceCombiner::IsLeftTurn(void)
{
    return _isLeftTurn;
}
bool BroSequenceCombiner::IsRightTurn(void)
{
    return _isRightTurn;
}
bool BroSequenceCombiner::IsCompleted(void)
{
    return IsLeftTurn() || IsRightTurn();
}
unsigned char BroSequenceCombiner::GetCurrentValue(void)
{
    return _circularBuffer[_index];
}
bool BroSequenceCombiner::Matches(const unsigned int sequence[])
{
    for (register auto i = 0, index = _index; i < BroSequenceCombinerSize; i++, MovePrevious(index))
        if (sequence[i] != _circularBuffer[index])
            return false;

    return true;
}
void BroSequenceCombiner::Reset(void)
{
    _index = 0;
    for (register auto i = 0; i < BroSequenceCombinerSize; i++)
        _circularBuffer[i] = EndOfSequence;
    _isLeftTurn = false;
    _isRightTurn = false;
}
void BroSequenceCombiner::EnqueueIfNeeded(const unsigned int &value)
{
    if (GetCurrentValue() == value)
        return;

    MoveNext();
    _circularBuffer[_index] = value;

    if (value != EndOfSequence)
        return;

    _isRightTurn = Matches(RightTurnSequence);
    _isLeftTurn = Matches(LeftTurnSequence);
}