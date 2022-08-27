#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <Iterator.hpp>
#include <Enable_if.hpp>


namespace ft
{
//.........................................................................................REVERSE ITERATOR
        template <class Iterator>
        class reverse_iterator
        {

                public:

                        typedef Iterator                                                        iterator_type;
                        typedef typename ft::iterator_traits<Iterator>::difference_type         difference_type;
                        typedef typename ft::iterator_traits<Iterator>::reference               reference;
                        typedef typename ft::iterator_traits<Iterator>::pointer                 pointer;

                        reverse_iterator() : current() {};

                        explicit reverse_iterator(Iterator x) : current(x) {};

                        template <class U>
                        reverse_iterator(const reverse_iterator<U> &u) :current(u.base()) {};

                        Iterator base() const
                        {
                                return current;
                        };

                        reference operator*() const
                        {
                                Iterator tmp = current;
                                return *--tmp;
                        };

                        pointer operator->() const
                        {
                                return &(operator*());
                        };

                        reverse_iterator& operator++()
                        {
                                --current;
                                return *this;
                        };
			
			template <class U>
                        reverse_iterator& operator=(const reverse_iterator<U> &u)
                        {
                                current = u.base();
                                return *this;
                        };

                        reverse_iterator operator++(int)
                        {
                                reverse_iterator tmp = *this;
                                --current;
                                return tmp;
                        };

                        reverse_iterator& operator--()
                        {
                                ++current;
                                return *this;
                        };

                        reverse_iterator operator--(int)
                        {
                                reverse_iterator tmp = *this;
                                ++current;
                                return tmp;
                        };

                        reverse_iterator operator+ (typename reverse_iterator<Iterator>::difference_type n) const
                        {
                                return reverse_iterator(current - n);
                        };

                        reverse_iterator& operator+=(typename reverse_iterator<Iterator>::difference_type n)
                        {
                                current -= n;
                                return *this;
                        };

                        reverse_iterator operator- (typename reverse_iterator<Iterator>::difference_type n) const
                        {
                                return reverse_iterator(current + n);
                        };

                        reverse_iterator& operator-=(typename reverse_iterator<Iterator>::difference_type n)
                        {
                                current += n;
                                return *this;
                        };

                        reference operator[](typename reverse_iterator<Iterator>::difference_type n) const
                        {
                                return current[-n - 1];
                        };

                        protected:

                                Iterator current;
        };

template <class Iterator1, class Iterator2>
        bool operator<( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
        {
                return x.base() > y.base();
        };

        template <class Iterator>
        bool operator<( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
        {
                return x.base() > y.base();
        };

        template <class Iterator1, class Iterator2>
        bool operator!=(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
        {
                return x.base() != y.base();
        };

        template <class Iterator>
        bool operator!=(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
        {
                return x.base() != y.base();
        };

        template <class Iterator1, class Iterator2>
        bool operator>(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
        {
                return x.base() < y.base();
        };

        template <class Iterator>
        bool operator>(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
        {
                return x.base() < y.base();
        };

        template <class Iterator1, class Iterator2>
        bool operator>=(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
        {
                return x.base() <= y.base();
        };

        template <class Iterator>
        bool operator>=(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
        {
                return x.base() <= y.base();
        };

        template <class Iterator1, class Iterator2>
        bool operator<=(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
        {
                return x.base() >= y.base();
        };

        template <class Iterator>
        bool operator<=(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
        {
                return x.base() >= y.base();
        };

	template <class Iterator1, class Iterator2>
        typename ft::reverse_iterator<Iterator1>::difference_type operator-(const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
        {
                return y.base() - x.base();
        };

        template <class Iterator>
        typename ft::reverse_iterator<Iterator>::difference_type operator-(const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
        {
                return y.base() - x.base();
        };

        template <class Iterator>
        ft::reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& x)
        {
                return ft::reverse_iterator<Iterator> (x.base() - n);
        };
}

#endif
