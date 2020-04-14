#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <app/engine.hpp>
#include <audio/types.hpp>

#include <memory>
#include <thread>

struct Audio_interface_stub {
    Audio::nframes_t get_sample_rate() const { return 666; }
    int get_in_chan_count() const { return 2; };
    int get_out_chan_count() const { return 4; };

    Audio::sample_t* get_in_buf(int chan_idx, Audio::nframes_t nframes) const
    {
        // suppress unused parameter warnings
        (void) chan_idx;
        (void) nframes;

        return _in_buf.get();
    }

    Audio::sample_t* get_out_buf(int chan_idx, Audio::nframes_t nframes) const
    {
        // suppress unused parameter warnings
        (void) chan_idx;
        (void) nframes;

        return _out_buf.get();
    }

    void set_process_callback(Audio::Callback_function* callback) { (void) callback; }
    void unset_process_callback() {}
    void start_processing() {}
    void stop_processing() {}

    std::unique_ptr<Audio::sample_t[]> _in_buf = std::make_unique<Audio::sample_t[]>({5});
    std::unique_ptr<Audio::sample_t[]> _out_buf = std::make_unique<Audio::sample_t[]>({5});
};

SCENARIO( "Application engine can be started and stopped", "[app]" )
{
    GIVEN( "Initialized engine" )
    {
        Audio_interface_stub audio_interface_stub;
        Beetchef::Engine engine(std::move(audio_interface_stub));

        REQUIRE( engine.is_running() == false );

        WHEN( "the engine is started" )
        {
            std::thread engine_thread([&](){ engine.start(); });

            while (!engine.is_running()) { /* wait until it starts... TODO: add timeout */ };

            THEN( "the engine is running" )
            {
                REQUIRE( engine.is_running() == true );

                AND_WHEN( "engine is stopped" )
                {
                    engine.stop();

                    THEN( "the engine is not running" )
                    {
                        REQUIRE( engine.is_running() == false );
                    }
                }
            }

            engine_thread.join();
        }
    }
}
