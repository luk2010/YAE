/**
 * @file TextAttributes.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-12
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_TEXTATTRIBUTES_H__
#define __YAE_TEXTATTRIBUTES_H__

#include "YAE/Common.h"
#include "YAE/Color.h"
#include "YAE/Font.h"

namespace YAE 
{
    /**
     *  @brief
     *      A set of attributes that can be used to render a character.
     */
    struct TextAttributes
    {
        //! @brief The text color.
        std::optional < Color > color;
        
        //! @brief The font used to render the text.
        Ref < Font > font;

        /**
         *  @brief 
         *      Merges this attribute with another attributes.
         */
        inline TextAttributes& merge(const TextAttributes& rhs)
        {
            if (rhs.color.has_value()) {
                color = rhs.color;
            }
            if (rhs.font) {
                font = rhs.font;
            }
            return *this;
        }

        /**
         *  @brief 
         *      Returns true if the attributes are equal.
         */
        inline bool isEqual(const TextAttributes& rhs) const  
        {
            return color.value_or(Color()) == rhs.color.value_or(Color())
                && font == rhs.font;
        }
    };
}

#endif 
