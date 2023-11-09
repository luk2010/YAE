/**
 * @file Application.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_APPLICATION_H__
#define __YAE_APPLICATION_H__

#include "YAE/Common.h"

namespace YAE 
{
    /**
     * @brief 
     *     An Application class that holds the main logic of a program.
     * 
     * You generally derives from this class and implement observer methods like
     * `ready()` or `willTerminate()`. You cannot create multiple instance of this
     * class. Instead, get the current instance with the static method `Current()`.
     */
    class Application 
    {
#       if YAE_LIB_OSX 

        //! @brief The instance handle.
        YAE_OSX_ID(NSApplication) mHandle;

        //! @brief The delegate handle.
        YAE_OSX_IT(NSApplicationDelegate) mDelegateHandle;

    public:

        /**
         * @brief 
         *     Returns the NSApplication handle.
         */
        inline YAE_OSX_ID(NSApplication) handle() const { return mHandle; }

        /**
         * @brief 
         *     Returns the NSApplicationDelegate handle.
         */
        inline YAE_OSX_IT(NSApplicationDelegate) delegateHandle() const { return mDelegateHandle; }

    private:

#       endif 

    public:

        /**
         * @brief 
         *     Creates a new Application instance.
         */
        Application();

        /**
         * @brief 
         *     Virtual destructor.
         */
        virtual ~Application();

        /**
         * @brief 
         *     Runs the application main event loop.
         */
        virtual int run();

        /**
         * @brief 
         *     Terminates the application event loop.
         */
        virtual void terminate();

    YAE_EVENTS:

        /**
         * @brief 
         *     Called when the application is launched and ready.
         */
        virtual void ready() {}

        /**
         * @brief 
         *     Called when the application will terminate.
         */
        virtual void willTerminate() {}
    };
}

#endif 