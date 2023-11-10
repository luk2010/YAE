/**
 * @file View.h
 * @author Luk2010
 * @brief 
 * @version 0.1
 * @date 2023-11-10
 * 
 * @copyright Atlanti's Corp @2023
 * 
 */

#ifndef __YAE_VIEW_H__
#define __YAE_VIEW_H__

#include "YAE/Common.h"

namespace YAE
{
    /**
     *  @brief
     *      Defines the most basic class to draw a YAE element in the native hierarchy.
     */
    class View : public std::enable_shared_from_this < View >
    {
        //! @brief The view's parent.
        Weak < View > mParent;
        
        //! @brief The view's children.
        std::vector < Ref < View > > mChildren;
        
        //! @brief True if the view should call `layoutChildren`.
        std::atomic < bool > mNeedsLayout;
        
#       if YAE_LIB_OSX
        
        //! @brief The NSView handle.
        YAE_OSX_ID(NSView) mHandle;
        
    public:
        
        /**
         *  @brief
         *      Returns the view handle.
         */
        inline YAE_OSX_ID(NSView) handle() const { return mHandle; }
        
    protected:
        
        /**
         *  @brief
         *      Sets the current NSView handle and returns the old handle.
         */
        virtual void* setHandle(void* handle);
        
#       endif
        
    public:
        
        /**
         *  @brief
         *      Creates a new view.
         *
         *  @param frameRect
         *      The initial view frame rectangle. Can be a zero sized rectangle.
         */
        View(const Rect& frameRect = Rect());
        
        /**
         *  @brief
         *      Destroys the view.
         */
        virtual ~View();
        
        /**
         *  @brief
         *      Returns the view's frame rectangle.
         */
        virtual Rect frame() const;
        
        /**
         *  @brief
         *      Sets the view's frame rectangle.
         *
         *  @note
         *      Setting the view's frame always triggers a call to `layoutChildren()`. Indeed,
         *      `setFrame()` calls `setNeedsLayout(true)`.
         */
        virtual void setFrame(const Rect& frameRect);
        
        /**
         *  @brief
         *      Returns the view parent.
         */
        inline Ref < View > parent() const { return mParent.lock(); }
        
        /**
         *  @brief
         *      Returns the view children.
         */
        inline auto children() const { return mChildren; }
        
        /**
         *  @brief
         *      Adds a child to the view hierarchy.
         *
         *  @param child
         *      The child view to add.
         *
         *  @param beforeHint
         *      A view before which the child should be inserted. If `nullptr`, then
         *      the child is appended at the end of the children list.
         *
         *  @return
         *      The child parameter on success, `nullptr` otherwise.
         *
         *  @note
         *      The method `shouldAddChild(child)` is called on this instance. If it
         *      returns `false`, the child is not inserted. It then calls `didAttach()` on the
         *      child and `didAddChild(child)` on the parent.
         */
        virtual Ref < View > addChild(const Ref < View >& child, const Ref < View >& beforeHint);
        
        /**
         *  @brief
         *      Sets weither the view needs to layout its children or not.
         */
        inline void setNeedsLayout(bool rhs) { mNeedsLayout.store(rhs); }
        
        /**
         *  @brief
         *      Updates the view.
         */
        void update();
        
    YAE_EVENTS:
        
        /**
         *  @brief
         *      Layouts its children.
         */
        virtual void layoutChildren() { }
        
        /**
         *  @brief
         *      Returns true if a given child view can be inserted in this view.
         */
        virtual bool shouldAddChild(const View& child) const { return true; }
        
        /**
         *  @brief
         *      Called when a view is inserted in the view children.
         */
        virtual void didAddChild(View& child) { }
        
        /**
         *  @brief
         *      Called when the view is attached to another parent.
         */
        virtual void didAttach() { }
    };
}

#endif 
