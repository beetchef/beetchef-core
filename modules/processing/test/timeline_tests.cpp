#include <catch2/catch.hpp>

#include <processing/timeline.hpp>

SCENARIO( "Timeline configuration keeps consistent", "[processing]" )
{
    GIVEN( "a Timeline with any configuration" )
    {
        Processing::Timeline timeline;

        WHEN( "beat length is queried from click config" )
        {
            auto click_config = timeline.get_click_config();
            auto beat_length = click_config.get_beat_length();

            THEN( "correct formula is used to calculate it" )
            {
                // beat_length = 60 seconds / tempo * quarter note length / signature_denominator * sample rate
                REQUIRE( beat_length == 60.0f / click_config.tempo * 4.0f / click_config.signature_denominator * click_config.sample_rate );
            }
        }
    }

    GIVEN( "a Timeline with a specific configuration" )
    {
        // different tempos
        Processing::Timeline timeline_1 {60, 4, 4, 48000, 1};
        Processing::Timeline timeline_2 {100, 4, 4, 48000, 1};
        Processing::Timeline timeline_3 {120, 4, 4, 48000, 1};

        // different time signatures
        Processing::Timeline timeline_4 {60, 2, 4, 48000, 1};
        Processing::Timeline timeline_5 {60, 5, 4, 48000, 1};
        Processing::Timeline timeline_6 {60, 7, 8, 48000, 1};

        // different sample rates
        Processing::Timeline timeline_7 {60, 4, 4, 44100, 1};
        Processing::Timeline timeline_8 {60, 4, 4, 88200, 1};
        Processing::Timeline timeline_9 {60, 4, 4, 96000, 1};

        // different number of timeslots per beat
        Processing::Timeline timeline_10 {60, 4, 4, 48000, 2};
        Processing::Timeline timeline_11 {60, 4, 4, 48000, 4};
        Processing::Timeline timeline_12 {60, 4, 4, 48000, 6};

        WHEN( "beat length is queried from click config" )
        {
            auto beat_length_1 = timeline_1.get_click_config().get_beat_length();
            auto beat_length_2 = timeline_2.get_click_config().get_beat_length();
            auto beat_length_3 = timeline_3.get_click_config().get_beat_length();
            
            auto beat_length_4 = timeline_4.get_click_config().get_beat_length();
            auto beat_length_5 = timeline_5.get_click_config().get_beat_length();
            auto beat_length_6 = timeline_6.get_click_config().get_beat_length();
            
            auto beat_length_7 = timeline_7.get_click_config().get_beat_length();
            auto beat_length_8 = timeline_8.get_click_config().get_beat_length();
            auto beat_length_9 = timeline_9.get_click_config().get_beat_length();

            auto beat_length_10 = timeline_10.get_click_config().get_beat_length();
            auto beat_length_11 = timeline_11.get_click_config().get_beat_length();
            auto beat_length_12 = timeline_12.get_click_config().get_beat_length();

            THEN( "a correct specific value is returned" )
            {
                REQUIRE( beat_length_1 == 48000 );
                REQUIRE( beat_length_2 == 28800 );
                REQUIRE( beat_length_3 == 24000 );

                REQUIRE( beat_length_4 == 48000 );
                REQUIRE( beat_length_5 == 48000 );
                REQUIRE( beat_length_6 == 24000 );

                REQUIRE( beat_length_7 == 44100 );
                REQUIRE( beat_length_8 == 88200 );
                REQUIRE( beat_length_9 == 96000 );

                REQUIRE( beat_length_10 == 48000 );
                REQUIRE( beat_length_11 == 48000 );
                REQUIRE( beat_length_12 == 48000 );
            }           
        }

        WHEN( "timeslot length is queried" )
        {
            auto timeslot_length_1 = timeline_1.get_timeslot_length();
            auto timeslot_length_2 = timeline_2.get_timeslot_length();
            auto timeslot_length_3 = timeline_3.get_timeslot_length();

            auto timeslot_length_4 = timeline_4.get_timeslot_length();
            auto timeslot_length_5 = timeline_5.get_timeslot_length();
            auto timeslot_length_6 = timeline_6.get_timeslot_length();

            auto timeslot_length_7 = timeline_7.get_timeslot_length();
            auto timeslot_length_8 = timeline_8.get_timeslot_length();
            auto timeslot_length_9 = timeline_9.get_timeslot_length();

            auto timeslot_length_10 = timeline_10.get_timeslot_length();
            auto timeslot_length_11 = timeline_11.get_timeslot_length();
            auto timeslot_length_12 = timeline_12.get_timeslot_length();

            THEN( "it has a correct value based on number of timeslots per beat" )
            {
                REQUIRE( timeslot_length_1 == 48000 );
                REQUIRE( timeslot_length_2 == 28800 );
                REQUIRE( timeslot_length_3 == 24000 );

                REQUIRE( timeslot_length_4 == 48000 );
                REQUIRE( timeslot_length_5 == 48000 );
                REQUIRE( timeslot_length_6 == 24000 );

                REQUIRE( timeslot_length_7 == 44100 );
                REQUIRE( timeslot_length_8 == 88200 );
                REQUIRE( timeslot_length_9 == 96000 );

                REQUIRE( timeslot_length_10 == 24000 );
                REQUIRE( timeslot_length_11 == 12000 );
                REQUIRE( timeslot_length_12 == 8000 );
            }
        }
    }
}

SCENARIO( "Timeline correctly updates and calculates process queue", "[processing]" )
{
    GIVEN( "a Timeline with a specific configuration and initial processing state" )
    {
        Processing::Timeline timeline {60, 4, 4, 48000, 1};

        REQUIRE( timeline.get_current_offset() == 0 );
        REQUIRE( timeline.get_current_timeslot() == 0 );
        REQUIRE( timeline.get_timeslot_length() == 48000 );

        WHEN( "the timeline is updated for a number of frames less than timeslot length - staying within current timeslot" )
        {
            Audio::nframes_t nframes_for_update = 40000;
            timeline.update(nframes_for_update);

            THEN( "the current timeslot remains the same" )
            {
                REQUIRE( timeline.get_current_timeslot() == 0 );
            }

            THEN( "the current offset is equal to the number of frames for update" )
            {
                REQUIRE( timeline.get_current_offset() == nframes_for_update );
            }

            THEN( "calculated process queue contains 1 correct process frame" )
            {
                REQUIRE( timeline.get_process_queue().size() == 1 );

                auto process_frame = timeline.get_process_queue()[0];

                REQUIRE( process_frame.begin_timeslot == 0 );
                REQUIRE( process_frame.offset == 0 );
                REQUIRE( process_frame.nframes == nframes_for_update );
            }
        }

        WHEN( "the timeline is updated for a number of frames less just by 1 frame than timeslot length - staying within current timeslot" )
        {
            Audio::nframes_t nframes_for_update = 47999;
            timeline.update(nframes_for_update);

            THEN( "the current timeslot remains the same" )
            {
                REQUIRE( timeline.get_current_timeslot() == 0 );
            }

            THEN( "the current offset is equal to the number of frames for update" )
            {
                REQUIRE( timeline.get_current_offset() == nframes_for_update );
            }

            THEN( "calculated process queue contains 1 correct process frame" )
            {
                REQUIRE( timeline.get_process_queue().size() == 1 );

                auto process_frame = timeline.get_process_queue()[0];

                REQUIRE( process_frame.begin_timeslot == 0 );
                REQUIRE( process_frame.offset == 0 );
                REQUIRE( process_frame.nframes == nframes_for_update );
            }
        }

        WHEN( "the timeline is updated for a number of frames equal to timeslot length - exceeding current timeslot" )
        {
            Audio::nframes_t nframes_for_update = 48000;
            timeline.update(nframes_for_update);

            THEN( "the current timeslot is incremented by 1" )
            {
                REQUIRE( timeline.get_current_timeslot() == 1 );
            }

            THEN( "the current offset is again 0" )
            {
                REQUIRE( timeline.get_current_offset() == 0 );
            }

            THEN( "calculated process queue contains 1 correct process frame" )
            {
                REQUIRE( timeline.get_process_queue().size() == 1 );

                auto process_frame = timeline.get_process_queue()[0];

                REQUIRE( process_frame.begin_timeslot == 0 );
                REQUIRE( process_frame.offset == 0 );
                REQUIRE( process_frame.nframes == nframes_for_update );
            }
        }

        WHEN( "the timeline is updated for a number of frames exceeding the timeslot length and less than 2 timeslot lengths - exceeding current timeslot" )
        {
            Audio::nframes_t nframes_for_update = 48500;
            timeline.update(nframes_for_update);

            THEN( "the current timeslot is incremented by 1" )
            {
                REQUIRE( timeline.get_current_timeslot() == 1 );
            }

            THEN( "the current offset is equal to the exceeding part" )
            {
                REQUIRE( timeline.get_current_offset() == 500 );
            }

            THEN( "calculated process queue contains 1 correct process frame" )
            {
                REQUIRE( timeline.get_process_queue().size() == 1 );

                auto process_frame = timeline.get_process_queue()[0];

                REQUIRE( process_frame.begin_timeslot == 0 );
                REQUIRE( process_frame.offset == 0 );
                REQUIRE( process_frame.nframes == nframes_for_update );
            }
        }

        WHEN( "the timeline is updated for a number of frames exceeding the timeslot length and less just by 1 frame than 2 timeslot lengths - exceeding current timeslot" )
        {
            Audio::nframes_t nframes_for_update = 95999;
            timeline.update(nframes_for_update);

            THEN( "the current timeslot is still incremented just by 1" )
            {
                REQUIRE( timeline.get_current_timeslot() == 1 );
            }

            THEN( "the current offset is equal to the exceeding part" )
            {
                REQUIRE( timeline.get_current_offset() == 47999 );
            }

            THEN( "calculated process queue contains 1 correct process frame" )
            {
                REQUIRE( timeline.get_process_queue().size() == 1 );

                auto process_frame = timeline.get_process_queue()[0];

                REQUIRE( process_frame.begin_timeslot == 0 );
                REQUIRE( process_frame.offset == 0 );
                REQUIRE( process_frame.nframes == nframes_for_update );
            }
        }

        WHEN( "the timeline is updated for a number of frames exceeding 2 timeslot lengths and less than 3 timeslot lengths - exceeding current and next timeslot" )
        {
            Audio::nframes_t nframes_for_update = 96500;
            timeline.update(nframes_for_update);

            THEN( "the current timeslot is incremented by 2" )
            {
                REQUIRE( timeline.get_current_timeslot() == 2 );
            }

            THEN( "the current offset is equal to the exceeding part" )
            {
                REQUIRE( timeline.get_current_offset() == 500 );
            }

            THEN( "calculated process queue contains 1 correct process frame" )
            {
                REQUIRE( timeline.get_process_queue().size() == 1 );

                auto process_frame = timeline.get_process_queue()[0];

                REQUIRE( process_frame.begin_timeslot == 0 );
                REQUIRE( process_frame.offset == 0 );
                REQUIRE( process_frame.nframes == nframes_for_update );
            }
        }

        WHEN( "the timeline is updated for a number of frames equal to a multiple of timeslot length - exceeding current and next 6 timeslots" )
        {
            Audio::nframes_t nframes_for_update = 48000 * 7;
            timeline.update(nframes_for_update);

            THEN( "the current timeslot is incremented by the value of multiplier used" )
            {
                REQUIRE( timeline.get_current_timeslot() == 7 );
            }

            THEN( "the current offset is again 0" )
            {
                REQUIRE( timeline.get_current_offset() == 0 );
            }

            THEN( "calculated process queue contains 1 correct process frame" )
            {
                REQUIRE( timeline.get_process_queue().size() == 1 );

                auto process_frame = timeline.get_process_queue()[0];

                REQUIRE( process_frame.begin_timeslot == 0 );
                REQUIRE( process_frame.offset == 0 );
                REQUIRE( process_frame.nframes == nframes_for_update );
            }
        }
    }
}
