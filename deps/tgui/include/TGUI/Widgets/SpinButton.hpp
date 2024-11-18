/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2024 Bruno Van de Velde (vdv_b@tgui.eu)
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

#ifndef TGUI_SPIN_BUTTON_HPP
#define TGUI_SPIN_BUTTON_HPP

#include <TGUI/Renderers/SpinButtonRenderer.hpp>
#include <TGUI/Widgets/ClickableWidget.hpp>
#include <TGUI/Timer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TGUI_MODULE_EXPORT namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Spin button widget
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API SpinButton : public ClickableWidget
    {
    public:

        using Ptr = std::shared_ptr<SpinButton>; //!< Shared widget pointer
        using ConstPtr = std::shared_ptr<const SpinButton>; //!< Shared constant widget pointer

        static constexpr const char StaticWidgetType[] = "SpinButton"; //!< Type name of the widget

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /// @brief Constructor
        /// @param typeName     Type of the widget
        /// @param initRenderer Should the renderer be initialized? Should be true unless a derived class initializes it.
        /// @see create
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SpinButton(const char* typeName = StaticWidgetType, bool initRenderer = true);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new spin button widget
        ///
        /// @param minimum  The minimum value of the spin button
        /// @param maximum  The maximum value of the spin button
        ///
        /// @return The new spin button
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static SpinButton::Ptr create(float minimum = 0, float maximum = 10);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another spin button
        ///
        /// @param spinButton  The other spin button
        ///
        /// @return The new spin button
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD static SpinButton::Ptr copy(const SpinButton::ConstPtr& spinButton);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD SpinButtonRenderer* getSharedRenderer() override;
        TGUI_NODISCARD const SpinButtonRenderer* getSharedRenderer() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD SpinButtonRenderer* getRenderer() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the spin button
        ///
        /// @param size  The new size of the spin button
        ///
        /// Note that the Orientation property is changed by this function based on the given width and height.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a minimum value
        ///
        /// @param minimum  The new minimum value
        ///
        /// When the value is too small then it will be changed to this minimum.
        /// The default minimum value is 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMinimum(float minimum);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the minimum value
        ///
        /// @return The current minimum value
        ///
        /// The default minimum value 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getMinimum() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets a maximum value
        ///
        /// @param maximum  The new maximum value
        ///
        /// When the value is too big then it will be changed to this maximum.
        /// The default maximum value is 10.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximum(float maximum);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the maximum value
        ///
        /// @return The current maximum value
        ///
        /// The default maximum value 10.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getMaximum() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the current value
        ///
        /// @param value  The new value
        ///
        /// The value can't be smaller than the minimum or bigger than the maximum.
        /// The default value is 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setValue(float value);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current value
        ///
        /// @return The current value
        ///
        /// The default value is 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getValue() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes how much the value changes on each arrow press
        /// @param step  The new step size
        /// @pre The step size must be a positive value or 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setStep(float step);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the number of positions the thumb advances with each move
        /// @return The current step size
        /// @see setStep
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD float getStep() const;

#ifndef TGUI_REMOVE_DEPRECATED_CODE
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the spin button lies horizontally or vertically
        /// @param vertical  Should the spin button lie vertically?
        ///
        /// This function will swap the width and height of the spin button if it didn't lie in the wanted direction.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_DEPRECATED("Use setOrientation instead")void setVerticalScroll(bool vertical);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the spin button lies horizontally or vertically
        /// @return Does the spin button lie vertically?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_DEPRECATED("Use getOrientation instead")TGUI_NODISCARD bool getVerticalScroll() const;
#endif

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the spin button lies horizontally or vertically
        /// @param orientation  Orientation of the spin button
        ///
        /// This function will swap the width and height of the spin button if it didn't lie in the wanted direction.
        ///
        /// @since TGUI 1.4
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setOrientation(Orientation orientation);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the spin button lies horizontally or vertically
        /// @return Orientation of the spin button
        /// @since TGUI 1.4
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Orientation getOrientation() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool leftMousePressed(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleased(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMoved(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(BackendRenderTarget& target, RenderStates states) const override;

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
        TGUI_NODISCARD Signal& getSignal(String signalName) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Name of the property that was changed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const String& property) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size of the arrows
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Vector2f getArrowSize() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_NODISCARD Widget::Ptr clone() const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Schedules a callback to regularly change the value of the spin button as long as the mouse remains pressed on an arrow
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void callMousePressPeriodically(std::chrono::time_point<std::chrono::steady_clock> clicked);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalFloat onValueChange = {"ValueChanged"}; //!< Value of the spin button changed. Optional parameter: new value

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        Orientation m_orientation = Orientation::Vertical; // Is the spin button draw horizontally (arrows next to each other) or vertically (arrows on top of each other)?
        std::chrono::time_point<std::chrono::steady_clock> m_PressedAt;

        float m_minimum = 0;
        float m_maximum = 10;
        float m_value = 0;
        float m_step = 1;

        // On which arrow is the mouse?
        bool m_mouseHoverOnTopArrow = false;
        bool m_mouseDownOnTopArrow = false;

        Sprite m_spriteArrowUp;
        Sprite m_spriteArrowUpHover;
        Sprite m_spriteArrowDown;
        Sprite m_spriteArrowDownHover;

        // Cached renderer properties
        Borders m_bordersCached;
        Color   m_borderColorCached;
        Color   m_backgroundColorCached;
        Color   m_backgroundColorHoverCached;
        Color   m_arrowColorCached;
        Color   m_arrowColorHoverCached;
        float   m_borderBetweenArrowsCached = 0;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_SPIN_BUTTON_HPP
