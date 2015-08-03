###############################################################################
#  Copyright (c) 2014-2015 libgroestlcoin developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################

# Automake settings.
#==============================================================================
# Look for macros in the m4 subdirectory.
#------------------------------------------------------------------------------
ACLOCAL_AMFLAGS = -I m4


# Distribute, make and install products.
#==============================================================================
# files => ${pkgconfigdir}
#------------------------------------------------------------------------------
pkgconfig_DATA = \
    libgroestlcoin.pc

# files => ${docdir}
#------------------------------------------------------------------------------
doc_DATA = \
    AUTHORS \
    COPYING \
    ChangeLog \
    INSTALL \
    NEWS \
    README

# src/libgroestlcoin.la => ${libdir}
#------------------------------------------------------------------------------
lib_LTLIBRARIES = src/libgroestlcoin.la
src_libgroestlcoin_la_CPPFLAGS = -I${srcdir}/include ${icu} ${testnet} ${boost_CPPFLAGS} ${pthread_CPPFLAGS} ${icu_i18n_CPPFLAGS} ${secp256k1_CPPFLAGS}
src_libgroestlcoin_la_LDFLAGS = ${boost_LDFLAGS}
src_libgroestlcoin_la_LIBADD = ${boost_chrono_LIBS} ${boost_date_time_LIBS} ${boost_filesystem_LIBS} ${boost_locale_LIBS} ${boost_program_options_LIBS} ${boost_regex_LIBS} ${boost_system_LIBS} ${boost_thread_LIBS} ${pthread_LIBS} ${rt_LIBS} ${icu_i18n_LIBS} ${dl_LIBS} ${secp256k1_LIBS}
src_libgroestlcoin_la_SOURCES = \
    src/block.cpp \
    src/constants.cpp \
    src/error.cpp \
    src/satoshi_serialize.cpp \
    src/script.cpp \
    src/stealth.cpp \
    src/transaction.cpp \
    src/config/directory.cpp \
    src/config/parameter.cpp \
    src/config/printer.cpp \
    src/formats/base10.cpp \
    src/formats/base16.cpp \
    src/formats/base58.cpp \
    src/formats/base64.cpp \
    src/formats/base85.cpp \
    src/math/checksum.cpp \
	src/math/sphlib/groestl.cpp \
    src/math/ec_keys.cpp \
    src/math/hash.cpp \
    src/math/hash_number.cpp \
    src/math/script_number.cpp \
    src/math/secp256k1_initializer.cpp \
    src/math/uint256.cpp \
    src/math/external/hmac_sha256.c \
    src/math/external/hmac_sha256.h \
    src/math/external/hmac_sha512.c \
    src/math/external/hmac_sha512.h \
    src/math/external/pkcs5_pbkdf2.c \
    src/math/external/pkcs5_pbkdf2.h \
    src/math/external/ripemd160.c \
    src/math/external/ripemd160.h \
    src/math/external/sha1.c \
    src/math/external/sha1.h \
    src/math/external/sha256.c \
    src/math/external/sha256.h \
    src/math/external/sha512.c \
    src/math/external/sha512.h \
    src/math/external/zeroize.c \
    src/math/external/zeroize.h \
    src/network/acceptor.cpp \
    src/network/authority.cpp \
    src/network/channel.cpp \
    src/network/channel_proxy.cpp \
    src/network/channel_stream_loader.cpp \
    src/network/connect_with_timeout.cpp \
    src/network/connect_with_timeout.hpp \
    src/network/handshake.cpp \
    src/network/hosts.cpp \
    src/network/network.cpp \
    src/network/protocol.cpp \
    src/network/seeder.cpp \
    src/unicode/console_streambuf.cpp \
    src/unicode/ifstream.cpp \
    src/unicode/ofstream.cpp \
    src/unicode/unicode.cpp \
    src/unicode/unicode_istream.cpp \
    src/unicode/unicode_ostream.cpp \
    src/unicode/unicode_streambuf.cpp \
    src/utility/async_strand.cpp \
    src/utility/binary.cpp \
    src/utility/logger.cpp \
    src/utility/random.cpp \
    src/utility/string.cpp \
    src/utility/thread.cpp \
    src/utility/threadpool.cpp \
    src/utility/time.cpp \
    src/utility/timed_section.cpp \
    src/wallet/address.cpp \
    src/wallet/dictionary.cpp \
    src/wallet/hd_keys.cpp \
    src/wallet/key_formats.cpp \
    src/wallet/message.cpp \
    src/wallet/mnemonic.cpp \
    src/wallet/stealth_address.cpp \
    src/wallet/uri.cpp

# local: examples/libgroestlcoin_examples
#------------------------------------------------------------------------------
if WITH_EXAMPLES

noinst_PROGRAMS = examples/libgroestlcoin_examples
examples_libgroestlcoin_examples_CPPFLAGS = -I${srcdir}/include ${icu} ${testnet} ${boost_CPPFLAGS} ${pthread_CPPFLAGS} ${icu_i18n_CPPFLAGS} ${secp256k1_CPPFLAGS}
examples_libgroestlcoin_examples_LDFLAGS = ${boost_LDFLAGS}
examples_libgroestlcoin_examples_LDADD = src/libgroestlcoin.la ${boost_chrono_LIBS} ${boost_date_time_LIBS} ${boost_filesystem_LIBS} ${boost_locale_LIBS} ${boost_program_options_LIBS} ${boost_regex_LIBS} ${boost_system_LIBS} ${boost_thread_LIBS} ${pthread_LIBS} ${rt_LIBS} ${icu_i18n_LIBS} ${dl_LIBS} ${secp256k1_LIBS}
examples_libgroestlcoin_examples_SOURCES = \
    examples/main.cpp

endif WITH_EXAMPLES

# local: test/libgroestlcoin_test
#------------------------------------------------------------------------------
if WITH_TESTS

TESTS = libgroestlcoin_test_runner.sh

check_PROGRAMS = test/libgroestlcoin_test
test_libgroestlcoin_test_CPPFLAGS = -I${srcdir}/include ${icu} ${testnet} ${boost_CPPFLAGS} ${pthread_CPPFLAGS} ${icu_i18n_CPPFLAGS} ${secp256k1_CPPFLAGS}
test_libgroestlcoin_test_LDFLAGS = ${boost_LDFLAGS}
test_libgroestlcoin_test_LDADD = src/libgroestlcoin.la ${boost_unit_test_framework_LIBS} ${boost_chrono_LIBS} ${boost_date_time_LIBS} ${boost_filesystem_LIBS} ${boost_locale_LIBS} ${boost_program_options_LIBS} ${boost_regex_LIBS} ${boost_system_LIBS} ${boost_thread_LIBS} ${pthread_LIBS} ${rt_LIBS} ${icu_i18n_LIBS} ${dl_LIBS} ${secp256k1_LIBS}
test_libgroestlcoin_test_SOURCES = \
    test/base10.cpp \
    test/base16.cpp \
    test/base58.cpp \
    test/base64.cpp \
    test/base85.cpp \
    test/big_number.cpp \
    test/big_number.hpp \
    test/binary.cpp \
    test/binary_trie.cpp \
    test/checksum.cpp \
	src/math/sphlib/groestl.cpp \
    test/ec_keys.cpp \
    test/format.cpp \
    test/hash.cpp \
    test/hash.hpp \
    test/hash_number.cpp \
    test/hd_keys.cpp \
    test/key_formats.cpp \
    test/main.cpp \
    test/message.cpp \
    test/mnemonic.cpp \
    test/mnemonic.hpp \
    test/parameter.cpp \
    test/printer.cpp \
    test/satoshi_words.cpp \
    test/script.cpp \
    test/script.hpp \
    test/script_number.cpp \
    test/script_number.hpp \
    test/serialize.cpp \
    test/stealth.cpp \
    test/stealth_address.cpp \
    test/thread.cpp \
    test/unicode.cpp \
    test/unicode_istream.cpp \
    test/unicode_ostream.cpp \
    test/uri.cpp

endif WITH_TESTS

# files => ${includedir}/groestlcoin
#------------------------------------------------------------------------------
include_groestlcoindir = ${includedir}/groestlcoin
include_groestlcoin_HEADERS = \
    include/groestlcoin/groestlcoin.hpp

include_groestlcoin_groestlcoindir = ${includedir}/groestlcoin/groestlcoin
include_groestlcoin_groestlcoin_HEADERS = \
    include/groestlcoin/groestlcoin/block.hpp \
    include/groestlcoin/groestlcoin/compat.h \
    include/groestlcoin/groestlcoin/compat.hpp \
    include/groestlcoin/groestlcoin/constants.hpp \
    include/groestlcoin/groestlcoin/define.hpp \
    include/groestlcoin/groestlcoin/error.hpp \
    include/groestlcoin/groestlcoin/primitives.hpp \
    include/groestlcoin/groestlcoin/satoshi_serialize.hpp \
    include/groestlcoin/groestlcoin/script.hpp \
    include/groestlcoin/groestlcoin/stealth.hpp \
    include/groestlcoin/groestlcoin/transaction.hpp \
    include/groestlcoin/groestlcoin/version.hpp

include_groestlcoin_groestlcoin_configdir = ${includedir}/groestlcoin/groestlcoin/config
include_groestlcoin_groestlcoin_config_HEADERS = \
    include/groestlcoin/groestlcoin/config/directory.hpp \
    include/groestlcoin/groestlcoin/config/parameter.hpp \
    include/groestlcoin/groestlcoin/config/printer.hpp

include_groestlcoin_groestlcoin_formatsdir = ${includedir}/groestlcoin/groestlcoin/formats
include_groestlcoin_groestlcoin_formats_HEADERS = \
    include/groestlcoin/groestlcoin/formats/base10.hpp \
    include/groestlcoin/groestlcoin/formats/base16.hpp \
    include/groestlcoin/groestlcoin/formats/base58.hpp \
    include/groestlcoin/groestlcoin/formats/base64.hpp \
    include/groestlcoin/groestlcoin/formats/base85.hpp

include_groestlcoin_groestlcoin_impl_formatsdir = ${includedir}/groestlcoin/groestlcoin/impl/formats
include_groestlcoin_groestlcoin_impl_formats_HEADERS = \
    include/groestlcoin/groestlcoin/impl/formats/base16.ipp

include_groestlcoin_groestlcoin_impl_serializedir = ${includedir}/groestlcoin/groestlcoin/impl/serialize
include_groestlcoin_groestlcoin_impl_serialize_HEADERS = \
    include/groestlcoin/groestlcoin/impl/serialize/block.ipp \
    include/groestlcoin/groestlcoin/impl/serialize/misc.ipp

include_groestlcoin_groestlcoin_impl_triedir = ${includedir}/groestlcoin/groestlcoin/impl/trie
include_groestlcoin_groestlcoin_impl_trie_HEADERS = \
    include/groestlcoin/groestlcoin/impl/trie/binary_trie.ipp \
    include/groestlcoin/groestlcoin/impl/trie/trie_iterator.ipp \
    include/groestlcoin/groestlcoin/impl/trie/trie_reverse_iterator.ipp \
    include/groestlcoin/groestlcoin/impl/trie/trie_structure_node.ipp \
    include/groestlcoin/groestlcoin/impl/trie/trie_value_node.ipp

include_groestlcoin_groestlcoin_impl_utilitydir = ${includedir}/groestlcoin/groestlcoin/impl/utility
include_groestlcoin_groestlcoin_impl_utility_HEADERS = \
    include/groestlcoin/groestlcoin/impl/utility/array_slice.ipp \
    include/groestlcoin/groestlcoin/impl/utility/collection.ipp \
    include/groestlcoin/groestlcoin/impl/utility/data.ipp \
    include/groestlcoin/groestlcoin/impl/utility/endian.ipp \
    include/groestlcoin/groestlcoin/impl/utility/serializer.ipp

include_groestlcoin_groestlcoin_mathdir = ${includedir}/groestlcoin/groestlcoin/math
include_groestlcoin_groestlcoin_math_HEADERS = \
    include/groestlcoin/groestlcoin/math/checksum.hpp \
    include/groestlcoin/groestlcoin/math/ec_keys.hpp \
    include/groestlcoin/groestlcoin/math/hash.hpp \
    include/groestlcoin/groestlcoin/math/hash_number.hpp \
    include/groestlcoin/groestlcoin/math/script_number.hpp \
    include/groestlcoin/groestlcoin/math/secp256k1_initializer.hpp \
    include/groestlcoin/groestlcoin/math/uint256.hpp

include_groestlcoin_groestlcoin_networkdir = ${includedir}/groestlcoin/groestlcoin/network
include_groestlcoin_groestlcoin_network_HEADERS = \
    include/groestlcoin/groestlcoin/network/acceptor.hpp \
    include/groestlcoin/groestlcoin/network/authority.hpp \
    include/groestlcoin/groestlcoin/network/channel.hpp \
    include/groestlcoin/groestlcoin/network/channel_loader_module.hpp \
    include/groestlcoin/groestlcoin/network/channel_proxy.hpp \
    include/groestlcoin/groestlcoin/network/channel_stream_loader.hpp \
    include/groestlcoin/groestlcoin/network/handshake.hpp \
    include/groestlcoin/groestlcoin/network/hosts.hpp \
    include/groestlcoin/groestlcoin/network/network.hpp \
    include/groestlcoin/groestlcoin/network/protocol.hpp \
    include/groestlcoin/groestlcoin/network/seeder.hpp \
    include/groestlcoin/groestlcoin/network/shared_const_buffer.hpp

include_groestlcoin_groestlcoin_triedir = ${includedir}/groestlcoin/groestlcoin/trie
include_groestlcoin_groestlcoin_trie_HEADERS = \
    include/groestlcoin/groestlcoin/trie/binary_trie.hpp \
    include/groestlcoin/groestlcoin/trie/trie_iterator.hpp \
    include/groestlcoin/groestlcoin/trie/trie_reverse_iterator.hpp \
    include/groestlcoin/groestlcoin/trie/trie_structure_node.hpp \
    include/groestlcoin/groestlcoin/trie/trie_value_node.hpp

include_groestlcoin_groestlcoin_unicodedir = ${includedir}/groestlcoin/groestlcoin/unicode
include_groestlcoin_groestlcoin_unicode_HEADERS = \
    include/groestlcoin/groestlcoin/unicode/console_streambuf.hpp \
    include/groestlcoin/groestlcoin/unicode/ifstream.hpp \
    include/groestlcoin/groestlcoin/unicode/ofstream.hpp \
    include/groestlcoin/groestlcoin/unicode/unicode.hpp \
    include/groestlcoin/groestlcoin/unicode/unicode_istream.hpp \
    include/groestlcoin/groestlcoin/unicode/unicode_ostream.hpp \
    include/groestlcoin/groestlcoin/unicode/unicode_streambuf.hpp

include_groestlcoin_groestlcoin_utilitydir = ${includedir}/groestlcoin/groestlcoin/utility
include_groestlcoin_groestlcoin_utility_HEADERS = \
    include/groestlcoin/groestlcoin/utility/array_slice.hpp \
    include/groestlcoin/groestlcoin/utility/assert.hpp \
    include/groestlcoin/groestlcoin/utility/async_parallel.hpp \
    include/groestlcoin/groestlcoin/utility/async_strand.hpp \
    include/groestlcoin/groestlcoin/utility/binary.hpp \
    include/groestlcoin/groestlcoin/utility/collection.hpp \
    include/groestlcoin/groestlcoin/utility/data.hpp \
    include/groestlcoin/groestlcoin/utility/decorator.hpp \
    include/groestlcoin/groestlcoin/utility/endian.hpp \
    include/groestlcoin/groestlcoin/utility/logger.hpp \
    include/groestlcoin/groestlcoin/utility/random.hpp \
    include/groestlcoin/groestlcoin/utility/serializer.hpp \
    include/groestlcoin/groestlcoin/utility/string.hpp \
    include/groestlcoin/groestlcoin/utility/subscriber.hpp \
    include/groestlcoin/groestlcoin/utility/thread.hpp \
    include/groestlcoin/groestlcoin/utility/threadpool.hpp \
    include/groestlcoin/groestlcoin/utility/time.hpp \
    include/groestlcoin/groestlcoin/utility/timed_section.hpp

include_groestlcoin_groestlcoin_walletdir = ${includedir}/groestlcoin/groestlcoin/wallet
include_groestlcoin_groestlcoin_wallet_HEADERS = \
    include/groestlcoin/groestlcoin/wallet/address.hpp \
    include/groestlcoin/groestlcoin/wallet/dictionary.hpp \
    include/groestlcoin/groestlcoin/wallet/hd_keys.hpp \
    include/groestlcoin/groestlcoin/wallet/key_formats.hpp \
    include/groestlcoin/groestlcoin/wallet/message.hpp \
    include/groestlcoin/groestlcoin/wallet/mnemonic.hpp \
    include/groestlcoin/groestlcoin/wallet/stealth_address.hpp \
    include/groestlcoin/groestlcoin/wallet/uri.hpp


# Custom make targets.
#==============================================================================
# make target: examples
#------------------------------------------------------------------------------
target_examples = \
    examples/libgroestlcoin_examples

examples: ${target_examples}

