#ifndef CLICK_HPP
#define CLICK_HPP


class Click {
    public:
        Click(unsigned int tempo, unsigned int signatureNumerator, unsigned int signatureDenominator);
        void start();
    protected:
    private:
        unsigned int mTempo;
        unsigned int mSignatureNumerator;
        unsigned int mSignatureDenominator;
        unsigned int mCurrentBeat;
        long mBeatDuration;
        long mBarDuration;
        bool mIsRunning;
};

#endif
