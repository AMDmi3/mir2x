/*
 * =====================================================================================
 *
 *       Filename: pngtexoffdbn.hpp
 *        Created: 03/17/2016 01:17:51
 *  Last Modified: 07/06/2017 23:51:59
 *
 *    Description: 
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */


#pragma once
#include "pngtexoffdb.hpp"

#define PNGTEXOFFDBN_LC_DEPTH  (2              )
#define PNGTEXOFFDBN_LC_LENGTH (2048           )
#define PNGTEXOFFDBN_CAPACITY  (2 * 2048 + 1024)

using PNGTexOffDBType = PNGTexOffDB<
    PNGTEXOFFDBN_LC_DEPTH,PNGTEXOFFDBN_LC_LENGTH, PNGTEXOFFDBN_CAPACITY>;

class PNGTexOffDBN: public PNGTexOffDBType
{
    public:
        PNGTexOffDBN()
            : PNGTexOffDBType()
        {}

        virtual ~PNGTexOffDBN() = default;

    public:
        SDL_Texture *Retrieve(uint32_t nKey, int *pDX, int *pDY)
        {
            const auto &fnLinearCacheKey = [&](uint32_t nKey)
            {
                return (nKey & 0X0000FFFF) % PNGTEXOFFDBN_LC_LENGTH;
            };

            PNGTexOffItem stItem;
            RetrieveItem(nKey, &stItem, fnLinearCacheKey);

            if(pDX){ *pDX = stItem.DX; };
            if(pDY){ *pDY = stItem.DY; };

            return stItem.Texture;
        }

        SDL_Texture *Retrieve(uint8_t nIndex, uint16_t nImage, int *pDX, int *pDY)
        {
            return Retrieve((uint32_t)(((uint32_t)(nIndex) << 16) + nImage), pDX, pDY);
        }
};
