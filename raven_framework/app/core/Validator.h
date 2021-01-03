#pragma once
#include <FailedValidationException.h>
namespace raven
{
	namespace validate
	{
		enum class type
		{
			String,
			Int,
			Double,
			Bool,
			Array,
			Object,
		};
	}
	class Validator
	{
		
	public:
		

		rapidjson::Document _document;

		Validator(rapidjson::GenericDocument<rapidjson::UTF8<>>& document)
		{
			_document.CopyFrom(document, document.GetAllocator());
		}

		Validator* required(const char * key)
		{
			if (!_document.HasMember(key))
				throw exceptions::MissingFieldException("name", _document.GetString());

			return this;
		}

		Validator* required(const char* key, const validate::type typ)
		{
			if (!_document.HasMember(key))
				throw exceptions::MissingFieldException("name", _document.GetString());
			switch (typ)
			{
			case validate::type::String:
				check([key](rapidjson::Document* doc)->std::string
					{
						if ((*doc)[key].IsString()) return "";
						std::string e = key;
						e += " can not be converted to String";
						return e;
					});
				break;
			case validate::type::Int:
				check([key](rapidjson::Document* doc)->std::string
					{
						if ((*doc)[key].IsInt()) return "";
						std::string e = key;
						e += " can not be converted to Int";
						return e;
					});
				break;
			case validate::type::Double:
				check([key](rapidjson::Document* doc)->std::string
					{
						if ((*doc)[key].IsDouble()) return "";
						std::string e = key;
						e += " can not be converted to Double";
						return e;
					});
				break;
			case validate::type::Bool:
				check([key](rapidjson::Document* doc)->std::string
					{
						if ((*doc)[key].IsBool()) return "";
						std::string e = key;
						e += " can not be converted to Bool";
						return e;
					});
				break;
			case validate::type::Object:
				check([key](rapidjson::Document* doc)->std::string
					{
						if ((*doc)[key].IsObject()) return "";
						std::string e = key;
						e += " can not be converted to Object";
						return e;
					});
				break;
			case validate::type::Array:
				check([key](rapidjson::Document* doc)->std::string
					{
						if ((*doc)[key].IsObject()) return "";
						std::string e = key;
						e += " can not be converted to Array";
						return e;
					});
				break;
			default:
				break;
			}

			return this;
		}

		template <typename Function> Validator* check(Function function)
		{
			const auto result = function(&_document);
			if (!result.empty())
				throw raven::exceptions::FailedValidationException(result.c_str());
			return this;
		}
	};
}

