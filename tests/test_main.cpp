#include <core/utility_functions.hpp>
#include <tests/test_geometry2d.hpp>

int main() {
	#ifdef GEOMETRY_2D_TESTS
	bool geometry2d_test = sdl::Tests::test_geometry2d();
	if (geometry2d_test)
		return geometry2d_test ? 0 : 1;
	#endif

	sdl::UtilityFunctions::print("All tests passed!");
	return 0;
}