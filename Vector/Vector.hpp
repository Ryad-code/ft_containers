#ifndef VECTOR_HPP
#define VECTOR_HPP

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T					value_type;
			typedef Allocator				allocator_type;
			typedef std::size_t					size_type;
			typedef std::ptrdiff_t				difference_type;
			typedef value_type&				reference;
			typedef const value_type&			const_reference;
			typedef value_type*				pointer;
			typedef const value_type*			const_pointer;	
		//	typedef std::random_access_iterator<T>		iterator;
		//	typedef std::random_access_iterator<const T>	const_iterator;
		//	typedef std::reverse_iterator<iterator>		reverse_iterator;
		//	typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			pointer		_pointer;
			allocator_type	_alloc;
			size_type	_capacity;
			size_type	_size;

		public:
			explicit vector( const Allocator& alloc = Allocator() ) : _pointer(0), _alloc(alloc), _capacity(0), _size(0)
			{
			};	

	};
}

#endif
