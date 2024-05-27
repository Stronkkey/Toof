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
#include <core/utility_functions.hpp>

#include <unordered_map>
#include <memory>

using namespace Toof::Tests;

std::unordered_map<Toof::String, std::unique_ptr<Test>> tests;

#define PRINT_RETURN(message, return_value) { PRINT_LINE(message); return return_value; }

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

TestRun try_test_run(const Toof::String &name) {
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
	else if (run == TEST_RUN_SUCCESS) {
		PRINT_LINE("Test ran succesfully.");
	} else
		PRINT_RETURN("Test failed.", EXIT_FAILURE);

	return EXIT_SUCCESS;
}