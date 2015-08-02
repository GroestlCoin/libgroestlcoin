/**
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
#ifndef LIBGROESTLCOIN_DIRECTORY_HPP
#define LIBGROESTLCOIN_DIRECTORY_HPP

#include <string>
#include <groestlcoin/groestlcoin/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libgroestlcoin {
namespace config {

/**
 * Get the windows configuration directory.
 * @return Path or empty string if unable to retrieve.
 */
BC_API std::string windows_config_directory();

} // namespace config
} // namespace libgroestlcoin

#endif