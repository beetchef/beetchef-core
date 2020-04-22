/*
 *  Beetchef - real time audio sequencer
 *  Copyright (C) 2020 Anton Šefčík
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <catch2/catch.hpp>

#include <processing/timeline.hpp>

#include <limits>

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

SCENARIO( "Timeline correctly updates its counters", "[processing]" )
{
    GIVEN( "a Timeline in an initial state with specific configuration without loops" )
    {
        Processing::Timeline timeline {60, 4, 4, 48000, 1};

        REQUIRE( timeline.get_current_offset() == 0 );
        REQUIRE( timeline.get_current_timeslot() == 0 );
        REQUIRE( timeline.get_timeslot_length() == 48000 );
        REQUIRE( timeline.get_loops().empty() );

        WHEN( "the timeline is updated for nframes less than timeslot length - staying within current timeslot" )
        {
            Audio::nframes_t nframes_for_update = 40000;
            timeline.update(nframes_for_update);

            THEN( "current timeslot remains the same" )
            {
                REQUIRE( timeline.get_current_timeslot() == 0 );
            }

            THEN( "current offset is equal to nframes passed" )
            {
                REQUIRE( timeline.get_current_offset() == nframes_for_update );
            }
        }

        WHEN( "the timeline is updated for nframes less just by 1 frame than timeslot length - staying within current timeslot (corner)" )
        {
            Audio::nframes_t nframes_for_update = 47999;
            timeline.update(nframes_for_update);

            THEN( "current timeslot remains the same" )
            {
                REQUIRE( timeline.get_current_timeslot() == 0 );
            }

            THEN( "current offset is equal to the number of frames for update" )
            {
                REQUIRE( timeline.get_current_offset() == nframes_for_update );
            }
        }

        WHEN( "the timeline is updated for nframes equal to timeslot length - exceeding current timeslot (corner)" )
        {
            Audio::nframes_t nframes_for_update = 48000;
            timeline.update(nframes_for_update);

            THEN( "current timeslot is incremented by 1" )
            {
                REQUIRE( timeline.get_current_timeslot() == 1 );
            }

            THEN( "current offset is again 0" )
            {
                REQUIRE( timeline.get_current_offset() == 0 );
            }
        }
        
        WHEN( "the timeline is updated for nframes between 1 and 2 timeslot lengths - exceeding current timeslot" )
        {
            Audio::nframes_t nframes_for_update = 48500;
            timeline.update(nframes_for_update);

            THEN( "current timeslot is incremented by 1" )
            {
                REQUIRE( timeline.get_current_timeslot() == 1 );
            }

            THEN( "current offset is equal to the exceeding part" )
            {
                REQUIRE( timeline.get_current_offset() == 500 );
            }
        }

        WHEN( "the timeline is updated for nframes less just by 1 frame than 2 timeslot lengths - exceeding current timeslot (corner)" )
        {
            Audio::nframes_t nframes_for_update = 95999;
            timeline.update(nframes_for_update);

            THEN( "current timeslot is still incremented just by 1" )
            {
                REQUIRE( timeline.get_current_timeslot() == 1 );
            }

            THEN( "current offset is equal to the exceeding part" )
            {
                REQUIRE( timeline.get_current_offset() == 47999 );
            }
        }

        WHEN( "the timeline is updated for nframes between 2 and 3 timeslot lengths - exceeding current and next timeslot" )
        {
            Audio::nframes_t nframes_for_update = 96500;
            timeline.update(nframes_for_update);

            THEN( "current timeslot is incremented by 2" )
            {
                REQUIRE( timeline.get_current_timeslot() == 2 );
            }

            THEN( "current offset is equal to the exceeding part" )
            {
                REQUIRE( timeline.get_current_offset() == 500 );
            }
        }

        WHEN( "the timeline is updated for nframes equal to 7 times timeslot length - exceeding current and next 6 timeslots (corner)" )
        {
            Audio::nframes_t nframes_for_update = 48000 * 7;
            timeline.update(nframes_for_update);

            THEN( "current timeslot is incremented by 7" )
            {
                REQUIRE( timeline.get_current_timeslot() == 7 );
            }

            THEN( "the current offset is again 0" )
            {
                REQUIRE( timeline.get_current_offset() == 0 );
            }
        }
    }
}

SCENARIO( "Timeline correctly calculates process queue", "[processing]" )
{
    GIVEN( "a Timeline without loops" )
    {
        Processing::Timeline timeline;

        REQUIRE( timeline.get_loops().empty() );

        WHEN( "the timeline is updated for any nframes" )
        {
            timeline.update(std::numeric_limits<Audio::nframes_t>::max());

            THEN( "always only 1 process frame is calculated in the process queue" )
            {
                REQUIRE( timeline.get_process_queue().size() == 1 );
            }
        }
    }

    GIVEN( "a Timeline with a loop around 2 timeslots" )
    {
        Processing::Timeline timeline;
        timeline.add_loop({0, 1, -1});

        WHEN( "the timeline is updated to exceed current timeslot but not to exceed the loop" )
        {
            Audio::nframes_t nframes_for_update = timeline.get_timeslot_length() + 42;

            timeline.update(nframes_for_update);

            THEN( "only 1 process frame is calculated in the process queue" )
            {
                REQUIRE( timeline.get_process_queue().size() == 1 );

                AND_THEN( "the process frame contains correct values" )
                {
                    auto process_frame = timeline.get_process_queue()[0];

                    REQUIRE( process_frame.begin_timeslot == 0 );
                    REQUIRE( process_frame.nframes == nframes_for_update );
                    REQUIRE( process_frame.offset == 0 );
                }
            }
        }

        WHEN( "the timeline is update to exceed the loop" )
        {
            Audio::nframes_t timeslot_length = timeline.get_timeslot_length();
            Audio::nframes_t nframes_for_update = timeslot_length * 3 + 42;
            timeline.update(nframes_for_update);

            THEN( "2 process frames are calculated in the process queue" )
            {
                auto process_queue = timeline.get_process_queue();

                REQUIRE( process_queue.size() == 2 );

                AND_THEN( "the process frames contain correct values" )
                {
                    REQUIRE( process_queue[0].begin_timeslot == 0 );
                    REQUIRE( process_queue[0].nframes == timeslot_length * 2 );
                    REQUIRE( process_queue[0].offset == 0 );

                    REQUIRE( process_queue[1].begin_timeslot == 0 );
                    REQUIRE( process_queue[1].nframes == nframes_for_update - timeslot_length * 2 );
                    REQUIRE( process_queue[1].offset == 0 );
                }
            }
        }
    }
}
