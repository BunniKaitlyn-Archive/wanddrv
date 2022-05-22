#pragma once
#include <windows.h>
#include <ViGEm/Client.h>

#include "vive_controller.h"

class VirtualController
{
private:
    PVIGEM_CLIENT client;

public:
    PVIGEM_TARGET pad;

    VirtualController();
    ~VirtualController();

    void Update(ViveController_State state);
};
