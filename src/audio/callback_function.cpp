#include "callback_function.hpp"
#include "audio/audio_types.hpp"

Callback_function::Callback_function()
    : _pimpl{nullptr}
{
}

Callback_function::Callback_function(const Callback_function& other)
    : _pimpl{other._pimpl->clone()}
{
}

Callback_function& Callback_function::operator=(const Callback_function& other)
{
    _pimpl = other._pimpl->clone();
    return *this;
}

int Callback_function::operator()(nframes_t nframes)
{
    return _pimpl->operator()(nframes);
}

Callback_function::operator bool() const
{
    return _pimpl.get();
}
