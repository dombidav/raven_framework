#pragma once
#include <colony.h>
#include <functional>

namespace raven::eloquent
{
	template<class T> class Collection : public plf::colony<T>
	{
	public:
		template <class Fun> Collection<T>* where(Fun predicate)
		{
			auto* result = new Collection<T>();
			for (auto i = this->begin(); i != this->end(); std::advance(i, 1))
			{
				if(predicate(*i))
				{
					result->insert(*i);
				}
			}
			return result;
		}

		template <class Fun> Collection<T>* except(Fun predicate)
		{
			auto* result = new Collection<T>();
			for (auto i = this->begin(); i != this->end(); std::advance(i, 1))
			{
				if (!predicate(*i))
				{
					result->insert(*i);
				}
			}
			return result;
		}

		T* first()
		{
			return this->empty() ? nullptr : &*this->begin();
		}
		template <class Fun> T* first(Fun predicate, T* _default)
		{
			auto temp = first(predicate);
			return temp ? temp : _default;
		}
		template <class Fun> T* first(Fun predicate)
		{
			for (auto i = this->begin(); i != this->end(); std::advance(i, 1))
			{
				if (predicate(*i))
				{
					return &*i;
				}
			}
			return nullptr;
		}

		template <typename Functor> auto Select(Functor selector) -> Collection<decltype(selector(new T))>*
		{
			using ResultType = decltype(selector(new T));
			
			auto result = new Collection<ResultType>();
			for (auto i = this->begin(); i != this->end(); std::advance(i, 1))
			{
				result->insert(selector(&*i));
			}
			return result;
		}

		void ForEach(void (*functor)(T item))
		{
			for (auto i = this->begin(); i != this->end(); std::advance(i, 1))
			{
				functor(*i);
			}
		}

		template <typename Functor>
		bool Any(Functor selector)
		{
			for (auto i = this->begin(); i != this->end(); std::advance(i, 1))
			{
				if (selector(*i))
					return true;
			}
			return false;
		}

		template <typename Functor>
		bool All(Functor selector)
		{
			for (auto i = this->begin(); i != this->end(); std::advance(i, 1))
			{
				if (!selector(*i))
					return false;
			}
			return true;
		}
		
	};
}
