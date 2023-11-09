/**
 * @file Application.mm
 * @author Luk2010
 * @brief
 * @version 0.1
 * @date 2023-11-09
 *
 * @copyright Atlanti's Corp @2023
 *
 */

#include "YAE/Application.h"
#include "YAE/Error.h"

@interface AppDelegate : NSObject < NSApplicationDelegate >
@property (nonatomic, assign) YAE::Application* app;
@end

@implementation AppDelegate
@synthesize app;

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    [NSApp activateIgnoringOtherApps:YES];
    self.app->ready();
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    self.app->willTerminate();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return NO;
}

@end

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
            throw Error("YAE::Application: An application has already been created.");

        mCurrApp = this;

        AppDelegate* delegate = mDelegateHandle = [[AppDelegate alloc] init];
        [delegate setApp:this];
        
        mHandle = NSApp = [NSApplication sharedApplication];
        [mHandle setActivationPolicy:NSApplicationActivationPolicyRegular];
        [mHandle setDelegate:mDelegateHandle];
    }

    Application::~Application() 
    {

    }

    int Application::run() 
    {
        [mHandle run];
        return 0;
    }
    
    void Application::terminate()
    {
        [mHandle terminate:nil];
    }
}
