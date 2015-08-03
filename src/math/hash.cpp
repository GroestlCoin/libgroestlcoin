/*
 * Copyright (c) 2011-2015 libgroestlcoin developers (see AUTHORS)
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
#include <groestlcoin/groestlcoin/math/hash.hpp>

#include <string.h>

#include <algorithm>
#include <new>
#include "../math/external/hmac_sha256.h"
#include "../math/external/hmac_sha512.h"
#include "../math/external/pkcs5_pbkdf2.h"
#include "../math/external/ripemd160.h"
#include "../math/external/sha1.h"
#include "../math/external/sha256.h"
#include "../math/external/sha512.h"

extern "C" {
#include "sphlib/sph_groestl.h"	//GRS
}

namespace libgroestlcoin {

short_hash ripemd160_hash(data_slice data)
{
    short_hash hash;
    RMD160(data.data(), data.size(), hash.data());
    return hash;
}

short_hash sha1_hash(data_slice data)
{
    short_hash hash;
    SHA1_(data.data(), data.size(), hash.data());
    return hash;
}

hash_digest sha256_hash(data_slice data)
{
    hash_digest hash;
    SHA256_(data.data(), data.size(), hash.data());
    return hash;
}

hash_digest sha256_hash(data_slice first, data_slice second)
{
    hash_digest hash;

    SHA256CTX context;
    SHA256Init(&context);
    SHA256Update(&context, first.data(), first.size());
    SHA256Update(&context, second.data(), second.size());
    SHA256Final(&context, hash.data());

    return hash;
}

hash_digest hmac_sha256_hash(data_slice data, data_slice key)
{
    hash_digest hash;
    HMACSHA256(data.data(), data.size(), key.data(),
        key.size(), hash.data());
    return hash;
}

long_hash sha512_hash(data_slice data)
{
    long_hash hash;
    SHA512_(data.data(), data.size(), hash.data());
    return hash;
}

long_hash hmac_sha512_hash(data_slice data, data_slice key)
{
    long_hash hash;
    HMACSHA512(data.data(), data.size(), key.data(),
        key.size(), hash.data());
    return hash;
}

long_hash pkcs5_pbkdf2_hmac_sha512(data_slice passphrase,
    data_slice salt, size_t iterations)
{
    long_hash hash;
    if (pkcs5_pbkdf2(passphrase.data(), passphrase.size(),
        salt.data(), salt.size(), hash.data(), hash.size(), iterations))
        throw std::bad_alloc();
    return hash;
}

/*!!!GRS hash_digest bitcoin_hash(data_slice data)
{
    return sha256_hash(sha256_hash(data));
}*/

hash_digest SHA256_SHA256(data_slice data) {
	return sha256_hash(sha256_hash(data));
}

hash_digest groestlcoin_hash(data_slice data) {
    sph_groestl512_context  ctx_gr[2];
    static unsigned char pblank[1];
    std::array<uint8_t, 64> hash1;
	
    sph_groestl512_init(&ctx_gr[0]);
    sph_groestl512 (&ctx_gr[0], data.data() ? data.data() : pblank, data.size());
    sph_groestl512_close(&ctx_gr[0], static_cast<void*>(hash1.data()));
	
	std::array<uint8_t, 64> hash2;
	sph_groestl512_init(&ctx_gr[1]);
	sph_groestl512(&ctx_gr[1],static_cast<const void*>(hash1.data()), 64);
	sph_groestl512_close(&ctx_gr[1],static_cast<void*>(hash2.data()));
	
	hash_digest r;
	memcpy(r.data(), hash2.data(), 32);
	return r;
}

hash_digest HashFromTx(data_slice data) {
	return sha256_hash(data);
}

short_hash bitcoin_short_hash(data_slice data)
{
    return ripemd160_hash(sha256_hash(data));
}

} // namespace libgroestlcoin

