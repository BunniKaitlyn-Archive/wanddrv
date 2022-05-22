#pragma once
#include <inttypes.h>
#include <hidapi.h>
#include <vector>

#define CONTROLLER_INTERFACE 2

class Util
{
public:
    static int16_t ReadS16(uint8_t* buffer, int32_t offset)
    {
        return (int16_t)buffer[offset] | (int16_t)buffer[offset + 1] << 8;
    }

    static uint16_t ReadU16(uint8_t* buffer, int32_t offset)
    {
        return (uint16_t)buffer[offset] | (uint16_t)buffer[offset + 1] << 8;
    }

    static int32_t ReadS32(uint8_t* buffer, int32_t offset)
    {
        return (int32_t)buffer[offset] | (int32_t)buffer[offset + 1] << 8 |
            (int32_t)buffer[offset + 2] << 16 | (int32_t)buffer[offset + 3] << 24;
    }

    static uint32_t ReadU32(uint8_t* buffer, int32_t offset)
    {
        return (uint32_t)buffer[offset] | (uint32_t)buffer[offset + 1] << 8 |
            (uint32_t)buffer[offset + 2] << 16 | (uint32_t)buffer[offset + 3] << 24;
    }

    static std::vector<char*> GetControllerPaths()
    {
        std::vector<char*> paths;

        struct hid_device_info *devices, *current_device;

        devices = hid_enumerate(0x28de, 0x2012);
        current_device = devices;

        while (current_device)
        {
            if (current_device->interface_number == CONTROLLER_INTERFACE)
            {
                paths.push_back(current_device->path);
            }

            current_device = current_device->next;
        }

        return paths;
    }
};
