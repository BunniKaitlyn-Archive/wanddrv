#include "virtual_controller.h"

#include <stdio.h>

VirtualController::VirtualController()
{
    // TODO(Kaitlyn): Move client initialization out of here, it's slow.
    this->client = vigem_alloc();
    if (this->client == nullptr)
    {
        printf("ViGEm client could not be allocated.");
    }

    VIGEM_ERROR connect_result = vigem_connect(this->client);
    if (!VIGEM_SUCCESS(connect_result))
    {
        printf("ViGEm connection failed. Code = 0x%x08", connect_result);
    }

    this->pad = vigem_target_x360_alloc();

    VIGEM_ERROR target_result = vigem_target_add(this->client, this->pad);
    if (!VIGEM_SUCCESS(target_result))
    {
        printf("Target plug-in failed. Code = 0x%x08", target_result);
    }
}

VirtualController::~VirtualController()
{
    vigem_target_remove(this->client, this->pad);
    vigem_target_free(this->pad);
}

void VirtualController::Update(ViveController_State state)
{
    XUSB_REPORT report{};

    if (state.pressed_buttons & (uint32_t)ViveController_Button::System)
    {
        report.wButtons |= XUSB_GAMEPAD_START;
    }
    else
    {
        report.wButtons &= ~XUSB_GAMEPAD_START;
    }

    if (state.pressed_buttons & (uint32_t)ViveController_Button::Application)
    {
        report.wButtons |= XUSB_GAMEPAD_BACK;
    }
    else
    {
        report.wButtons &= ~XUSB_GAMEPAD_BACK;
    }

    if (state.pressed_buttons & (uint32_t)ViveController_Button::Touchpad)
    {
        report.wButtons |= XUSB_GAMEPAD_RIGHT_THUMB;
    }
    else
    {
        report.wButtons &= ~XUSB_GAMEPAD_RIGHT_THUMB;
    }

    if (state.pressed_buttons & (uint32_t)ViveController_Button::Grip)
    {
        report.wButtons |= XUSB_GAMEPAD_RIGHT_SHOULDER;
    }
    else
    {
        report.wButtons &= ~XUSB_GAMEPAD_RIGHT_SHOULDER;
    }

    report.bRightTrigger = (uint8_t)state.trigger_value;

    report.sThumbRX = state.touchpad_horizontal;
    report.sThumbRY = state.touchpad_vertical;

    vigem_target_x360_update(client, pad, report);
}
