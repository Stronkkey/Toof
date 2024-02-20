#include <tests/math_tests.hpp>
#include <core/utility_functions.hpp>

#include <unordered_map>
#include <vector>
#include <memory>
#include <cstring>

using namespace sdl::Tests;
using sdl::UtilityFunctions::print;

std::unordered_map<std::string, std::unique_ptr<Test>> tests;

#define PRINT_RETURN(message, return_value) { print(message); return return_value; }

void create_tests() {
	tests.insert({"success", std::make_unique<SuccessTest>()});
	tests.insert({"fail", std::make_unique<FailTest>()});
	tests.insert({"math", std::make_unique<MathTest>()});
	tests.insert({"color", std::make_unique<ColorTest>()});
}

constexpr bool str_same(const char *str1, const char *str2) {
	for (int i = 0; str1[i] != '\0'; i++)
		if (str2[i] == '\0' || str1[i] != str2[i])
			return false;

	return true;
}

bool run_test(const std::unique_ptr<Test> &test) {
	return test->run_test();
}

enum TestRun {
	TEST_RUN_FAILURE = 0,
	TEST_RUN_SUCCESS = 1,
	TEST_RUN_UNKNOWN = 2,
};

TestRun try_test_run(const std::string &name) {
	const auto &iterator = tests.find(name);
	if (iterator != tests.end())
		PRINT_RETURN("Running test \"" + name + "\"", (TestRun)run_test(iterator->second));
	return TEST_RUN_UNKNOWN;
}

int main(const int argc, const char **argv) {
	if (argc < 2)
		PRINT_RETURN("Not enough arguments.", EXIT_FAILURE);
	create_tests();

	TestRun run = try_test_run(argv[1]);
	if (run == TEST_RUN_UNKNOWN)
		PRINT_RETURN("No test ran.", EXIT_FAILURE)
	else if (run == TEST_RUN_SUCCESS)
		print("Test ran succesfully.");
	else
		PRINT_RETURN("Test failed.", EXIT_FAILURE);

	return EXIT_SUCCESS;
}