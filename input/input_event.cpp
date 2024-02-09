#include <input/input_event.hpp>
#include <input/input_map.hpp>

sdl::InputEvent::InputEvent(const std::shared_ptr<InputMap> &input_map): input_map(input_map), pressed(false), canceled(true) {
}

bool sdl::InputEvent::is_action(const std::string &action_name) const {
	const std::shared_ptr<InputMap> input_map = this->input_map.lock();
	return input_map ? input_map->is_action_active(action_name) : false;
}

bool sdl::InputEvent::is_action_pressed(const std::string &action_name, const bool allow_echo) const {
	const std::shared_ptr<InputMap> input_map = this->input_map.lock();
	return input_map ? input_map->is_action_pressed(action_name, allow_echo) : false;
}