#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <iterator>
#include <stdexcept>

/*! \namespace sc
    \brief namespace to differ from std
*/
namespace sc{


	/*! \class list
    	\brief means like std::vector

    	With this class we try to implement our own vector, but with linked lists.
	*/
	template< typename T >
	class list{
		private:
			//=== Alias
			typedef size_t size_type; //!< Type of size.
			static constexpr size_type initial_size=0; //!< Default value is 0.

			//=== Attributes
			struct Node{
				T data;
				Node* next;
				Node* prev;
			};

			size_type m_size; //!< size of the list.
			Node * head; //!< Head Node pointer.
			Node * tail; //!< Tail Node pointer.


		public:
			class my_iterator;

			//=== Constructors
			/// Default constructor.
			list( )
				: m_size{initial_size}, head{new Node}, tail{new Node}
			{
				head->next = tail;
				head->prev = nullptr;
				tail->prev = head;
				tail->next = nullptr;
			}

			/// Constructor with a defined capacity.
			explicit list( size_type count )
				: m_size{count}, head{new Node}, tail{new Node}
			{	
				head->prev = nullptr;
				tail->next = nullptr;

				Node * fast = head;
				Node * temp;
				for(size_type i{0u} ; i < count ; i++)
				{
					temp = new Node;
					temp->data = 0;

					fast->next = temp;
					temp->prev = fast;

					fast = fast->next;
				}

				tail->prev = fast;
				fast->next = tail;
			}
			
			/// Constructor with elements in [first, last) range.
			template< typename InputIt >
			list( InputIt first, InputIt last )
				: m_size{(size_type)(last - first)}, head{new Node}, tail{new Node}
			{
				head->prev = nullptr;
				tail->next = nullptr;
				head->next = tail;
				tail->prev = head;

				while(first != last)
				{
					tail->next = new Node;
					tail->next->prev = tail;
					tail->data = *(first++);
					tail = tail->next;
					tail->next = nullptr;
				}
			}

			/// Copy constructor.
			list( const list& other )
				: m_size{other.size()}, head{new Node}, tail{ new Node }
			{
				head->prev = nullptr;
				tail->next = nullptr;

				Node * otherTemp = other.head->next;
				Node * temp = head;
				for( size_type i{0u} ; i < m_size ; i++ )
				{
					Node * newNode = new Node;
					temp->next = newNode;
					newNode->prev = temp;

					newNode->data = otherTemp->data;

					otherTemp = otherTemp->next;
					temp = temp->next;
				}

				temp->next = tail;
				tail->prev = temp;
			}

			/// std::initializer_list copy constructor.
			list( std::initializer_list<T> ilist )
				: m_size{ilist.size()}, head{new Node}, tail{new Node}
			{
				head->prev = nullptr;
				tail->next = nullptr;
				head->next = tail;
				tail->prev = head;

				for( const T& e : ilist )
				{
						tail->next = new Node;
						tail->next->prev = tail;
						tail->data = e;
						tail = tail->next;
						tail->next = nullptr;
				}
			}

			/// Destructor.
			~list( )
			{
				while( tail != head )
				{
					tail = tail->prev;
					delete tail->next;
				}
				delete head;
			}

			//=== Iterators
			/// Returns an iterator pointing to the first item in the list.
			my_iterator begin()
			{
				my_iterator iter(head->next);
				return iter;
			}

			/// Returns a iterator pointing to the position just after the last item in the list.
			my_iterator end()
			{
				my_iterator iter(tail);
				return iter;
			}

			/// Returns a constant iterator pointing to the first element of the list.
			const my_iterator cbegin() const
			{
				my_const_iterator iter(head->next);
				return iter;
			}

			/// Returns a constant iterator pointing to the position just after the last element of the list.
			const my_iterator cend() const
			{
				my_const_iterator iter(tail);
				return iter;
			}


	// 	public:
			//=== Methods
			/// Returns the size of the list.
			size_type size( ) const
			{return this->m_size;}

			/// Delete all array elements.
			void clear( )
			{
				while( tail != head )
				{
					tail = tail->prev;
					delete tail->next;
				}
				delete head;

				this->m_size = initial_size;

				head = new Node;
				tail = new Node;

				head->next = tail;
				head->prev = nullptr;
				tail->prev = head;
				tail->next = nullptr;
			}

			/// Checks if the array is empty.
			bool empty( )
			{return m_size == 0;}
			
			/// Adds value to the front of the list.
			void push_front( const T & value )
			{
				head->data = value;
				head->prev = new Node;
				head->prev->next = head;
				head = head->prev;
				head->prev = nullptr;
				m_size++;
			}

			/// Adds value to the end of the list.
			void push_back( const T & value )
			{	
				tail->data = value;
				tail->next = new Node;
				tail->next->prev = tail;
				tail = tail->next;
				tail->next = nullptr;
				m_size++;
			}
			
			/// Removes the object at the end of the list.
			void pop_back( )
			{
				if(m_size == 0)
					return;

				Node * target = tail->prev;
				tail->prev = target->prev;
				tail->prev->next = tail;

				delete target;

				m_size--;
			}

			/// Removes the object at the front of the list.
			void pop_front( )
			{
				if(m_size == 0)
					return;

				Node * target = head->next;
				head->next = target->next;
				target->next->prev = head;

				delete target;

				m_size--;
			}

			/// Returns the object at the end of the list.
			const T & back( ) const
			{
				return tail->prev->data;
			}

			/// Returns the object at the beginning of the list.
			const T & front( ) const
			{
				return head->next->data;
			}

			/// Replaces the content of the list with copies of value.
			void assign( const T & value )
			{
				Node * fast = head->next;
				for( size_type i{0u} ; i<m_size ; i++ )
				{
					fast->data = value;
					fast = fast->next;
				}
			}

	// 		/// Return the object at the index position.
	// 		T & operator[]( size_type pos )
	// 		{ return arr[pos]; }

	// 		/// Returns the object at the index pos in the array.
	// 		T & at( size_type pos )
	// 		{
	// 			if( not (pos < m_size and pos >= 0) )
	// 				throw std::out_of_range("error in at(): out of range");
	// 			else
	// 				return arr[pos];
	// 		}

	// 		/// Return the capacity of array.
	// 		size_type capacity( ) const
	// 		{return m_capacity;}

	// 		/// Realoc the storage to new_cap
	// 		void reserve( size_type new_cap )
	// 		{
	// 			if( new_cap <= m_capacity )
	// 				return;

	// 			list<T> aux = *this;

	// 			delete arr;
	// 			this->m_capacity = new_cap;
	// 			this->arr = new T[m_capacity];

	// 			for( size_type i{0u} ; i < m_size ; i++ )
	// 				arr[i] = aux[i];
	// 		}

	// 		/// Desaloc unused storage
	// 		void shrink_to_fit( )
	// 		{
	// 			if( m_size == m_capacity )
	// 				return;

	// 			list<T> aux = *this;
				
	// 			delete arr;
	// 			this->m_capacity = m_size;
	// 			this->arr = new T[m_capacity];

	// 			for( size_type i{0u} ; i < m_size ; i++ )
	// 				arr[i] = aux[i];
	// 		}			

			//=== Operators overload
			/// Operator= overload for vectors
			list& operator=( const list& other )
			{
				Node * fast = head->next;
				Node * otherTemp = other.head->next;
				for( size_type i{0u} ; i < other.size() ; i++ )
				{
					if( fast == tail )
					{
						tail->next = new Node;
						tail->next->prev = tail;
						tail = tail->next;
						tail->next = nullptr;
					}

					fast->data = otherTemp->data;
					
					fast = fast->next;
					otherTemp = otherTemp->next;
				}

				this->m_size = other.size();

				return *this;
			}

			/// Operator= overload for initializer_list
			list& operator=( std::initializer_list<T> ilist )
			{
				Node * fast = head->next;
				for( const T& e : ilist)
				{
					if( fast == tail )
					{
						tail->next = new Node;
						tail->next->prev = tail;
						tail = tail->next;
						tail->next = nullptr;
					}

					fast->data = e;
					
					fast = fast->next;
				}

				this->m_size = ilist.size();

				return *this;
			}

			/// Operator== overload for vectors comparison
			bool operator==( const list& rhs )
			{
				if( m_size == rhs.size() )
				{
					Node* temp;
					temp = rhs.head->next;
					tail = head->next;
					for( size_type i{0u} ; i < m_size ; i++ )
					{
						if(tail->data != temp->data) return false;
						else
						{
							tail = tail->next;
							temp = temp->next;
						}
					}
					return true;
				}
				else return false;
			}

			/// Operator!= overload for vectors comparison
			bool operator!=( const list& rhs )
			{
				if( this->m_size == rhs.size() )
				{
					Node* temp;
					temp = rhs.head->next;
					tail = head->next;
					for(int i=0; i<(int)this->m_size; i++)
					{
						if(tail->data != temp->data) return true;
						else
						{
							tail = tail->next;
							temp = temp->next;
						}
					}
					return false;
				}
				else return true;
			}

			//=== Operations
			/// Adds value into the list before pos. Returns an iterator to the position of the inserted item.
			my_iterator insert ( my_iterator pos, const T & value )
			{
				Node * temp = pos.getIt();
				Node * newNode = new Node;

				newNode->data = value;
				newNode->next = temp;
				newNode->prev = temp->prev;
				temp->prev = newNode;
				newNode->prev->next = newNode;

				m_size++;

				return pos;
			}

			///inserts elements from the range [first; last) before pos.
			template< typename InItr >
			my_iterator insert( my_iterator pos, InItr first, InItr last )
			{
				Node * it = pos.getIt();
				Node * fast = it;
				fast = fast->prev;

				while( first != last )
				{
					fast->next = new Node;
					fast->next->data = *(first++);
					fast->next->prev = fast;
					fast = fast->next;
					m_size++;
				}

				fast->next = it;
				it->prev = fast;

				return pos;
			}

			/// Inserts elements from the initializer list ilist before pos.
			my_iterator insert( my_iterator pos, std::initializer_list< T > ilist )
			{
				Node * it = pos.getIt();
				Node * fast = it;
				fast = fast->prev;

				for( const T& e : ilist )
				{
					fast->next = new Node;
					fast->next->data = e;
					fast->next->prev = fast;
					fast = fast->next;
					m_size++;
				}

				fast->next = it;
				it->prev = fast;

				return pos;
			}

			/// Removes the object at position pos. Returns an iterator to the element that follows pos before the call.
			my_iterator erase( my_iterator pos )
			{
				Node * target = pos.getIt();
				pos++;

				target->next->prev = target->prev;
				target->prev->next = target->next;

				delete target;

				m_size--;

				return pos;
			}

			/// Removes elements in the range [first; last).
			my_iterator erase( my_iterator ifirst, my_iterator ilast )
			{
				Node * first = ifirst.getIt();
				Node * last = ilast.getIt();

				while( first != last )
				{
					Node * target = first;
					first = first->next;

					first->prev = target->prev;
					target->prev->next = first;

					delete target;

					m_size--;
				}

				return last;
			}

	// 		/// Replaces the contents with count copies of value value.
	// 		template< typename InItr >
	// 		void assign( InItr first, InItr last )
	// 		{
	// 			size_type range_size = last-first;

	// 			if( range_size > m_capacity ){
	// 				reserve( range_size );
	// 				this->m_capacity = range_size;
	// 			}

	// 			delete arr;
	// 			this->m_size = range_size;
	// 			this->arr = new T[m_capacity];

	// 			size_type count{0u};
	// 			while( first != last )
	// 				arr[count++] = *(first++);
	// 		}

	// 		/// Replaces the contents of the list with copies of the elements in the range [first; last).
	// 		void assign( std::initializer_list< T > ilist )
	// 		{
	// 			if( ilist.size() > m_capacity ){
	// 				reserve( ilist.size() );
	// 				this->m_capacity = ilist.size();
	// 			}

	// 			delete arr;
	// 			this->m_size = ilist.size();
	// 			this->arr = new T[m_capacity];

	// 			size_type count{0u};
	// 			for( const T& e : ilist )
	// 				arr[count++] = e;
	// 		}
			
			// gift hahaha
			friend std::ostream& operator<<(std::ostream& os, const list& lf)
			{
				Node * temp = lf.head->next;
			    os << "[ ";
			    for( size_type i{0u} ; i < lf.size() ; i++ )
			    {
			        os << temp->data << " ";
			        temp = temp->next;
			    }
			    os << "]";

			    return os;
			}	


	public:

		/*! \class my_iterator
			
			With this class we're trying to implement an iterator class for vectors.
		*/
		class my_iterator{
			private:
				Node * it; //!< Iterator pointer
				typedef my_iterator iterator; 

			public:
				//=== Alias
				// typedef size_t size_type; //!< Type of size.
				
				//=== Constructor
				my_iterator(Node * it)
					: it{it}
				{/*empty*/}

				//=== Destructor
				~my_iterator()
				{/*empty*/}

			public:
				//=== Operators
				iterator operator++(void)
				{ 
					it = it->next;
					return iterator( it ); 
				}

				iterator operator++(int)
				{ 
					iterator temp( it );
					it = it->next;
					return temp;
				}

				T operator*()
				{ return it->data; }

				iterator operator--(void)
				{ 
					it = it->prev;
					return iterator( it ); 
				}

				iterator operator--(int)
				{
					iterator temp( it );
					it = it->prev;
					return temp;
				}

				friend iterator operator+(int n, iterator it)
				{
					for( int i = 0 ; i < n ; i++ )
						it = it->next;
					return iterator( it );
				}

				friend iterator operator+(iterator it, int n)
				{
					for( int i = 0 ; i < n ; i++ )
						it = it->next;
					return iterator( it );
				}

				friend iterator operator-(int n, iterator it)
				{
					for( int i = 0 ; i < n ; i++ )
						it = it->prev;
					return iterator( it );
				}

				friend iterator operator-(iterator it, int n)
				{
					for( int i = 0 ; i < n ; i++ )
						it = it->prev;
					return iterator( it );
				}

				friend size_type operator-(iterator it1, iterator it2)
				{
					size_t count = 0;
					while( it2 != it1 )
					{
						count++;
						it2++;
					}
					return count;
				}

				Node * operator->()
				{
					return it;
				}

				bool operator==( const iterator& it2) const
				{ return it == it2.it; }

				bool operator!=( const iterator& it2) const
				{ return it != it2.it; }

				Node * getIt()
				{ return it; }

		}; // class my_iterator
		

	// 	// ! \class my_constiterator
			
	// 	// 	With this class we're trying to implement an constant iterator class for vectors.
		


		class my_const_iterator{
			private:
				const Node * it; //!< Iterator pointer
				typedef my_const_iterator iterator; 

			public:
				//=== Alias
				// typedef size_t size_type; //!< Type of size.
				
				//=== Constructor
				my_const_iterator(Node * it)
					: it{it}
				{/*empty*/}

				//=== Destructor
				~my_const_iterator()
				{/*empty*/}

			public:
				//=== Operators
				iterator operator++(void)
				{ 
					it = it->next;
					return iterator( it ); 
				}

				iterator operator++(int)
				{ 
					iterator temp( it );
					it = it->next;
					return temp;
				}

				T operator*()
				{ return it->data; }

				iterator operator--(void)
				{ 
					it = it->prev;
					return iterator( it ); 
				}

				iterator operator--(int)
				{
					iterator temp( it );
					it = it->prev;
					return temp;
				}

				friend iterator operator+(int n, iterator it)
				{
					for( int i = 0 ; i < n ; i++ )
						it = it->next;
					return iterator( it );
				}

				friend iterator operator+(iterator it, int n)
				{
					for( int i = 0 ; i < n ; i++ )
						it = it->next;
					return iterator( it );
				}

				friend iterator operator-(int n, iterator it)
				{
					for( int i = 0 ; i < n ; i++ )
						it = it->prev;
					return iterator( it );
				}

				friend iterator operator-(iterator it, int n)
				{
					for( int i = 0 ; i < n ; i++ )
						it = it->prev;
					return iterator( it );
				}

				friend size_type operator-(iterator it1, iterator it2)
				{
					size_t count = 0;
					while( it2 != it1 )
					{
						count++;
						it2++;
					}
					return count;
				}

				Node * operator->()
				{
					return it;
				}

				bool operator==( const iterator& it2) const
				{ return it == it2.it; }

				bool operator!=( const iterator& it2) const
				{ return it != it2.it; }

				Node * getIt()
				{ return it; }
		}; // class my_const_iterator
		
	}; // class list

} // namespace sc

#endif
