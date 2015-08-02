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
#ifndef LIBGROESTLCOIN_CHANNEL_STREAM_LOADER_HPP
#define LIBGROESTLCOIN_CHANNEL_STREAM_LOADER_HPP

#include <string>
#include <vector>
#include <groestlcoin/groestlcoin/define.hpp>
#include <groestlcoin/groestlcoin/network/channel_loader_module.hpp>
#include <groestlcoin/groestlcoin/utility/data.hpp>

namespace libgroestlcoin {
namespace network {

class BC_API channel_stream_loader
{
public:
    channel_stream_loader();
    ~channel_stream_loader();

    /// This class is not copyable.
    channel_stream_loader(const channel_stream_loader&) = delete;
    void operator=(const channel_stream_loader&) = delete;

    void add(bc::network::channel_loader_module_base* module);
    void load_lookup(const std::string& symbol,
        const bc::data_chunk& stream) const;

private:
    typedef std::vector<channel_loader_module_base*> module_list;

    module_list modules_;
};

} // namespace network
} // namespace libgroestlcoin

#endif

