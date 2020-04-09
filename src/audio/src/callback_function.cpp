#include "audio/callback_function.hpp"
#include "audio/types.hpp"

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
