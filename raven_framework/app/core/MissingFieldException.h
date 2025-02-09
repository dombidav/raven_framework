#pragma once
#pragma once
#include <JsonException.h>

namespace raven::exceptions
{
	class MissingFieldException : public JsonException
	{
	public:

		explicit MissingFieldException(const char* field_name, const char * json) : JsonException(json)
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
