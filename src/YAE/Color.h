/**
 * @file Color.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-11
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_COLOR_H__
#define __YAE_COLOR_H__

#include "YAE/Common.h"

namespace YAE 
{
    /**
     *  @brief 
     *      A RGBA Color in a float format.    
     */
    struct Color 
    {
        float red = 0;
        float green = 0;
        float blue = 0;
        float alpha = 0;

        inline bool operator == (const Color& rhs) const 
        {
            return red == rhs.red 
                && green == rhs.green 
                && blue == rhs.blue 
                && alpha == rhs.alpha;
        }

#       if YAE_LIB_OSX && defined(__OBJC__)

        static inline NSColor* ToNSColor(const Color& rhs)
        {
            return [NSColor colorWithRed:static_cast < double >(rhs.red)
                                   green:static_cast < double >(rhs.green)
                                    blue:static_cast < double >(rhs.blue)
                                   alpha:static_cast < double >(rhs.alpha)];
        }
        static inline Color FromNSColor(NSColor* rhs)
        {
            return Color{ static_cast < float >(rhs.redComponent),
                          static_cast < float >(rhs.greenComponent),
                          static_cast < float >(rhs.blueComponent),
                          static_cast < float >(rhs.alphaComponent) };
        }

#       endif 
    };
}

#endif 
