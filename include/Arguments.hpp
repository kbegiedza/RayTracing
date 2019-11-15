#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <string>
#include <algorithm>

namespace rt
{
	class Arguments
	{
	public:
		template <typename T>
		static bool is_argument_present(const char **begin, const char **end, std::initializer_list<T> args)
		{
			for (auto&& arg : args)
			{
				if (std::find(begin, end, arg) != end)
				{
					return true;
				}
			}

			return false;
		}

		static void show_help();

	public:
		bool parse_arguments(const int argc, const char** args);

		const size_t width() const;
		const size_t height() const;
		const size_t smoothing() const;
		const float aperture() const;
		const std::string output_path() const;

	private:
		size_t width_;
		size_t height_;
		size_t smoothing_;
		float aperture_;
		std::string output_path_;
	};

} // namespace bk

#endif