#pragma once

#include <types/rect2.hpp>

#include <SDL_video.h>
#include <SDL_log.h>

namespace sdl {

class Window {

private:
	enum InitilizationStatus {
		INITIALIZED,
		NOT_INITIALIZED,
		INITILIZATION_FAILED
	};

	static InitilizationStatus initialized;
	static void try_initialize();
	static void fail_with_message(const std::string &message,
	    const SDL_LogCategory category = SDL_LOG_CATEGORY_APPLICATION);

	std::string window_title;
	Rect2i window_rect;

	SDL_Window *window;

public:
	Window();
	~Window();

	SDL_Window *get_window() const;

	void set_window_rect(const Rect2i &window_rect);
  	Rect2i get_window_rect() const;

	void set_window_title(const std::string &new_title);
	std::string get_window_title() const;

	int get_refresh_rate() const;

	bool intialized_successfully() const;
};

}