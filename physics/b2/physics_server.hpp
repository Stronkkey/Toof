/*  This file is part of the Toof Engine. */
/** @file physics_server.hpp */
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
#ifdef TOOF_B2_ENABLED

#pragma once

#include <servers/physics_server_2d.hpp>

namespace Toof {

class B2PhysicsServer : public PhysicsServer2D {
private:
	std::unique_ptr<WorldType> _create_world() override;
	std::unique_ptr<BodyType> _create_static_body(std::unique_ptr<WorldType> &world_type) override;
	std::unique_ptr<BodyType> _create_kinematic_body(std::unique_ptr<WorldType> &world_type) override;
	std::unique_ptr<BodyType> _create_dynamic_body(std::unique_ptr<WorldType> &world_type) override;
	std::unique_ptr<CapsuleShapeType> _create_capsule_shape(double height, double radius) override;
	std::unique_ptr<CircleShapeType> _create_circle_shape(double radius) override;
	std::unique_ptr<ConcavePolygonShapeType> _create_concave_polygon_shape(std::vector<Vector2f> &&segments) override;
	std::unique_ptr<ConvexPolygonShapeType> _create_convex_polygon_shape(std::vector<Vector2f> &&vertices) override;
	std::unique_ptr<RectShapeType> _create_rect_shape(const Vector2f &size) override;
	std::unique_ptr<SegmentShapeType> _create_segment_shape(const Vector2f &point_a, const Vector2f &point_b) override;
	std::unique_ptr<WorldBoundaryShapeType> _create_world_boundary_shape(double distance, const Vector2f &normal) override;
};

}

#endif
