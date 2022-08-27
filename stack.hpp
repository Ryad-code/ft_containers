#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
		protected:
			Container	c;

		public:
			typedef T		value_type;
			typedef	Container	container_type;
			typedef	size_t		size_type;
//..............................................................................//Member functions
			explicit stack( const Container& a = Container()): c(a)	//Constructor
			{
			}

			bool			empty(void) const
			{
				return c.empty();
			}

			size_type		size(void) const
			{
				return c.size();
			}

			value_type&		top(void)
			{
				return c.back();
			}

			const value_type&	top(void) const
			{
				return c.back();
			}

			void			push(const value_type& value)
			{
				c.push_back(value);
			}

			void			pop(void)
			{
				c.pop_back();
			}
//.............................................................................//Operators
			template <class Tt, class Containerr>
			friend bool operator== (const stack<Tt,Containerr>& lhs, const stack<Tt,Containerr>& rhs);

			template <class Tt, class Containerr>
			friend bool operator!= (const stack<Tt,Containerr>& lhs, const stack<Tt,Containerr>& rhs);

			template <class Tt, class Containerr>
			friend bool operator< (const stack<Tt,Containerr>& lhs, const stack<Tt,Containerr>& rhs);

			template <class Tt, class Containerr>
			friend bool operator<= (const stack<Tt,Containerr>& lhs, const stack<Tt,Containerr>& rhs);

			template <class Tt, class Containerr>
			friend bool operator> (const stack<Tt,Containerr>& lhs, const stack<Tt,Containerr>& rhs);

			template <class Tt, class Containerr>
			friend bool operator>= (const stack<Tt,Containerr>& lhs, const stack<Tt,Containerr>& rhs);

	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	};

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c != rhs.c);
	};

	template <class T, class Container>
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	};

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c <= rhs.c);
	};

	template <class T, class Container>
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c > rhs.c);
	};

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c >= rhs.c);
	};

}

#endif
