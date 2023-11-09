/**
 * @file main.cpp
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#include <YAE/YAE.h>

class MainWin : public YAE::Window
{
public:
    using YAE::Window::Window;
    
YAE_EVENTS:
    void beforeClose() {
        YAE::Application::Current().terminate();
    }
};

class App : public YAE::Application 
{
    YAE::Ref < YAE::Window > mWindow;
    
protected:
    void ready() {
        mWindow = YAE::Make < MainWin >(YAE::Rect{
            {}, { 1024, 768 }
        });
        mWindow->show();
    }
};

int main() 
{
    return App().run();
}
