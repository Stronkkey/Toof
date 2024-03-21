#include <servers/rendering/window.hpp>
#include <servers/rendering_server.hpp>

#include <SDL.h>
#include <SDL_image.h>

using namespace sdl;

Window::InitilizationStatus Window::initialized = Window::NOT_INITIALIZED;

Window::Window() : window_title("Window"), window_rect(Rect2i(0, 0, 320, 240)) {
	try_initialize();
	if (!intialized_successfully())
		return;

	window = SDL_CreateWindow(window_title.c_str(),
	    window_rect.x,
	    window_rect.y,
	    window_rect.w,
	    window_rect.h,
	    SDL_WINDOW_RESIZABLE);
}

Window::~Window() {
	SDL_DestroyWindow(window);
}

void Window::try_initialize() {
	if (initialized != NOT_INITIALIZED)
		return;

	const bool sdl_init_success = SDL_Init(SDL_INIT_VIDEO) == 0;
	const bool sdl_img_success = IMG_Init(IMG_INIT_PNG) != 0;

	if (!sdl_init_success)
		fail_with_message("Couldn't initialize SDL.", SDL_LOG_CATEGORY_APPLICATION);

	if (!sdl_img_success)
		fail_with_message("Couldn't initialize SDL_Image.", SDL_LOG_CATEGORY_APPLICATION);

	if (initialized == INITILIZATION_FAILED)
		return;

	initialized = INITIALIZED;
}

void Window::fail_with_message(const String &message, const SDL_LogCategory category) {
	const String aborting_string = " Aborting...";

	SDL_LogCritical(category, (message + aborting_string).c_str(), SDL_GetError());
	initialized = INITILIZATION_FAILED;
}

bool Window::intialized_successfully() const {
	return initialized == INITIALIZED;
}

void Window::set_window_rect(const Rect2i &window_rect) {
	this->window_rect = window_rect;
	if (window) {
		SDL_SetWindowPosition(window, window_rect.x, window_rect.y);
		SDL_SetWindowSize(window, window_rect.w, window_rect.h);
	}
}

void Window::set_window_title(const String &new_title) {
	window_title = new_title;
	if (window)
		SDL_SetWindowTitle(window, window_title.c_str());
}

int Window::get_refresh_rate() const {
  const int display_index = SDL_GetWindowDisplayIndex(window);
  SDL_DisplayMode mode;
  SDL_GetDisplayMode(display_index, 0, &mode);
  return mode.refresh_rate;
}