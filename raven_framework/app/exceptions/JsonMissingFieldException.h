#pragma once
#pragma once
#include <JsonException.h>

namespace raven::exceptions
{
	class JsonMissingFieldException : public JsonException
	{
	public:

		explicit JsonMissingFieldException(const char* json, const char * field_name) : JsonException(json)
		{
			field_name_ = field_name;
		}

		[[nodiscard]] const char* get_field() const
		{
			return field_name_;
		}
	private:
		const char* field_name_;
	};
}