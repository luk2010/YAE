/**
 * @file AttributedString.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_ATTRIBUTEDSTRING_H__
#define __YAE_ATTRIBUTEDSTRING_H__

#include "YAE/Common.h"
#include "YAE/TextAttributes.h"

namespace YAE 
{
    /**
     *  @brief 
     *      A string that manages TextAttributes objects for each character in
     *      the string.
     */
    class AttributedString 
    {
        //! @brief The string.
        std::string mString;

        //! @brief The attributes.
        std::vector < TextAttributes > mAttributes;

    public:

        /**
         *  @brief 
         *      Creates a new AttributedString.
         * 
         *  @param string 
         *      The string to decorate.
         * 
         *  @param attributes
         *      The attributes to initialize the string with.    
         */
        AttributedString(const std::string& string, const TextAttributes& attributes = TextAttributes());

        /**
         *  @brief 
         *      Destructor.
         */
        virtual ~AttributedString() = default;

        /**
         *  @brief 
         *      Sets some attributes to the given range of characters in the string.
         */
        virtual void set(const Range& range, const TextAttributes& attributes);

        /**
         *  @brief 
         *      Returns the attributes of a given character.
         */
        virtual TextAttributes attributesAtIndex(std::size_t index) const;

        /**
         *  @brief 
         *      Returns the string.
         */
        const std::string& string() const { return mString; }

        /**
         *  @brief 
         *      Returns a view of the attributed string.
         */
        std::string_view view(const Range& range) const 
        {
            if (range.start + range.length > mString.length()) {
                return std::string_view();
            }

            return std::string_view(mString.data() + range.start, range.length);
        }
    };
}

#endif 