#include <limits> // for std::numeric_limits


//  auto __begin = std::begin(range);
//  auto __end = std::end(range);
//  for (; __begin != __end; ++__begin) {
//       auto x = *__begin;
//       code_block
//  }

template < class IntegralType >
class numeric_iterator {
public:
    explicit numeric_iterator(IntegralType position = 0) : value_{position} {/*emtpy!*/}

    IntegralType operator* () const
    {
        return value_;
    }

    numeric_iterator<IntegralType> operator ++ ()
    {
        ++value_;
        return *this;
    }

    bool operator != (const numeric_iterator& other) const
    {
        return value_ != other.value_;
    }

private:
    IntegralType value_;
};


template < class IntegralType >
class reverse_numeric_iterator {
public:
    explicit reverse_numeric_iterator(IntegralType position = 0) : value_{ position } {/*emtpy!*/ }

    IntegralType operator* () const
    {
        return value_;
    }

    reverse_numeric_iterator<IntegralType> operator ++ ()
    {
        --value_;
        return *this;
    }

    bool operator != (const reverse_numeric_iterator& other) const
    {
        return value_ != other.value_;
    }

private:
    IntegralType value_;
};

class size_range {
public:
    size_range(size_t start = std::numeric_limits<std::size_t>::min(), size_t end = std::numeric_limits<std::size_t>::max())
        : start_{start}, end_{end} {/*empty!*/}

    numeric_iterator<size_t> begin() const
    {
        return numeric_iterator<size_t> {start_};
    }

    numeric_iterator<size_t> end() const
    {
        return numeric_iterator<size_t> {end_};
    }

private:
    size_t start_, end_;
};


class reverse_size_range {
public:
    reverse_size_range(size_t start = std::numeric_limits<std::size_t>::min(), size_t end = std::numeric_limits<std::size_t>::max())
        : start_{ start }, end_{ end }  /*empty!*/
    {
    }

    reverse_numeric_iterator<size_t> begin() const
    {
        return reverse_numeric_iterator<size_t> {start_};
    }

    reverse_numeric_iterator<size_t> end() const
    {
        return reverse_numeric_iterator<size_t> {end_};
    }

private:
    size_t start_, end_;
};