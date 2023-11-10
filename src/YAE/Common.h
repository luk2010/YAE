/**
 * @file Common.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_COMMON_H__
#define __YAE_COMMON_H__

#include "configure.h"
#include <exception>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <string_view>
#include <atomic>
#include <vector>

#if YAE_LIB_OSX

#   ifndef __OBJC__
#       define YAE_OSX_ID(KLASS) void*
#       define YAE_OSX_IT(KLASS) void* 
#       define YAE_EVENTS protected
#   else  
#       include <CoreFoundation/CoreFoundation.h>
#       include <Cocoa/Cocoa.h>
#       define YAE_OSX_ID(KLASS) KLASS*
#       define YAE_OSX_IT(KLASS) id<KLASS>
#       define YAE_EVENTS public
#   endif 

#else  

#   define YAE_EVENTS protected

#endif 

namespace YAE 
{
    template < class T > using Ref = std::shared_ptr < T >;
    template < class T > using Weak = std::weak_ptr < T >;
    template < class T, class... A > inline auto Make(A&&...a) { return std::make_shared < T >(std::forward < A >(a)...); }
    
    /**
     * @brief 
     *     Defines a 2d point.
     */
    struct Point 
    {
        double x = 0; 
        double y = 0;

#   ifdef __OBJC__ 

        static inline CGPoint ToCGPoint(const Point& rhs)
        {
            return CGPointMake(rhs.x, rhs.y);
        }
        static inline Point FromCGPoint(const CGPoint& rhs)
        {
            return Point{ rhs.x, rhs.y };
        }

#   endif 
    };

    /**
     * @brief 
     *     A 2d size.
     */
    struct Size 
    {
        double width = 0;
        double height = 0;

#       ifdef __OBJC__

        static inline CGSize ToCGSize(const Size& rhs) 
        {
            return CGSizeMake(rhs.width, rhs.height);
        }
        static inline Size FromCGSize(const CGSize& rhs)
        {
            return Size{ rhs.width, rhs.height };
        }

#       endif 
    };

    /**
     * @brief 
     *     A 2d rectangle.
     */
    struct Rect 
    {
        Point origin; 
        Size size;

#       ifdef __OBJC__

        static inline CGRect ToCGRect(const Rect& rhs) 
        {
            return CGRectMake(rhs.origin.x, rhs.origin.y, rhs.size.width, rhs.size.height);
        }
        static inline Rect FromCGRect(const CGRect& rhs)
        {
            return Rect{ { rhs.origin.x, rhs.origin.y }, { rhs.size.width, rhs.size.height } };
        }

#       endif 
    };
}

#endif 
