#pragma once
#include <RavenException.h>

namespace raven::exceptions
{
	class JsonException : public RavenException
	{
	public:
		explicit JsonException(const char* json) : RavenException("Couldn't parse JSON content", 400)
		{
			json_ = json;
		}

		[[nodiscard]] const char* get_json() const
		{
			return json_;
		}
	private:
		const char* json_;
	};
}
