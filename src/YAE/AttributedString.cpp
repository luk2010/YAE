/**
 * @file AttributedString.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "AttributedString.h"

namespace YAE 
{
    AttributedString::AttributedString(const std::string& string, const TextAttributes& attributes) 
    {
        mString = string;
        mAttributes.resize(string.length(), attributes);
    }

    void AttributedString::set(const Range& range, const TextAttributes& attributes) 
    {
        std::size_t end = range.start + range.length;

        for (std::size_t i = range.start ; i <= end && i < mAttributes.size() ; ++i) {
            mAttributes[i].merge(attributes);
        }
    }

    TextAttributes AttributedString::attributesAtIndex(std::size_t index) const 
    {
        return mAttributes[index];
    }
}