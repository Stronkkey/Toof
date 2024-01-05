#pragma once

#include <vector>

namespace sdl {

template<typename sig>
class Signal {

typedef sig callable;

private:
	std::vector<callable*> bound_callables;

public:
	void connect(const callable *callable);
	void disconnect(const callable *callable);
	void disconnect_all();
	bool is_connected(const callable *callable) const;

	template<typename... args>
	void emit(args... arguments) const;

	template<typename... args>
	void operator()(args... arguments) const;
};

}