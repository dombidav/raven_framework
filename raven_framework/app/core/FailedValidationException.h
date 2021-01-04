#pragma once
#include "RavenException.h"

namespace raven::exceptions
{
	class FailedValidationException : public exceptions::RavenException
	{
	public:
		explicit FailedValidationException(const char* message) : RavenException(message, 400)
		{}
	};
}
