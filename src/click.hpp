#ifndef CLICK_HPP
#define CLICK_HPP

#include "jack_connection_node.hpp"
#include "messaging_handler.hpp"
#include "jack_client_wrapper.hpp"

class Click: public JackConnectionNode {
    public:
        Click(unsigned int tempo, unsigned int signatureNumerator, unsigned int signatureDenominator);
        bool initialize(JackClientWrapper *jackClientWrapper);
        void start();
        void processCallback(jack_nframes_t nframes);
    protected:
    private:
        JackClientWrapper *mJackClientWrapper;
        unsigned int mTempo;
        unsigned int mSignatureNumerator;
        unsigned int mSignatureDenominator;
        unsigned int mCurrentBeat;
        long mBeatDuration;
        long mBarDuration;
        bool mIsRunning;
        MessagingHandler mMessagingHandler;
};

#endif
