/*
 * File: hashcode.h
 * Description: This header provides functionality to compute hash codes for various data types,
 * utilizing a deterministic algorithm to ensure uniform distribution across the integer space. 
 * It employs the djb2 algorithm by Daniel J. Bernstein.
 * 
 * Version: 2022/07/05
 * Source: Stanford University, Computer Science Department.
 */

#ifndef HASHCODE_H
#define HASHCODE_H

#include <string>
#include <utility>

constexpr int HASH_SEED = 5381;                 // Initial hash value
constexpr int HASH_MULTIPLIER = 33;             // Multiplier for hash computation
constexpr unsigned int HASH_MASK = ~0u >> 1;    // Mask to ensure a positive hash value

// Accessor functions for hash constants
constexpr int hashSeed() {
    return HASH_SEED;
}

constexpr int hashMultiplier() {
    return HASH_MULTIPLIER;
}

constexpr int hashMask() {
    return HASH_MASK;
}

// Overloaded hashCode functions for various types
constexpr int hashCode(bool key) {
    return static_cast<int>(key);
}

constexpr int hashCode(char key) {
    return key;
}

int hashCode(double key) {
    auto bytePtr = reinterpret_cast<const char*>(&key);
    unsigned hash = HASH_SEED;
    for (size_t i = 0; i < sizeof(double); ++i) {
        hash = HASH_MULTIPLIER * hash + static_cast<int>(bytePtr[i]);
    }
    return static_cast<int>(hash & HASH_MASK);
}

int hashCode(float key) {
    auto bytePtr = reinterpret_cast<const char*>(&key);
    unsigned hash = HASH_SEED;
    for (size_t i = 0; i < sizeof(float); ++i) {
        hash = HASH_MULTIPLIER * hash + static_cast<int>(bytePtr[i]);
    }
    return static_cast<int>(hash & HASH_MASK);
}

constexpr int hashCode(int key) {
    return key & HASH_MASK;
}

constexpr int hashCode(long key) {
    return static_cast<int>(key & HASH_MASK);
}

int hashCode(const char* str) {
    unsigned hash = HASH_SEED;
    for (int i = 0; str && str[i] != '\0'; ++i) {
        hash = HASH_MULTIPLIER * hash + str[i];
    }
    return static_cast<int>(hash & HASH_MASK);
}

int hashCode(const std::string& str) {
    unsigned hash = HASH_SEED;
    for (char ch : str) {
        hash = HASH_MULTIPLIER * hash + ch;
    }
    return static_cast<int>(hash & HASH_MASK);
}

constexpr int hashCode(void* key) {
    return hashCode(reinterpret_cast<long>(key));
}

// Template function to compute a hash code from multiple values
template <typename T1, typename T2, typename... Others>
int hashCode(T1&& first, T2&& second, Others&&... remaining) {
    int result = hashSeed();
    result += hashCode(std::forward<T2>(second), std::forward<Others>(remaining)...);
    result *= hashMultiplier();
    result += hashCode(std::forward<T1>(first));
    return hashCode(result);
}

#endif // HASHCODE_H
