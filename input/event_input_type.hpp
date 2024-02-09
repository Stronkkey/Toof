#pragma once

#include <SDL_events.h>

namespace sdl {

enum EventInputType {
	EVENT_INPUT_TYPE_NONE = 0,
	EVENT_INPUT_TYPE_AUDIO_DEVICE,
	EVENT_INPUT_TYPE_CONTROLLER_AXIS,
	EVENT_INPUT_TYPE_CONTROLLER_BUTTON,
	EVENT_INPUT_TYPE_CONTROLLER_DEVICE,
	EVENT_INPUT_TYPE_DOLLAR_GESTURE,
	EVENT_INPUT_TYPE_DROP,
	EVENT_INPUT_TYPE_TOUCH_FINGER,
	EVENT_INPUT_TYPE_KEYBOARD,
	EVENT_INPUT_TYPE_JOY_AXIS,
	EVENT_INPUT_TYPE_JOY_BALL,
	EVENT_INPUT_TYPE_JOY_HAT,
	EVENT_INPUT_TYPE_JOY_BUTTON,
	EVENT_INPUT_TYPE_JOY_DEVICE,
	EVENT_INPUT_TYPE_MOUSE_MOTION,
	EVENT_INPUT_TYPE_MOUSE_BUTTON,
	EVENT_INPUT_TYPE_MOUSE_WHEEL,
	EVENT_INPUT_TYPE_MULTI_GESTURE,
	EVENT_INPUT_TYPE_QUIT,
	EVENT_INPUT_TYPE_SYSWM,
	EVENT_INPUT_TYPE_TEXT_EDITING,
	EVENT_INPUT_TYPE_TEXT_INPUT,
	EVENT_INPUT_TYPE_USER,
	EVENT_INPUT_TYPE_WINDOW,
};

constexpr EventInputType get_event_type(const SDL_Event *event) {
	switch (event->type) {
		case SDL_AUDIODEVICEADDED:
			return EVENT_INPUT_TYPE_AUDIO_DEVICE;
		case SDL_AUDIODEVICEREMOVED:
			return EVENT_INPUT_TYPE_AUDIO_DEVICE;
		case SDL_CONTROLLERAXISMOTION:
			return EVENT_INPUT_TYPE_CONTROLLER_AXIS;
		case SDL_CONTROLLERBUTTONDOWN:
			return EVENT_INPUT_TYPE_CONTROLLER_BUTTON;
		case SDL_CONTROLLERBUTTONUP:
			return EVENT_INPUT_TYPE_CONTROLLER_BUTTON;
		case SDL_CONTROLLERDEVICEADDED:
			return EVENT_INPUT_TYPE_CONTROLLER_DEVICE;
		case SDL_CONTROLLERDEVICEREMOVED:
			return EVENT_INPUT_TYPE_CONTROLLER_DEVICE;
		case SDL_CONTROLLERDEVICEREMAPPED:
			return EVENT_INPUT_TYPE_CONTROLLER_DEVICE;
		case SDL_DOLLARGESTURE:
			return EVENT_INPUT_TYPE_DOLLAR_GESTURE;
		case SDL_DOLLARRECORD:
			return EVENT_INPUT_TYPE_DOLLAR_GESTURE;
		case SDL_DROPFILE:
			return EVENT_INPUT_TYPE_DROP;
		case SDL_DROPTEXT:
			return EVENT_INPUT_TYPE_DROP;
		case SDL_DROPBEGIN:
			return EVENT_INPUT_TYPE_DROP;
		case SDL_DROPCOMPLETE:
			return EVENT_INPUT_TYPE_DROP;
		case SDL_FINGERMOTION:
			return EVENT_INPUT_TYPE_TOUCH_FINGER;
		case SDL_FINGERDOWN:
			return EVENT_INPUT_TYPE_TOUCH_FINGER;
		case SDL_FINGERUP:
			return EVENT_INPUT_TYPE_TOUCH_FINGER;
		case SDL_KEYDOWN:
			return EVENT_INPUT_TYPE_KEYBOARD;
		case SDL_KEYUP:
			return EVENT_INPUT_TYPE_KEYBOARD;
		case SDL_JOYAXISMOTION:
			return EVENT_INPUT_TYPE_JOY_AXIS;
		case SDL_JOYBALLMOTION:
			return EVENT_INPUT_TYPE_JOY_BALL;
		case SDL_JOYHATMOTION:
			return EVENT_INPUT_TYPE_JOY_HAT;
		case SDL_JOYBUTTONDOWN:
			return EVENT_INPUT_TYPE_JOY_BUTTON;
		case SDL_JOYBUTTONUP:
			return EVENT_INPUT_TYPE_JOY_BUTTON;
		case SDL_JOYDEVICEADDED:
			return EVENT_INPUT_TYPE_JOY_DEVICE;
		case SDL_JOYDEVICEREMOVED:
			return EVENT_INPUT_TYPE_JOY_DEVICE;
		case SDL_MOUSEMOTION:
			return EVENT_INPUT_TYPE_MOUSE_MOTION;
		case SDL_MOUSEBUTTONDOWN:
			return EVENT_INPUT_TYPE_MOUSE_BUTTON;
		case SDL_MOUSEBUTTONUP:
			return EVENT_INPUT_TYPE_MOUSE_BUTTON;
		case SDL_MOUSEWHEEL:
			return EVENT_INPUT_TYPE_MOUSE_WHEEL;
		case SDL_MULTIGESTURE:
			return EVENT_INPUT_TYPE_MULTI_GESTURE;
		case SDL_QUIT:
			return EVENT_INPUT_TYPE_QUIT;
		case SDL_SYSWMEVENT:
			return EVENT_INPUT_TYPE_SYSWM;
		case SDL_TEXTEDITING:
			return EVENT_INPUT_TYPE_TEXT_EDITING;
		case SDL_TEXTINPUT:
			return EVENT_INPUT_TYPE_TEXT_INPUT;
		case SDL_USEREVENT:
			return EVENT_INPUT_TYPE_USER;
		case SDL_WINDOWEVENT:
			return EVENT_INPUT_TYPE_WINDOW;
	}
	return EVENT_INPUT_TYPE_NONE;
}

}