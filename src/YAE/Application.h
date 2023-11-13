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
#include "YAE/Window.h"

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
        //! @brief The current opened windows.
        std::vector < Weak < Window > > mWindows;

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

#       elif YAE_LIB_X11

        //! @brief The X11 display.
        Display* mDisplay;

        //! @brief The default screen.
        int mDefaultScreen;

        //! @brief Is the app running ?
        std::atomic < bool > mIsRunning;

    public:

        /**
         *  @brief 
         *      Returns the current display handle.
         */
        inline Display* display() const { return mDisplay; }

        /**
         *  @brief 
         *      Returns the default screen.
         */
        inline int defaultScreen() const { return mDefaultScreen; }

#       endif 

    public:
        
        /**
         *  @brief
         *      Returns the current application.
         */
        static Application& Current();

        /**
         *  @brief
         *     Creates a new Application instance.
         */
        Application();

        /**
         *  @brief
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

        /**
         *  @brief
         *      Registers a window in the application.
         */
        virtual inline void addWindow(const Ref < Window >& window)
        {
            for (auto it = mWindows.begin(); it != mWindows.end(); it++) {
                if ((*it).lock() == window) {
                    return;
                }
            }
            mWindows.push_back(window);
        }

        /**
         *  @brief 
         *      Unregisters a window from the application.
         */
        virtual inline void removeWindow(const Ref < Window >& window) 
        {
            for (auto it = mWindows.begin(); it != mWindows.end(); it++) {
                if ((*it).lock() == window) {
                    mWindows.erase(it);
                    return;
                }
            }
        }

        /**
         *  @brief 
         *      Returns the windows currently opened.
         */
        inline auto windows() const { return mWindows; }

        /**
         *  @brief 
         *      Returns true if the app is currently running.
         */
        bool isRunning() const;

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
