#ifndef CLICK_HPP
#define CLICK_HPP


class Click {
    public:
        Click(unsigned int tempo, unsigned int signatureNominator, unsigned int signatureDenominator);
        void start();
    protected:
    private:
        unsigned int mTempo;
        unsigned int mSignatureNominator;
        unsigned int mSignatureDenominator;
        unsigned int mCurrentBeat;
        long mBeatDuration;
        long mBarDuration;
        bool mIsRunning;
};

#endif
