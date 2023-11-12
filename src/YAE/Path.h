/**
 * @file Path.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-11
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_PATH_H__
#define __YAE_PATH_H__

#include "YAE/Common.h"

namespace YAE
{
    /**
     *  @brief
     *      A native representation of a 2d path.
     */
    class Path
    {
#       if YAE_LIB_OSX || YAE_LIB_IOS
        
        //! @brief The CGPathRef handle.
        CGPathRef mHandle;
        
    public:
        
        /**
         *  @brief
         *      Creates a new Path with a CGPathRef handle.
         */
        inline Path(CGPathRef handle): mHandle(handle) { }
        
        /**
         *  @brief
         *      Returns the path CGPathRef handle.
         */
        inline CGPathRef handle() const { return mHandle; }
        
#       endif
    };
}

#endif
