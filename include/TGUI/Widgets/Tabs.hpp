/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_TAB_HPP
#define TGUI_TAB_HPP


#include <TGUI/Widget.hpp>
#include <TGUI/Renderers/TabsRenderer.hpp>
#include <TGUI/Text.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Tabs widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Tabs : public Widget
    {
    public:

        typedef std::shared_ptr<Tabs> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const Tabs> ConstPtr; ///< Shared constant widget pointer


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Tabs();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new tabs widget
        ///
        /// @return The new tabs
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Tabs::Ptr create();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another tab
        ///
        /// @param tab  The other tab
        ///
        /// @return The new tab
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Tabs::Ptr copy(Tabs::ConstPtr tab);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        ///
        /// @return Temporary pointer to the renderer
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TabsRenderer* getRenderer() const
        {
            return aurora::downcast<TabsRenderer*>(m_renderer.get());
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the area used by the tabs
        ///
        /// @param size  Total size of the tabs
        ///
        /// When this function is called, the tabs will no longer be auto-sizing, but each tab will get an equal width such that
        /// the total width corresponds to the size passed to this function.
        ///
        /// @see setAutoSize
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void setSize(const Layout2d& size) override;
        using Transformable::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the tabs are auto-sized or not
        ///
        /// @param autoSize  Should the size of the tabs depend on their content?
        ///
        /// When the tabs are in auto-size mode, the width of the tabs will be depend on the text which they contain.
        /// Otherwise, all tabs have an equal width to fill the size of the widget.
        ///
        /// The tabs are auto-sized by default.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setAutoSize(bool autoSize);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the tabs are auto-sized or not
        ///
        /// @return Is the width of the tabs dependent on their content?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getAutoSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a new tab
        ///
        /// @param text    The text of the tab that will be drawn on top of it
        /// @param select  Do you want the new tab to be selected immediately?
        ///
        /// @return  The index of the tab in the list
        ///
        /// @warning The index returned by this function may no longer be correct when a tab is removed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t add(const sf::String& text, bool select = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Inserts a new tab somewhere between the other tabs
        ///
        /// @param index   The index where the tab gets inserted. 0 means before the first tab, 1 means behind the first tab
        /// @param text    The text of the tab that will be drawn on top of it
        /// @param select  Do you want the new tab to be selected immediately?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void insert(std::size_t index, const sf::String& text, bool select = true);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets the text of one of the tabs
        ///
        /// @param index  The index of the tab. The first tab has index 0
        ///
        /// @return The text on the tab or an empty string when index was too high
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getText(std::size_t index) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of one of the tabs
        ///
        /// @param index  The index of the tab to be changed. The first tab has index 0
        /// @param text   The new text of the tab that will be drawn on top of it
        ///
        /// @return True when text was successfully changed, false when index was too high
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool changeText(std::size_t index, const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects the tab with a given text
        ///
        /// @param text  The text of the tab to select
        ///
        /// When the text doen't match any tab then nothing will be changed.
        /// If there are multiple tabs with the same text then the first one will be selected.
        ///
        /// @see select(int)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void select(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects the tab with a given index
        ///
        /// @param index  The index of the tab to select
        ///
        /// When the index is too high then nothing will happen.
        ///
        /// @see select(sf::String)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void select(std::size_t index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Deselects the selected tab
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deselect();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a tab with a given text
        ///
        /// @param text  The text on the tab to remove
        ///
        /// When multiple tabs have the same text, only the first will be removed.
        ///
        /// @see remove(unsigned int)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void remove(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes a tab with a given index
        ///
        /// @param index  The index of the tab to remove
        ///
        /// When the index is too high then nothing will happen.
        ///
        /// @see remove(sf::String)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void remove(std::size_t index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all tabs
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAll();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets the text that is drawn on the currently selected tab
        ///
        /// @return The text on the tab.
        ///         When no tab is selected then this function returns an empty string
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getSelected() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets the index of the currently selected tab
        ///
        /// @return The index of the tab.
        ///         When no tab is selected then this function returns -1
        ///
        /// @warning The index returned by this function may no longer be correct when a tab is removed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getSelectedIndex() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the character size of the text
        ///
        /// @param size  The new size of the text
        ///              If the size is 0 (default) then the text will be scaled to fit in the tab.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int size);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the character size of the text
        ///
        /// @return The text size
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the height of the tabs
        ///
        /// @param height  Height of the tabs
        ///
        /// When the tabs are auto-sizing, this function allows changing the width of the tabs without setting a fixed width
        /// like calling setSize would do.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTabHeight(float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the maximum tab width of the tabs
        ///
        /// @param maximumWidth  Maximum width of a single tab
        ///
        /// This property only has effect when the tabs are auto-sizing.
        ///
        /// If the text on the tab is longer than this width then it will be cropped to fit inside the tab.
        /// By default, the maximum width is 0 which means that there is no limitation.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumTabWidth(float maximumWidth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum tab width of the tabs
        ///
        /// @return Maximum tab width
        ///
        /// This property only has effect when the tabs are auto-sizing.
        ///
        /// If the text on the tab is longer than this width then it will be cropped to fit inside the tab.
        /// By default, the maximum width is 0 which means that there is no limitation.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getMaximumTabWidth() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the minimum tab width of the tabs
        ///
        /// @param minimumWidth  Minimum width of a single tab
        ///
        /// This property only has effect when the tabs are auto-sizing.
        ///
        /// Every tab is at least as wide as this minimum or twice the distance to side.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMinimumTabWidth(float minimumWidth);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the minimum tab width of the tabs
        ///
        /// @return Minimum tab width
        ///
        /// This property only has effect when the tabs are auto-sizing.
        ///
        /// Every tab is at least as wide as this minimum or twice the distance to side.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getMinimumTabWidth() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the amount of tabs
        ///
        /// @return Number of tabs
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getTabsCount() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        ///
        /// @return Is the mouse on top of the widget?
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual bool mouseOnWidget(sf::Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void leftMousePressed(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseMoved(sf::Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void mouseNoLongerOnWidget() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves a signal based on its name
        ///
        /// @param signalName  Name of the signal
        ///
        /// @return Signal that corresponds to the name
        ///
        /// @throw Exception when the name does not match any signal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Signal& getSignal(std::string&& signalName) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculates the size of each tab image.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void recalculateTabsWidth();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update the colors of the text that is drawn on the tabs
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateTextColors();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual Widget::Ptr clone() const override
        {
            return std::make_shared<Tabs>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalWrapper<SignalString> onTabSelect = {"TabSelected"}; ///< An item was selected in the list box. Optional parameter: selected item


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:
        unsigned int       m_requestedTextSize = 0;
        unsigned int       m_textSize = 22;
        float              m_maximumTabWidth = 0;
        float              m_minimumTabWidth = 0;
        int                m_selectedTab = -1;
        int                m_hoveringTab = -1;
        bool               m_autoSize = true;
        std::vector<float> m_tabWidth;
        std::vector<Text>  m_tabTexts;

        Sprite m_spriteTab;
        Sprite m_spriteSelectedTab;

        // Cached renderer properties
        Borders   m_bordersCached;
        Color     m_borderColorCached;
        Color     m_backgroundColorCached;
        Color     m_backgroundColorHoverCached;
        Color     m_selectedBackgroundColorCached;
        Color     m_selectedBackgroundColorHoverCached;
        Color     m_textColorCached;
        Color     m_textColorHoverCached;
        Color     m_selectedTextColorCached;
        Color     m_selectedTextColorHoverCached;
        float     m_distanceToSideCached = 0;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_TAB_HPP
