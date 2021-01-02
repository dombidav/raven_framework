#pragma once
#include <exception>
#include <string>
#include <utility>

namespace raven::exceptions
{
	/**
		 * \brief Every exception should derive from this class
		 */
		class RavenException : virtual public std::exception {

		protected:

			int error_number_;               ///< Error number
			std::string error_message_;      ///< Error message

		public:

			/** Constructor (C++ STL string, int, int).
         *  @param msg The error message
         *  @param err_num Error number
         */
			explicit
			RavenException(std::string msg, const int err_num) :
				error_number_(err_num),
				error_message_(std::move(msg))
			{}

			/** Destructor.
         *  Virtual to allow for sub classing.
         */
			virtual ~RavenException() noexcept {}

			/** Returns a pointer to the (constant) error description.
         *  @return A pointer to a const char*. The underlying memory
         *  is in possession of the Except object. Callers must
         *  not attempt to free the memory.
         */
			[[nodiscard]] const char* what() const noexcept override
			{
				return error_message_.c_str();
			}

			/** Returns error number.
         *  @return #error_number
         */
			[[nodiscard]] virtual int get_error_number() const noexcept {
				return error_number_;
			}

		};
}

