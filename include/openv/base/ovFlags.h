#pragma once
#include <type_traits>
namespace ov {

template <typename E>
class Flags final
{
    static_assert(std::is_enum_v<E>, "#error Flags<>");
public:
    using enum_type = std::underlying_type_t<E>;

public:
    constexpr Flags() : value(0) {}
    constexpr Flags(E e) : value(static_cast<enum_type>(e)) {}

public:
    constexpr Flags& operator&=(E e) { value &= static_cast<enum_type>(e); return *this; }
    constexpr Flags& operator&=(Flags rhs) { value &= rhs.value; return *this; }

    constexpr Flags& operator|=(E e) { value |= static_cast<enum_type>(e); return *this; }
    constexpr Flags& operator|=(Flags rhs) { value |= rhs.value; return *this; }

    constexpr Flags& operator^=(E e) { value ^= static_cast<enum_type>(e); return *this; }
    constexpr Flags& operator^=(Flags rhs) { value ^= rhs.value; return *this; }

    constexpr Flags operator&(E e) const { return Flags(static_cast<E>(value & static_cast<enum_type>(e))); }
    constexpr Flags operator&(Flags rhs) const { return Flags(static_cast<E>(value & rhs.value)); }

    constexpr Flags operator|(E e) const { return Flags(static_cast<E>(value | static_cast<enum_type>(e))); }
    constexpr Flags operator|(Flags rhs) const { return Flags(static_cast<E>(value | rhs.value)); }

    constexpr Flags operator^(E e) const { return Flags(static_cast<E>(value ^ static_cast<enum_type>(e))); }
    constexpr Flags operator^(Flags rhs) const { return Flags(static_cast<E>(value ^ rhs.value)); }

    constexpr Flags operator~() const { return Flags(static_cast<E>(~value)); }

    constexpr bool operator==(E e) const { return value == static_cast<enum_type>(e); } 
    constexpr bool operator==(Flags rhs) const { return value == rhs.value; }

    constexpr bool operator!=(E e) const { return value != static_cast<enum_type>(e); } 
    constexpr bool operator!=(Flags rhs) const { return value != rhs.value; }

    constexpr bool operator!() const { return !value; }

    constexpr operator enum_type() const { return value; }
    constexpr operator bool() const { return !!value; }

    constexpr bool empty() const { return !value }

private:
    enum_type value;
};

template <typename E> struct enum_enable_operators { static constexpr bool value = false; };
template <typename E> using enum_enable_operators_t = std::enable_if_t<enum_enable_operators<E>::value, Flags<E>>;

template <typename E> enum_enable_operators_t<E> operator|(E lhs, E rhs) 
{ 
    return Flags<E>(static_cast<E>(static_cast<typename Flags<E>::enum_type>(lhs) | static_cast<typename Flags<E>::enum_type>(rhs)));
}

template <typename E> enum_enable_operators_t<E> operator&(E lhs, E rhs) 
{ 
    return Flags<E>(static_cast<E>(static_cast<typename Flags<E>::enum_type>(lhs) & static_cast<typename Flags<E>::enum_type>(rhs)));
}

template <typename E> enum_enable_operators_t<E> operator^(E lhs, E rhs) 
{ 
    return Flags<E>(static_cast<E>(static_cast<typename Flags<E>::enum_type>(lhs) ^ static_cast<typename Flags<E>::enum_type>(rhs)));
}

template <typename E> enum_enable_operators_t<E> operator~(E rhs) 
{ 
    return Flags<E>(static_cast<E>(~static_cast<typename Flags<E>::enum_type>(rhs)));
}

#define OPENV_FLAGS_ENABLE_OPERATORS(E) template <> struct enum_enable_operators<E> { static constexpr bool value = true; };
}
