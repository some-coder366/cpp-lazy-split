#include <experimental/generator>
#include <string_view>
#include <iostream>

std::experimental::generator<std::wstring_view> CoSplit(std::wstring_view str, std::wstring_view delim)
{
	std::wstring_view::size_type start_pos = 0;
	for (auto end_pos = str.find(delim);
		end_pos != std::wstring_view::npos;
		start_pos = end_pos + delim.length(), end_pos = str.find(delim, start_pos))
		co_yield str.substr(start_pos, end_pos - start_pos);
	co_yield str.substr(start_pos, str.length() - start_pos);
}

std::experimental::generator<std::string_view> CoSplit(std::string_view str, std::string_view delim)
{
	std::string_view::size_type start_pos = 0;
	for (auto end_pos = str.find(delim);
		end_pos != std::string_view::npos;
		start_pos = end_pos + delim.length(), end_pos = str.find(delim, start_pos))
		co_yield str.substr(start_pos, end_pos - start_pos);
	co_yield str.substr(start_pos, str.length() - start_pos);
}

std::experimental::generator<std::u16string_view> CoSplit(std::u16string_view str, std::u16string_view delim)
{
	std::u16string_view::size_type start_pos = 0;
	for (auto end_pos = str.find(delim);
		end_pos != std::u16string_view::npos;
		start_pos = end_pos + delim.length(), end_pos = str.find(delim, start_pos))
		co_yield str.substr(start_pos, end_pos - start_pos);
	co_yield str.substr(start_pos, str.length() - start_pos);
}

std::experimental::generator<std::u32string_view> CoSplit(std::u32string_view str, std::u32string_view delim)
{
	std::u32string_view::size_type start_pos = 0;
	for (auto end_pos = str.find(delim);
		end_pos != std::u32string_view::npos;
		start_pos = end_pos + delim.length(), end_pos = str.find(delim, start_pos))
		co_yield str.substr(start_pos, end_pos - start_pos);
	co_yield str.substr(start_pos, str.length() - start_pos);
}


int main(int argc, char ** argv)
{
	std::string tosplitstr = "this**is**some**string**to**split";
	for (auto token : CoSplit(tosplitstr, "**"))
		std::cout << token << " ==> " << token.size() << std::endl;
	std::cout << " ====================== " << std::endl;
	std::wstring tosplitwstr = L"but&^%this&^%is&^%another&^%wide&^%string&^%to&^%split&^%";
	for (auto token : CoSplit(tosplitwstr, L"&^%"))
		std::wcout << token << " ==> " << token.size() << std::endl;
	std::cout << " ====================== " << std::endl;
	std::string anotherstr = "yet#!another#!string#!to#!split#!";
	
	auto SplitRange = CoSplit(anotherstr, "#!"); // string and delim must be valid as far as the SplitRange is still consumed
	
	for (auto token : SplitRange)
		std::cout << token << " ==> " << token.size() << std::endl;
	
	return 0;
}
