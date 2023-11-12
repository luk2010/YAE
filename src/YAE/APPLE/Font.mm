/**
 * @file Font.mm
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-11-11
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "YAE/Font.h"

namespace YAE
{
    double Font::size() const
    {
        return CTFontGetSize(mHandle);
    }
    
    std::string Font::familyName() const
    {
        CFStringRef name = CTFontCopyFamilyName(mHandle);
        
        std::string res;
        res.resize(CFStringGetLength(name), 0);
        
        CFStringGetCString(name, &res[0], res.size(), kCFStringEncodingUTF8);
        CFRelease(name);
        
        return res;
    }
    
    std::vector < std::size_t > Font::glyphsForString(const std::string_view& string) const
    {
        CFStringRef _string = CFStringCreateWithBytes(NULL, string.data(), string.length(), kCFStringEncodingUTF8, YES);
        
        std::vector < std::size_t > glyphs;
        std::vector < CGGlyph > _glyphs;
        _glyphs.resize(string.length());
        
        CTFontGetGlyphsForCharacters(mHandle, 
                                     CFStringGetCharactersPtr(_string),
                                     &_glyphs[0],
                                     string.length());
        
        glyphs.insert(glyphs.end(), _glyphs.begin(), _glyphs.end());
        
        CFRelease(_string);
        
        return glyphs;
    }
    
    Ref < Path > Font::pathForGlyph(std::size_t glyph) const
    {
        CGPathRef _path = CTFontCreatePathForGlyph(mHandle,
                                                   static_cast < CGGlyph >(glyph),
                                                   NULL);
        
        if (!_path)
            return nullptr;
    
        return Make < Path >(_path);
    }
}
