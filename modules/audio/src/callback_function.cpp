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

#include <audio/callback_function.hpp>
#include <audio/types.hpp>

using Audio::Callback_function;

Callback_function::Callback_function(const Callback_function& other)
    : _callable{other._callable->clone()}
{
}

Callback_function& Callback_function::operator=(const Callback_function& other)
{
    _callable = other._callable->clone();
    return *this;
}

int Callback_function::operator()(const nframes_t nframes) const
{
    return _callable->operator()(nframes);
}

Callback_function::operator bool() const
{
    return _callable.get();
}
