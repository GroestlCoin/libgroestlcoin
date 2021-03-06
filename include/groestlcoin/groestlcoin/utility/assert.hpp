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
#ifndef LIBGROESTLCOIN_ASSERT_HPP
#define LIBGROESTLCOIN_ASSERT_HPP

#ifdef NDEBUG
    #define BITCOIN_ASSERT(expr)
    #define BITCOIN_ASSERT_MSG(expr, msg)
    #define DEBUG_ONLY(expression)
#else
    #include <cassert>
    #define BITCOIN_ASSERT(expr) assert(expr)
    #define BITCOIN_ASSERT_MSG(expr, msg) assert((expr)&&(msg))
    #define DEBUG_ONLY(expression) expression
#endif

#endif
