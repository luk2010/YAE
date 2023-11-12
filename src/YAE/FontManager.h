/**
 * @file FontManager.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-12
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_FONTMANAGER_H__
#define __YAE_FONTMANAGER_H__

#include "YAE/Font.h"

namespace YAE
{
    /**
     *  @brief
     *      Values used to make a font trait mask.
     */
    enum class FontTrait
    {
        Regular = 0,
        Italic = 1 << 0,
        Bold = 1 << 1,
        Condensed = 1 << 2
    };
    
    typedef std::underlying_type_t < FontTrait > FontTraitMask;
    
    /**
     *  @brief
     *      A Singleton that loads native fonts.
     */
    class FontManager
    {
    public:
        
        /**
         *  @brief
         *      Returns the static instance.
         */
        static inline FontManager& Get() {
            static FontManager instance;
            return instance;
        }
        
    private:
        
        /**
         *  @brief
         *      Constructor.
         */
        FontManager();
        
        FontManager(const FontManager&) = delete;
        FontManager& operator = (const FontManager&) = delete;
        
    public:
        
        /**
         *  @brief
         *      Loads a font.
         *
         *  @param familyName
         *      The font family name.
         *
         *  @param size
         *      The font size, in point units.
         *
         *  @param traits
         *      A FontTraitMask value.
         */
        Ref < Font > font(const std::string_view& familyName, float size, FontTraitMask traits);
    };
}

#endif 
