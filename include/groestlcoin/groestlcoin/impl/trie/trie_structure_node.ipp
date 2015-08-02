/**
 * Copyright 2011-2015
 *
 * Modified from https://github.com/BoostGSoC13/boost.trie
 *
 * Distributed under the Boost Software License, Version 1.0.
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef LIBGROESTLCOIN_TRIE_STRUCTURE_NODE_IPP
#define LIBGROESTLCOIN_TRIE_STRUCTURE_NODE_IPP

namespace libgroestlcoin {

// trie_node implenentation
template<typename Value>
trie_structure_node<Value>::trie_structure_node()
    : parent(0), value_head(nullptr), value_tail(nullptr),
    value_leftmost(nullptr), value_rightmost(nullptr), previous(nullptr),
    next(nullptr), label()
{
    children_[0] = nullptr;
    children_[1] = nullptr;
}

template<typename Value>
bool trie_structure_node<Value>::has_children() const
{
    return (children_[0] != nullptr) || (children_[1] != nullptr);
}

template<typename Value>
bool trie_structure_node<Value>::has_value() const
{
    return !(value_head == nullptr);
}

template<typename Value>
typename trie_structure_node<Value>::structure_node_type*
    trie_structure_node<Value>::get_child(
        bool matching_bit) const
{
    return matching_bit ? children_[1] : children_[0];
}

template<typename Value>
void trie_structure_node<Value>::set_child(
    bool matching_bit, structure_node_type* node)
{
    int index = matching_bit ? 1 : 0;
    children_[index] = node;
}

template<typename Value>
typename trie_structure_node<Value>::structure_node_type*
    trie_structure_node<Value>::get_first_child() const
{
    auto result = children_[0];

    if (result == nullptr)
    {
        result = children_[1];
    }

    return result;
}

template<typename Value>
typename trie_structure_node<Value>::structure_node_type*
trie_structure_node<Value>::get_last_child() const
{
    auto result = children_[1];

    if (result == nullptr)
    {
        result = children_[0];
    }

    return result;
}

} // namespace libgroestlcoin

#endif
