#pragma once

#include <string>
#include "types.hpp"

class Result {
public:
    constexpr Result() : m_value(0) { }

    constexpr Result(u32 value) : m_value(value) { }

    constexpr Result(u32 module, u32 desc) : m_value((module & 0x1FF ) | (desc & 0x1FFF) << 9) { }

    constexpr Result(const Result &result) : m_value(result.m_value) { }

    constexpr u32 getModule() const {
        return this->m_value & 0x1FF;
    }

    constexpr u32 getDescription() const {
        return (this->m_value >> 9) & 0x1FFF;
    }

    std::string getString() const {
        char buffer[0x20];
        sprintf(buffer, "2%03d-%04d (0x%x)", this->getModule(), this->getDescription(), static_cast<u32>(*this));

        return buffer;
    }


    constexpr bool operator==(const Result &other) const {
        return this->getDescription() == other.getDescription();
    }

    constexpr bool operator!=(const Result &other) const {
        return this->getDescription() != other.getDescription();
    }


    constexpr Result operator=(const u32 &other) const {
        return Result(other);
    }

    constexpr Result operator=(const Result &other) const {
        return Result(static_cast<u32>(other));
    }

    constexpr Result operator=(const Result &&other) const {
        return Result(static_cast<u32>(other));
    }

    constexpr operator u32() const {
        return this->m_value;
    }

    constexpr bool succeeded() const {
        return this->m_value == 0;
    }

    constexpr bool failed() const {
        return !this->succeeded();
    }

private:
    const u32 m_value;
};

template<typename T>
using ResultVal = std::pair<Result, T>;