#pragma once

#include <core/math/rect2.hpp>

#include <SDL_video.h>
#include <SDL_log.h>

namespace Toof {

class Window {

private:
	enum InitilizationStatus {
		INITIALIZED,
		NOT_INITIALIZED,
		INITILIZATION_FAILED
	};

	static InitilizationStatus initialized;
	static void try_initialize();
	static void fail_with_message(const String &message, const SDL_LogCategory category = SDL_LOG_CATEGORY_APPLICATION);

	String window_title;
	Rect2i window_rect;

	SDL_Window *window;

public:
	Window();
	~Window();

	constexpr SDL_Window *get_window() const {
		return window;
	}

	void set_window_rect(const Rect2i &window_rect);
  	constexpr const Rect2i &get_window_rect() const {
		return window_rect;
	}

	void set_window_title(const String &new_title);
	constexpr const String &get_window_title() const {
		return window_title;
	}

	int get_refresh_rate() const;

	bool intialized_successfully() const;
};

}
