/**
 * @file FontManager.mm
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-12
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "YAE/FontManager.h"

namespace YAE
{
    FontManager::FontManager()
    {
        
    }
    
    Ref < Font > FontManager::font(const std::string_view& familyName, float size, FontTraitMask traits)
    {
        NSString* _familyName = [[NSString alloc] initWithBytes:familyName.data()
                                                         length:familyName.length()
                                                       encoding:NSUTF8StringEncoding];
        CGFloat _size = static_cast < CGFloat >(size);
        NSFontTraitMask _mask = 0;
        if (traits & (FontTraitMask) FontTrait::Bold) _mask |= NSFontBoldTrait;
        if (traits & (FontTraitMask) FontTrait::Italic) _mask |= NSFontItalicTrait;
        if (traits & (FontTraitMask) FontTrait::Condensed) _mask |= NSFontCondensedTrait;
        
        NSFont* _font = [NSFontManager.sharedFontManager fontWithFamily:_familyName
                                                                 traits:_mask
                                                                 weight:400
                                                                   size:size];
        
        if (!_font)
            return nullptr;
        
        return Make < Font >((__bridge_retained CTFontRef)_font);
    }
}
