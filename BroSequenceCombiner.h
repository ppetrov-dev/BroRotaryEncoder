#ifndef broSequenceCombiner
#define broSequenceCombiner

#define BroSequenceCombinerSize 4
class BroSequenceCombiner
{
private:
    static const unsigned int EndOfSequence = 3;
    const unsigned int LeftTurnSequence[BroSequenceCombinerSize] = {3, 2, 0, 1};
    const unsigned int RightTurnSequence[BroSequenceCombinerSize] = {3, 1, 0, 2};

    int _index = 0;
    unsigned char _lastValue = EndOfSequence;
    bool _isLeftTurn = false, _isRightTurn = false;
    unsigned char _circularBuffer[BroSequenceCombinerSize];
    void MoveNext(void);
    void MovePrevious(void);
    void MovePrevious(int &index);
    bool Matches(const unsigned int sequence[]);
    unsigned char GetCurrentValue(void);

public:
    BroSequenceCombiner(void);
    void EnqueueIfNeeded(const unsigned int &value);

    bool IsCompleted(void);
    bool IsLeftTurn(void);
    bool IsRightTurn(void);

    void Reset(void);
};

#endif //broSequenceCombiner