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
    
    std::vector < GlyphId > Font::glyphsForString(const std::string_view& string) const
    {
        NSString* _string = [[NSString alloc] initWithBytes:string.data()
                                                     length:string.length()
                                                   encoding:NSUTF8StringEncoding];
        
        NSUInteger bufferLength = [_string lengthOfBytesUsingEncoding:NSUTF16StringEncoding] + 1;
        UTF16Char* buffer = (UTF16Char*) malloc(bufferLength);
        [_string getCharacters:buffer range:NSMakeRange(0, _string.length)];
        
        std::vector < GlyphId > glyphs;
        glyphs.resize(string.length(), 0);
        
        CTFontGetGlyphsForCharacters(mHandle, 
                                     buffer,
                                     (CGGlyph*) glyphs.data(),
                                     string.length());
        
        return glyphs;
    }
    
    Ref < Path > Font::pathForGlyph(GlyphId glyph) const
    {
        CGPathRef _path = CTFontCreatePathForGlyph(mHandle,
                                                   static_cast < CGGlyph >(glyph),
                                                   NULL);
        
        if (!_path)
            return nullptr;
    
        return Make < Path >(_path);
    }
    
    std::vector < Size > Font::advancesForGlyphs(const std::vector < GlyphId >& glyphs) const
    {
        std::vector < Size > advances;
        advances.resize(glyphs.size(), Size());
        
        CTFontGetAdvancesForGlyphs(mHandle,
                                   kCTFontOrientationDefault,
                                   (const CGGlyph*) &glyphs[0],
                                   (CGSize*) &advances[0],
                                   (CGFloat) glyphs.size());
        
        return advances;
    }
}
