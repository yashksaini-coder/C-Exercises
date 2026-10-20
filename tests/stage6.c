#include "support.h"
#include <arpa/inet.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef int stage_6_keep_translation_unit_nonempty;

#if EXERCISE == 51
void run_tests(void) {
    CASE("0 and 1");
    UINT(0u, bit_count(0u));
    UINT(1u, bit_count(1u));
    CASE("0xFF -> 8, 0xA5A5A5A5 -> 16");
    UINT(8u, bit_count(0xFFu));
    UINT(16u, bit_count(0xA5A5A5A5u));
    CASE("top bit only -> 1 (shift must be unsigned)");
    UINT(1u, bit_count(0x80000000u));
    CASE("all bits -> 32");
    UINT(32u, bit_count(0xFFFFFFFFu));
    CASE("powers of two each have one bit");
    bool ok = true;
    for (unsigned i = 0; i < 32; ++i)
        if (bit_count(UINT32_C(1) << i) != 1) ok = false;
    TRUE(ok);
    UINT(31u, bit_count(0x7FFFFFFFu));
}
#elif EXERCISE == 52
void run_tests(void) {
    CASE("1, 2, 4, 1024");
    TRUE(is_power_of_two(1));
    TRUE(is_power_of_two(2));
    TRUE(is_power_of_two(4));
    TRUE(is_power_of_two(1024));
    CASE("0 is not a power of two");
    FALSE(is_power_of_two(0));
    CASE("3, 6, 1023, 1025");
    FALSE(is_power_of_two(3));
    FALSE(is_power_of_two(6));
    FALSE(is_power_of_two(1023));
    FALSE(is_power_of_two(1025));
    CASE("2^63 and UINT64_MAX");
    TRUE(is_power_of_two(UINT64_C(1) << 63));
    FALSE(is_power_of_two(UINT64_MAX));
    FALSE(is_power_of_two((UINT64_C(1) << 63) + 1));
    CASE("every power of two up to 2^63");
    bool ok = true;
    for (unsigned i = 0; i < 64; ++i)
        if (!is_power_of_two(UINT64_C(1) << i)) ok = false;
    TRUE(ok);
}
#elif EXERCISE == 53
void run_tests(void) {
    CASE("0 and all ones are fixed points");
    UINT(0u, reverse_bits(0u));
    UINT(0xFFFFFFFFu, reverse_bits(0xFFFFFFFFu));
    CASE("1 <-> 0x80000000");
    UINT(0x80000000u, reverse_bits(1u));
    UINT(1u, reverse_bits(0x80000000u));
    CASE("0x12345678 -> 0x1E6A2C48 (bit reversal, not byte swap)");
    UINT(0x1E6A2C48u, reverse_bits(0x12345678u));
    TRUE(reverse_bits(0x12345678u) != 0x78563412u);
    CASE("0x0000FFFF -> 0xFFFF0000, 0xF0F0F0F0 -> 0x0F0F0F0F");
    UINT(0xFFFF0000u, reverse_bits(0x0000FFFFu));
    UINT(0x0F0F0F0Fu, reverse_bits(0xF0F0F0F0u));
    CASE("involution: reverse twice is identity");
    const uint32_t samples[] = {0xDEADBEEFu, 0x00000002u, 0x40000000u, 0xCAFEBABEu, 7u};
    bool ok = true;
    for (size_t i = 0; i < sizeof samples / sizeof samples[0]; ++i)
        if (reverse_bits(reverse_bits(samples[i])) != samples[i]) ok = false;
    TRUE(ok);
}
#elif EXERCISE == 54
void run_tests(void) {
    CASE("set bit 0 of 0");
    UINT(1u, bit_set(0u, 0, true));
    CASE("set bit 31 (1u << 31, not 1 << 31)");
    UINT(0x80000000u, bit_set(0u, 31, true));
    UINT(0xFFFFFFFFu, bit_set(0x7FFFFFFFu, 31, true));
    CASE("clear bit 3 of 0xFF, then set it again");
    UINT(0xF7u, bit_set(0xFFu, 3, false));
    UINT(0xFFu, bit_set(0xF7u, 3, true));
    CASE("idempotent: setting a set bit, clearing a clear bit");
    UINT(5u, bit_set(5u, 0, true));
    UINT(5u, bit_set(5u, 1, false));
    UINT(0u, bit_set(0x80000000u, 31, false));
    CASE("index >= 32 leaves value unchanged");
    UINT(5u, bit_set(5u, 32, true));
    UINT(5u, bit_set(5u, 100, false));
    UINT(0xFFFFFFFFu, bit_set(0xFFFFFFFFu, UINT_MAX, false));
    CASE("walk every bit");
    uint32_t v = 0;
    for (unsigned i = 0; i < 32; ++i) v = bit_set(v, i, true);
    UINT(0xFFFFFFFFu, v);
    for (unsigned i = 0; i < 32; i += 2) v = bit_set(v, i, false);
    UINT(0xAAAAAAAAu, v);
}
#elif EXERCISE == 55
void run_tests(void) {
    CASE("{00 00 00 01} -> 1");
    const unsigned char one[4] = {0x00, 0x00, 0x00, 0x01};
    UINT(1u, read_u32_be(one));
    CASE("{12 34 56 78} -> 0x12345678");
    const unsigned char mixed[4] = {0x12, 0x34, 0x56, 0x78};
    UINT(0x12345678u, read_u32_be(mixed));
    CASE("{FF FF FF FF} -> 0xFFFFFFFF");
    const unsigned char ones[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    UINT(0xFFFFFFFFu, read_u32_be(ones));
    CASE("{80 00 00 00} -> 0x80000000 (int << 24 would overflow)");
    const unsigned char top[4] = {0x80, 0x00, 0x00, 0x00};
    UINT(0x80000000u, read_u32_be(top));
    CASE("unaligned offset inside a larger buffer");
    unsigned char buffer[9] = {0xAA, 0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x00, 0x01, 0x00};
    UINT(0xDEADBEEFu, read_u32_be(buffer + 1));
    UINT(0xEF000001u, read_u32_be(buffer + 4));
    UINT(0x00000100u, read_u32_be(buffer + 5));
}
#elif EXERCISE == 56
void run_tests(void) {
    CASE("1 -> {00 00 00 01}");
    unsigned char b[4] = {0xAA, 0xAA, 0xAA, 0xAA};
    write_u32_be(b, 1u);
    const unsigned char one[4] = {0x00, 0x00, 0x00, 0x01};
    BYTES(one, b, 4);
    CASE("0x12345678 -> {12 34 56 78}");
    write_u32_be(b, 0x12345678u);
    const unsigned char mixed[4] = {0x12, 0x34, 0x56, 0x78};
    BYTES(mixed, b, 4);
    CASE("0xFFFFFFFF and 0");
    write_u32_be(b, 0xFFFFFFFFu);
    const unsigned char ones[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    BYTES(ones, b, 4);
    write_u32_be(b, 0u);
    const unsigned char zeros[4] = {0, 0, 0, 0};
    BYTES(zeros, b, 4);
    CASE("writes exactly four bytes at an unaligned offset");
    unsigned char buffer[9];
    memset(buffer, 0xCC, sizeof buffer);
    write_u32_be(buffer + 3, 0xDEADBEEFu);
    const unsigned char expected[9] = {0xCC, 0xCC, 0xCC, 0xDE, 0xAD, 0xBE, 0xEF, 0xCC, 0xCC};
    BYTES(expected, buffer, 9);
    CASE("0x80000000 top byte");
    write_u32_be(b, 0x80000000u);
    const unsigned char top[4] = {0x80, 0x00, 0x00, 0x00};
    BYTES(top, b, 4);
}
#elif EXERCISE == 57
void run_tests(void) {
    CASE("my_htons matches htons");
    UINT(htons(0x1234), my_htons(0x1234));
    UINT(htons(1), my_htons(1));
    UINT(htons(0xFF00), my_htons(0xFF00));
    UINT(htons(0xABCD), my_htons(0xABCD));
    CASE("my_htonl matches htonl");
    UINT(htonl(0x12345678u), my_htonl(0x12345678u));
    UINT(htonl(1u), my_htonl(1u));
    UINT(htonl(0x80000000u), my_htonl(0x80000000u));
    UINT(htonl(0xDEADBEEFu), my_htonl(0xDEADBEEFu));
    CASE("0 and all-ones are unchanged on every host");
    UINT(0u, my_htons(0));
    UINT(0xFFFFu, my_htons(0xFFFF));
    UINT(0u, my_htonl(0u));
    UINT(0xFFFFFFFFu, my_htonl(0xFFFFFFFFu));
    CASE("applying twice is the identity");
    UINT(0x1234u, my_htons(my_htons(0x1234)));
    UINT(0x12345678u, my_htonl(my_htonl(0x12345678u)));
    CASE("result stored in memory reads as big-endian bytes");
    uint32_t net = my_htonl(0x01020304u);
    unsigned char bytes[4];
    memcpy(bytes, &net, 4);
    const unsigned char expected[4] = {0x01, 0x02, 0x03, 0x04};
    BYTES(expected, bytes, 4);
    uint16_t net16 = my_htons(0x0A0B);
    unsigned char bytes16[2];
    memcpy(bytes16, &net16, 2);
    const unsigned char expected16[2] = {0x0A, 0x0B};
    BYTES(expected16, bytes16, 2);
}
#elif EXERCISE == 58
void run_tests(void) {
    unsigned char b[64];
    CASE("\"c\" 0x41 -> 1 byte");
    memset(b, 0xEE, sizeof b);
    UINT(1u, pack(b, "c", 0x41));
    INT(0x41, b[0]);
    INT(0xEE, b[1]);
    CASE("\"h\" 0x1234 -> 12 34");
    UINT(2u, pack(b, "h", 0x1234));
    const unsigned char h[2] = {0x12, 0x34};
    BYTES(h, b, 2);
    CASE("\"lq\" 0xDEADBEEF, 1 -> 12 bytes");
    UINT(12u, pack(b, "lq", (uint32_t)0xDEADBEEFu, (uint64_t)1));
    const unsigned char lq[12] = {0xDE, 0xAD, 0xBE, 0xEF, 0, 0, 0, 0, 0, 0, 0, 1};
    BYTES(lq, b, 12);
    CASE("\"s\" \"hi\" -> 00 02 68 69");
    UINT(4u, pack(b, "s", "hi"));
    const unsigned char s[4] = {0x00, 0x02, 'h', 'i'};
    BYTES(s, b, 4);
    CASE("\"chs\" -1, 258, \"\" -> FF 01 02 00 00 (low bits only, empty string)");
    UINT(5u, pack(b, "chs", -1, 258, ""));
    const unsigned char chs[5] = {0xFF, 0x01, 0x02, 0x00, 0x00};
    BYTES(chs, b, 5);
    CASE("empty format, unknown chars ignored, q with the top bit set");
    UINT(0u, pack(b, "", 0));
    UINT(0u, pack(b, "xyz"));
    UINT(8u, pack(b, "q", UINT64_C(0x8000000000000001)));
    const unsigned char q[8] = {0x80, 0, 0, 0, 0, 0, 0, 0x01};
    BYTES(q, b, 8);
    UINT(13u, pack(b, "l-s", (uint32_t)0x01020304u, "abcdefg"));
    const unsigned char ls[13] = {1, 2, 3, 4, 0, 7, 'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    BYTES(ls, b, 13);
}
#elif EXERCISE == 59
void run_tests(void) {
    int c = 0;
    uint16_t h = 0;
    uint32_t l = 0;
    uint64_t q = 0;
    char text[32];
    CASE("\"c\" {41} -> 0x41; {FF} -> -1 (signed)");
    const unsigned char c41[1] = {0x41};
    UINT(1u, unpack(c41, "c", &c));
    INT(0x41, c);
    const unsigned char cff[1] = {0xFF};
    UINT(1u, unpack(cff, "c", &c));
    INT(-1, c);
    const unsigned char c80[1] = {0x80};
    UINT(1u, unpack(c80, "c", &c));
    INT(-128, c);
    CASE("\"h\" {12 34} -> 0x1234");
    const unsigned char h12[2] = {0x12, 0x34};
    UINT(2u, unpack(h12, "h", &h));
    UINT(0x1234u, h);
    CASE("\"lq\" -> 0xDEADBEEF, 1 (12 bytes consumed)");
    const unsigned char lq[12] = {0xDE, 0xAD, 0xBE, 0xEF, 0, 0, 0, 0, 0, 0, 0, 1};
    UINT(12u, unpack(lq, "lq", &l, &q));
    UINT(0xDEADBEEFu, l);
    UINT(1u, q);
    CASE("\"s\" {00 02 h i} -> \"hi\" NUL-terminated");
    memset(text, 'X', sizeof text);
    const unsigned char s[4] = {0x00, 0x02, 'h', 'i'};
    UINT(4u, unpack(s, "s", text));
    STRING("hi", text);
    CASE("q with the top byte set: byte << 56 must be done in uint64_t");
    const unsigned char qtop[8] = {0x80, 0, 0, 0, 0, 0, 0, 0x01};
    UINT(8u, unpack(qtop, "q", &q));
    UINT(UINT64_C(0x8000000000000001), q);
    CASE("round-trip of a packed record: \"chlqs\" then empty string and unknown char");
    const unsigned char wire[] = {0x41, 0x12, 0x34, 0xDE, 0xAD, 0xBE, 0xEF, 0, 0, 0, 0, 0, 0, 0, 1,
                                  0x00, 0x02, 'h', 'i', 0x00, 0x00};
    char text2[8];
    memset(text2, 'X', sizeof text2);
    c = 0; h = 0; l = 0; q = 0;
    UINT(sizeof wire, unpack(wire, "chl?qss", &c, &h, &l, &q, text, text2));
    INT(0x41, c);
    UINT(0x1234u, h);
    UINT(0xDEADBEEFu, l);
    UINT(1u, q);
    STRING("hi", text);
    STRING("", text2);
    UINT(0u, unpack(wire, "", &c));
}
#elif EXERCISE == 60
void run_tests(void) {
    CASE("IPv4 header with zeroed checksum field -> 0xB1E6");
    unsigned char header[20] = {0x45, 0x00, 0x00, 0x3C, 0x1C, 0x46, 0x40, 0x00, 0x40, 0x06,
                                0x00, 0x00, 0xAC, 0x10, 0x0A, 0x63, 0xAC, 0x10, 0x0A, 0x0C};
    UINT(0xB1E6u, internet_checksum(header, 20));
    CASE("same header with the checksum inserted verifies to 0");
    header[10] = 0xB1;
    header[11] = 0xE6;
    UINT(0u, internet_checksum(header, 20));
    CASE("odd length {01 02 03} pads the last byte on the right -> 0xFBFD");
    const unsigned char odd[3] = {0x01, 0x02, 0x03};
    UINT(0xFBFDu, internet_checksum(odd, 3));
    const unsigned char single[1] = {0xAB};
    UINT(0x54FFu, internet_checksum(single, 1));
    CASE("empty buffer -> 0xFFFF; {FF FF} -> 0");
    UINT(0xFFFFu, internet_checksum(header, 0));
    const unsigned char ffff[2] = {0xFF, 0xFF};
    UINT(0u, internet_checksum(ffff, 2));
    CASE("carries must fold: {FF FF FF FF} -> 0, many 0xFFFF words -> 0");
    const unsigned char four[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    UINT(0u, internet_checksum(four, 4));
    unsigned char many[2000];
    memset(many, 0xFF, sizeof many);
    UINT(0u, internet_checksum(many, sizeof many));
    CASE("insert-and-verify on an arbitrary odd-length payload");
    unsigned char payload[13] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0xAB, 0, 0, 0xCD}; /* field at 10..11 is zero */
    uint16_t sum = internet_checksum(payload, 13);
    payload[10] = (unsigned char)(sum >> 8); /* the field must sit on a 16-bit word boundary */
    payload[11] = (unsigned char)sum;
    UINT(0u, internet_checksum(payload, 13));
}
#endif
