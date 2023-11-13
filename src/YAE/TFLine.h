/**
 * @file TFLine.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_TFLINE_H__
#define __YAE_TFLINE_H__

#include "YAE/AttributedString.h"
#include "YAE/GlyphRun.h"

namespace YAE 
{
    /**
     *  @brief 
     *      A text line that devises into multiple `GlyphRun` objects.
     */
    class TFLine 
    {
        //! @brief The string view for this line.
        std::string_view mString; 

        //! @brief The GlyphRuns for this line.
        std::vector < GlyphRun > mGlyphRuns; 

        //! @brief The attributed string.
        Ref < AttributedString > mAttribStr;

    public:


    };
}

#endif 