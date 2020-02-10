#ifndef BEETCHEF_CALLBACK_FUNCTION_HPP
#define BEETCHEF_CALLBACK_FUNCTION_HPP

#include "audio_types.hpp"

#include <memory>

class Callback_function {
    public:
        Callback_function();

        template<typename T>
        explicit Callback_function(T callable)
            : _pimpl(std::make_unique<Cb_model<T>>(std::move(callable)))
        { }

        Callback_function(const Callback_function&);
        Callback_function(Callback_function&&) = default;
        Callback_function& operator=(const Callback_function&);
        Callback_function& operator=(Callback_function&&) = default;
        ~Callback_function() = default;

        int operator()(nframes_t nframes);

        operator bool() const;

    private:

        struct Cb_concept {
            virtual ~Cb_concept() = default;
            virtual int operator()(nframes_t) = 0;
            virtual std::unique_ptr<Cb_concept> clone() const = 0;
        };

        template<typename T>
        struct Cb_model final : public Cb_concept {
            explicit Cb_model(T self) : _self{std::move(self)}
            { }

            int operator()(nframes_t nframes) override
            {
                return _self(nframes);
            };

            std::unique_ptr<Cb_concept> clone() const override
            {
                return std::make_unique<Cb_model>(_self);
            }

            T _self;
        };

        std::unique_ptr<Cb_concept> _pimpl;
};

#endif // BEETCHEF_CALLBACK_FUNCTION_HPP
