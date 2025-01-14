#pragma once
#ifndef _STRM_H
# define _STRM_H

#include "typs.h"

namespace strmc {

    TP(autolike B)
    struct bidxt //B-filted idxTyp
    {
        autolike v : B;
    };

    typedef struct {
        strt v;
    } not_basically_nullptred_strt;

    typedef struct {
        strt v = nullptr;
    } basically_nullptred_strt;

    TP(autolike B, bool basically_nullptred = false, typename T = bidxt<B>, typename MAPT = std::conditional<basically_nullptred, basically_nullptred_strt, not_basically_nullptred_strt>)
    struct strmap {
        /**
         * # file format `strmap`
         * 
         * ## call : strmap(filename)
         * 
         *  return hash-mapping ptr
         * 
         * ## idx : strmap[filename]
         * 
         *  hashmap idx access
         * 
         * ## how2work?
         * 
         *  - `indexof_dataseg frame[hash(filename)]`
         *  - `txt-file-seg dataseg`
         * 
         * it work as hash-map
         */
        public:
            MAPT frame[1<<B]; //MAP
            char detaseg[8<<sizeof(strt)]; //DATAS
            
            /**
             * # `strt& obj(strt filename)` it returns index of where file is placeses
             * 
             * ## fixing link
             * 
             * it can change where obj[filename] is pointing.
             * 
             * ### index nullptr
             * 
             *  = undefined
             * 
             * ## why `final` used
             * 
             * it should be work as struct, but objective.
             */
            final inline strt& operator()(strt filename) { //getlink;
                return &this->frame[this->strhash(filename)].v;
            }

            /**
             * # `strt& obj[strt filename]` use obj as an hashmap, by using obj(filename) to get index.
             * 
             * ## undefined value
             * 
             *  = if null returns.
             * 
             * ## why `final` used
             * 
             * it should be work as struct, but objective.
             */
            final inline strt& operator[](strt filename) {
                register strt idx = *this(filename);
                return idx==nullptr?null:&dataseg[idx]; //oh shit I don't know what I should do to.
            }   

        protected:
            virtual inline T strhash(strt) = 0;
    };
};

using strmc::strmap; //strmap<B>

#endif