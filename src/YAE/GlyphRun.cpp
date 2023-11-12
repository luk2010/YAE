/**
 * @file GlyphRun.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-12
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "YAE/GlyphRun.h"
#include "YAE/FontManager.h"

namespace YAE 
{
    GlyphRun::GlyphRun(const std::string_view& string, const TextAttributes& attributes, const Point& origin)
    {
        mString = string;
        mAttributes = attributes;

        if (!attributes.font) {
            mAttributes.font = FontManager::Get().font("Arial", 16, (FontTraitMask) FontTrait::Regular);
        }

        mGlyphs = mAttributes.font->glyphsForString(string);
        mPositions.resize(string.length(), Point());
        auto advances = mAttributes.font->advancesForGlyphs(mGlyphs);
        Point cursor = origin;

        for (auto i = 0; i < mGlyphs.size(); ++i) {
            mPositions[i] = cursor;
            cursor.x += advances[i].width;
            cursor.y += advances[i].height;
        }
    }

    std::size_t GlyphRun::numberOfGlyphs() const 
    {
        return mGlyphs.size();
    }

    const std::vector < GlyphId >& GlyphRun::glyphs() const 
    {
        return mGlyphs;
    }

    const std::vector < Point >& GlyphRun::positions() const 
    {
        return mPositions;
    }

    const TextAttributes& GlyphRun::attributes() const 
    {
        return mAttributes;
    }

    const std::string_view& GlyphRun::string() const 
    {
        return mString;
    }
}