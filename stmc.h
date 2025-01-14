#pragma once
#ifndef _STMC_H
# define _STMC_H

#include "stmc_compresser_interface.h"

TP(autolike B, CompresserInterfaced T, typename M = strmap<B>)
struct CompressedStrmap {
    /**
     * # `CompressedStrmap` 4 using var 2 use.
     * 
     * ## Functions (=Method... well too sucks methods (becauses...=), Actually, this is not perfect obj, and I hope it still be like union-managementing-struct)
     * 
     * ### `constructor`) `CompressedStrmap(can be dynamic \[compressed file | uncompressed stm file\])`
     * 
     * ### `__enter__`) `__enter__()` or `__enter__(size_that_will_encrease_when_decompress)`
     * 
     * ### `__exit__`) make it compress to end (not deconstruct, it isn't delete the file \[WARNING\])
     * 
     * ## field
     * 
     * ### `var.ptr4compressed_v` : compressed ver
     * 
     * ### `var.ptr4compressed_v` : uncompressed stm file type ver
     * 
     * ### WARN : not type safe.
     */

    public:
        union 
        {
            autolike ptr4compressed_v;
            M* ptr4decompressed_v;
        };

        final inline CompressedStrmap(autolike core) {
            this->ptr4compressed_v = core;
        }

        final inline CompressedStrmap(M* strmap) {
            this->ptr4decompressed_v = strmap;
        }

        final inline void __enter__(void) {
            T.decompress_smartly(this->ptr4compressed_v);
        }

        final inline void __enter__(autolike size) {
            T.decompress(this->ptr4compressed_v, size);
        }

        final inline void __exit__(void) {
            T.compress(this->ptr4compressed_v);
        }
};

#endif