/* @file          error.hpp                                                   */
/* @date          2020-05-03                                                  */

#ifndef LIB__LIBRESULT__INCLUDE__ERROR__ERROR_HPP
#define LIB__LIBRESULT__INCLUDE__ERROR__ERROR_HPP


#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <exception>

namespace __ensure_unuqie
{
class __error_0
{};
} // namespace __ensure_unuqie

class Error: public std::exception
{
public:
    Error(const std::string context) : m_context(context) {}
    virtual ~Error() {}

    virtual unsigned id() const
    {
        return m_id;
    };
    virtual std::string id_str() const = 0;
    virtual std::string name() const   = 0;
    virtual std::string help() const
    {
        return m_help;
    };
    virtual std::string context() const
    {
        return m_context;
    };

    virtual std::string to_full_string() const
    {
        std::stringstream ss;
        ss << "Error " << id() << " (" << id_str() << ") "
           << "\n  " << name() << "\n  " << help() << "\n    " << context();
        return ss.str();
    }

    virtual std::string to_string() const
    {
        std::stringstream ss;
        ss << name() << " (" << id() << ")\n  " << help() << "\n    "
           << context();
        return ss.str();
    }

protected:
    std::string m_context;
    std::string m_help;
    unsigned m_id = 0;
};

#define DefineError(CODE_NAME, base_error, ID, name_str, HELP)                 \
    namespace __ensure_unuqie                                                  \
    {                                                                          \
    class __error_##ID##                                                       \
    {};                                                                        \
    }                                                                          \
    class CODE_NAME : public base_error                                        \
    {                                                                          \
        static_assert(std::is_base_of<Error, base_error>::value,               \
                      #base_error " must be derived from Error");              \
                                                                               \
    public:                                                                    \
        CODE_NAME(const std::string& context = "") : base_error(context)       \
        {                                                                      \
            m_id   = ID;                                                       \
            m_help = HELP;                                                     \
        }                                                                      \
        std::string id_str() const                                             \
        {                                                                      \
            std::string ret;                                                   \
            if constexpr(!std::is_same<Error, base_error>::value)              \
            {                                                                  \
                ret += base_error::id_str() + ".";                             \
            }                                                                  \
            ret += #CODE_NAME;                                                 \
            return ret;                                                        \
        }                                                                      \
        std::string name() const                                               \
        {                                                                      \
            std::string ret;                                                   \
            if constexpr(!std::is_same<Error, base_error>::value)              \
            {                                                                  \
                ret += base_error::name() + ": ";                              \
            }                                                                  \
            ret += name_str;                                                   \
            return ret;                                                        \
        }                                                                      \
    }


#endif // LIB__LIBRESULT__INCLUDE__ERROR__ERROR_HPP
