/*  This file is part of the Toof Engine. */
/** @file window.hpp */
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
