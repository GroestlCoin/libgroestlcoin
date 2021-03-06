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
#include <groestlcoin/groestlcoin/stealth.hpp>

#include <groestlcoin/groestlcoin/math/hash.hpp>
#include <groestlcoin/groestlcoin/utility/assert.hpp>

namespace libgroestlcoin {

binary_type calculate_stealth_prefix(const script_type& stealth_script)
{
    const auto stealth_data = save_script(stealth_script);
    const auto index = groestlcoin_hash(stealth_data);
    const auto bitsize = binary_type::bits_per_block * sizeof(uint32_t);
    return binary_type(bitsize, index);
}

bool extract_stealth_info(stealth_info& info,
    const script_type& output_script)
{
    if (output_script.type() != payment_type::stealth_info)
        return false;

    info.bitfield = calculate_stealth_prefix(output_script);
    if (output_script.operations().size() < 2)
        return false;

    const data_chunk& data = output_script.operations()[1].data;
    if (data.size() < hash_size)
        return false;

    std::copy(data.begin(), data.begin() + hash_size,
        info.ephem_pubkey_hash.begin());
    return true;
}

ec_secret shared_secret(const ec_secret& secret, const ec_point& pubkey)
{
    auto final = pubkey;
    DEBUG_ONLY(const auto success =) ec_multiply(final, secret);
    BITCOIN_ASSERT(success);
    return sha256_hash(final);
}

ec_point uncover_stealth(const ec_point& ephem_pubkey, 
    const ec_secret& scan_secret, const ec_point& spend_pubkey)
{
    auto final = spend_pubkey;
    const auto shared = shared_secret(scan_secret, ephem_pubkey);
    DEBUG_ONLY(const auto success = ) ec_add(final, shared);
    BITCOIN_ASSERT(success);
    return final;
}

ec_secret uncover_stealth_secret(const ec_point& pubkey,
    const ec_secret& secret, const ec_secret& spend_secret)
{
    auto final = spend_secret;
    const auto shared = shared_secret(secret, pubkey);
    DEBUG_ONLY(const auto success = ) ec_add(final, shared);
    BITCOIN_ASSERT(success);
    return final;
}

} // namespace libgroestlcoin

