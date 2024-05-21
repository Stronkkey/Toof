#include <tests/base_tests.hpp>
#include <core/utility_functions.hpp>

#include <memory>

using namespace Toof::Tests;

bool SuccessTest::_test() {
	TEST_CASE(true); // Should not fail
	return true;
}

bool FailTest::_test() {
	TEST_CASE(false); // Should fail
	return true;
}

void Test::_test_fail(const String &message) {
	if (message == "")
		return;
	PRINT_LINE(message);
}

bool Test::run_test() {
	return _test();
}
