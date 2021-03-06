/*
 * Copyright (c) 2011-2014 libgroestlcoin developers (see AUTHORS)
 *
 * This file is part of libgroestlcoin.
 *
 * libgroestlcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBGROESTLCOIN_MESSAGE_HPP
#define LIBGROESTLCOIN_MESSAGE_HPP

#include <string>
#include <groestlcoin/groestlcoin/compat.hpp>
#include <groestlcoin/groestlcoin/define.hpp>
#include <groestlcoin/groestlcoin/math/ec_keys.hpp>
#include <groestlcoin/groestlcoin/math/hash.hpp>
#include <groestlcoin/groestlcoin/wallet/address.hpp>

namespace libgroestlcoin {

BC_CONSTEXPR size_t message_signature_size = 65;
typedef byte_array<message_signature_size> message_signature;

/**
 * Hashes a messages in preparation for signing.
 */
BC_API hash_digest hash_message(data_slice message);

/**
 * Signs a message.
 * Uses deterministic signatures.
 * @return a signature in Bitcoin's own format.
 * This should be base64 encoded for presentation to the user.
 */
BC_API message_signature sign_message(data_slice message,
    const std::string& wif);

/**
 * Signs a message.
 * Uses deterministic signatures.
 * @param compressed true if the bitcoin address derived from the
 * private key is in compressed format.
 * @return a signature in Bitcoin's own format.
 * This should be base64 encoded for presentation to the user.
 */
BC_API message_signature sign_message(data_slice message,
    const ec_secret& secret, bool compressed=true);

/**
 * Verifies a message.
 * @param signature a message signature in Bitcoin's own format.
 * The user will generally provide this as a base64 string,
 * which the user interface must decode.
 * @return false if the signature does not match the address,
 * or if there are any errors in the signature encoding.
 */
BC_API bool verify_message(data_slice message,
    const payment_address& address, const message_signature& signature);

} // namespace libgroestlcoin

#endif

