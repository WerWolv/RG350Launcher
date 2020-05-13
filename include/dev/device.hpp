#pragma once

#include <venus.hpp>

#include <string>

namespace dev {

    class Device {
    public:
        Device(const std::string &devicePath);
        virtual ~Device();

    protected:
        std::string read();
        void write(const std::string &value);

    private:
        FILE *m_deviceFile = nullptr;
    };

    class DeviceInteger : public Device {
    public:
        DeviceInteger(const std::string &devicePath) : Device(devicePath) {}

        operator s32() {
            return std::stol(Device::read());
        }

        DeviceInteger& operator=(s32 value) {
            Device::write(std::to_string(value));

            return *this;
        }
    };

    class DeviceFloat : public Device {
    public:
        DeviceFloat(const std::string &devicePath) : Device(devicePath) {}

        operator float() {
            return std::stof(Device::read());
        }

        DeviceFloat& operator=(float value) {
            Device::write(std::to_string(value));

            return *this;
        }
    };

    class DeviceString : public Device {
    public:
        DeviceString(const std::string &devicePath) : Device(devicePath) {}

        operator std::string() {
            return Device::read();
        }

        DeviceString& operator=(std::string value) {
            Device::write(value);

            return *this;
        }
    };

}