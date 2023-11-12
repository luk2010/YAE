/**
 * @file Font.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-11
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_FONT_H__
#define __YAE_FONT_H__

#include "YAE/Common.h"
#include "YAE/Path.h"

namespace YAE
{
    /**
     *  @brief
     *      A native raw font.
     */
    class Font
    {
#       if YAE_LIB_OSX
        
        //! @brief The CoreText CTFont instance.
        CTFontRef mHandle;
        
    public:
        
        /**
         *  @brief
         *      Returns the CTFont instance.
         */
        inline CTFontRef handle() const { return mHandle; }
        
        /**
         *  @brief
         *      Creates a new font from a CTFontRef instance.
         */
        inline Font(CTFontRef handle): mHandle(handle) { }
        
        /**
         *  @brief
         *      Destroys the font.
         */
        inline ~Font() { CFRelease(mHandle); }
        
#       endif
        
    public:
        
        /**
         *  @brief
         *      Returns the font size.
         */
        double size() const;
        
        /**
         *  @brief
         *      Returns the font family name.
         */
        std::string familyName() const;
        
        /**
         *  @brief
         *      Returns a list of glyph indices for the given string.
         */
        std::vector < std::size_t > glyphsForString(const std::string_view& string) const;
        
        /**
         *  @brief
         *      Returns the path for a given glyph index.
         */
        Ref < Path > pathForGlyph(std::size_t glyph) const;
    };
}

#endif 
