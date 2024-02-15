#pragma once

#include <input/input_event.hpp>

namespace sdl {

struct InputProxy {
	std::shared_ptr<InputEvent> input_event;

	InputProxy() {
		input_event = std::make_unique<InputEvent>();
	}

	InputProxy(const std::shared_ptr<InputEvent> &input_event): input_event(input_event) {
	}

	bool operator==(const InputProxy &input) const {
		return input_event->same_input(input.input_event.get());
	}

	bool operator!=(const InputProxy &input) const {
		return !input_event->same_input(input.input_event.get());
	}
};

}
