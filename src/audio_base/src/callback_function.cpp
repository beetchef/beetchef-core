#include "audio_base/callback_function.hpp"
#include "audio_base/types.hpp"

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

int Callback_function::operator()(const nframes_t nframes) const
{
    return _pimpl->operator()(nframes);
}

Callback_function::operator bool() const
{
    return _pimpl.get();
}
