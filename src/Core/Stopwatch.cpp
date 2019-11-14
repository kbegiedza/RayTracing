#include "Core/Stopwatch.hpp"

namespace rt
{
	using namespace std::chrono;

	Stopwatch Stopwatch::StartNew()
	{
		Stopwatch s;
		s.Start();

		return s;
	}

	void Stopwatch::Start()
	{
		start_ = high_resolution_clock::now();
		running_ = true;
	}

	void Stopwatch::Restart()
	{
		start_ = high_resolution_clock::now();
		running_ = true;
	}

	void Stopwatch::Stop()
	{
		end_ = high_resolution_clock::now();
		running_ = false;
	}

	std::chrono::milliseconds Stopwatch::elapsed_milliseconds()
	{
		const auto current_end = running_ 
			? high_resolution_clock::now() 
			: end_;

		return duration_cast<milliseconds>(current_end - start_);
	}
}