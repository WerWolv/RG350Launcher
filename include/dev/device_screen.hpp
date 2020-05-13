#pragma once

#include "device.hpp"

namespace dev {

    class DeviceScreen {
    public:
        DeviceScreen() :
            m_devBrightness("/sys/class/backlight/pwm-backlight/brightness"),
            m_devMaxBrightness("/sys/class/backlight/pwm-backlight/max_brightness"),
            m_devBlanking("/sys/class/graphics/fb0/blank")
        { }

        u32 getBrightness() {
            return this->m_devBrightness;
        }

        u32 getMaxBrightness() {
            return this->m_devMaxBrightness;
        }


        void setBrightness(u32 brightness) {
            this->m_devBrightness = brightness;
        }

        void setBlanking(bool blank) {
            this->m_devBlanking = blank;
        }

    private:
        DeviceInteger m_devBrightness;
        DeviceInteger m_devMaxBrightness;
        DeviceInteger m_devBlanking;
    };

}