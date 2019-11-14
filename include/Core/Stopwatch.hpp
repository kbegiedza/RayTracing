#ifndef STOPWATCH_HPP_
#define STOPWATCH_HPP_

#include <chrono>

namespace rt
{
	class Stopwatch
	{
	public:
		static Stopwatch StartNew();

	public:
		void Start();
		void Restart();
		void Stop();

		std::chrono::milliseconds elapsed_milliseconds();

	private:
		std::chrono::time_point<std::chrono::steady_clock> start_;
		std::chrono::time_point<std::chrono::steady_clock> end_;
		bool running_;
	};
}

#endif // !STOPWATCH_HPP_