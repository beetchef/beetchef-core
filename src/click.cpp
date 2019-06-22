#include "click.hpp"
#include <iostream>
#include <chrono>
#include <thread>

using std::cout;
using std::endl;
using std::string;

const string LOG_LABEL = "[Click]: ";

/*
    NOTE: 
    
    beat duration is calculated as:

        beatDuration = 1 minute / tempo * quarter note length / signatureDenominator

    bar duration is then calculated as:

        beatDuration * signatureNominator

    EXAMPLE:
    (1 beat each second)

    signature = 4/4
    signatureNominator = 4
    signatureDenominator = 4
    tempo = 60 bpm (quarter note beats per minute)

    beatDuration = 60000(1min in milis) / 60(tempo) * 4(quarter note length) / 4(signatureDenominator) = 60000 / 60 = 1000 ms (= 1s)

    barDuration = 1000 * 4(nominator) = 4000 ms (=4s)

 */

Click::Click(unsigned int tempo, unsigned int signatureNominator, unsigned int signatureDenominator) {
    mIsRunning = false;
    mCurrentBeat = 1;
    mTempo = tempo;
    mSignatureNominator = signatureNominator;
    mSignatureDenominator = signatureDenominator;
    mBeatDuration = 60000 /* 1 minute in milis */ / tempo * 4 /* quarter note length */ / signatureDenominator;
    mBarDuration = mBeatDuration * mSignatureNominator;
    cout << LOG_LABEL << "created..." << endl;
    cout << LOG_LABEL << "tempo: " << mTempo << endl;
    cout << LOG_LABEL << "Time signature: " << signatureNominator << "/" << signatureDenominator << endl;
}

void Click::start() {
    mIsRunning = true;
    cout << LOG_LABEL << "started..." << endl;
    
    std::thread clickLoopThread([this]() {
        while (mIsRunning) {
            // nextBeatTimePoint is current time + beat duration
            auto nextBeatTimePoint = std::chrono::steady_clock::now() + std::chrono::milliseconds(mBeatDuration);
            
            cout << LOG_LABEL << "*click* " << mCurrentBeat << endl;
            
            if (mCurrentBeat < mSignatureNominator) {
                // this was not the last beat within the bar, increment mCurrentBeat
                mCurrentBeat++;
            } else {
                // this was the last beat within the bar, reset mCurrentBeat to 1
                mCurrentBeat = 1;
                cout << endl;
            }
            std::this_thread::sleep_until(nextBeatTimePoint);
        }
    });

    // detach clickLoopThread and continue in execution flow
    clickLoopThread.detach();
}
