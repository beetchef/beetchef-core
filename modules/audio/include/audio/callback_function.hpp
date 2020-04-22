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

#ifndef BEETCHEF_CALLBACK_FUNCTION_HPP
#define BEETCHEF_CALLBACK_FUNCTION_HPP

#include "types.hpp"

#include <memory>

namespace Audio
{
    class Callback_function {
        public:

            template<typename T>
            explicit Callback_function(T callable)
                : _callable(std::make_unique<Cb_model<T>>(std::move(callable)))
            { }

            Callback_function(const Callback_function&);
            Callback_function(Callback_function&&) = default;
            Callback_function& operator=(const Callback_function&);
            Callback_function& operator=(Callback_function&&) = default;
            ~Callback_function() = default;

            int operator()(const nframes_t nframes) const;

            operator bool() const;

        private:

            struct Cb_concept {
                virtual ~Cb_concept() = default;
                virtual int operator()(const nframes_t) const = 0;
                virtual std::unique_ptr<Cb_concept> clone() const = 0;
            };

            template<typename T>
            struct Cb_model final : public Cb_concept {
                explicit Cb_model(T self) : _self{std::move(self)}
                { }

                int operator()(const nframes_t nframes) const override
                {
                    return _self(nframes);
                };

                std::unique_ptr<Cb_concept> clone() const override
                {
                    return std::make_unique<Cb_model>(_self);
                }

                T _self;
            };

            std::unique_ptr<Cb_concept> _callable;
    };

    inline constexpr auto dummy_callback {[](nframes_t nframes)->int
    {
        (void) nframes; // suppress unused parameter warning
        return 0;
    }};

}; // namespace Audio

#endif // BEETCHEF_CALLBACK_FUNCTION_HPP
