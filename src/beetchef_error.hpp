#ifndef BEETCHEF_ERROR_HPP
#define BEETCHEF_ERROR_HPP

#include <exception>
#include <string>

class Beetchef_error : public std::exception {
    public:
        Beetchef_error(std::string const& msg) : _msg{msg} { };
        char const* what() const noexcept override { return _msg.c_str(); };
    private:
        std::string _msg;
};

#endif // BEETCHEF_ERROR_HPP
