#pragma once
#ifndef _STMC_COMPRESSER_INTERFACE_H
# define _STMC_COMPRESSER_INTERFACE_H

#include "my_concept_include.h"
#include "strm.h"

TP(typename I, typename T)
using is_subcls = typename std::enable_if<std::is_base_of<I, T>::value>::type

TP(autolike B, typename T = strmap<B>)
struct CompresserInterface
{
    public:

        /**
         * 
         * # CompresserInterface
         * 
         * get compressing format info, or work compress/decompress inplace.
         * 
         * ## \[f\] `ptr-typ4idx CompresserInterface.calculate_decompressed_file_size(autolike compressed-file-ptr)`
         * 
         *  get size when decompress
         * 
         * ## \[inline-replace\] `void CompresserInterface.decompress_file(ptr target, autolike decompressed_file_size)`
         * 
         *  decompress by getting size and target ptr.
         * 
         * ## \[inline-replace\] `void CompresserInterface.compress_file(ptr target)`
         * 
         *  compress
         *  
         *  actually, it's too easy, It just needs to links, didn't requires other work.
         * 
         * ## \[inline-replace\] `void CompresserInterface.decompress_smartly(ptr target)`
         * 
         *  1. get `CompresserInterface.calculate_decompressed_file_size` 2 get size
         *  2. use `CompresserInterface.decompress_file` 2 decompress
         */

        virtual static inline autolike calculate_decompressed_file_size(autolike) = 0;
        virtual static inline void decompress_file(T*, autolike) = 0;
        virtual static inline void compress_file(T*) = 0;
        final static inline void decompress_smartly(T* file) {
            decompress_file(file, calculate_decompressed_file_size(file));
        }
};

TP(typename T)
using isCompresserInterface = is_subcls<CompresserInterface<autolike, strmap<autolike>>, T>;

TP(typename T)
concept CompresserInterfaced = isCompresserInterface<T>::value;

#endif