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
#ifdef TOOF_PHYSICS_ENABLED

#include <scene/2d/physics/physics_body2d.hpp>
#include <scene/main/scene_tree.hpp>
#include <servers/physics_server.hpp>

void Toof::PhysicsBody2D::ready() {
	physics_body_rid = get_physics_server()->body_create();
}

void Toof::PhysicsBody2D::_notification(const int what) {
	Node2D::_notification(what);

	if (what == NOTIFICATION_READY)
		ready();
}

const std::unique_ptr<Toof::PhysicsServer2D> &Toof::PhysicsBody2D::get_physics_server() const {
	if (is_inside_tree())
		return get_tree()->get_physics_server();

	std::unique_ptr<PhysicsServer2D> _p;
	std::unique_ptr<PhysicsServer2D> *p = &_p;
	return *p;
}

void Toof::PhysicsBody2D::add_collision_exception_with(const PhysicsBody2D*) {
}

void Toof::PhysicsBody2D::remove_collision_exception_with(const PhysicsBody2D*) {
}

#endif