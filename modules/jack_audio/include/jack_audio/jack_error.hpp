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

#ifndef BEETCHEF_JACK_INIT_ERROR_HPP
#define BEETCHEF_JACK_INIT_ERROR_HPP

#include <exception>
#include <string>

namespace Jack_audio
{
    class Jack_error : public std::exception {
        public:
            explicit Jack_error(std::string const& msg) : _msg{msg} { };
            char const* what() const noexcept override { return _msg.c_str(); };
        private:
            std::string _msg;
    };

}; // namespace Jack_audio

#endif // BEETCHEF_JACK_INIT_ERROR_HPP
