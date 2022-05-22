#include <windows.h>
#include <hidapi.h>
#include <iostream>

#include "util.h"
#include "virtual_controller.h"
#include "vive_controller.h"

int main()
{
    if (hid_init())
    {
        return -1;
    }

    std::vector<char*> controller_paths = Util::GetControllerPaths();
    std::vector<ViveController*> vive_controllers;

    if (controller_paths.size() >= 2)
    {
        printf("wanddrv does not support more than 2 controllers.");
        return -1;
    }

    for (auto& path : controller_paths)
    {
        hid_device *handle = hid_open_path(path);
        if (handle != nullptr)
        {
            vive_controllers.push_back(new ViveController(handle));
        }
    }

    VirtualController* virtual_controller = new VirtualController();

    while (true)
    {
        for (auto& controller : vive_controllers)
        {
            controller->Update();

            ViveController_State state = controller->state;

            virtual_controller->Update(state);
        }
    }

    for (auto& controller : vive_controllers)
    {
        delete controller;
    }

    hid_exit();
    return 0;
}
