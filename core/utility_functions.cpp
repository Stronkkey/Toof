#include <core/math/color.hpp>
#include <core/math/rect2.hpp>
#include <core/math/transform2d.hpp>
#include <core/math/vector2.hpp>
#include <core/utility_functions.hpp>
#include <items/item.hpp>

#include <SDL_timer.h>

#include <iostream>

using namespace sdl;

real_t UtilityFunctions::get_passed_time() {
	real_t time = SDL_GetTicks64();
	time *= 0.001;
	return time;
}

std::string UtilityFunctions::to_string(const std::any &variant) {
	const std::type_info &type_info = variant.type();

	// Ouch

	if (type_info == typeid(int))
		return std::to_string(std::any_cast<int>(variant));

	if (type_info == typeid(long))
		return std::to_string(std::any_cast<long>(variant));

	if (type_info == typeid(float))
		return std::to_string(std::any_cast<float>(variant));

	if (type_info == typeid(double))
		return std::to_string(std::any_cast<double>(variant));

	if (type_info == typeid(long long))
		return std::to_string(std::any_cast<long long>(variant));

	if (type_info == typeid(long double))
		return std::to_string(std::any_cast<long double>(variant));

	if (type_info == typeid(unsigned int))
		return std::to_string(std::any_cast<unsigned int>(variant));

	if (type_info == typeid(unsigned long))
		return std::to_string(std::any_cast<unsigned long>(variant));

	if (type_info == typeid(unsigned long long))
		return std::to_string(std::any_cast<unsigned long long>(variant));

	if (type_info == typeid(std::string))
		return std::any_cast<std::string>(variant);

	if (type_info == typeid(char)) {
		char character = std::any_cast<char>(variant);
		return std::string(&character, 1);
	}

	if (type_info == typeid(Vector2))
		return std::any_cast<Vector2>(variant).to_string();

	if (type_info == typeid(Vector2i))
		return std::any_cast<Vector2i>(variant).to_string();

	if (type_info == typeid(Rect2))
		return std::any_cast<Rect2>(variant).to_string();

	if (type_info == typeid(Rect2i))
		return std::any_cast<Rect2i>(variant).to_string();

	if (type_info == typeid(Color))
		return std::any_cast<Color>(variant).to_string();

	if (type_info == typeid(Transform2D))
		return std::any_cast<Transform2D>(variant).to_string();

	if (type_info == typeid(int*))
		return std::to_string(*std::any_cast<int*>(variant));

	if (type_info == typeid(long*))
		return std::to_string(*std::any_cast<long*>(variant));

	if (type_info == typeid(float*))
		return std::to_string(*std::any_cast<float*>(variant));

	if (type_info == typeid(double*))
		return std::to_string(*std::any_cast<double*>(variant));

	if (type_info == typeid(long long*))
		return std::to_string(*std::any_cast<long long*>(variant));

	if (type_info == typeid(long double*))
		return std::to_string(*std::any_cast<long double*>(variant));

	if (type_info == typeid(unsigned int*))
		return std::to_string(*std::any_cast<unsigned int*>(variant));

	if (type_info == typeid(unsigned long*))
		return std::to_string(*std::any_cast<unsigned long*>(variant));

	if (type_info == typeid(unsigned long long*))
		return std::to_string(*std::any_cast<unsigned long long*>(variant));

	if (type_info == typeid(std::string*))
		return *std::any_cast<std::string*>(variant);

	if (type_info == typeid(char*))
		return std::any_cast<char*>(variant);

	if (type_info == typeid(Vector2*))
		return std::any_cast<Vector2*>(variant)->to_string();

	if (type_info == typeid(Vector2i*))
		return std::any_cast<Vector2i*>(variant)->to_string();

	if (type_info == typeid(Rect2*))
		return std::any_cast<Rect2*>(variant)->to_string();

	if (type_info == typeid(Rect2i*))
		return std::any_cast<Rect2i*>(variant)->to_string();

	if (type_info == typeid(Color*))
		return std::any_cast<Color*>(variant)->to_string();

	if (type_info == typeid(Transform2D*))
		return std::any_cast<Transform2D*>(variant)->to_string();

	if (type_info == typeid(Item*))
		return std::any_cast<Item*>(variant)->get_name() + ":<" + typeid(Item*).name() + ">";

	if (type_info == typeid(const int*))
		return std::to_string(*std::any_cast<const int*>(variant));

	if (type_info == typeid(const long*))
		return std::to_string(*std::any_cast<const long*>(variant));

	if (type_info == typeid(const float*))
		return std::to_string(*std::any_cast<const float*>(variant));

	if (type_info == typeid(const double*))
		return std::to_string(*std::any_cast<const double*>(variant));

	if (type_info == typeid(const long long*))
		return std::to_string(*std::any_cast<const long long*>(variant));

	if (type_info == typeid(const long double*))
		return std::to_string(*std::any_cast<const long double*>(variant));

	if (type_info == typeid(const unsigned int*))
		return std::to_string(*std::any_cast<const unsigned int*>(variant));

	if (type_info == typeid(const unsigned long*))
		return std::to_string(*std::any_cast<const unsigned long*>(variant));

	if (type_info == typeid(const unsigned long long*))
		return std::to_string(*std::any_cast<const unsigned long long*>(variant));

	if (type_info == typeid(const std::string*))
		return *std::any_cast<const std::string*>(variant);

	if (type_info == typeid(const char*))
		return std::any_cast<const char*>(variant);

	if (type_info == typeid(const Vector2*))
		return std::any_cast<const Vector2*>(variant)->to_string();

	if (type_info == typeid(const Vector2i*))
		return std::any_cast<const Vector2i*>(variant)->to_string();

	if (type_info == typeid(const Rect2*))
		return std::any_cast<const Rect2*>(variant)->to_string();

	if (type_info == typeid(const Rect2i*))
		return std::any_cast<const Rect2i*>(variant)->to_string();

	if (type_info == typeid(const Color*))
		return std::any_cast<const Color*>(variant)->to_string();

	if (type_info == typeid(const Transform2D*))
		return std::any_cast<const Transform2D*>(variant)->to_string();

	if (type_info == typeid(const Item*))
		return std::any_cast<const Item*>(variant)->get_name() + ":<" + typeid(const Item*).name() + ">";

	return "";
}

void UtilityFunctions::print(const std::any &variant) {
	std::cout << to_string(variant) + "\n";
}

void UtilityFunctions::print(const std::initializer_list<std::any> &variants) {
	for (const std::any &element: variants)
		std::cout << to_string(element);
	std::cout << "\n";
}

void UtilityFunctions::print_err(const std::any &variant) {
	std::cerr << to_string(variant) + "\n";
}

void UtilityFunctions::print_err(const std::initializer_list<std::any> &variants) {
	for (const std::any &element: variants)
		std::cerr << to_string(element);
	std::cerr << "\n";
}