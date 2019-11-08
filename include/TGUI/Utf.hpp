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


#ifndef TGUI_UTF_HPP
#define TGUI_UTF_HPP

#include <string>
#include <array>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    namespace utf
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        void encodeCharUtf8(char32_t input, std::string& outStrUtf8);
        void convertUtf32toUtf8(const std::u32string& strUtf32, std::string& outStrUtf8);
        void convertUtf16toUtf8(const std::u16string& strUtf16, std::string& outStrUtf8);
        void convertWidetoUtf8(const std::wstring& wideStr, std::string& outStrUtf8);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        inline void encodeCharUtf8(char32_t input, std::string& outStrUtf8)
        {
            if (input < 128)
            {
                outStrUtf8.push_back(static_cast<int>(input));
                return;
            }

            // Encode the character (if it is valid)
            if ((input > 0x0010FFFF) || ((input >= 0xD800) && (input <= 0xDBFF)))
                return;

            // Get the number of bytes to write
            std::size_t bytestoWrite;
            if (input <  0x800)
                bytestoWrite = 2;
            else if (input <  0x10000)
                bytestoWrite = 3;
            else if (input <= 0x0010FFFF)
                bytestoWrite = 4;
            else
                return;

            static const unsigned char firstByteMask[5] = { 0, 0, 0xC0, 0xE0, 0xF0 };

            // Extract the bytes to write
            std::array<char, 4> bytes;
            if (bytestoWrite == 4) { bytes[3] = static_cast<char>((input | 0x80) & 0xBF); input >>= 6; }
            if (bytestoWrite >= 3) { bytes[2] = static_cast<char>((input | 0x80) & 0xBF); input >>= 6; }
            if (bytestoWrite >= 2) { bytes[1] = static_cast<char>((input | 0x80) & 0xBF); input >>= 6; }
            if (bytestoWrite >= 1) { bytes[0] = static_cast<char> (input | firstByteMask[bytestoWrite]); }

            // Add them to the output
            outStrUtf8.append(bytes.begin(), bytes.begin() + bytestoWrite);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        inline void convertUtf32toUtf8(const std::u32string& strUtf32, std::string& outStrUtf8)
        {
            for (const char32_t& codepoint : strUtf32)
                encodeCharUtf8(codepoint, outStrUtf8);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        inline void convertUtf16toUtf8(const std::u16string& strUtf16, std::string& outStrUtf8)
        {
            for (auto it = strUtf16.begin(); it != strUtf16.end(); ++it)
            {
                char32_t codepoint;
                char16_t first = *it;
                if ((first < 0xD800) || (first > 0xDBFF))
                    codepoint = first;
                else
                {
                    if (++it == strUtf16.end())
                        return; // Unfinished surrogate pair

                    char16_t second = *it;
                    if ((second >= 0xDC00) && (second <= 0xDFFF))
                        codepoint = ((first - 0xD800) << 10) + (second - 0xDC00) + 0x0010000;
                    else // Invalid surrogate pair
                        continue;
                }

                encodeCharUtf8(codepoint, outStrUtf8);
            }
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        inline void convertWidetoUtf8(const std::wstring& wideStr, std::string& outStrUtf8)
        {
            for (const wchar_t& codepoint : wideStr)
                encodeCharUtf8(static_cast<char32_t>(codepoint), outStrUtf8);
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_UTF_HPP
