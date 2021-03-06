/*
 * Copyright (c) 2011-2013 libgroestlcoin developers (see AUTHORS)
 *
 * This file is part of libgroestlcoin.
 *
 * libgroestlcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBGROESTLCOIN_ENDIAN_HPP
#define LIBGROESTLCOIN_ENDIAN_HPP

#include <groestlcoin/groestlcoin/define.hpp>
#include <groestlcoin/groestlcoin/utility/data.hpp>

namespace libgroestlcoin {

template <typename T, typename Iterator>
T from_big_endian(Iterator start, Iterator end);

template <typename T, typename Iterator>
T from_little_endian(Iterator start, Iterator end);

template <typename T, typename Iterator>
T from_big_endian_unsafe(Iterator in);

template <typename T, typename Iterator>
T from_little_endian_unsafe(Iterator in);

template <typename T>
byte_array<sizeof(T)> to_big_endian(T n);

template <typename T>
byte_array<sizeof(T)> to_little_endian(T n);

byte_array<1> to_byte(uint8_t byte);

} // namespace libgroestlcoin

#include <groestlcoin/groestlcoin/impl/utility/endian.ipp>

#endif
