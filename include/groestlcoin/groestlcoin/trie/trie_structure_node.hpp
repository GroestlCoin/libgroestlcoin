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

#ifndef LIBGROESTLCOIN_TRIE_STRUCTURE_NODE_HPP
#define LIBGROESTLCOIN_TRIE_STRUCTURE_NODE_HPP

#include <boost/utility.hpp>
#include <groestlcoin/groestlcoin/trie/trie_value_node.hpp>
#include <groestlcoin/groestlcoin/utility/binary.hpp>

namespace libgroestlcoin {

template <typename Value>
class trie_structure_node : private boost::noncopyable
{
public:

    typedef Value value_type;
    typedef trie_structure_node<value_type> structure_node_type;
    typedef trie_value_node<value_type> value_node_type;

    structure_node_type* parent;

    value_node_type* value_head;
    value_node_type* value_tail;

    value_node_type* value_leftmost;
    value_node_type* value_rightmost;

    structure_node_type* previous;
    structure_node_type* next;

    binary_type label;

public:

    explicit trie_structure_node();

    bool has_children() const;

    bool has_value() const;

    structure_node_type* get_child(bool matching_bit) const;

    void set_child(bool matching_bit, structure_node_type* node);

    structure_node_type* get_first_child() const;

    structure_node_type* get_last_child() const;

private:

    structure_node_type* children_[2];

};

} // namespace libgroestlcoin

#include <groestlcoin/groestlcoin/impl/trie/trie_structure_node.ipp>

#endif
