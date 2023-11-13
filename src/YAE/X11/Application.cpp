/**
 * @file Application.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-13
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include "YAE/Application.h"
#include "YAE/Error.h"

namespace YAE 
{
    Application* mCurrApp = NULL; 

    Application& Application::Current() 
    {
        return *mCurrApp;
    }

    Application::Application() 
    {
        if (mCurrApp) 
            throw Error("YAE::Application: An application is already running.");
        
        mCurrApp = this;
        mDisplay = XOpenDisplay("");
        mDefaultScreen = DefaultScreen(mDisplay);
        mIsRunning = false;

        if (!mDisplay) {
            throw Error("YAE::Application: Cannot find a suitable X11 display.");
        }
    }

    Application::~Application()
    {
        XCloseDisplay(mDisplay);        
    }

    int Application::run() 
    {
        if (mIsRunning) {
            throw Error("YAE::Application: app is already running.");
        }

        mIsRunning = true;
        XEvent event;

        ready();

        while (mIsRunning) {
            

            XNextEvent(mDisplay, &event);

            if (event.type != KeymapNotify) {

                ::Window wnd = event.xany.window;

                if (!wnd) {
                    continue;
                }

                for (auto& windowWk : mWindows) {
                    auto window = windowWk.lock();

                    if (!window || window->handle() != wnd) {
                        continue;
                    }

                    window->dispatchXEvent(&event);
                }

            }
        }

        willTerminate();

        return EXIT_SUCCESS;
    }

    void Application::terminate() 
    {
        mIsRunning.store(false);
    }
}