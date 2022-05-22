#pragma once
#include <inttypes.h>
#include <hidapi.h>
#include <string>
#include <thread>

enum class ViveController_Button
{
	Trigger = 1 << 0,
	Grip = 1 << 2,
	Application = 1 << 12,
	System = 1 << 13,
	Touchpad = 1 << 18,
	Thumb = 1 << 20
};

struct ViveController_State
{
public:
	uint32_t pressed_buttons;

	uint16_t trigger_value;

	int16_t touchpad_horizontal;
	int16_t touchpad_vertical;
};

class ViveController
{
public:
	hid_device* handle;

	std::wstring serial_number;

	ViveController_State state;

	ViveController(hid_device *handle);
	~ViveController();

	void Update();
};
