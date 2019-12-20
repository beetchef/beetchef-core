#include "click.hpp"
#include "messaging_handler.hpp"
#include <iostream>
#include <chrono>
#include <thread>

using std::cout;
using std::endl;
using std::string;

#define LOG_LABEL "[Click]: "

/*
    NOTE:

    beat duration is calculated as:

        beat_duration = 1 minute / tempo * quarter note length / signature_denominator

    bar duration is then calculated as:

        bar_duration = beat_duration * signature_numerator

    EXAMPLE:
    (1 beat each second)

    signature = 4/4
    signature_numerator = 4
    signature_denominator = 4
    tempo = 60 bpm (quarter note beats per minute)

    beat_duration = 60000(1min in milis) / 60(tempo) * 4(quarter note length) / 4(signature_denominator) = 60000 / 60 = 1000 ms (= 1s)

    bar_duration = 1000 * 4(signature_numerator) = 4000 ms (=4s)

 */

Click::Click(unsigned int tempo, unsigned int signature_numerator, unsigned int signature_denominator) : _messaging_handler() {
    _is_running = false;
    _current_beat = 1;
    _tempo = tempo;
    _signature_numerator = signature_numerator;
    _signature_denominator = signature_denominator;
    _beat_duration = 60000 /* 1 minute in milis */ / tempo * 4 /* quarter note length */ / signature_denominator;
    _bar_duration = _beat_duration * _signature_numerator;
    cout << LOG_LABEL << "created..." << endl;
    cout << LOG_LABEL << "tempo: " << _tempo << endl;
    cout << LOG_LABEL << "time signature: " << _signature_numerator << "/" << _signature_denominator << endl;
}

bool Click::initialize(Jack_client_wrapper *jack_client_wrapper) {

    _jack_client_wrapper = jack_client_wrapper;
    _jack_client_wrapper->register_connection_node(this);

    return true;
}

void Click::start() {
    _is_running = true;
    cout << LOG_LABEL << "started..." << endl;

    std::thread click_loop_thread([this]() {
        // TMP: testing
        int total_beat_count = 0;

        while (_is_running) {
            // next_beat_timepoint is current time + beat duration
            auto next_beat_timepoint = std::chrono::steady_clock::now() + std::chrono::milliseconds(_beat_duration);

            cout << LOG_LABEL << "*click* " << _current_beat << endl;

            // TMP: testing
            total_beat_count++;

            // TMP: testing
            if (total_beat_count == 5 || total_beat_count == 9) {
                _messaging_handler.send_message("/sl/0/hit", "record");
            }

            if (_current_beat < _signature_numerator) {
                // this was not the last beat within the bar, increment mCurrentBeat
                _current_beat++;
            } else {
                // this was the last beat within the bar, reset mCurrentBeat to 1
                _current_beat = 1;
                cout << endl;
            }
            std::this_thread::sleep_until(next_beat_timepoint);
        }
    });

    // detach clickLoopThread and continue in flow execution
    click_loop_thread.detach();
}

void Click::jack_process_callback(jack_nframes_t nframes) {
    cout << LOG_LABEL << "JACK process callback - TODO: process " << nframes << " frames here..." << endl;
};
