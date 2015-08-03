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
#include <groestlcoin/groestlcoin/math/ec_keys.hpp>

#include <algorithm>
#include <mutex>
#include <secp256k1.h>
#include <groestlcoin/groestlcoin/math/hash.hpp>
#include <groestlcoin/groestlcoin/math/secp256k1_initializer.hpp>
#include <groestlcoin/groestlcoin/utility/assert.hpp>
#include <groestlcoin/groestlcoin/utility/endian.hpp>

namespace libgroestlcoin {

ec_point secret_to_public_key(const ec_secret& secret,
    bool compressed)
{
    const auto signing_context = signing.context();
    size_t public_key_size = ec_uncompressed_size;
    if (compressed)
        public_key_size = ec_compressed_size;

	secp256k1_pubkey_t pubkey;
	int out_size = 65;
	ec_point out(public_key_size);
	if (::secp256k1_ec_pubkey_create(signing_context, &pubkey, secret.data()) &&
		::secp256k1_ec_pubkey_serialize(signing_context, out.data(), &out_size, &pubkey, compressed)) {
        BITCOIN_ASSERT_MSG(public_key_size == static_cast<size_t>(out_size),
            "secp256k1_ec_pubkey_create returned invalid size");
        return out;
    }

    return ec_point();
}

bool verify_public_key(const ec_point& public_key)
{
    const auto verification_context = verification.context();
	secp256k1_pubkey_t pubkey;
	return ::secp256k1_ec_pubkey_parse(verification_context, &pubkey, public_key.data(), static_cast<uint32_t>(public_key.size()));
}

bool verify_public_key_fast(const ec_point& public_key)
{
    if (public_key.size() == ec_compressed_size)
        return public_key[0] == 0x02 || public_key[0] == 0x03;

    if (public_key.size() == ec_uncompressed_size)
        return public_key[0] == 0x04;

    return false;
}

bool verify_private_key(const ec_secret& private_key)
{
    const auto verification_context = verification.context();
    return secp256k1_ec_seckey_verify(verification_context, private_key.data())
        == 1;
}

endorsement sign(ec_secret secret, hash_digest hash)
{
    const auto signing_context = signing.context();
    int out_size = max_endorsement_size;
    endorsement signature(out_size);
	secp256k1_ecdsa_signature_t sig;
    if (!secp256k1_ecdsa_sign(signing_context, hash.data(), &sig, secret.data(), secp256k1_nonce_function_rfc6979, nullptr) ||
		!secp256k1_ecdsa_signature_serialize_der(signing_context, signature.data(), &out_size, &sig))
    {
        BITCOIN_ASSERT_MSG(false, "secp256k1_ecdsa_sign failed");
        out_size = 0;
	}

    signature.resize(out_size);
    return signature;
}

compact_signature sign_compact(ec_secret secret, hash_digest hash)
{
    const auto signing_context = signing.context();
    compact_signature out;

	secp256k1_ecdsa_signature_t sig;
	if (!secp256k1_ecdsa_sign(signing_context, hash.data(), &sig, secret.data(), secp256k1_nonce_function_rfc6979, nullptr) ||
		!secp256k1_ecdsa_signature_serialize_compact(signing_context, out.signature.data(), &out.recid, &sig))
    {
        BITCOIN_ASSERT_MSG(false, "secp256k1_ecdsa_sign_compact failed");
        return compact_signature();
    }
    return out;
}

bool verify_signature(const ec_point& public_key, hash_digest hash,
    const endorsement& signature)
{
    auto signing_context = verification.context();
	secp256k1_pubkey_t pubkey;
	secp256k1_ecdsa_signature_t sig;
	auto result = secp256k1_ec_pubkey_parse(signing_context, &pubkey, public_key.data(), public_key.size() &&
		secp256k1_ecdsa_signature_parse_der(signing_context, &sig, signature.data(), signature.size()) &&
		secp256k1_ecdsa_verify(signing_context, hash.data(), &sig, &pubkey));

    BITCOIN_ASSERT_MSG(result >= 0, "secp256k1_ecdsa_verify failed");

    return result == 1;
}

ec_point recover_compact(compact_signature signature, hash_digest hash,
    bool compressed)
{
    const auto verification_context = verification.context();
    size_t public_key_size = ec_uncompressed_size;
    if (compressed)
        public_key_size = ec_compressed_size;

    ec_point out(public_key_size);
    int out_size;
	secp256k1_ecdsa_signature_t sig;
	secp256k1_pubkey_t pubkey;
	if (secp256k1_ecdsa_signature_parse_compact(verification_context, &sig, signature.signature.data(), signature.recid) &&
		secp256k1_ecdsa_recover(verification_context, hash.data(), &sig, &pubkey) &&
		secp256k1_ec_pubkey_serialize(verification_context, out.data(), &out_size, &pubkey, compressed))
    {
        BITCOIN_ASSERT_MSG(public_key_size == static_cast<size_t>(out_size),
            "secp256k1_ecdsa_recover_compact returned invalid size");
        return out;
    }

    return ec_point();
}

bool ec_add(ec_point& a, const ec_secret& b)
{
    const auto verification_context = verification.context();
	secp256k1_pubkey_t pubkey;
	return secp256k1_ec_pubkey_parse(verification_context, &pubkey, a.data(), a.size()) &&
		secp256k1_ec_pubkey_tweak_add(verification_context, &pubkey, b.data());
}

bool ec_add(ec_secret& a, const ec_secret& b)
{
    const auto verification_context = verification.context();
    return secp256k1_ec_privkey_tweak_add(verification_context, a.data(),
        b.data()) == 1;
}

bool ec_multiply(ec_point& a, const ec_secret& b)
{
    const auto verification_context = verification.context();
	secp256k1_pubkey_t pubkey;
	return secp256k1_ec_pubkey_parse(verification_context, &pubkey, a.data(), a.size()) &&
		secp256k1_ec_pubkey_tweak_mul(verification_context, &pubkey, b.data());
}

bool ec_multiply(ec_secret& a, const ec_secret& b)
{
    const auto verification_context = verification.context();
    return secp256k1_ec_privkey_tweak_mul(verification_context, a.data(),
        b.data()) == 1;
}

///////////////////////////////////////////////////////////////////////////////
// DEPRECATED (now redundant with secp256k1 implementation)
///////////////////////////////////////////////////////////////////////////////
ec_secret create_nonce(ec_secret secret, hash_digest hash, uint32_t index)
{
    hash_digest K
    {{
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    }};
    hash_digest V
    {{
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
    }};

    K = hmac_sha256_hash(build_data({V, to_byte(0x00), secret, hash}), K);
    V = hmac_sha256_hash(V, K);
    K = hmac_sha256_hash(build_data({V, to_byte(0x01), secret, hash}), K);
    V = hmac_sha256_hash(V, K);

    while (true)
    {
        V = hmac_sha256_hash(V, K);

        if (0 == index)
            return V;
        --index;

        K = hmac_sha256_hash(build_data({V, to_byte(0x00)}), K);
        V = hmac_sha256_hash(V, K);
    }
}

///////////////////////////////////////////////////////////////////////////////
// DEPRECATED (deterministic signatures are safer)
///////////////////////////////////////////////////////////////////////////////
endorsement sign(ec_secret secret, hash_digest hash, ec_secret /* nonce */)
{
    // THE CALLER'S NONCE IS IGNORED.
    return sign(secret, hash);
}

///////////////////////////////////////////////////////////////////////////////
// DEPRECATED (deterministic signatures are safer)
///////////////////////////////////////////////////////////////////////////////
compact_signature sign_compact(ec_secret secret, hash_digest hash,
    ec_secret /* nonce */)
{
    // THE CALLER'S NONCE IS IGNORED.
    return sign_compact(secret, hash);
}

} // namespace libgroestlcoin

