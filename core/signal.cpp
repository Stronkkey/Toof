#include <algorithm>
#include <core/signal.hpp>

template<typename sig>
void sdl::Signal<sig>::connect(const callable *callable) {
	bound_callables.push_back(callable);
}

template<typename sig>
void sdl::Signal<sig>::disconnect(const callable *callable) {
	auto iterator = std::find(callable, bound_callables.begin(), bound_callables.end());
	if (iterator != bound_callables.end())
		bound_callables.erase(iterator);
}

template<typename sig>
void sdl::Signal<sig>::disconnect_all() {
	bound_callables.clear();
}

template<typename sig>
bool sdl::Signal<sig>::is_connected(const callable *callable) const {
	return std::find(callable, bound_callables.begin(), bound_callables.end()) != bound_callables.end();
}

template<typename sig>
template<typename... args>
void sdl::Signal<sig>::emit(args... arguments) const {
	for (callable *callable: bound_callables)
		callable(arguments...);
}

template<typename sig>
template<typename... args>
void sdl::Signal<sig>::operator()(args... arguments) const {
	emit(arguments...);
}