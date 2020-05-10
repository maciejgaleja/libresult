/* @file          result.hpp                                                  */

#ifndef LIB__LIBRESULT__INCLUDE__ERROR__RESULT_HPP
#define LIB__LIBRESULT__INCLUDE__ERROR__RESULT_HPP


#include "error.hpp"

#include <cassert>
#include <optional>

template <typename T>
class Result
{
public:
    static Result<T> ok(T value)
    {
        Result<T> ret;
        ret.m_value = value;
        return ret;
    }

    template <typename E>
    static Result<T> err(const std::string& context = "")
    {
        Result<T> ret;
        ret.m_error = std::make_unique<E>(context);
        return ret;
    }

    T value()
    {
        T ret;
        if(m_value)
        {
            ret = *m_value;
        }
        else
        {
            if(m_error)
            {
                throw *(dynamic_cast<std::exception*>(m_error.get()));
            }
            else
            {
                assert(false);
            }
        }
        return ret;
    }

    const Error& error()
    {
        if(m_error)
        {
            return *m_error;
        }
        else
        {
            assert(false);
        }
    }

    explicit operator bool() const
    {
        return m_value.has_value();
    }

private:
    Result() {}
    std::optional<T> m_value;
    std::unique_ptr<Error> m_error;
};


#endif // LIB__LIBRESULT__INCLUDE__ERROR__RESULT_HPP
