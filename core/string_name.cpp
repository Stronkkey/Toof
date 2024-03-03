#include <core/string_name.hpp>

#include <stdexcept>

using String = sdl::String;
using StringName = sdl::StringName;

std::unordered_set<StringName::__String_Storer__> StringName::stored_strings = {};
std::unordered_set<StringName::__String_Saver__> StringName::strings = {};

StringName::StringName(): saved_string(allocate_string("")) {
}

StringName::StringName(const_reference string): saved_string(allocate_string(string)) {
}

StringName::~StringName() {
}

const StringName::CharT &StringName::operator[](const size_type index) const {
	return (*saved_string)[index];
}

const StringName::CharT &StringName::at(const size_type index) const {
	return saved_string->at(index);
}

void StringName::set_string(const_reference new_string) {
	if (saved_string == new_string)
		return;

	saved_string = allocate_string(new_string);
}

StringName::__String_Saver__ StringName::allocate_string(const_reference string) const {
	auto iterator = stored_strings.find(string);
	if (iterator != stored_strings.end())
		return iterator._M_cur->_M_v();

	return stored_strings.insert(string).first._M_cur->_M_v();
}

StringName::const_reference StringName::get_string() const {
	return *saved_string;
}

const String *StringName::get_string_ptr() const {
	return saved_string.stored_string.string.get();
}

StringName::operator String() const {
	return *saved_string;
}

const StringName::CharT &StringName::front() const {
	return saved_string->front();
}

const StringName::CharT &StringName::back() const {
	return saved_string->back();
}

const StringName::CharT *StringName::data() const {
	return saved_string->data();
}

StringName::size_type StringName::size() const {
	return saved_string->size();
}

StringName::size_type StringName::length() const {
	return saved_string->length();
}

StringName::size_type StringName::max_size() const {
	return saved_string->max_size();
}

bool StringName::empty() const {
	return saved_string->empty();
}

void StringName::remove_prefix(const size_type n) {
	value_type str = *saved_string;
	if (n <= str.size())
		str.resize(str.size() - n);
	saved_string = allocate_string(std::move(str));
}

void StringName::remove_suffix(const size_type n) {
	value_type str = *saved_string;
	if (n <= str.size())
		str.erase(0, n);
	saved_string = allocate_string(std::move(str));
}

void StringName::swap(StringName &string_name) {
	__String_Saver__ temp = std::move(saved_string);
	saved_string = std::move(string_name.saved_string);
	string_name.saved_string = std::move(temp);
}

StringName::size_type StringName::copy(CharT *dest, const size_type count, const size_type pos) const {
	const size_type final_size = std::min(count, saved_string->size() - pos);
	if (pos > saved_string->size())
		throw std::out_of_range("terminate called after throwing an instance of 'std::out_of_range'");
	
	traits_type::copy(dest, saved_string->data() + pos, final_size);
	return final_size;
}

StringName StringName::substr(const size_type pos, const size_type count) const {
	return saved_string->substr(pos, count);
}

int StringName::compare(const StringName &string_name) const {
	return saved_string->compare(*string_name.saved_string);
}

StringName::size_type StringName::find(const StringName &string_name, const size_type pos) const {
	return saved_string->find(*string_name.saved_string, pos);
}

StringName::size_type StringName::find(const CharT character, const size_type pos) const {
	return saved_string->find(character, pos);
}

StringName::size_type StringName::find(const CharT *string, const size_type pos, const size_type count) const {
	return saved_string->find(string, pos, count);
}

StringName::size_type StringName::find(const CharT *string, const size_type pos) const {
	return saved_string->find(string, pos);
}

StringName::size_type StringName::rfind(const StringName &string_name, const size_type pos) const {
	return saved_string->rfind(*string_name.saved_string, pos);
}

StringName::size_type StringName::rfind(const CharT character, const size_type pos) const {
	return saved_string->rfind(character, pos);
}

StringName::size_type StringName::rfind(const CharT *string, const size_type pos, const size_type count) const {
	return saved_string->rfind(string, pos, count);
}

StringName::size_type StringName::rfind(const CharT *string, const size_type pos) const {
	return saved_string->rfind(string, pos);
}

StringName::size_type StringName::find_first_of(const StringName &string_name, const size_type pos) const {
	return saved_string->find_first_of(*string_name.saved_string, pos);
}

StringName::size_type StringName::find_first_of(const CharT character, const size_type pos) const {
	return saved_string->find_first_of(character, pos);
}

StringName::size_type StringName::find_first_of(const CharT *string, const size_type pos, const size_type count) const {
	return saved_string->find_first_of(string, pos, count);
}

StringName::size_type StringName::find_first_of(const CharT *string, const size_type pos) const {
	return saved_string->find_first_of(string, pos);
}

StringName::size_type StringName::find_last_of(const StringName &string_name, const size_type pos) const {
	return saved_string->find_last_of(*string_name.saved_string, pos);
}

StringName::size_type StringName::find_last_of(const CharT character, const size_type pos) const {
	return saved_string->find_last_of(character, pos);
}

StringName::size_type StringName::find_last_of(const CharT *string, const size_type pos, const size_type count) const {
	return saved_string->find_last_of(string, pos, count);
}

StringName::size_type StringName::find_last_of(const CharT *string, const size_type pos) const {
	return saved_string->find_last_of(string, pos);
}

StringName::size_type StringName::find_first_not_of(const StringName &string_name, const size_type pos) const {
	return saved_string->find_first_not_of(*string_name.saved_string, pos);
}

StringName::size_type StringName::find_first_not_of(const CharT character, const size_type pos) const {
	return saved_string->find_first_not_of(character, pos);
}

StringName::size_type StringName::find_first_not_of(const CharT *string, const size_type pos, const size_type count) const {
	return saved_string->find_first_not_of(string, pos, count);
}

StringName::size_type StringName::find_first_not_of(const CharT *string, const size_type pos) const {
	return saved_string->find_first_not_of(string, pos);
}

StringName::size_type StringName::find_last_not_of(const StringName &string_name, const size_type pos) const {
	return saved_string->find_last_not_of(*string_name.saved_string, pos);
}

StringName::size_type StringName::find_last_not_of(const CharT character, const size_type pos) const {
	return saved_string->find_last_not_of(character, pos);
}

StringName::size_type StringName::find_last_not_of(const CharT *string, const size_type pos, const size_type count) const {
	return saved_string->find_last_not_of(string, pos, count);
}

StringName::size_type StringName::find_last_not_of(const CharT *string, const size_type pos) const {
	return saved_string->find_last_not_of(string, pos);
}

void StringName::operator=(const StringName &string_name) {
	saved_string = string_name.saved_string;
}

void StringName::operator=(const_reference string) {
	saved_string = allocate_string(string);
}

void StringName::operator+=(const_reference string) {
	saved_string = allocate_string(*saved_string + string);
}

void StringName::operator+=(const StringName &string_name) {
	saved_string = allocate_string(*saved_string + *string_name.saved_string);
}

StringName StringName::operator+(const_reference string) const {
	return StringName(*saved_string + string);
}

StringName StringName::operator+(const StringName &string_name) const {
	return StringName(*saved_string.stored_string.string + *string_name.saved_string.stored_string.string);
}

bool StringName::operator==(const StringName &right) const {
	return (*saved_string == *right.saved_string);
}

bool StringName::operator!=(const StringName &right) const {
	return (*saved_string != *right.saved_string);
}

bool StringName::operator<(const StringName &right) const {
	return (*saved_string < *right.saved_string);
}

bool StringName::operator>(const StringName &right) const {
	return (*saved_string > *right.saved_string);
}

bool StringName::operator<=(const StringName &right) const {
	return (*saved_string <= *right.saved_string);
}
bool StringName::operator>=(const StringName &right) const {
	return (*saved_string >= *right.saved_string);
}
	
StringName::__os_type__ &operator<<(StringName::__os_type__ &left, const StringName &right) {
	return (left << right.get_string());
}
