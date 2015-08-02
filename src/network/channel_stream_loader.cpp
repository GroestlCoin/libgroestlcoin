/**
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
#include <groestlcoin/groestlcoin/network/channel_stream_loader.hpp>

#include <string>
#include <groestlcoin/groestlcoin/network/channel_loader_module.hpp>
#include <groestlcoin/groestlcoin/utility/assert.hpp>
#include <groestlcoin/groestlcoin/utility/data.hpp>

namespace libgroestlcoin {
namespace network {

channel_stream_loader::channel_stream_loader()
{
}

channel_stream_loader::~channel_stream_loader()
{
    for (auto module: modules_)
        delete module;
}

void channel_stream_loader::add(channel_loader_module_base* module)
{
    BITCOIN_ASSERT(module != nullptr);
    modules_.push_back(module);
}

void channel_stream_loader::load_lookup(const std::string& symbol,
    const data_chunk& stream) const
{
    for (auto module: modules_)
        if (module->lookup_symbol() == symbol)
            module->attempt_load(stream);
}

} // namespace network
} // namespace libgroestlcoin
