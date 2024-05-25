/*  This file is part of the Toof Engine. */
/*
  BSD 3-Clause License

  Copyright (c) 2024-present, Stronkkey and Contributors

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <servers/rendering/window.hpp>
#include <servers/rendering_server.hpp>

#include <SDL.h>
#include <SDL_image.h>

using namespace Toof;

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