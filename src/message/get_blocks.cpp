/*
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
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
#include <bitcoin/bitcoin/message/get_blocks.hpp>

#include <bitcoin/bitcoin/constants.hpp>

namespace libbitcoin {
namespace message {

get_blocks::get_blocks()
{
}

get_blocks::get_blocks(const data_chunk& value)
: get_blocks(value.begin(), value.end())
{
}

get_blocks::operator const data_chunk() const
{
    data_chunk result(satoshi_size());
    auto serial = make_serializer(result.begin());

    serial.write_4_bytes(protocol_version);

    serial.write_variable_uint(start_hashes.size());

    for (hash_digest start_hash: start_hashes)
    {
        serial.write_hash(start_hash);
    }

    serial.write_hash(hash_stop);

    return result;
}

size_t get_blocks::satoshi_size() const
{
    return 36 +
        variable_uint_size(start_hashes.size()) +
        hash_size * start_hashes.size();
}

} // end message
} // end libbitcoin