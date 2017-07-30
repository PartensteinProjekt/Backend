// ------------------------------------------------------------------------------
#pragma once
// ------------------------------------------------------------------------------

#include <map>
#include <initializer_list>
#include <vector>
#include <iostream>
#include <algorithm> // for std::copy
#include <iterator> // for std::ostream_iterator
#include <optional>

template < class T >
class trie {
public:
    template < class Iterator >
    void insert(Iterator beg, Iterator end)
    {
        if (beg == end) {
            return;
        }

        sub_tries_[*beg].insert(std::next(beg), end);
    }

    template < class Container >
    void insert(const Container& c)
    {
        insert(std::begin(c), std::end(c));
    }

    void insert(const std::initializer_list<T>& list)
    {
        insert(std::begin(list), std::end(list));
    }

    // depth-first search for all sub-nodes
    void print(std::vector<T>& nodes) const
    {
        if (sub_tries_.empty()) {
            std::copy(std::begin(nodes), std::end(nodes), std::ostream_iterator<T> {std::cout, " "});
            std::cout << '\n';
        }
        for (const auto& node : sub_tries_) {
            nodes.push_back(node.first);
            node.second.print(nodes);
            nodes.pop_back();
        }
    }

    void print() const
    {
        std::vector<T> nodes{};
        print(nodes);
    }

    template < class Iterator >
    std::optional<std::reference_wrapper<const trie>> sub_trie(Iterator it, Iterator end) const
    {
        if (it == end) {
            return ref(*this);
        }

        // its important to use 'find' and not the [] operator here.
        // The latter will create new nodes if it doesn't find a trie... which isn't quite what we want! ~ JSt
        auto found(sub_tries_.find(*it));
        if (found == std::end(sub_tries_)) {
            return {};
        }

        return found->second.sub_trie(std::next(it), end);
    }

    template < class Container >
    auto sub_trie(const Container& c)
    {
        return sub_trie(std::begin(c), std::end(c));
    }
private:
    std::map<T, trie> sub_tries_;
};