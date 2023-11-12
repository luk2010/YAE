/**
 * @file GlyphRun.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-12
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_GLYPHRUN_H__
#define __YAE_GLYPHRUN_H__

#include "YAE/Common.h"
#include "YAE/Font.h"
#include "YAE/TextAttributes.h"

namespace YAE
{
    /**
     *  @brief
     *      Represents a set of consecutive glyphs that shares the same charater attributes.
     */
    class GlyphRun
    {
        //! @brief The array of glyphs to render.
        std::vector < GlyphId > mGlyphs;
        
        //! @brief The array of positions of each glyph to render. The positions are relative
        //! to the beginning of the line surrrounding the run.
        std::vector < Point > mPositions;
        
        //! @brief The attributes used to render the glyphs.
        TextAttributes mAttributes;
        
        //! @brief The string used to render the glyphs.
        std::string_view mString;
        
    public:
        
        /**
         *  @brief
         *      Creates a new GlyphRun.
         *
         *  @param string
         *      The characters we need to render.
         *
         *  @param attributes
         *      The charater's attributes.
         *
         *  @param origin
         *      The run origin point.
         */
        GlyphRun(const std::string_view& string, const TextAttributes& attributes, const Point& origin);
        
        /**
         *  @brief
         *      Returns the number of glyphs.
         */
        std::size_t numberOfGlyphs() const;
        
        /**
         *  @brief
         *      Returns the glyphs to be rendered.
         */
        const std::vector < GlyphId >& glyphs() const;
        
        /**
         *  @brief
         *      Returns the positions for each glyph.
         */
        const std::vector < Point >& positions() const;
        
        /**
         *  @brief
         *      Returns the attributes.
         */
        const TextAttributes& attributes() const;
        
        /**
         *  @brief
         *      Returns the string used to render the glyphs.
         */
        const std::string_view& string() const;
    };
}

#endif 
