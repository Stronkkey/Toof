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
#include <servers/rendering/2d/canvas_item.hpp>
#include <servers/rendering/2d/drawing_item.hpp>

using namespace Toof;

#define __EXPIRED_CHECK__ if (parent.expired()) {parent.reset(); return; }

void detail::CanvasItem::set_global_transform() {
	__EXPIRED_CHECK__

	global_transform = transform;
	std::shared_ptr<CanvasItem> parent_canvas_item = parent.lock();

	while (parent_canvas_item) {
		global_transform *= parent_canvas_item->transform;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

void detail::CanvasItem::set_global_modulate() {
	__EXPIRED_CHECK__

	global_modulate = modulate;
	std::shared_ptr<CanvasItem> parent_canvas_item = parent.lock();

	while (parent_canvas_item) {
		global_modulate *= parent_canvas_item->modulate;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

void detail::CanvasItem::set_global_visible() {
	__EXPIRED_CHECK__

	if (!visible) {
		global_visible = false;
		return;
	}

	global_visible = true;
	std::shared_ptr<CanvasItem> parent_canvas_item = parent.lock();

	while (parent_canvas_item && global_visible) {
		global_visible = parent_canvas_item->visible;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

void detail::CanvasItem::set_global_zindex() {
	__EXPIRED_CHECK__

	if (!zindex_relative) {
		global_zindex = zindex;
		return;
	}

	std::shared_ptr<CanvasItem> parent_canvas_item = parent.lock();
	global_zindex = zindex;

	while (parent_canvas_item) {
		global_zindex += parent_canvas_item->zindex;
		parent_canvas_item = parent_canvas_item->parent.lock();
	}
}

const Transform2D &detail::CanvasItem::get_global_transform() {
	set_global_transform();
	return global_transform;
}

const ColorV &detail::CanvasItem::get_global_modulate() {
	set_global_modulate();
	return global_modulate;
}

bool detail::CanvasItem::is_globally_visible() {
	set_global_visible();
	return global_visible;
}

int detail::CanvasItem::get_global_zindex() {
	set_global_zindex();
	return global_zindex;
}