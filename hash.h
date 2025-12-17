#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long out[5] = {0};

        int n = static_cast<int>(k.size());
        int group = 0;

        // build groups
        for (int end = n; end > 0; end -= 6) {
            if (group < 5) {
                int start = end - 6;
                if (start < 0) start = 0;

                unsigned long long value = 0;
                for (int i = start; i < end; i++) {
                    value = value * 36 + static_cast<unsigned long long>(letterDigitToNumber(k[i]));
                }
                out[4 - group] = value;
                group++;
            }
        }

        unsigned long long hash = 0;
        for (int i = 0; i < 5; i++) {
            hash += static_cast<unsigned long long>(rValues[i] * out[i]);
        }

        return static_cast<HASH_INDEX_T>(hash);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        unsigned char c = static_cast<unsigned char>(letter);
        c = static_cast<unsigned char>(std::tolower(c));
        if (c >= 'a' && c <= 'z') return static_cast<HASH_INDEX_T>(c - 'a');
        if (c >= '0' && c <= '9') return static_cast<HASH_INDEX_T>(26 + (c - '0'));
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
