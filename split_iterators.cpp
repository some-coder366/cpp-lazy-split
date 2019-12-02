#include <string_view>
#include <iostream>

struct SplitterEndMark {};

template <class Str>
class SplitterIter
{

	using string_type = Str;
	using size_type = typename string_type::size_type;

	string_type src;
	string_type delim;
	size_type first_pos;
	size_type last_pos;
	mutable bool finished = false;

public:

	SplitterIter(string_type str, string_type separator) noexcept : src{ str }, delim{ separator },
		first_pos{ 0 }, last_pos{ src.find(delim) }
	{}

	SplitterIter& operator++() noexcept
	{
		first_pos = last_pos + delim.size();
		last_pos = src.find(delim, first_pos);
		return *this;
	}

	string_type operator*() const noexcept
	{
		if (last_pos != string_type::npos)
			return src.substr(first_pos, last_pos - first_pos);
		finished = true;
		return src.substr(first_pos, src.size() - first_pos);
	}

	friend constexpr bool operator!=(const SplitterIter& s, SplitterEndMark) noexcept { return !s.finished; }

	friend constexpr bool operator!=(SplitterEndMark, const SplitterIter& s) noexcept { return !s.finished; }

private:

};


template <class Str>
struct SplitterRangeStruct
{
	
	SplitterRangeStruct(Str src, Str delim) noexcept : src{ src }, delim{ delim } {}

	auto begin() const noexcept { return SplitterIter<Str>{ src, delim }; }

	auto end() const noexcept { return SplitterEndMark{}; }

	Str src;
	Str delim;

};

auto SplitView(std::string_view str, std::string_view delim)
{
	return SplitterRangeStruct<std::string_view>{ str, delim };
}

auto SplitView(std::wstring_view str, std::wstring_view delim)
{
	return SplitterRangeStruct<std::wstring_view>{ str, delim };
}

auto SplitView(std::u16string_view str, std::u16string_view delim)
{
	return SplitterRangeStruct<std::u16string_view>{ str, delim };
}

auto SplitView(std::u32string_view str, std::u32string_view delim)
{
	return SplitterRangeStruct<std::u32string_view>{ str, delim };
}


int main(int argc, char ** argv)
{
	std::string tosplitstr = "this**is**some**string**to**split";
	for (auto token : SplitView(tosplitstr, "**"))
		std::cout << token << " ==> " << token.size() << std::endl;
	std::cout << " ====================== " << std::endl;
	std::wstring tosplitwstr = L"but&^%this&^%is&^%another&^%wide&^%string&^%to&^%split&^%";
	for (auto token : SplitView(tosplitwstr, L"&^%"))
		std::wcout << token << " ==> " << token.size() << std::endl;
	std::cout << " ====================== " << std::endl;
	std::string anotherstr = "yet#!another#!string#!to#!split#!";
	
	auto SplitRange = SplitView(anotherstr, "#!"); // string and delim must be valid as far as the SplitRange is still consumed
	
	for (auto token : SplitRange)
		std::cout << token << " ==> " << token.size() << std::endl;
	
	return 0;
}

