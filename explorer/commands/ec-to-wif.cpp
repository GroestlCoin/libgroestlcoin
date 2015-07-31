/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <groestlcoin/explorer/commands/ec-to-wif.hpp>

#include <iostream>
#include <groestlcoin/explorer/define.hpp>
#include <groestlcoin/explorer/primitives/wif.hpp>

using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result ec_to_wif::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& secret = get_ec_private_key_argument();
    const auto& uncompressed = get_uncompressed_option();

    // TESTNET REQUIRES RECOMPILE
    auto import_format = wif(secret, !uncompressed);

    output << import_format << std::endl;
    return console_result::okay;
}