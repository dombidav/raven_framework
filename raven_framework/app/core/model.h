#pragma once
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>



#include "JsonException.h"

namespace raven::eloquent
{
	class model
	{
	public:
		model() = default;
		virtual ~model()
		{
				
		}
		std::string Serialize()
		{
			rapidjson::StringBuffer s;
			rapidjson::Writer<rapidjson::StringBuffer> writer(s);

			writer.StartObject();               // Between StartObject()/EndObject(),
			
			populateWriter(&writer);

			writer.EndObject();
			return s.GetString();
		}

	protected:
		virtual void populateWriter(rapidjson::Writer<rapidjson::StringBuffer>* writer) = 0;
		static rapidjson::GenericDocument<rapidjson::UTF8<>> parse(const char* json)
		{
			rapidjson::Document document;
			if (document.Parse(json).HasParseError() || !document.IsObject())
				throw exceptions::JsonException(json);

			return document;
		}
		
	};
}
