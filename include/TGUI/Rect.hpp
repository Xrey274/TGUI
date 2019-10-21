/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
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


#ifndef TGUI_RECT_HPP
#define TGUI_RECT_HPP

#include <TGUI/Vector2.hpp>

#include <SFML/Graphics/Rect.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    template <typename T>
    class Rect
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Default constructor
        ///
        /// Creates an empty rectangle (it is equivalent to calling Rect{0, 0, 0, 0}).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_CONSTEXPR Rect() = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructs the rectangle from an sf::Rect
        ///
        /// @param rect  Rectangle to initialize
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Rect(sf::Rect<T> rect) :
            left  {rect.left},
            top   {rect.top},
            width {rect.width},
            height{rect.height}
        {
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructs the rectangle from its position and size
        ///
        /// @param rectLeft   Left coordinate of the rectangle
        /// @param rectTop    Top coordinate of the rectangle
        /// @param rectWidth  Width of the rectangle
        /// @param rectHeight Height of the rectangle
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_CONSTEXPR Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight) :
            left  {rectLeft},
            top   {rectTop},
            width {rectWidth},
            height{rectHeight}
        {
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructs the rectangle from its position and size
        ///
        /// @param position Position of the top-left corner of the rectangle
        /// @param size     Size of the rectangle
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_CONSTEXPR Rect(Vector2<T> position, Vector2<T> size) :
            left  {position.x},
            top   {position.y},
            width {size.x},
            height{size.y}
        {
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the position of the rectangle
        ///
        /// @param position  New position for the rectangle
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_CONSTEXPR void setPosition(Vector2<T> position)
        {
            left = position.x;
            top = position.y;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the position of the rectangle
        ///
        /// @return Rectangle position
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_CONSTEXPR Vector2<T> getPosition() const
        {
            return {left, top};
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the size of the rectangle
        ///
        /// @param size  New size for the rectangle
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_CONSTEXPR void setSize(Vector2<T> size)
        {
            width = size.x;
            height = size.y;
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the size of the rectangle
        ///
        /// @return Rectangle size
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_CONSTEXPR Vector2<T> getSize() const
        {
            return {width, height};
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts the Rect to an sf::Rect
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        operator sf::Rect<T>() const
        {
            return sf::Rect<T>{left, top, width, height};
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Check if a point is inside the rectangle's area
        ///
        /// This check is non-inclusive. If the point lies on the edge of the rectangle, this function will return false.
        ///
        /// @param pos  Coordinate to test
        ///
        /// @return True if the point is inside, false otherwise
        ///
        /// @warning This code assumes the width and height are positive.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_CONSTEXPR bool contains(const Vector2<T>& pos) const
        {
            return (pos.x >= left) && (pos.x < left + width) && (pos.y >= top) && (pos.y < top + height);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Check the intersection between two rectangles
        ///
        /// @param rectangle  Rectangle to test
        ///
        /// @return True if rectangles overlap, false otherwise
        ///
        /// @warning This code assumes the width and height of both rectangles are positive.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TGUI_CONSTEXPR bool intersects(const Rect<T>& rect) const
        {
            // Compute the intersection boundaries
            const T interLeft   = std::max(left, rect.left);
            const T interTop    = std::max(top, rect.top);
            const T interRight  = std::min(left + width, rect.left + rect.width);
            const T interBottom = std::min(top + height, rect.top + rect.height);

            // If the intersection is valid (positive non zero area), then there is an intersection
            return (interLeft < interRight) && (interTop < interBottom);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        T left = 0;   ///< Left coordinate of the rectangle
        T top = 0;    ///< Top coordinate of the rectangle
        T width = 0;  ///< Width of the rectangle
        T height = 0; ///< Height of the rectangle
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Checks if two Rect objects are equal
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    TGUI_CONSTEXPR bool operator==(const Rect<T>& left, const Rect<T>& right)
    {
        return (left.left == right.left) && (left.width == right.width)
            && (left.top == right.top) && (left.height == right.height);
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Checks if two Rect objects are different
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T>
    TGUI_CONSTEXPR bool operator!=(const Rect<T>& left, const Rect<T>& right)
    {
        return !(left == right);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    using FloatRect = Rect<float>;
    using UIntRect = Rect<unsigned int>;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_RECT_HPP
