/*
 * Copyright (c) 2011-2014 libgroestlcoin developers (see AUTHORS)
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
#include <groestlcoin/groestlcoin/math/checksum.hpp>

#include <groestlcoin/groestlcoin/math/hash.hpp>
#include <groestlcoin/groestlcoin/utility/endian.hpp>

namespace libgroestlcoin {

void append_checksum(data_chunk& data) {
	uint32_t checksum = groestlcoin_checksum(data);	//GRS
	extend_data(data, to_little_endian(checksum));
}

uint32_t groestlcoin_checksum(data_slice chunk)
{
    hash_digest hash = groestlcoin_hash(chunk);	//GRS
    return from_little_endian_unsafe<uint32_t>(hash.begin());
}

bool verify_checksum(data_slice data)
{
    // guard against insufficient data length
    if (data.size() < checksum_size)
        return false;

    data_slice body(data.begin(), data.end() - checksum_size);
    auto checksum = from_little_endian_unsafe<uint32_t>(data.end() - checksum_size);
    return groestlcoin_checksum(body) == checksum;	// GRS
}

} // namespace libgroestlcoin

