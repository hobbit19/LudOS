// -*- C++ -*-
//===----------------------------- map ------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_MAP
#define _LIBCPP_MAP

/*

    map synopsis

namespace std
{

template <class Key, class T, class Compare = less<Key>,
          class Allocator = allocator<pair<const Key, T>>>
class map
{
public:
    // types:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef Compare                                  key_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;

    typedef implementation-defined                   iterator;
    typedef implementation-defined                   const_iterator;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

    class value_compare
        : public binary_function<value_type, value_type, bool>
    {
        friend class map;
    protected:
        key_compare comp;

        value_compare(key_compare c);
    public:
        bool operator()(const value_type& x, const value_type& y) const;
    };

    // construct/copy/destroy:
    map()
        noexcept(
            is_nothrow_default_constructible<allocator_type>::value &&
            is_nothrow_default_constructible<key_compare>::value &&
            is_nothrow_copy_constructible<key_compare>::value);
    explicit map(const key_compare& comp);
    map(const key_compare& comp, const allocator_type& a);
    template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare& comp = key_compare());
    template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare& comp, const allocator_type& a);
    map(const map& m);
    map(map&& m)
        noexcept(
            is_nothrow_move_constructible<allocator_type>::value &&
            is_nothrow_move_constructible<key_compare>::value);
    explicit map(const allocator_type& a);
    map(const map& m, const allocator_type& a);
    map(map&& m, const allocator_type& a);
    map(initializer_list<value_type> il, const key_compare& comp = key_compare());
    map(initializer_list<value_type> il, const key_compare& comp, const allocator_type& a);
    template <class InputIterator>
        map(InputIterator first, InputIterator last, const allocator_type& a)
            : map(first, last, Compare(), a) {}  // C++14
    map(initializer_list<value_type> il, const allocator_type& a)
        : map(il, Compare(), a) {}  // C++14
   ~map();

    map& operator=(const map& m);
    map& operator=(map&& m)
        noexcept(
            allocator_type::propagate_on_container_move_assignment::value &&
            is_nothrow_move_assignable<allocator_type>::value &&
            is_nothrow_move_assignable<key_compare>::value);
    map& operator=(initializer_list<value_type> il);

    // iterators:
          iterator begin() noexcept;
    const_iterator begin() const noexcept;
          iterator end() noexcept;
    const_iterator end()   const noexcept;

          reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
          reverse_iterator rend() noexcept;
    const_reverse_iterator rend()   const noexcept;

    const_iterator         cbegin()  const noexcept;
    const_iterator         cend()    const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend()   const noexcept;

    // capacity:
    bool      empty()    const noexcept;
    size_type size()     const noexcept;
    size_type max_size() const noexcept;

    // element access:
    mapped_type& operator[](const key_type& k);
    mapped_type& operator[](key_type&& k);

          mapped_type& at(const key_type& k);
    const mapped_type& at(const key_type& k) const;

    // modifiers:
    template <class... Args>
        pair<iterator, bool> emplace(Args&&... args);
    template <class... Args>
        iterator emplace_hint(const_iterator position, Args&&... args);
    pair<iterator, bool> insert(const value_type& v);
    pair<iterator, bool> insert(      value_type&& v);                                // C++17
    template <class P>
        pair<iterator, bool> insert(P&& p);
    iterator insert(const_iterator position, const value_type& v);
    iterator insert(const_iterator position,       value_type&& v);                   // C++17
    template <class P>
        iterator insert(const_iterator position, P&& p);
    template <class InputIterator>
        void insert(InputIterator first, InputIterator last);
    void insert(initializer_list<value_type> il);

    template <class... Args>
        pair<iterator, bool> try_emplace(const key_type& k, Args&&... args);          // C++17
    template <class... Args>
        pair<iterator, bool> try_emplace(key_type&& k, Args&&... args);               // C++17
    template <class... Args>
        iterator try_emplace(const_iterator hint, const key_type& k, Args&&... args); // C++17
    template <class... Args>
        iterator try_emplace(const_iterator hint, key_type&& k, Args&&... args);      // C++17
    template <class M>
        pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);            // C++17
    template <class M>
        pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);                 // C++17
    template <class M>
        iterator insert_or_assign(const_iterator hint, const key_type& k, M&& obj);   // C++17
    template <class M>
        iterator insert_or_assign(const_iterator hint, key_type&& k, M&& obj);        // C++17

    iterator  erase(const_iterator position);
    iterator  erase(iterator position); // C++14
    size_type erase(const key_type& k);
    iterator  erase(const_iterator first, const_iterator last);
    void clear() noexcept;

    void swap(map& m)
        noexcept(allocator_traits<allocator_type>::is_always_equal::value &&
            is_nothrow_swappable<key_compare>::value); // C++17

    // observers:
    allocator_type get_allocator() const noexcept;
    key_compare    key_comp()      const;
    value_compare  value_comp()    const;

    // map operations:
          iterator find(const key_type& k);
    const_iterator find(const key_type& k) const;
    template<typename K>
        iterator find(const K& x);              // C++14
    template<typename K>
        const_iterator find(const K& x) const;  // C++14
    template<typename K>
      size_type count(const K& x) const;        // C++14

    size_type      count(const key_type& k) const;
          iterator lower_bound(const key_type& k);
    const_iterator lower_bound(const key_type& k) const;
    template<typename K>
        iterator lower_bound(const K& x);              // C++14
    template<typename K>
        const_iterator lower_bound(const K& x) const;  // C++14

          iterator upper_bound(const key_type& k);
    const_iterator upper_bound(const key_type& k) const;
    template<typename K>
        iterator upper_bound(const K& x);              // C++14
    template<typename K>
        const_iterator upper_bound(const K& x) const;  // C++14

    pair<iterator,iterator>             equal_range(const key_type& k);
    pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
    template<typename K>
        pair<iterator,iterator>             equal_range(const K& x);        // C++14
    template<typename K>
        pair<const_iterator,const_iterator> equal_range(const K& x) const;  // C++14
};

template <class Key, class T, class Compare, class Allocator>
bool
operator==(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool
operator< (const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool
operator!=(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool
operator> (const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool
operator>=(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool
operator<=(const map<Key, T, Compare, Allocator>& x,
           const map<Key, T, Compare, Allocator>& y);

// specialized algorithms:
template <class Key, class T, class Compare, class Allocator>
void
swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y)
    noexcept(noexcept(x.swap(y)));

template <class Key, class T, class Compare = less<Key>,
          class Allocator = allocator<pair<const Key, T>>>
class multimap
{
public:
    // types:
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef pair<const key_type,mapped_type>         value_type;
    typedef Compare                                  key_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::size_type       size_type;
    typedef typename allocator_type::difference_type difference_type;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;

    typedef implementation-defined                   iterator;
    typedef implementation-defined                   const_iterator;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

    class value_compare
        : public binary_function<value_type,value_type,bool>
    {
        friend class multimap;
    protected:
        key_compare comp;
        value_compare(key_compare c);
    public:
        bool operator()(const value_type& x, const value_type& y) const;
    };

    // construct/copy/destroy:
    multimap()
        noexcept(
            is_nothrow_default_constructible<allocator_type>::value &&
            is_nothrow_default_constructible<key_compare>::value &&
            is_nothrow_copy_constructible<key_compare>::value);
    explicit multimap(const key_compare& comp);
    multimap(const key_compare& comp, const allocator_type& a);
    template <class InputIterator>
        multimap(InputIterator first, InputIterator last, const key_compare& comp);
    template <class InputIterator>
        multimap(InputIterator first, InputIterator last, const key_compare& comp,
                 const allocator_type& a);
    multimap(const multimap& m);
    multimap(multimap&& m)
        noexcept(
            is_nothrow_move_constructible<allocator_type>::value &&
            is_nothrow_move_constructible<key_compare>::value);
    explicit multimap(const allocator_type& a);
    multimap(const multimap& m, const allocator_type& a);
    multimap(multimap&& m, const allocator_type& a);
    multimap(initializer_list<value_type> il, const key_compare& comp = key_compare());
    multimap(initializer_list<value_type> il, const key_compare& comp,
             const allocator_type& a);
    template <class InputIterator>
        multimap(InputIterator first, InputIterator last, const allocator_type& a)
            : multimap(first, last, Compare(), a) {} // C++14
    multimap(initializer_list<value_type> il, const allocator_type& a)
        : multimap(il, Compare(), a) {} // C++14
    ~multimap();

    multimap& operator=(const multimap& m);
    multimap& operator=(multimap&& m)
        noexcept(
            allocator_type::propagate_on_container_move_assignment::value &&
            is_nothrow_move_assignable<allocator_type>::value &&
            is_nothrow_move_assignable<key_compare>::value);
    multimap& operator=(initializer_list<value_type> il);

    // iterators:
          iterator begin() noexcept;
    const_iterator begin() const noexcept;
          iterator end() noexcept;
    const_iterator end()   const noexcept;

          reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
          reverse_iterator rend() noexcept;
    const_reverse_iterator rend()   const noexcept;

    const_iterator         cbegin()  const noexcept;
    const_iterator         cend()    const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend()   const noexcept;

    // capacity:
    bool      empty()    const noexcept;
    size_type size()     const noexcept;
    size_type max_size() const noexcept;

    // modifiers:
    template <class... Args>
        iterator emplace(Args&&... args);
    template <class... Args>
        iterator emplace_hint(const_iterator position, Args&&... args);
    iterator insert(const value_type& v);
    iterator insert(      value_type&& v);                                            // C++17
    template <class P>
        iterator insert(P&& p);
    iterator insert(const_iterator position, const value_type& v);
    iterator insert(const_iterator position,       value_type&& v);                   // C++17
    template <class P>
        iterator insert(const_iterator position, P&& p);
    template <class InputIterator>
        void insert(InputIterator first, InputIterator last);
    void insert(initializer_list<value_type> il);

    iterator  erase(const_iterator position);
    iterator  erase(iterator position); // C++14
    size_type erase(const key_type& k);
    iterator  erase(const_iterator first, const_iterator last);
    void clear() noexcept;

    void swap(multimap& m)
        noexcept(allocator_traits<allocator_type>::is_always_equal::value &&
            is_nothrow_swappable<key_compare>::value); // C++17

    // observers:
    allocator_type get_allocator() const noexcept;
    key_compare    key_comp()      const;
    value_compare  value_comp()    const;

    // map operations:
          iterator find(const key_type& k);
    const_iterator find(const key_type& k) const;
    template<typename K>
        iterator find(const K& x);              // C++14
    template<typename K>
        const_iterator find(const K& x) const;  // C++14
    template<typename K>
      size_type count(const K& x) const;        // C++14

    size_type      count(const key_type& k) const;
          iterator lower_bound(const key_type& k);
    const_iterator lower_bound(const key_type& k) const;
    template<typename K>
        iterator lower_bound(const K& x);              // C++14
    template<typename K>
        const_iterator lower_bound(const K& x) const;  // C++14

          iterator upper_bound(const key_type& k);
    const_iterator upper_bound(const key_type& k) const;
    template<typename K>
        iterator upper_bound(const K& x);              // C++14
    template<typename K>
        const_iterator upper_bound(const K& x) const;  // C++14

    pair<iterator,iterator>             equal_range(const key_type& k);
    pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
    template<typename K>
        pair<iterator,iterator>             equal_range(const K& x);        // C++14
    template<typename K>
        pair<const_iterator,const_iterator> equal_range(const K& x) const;  // C++14
};

template <class Key, class T, class Compare, class Allocator>
bool
operator==(const multimap<Key, T, Compare, Allocator>& x,
           const multimap<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool
operator< (const multimap<Key, T, Compare, Allocator>& x,
           const multimap<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool
operator!=(const multimap<Key, T, Compare, Allocator>& x,
           const multimap<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool
operator> (const multimap<Key, T, Compare, Allocator>& x,
           const multimap<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool
operator>=(const multimap<Key, T, Compare, Allocator>& x,
           const multimap<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool
operator<=(const multimap<Key, T, Compare, Allocator>& x,
           const multimap<Key, T, Compare, Allocator>& y);

// specialized algorithms:
template <class Key, class T, class Compare, class Allocator>
void
swap(multimap<Key, T, Compare, Allocator>& x,
     multimap<Key, T, Compare, Allocator>& y)
    noexcept(noexcept(x.swap(y)));

}  // std

*/

#include "__config.hpp"
#include "__tree.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#include "utility.hpp"
#include "functional.hpp"
#include "initializer_list.hpp"
#include "type_traits.hpp"

#if !defined(_LIBCPP_HAS_NO_PRAGMA_SYSTEM_HEADER)
#pragma GCC system_header
#endif

_LIBCPP_BEGIN_NAMESPACE_STD

template <class _Key, class _CP, class _Compare, bool _IsSmall>
class __map_value_compare
    : private _Compare
{
public:
    _LIBCPP_INLINE_VISIBILITY
    __map_value_compare()
        _NOEXCEPT_(is_nothrow_default_constructible<_Compare>::value)
        : _Compare() {}
    _LIBCPP_INLINE_VISIBILITY
    __map_value_compare(_Compare c)
        _NOEXCEPT_(is_nothrow_copy_constructible<_Compare>::value)
        : _Compare(c) {}
    _LIBCPP_INLINE_VISIBILITY
    const _Compare& key_comp() const _NOEXCEPT {return *this;}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _CP& __x, const _CP& __y) const
        {return static_cast<const _Compare&>(*this)(__x.__cc.first, __y.__cc.first);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _CP& __x, const _Key& __y) const
        {return static_cast<const _Compare&>(*this)(__x.__cc.first, __y);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _Key& __x, const _CP& __y) const
        {return static_cast<const _Compare&>(*this)(__x, __y.__cc.first);}
    void swap(__map_value_compare&__y)
        _NOEXCEPT_(__is_nothrow_swappable<_Compare>::value)
    {
      using _VSTD::swap;
      swap(static_cast<_Compare&>(*this), static_cast<_Compare&>(__y));
    }

#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value, bool>::type
    operator () ( const _K2& __x, const _CP& __y ) const
        {return static_cast<const _Compare&>(*this) (__x, __y.__cc.first);}

    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value, bool>::type
    operator () (const _CP& __x, const _K2& __y) const
        {return static_cast<const _Compare&>(*this) (__x.__cc.first, __y);}
#endif
};

template <class _Key, class _CP, class _Compare>
class __map_value_compare<_Key, _CP, _Compare, false>
{
    _Compare comp;

public:
    _LIBCPP_INLINE_VISIBILITY
    __map_value_compare()
        _NOEXCEPT_(is_nothrow_default_constructible<_Compare>::value)
        : comp() {}
    _LIBCPP_INLINE_VISIBILITY
    __map_value_compare(_Compare c)
        _NOEXCEPT_(is_nothrow_copy_constructible<_Compare>::value)
        : comp(c) {}
    _LIBCPP_INLINE_VISIBILITY
    const _Compare& key_comp() const _NOEXCEPT {return comp;}

    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _CP& __x, const _CP& __y) const
        {return comp(__x.__cc.first, __y.__cc.first);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _CP& __x, const _Key& __y) const
        {return comp(__x.__cc.first, __y);}
    _LIBCPP_INLINE_VISIBILITY
    bool operator()(const _Key& __x, const _CP& __y) const
        {return comp(__x, __y.__cc.first);}
    void swap(__map_value_compare&__y)
        _NOEXCEPT_(__is_nothrow_swappable<_Compare>::value)
    {
        using _VSTD::swap;
        swap(comp, __y.comp);
    }

#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value, bool>::type
    operator () ( const _K2& __x, const _CP& __y ) const
        {return comp (__x, __y.__cc.first);}

    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value, bool>::type
    operator () (const _CP& __x, const _K2& __y) const
        {return comp (__x.__cc.first, __y);}
#endif
};

template <class _Key, class _CP, class _Compare, bool __b>
inline _LIBCPP_INLINE_VISIBILITY
void
swap(__map_value_compare<_Key, _CP, _Compare, __b>& __x,
     __map_value_compare<_Key, _CP, _Compare, __b>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

template <class _Allocator>
class __map_node_destructor
{
    typedef _Allocator                          allocator_type;
    typedef allocator_traits<allocator_type>    __alloc_traits;

public:
    typedef typename __alloc_traits::pointer    pointer;

private:
    allocator_type& __na_;

    __map_node_destructor& operator=(const __map_node_destructor&);

public:
    bool __first_constructed;
    bool __second_constructed;

    _LIBCPP_INLINE_VISIBILITY
    explicit __map_node_destructor(allocator_type& __na) _NOEXCEPT
        : __na_(__na),
          __first_constructed(false),
          __second_constructed(false)
        {}

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    __map_node_destructor(__tree_node_destructor<allocator_type>&& __x) _NOEXCEPT
        : __na_(__x.__na_),
          __first_constructed(__x.__value_constructed),
          __second_constructed(__x.__value_constructed)
        {
            __x.__value_constructed = false;
        }
#endif  // _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY
    void operator()(pointer __p) _NOEXCEPT
    {
        if (__second_constructed)
            __alloc_traits::destroy(__na_, _VSTD::addressof(__p->__value_.__cc.second));
        if (__first_constructed)
            __alloc_traits::destroy(__na_, _VSTD::addressof(__p->__value_.__cc.first));
        if (__p)
            __alloc_traits::deallocate(__na_, __p, 1);
    }
};

template <class _Key, class _Tp, class _Compare, class _Allocator>
    class map;
template <class _Key, class _Tp, class _Compare, class _Allocator>
    class multimap;
template <class _TreeIterator> class __map_const_iterator;

#ifndef _LIBCPP_CXX03_LANG

template <class _Key, class _Tp>
union __value_type
{
    typedef _Key                                     key_type;
    typedef _Tp                                      mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef pair<key_type, mapped_type>              __nc_value_type;

    value_type __cc;
    __nc_value_type __nc;

    _LIBCPP_INLINE_VISIBILITY
    __value_type& operator=(const __value_type& __v)
        {__nc = __v.__cc; return *this;}

    _LIBCPP_INLINE_VISIBILITY
    __value_type& operator=(__value_type&& __v)
        {__nc = _VSTD::move(__v.__nc); return *this;}

    template <class _ValueTp,
              class = typename enable_if<
                    __is_same_uncvref<_ValueTp, value_type>::value
                 >::type
             >
    _LIBCPP_INLINE_VISIBILITY
    __value_type& operator=(_ValueTp&& __v) {
        __nc = _VSTD::forward<_ValueTp>(__v); return *this;
    }

private:
    __value_type() _LIBCPP_EQUAL_DELETE;
    ~__value_type() _LIBCPP_EQUAL_DELETE;
    __value_type(const __value_type& __v) _LIBCPP_EQUAL_DELETE;
    __value_type(__value_type&& __v) _LIBCPP_EQUAL_DELETE;
};

#else

template <class _Key, class _Tp>
struct __value_type
{
    typedef _Key                                     key_type;
    typedef _Tp                                      mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;

    value_type __cc;

private:
   __value_type();
   __value_type(__value_type const&);
   __value_type& operator=(__value_type const&);
   ~__value_type();
};

#endif // _LIBCPP_CXX03_LANG

template <class _Tp>
struct __extract_key_value_types;

template <class _Key, class _Tp>
struct __extract_key_value_types<__value_type<_Key, _Tp> >
{
  typedef _Key const __key_type;
  typedef _Tp        __mapped_type;
};

template <class _TreeIterator>
class _LIBCPP_TEMPLATE_VIS __map_iterator
{
    typedef typename _TreeIterator::_NodeTypes                   _NodeTypes;
    typedef typename _TreeIterator::__pointer_traits             __pointer_traits;

    _TreeIterator __i_;

public:
    typedef bidirectional_iterator_tag                           iterator_category;
    typedef typename _NodeTypes::__map_value_type                value_type;
    typedef typename _TreeIterator::difference_type              difference_type;
    typedef value_type&                                          reference;
    typedef typename _NodeTypes::__map_value_type_pointer        pointer;

    _LIBCPP_INLINE_VISIBILITY
    __map_iterator() _NOEXCEPT {}

    _LIBCPP_INLINE_VISIBILITY
    __map_iterator(_TreeIterator __i) _NOEXCEPT : __i_(__i) {}

    _LIBCPP_INLINE_VISIBILITY
    reference operator*() const {return __i_->__cc;}
    _LIBCPP_INLINE_VISIBILITY
    pointer operator->() const {return pointer_traits<pointer>::pointer_to(__i_->__cc);}

    _LIBCPP_INLINE_VISIBILITY
    __map_iterator& operator++() {++__i_; return *this;}
    _LIBCPP_INLINE_VISIBILITY
    __map_iterator operator++(int)
    {
        __map_iterator __t(*this);
        ++(*this);
        return __t;
    }

    _LIBCPP_INLINE_VISIBILITY
    __map_iterator& operator--() {--__i_; return *this;}
    _LIBCPP_INLINE_VISIBILITY
    __map_iterator operator--(int)
    {
        __map_iterator __t(*this);
        --(*this);
        return __t;
    }

    friend _LIBCPP_INLINE_VISIBILITY
    bool operator==(const __map_iterator& __x, const __map_iterator& __y)
        {return __x.__i_ == __y.__i_;}
    friend
    _LIBCPP_INLINE_VISIBILITY
    bool operator!=(const __map_iterator& __x, const __map_iterator& __y)
        {return __x.__i_ != __y.__i_;}

    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
    template <class> friend class _LIBCPP_TEMPLATE_VIS __map_const_iterator;
};

template <class _TreeIterator>
class _LIBCPP_TEMPLATE_VIS __map_const_iterator
{
    typedef typename _TreeIterator::_NodeTypes                   _NodeTypes;
    typedef typename _TreeIterator::__pointer_traits             __pointer_traits;

    _TreeIterator __i_;

public:
    typedef bidirectional_iterator_tag                           iterator_category;
    typedef typename _NodeTypes::__map_value_type                value_type;
    typedef typename _TreeIterator::difference_type              difference_type;
    typedef const value_type&                                    reference;
    typedef typename _NodeTypes::__const_map_value_type_pointer  pointer;

    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator() _NOEXCEPT {}

    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator(_TreeIterator __i) _NOEXCEPT : __i_(__i) {}
    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator(__map_iterator<
        typename _TreeIterator::__non_const_iterator> __i) _NOEXCEPT
        : __i_(__i.__i_) {}

    _LIBCPP_INLINE_VISIBILITY
    reference operator*() const {return __i_->__cc;}
    _LIBCPP_INLINE_VISIBILITY
    pointer operator->() const {return pointer_traits<pointer>::pointer_to(__i_->__cc);}

    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator& operator++() {++__i_; return *this;}
    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator operator++(int)
    {
        __map_const_iterator __t(*this);
        ++(*this);
        return __t;
    }

    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator& operator--() {--__i_; return *this;}
    _LIBCPP_INLINE_VISIBILITY
    __map_const_iterator operator--(int)
    {
        __map_const_iterator __t(*this);
        --(*this);
        return __t;
    }

    friend _LIBCPP_INLINE_VISIBILITY
    bool operator==(const __map_const_iterator& __x, const __map_const_iterator& __y)
        {return __x.__i_ == __y.__i_;}
    friend _LIBCPP_INLINE_VISIBILITY
    bool operator!=(const __map_const_iterator& __x, const __map_const_iterator& __y)
        {return __x.__i_ != __y.__i_;}

    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
    template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS multimap;
    template <class, class, class> friend class _LIBCPP_TEMPLATE_VIS __tree_const_iterator;
};

template <class _Key, class _Tp, class _Compare = less<_Key>,
          class _Allocator = allocator<pair<const _Key, _Tp> > >
class _LIBCPP_TEMPLATE_VIS map
{
public:
    // types:
    typedef _Key                                     key_type;
    typedef _Tp                                      mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef pair<key_type, mapped_type>              __nc_value_type;
    typedef _Compare                                 key_compare;
    typedef _Allocator                               allocator_type;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;

    static_assert((is_same<typename allocator_type::value_type, value_type>::value),
                  "Allocator::value_type must be same type as value_type");

    class _LIBCPP_TEMPLATE_VIS value_compare
        : public binary_function<value_type, value_type, bool>
    {
        friend class map;
    protected:
        key_compare comp;

        _LIBCPP_INLINE_VISIBILITY value_compare(key_compare c) : comp(c) {}
    public:
        _LIBCPP_INLINE_VISIBILITY
        bool operator()(const value_type& __x, const value_type& __y) const
            {return comp(__x.first, __y.first);}
    };

private:

    typedef _VSTD::__value_type<key_type, mapped_type>             __value_type;
    typedef __map_value_compare<key_type, __value_type, key_compare> __vc;
    typedef typename __rebind_alloc_helper<allocator_traits<allocator_type>,
                                                 __value_type>::type __allocator_type;
    typedef __tree<__value_type, __vc, __allocator_type>   __base;
    typedef typename __base::__node_traits                 __node_traits;
    typedef allocator_traits<allocator_type>               __alloc_traits;

    __base __tree_;

public:
    typedef typename __alloc_traits::pointer               pointer;
    typedef typename __alloc_traits::const_pointer         const_pointer;
    typedef typename __alloc_traits::size_type             size_type;
    typedef typename __alloc_traits::difference_type       difference_type;
    typedef __map_iterator<typename __base::iterator>             iterator;
    typedef __map_const_iterator<typename __base::const_iterator> const_iterator;
    typedef _VSTD::reverse_iterator<iterator>               reverse_iterator;
    typedef _VSTD::reverse_iterator<const_iterator>         const_reverse_iterator;

    _LIBCPP_INLINE_VISIBILITY
    map()
        _NOEXCEPT_(
            is_nothrow_default_constructible<allocator_type>::value &&
            is_nothrow_default_constructible<key_compare>::value &&
            is_nothrow_copy_constructible<key_compare>::value)
        : __tree_(__vc(key_compare())) {}

    _LIBCPP_INLINE_VISIBILITY
    explicit map(const key_compare& __comp)
        _NOEXCEPT_(
            is_nothrow_default_constructible<allocator_type>::value &&
            is_nothrow_copy_constructible<key_compare>::value)
        : __tree_(__vc(__comp)) {}

    _LIBCPP_INLINE_VISIBILITY
    explicit map(const key_compare& __comp, const allocator_type& __a)
        : __tree_(__vc(__comp), typename __base::allocator_type(__a)) {}

    template <class _InputIterator>
    _LIBCPP_INLINE_VISIBILITY
        map(_InputIterator __f, _InputIterator __l,
            const key_compare& __comp = key_compare())
        : __tree_(__vc(__comp))
        {
            insert(__f, __l);
        }

    template <class _InputIterator>
    _LIBCPP_INLINE_VISIBILITY
        map(_InputIterator __f, _InputIterator __l,
            const key_compare& __comp, const allocator_type& __a)
        : __tree_(__vc(__comp), typename __base::allocator_type(__a))
        {
            insert(__f, __l);
        }

#if _LIBCPP_STD_VER > 11
    template <class _InputIterator>
    _LIBCPP_INLINE_VISIBILITY
    map(_InputIterator __f, _InputIterator __l, const allocator_type& __a)
        : map(__f, __l, key_compare(), __a) {}
#endif

    _LIBCPP_INLINE_VISIBILITY
    map(const map& __m)
        : __tree_(__m.__tree_)
        {
            insert(__m.begin(), __m.end());
        }

    _LIBCPP_INLINE_VISIBILITY
    map& operator=(const map& __m)
        {
#ifndef _LIBCPP_CXX03_LANG
            __tree_ = __m.__tree_;
#else
            if (this != &__m) {
                __tree_.clear();
                __tree_.value_comp() = __m.__tree_.value_comp();
                __tree_.__copy_assign_alloc(__m.__tree_);
                insert(__m.begin(), __m.end());
            }
#endif
            return *this;
        }

#ifndef _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY
    map(map&& __m)
        _NOEXCEPT_(is_nothrow_move_constructible<__base>::value)
        : __tree_(_VSTD::move(__m.__tree_))
        {
        }

    map(map&& __m, const allocator_type& __a);

    _LIBCPP_INLINE_VISIBILITY
    map& operator=(map&& __m)
        _NOEXCEPT_(is_nothrow_move_assignable<__base>::value)
        {
            __tree_ = _VSTD::move(__m.__tree_);
            return *this;
        }

    _LIBCPP_INLINE_VISIBILITY
    map(initializer_list<value_type> __il, const key_compare& __comp = key_compare())
        : __tree_(__vc(__comp))
        {
            insert(__il.begin(), __il.end());
        }

    _LIBCPP_INLINE_VISIBILITY
    map(initializer_list<value_type> __il, const key_compare& __comp, const allocator_type& __a)
        : __tree_(__vc(__comp), typename __base::allocator_type(__a))
        {
            insert(__il.begin(), __il.end());
        }

#if _LIBCPP_STD_VER > 11
    _LIBCPP_INLINE_VISIBILITY
    map(initializer_list<value_type> __il, const allocator_type& __a)
        : map(__il, key_compare(), __a) {}
#endif

    _LIBCPP_INLINE_VISIBILITY
    map& operator=(initializer_list<value_type> __il)
        {
            __tree_.__assign_unique(__il.begin(), __il.end());
            return *this;
        }

#endif  // _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY
    explicit map(const allocator_type& __a)
        : __tree_(typename __base::allocator_type(__a))
        {
        }

    _LIBCPP_INLINE_VISIBILITY
    map(const map& __m, const allocator_type& __a)
        : __tree_(__m.__tree_.value_comp(), typename __base::allocator_type(__a))
        {
            insert(__m.begin(), __m.end());
        }

    _LIBCPP_INLINE_VISIBILITY
          iterator begin() _NOEXCEPT {return __tree_.begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator begin() const _NOEXCEPT {return __tree_.begin();}
    _LIBCPP_INLINE_VISIBILITY
          iterator end() _NOEXCEPT {return __tree_.end();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator end() const _NOEXCEPT {return __tree_.end();}

    _LIBCPP_INLINE_VISIBILITY
          reverse_iterator rbegin() _NOEXCEPT {return reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rbegin() const _NOEXCEPT
        {return const_reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
          reverse_iterator rend() _NOEXCEPT
            {return       reverse_iterator(begin());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rend() const _NOEXCEPT
        {return const_reverse_iterator(begin());}

    _LIBCPP_INLINE_VISIBILITY
    const_iterator cbegin() const _NOEXCEPT {return begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator cend() const _NOEXCEPT {return end();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crbegin() const _NOEXCEPT {return rbegin();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crend() const _NOEXCEPT {return rend();}

     _LIBCPP_INLINE_VISIBILITY
    bool      empty() const _NOEXCEPT {return __tree_.size() == 0;}
    _LIBCPP_INLINE_VISIBILITY
    size_type size() const _NOEXCEPT {return __tree_.size();}
    _LIBCPP_INLINE_VISIBILITY
    size_type max_size() const _NOEXCEPT {return __tree_.max_size();}

    mapped_type& operator[](const key_type& __k);
#ifndef _LIBCPP_CXX03_LANG
    mapped_type& operator[](key_type&& __k);
#endif

          mapped_type& at(const key_type& __k);
    const mapped_type& at(const key_type& __k) const;

    _LIBCPP_INLINE_VISIBILITY
    allocator_type get_allocator() const _NOEXCEPT {return allocator_type(__tree_.__alloc());}
    _LIBCPP_INLINE_VISIBILITY
    key_compare    key_comp()      const {return __tree_.value_comp().key_comp();}
    _LIBCPP_INLINE_VISIBILITY
    value_compare  value_comp()    const {return value_compare(__tree_.value_comp().key_comp());}

#ifndef _LIBCPP_CXX03_LANG
    template <class ..._Args>
    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool> emplace(_Args&& ...__args) {
        return __tree_.__emplace_unique(_VSTD::forward<_Args>(__args)...);
    }

    template <class ..._Args>
    _LIBCPP_INLINE_VISIBILITY
    iterator emplace_hint(const_iterator __p, _Args&& ...__args) {
        return __tree_.__emplace_hint_unique(__p.__i_, _VSTD::forward<_Args>(__args)...);
    }

    template <class _Pp,
              class = typename enable_if<is_constructible<value_type, _Pp>::value>::type>
        _LIBCPP_INLINE_VISIBILITY
        pair<iterator, bool> insert(_Pp&& __p)
            {return __tree_.__insert_unique(_VSTD::forward<_Pp>(__p));}

    template <class _Pp,
              class = typename enable_if<is_constructible<value_type, _Pp>::value>::type>
        _LIBCPP_INLINE_VISIBILITY
        iterator insert(const_iterator __pos, _Pp&& __p)
            {return __tree_.__insert_unique(__pos.__i_, _VSTD::forward<_Pp>(__p));}

#endif  // _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool>
        insert(const value_type& __v) {return __tree_.__insert_unique(__v);}

    _LIBCPP_INLINE_VISIBILITY
    iterator
        insert(const_iterator __p, const value_type& __v)
            {return __tree_.__insert_unique(__p.__i_, __v);}

#ifndef _LIBCPP_CXX03_LANG
    _LIBCPP_INLINE_VISIBILITY
    pair<iterator, bool>
    insert(value_type&& __v) {return __tree_.__insert_unique(_VSTD::move(__v));}

    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __p,  value_type&& __v)
    {return __tree_.__insert_unique(__p.__i_, _VSTD::move(__v));}

    _LIBCPP_INLINE_VISIBILITY
    void insert(initializer_list<value_type> __il)
        {insert(__il.begin(), __il.end());}
#endif

    template <class _InputIterator>
        _LIBCPP_INLINE_VISIBILITY
        void insert(_InputIterator __f, _InputIterator __l)
        {
            for (const_iterator __e = cend(); __f != __l; ++__f)
                insert(__e.__i_, *__f);
        }

#if _LIBCPP_STD_VER > 14

    template <class... _Args>
        _LIBCPP_INLINE_VISIBILITY
        pair<iterator, bool> try_emplace(const key_type& __k, _Args&&... __args)
    {
        return __tree_.__emplace_unique_key_args(__k,
            _VSTD::piecewise_construct,
            _VSTD::forward_as_tuple(__k),
            _VSTD::forward_as_tuple(_VSTD::forward<_Args>(__args)...));
    }

    template <class... _Args>
        _LIBCPP_INLINE_VISIBILITY
        pair<iterator, bool> try_emplace(key_type&& __k, _Args&&... __args)
    {
        return __tree_.__emplace_unique_key_args(__k,
            _VSTD::piecewise_construct,
            _VSTD::forward_as_tuple(_VSTD::move(__k)),
            _VSTD::forward_as_tuple(_VSTD::forward<_Args>(__args)...));
    }

    template <class... _Args>
        _LIBCPP_INLINE_VISIBILITY
        iterator try_emplace(const_iterator __h, const key_type& __k, _Args&&... __args)
    {
        return __tree_.__emplace_hint_unique_key_args(__h.__i_, __k,
            _VSTD::piecewise_construct,
            _VSTD::forward_as_tuple(__k),
            _VSTD::forward_as_tuple(_VSTD::forward<_Args>(__args)...));
    }

    template <class... _Args>
        _LIBCPP_INLINE_VISIBILITY
        iterator try_emplace(const_iterator __h, key_type&& __k, _Args&&... __args)
    {
        return __tree_.__emplace_hint_unique_key_args(__h.__i_, __k,
            _VSTD::piecewise_construct,
            _VSTD::forward_as_tuple(_VSTD::move(__k)),
            _VSTD::forward_as_tuple(_VSTD::forward<_Args>(__args)...));
    }

    template <class _Vp>
        _LIBCPP_INLINE_VISIBILITY
        pair<iterator, bool> insert_or_assign(const key_type& __k, _Vp&& __v)
    {
        iterator __p = lower_bound(__k);
        if ( __p != end() && !key_comp()(__k, __p->first))
        {
            __p->second = _VSTD::forward<_Vp>(__v);
            return _VSTD::make_pair(__p, false);
        }
        return _VSTD::make_pair(emplace_hint(__p, __k, _VSTD::forward<_Vp>(__v)), true);
    }

    template <class _Vp>
        _LIBCPP_INLINE_VISIBILITY
        pair<iterator, bool> insert_or_assign(key_type&& __k, _Vp&& __v)
    {
        iterator __p = lower_bound(__k);
        if ( __p != end() && !key_comp()(__k, __p->first))
        {
            __p->second = _VSTD::forward<_Vp>(__v);
            return _VSTD::make_pair(__p, false);
        }
        return _VSTD::make_pair(emplace_hint(__p, _VSTD::move(__k), _VSTD::forward<_Vp>(__v)), true);
    }

    template <class _Vp>
        _LIBCPP_INLINE_VISIBILITY
        iterator insert_or_assign(const_iterator __h, const key_type& __k, _Vp&& __v)
     {
        iterator __p = lower_bound(__k);
        if ( __p != end() && !key_comp()(__k, __p->first))
        {
            __p->second = _VSTD::forward<_Vp>(__v);
            return __p;
        }
        return emplace_hint(__h, __k, _VSTD::forward<_Vp>(__v));
     }

    template <class _Vp>
        _LIBCPP_INLINE_VISIBILITY
        iterator insert_or_assign(const_iterator __h, key_type&& __k, _Vp&& __v)
     {
        iterator __p = lower_bound(__k);
        if ( __p != end() && !key_comp()(__k, __p->first))
        {
            __p->second = _VSTD::forward<_Vp>(__v);
            return __p;
        }
        return emplace_hint(__h, _VSTD::move(__k), _VSTD::forward<_Vp>(__v));
     }

#endif // _LIBCPP_STD_VER > 14

    _LIBCPP_INLINE_VISIBILITY
    iterator erase(const_iterator __p) {return __tree_.erase(__p.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    iterator erase(iterator __p)       {return __tree_.erase(__p.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    size_type erase(const key_type& __k)
        {return __tree_.__erase_unique(__k);}
    _LIBCPP_INLINE_VISIBILITY
    iterator  erase(const_iterator __f, const_iterator __l)
        {return __tree_.erase(__f.__i_, __l.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    void clear() _NOEXCEPT {__tree_.clear();}

    _LIBCPP_INLINE_VISIBILITY
    void swap(map& __m)
        _NOEXCEPT_(__is_nothrow_swappable<__base>::value)
        {__tree_.swap(__m.__tree_);}

    _LIBCPP_INLINE_VISIBILITY
    iterator find(const key_type& __k)             {return __tree_.find(__k);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator find(const key_type& __k) const {return __tree_.find(__k);}
#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,iterator>::type
    find(const _K2& __k)                           {return __tree_.find(__k);}
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,const_iterator>::type
    find(const _K2& __k) const                     {return __tree_.find(__k);}
#endif

    _LIBCPP_INLINE_VISIBILITY
    size_type      count(const key_type& __k) const
        {return __tree_.__count_unique(__k);}
#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,size_type>::type
    count(const _K2& __k) const {return __tree_.__count_unique(__k);}
#endif
    _LIBCPP_INLINE_VISIBILITY
    iterator lower_bound(const key_type& __k)
        {return __tree_.lower_bound(__k);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator lower_bound(const key_type& __k) const
        {return __tree_.lower_bound(__k);}
#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,iterator>::type
    lower_bound(const _K2& __k)       {return __tree_.lower_bound(__k);}

    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,const_iterator>::type
    lower_bound(const _K2& __k) const {return __tree_.lower_bound(__k);}
#endif

    _LIBCPP_INLINE_VISIBILITY
    iterator upper_bound(const key_type& __k)
        {return __tree_.upper_bound(__k);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator upper_bound(const key_type& __k) const
        {return __tree_.upper_bound(__k);}
#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,iterator>::type
    upper_bound(const _K2& __k)       {return __tree_.upper_bound(__k);}
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,const_iterator>::type
    upper_bound(const _K2& __k) const {return __tree_.upper_bound(__k);}
#endif

    _LIBCPP_INLINE_VISIBILITY
    pair<iterator,iterator> equal_range(const key_type& __k)
        {return __tree_.__equal_range_unique(__k);}
    _LIBCPP_INLINE_VISIBILITY
    pair<const_iterator,const_iterator> equal_range(const key_type& __k) const
        {return __tree_.__equal_range_unique(__k);}
#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,pair<iterator,iterator>>::type
    equal_range(const _K2& __k)       {return __tree_.__equal_range_unique(__k);}
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,pair<const_iterator,const_iterator>>::type
    equal_range(const _K2& __k) const {return __tree_.__equal_range_unique(__k);}
#endif

private:
    typedef typename __base::__node                    __node;
    typedef typename __base::__node_allocator          __node_allocator;
    typedef typename __base::__node_pointer            __node_pointer;
    typedef typename __base::__node_base_pointer       __node_base_pointer;
    typedef typename __base::__parent_pointer          __parent_pointer;

    typedef __map_node_destructor<__node_allocator> _Dp;
    typedef unique_ptr<__node, _Dp> __node_holder;

#ifdef _LIBCPP_CXX03_LANG
    __node_holder __construct_node_with_key(const key_type& __k);
#endif
};


#ifndef _LIBCPP_CXX03_LANG
template <class _Key, class _Tp, class _Compare, class _Allocator>
map<_Key, _Tp, _Compare, _Allocator>::map(map&& __m, const allocator_type& __a)
    : __tree_(_VSTD::move(__m.__tree_), typename __base::allocator_type(__a))
{
    if (__a != __m.get_allocator())
    {
        const_iterator __e = cend();
        while (!__m.empty())
            __tree_.__insert_unique(__e.__i_,
                    _VSTD::move(__m.__tree_.remove(__m.begin().__i_)->__value_.__nc));
    }
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
_Tp&
map<_Key, _Tp, _Compare, _Allocator>::operator[](const key_type& __k)
{
    return __tree_.__emplace_unique_key_args(__k,
        _VSTD::piecewise_construct,
        _VSTD::forward_as_tuple(__k),
        _VSTD::forward_as_tuple()).first->__cc.second;
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
_Tp&
map<_Key, _Tp, _Compare, _Allocator>::operator[](key_type&& __k)
{
    return __tree_.__emplace_unique_key_args(__k,
        _VSTD::piecewise_construct,
        _VSTD::forward_as_tuple(_VSTD::move(__k)),
        _VSTD::forward_as_tuple()).first->__cc.second;
}

#else // _LIBCPP_CXX03_LANG

template <class _Key, class _Tp, class _Compare, class _Allocator>
typename map<_Key, _Tp, _Compare, _Allocator>::__node_holder
map<_Key, _Tp, _Compare, _Allocator>::__construct_node_with_key(const key_type& __k)
{
    __node_allocator& __na = __tree_.__node_alloc();
    __node_holder __h(__node_traits::allocate(__na, 1), _Dp(__na));
    __node_traits::construct(__na, _VSTD::addressof(__h->__value_.__cc.first), __k);
    __h.get_deleter().__first_constructed = true;
    __node_traits::construct(__na, _VSTD::addressof(__h->__value_.__cc.second));
    __h.get_deleter().__second_constructed = true;
    return _LIBCPP_EXPLICIT_MOVE(__h);  // explicitly moved for C++03
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
_Tp&
map<_Key, _Tp, _Compare, _Allocator>::operator[](const key_type& __k)
{
    __parent_pointer __parent;
    __node_base_pointer& __child = __tree_.__find_equal(__parent, __k);
    __node_pointer __r = static_cast<__node_pointer>(__child);
    if (__child == nullptr)
    {
        __node_holder __h = __construct_node_with_key(__k);
        __tree_.__insert_node_at(__parent, __child, static_cast<__node_base_pointer>(__h.get()));
        __r = __h.release();
    }
    return __r->__value_.__cc.second;
}

#endif  // _LIBCPP_CXX03_LANG

template <class _Key, class _Tp, class _Compare, class _Allocator>
_Tp&
map<_Key, _Tp, _Compare, _Allocator>::at(const key_type& __k)
{
    __parent_pointer __parent;
    __node_base_pointer& __child = __tree_.__find_equal(__parent, __k);
#ifndef _LIBCPP_NO_EXCEPTIONS
    if (__child == nullptr)
        throw out_of_range("map::at:  key not found");
#endif  // _LIBCPP_NO_EXCEPTIONS
    return static_cast<__node_pointer>(__child)->__value_.__cc.second;
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
const _Tp&
map<_Key, _Tp, _Compare, _Allocator>::at(const key_type& __k) const
{
    __parent_pointer __parent;
    __node_base_pointer __child = __tree_.__find_equal(__parent, __k);
#ifndef _LIBCPP_NO_EXCEPTIONS
    if (__child == nullptr)
        throw out_of_range("map::at:  key not found");
#endif  // _LIBCPP_NO_EXCEPTIONS
    return static_cast<__node_pointer>(__child)->__value_.__cc.second;
}


template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator==(const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return __x.size() == __y.size() && _VSTD::equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator< (const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return _VSTD::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__x == __y);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator> (const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return __y < __x;
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator>=(const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__x < __y);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator<=(const map<_Key, _Tp, _Compare, _Allocator>& __x,
           const map<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__y < __x);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
swap(map<_Key, _Tp, _Compare, _Allocator>& __x,
     map<_Key, _Tp, _Compare, _Allocator>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

template <class _Key, class _Tp, class _Compare = less<_Key>,
          class _Allocator = allocator<pair<const _Key, _Tp> > >
class _LIBCPP_TEMPLATE_VIS multimap
{
public:
    // types:
    typedef _Key                                     key_type;
    typedef _Tp                                      mapped_type;
    typedef pair<const key_type, mapped_type>        value_type;
    typedef pair<key_type, mapped_type>              __nc_value_type;
    typedef _Compare                                 key_compare;
    typedef _Allocator                               allocator_type;
    typedef value_type&                              reference;
    typedef const value_type&                        const_reference;

    static_assert((is_same<typename allocator_type::value_type, value_type>::value),
                  "Allocator::value_type must be same type as value_type");

    class _LIBCPP_TEMPLATE_VIS value_compare
        : public binary_function<value_type, value_type, bool>
    {
        friend class multimap;
    protected:
        key_compare comp;

        _LIBCPP_INLINE_VISIBILITY
        value_compare(key_compare c) : comp(c) {}
    public:
        _LIBCPP_INLINE_VISIBILITY
        bool operator()(const value_type& __x, const value_type& __y) const
            {return comp(__x.first, __y.first);}
    };

private:

    typedef _VSTD::__value_type<key_type, mapped_type>             __value_type;
    typedef __map_value_compare<key_type, __value_type, key_compare> __vc;
    typedef typename __rebind_alloc_helper<allocator_traits<allocator_type>,
                                                 __value_type>::type __allocator_type;
    typedef __tree<__value_type, __vc, __allocator_type>            __base;
    typedef typename __base::__node_traits                          __node_traits;
    typedef allocator_traits<allocator_type>                        __alloc_traits;

    __base __tree_;

public:
    typedef typename __alloc_traits::pointer               pointer;
    typedef typename __alloc_traits::const_pointer         const_pointer;
    typedef typename __alloc_traits::size_type             size_type;
    typedef typename __alloc_traits::difference_type       difference_type;
    typedef __map_iterator<typename __base::iterator>      iterator;
    typedef __map_const_iterator<typename __base::const_iterator> const_iterator;
    typedef _VSTD::reverse_iterator<iterator>               reverse_iterator;
    typedef _VSTD::reverse_iterator<const_iterator>         const_reverse_iterator;

    _LIBCPP_INLINE_VISIBILITY
    multimap()
        _NOEXCEPT_(
            is_nothrow_default_constructible<allocator_type>::value &&
            is_nothrow_default_constructible<key_compare>::value &&
            is_nothrow_copy_constructible<key_compare>::value)
        : __tree_(__vc(key_compare())) {}

    _LIBCPP_INLINE_VISIBILITY
    explicit multimap(const key_compare& __comp)
        _NOEXCEPT_(
            is_nothrow_default_constructible<allocator_type>::value &&
            is_nothrow_copy_constructible<key_compare>::value)
        : __tree_(__vc(__comp)) {}

    _LIBCPP_INLINE_VISIBILITY
    explicit multimap(const key_compare& __comp, const allocator_type& __a)
        : __tree_(__vc(__comp), typename __base::allocator_type(__a)) {}

    template <class _InputIterator>
        _LIBCPP_INLINE_VISIBILITY
        multimap(_InputIterator __f, _InputIterator __l,
            const key_compare& __comp = key_compare())
        : __tree_(__vc(__comp))
        {
            insert(__f, __l);
        }

    template <class _InputIterator>
        _LIBCPP_INLINE_VISIBILITY
        multimap(_InputIterator __f, _InputIterator __l,
            const key_compare& __comp, const allocator_type& __a)
        : __tree_(__vc(__comp), typename __base::allocator_type(__a))
        {
            insert(__f, __l);
        }

#if _LIBCPP_STD_VER > 11
    template <class _InputIterator>
    _LIBCPP_INLINE_VISIBILITY
    multimap(_InputIterator __f, _InputIterator __l, const allocator_type& __a)
        : multimap(__f, __l, key_compare(), __a) {}
#endif

    _LIBCPP_INLINE_VISIBILITY
    multimap(const multimap& __m)
        : __tree_(__m.__tree_.value_comp(),
          __alloc_traits::select_on_container_copy_construction(__m.__tree_.__alloc()))
        {
            insert(__m.begin(), __m.end());
        }

    _LIBCPP_INLINE_VISIBILITY
    multimap& operator=(const multimap& __m)
        {
#ifndef _LIBCPP_CXX03_LANG
            __tree_ = __m.__tree_;
#else
            if (this != &__m) {
                __tree_.clear();
                __tree_.value_comp() = __m.__tree_.value_comp();
                __tree_.__copy_assign_alloc(__m.__tree_);
                insert(__m.begin(), __m.end());
            }
#endif
            return *this;
        }

#ifndef _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY
    multimap(multimap&& __m)
        _NOEXCEPT_(is_nothrow_move_constructible<__base>::value)
        : __tree_(_VSTD::move(__m.__tree_))
        {
        }

    multimap(multimap&& __m, const allocator_type& __a);

    _LIBCPP_INLINE_VISIBILITY
    multimap& operator=(multimap&& __m)
        _NOEXCEPT_(is_nothrow_move_assignable<__base>::value)
        {
            __tree_ = _VSTD::move(__m.__tree_);
            return *this;
        }

    _LIBCPP_INLINE_VISIBILITY
    multimap(initializer_list<value_type> __il, const key_compare& __comp = key_compare())
        : __tree_(__vc(__comp))
        {
            insert(__il.begin(), __il.end());
        }

    _LIBCPP_INLINE_VISIBILITY
    multimap(initializer_list<value_type> __il, const key_compare& __comp, const allocator_type& __a)
        : __tree_(__vc(__comp), typename __base::allocator_type(__a))
        {
            insert(__il.begin(), __il.end());
        }

#if _LIBCPP_STD_VER > 11
    _LIBCPP_INLINE_VISIBILITY
    multimap(initializer_list<value_type> __il, const allocator_type& __a)
        : multimap(__il, key_compare(), __a) {}
#endif

    _LIBCPP_INLINE_VISIBILITY
    multimap& operator=(initializer_list<value_type> __il)
        {
            __tree_.__assign_multi(__il.begin(), __il.end());
            return *this;
        }

#endif  // _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY
    explicit multimap(const allocator_type& __a)
        : __tree_(typename __base::allocator_type(__a))
        {
        }

    _LIBCPP_INLINE_VISIBILITY
    multimap(const multimap& __m, const allocator_type& __a)
        : __tree_(__m.__tree_.value_comp(), typename __base::allocator_type(__a))
        {
            insert(__m.begin(), __m.end());
        }

    _LIBCPP_INLINE_VISIBILITY
          iterator begin() _NOEXCEPT {return __tree_.begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator begin() const _NOEXCEPT {return __tree_.begin();}
    _LIBCPP_INLINE_VISIBILITY
          iterator end() _NOEXCEPT {return __tree_.end();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator end() const _NOEXCEPT {return __tree_.end();}

    _LIBCPP_INLINE_VISIBILITY
          reverse_iterator rbegin() _NOEXCEPT {return reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rbegin() const _NOEXCEPT
        {return const_reverse_iterator(end());}
    _LIBCPP_INLINE_VISIBILITY
          reverse_iterator rend() _NOEXCEPT {return reverse_iterator(begin());}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator rend() const _NOEXCEPT
        {return const_reverse_iterator(begin());}

    _LIBCPP_INLINE_VISIBILITY
    const_iterator cbegin()  const _NOEXCEPT {return begin();}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator cend() const _NOEXCEPT {return end();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crbegin() const _NOEXCEPT {return rbegin();}
    _LIBCPP_INLINE_VISIBILITY
    const_reverse_iterator crend() const _NOEXCEPT {return rend();}

     _LIBCPP_INLINE_VISIBILITY
    bool empty() const _NOEXCEPT {return __tree_.size() == 0;}
    _LIBCPP_INLINE_VISIBILITY
    size_type size() const _NOEXCEPT {return __tree_.size();}
    _LIBCPP_INLINE_VISIBILITY
    size_type max_size() const _NOEXCEPT {return __tree_.max_size();}

    _LIBCPP_INLINE_VISIBILITY
    allocator_type get_allocator() const _NOEXCEPT {return allocator_type(__tree_.__alloc());}
    _LIBCPP_INLINE_VISIBILITY
    key_compare    key_comp() const {return __tree_.value_comp().key_comp();}
    _LIBCPP_INLINE_VISIBILITY
    value_compare  value_comp() const
        {return value_compare(__tree_.value_comp().key_comp());}

#ifndef _LIBCPP_CXX03_LANG

    template <class ..._Args>
    _LIBCPP_INLINE_VISIBILITY
    iterator emplace(_Args&& ...__args) {
        return __tree_.__emplace_multi(_VSTD::forward<_Args>(__args)...);
    }

    template <class ..._Args>
    _LIBCPP_INLINE_VISIBILITY
    iterator emplace_hint(const_iterator __p, _Args&& ...__args) {
        return __tree_.__emplace_hint_multi(__p.__i_, _VSTD::forward<_Args>(__args)...);
    }

    template <class _Pp,
              class = typename enable_if<is_constructible<value_type, _Pp>::value>::type>
        _LIBCPP_INLINE_VISIBILITY
        iterator insert(_Pp&& __p)
            {return __tree_.__insert_multi(_VSTD::forward<_Pp>(__p));}

    template <class _Pp,
              class = typename enable_if<is_constructible<value_type, _Pp>::value>::type>
        _LIBCPP_INLINE_VISIBILITY
        iterator insert(const_iterator __pos, _Pp&& __p)
            {return __tree_.__insert_multi(__pos.__i_, _VSTD::forward<_Pp>(__p));}

    _LIBCPP_INLINE_VISIBILITY
    iterator insert(value_type&& __v)
        {return __tree_.__insert_multi(_VSTD::move(__v));}

    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __p, value_type&& __v)
        {return __tree_.__insert_multi(__p.__i_, _VSTD::move(__v));}


    _LIBCPP_INLINE_VISIBILITY
    void insert(initializer_list<value_type> __il)
        {insert(__il.begin(), __il.end());}

#endif  // _LIBCPP_CXX03_LANG

    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const value_type& __v) {return __tree_.__insert_multi(__v);}

    _LIBCPP_INLINE_VISIBILITY
    iterator insert(const_iterator __p, const value_type& __v)
            {return __tree_.__insert_multi(__p.__i_, __v);}

    template <class _InputIterator>
        _LIBCPP_INLINE_VISIBILITY
        void insert(_InputIterator __f, _InputIterator __l)
        {
            for (const_iterator __e = cend(); __f != __l; ++__f)
                __tree_.__insert_multi(__e.__i_, *__f);
        }

    _LIBCPP_INLINE_VISIBILITY
    iterator erase(const_iterator __p) {return __tree_.erase(__p.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    iterator erase(iterator __p)       {return __tree_.erase(__p.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    size_type erase(const key_type& __k) {return __tree_.__erase_multi(__k);}
    _LIBCPP_INLINE_VISIBILITY
    iterator  erase(const_iterator __f, const_iterator __l)
        {return __tree_.erase(__f.__i_, __l.__i_);}
    _LIBCPP_INLINE_VISIBILITY
    void clear() {__tree_.clear();}

    _LIBCPP_INLINE_VISIBILITY
    void swap(multimap& __m)
        _NOEXCEPT_(__is_nothrow_swappable<__base>::value)
        {__tree_.swap(__m.__tree_);}

    _LIBCPP_INLINE_VISIBILITY
    iterator find(const key_type& __k)             {return __tree_.find(__k);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator find(const key_type& __k) const {return __tree_.find(__k);}
#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,iterator>::type
    find(const _K2& __k)                           {return __tree_.find(__k);}
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,const_iterator>::type
    find(const _K2& __k) const                     {return __tree_.find(__k);}
#endif

    _LIBCPP_INLINE_VISIBILITY
    size_type      count(const key_type& __k) const
        {return __tree_.__count_multi(__k);}
#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,size_type>::type
    count(const _K2& __k) const {return __tree_.__count_multi(__k);}
#endif
    _LIBCPP_INLINE_VISIBILITY
    iterator lower_bound(const key_type& __k)
        {return __tree_.lower_bound(__k);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator lower_bound(const key_type& __k) const
            {return __tree_.lower_bound(__k);}
#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,iterator>::type
    lower_bound(const _K2& __k)       {return __tree_.lower_bound(__k);}

    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,const_iterator>::type
    lower_bound(const _K2& __k) const {return __tree_.lower_bound(__k);}
#endif

    _LIBCPP_INLINE_VISIBILITY
    iterator upper_bound(const key_type& __k)
            {return __tree_.upper_bound(__k);}
    _LIBCPP_INLINE_VISIBILITY
    const_iterator upper_bound(const key_type& __k) const
            {return __tree_.upper_bound(__k);}
#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,iterator>::type
    upper_bound(const _K2& __k)       {return __tree_.upper_bound(__k);}
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,const_iterator>::type
    upper_bound(const _K2& __k) const {return __tree_.upper_bound(__k);}
#endif

    _LIBCPP_INLINE_VISIBILITY
    pair<iterator,iterator>             equal_range(const key_type& __k)
            {return __tree_.__equal_range_multi(__k);}
    _LIBCPP_INLINE_VISIBILITY
    pair<const_iterator,const_iterator> equal_range(const key_type& __k) const
            {return __tree_.__equal_range_multi(__k);}
#if _LIBCPP_STD_VER > 11
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,pair<iterator,iterator>>::type
    equal_range(const _K2& __k)       {return __tree_.__equal_range_multi(__k);}
    template <typename _K2>
    _LIBCPP_INLINE_VISIBILITY
    typename enable_if<__is_transparent<_Compare, _K2>::value,pair<const_iterator,const_iterator>>::type
    equal_range(const _K2& __k) const {return __tree_.__equal_range_multi(__k);}
#endif

private:
    typedef typename __base::__node                    __node;
    typedef typename __base::__node_allocator          __node_allocator;
    typedef typename __base::__node_pointer            __node_pointer;

    typedef __map_node_destructor<__node_allocator> _Dp;
    typedef unique_ptr<__node, _Dp> __node_holder;
};

#ifndef _LIBCPP_CXX03_LANG
template <class _Key, class _Tp, class _Compare, class _Allocator>
multimap<_Key, _Tp, _Compare, _Allocator>::multimap(multimap&& __m, const allocator_type& __a)
    : __tree_(_VSTD::move(__m.__tree_), typename __base::allocator_type(__a))
{
    if (__a != __m.get_allocator())
    {
        const_iterator __e = cend();
        while (!__m.empty())
            __tree_.__insert_multi(__e.__i_,
                    _VSTD::move(__m.__tree_.remove(__m.begin().__i_)->__value_.__nc));
    }
}
#endif

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator==(const multimap<_Key, _Tp, _Compare, _Allocator>& __x,
           const multimap<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return __x.size() == __y.size() && _VSTD::equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator< (const multimap<_Key, _Tp, _Compare, _Allocator>& __x,
           const multimap<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return _VSTD::lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator!=(const multimap<_Key, _Tp, _Compare, _Allocator>& __x,
           const multimap<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__x == __y);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator> (const multimap<_Key, _Tp, _Compare, _Allocator>& __x,
           const multimap<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return __y < __x;
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator>=(const multimap<_Key, _Tp, _Compare, _Allocator>& __x,
           const multimap<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__x < __y);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
bool
operator<=(const multimap<_Key, _Tp, _Compare, _Allocator>& __x,
           const multimap<_Key, _Tp, _Compare, _Allocator>& __y)
{
    return !(__y < __x);
}

template <class _Key, class _Tp, class _Compare, class _Allocator>
inline _LIBCPP_INLINE_VISIBILITY
void
swap(multimap<_Key, _Tp, _Compare, _Allocator>& __x,
     multimap<_Key, _Tp, _Compare, _Allocator>& __y)
    _NOEXCEPT_(_NOEXCEPT_(__x.swap(__y)))
{
    __x.swap(__y);
}

_LIBCPP_END_NAMESPACE_STD

#endif  // _LIBCPP_MAP
