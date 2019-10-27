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

#ifndef TGUI_OPTIONAL_HPP
#define TGUI_OPTIONAL_HPP

#include <TGUI/Config.hpp>

#if TGUI_COMPILED_WITH_CPP_VER >= 17
    #include <optional>
#else
    #include <memory>
#endif

namespace tgui
{
#if TGUI_COMPILED_WITH_CPP_VER >= 17
    template<typename T>
    using Optional = std::optional<T>;
#else
    template<typename T>
    class Optional
    {
    public:
        template<typename... Args>
        void emplace(Args&&... args)
        {
            m_ptr = std::make_unique<T>(args...);
        }

        explicit operator bool() const noexcept
        {
            return m_ptr;
        }

    private:
        std::unique_ptr<T> m_ptr;
    };
#endif
}

#endif // TGUI_OPTIONAL_HPP
