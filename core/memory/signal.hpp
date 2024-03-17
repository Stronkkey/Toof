#pragma once

#include <algorithm>
#include <optional>
#include <set>
#include <functional>
#include <unordered_map>
#include <list>

namespace sdl {

template<class, class...>
struct __Function_Storer__;

template<class R, class... Args>
struct __Function_Storer__ {
	using __Container_Iterator__ = typename std::list<__Function_Storer__>::iterator;
	using __Signature__ = R(Args...);
	using __Function_Ptr__ = R(*)(Args...);
	using __Function__ = std::function<__Signature__>;
	using __index__ = __Container_Iterator__;

	__Function__ function;

	__Function_Storer__(): function(nullptr) {
	}

	__Function_Storer__(const __Function__ &function): function(function) {
	}

	__Function_Storer__(__Function_Storer__&&) = default;
	__Function_Storer__(const __Function_Storer__ &right) = default;

	bool operator==(const __Function_Storer__ &storer) const {
		return (*function.template target<__Function_Ptr__>()) == (*storer.function.template target<__Function_Ptr__>());
	}
};

template<class>
class Signal;

/**
* A type representing a signal using the observer pattern.
*/
template<class R, class... Args>
class Signal<R(Args...)> {
private:
	using __Stored_Function__ = __Function_Storer__<R, Args...>;
	using __Container_Type__ = std::list<__Stored_Function__>;

	__Container_Type__ iterate_callables = {};
	std::unordered_map<__Stored_Function__, typename __Container_Type__::iterator> search_callables = {};
public:
	using Signature = R(Args...);
	using Callable = std::function<Signature>;
	using ReturnValue = R;

	Signal() = default;
	~Signal() = default;

	/**
	* @returns true if the @param callable is connected.
	*/
	bool is_connected(const Callable &callable) const {
		return search_callables.count(callable);
	}

	/**
	* Connects this signal to the @param callable.
	* @note a signal can only be connected once to the same Callable.
	* @see also is_connected.
	*/
	void connect(const Callable &callable) {
		if (search_callables.count(callable))
			return;

		iterate_callables.push_back(callable);
		search_callables.insert({callable, --iterate_callables.end()});
	}

	/**
	* Disconnects this signal from the specified Callable. Does nothing if the connection does not exist.
	* @see also is_connected.
	*/
	void disconnect(const Callable &callable) {
		const auto &iterator = search_callables.find(callable);
		if (iterator != search_callables.end()) {
			iterate_callables.erase(iterator->second);
			search_callables.erase(iterator->first);
		}
	}

	/**
	* Emits this signal. 
	* All Callables connected to this signal will be triggered with the paremters of @param args (if any parameters are required).
	*/
	void operator()(const Args&... args) {
		for (const auto &callable: iterate_callables)
			callable.function(args...);
	}

	/**
	* @returns an Array of connections for this signal.
	*/
	std::vector<Callable> get_connections() const {
		const size_t callable_size = iterate_callables.size();
		auto callables = std::vector<Callable>(callable_size);
		size_t i = 0;

		for (const auto &iterator: iterate_callables)
			callables[i++] = iterator.function;

		return callables;
	}
};

}

template<class R, class... Args>
struct std::hash<sdl::__Function_Storer__<R, Args...>> {
	using __T__ = sdl::__Function_Storer__<R, Args...>;
	using __Function_Pointer__ = R(*)(Args...);

	size_t operator()(const __T__ &storer) const noexcept {
		const auto &ptr = storer.function.template target<__Function_Pointer__>();

		return std::hash<__Function_Pointer__>{}(ptr ? *ptr : nullptr);
	}
};
