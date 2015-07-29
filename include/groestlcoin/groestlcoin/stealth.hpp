/*
 * Copyright (c) 2011-2013 libbitcoin developers (see AUTHORS)
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
#ifndef LIBBITCOIN_STEALTH_HPP
#define LIBBITCOIN_STEALTH_HPP

#include <groestlcoin/groestlcoin/define.hpp>
#include <groestlcoin/groestlcoin/script.hpp>
#include <groestlcoin/groestlcoin/utility/binary.hpp>

namespace libbitcoin {

struct BC_API stealth_info
{
    hash_digest ephem_pubkey_hash;
    binary_type bitfield;
};

/**
 * Calculate the stealth binary prefix from the RETURN output.
 */
BC_API binary_type calculate_stealth_prefix(
    const script_type& stealth_script);

BC_API bool extract_stealth_info(stealth_info& info,
    const script_type& output_script);

BC_API ec_secret shared_secret(const ec_secret& secret,
    const ec_point& pubkey);

BC_API ec_point uncover_stealth(const ec_point& pubkey,
    const ec_secret& secret, const ec_point& spend_pubkey);

BC_API ec_secret uncover_stealth_secret(const ec_point& ephem_pubkey,
    const ec_secret& scan_secret, const ec_secret& spend_secret);

// Obsoleted this as it is identical to uncover_stealth(), only the
// parameter names and order differ. The reason is that either party can
// uncover the spend pubkey using the shared secret, which in turn can be
// generated by a secret and pubkey. Different values but the same function.
//BC_API ec_point initiate_stealth(const ec_secret& ephem_secret,
//   const ec_point& scan_pubkey const ec_point& spend_pubkey);

} // namespace libbitcoin

#endif

