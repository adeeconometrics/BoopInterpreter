#ifndef __TYPES_H__
#define __TYPES_H__

#include <optional>
#include <variant>
#include <string>

namespace boop {
    struct Uncopyable {
        explicit Uncopyable() = default;
        Uncopyable(const Uncopyable&) = delete;
        Uncopyable(Uncopyable&&) = delete;

        virtual ~Uncopyable() = default;

        auto operator=(const Uncopyable&) noexcept -> Uncopyable& = delete;
        auto operator=(Uncopyable &&) noexcept -> Uncopyable& = delete;
    }

    typedef std::variant<std::string, double, float, int> LiteralType;
    typedef std::optional<LiteralType> OptionalLiteral;
}

#endif // __TYPES_H__