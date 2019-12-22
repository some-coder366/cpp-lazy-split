#pragma once
#include "LibBase.h"
#include <string_view>

namespace LIB_NAMESPACE
{


	template <class Str>
	class split_range_struct
	{

	public:

		struct splitter_end_mark {};

		class iterator
		{
			using string_type = Str;
			using size_type = typename string_type::size_type;

		public:

			iterator(string_type str, string_type separator) noexcept : src{ str }, delim{ separator },
				first_pos{ 0 }, last_pos{ src.find(delim) }
			{}

			iterator& operator++() noexcept
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

			friend constexpr bool operator!=(const iterator& iter, splitter_end_mark) noexcept { return !iter.finished; }

			friend constexpr bool operator!=(splitter_end_mark, const iterator& iter) noexcept { return !iter.finished; }

		private:

			string_type src;
			string_type delim;
			size_type first_pos;
			size_type last_pos;
			mutable bool finished = false;

		};

		constexpr split_range_struct(Str src, Str delim) noexcept : src{ src }, delim{ delim } {}

		auto begin() const noexcept { return iterator{ src, delim }; }

		constexpr auto end() const noexcept { return splitter_end_mark{}; }

	private:

		Str src;
		Str delim;

	};

	template<class StrView>
	struct split_with_pipe
	{
		
		constexpr split_with_pipe(StrView delim) noexcept : delim_view{ delim } {}
		StrView delim_view;

		friend constexpr split_range_struct<StrView> operator |(StrView str, split_with_pipe splitter) noexcept
		{
			return split_range_struct<StrView>{ str, splitter.delim_view };
		}

	};

	inline auto split(std::string_view delim)
	{
		return split_with_pipe<std::string_view>{ delim };
	}

	inline auto split(std::wstring_view delim)
	{
		return split_with_pipe<std::wstring_view>{ delim };
	}

	inline auto split(std::u16string_view delim)
	{
		return split_with_pipe<std::u16string_view>{ delim };
	}

	inline auto split(std::u32string_view delim)
	{
		return split_with_pipe<std::u32string_view>{ delim };
	}

	inline auto split(std::string_view str, std::string_view delim)
	{
		return split_range_struct<std::string_view>{ str, delim };
	}

	inline auto split(std::wstring_view str, std::wstring_view delim)
	{
		return split_range_struct<std::wstring_view>{ str, delim };
	}

	inline auto split(std::u16string_view str, std::u16string_view delim)
	{
		return split_range_struct<std::u16string_view>{ str, delim };
	}

	inline auto split(std::u32string_view str, std::u32string_view delim)
	{
		return split_range_struct<std::u32string_view>{ str, delim };
	}


};
