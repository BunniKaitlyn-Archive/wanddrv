#include "vive_controller.h"

#include <wchar.h>

#include "util.h"

#define MAX_STRING 255
#define MAX_READ 65

ViveController::ViveController(hid_device *handle)
{
    this->handle = handle;

    static wchar_t serial_number[MAX_STRING];
    hid_get_serial_number_string(handle, serial_number, MAX_STRING);
    this->serial_number = serial_number;

    wprintf(L"Controller (%s) initialized.\n", serial_number);
}

ViveController::~ViveController()
{
    hid_close(this->handle);
}

void ViveController::Update()
{
    uint8_t buffer[MAX_READ];
    int32_t result = hid_read(handle, buffer, MAX_READ);

    // We only want user input.
    if (Util::ReadU16(buffer, 0x02) == 0x3c01)
    {
        state.pressed_buttons = Util::ReadU32(buffer, 0x08);

        state.trigger_value = Util::ReadU16(buffer, 0x0c);

        state.touchpad_horizontal = Util::ReadS16(buffer, 0x14);
        state.touchpad_vertical = Util::ReadS16(buffer, 0x16);
    }
}