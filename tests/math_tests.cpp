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
#include <tests/math_tests.hpp>

#include <core/math/math_defs.hpp>
#include <core/math/transform2d.hpp>
#include <core/math/rect2.hpp>
#include <core/math/color.hpp>

using namespace Toof::Tests;

using Transform2D = Toof::Transform2D;
using ColorV = Toof::ColorV;

using Toof::Math::CMP_EPSILON;
using Toof::Math::PI;
using Toof::Math::radians_to_degrees;
using Toof::Math::degrees_to_radians;
using Toof::Math::is_zero_approx;
using Toof::Math::is_equal_approx;

constexpr Transform2D add_transform(const Transform2D &left, const Transform2D &right) {
	Transform2D transform;
	transform.origin = (left.origin + right.origin);
	transform.rotation = (left.rotation + right.rotation);
	transform.scale = (left.scale + right.scale);
	return transform;
}

constexpr Transform2D subtract_transform(const Transform2D &left, const Transform2D &right) {
	Transform2D transform;
	transform.origin = (left.origin - right.origin);
	transform.rotation = (left.rotation - right.rotation);
	transform.scale = (left.scale - right.scale);
	return transform;
}

bool ColorTest::_test() {
//	TEST_CASE(Color(182, 44, 125, 157).blend(Color(241, 208, 27, 23)) == Color(193, 73, 107, 168));
	return true;
}

bool MathTest::_test() {
	TEST_CASE(radians_to_degrees(PI) == 180.0);
	TEST_CASE(degrees_to_radians(180.0) == PI);

	TEST_CASE(is_zero_approx(0.0 - CMP_EPSILON));
	TEST_CASE(is_zero_approx(0.0 + CMP_EPSILON));
	TEST_CASE(is_equal_approx(1, 1.0 - CMP_EPSILON));
	TEST_CASE(is_equal_approx(1, 1.0 + CMP_EPSILON));

	return true;
}