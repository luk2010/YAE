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

#if YAE_LIB_OSX 

#   ifndef __OBJC__
#       define YAE_OSX_ID(KLASS) void*
#       define YAE_OSX_IT(KLASS) void* 
#       define YAE_EVENTS protected
#   else  
#       define YAE_OSX_ID(KLASS) KLASS*
#       define YAE_OSX_IT(KLASS) id<KLASS>
#       define YAE_EVENTS public
#   endif 

#else  

#   define YAE_EVENTS protected

#endif 

#endif 