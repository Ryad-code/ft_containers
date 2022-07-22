#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

namespace ft
{
	template < class T, class Container = std::vector<T> >
	class Stack
	{
		protected:
			Container	c;

		public:
			typedef T		value_type;
			typedef	Container	container_type;
			typedef	size_t		size_type;
//......................................................................................//Member functions
			explicit Stack( const Container& a = Container()): c(a)	//Constructor
			{
			}

			bool		empty(void) const
			{
				return c.empty();
			}

			size_type	size(void) const
			{
				return c.size();
			}

			value_type	top(void) const
			{
				return c.back();
			}

			void		push(const value_type& value)
			{
				c.push_back(value);
			}

			void		pop(void)
			{
				c.pop_back();
			}

	};
};

#endif
