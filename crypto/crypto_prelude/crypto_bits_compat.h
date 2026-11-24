/* The PVS2C IR emits unqualified names for integer_bv_ops primitives.
 * Use -include crypto_bits_compat.h when building those generated C files.
 * Define operations at their PVS word widths, including 64-bit XOR. */
#ifndef CRYPTO_BITS_COMPAT_H
#define CRYPTO_BITS_COMPAT_H

#include <stdint.h>

static inline uint8_t u8xor(uint8_t x, uint8_t y) { return (uint8_t)(x ^ y); }
static inline uint8_t u8and(uint8_t x, uint8_t y) { return (uint8_t)(x & y); }
static inline uint8_t u8or(uint8_t x, uint8_t y) { return (uint8_t)(x | y); }
static inline uint8_t u8not(uint8_t x) { return (uint8_t)~x; }

static inline uint16_t u16xor(uint16_t x, uint16_t y) { return (uint16_t)(x ^ y); }
static inline uint16_t u16and(uint16_t x, uint16_t y) { return (uint16_t)(x & y); }
static inline uint16_t u16or(uint16_t x, uint16_t y) { return (uint16_t)(x | y); }
static inline uint16_t u16not(uint16_t x) { return (uint16_t)~x; }

static inline uint32_t u32xor(uint32_t x, uint32_t y) { return (uint32_t)(x ^ y); }
static inline uint32_t u32and(uint32_t x, uint32_t y) { return (uint32_t)(x & y); }
static inline uint32_t u32or(uint32_t x, uint32_t y) { return (uint32_t)(x | y); }
static inline uint32_t u32not(uint32_t x) { return (uint32_t)~x; }

static inline uint64_t u64xor(uint64_t x, uint64_t y) { return (uint64_t)(x ^ y); }
static inline uint64_t u64and(uint64_t x, uint64_t y) { return (uint64_t)(x & y); }
static inline uint64_t u64or(uint64_t x, uint64_t y) { return (uint64_t)(x | y); }
static inline uint64_t u64not(uint64_t x) { return (uint64_t)~x; }

#endif
