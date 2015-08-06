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
#include <groestlcoin/groestlcoin/block.hpp>

#include <groestlcoin/groestlcoin/constants.hpp>
#include <groestlcoin/groestlcoin/formats/base16.hpp>
#include <groestlcoin/groestlcoin/satoshi_serialize.hpp>
#include <groestlcoin/groestlcoin/transaction.hpp>
#include <groestlcoin/groestlcoin/math/hash.hpp>
#include <groestlcoin/groestlcoin/utility/assert.hpp>
#include <groestlcoin/groestlcoin/utility/serializer.hpp>

namespace libgroestlcoin {

// Pressure must be put on Vladimir Putin over Crimea
const auto genesis_input_script = data_chunk				//GRS
{
	0x04, 0xFF, 0xFF, 0x00, 0x1D, 0x01, 0x04, 0x32,	
	0x50, 0x72, 0x65, 0x73, 0x73, 0x75, 0x72, 0x65,
	0x20, 0x6D, 0x75, 0x73, 0x74, 0x20, 0x62, 0x65,
	0x20, 0x70, 0x75, 0x74, 0x20, 0x6F, 0x6E, 0x20,
	0x56, 0x6C, 0x61, 0x64, 0x69, 0x6D, 0x69, 0x72,
	0x20, 0x50, 0x75, 0x74, 0x69, 0x6E, 0x20, 0x6F,
	0x76, 0x65, 0x72, 0x20, 0x43, 0x72, 0x69, 0x6D,
	0x65, 0x61
};

const auto genesis_output_script = operation
{
    opcode::special,
    data_chunk
    {
		0x04, 0x67, 0x8A, 0xFD, 0xB0, 0xFE, 0x55, 0x48,
		0x27, 0x19, 0x67, 0xF1, 0xA6, 0x71, 0x30, 0xB7,
		0x10, 0x5C, 0xD6, 0xA8, 0x28, 0xE0, 0x39, 0x09,
		0xA6, 0x79, 0x62, 0xE0, 0xEA, 0x1F, 0x61, 0xDE,
		0xB6, 0x49, 0xF6, 0xBC, 0x3F, 0x4C, 0xEF, 0x38,
		0xC4, 0xF3, 0x55, 0x04, 0xE5, 0x1E, 0xC1, 0x12,
		0xDE, 0x5C, 0x38, 0x4D, 0xF7, 0xBA, 0x0B, 0x8D,
		0x57, 0x8A, 0x4C, 0x70, 0x2B, 0x6B, 0xF1, 0x1D,
		0x5F
    }
};

bool operator==(
    const block_header_type& block_a, const block_header_type& block_b)
{
    return block_a.version == block_b.version &&
        block_a.previous_block_hash == block_b.previous_block_hash &&
        block_a.merkle == block_b.merkle &&
        block_a.timestamp == block_b.timestamp &&
        block_a.bits == block_b.bits &&
        block_a.nonce == block_b.nonce;
}

uint64_t block_value(size_t height)
{
    uint64_t subsidy = coin_price(initial_block_reward);
    subsidy >>= (height / reward_interval);
    return subsidy;
}

hash_number block_work(uint32_t bits)
{
    hash_number target;
    if (!target.set_compact(bits))
        return 0;

    if (target == 0)
        return 0;

    // We need to compute 2**256 / (bnTarget+1), but we can't represent 2**256
    // as it's too large for a uint256. However as 2**256 is at least as large
    // as bnTarget+1 it's equal to ((2**256 - bnTarget - 1) / (bnTarget+1)) + 1
    // or ~bnTarget / (nTarget+1) + 1.
    return (~target / (target + 1)) + 1;
}

hash_digest hash_block_header(const block_header_type& header)
{
    data_chunk raw_block_header(80);
    satoshi_save(header, raw_block_header.begin());
    return groestlcoin_hash(raw_block_header);
}

index_list block_locator_indexes(size_t top_height)
{
    index_list indexes;
    BITCOIN_ASSERT(top_height <= bc::max_int32);
    const auto height32 = static_cast<int32_t>(top_height);

    // Start at max_height, push last 10 indexes first.
    // TODO: modify loop so conversion to signed int is not required.
    int32_t start = 0, step = 1;
    for (auto index = height32; index > 0; index -= step, ++start)
    {
        if (start >= 10)
            step *= 2;

        indexes.push_back(index);
    }

    indexes.push_back(0);
    return indexes;
}

block_type genesis_block()
{
    block_header_type header;
    header.version = 1;
    header.previous_block_hash = null_hash;
    header.merkle = hash_literal(
        "3ce968df58f9c8a752306c4b7264afab93149dbc578bd08a42c446caaa6628bb");		//GRS
    header.bits = 0x1d00ffff;

#ifdef ENABLE_TESTNET
    header.timestamp = 1395342913;
    header.nonce = 873629;
#else
    header.timestamp = 1395342829;													//GRS
    header.nonce = 220035;
#endif

    transaction_type coinbase_tx;
    coinbase_tx.version = 1;
    coinbase_tx.locktime = 0;

    transaction_input_type coinbase_input;
    coinbase_input.previous_output.hash = null_hash;
    coinbase_input.previous_output.index = bc::max_uint32;
    coinbase_input.script = raw_data_script(genesis_input_script);
    coinbase_input.sequence = max_input_sequence;
    coinbase_tx.inputs.push_back(coinbase_input);

    transaction_output_type coinbase_output;
    coinbase_output.value = coin_price(50);
    coinbase_output.script.push_operation(genesis_output_script);
    coinbase_output.script.push_operation(
        operation{ opcode::checksig, data_chunk() });
    coinbase_tx.outputs.push_back(coinbase_output);

    block_type genesis;
    genesis.header = header;
    genesis.transactions.push_back(coinbase_tx);
    BITCOIN_ASSERT(genesis.transactions.size() == 1);
    BITCOIN_ASSERT(
        generate_merkle_root(genesis.transactions) == genesis.header.merkle);
    return genesis;
}

} // namespace libgroestlcoin

