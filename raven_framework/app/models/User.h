#pragma once
#include <string>

#include <model.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <Validator.h>

namespace raven
{
	namespace eloquent
	{
		class User : public model
		{
		public:
			User() : User("", 0)
			{
			}

			User(const char * name, const int test)
			{
				SetName(name);
				SetTest(test);
			}

			void SetName(const char * value)
			{
				name_ = value;
			}

			void SetTest(const int value)
			{
				test_ = value;
			}

			std::string GetName() const
			{
				return name_;
			}

			explicit User(const char * json) //DESERIALIZER
			{
				auto document = parse(json);
				(new raven::Validator(document))
					->required("name")
					->required("test", validate::type::Int);
				
				SetName(document["name"].GetString());
				SetTest(document["test"].GetInt());
			}
			
			~User() = default;

			void populateWriter(rapidjson::Writer<rapidjson::StringBuffer>* writer) override
			{
				writer->Key("name");                // output a key,
				writer->String(name_.c_str());             // follow by a value.
				writer->Key("test");
				writer->Int(test_);
			}
		private:
			std::string name_;
			int test_ = 0;
		};
	}
}
