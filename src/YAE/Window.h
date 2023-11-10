/**
 * @file Window.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-09
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_WINDOW_H__
#define __YAE_WINDOW_H__

#include "YAE/Common.h"
#include "YAE/View.h"

namespace YAE 
{
    /**
     * @brief 
     *      A Window on the screen.
     */
    class Window 
    {
        //! @brief The content view.
        Ref < View > mContentView;
        
#       if YAE_LIB_OSX

        //! @brief The NSWindow handle.
        YAE_OSX_ID(NSWindow) mHandle;

        //! @brief The NSWindowDelegate handle.
        YAE_OSX_IT(NSWindowDelegate) mDelegateHandle;

    public: 

        /**
         * @brief 
         *      Returns the NSWindow handle.
         */
        inline YAE_OSX_ID(NSWindow) handle() const { return mHandle; }

        /**
         * @brief 
         *      Returns the NSWindowDelegate handle.
         */
        inline YAE_OSX_IT(NSWindowDelegate) delegateHandle() const { return mDelegateHandle; }

    private:

#       endif

    public:

        /**
         * @brief 
         *      The available window styles.
         */
        enum Style 
        {
            Closable = 1 << 0,
            Resizable = 1 << 1,
            Titled = 1 << 2,

            Default = Closable|Resizable|Titled 
        };

        /**
         * @brief 
         *      Creates a new Window instance.
         *
         * @param frameRect
         *      The Rect that defines the window content frame.
         *
         * @param style
         *      The window style.
         */
        Window(const Rect& frameRect, Style style = Default);

        /**
         * @brief 
         *      Shows the window.
         */
        virtual void show();

        /**
         * @brief 
         *      Closes the window.
         */
        virtual void close();
        
        /**
         *  @brief
         *      Returns the window frame, including the title bar.
         */
        virtual Rect frame() const;
        
        /**
         *  @brief
         *      Sets the window frame, including the title bar.
         */
        virtual void setFrame(const Rect& frame);
        
        /**
         *  @brief
         *      Returns the content region size.
         */
        virtual Size contentSize() const;
        
        /**
         *  @brief
         *      Sets the window content size, i.e. the window size minus the
         *      title bar.
         */
        virtual void setContentSize(const Size& size);
        
        /**
         *  @brief
         *      Returns the window title.
         */
        virtual std::string_view title() const;
        
        /**
         *  @brief
         *      Sets the window title.
         */
        virtual void setTitle(const std::string_view& title);
        
        /**
         *  @brief
         *      Returns the content view.
         */
        inline auto contentView() const { return mContentView; }
        
        /**
         *  @brief
         *      Sets the content view.
         */
        void setContentView(const Ref < View >& view);
        
    YAE_EVENTS:
        
        /**
         * @brief
         *      Called before the window closes.
         */
        virtual void beforeClose() {}
        
        /**
         *  @brief
         *      Called after the window did resize.
         */
        virtual void resized(const Size& size) {}
    };
}

#endif 
