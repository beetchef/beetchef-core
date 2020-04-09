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
