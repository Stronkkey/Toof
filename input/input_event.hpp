#pragma once

#include <core/string/string_def.hpp>
#include <input/event_input_type.hpp>
#include <scene/resources/resource.hpp>

#include <memory>

namespace Toof {

class Input;

// Equal to EVENT_INPUT_TYPE_NONE
class InputEvent : public Resource {
private:
	const Input *input;

	virtual bool _same_input(const InputEvent*) const {
		return true;
	}

	virtual void _fill_with_event(const SDL_Event*) {
	}

protected:
	bool pressed;
	EventInputType type;

public:
	constexpr InputEvent(): input(nullptr), pressed(false), type(EVENT_INPUT_TYPE_NONE) {
	}

	constexpr void set_input(const Input *input) {
		this->input = input;
	}

	constexpr bool is_pressed() const {
		return pressed;
	}
	
	constexpr EventInputType get_type() const {
		return type;
	}

	bool is_action(const String &action_name) const;
	bool is_action_pressed(const String &action_name) const;
	bool is_action_released(const String &action_name) const;

	void fill_with_event(const SDL_Event *event);
	bool same_input(const InputEvent *input_event) const;
};

// Equal to EVENT_INPUT_TYPE_KEYBOARD
class InputEventKeyboard : public InputEvent {
private:
	SDL_Keycode key_code;
	SDL_Scancode scan_code;
	uint32_t time_stamp;
	uint16_t modifiers;

	void _fill_with_event(const SDL_Event *event) override;
	bool _same_input(const InputEvent *input_event) const override;
public:
	constexpr InputEventKeyboard(): key_code(SDLK_UNKNOWN), scan_code(SDL_SCANCODE_UNKNOWN), time_stamp(0), modifiers(0) {
		type = EVENT_INPUT_TYPE_KEYBOARD;
	}

	constexpr void set_keycode(const SDL_Keycode key_code) {
		this->key_code = key_code;
	}

	constexpr SDL_Keycode get_keycode() const {
		return key_code;
	}

	constexpr void set_scan_code(const SDL_Scancode scan_code) {
		this->scan_code = scan_code;
	}

	constexpr SDL_Scancode get_scan_code() const {
		return scan_code;
	}

	constexpr void set_time_stamp(const uint32_t time_stamp) {
		this->time_stamp = time_stamp;
	}

	constexpr uint32_t get_time_stamp() const {
		return time_stamp;
	}

	constexpr void set_modifiers(const uint16_t modifiers) {
		this->modifiers = modifiers;
	}

	constexpr uint16_t get_modifiers() const {
		return modifiers;
	}
};

// Equal to EVENT_INPUT_TYPE_USER << EVENT_INPUT_TYPE_WINDOW
class InputEventAction : public InputEvent {
private:
	String action_name;
	float strength;

	bool _same_input(const InputEvent *input_event) const override;
public:
	InputEventAction(): action_name(), strength(0.0f) {
		type = (EventInputType)(EVENT_INPUT_TYPE_USER << EVENT_INPUT_TYPE_WINDOW);
	}

	constexpr void set_pressed(const bool pressed) {
		this->pressed = pressed;
	}

	void set_action_name(const String &action_name) {
		this->action_name = action_name;
	}

	constexpr const String &get_action_name() const {
		return action_name;
	}

	constexpr void set_strength(const float strength) {
		this->strength = strength;
	}

	constexpr float get_strength() const {
		return strength;
	}
};

}
