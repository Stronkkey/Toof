#pragma once

#include <core/string_def.hpp>

#include <memory>
#include <unordered_set>

namespace sdl {

class StringName {
public:
	using traits_type = String::traits_type;
	using value_type = String;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using CharT = String::value_type;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

public:
	struct __String_Storer__ {
		std::shared_ptr<String> string;

		__String_Storer__() = default;
		__String_Storer__(const_reference string) {
			this->string = std::make_shared<String>(string);
		}

		bool operator==(const __String_Storer__ &string_storer) const {
			return *string == *string_storer.string;
		}
	};

	struct __String_Saver__ {
		__String_Storer__ stored_string;

		__String_Saver__() = default;
		__String_Saver__(const __String_Storer__ &string_storer): stored_string(string_storer) {
		}

		bool operator==(const __String_Storer__ &string_saver) const {
			return stored_string.string.get() == string_saver.string.get();
		}

		const_pointer operator->() const {
			return stored_string.string.get();
		}

		pointer operator->() {
			return stored_string.string.get();
		}

		const_reference operator*() const {
			return *stored_string.string;
		}

		reference operator*() {
			return *stored_string.string;
		}

		bool operator==(const_reference string) const {
			return *this->stored_string.string == string;
		}
	};

	struct ConstIterator {
    	using iterator_category = std::bidirectional_iterator_tag;
		using value_type = char;
		using difference_type = std::ptrdiff_t;
		using reference = const value_type&;
		using pointer = const value_type*;

		constexpr ConstIterator(pointer ptr): ptr(ptr) {}

		constexpr reference operator*() const {
			return *ptr;
		}

		constexpr pointer operator->() const {
			return ptr;
		}

		constexpr ConstIterator &operator++() {
			ptr++;
			return *this;
		}

		constexpr ConstIterator operator++(int) {
			ConstIterator tmp = *this;
			++(*this);
			return tmp;
		}

		constexpr ConstIterator &operator--() {
			ptr--;
			return *this;
		}

		constexpr ConstIterator operator--(int) {
			ConstIterator tmp = *this;
			--(*this);
			return tmp;
		}

		friend bool operator==(const ConstIterator &left, const ConstIterator &right) {
			return left.ptr == right.ptr;
		}

		friend bool operator!=(const ConstIterator &left, const ConstIterator &right) {
			return left.ptr != right.ptr;
		}

		private:
			pointer ptr;
	};

public:
	using const_iterator = ConstIterator;
	using iterator = ConstIterator;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	static constexpr size_type npos = size_type(-1);

private:
	static std::unordered_set<__String_Storer__> stored_strings;
	static std::unordered_set<__String_Saver__> strings;
	__String_Saver__ saved_string;

	void set_string(const_reference new_string);
	__String_Saver__ allocate_string(const_reference string) const;
	
public:
	StringName();
	StringName(const_reference string);

	~StringName();

		inline iterator begin() const noexcept {
		return saved_string.stored_string.string->data();
	}

	inline const_iterator cbegin() const noexcept {
		return saved_string->data();
	}

	inline iterator end() const noexcept {
		return (saved_string->data() + saved_string->size());
	}

	inline const_iterator cend() const noexcept {
		return (saved_string->data() + saved_string->size());
	}

	inline reverse_iterator rbegin() const noexcept {
		return reverse_iterator(iterator(&saved_string->back() + 1));
	}

	inline const_reverse_iterator crbegin() const noexcept {
		return const_reverse_iterator(iterator(&saved_string->back() + 1));
	}

	inline reverse_iterator rend() const noexcept {
		return reverse_iterator(iterator(saved_string->data()));
	}

	inline const_reverse_iterator crend() const noexcept {
		return const_reverse_iterator(iterator(saved_string->data()));
	}

	const CharT &operator[](const size_type index) const;
	const CharT &at(const size_type index) const;

	operator String() const;

	[[nodiscard]] const_reference get_string() const;
	[[nodiscard]] const_pointer get_string_ptr() const;

	[[nodiscard]] const CharT &front() const;
	[[nodiscard]] const CharT &back() const;
	[[nodiscard]] const CharT *data() const;

	[[nodiscard]] size_type size() const;
	[[nodiscard]] size_type length() const;
	[[nodiscard]] size_type max_size() const;
	[[nodiscard]] bool empty() const;

	void remove_prefix(const size_type n);
	void remove_suffix(const size_type n);
	void swap(StringName &string_name);

	size_type copy(CharT *dest, const size_type count, const size_type pos = 0) const;
	StringName substr(const size_type pos = 0, const size_type count = npos) const;
	int compare(const StringName &string_name) const;

	size_type find(const StringName &string_name, const size_type pos = 0) const;
	size_type find(const CharT character, const size_type pos = 0) const;
	size_type find(const CharT *string, const size_type pos, const size_type count) const;
	size_type find(const CharT *string, const size_type pos = 0) const;

	size_type rfind(const StringName &string_name, const size_type pos = npos) const;
	size_type rfind(const CharT character, const size_type pos = npos) const;
	size_type rfind(const CharT *string, const size_type pos, const size_type count) const;
	size_type rfind(const CharT *string, const size_type pos = npos) const;

	size_type find_first_of(const StringName &string_name, const size_type pos = 0) const;
	size_type find_first_of(const CharT character, const size_type pos = 0) const;
	size_type find_first_of(const CharT *string, const size_type pos, const size_type count) const;
	size_type find_first_of(const CharT *string, const size_type pos = 0) const;

	size_type find_last_of(const StringName &string_name, const size_type pos = npos) const;
	size_type find_last_of(const CharT character, const size_type pos = npos) const;
	size_type find_last_of(const CharT *string, const size_type pos, const size_type count) const;
	size_type find_last_of(const CharT *string, const size_type pos = npos) const;

	size_type find_first_not_of(const StringName &string_name, const size_type pos = 0) const;
	size_type find_first_not_of(const CharT character, const size_type pos = 0) const;
	size_type find_first_not_of(const CharT *string, const size_type pos, const size_type count) const;
	size_type find_first_not_of(const CharT *string, const size_type pos = 0) const;

	size_type find_last_not_of(const StringName &string_name, const size_type pos = npos) const;
	size_type find_last_not_of(const CharT character, const size_type pos = npos) const;
	size_type find_last_not_of(const CharT *string, const size_type pos, const size_type count) const;
	size_type find_last_not_of(const CharT *string, const size_type pos = npos) const;

	void operator=(const StringName &string_name);
	void operator=(const_reference string);

	void operator+=(const_reference string);
	void operator+=(const StringName &string_name);

	StringName operator+(const_reference string) const;
	StringName operator+(const StringName &string_name) const;

	bool operator==(const StringName &right) const;
	bool operator!=(const StringName &right) const;
	bool operator<(const StringName &right) const;
	bool operator>(const StringName &right) const;
	bool operator<=(const StringName &right) const;
	bool operator>=(const StringName &right) const;
	
	typedef std::basic_ostream<String::value_type, String::traits_type> __os_type__;
	friend __os_type__ &operator<<(__os_type__ &left, const StringName &right);
};

namespace literals {

inline StringName operator""_sn(const char *string, const size_t length) {
	return StringName(String(string, length));
}

}

}

template<>
struct std::hash<sdl::StringName::__String_Storer__> {
	size_t operator()(const sdl::StringName::__String_Storer__ &string_storer) const noexcept {
		return hash<sdl::String>()(*string_storer.string);
	}
};

template<>
struct std::hash<sdl::StringName::__String_Saver__> {
	size_t operator()(const sdl::StringName::__String_Saver__ &string_saver) const noexcept {
		return hash<sdl::String>()(*string_saver.stored_string.string);
	}
};

template<>
struct std::hash<sdl::StringName> {
	size_t operator()(const sdl::StringName &string_name) const noexcept {
		return hash<sdl::String>()(string_name.get_string());
	}
};
