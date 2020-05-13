#include "dev/device.hpp"

namespace dev {

    Device::Device(const std::string &devicePath) {
        this->m_deviceFile = fopen(devicePath.c_str(), "r+");
    }

    Device::~Device() {
        if (this->m_deviceFile != nullptr)
            fclose(this->m_deviceFile);
    }

    std::string Device::read() {
        if (this->m_deviceFile == nullptr)
            return "";

        std::string ret;

        fseek(this->m_deviceFile, 0, SEEK_END);
        u32 length = ftell(this->m_deviceFile);

        rewind(this->m_deviceFile);
        ret.reserve(length + 1);
        ret.resize(length);

        fread(ret.data(), 1, length, this->m_deviceFile);

        return ret;
    }

    void Device::write(const std::string &value) {
        if (this->m_deviceFile == nullptr)
            return;

        rewind(this->m_deviceFile);
        fwrite(value.data(), 1, value.length(), this->m_deviceFile);
    }

}