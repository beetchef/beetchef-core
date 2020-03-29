#ifndef BEETCHEF_JACK_INIT_ERROR_HPP
#define BEETCHEF_JACK_INIT_ERROR_HPP

#include <exception>
#include <string>

class Jack_init_error : public std::exception {
    public:
        explicit Jack_init_error(std::string const& msg) : _msg{msg} { };
        char const* what() const noexcept override { return _msg.c_str(); };
    private:
        std::string _msg;
};

#endif // BEETCHEF_JACK_INIT_ERROR_HPP
