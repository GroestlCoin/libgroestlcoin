/**
 * Copyright (c) 2011-2015 libgroestlcoin developers (see AUTHORS)
 *
 * This file is part of libgroestlcoin-explorer.
 *
 * libgroestlcoin-explorer is free software: you can redistribute it and/or
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

#include <groestlcoin/explorer/display.hpp>

#include <iostream>
#include <memory>
#include <boost/format.hpp>
#include <groestlcoin/explorer/define.hpp>
#include <groestlcoin/explorer/dispatch.hpp>
#include <groestlcoin/explorer/generated.hpp>
#include <groestlcoin/explorer/primitives/uri.hpp>
#include <groestlcoin/explorer/utility.hpp>
#include <groestlcoin/explorer/version.hpp>

namespace libgroestlcoin {
namespace explorer {

#define BX_HOME_PAGE_URL "https://github.com/libgroestlcoin/libgroestlcoin-explorer"

void display_command_names(std::ostream& stream)
{
    const auto func = [&stream](std::shared_ptr<command> explorer_command)
    {
        BITCOIN_ASSERT(explorer_command != nullptr);
        if (!explorer_command->obsolete())
            stream << explorer_command->name() << std::endl;
    };

    broadcast(func);
}

void display_connection_failure(std::ostream& stream, const primitives::uri& url)
{
    stream << format(BX_CONNECTION_FAILURE) % url << std::endl;
}

void display_invalid_command(std::ostream& stream, const std::string& command,
    const std::string& superseding)
{
    if (superseding.empty())
        stream << format(BX_INVALID_COMMAND) % command;
    else
        stream << format(BX_DEPRECATED_COMMAND) % command % superseding;

    stream << std::endl;
}

// English only hack to patch missing arg name in boost exception message.
static std::string fixup_boost_po_what_en(const std::string& what)
{
    std::string message(what);
    boost::replace_all(message, "for option is invalid", "is invalid");
    return message;
}

void display_invalid_parameter(std::ostream& stream, 
    const std::string& message)
{
    stream << format(BX_INVALID_PARAMETER) % fixup_boost_po_what_en(message)
        << std::endl;
}

void display_usage(std::ostream& stream)
{
    stream 
        << std::endl << BX_COMMAND_USAGE << std::endl
        << std::endl << format(BX_VERSION_MESSAGE) % 
            LIBBITCOIN_EXPLORER_VERSION % BX_NETWORK << std::endl
        << std::endl << BX_COMMANDS_HEADER << std::endl
        << std::endl;

    display_command_names(stream);

    stream
        << std::endl << BX_COMMANDS_HOME_PAGE << std::endl
        << std::endl << BX_HOME_PAGE_URL << std::endl;
}

} // namespace explorer
} // namespace libgroestlcoin
