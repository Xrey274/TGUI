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


#ifndef TGUI_STRING_HPP
#define TGUI_STRING_HPP

#include <TGUI/Config.hpp>
#include <string>
#include <cstring>
#include <locale>
#include <sstream>

#include <SFML/System/String.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Checks if a character is a whitespace character (space, tab, carriage return or line feed)
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API bool isWhitespace(char character);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Checks if a character is a whitespace character (space, tab, carriage return or line feed)
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TGUI_API bool isWhitespace(char32_t character);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Wrapper class to store strings
    ///
    /// A constructor and conversion operator are provided for sf::String to easily convert between sf::String and tgui::String.
    ///
    /// The interface is similar to std::string, but there are constructors and conversion operators to construct from and
    /// convert to std::string, std::wstring, std::u16string, std::u32string and std::u8string (if supported).
    /// Some extra helper functions are also provided to e.g. convert the string to an integer or float or to lowercase.
    ///
    /// All "const char*" and std::string arguments and return values are assumed to be UTF-8 encoded.
    /// Because data is stored as UTF-8, no conversions take place when assigning from std::string and getting the string back,
    /// so any encoding could be used as long as you don't expect the value to be shown or converted to a different string type.
    ///
    /// Note that data is stored as bytes, so e.g. str[2] will return the 3th byte, not necessarily the 3th UTF character.
    /// If you do need to access the codepoint, you need to first convert to UTF-32: str.toUtf32()[2]
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API String
    {
    private:
        std::string m_string;

    public:

        static const decltype(std::string::npos) npos;

        using iterator = std::string::iterator;
        using const_iterator = std::string::const_iterator;
        using reverse_iterator = std::string::reverse_iterator;
        using const_reverse_iterator = std::string::const_reverse_iterator;

        using value_type = char;
        using reference = char&;
        using const_reference = const char&;


    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts the string to an integer
        ///
        /// @param defaultValue  Value to return if conversion fails
        ///
        /// @brief Returns the integer value or defaultValue if the string didn't contain a base 10 integer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int toInt(int defaultValue = 0) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts the string to an unsigned int
        ///
        /// @param defaultValue  Value to return if conversion fails
        ///
        /// @brief Returns the unsigned integer value or defaultValue if the string didn't contain a base 10 unsigned integer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int toUInt(unsigned int defaultValue = 0) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts the string to a float
        ///
        /// @param defaultValue  Value to return if conversion fails
        ///
        /// @brief Returns the float value or defaultValue if the string didn't contain an float
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float toFloat(float defaultValue = 0) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a string with the whitespace at the start and end of this string removed
        ///
        /// @return Trimmed string
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String trim() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts the ASCII characters in the string to lowercase
        ///
        /// @return Lowercase string
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String toLower() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Converts the ASCII characters in the string to uppercase
        ///
        /// @return Uppercase string
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String toUpper() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Replaces all occurrences of a substring with a replacement string
        ///
        /// @param searchFor   The value being searched for
        /// @param replaceWith The value that replaces found searchFor values
        ///
        /// @return Reference to this object.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        String& replace(const String& searchFor, const String& replaceWith);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Construct the string from a number
        ///
        /// @param value  Number to convert to string
        ///
        /// @return String representing given number
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        template <typename T>
        static String fromNumber(T value)
        {
            std::ostringstream oss;
            oss.imbue(std::locale::classic());
            oss << value;
            return String(oss.str());
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        String() = default;

        String(const std::string& str);
        String(const std::wstring& str);
        String(const std::u16string& str);
        String(const std::u32string& str);

        String(std::string&& str) :
            m_string(std::move(str))
        {
        }

        String(char ansiChar);
        String(wchar_t wideChar);
        String(char16_t wideChar);
        String(char32_t wideChar);

        String(const char* str) :
            m_string(str)
        {
        }

        String(const wchar_t* str);
        String(const char16_t* str);
        String(const char32_t* str);

        String(std::size_t count, char ch);

        String(const std::string& str, std::size_t pos);
        String(const std::string& str, std::size_t pos, std::size_t count);
        String(const char* str, std::size_t count);

        String(std::initializer_list<char> chars);
        String(std::initializer_list<wchar_t> chars);
        String(std::initializer_list<char16_t> chars);
        String(std::initializer_list<char32_t> chars);

        String(std::string::const_iterator first, std::string::const_iterator last);
        String(std::wstring::const_iterator first, std::wstring::const_iterator last);
        String(std::u16string::const_iterator first, std::u16string::const_iterator last);
        String(std::u32string::const_iterator first, std::u32string::const_iterator last);

        String(const sf::String& str);
        explicit operator sf::String() const;

        explicit operator std::string() const
        {
            return m_string;
        }

        explicit operator std::wstring() const;
        explicit operator std::u16string() const;
        explicit operator std::u32string() const;

        std::string toAnsiString() const
        {
            return m_string;
        }

        std::wstring toWideString() const;
        std::u16string toUtf16() const;
        std::u32string toUtf32() const;

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        std::u8string toUtf8() const
        {
            return std::u8string(m_string.begin(), m_string.end());
        }
#else
        std::string toUtf8() const
        {
            return m_string;
        }
#endif

        String& assign(std::size_t count, char ch);
        String& assign(const std::string& str);
        String& assign(const String& str);
        String& assign(const std::string& str, std::size_t pos, std::size_t count = npos);
        String& assign(const String& str, std::size_t pos, std::size_t count = npos);
        String& assign(std::string&& str);
        String& assign(String&& str);
        String& assign(const char* str, std::size_t count);
        String& assign(const char* str);
        String& assign(std::initializer_list<char> chars);
        String& assign(std::string::const_iterator first, std::string::const_iterator last);

        reference       at(std::size_t pos);
        const_reference at(std::size_t pos) const;

        const_reference operator [](std::size_t index) const;
        reference operator [](std::size_t index);

        reference       front();
        const_reference front() const;

        reference       back();
        const_reference back() const;

        const char* data() const noexcept;
#if __cplusplus >= 201703L
        char* data() noexcept
        {
            return m_string.data();
        }
#endif
        const char* c_str() const noexcept;

        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        const_iterator cbegin() const noexcept;

        iterator end() noexcept;
        const_iterator end() const noexcept;
        const_iterator cend() const noexcept;

        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator crbegin() const noexcept;

        reverse_iterator rend() noexcept;
        const_reverse_iterator rend() const noexcept;
        const_reverse_iterator crend() const noexcept;

        bool empty() const noexcept;
        std::size_t size() const noexcept;
        std::size_t length() const noexcept;
        std::size_t max_size() const noexcept;

        void reserve(std::size_t newCap);
        std::size_t capacity() const noexcept;
        void shrink_to_fit();

        void clear() noexcept;

        String& insert(std::size_t index, std::size_t count, char ch);
        String& insert(std::size_t index, const std::string& str);
        String& insert(std::size_t index, const String& str);
        String& insert(std::size_t index, const std::string& str, std::size_t pos, std::size_t count = npos);
        String& insert(std::size_t index, const String& str, std::size_t pos, std::size_t count = npos);
        String& insert(std::size_t index, const char* str, std::size_t count);
        String& insert(std::size_t index, const char* str);
        iterator insert(const_iterator pos, char ch);
        iterator insert(const_iterator pos, std::size_t count, char ch);
        iterator insert(const_iterator pos, std::initializer_list<char> chars);
        iterator insert(const_iterator pos, std::string::const_iterator first, std::string::const_iterator last);

        String& erase(std::size_t index = 0, std::size_t count = npos);
        iterator erase(const_iterator position);
        iterator erase(const_iterator first, const_iterator last);

        void push_back(char ch);
        void pop_back();

        String& append(std::size_t count, char ch);
        String& append(const std::string& str);
        String& append(const String& str);
        String& append(const std::string& str, std::size_t pos, std::size_t count = npos);
        String& append(const String& str, std::size_t pos, std::size_t count = npos);
        String& append(const char* str, std::size_t count);
        String& append(const char* str);
        String& append(std::string::const_iterator first, std::string::const_iterator last);
        String& append(std::initializer_list<char> chars);

        String& operator+=(const String& str);

        int compare(const std::string& str) const noexcept;
        int compare(const String& str) const noexcept;
        int compare(std::size_t pos1, std::size_t count1, const std::string& str) const;
        int compare(std::size_t pos1, std::size_t count1, const String& str) const;
        int compare(std::size_t pos1, std::size_t count1, const std::string& str, std::size_t pos2, std::size_t count2 = npos) const;
        int compare(std::size_t pos1, std::size_t count1, const String& str, std::size_t pos2, std::size_t count2 = npos) const;
        int compare(const char* s) const;
        int compare(std::size_t pos1, std::size_t count1, const char* s) const;
        int compare(std::size_t pos1, std::size_t count1, const char* s, std::size_t count2) const;

        String& replace(std::size_t pos, std::size_t count, const std::string& str);
        String& replace(std::size_t pos, std::size_t count, const String& str);
        String& replace(const_iterator first, const_iterator last, const std::string& str);
        String& replace(const_iterator first, const_iterator last, const String& str);
        String& replace(std::size_t pos, std::size_t count, const std::string& str, std::size_t pos2, std::size_t count2 = npos);
        String& replace(std::size_t pos, std::size_t count, const String& str, std::size_t pos2, std::size_t count2 = npos);
        String& replace(const_iterator first, const_iterator last, std::string::const_iterator first2, std::string::const_iterator last2);
        String& replace(std::size_t pos, std::size_t count, const char* cstr, std::size_t count2);
        String& replace(const_iterator first, const_iterator last, const char* cstr, std::size_t count2);
        String& replace(std::size_t pos, std::size_t count, const char* cstr);
        String& replace(const_iterator first, const_iterator last, const char* cstr);
        String& replace(std::size_t pos, std::size_t count, std::size_t count2, char ch);
        String& replace(const_iterator first, const_iterator last, std::size_t count2, char ch);
        String& replace(const_iterator first, const_iterator last, std::initializer_list<char> chars);

        String substr(std::size_t pos = 0, std::size_t count = npos) const;

        std::size_t copy(char* dest, std::size_t count, std::size_t pos = 0) const;

        void resize(std::size_t count);
        void resize(std::size_t count, char ch);

        void swap(String& other);

        std::size_t find(const std::string& str, std::size_t pos = 0) const noexcept;
        std::size_t find(const String& str, std::size_t pos = 0) const noexcept;
        std::size_t find(const char* s, std::size_t pos, std::size_t count) const;
        std::size_t find(const char* s, std::size_t pos = 0) const;
        std::size_t find(char ch, std::size_t pos = 0) const noexcept;

        std::size_t find_first_of(const std::string& str, std::size_t pos = 0) const noexcept;
        std::size_t find_first_of(const String& str, std::size_t pos = 0) const noexcept;
        std::size_t find_first_of(const char* s, std::size_t pos, std::size_t count) const;
        std::size_t find_first_of(const char* s, std::size_t pos = 0) const;
        std::size_t find_first_of(char ch, std::size_t pos = 0) const noexcept;

        std::size_t find_first_not_of(const std::string& str, std::size_t pos = 0) const noexcept;
        std::size_t find_first_not_of(const String& str, std::size_t pos = 0) const noexcept;
        std::size_t find_first_not_of(const char* s, std::size_t pos, std::size_t count) const;
        std::size_t find_first_not_of(const char* s, std::size_t pos = 0) const;
        std::size_t find_first_not_of(char ch, std::size_t pos = 0) const noexcept;

        std::size_t rfind(const std::string& str, std::size_t pos = npos) const noexcept;
        std::size_t rfind(const String& str, std::size_t pos = npos) const noexcept;
        std::size_t rfind(const char* s, std::size_t pos, std::size_t count) const;
        std::size_t rfind(const char* s, std::size_t pos = npos) const;
        std::size_t rfind(char ch, std::size_t pos = npos) const noexcept;

        std::size_t find_last_of(const std::string& str, std::size_t pos = npos) const noexcept;
        std::size_t find_last_of(const String& str, std::size_t pos = npos) const noexcept;
        std::size_t find_last_of(const char* s, std::size_t pos, std::size_t count) const;
        std::size_t find_last_of(const char* s, std::size_t pos = npos) const;
        std::size_t find_last_of(char ch, std::size_t pos = npos) const noexcept;

        std::size_t find_last_not_of(const std::string& str, std::size_t pos = npos) const noexcept;
        std::size_t find_last_not_of(const String& str, std::size_t pos = npos) const noexcept;
        std::size_t find_last_not_of(const char* s, std::size_t pos, std::size_t count) const;
        std::size_t find_last_not_of(const char* s, std::size_t pos = npos) const;
        std::size_t find_last_not_of(char ch, std::size_t pos = npos) const noexcept;

        friend bool operator==(const String& left, const String& right);
        friend bool operator!=(const String& left, const String& right);
        friend bool operator<(const String& left, const String& right);
        friend bool operator<=(const String& left, const String& right);
        friend bool operator>(const String& left, const String& right);
        friend bool operator>=(const String& left, const String& right);
        friend String operator+(const String& left, const String& right);
        friend String operator+(const String& left, String&& right);
        friend String operator+(String&& left, const String& right);
        friend String operator+(String&& left, String&& right);

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        String(const std::u8string& str);
        String(char8_t utfChar);
        String(const char8_t* str);
        String(std::size_t count, char8_t ch);
        String(const std::u8string& str, std::size_t pos);
        String(const std::u8string& str, std::size_t pos, std::size_t count);
        String(const char8_t* str, std::size_t count);
        String(std::initializer_list<char8_t> chars);
        String(std::u8string::const_iterator first, std::u8string::const_iterator last);

        operator std::u8string() const;

        String& assign(std::size_t count, char8_t ch);
        String& assign(const std::u8string& str);
        String& assign(const std::u8string& str, std::size_t pos, std::size_t count = npos);
        String& assign(std::u8string&& str);
        String& assign(const char8_t* str, std::size_t count);
        String& assign(const char8_t* str);
        String& assign(std::initializer_list<char8_t> chars);
        String& assign(std::u8string::const_iterator first, std::u8string::const_iterator last);

        String& insert(std::size_t index, std::size_t count, char8_t ch);
        String& insert(std::size_t index, const std::u8string& str);
        String& insert(std::size_t index, const std::u8string& str, std::size_t pos, std::size_t count = npos);
        String& insert(std::size_t index, const char8_t* str, std::size_t count);
        String& insert(std::size_t index, const char8_t* str);
        iterator insert(const_iterator pos, char8_t ch);
        iterator insert(const_iterator pos, std::size_t count, char8_t ch);
        iterator insert(const_iterator pos, std::initializer_list<char8_t> chars);
        iterator insert(const_iterator pos, std::u8string::const_iterator first, std::u8string::const_iterator last);

        String& append(std::size_t count, char8_t ch);
        String& append(const std::u8string& str);
        String& append(const std::u8string& str, std::size_t pos, std::size_t count = npos);
        String& append(const char8_t* str, std::size_t count);
        String& append(const char8_t* str);
        String& append(std::initializer_list<char8_t> chars);
        String& append(std::u8string::const_iterator first, std::u8string::const_iterator last);

        int compare(const std::u8string& str) const noexcept;
        int compare(std::size_t pos1, std::size_t count1, const std::u8string& str) const;
        int compare(std::size_t pos1, std::size_t count1, const std::u8string& str, std::size_t pos2, std::size_t count2 = npos) const;
        int compare(const char8_t* s) const;
        int compare(std::size_t pos1, std::size_t count1, const char8_t* s) const;
        int compare(std::size_t pos1, std::size_t count1, const char8_t* s, std::size_t count2) const;

        String& replace(std::size_t pos, std::size_t count, const std::u8string& str);
        String& replace(const_iterator first, const_iterator last, const std::u8string& str);
        String& replace(std::size_t pos, std::size_t count, const std::u8string& str, std::size_t pos2, std::size_t count2 = npos);
        String& replace(const_iterator first, const_iterator last, std::u8string::const_iterator first2, std::u8string::const_iterator last2);
        String& replace(std::size_t pos, std::size_t count, const char8_t* cstr, std::size_t count2);
        String& replace(const_iterator first, const_iterator last, const char8_t* cstr, std::size_t count2);
        String& replace(std::size_t pos, std::size_t count, const char8_t* cstr);
        String& replace(const_iterator first, const_iterator last, const char8_t* cstr);
        String& replace(std::size_t pos, std::size_t count, std::size_t count2, char8_t ch);
        String& replace(const_iterator first, const_iterator last, std::size_t count2, char8_t ch);
        String& replace(const_iterator first, const_iterator last, std::initializer_list<char8_t> chars);

        void resize(std::size_t count, char8_t ch);

        std::size_t find(const std::u8string& str, std::size_t pos = 0) const noexcept;
        std::size_t find(const char8_t* s, std::size_t pos, std::size_t count) const;
        std::size_t find(const char8_t* s, std::size_t pos = 0) const;
        std::size_t find(char8_t ch, std::size_t pos = 0) const noexcept;

        std::size_t find_first_of(const std::u8string& str, std::size_t pos = 0) const noexcept;
        std::size_t find_first_of(const char8_t* s, std::size_t pos, std::size_t count) const;
        std::size_t find_first_of(const char8_t* s, std::size_t pos = 0) const;
        std::size_t find_first_of(char8_t ch, std::size_t pos = 0) const noexcept;

        std::size_t find_first_not_of(const std::u8string& str, std::size_t pos = 0) const noexcept;
        std::size_t find_first_not_of(const char8_t* s, std::size_t pos, std::size_t count) const;
        std::size_t find_first_not_of(const char8_t* s, std::size_t pos = 0) const;
        std::size_t find_first_not_of(char8_t ch, std::size_t pos = 0) const noexcept;

        std::size_t rfind(const std::u8string& str, std::size_t pos = npos) const noexcept;
        std::size_t rfind(const char8_t* s, std::size_t pos, std::size_t count) const;
        std::size_t rfind(const char8_t* s, std::size_t pos = npos) const;
        std::size_t rfind(char8_t ch, std::size_t pos = npos) const noexcept;

        std::size_t find_last_of(const std::u8string& str, std::size_t pos = npos) const noexcept;
        std::size_t find_last_of(const char8_t* s, std::size_t pos, std::size_t count) const;
        std::size_t find_last_of(const char8_t* s, std::size_t pos = npos) const;
        std::size_t find_last_of(char8_t ch, std::size_t pos = npos) const noexcept;

        std::size_t find_last_not_of(const std::u8string& str, std::size_t pos = npos) const noexcept;
        std::size_t find_last_not_of(const char8_t* s, std::size_t pos, std::size_t count) const;
        std::size_t find_last_not_of(const char8_t* s, std::size_t pos = npos) const;
        std::size_t find_last_not_of(char8_t ch, std::size_t pos = npos) const noexcept;

        friend std::basic_ostream<char8_t>& operator<<(std::basic_ostream<char8_t>& os, const String& str);
#endif
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    inline bool operator==(const String& left, const String& right)
    {
        return left.m_string == right.m_string;
    }

    inline bool operator!=(const String& left, const String& right)
    {
        return left.m_string != right.m_string;
    }

    inline bool operator<(const String& left, const String& right)
    {
        return left.m_string < right.m_string;
    }

    inline bool operator<=(const String& left, const String& right)
    {
        return left.m_string <= right.m_string;
    }

    inline bool operator>(const String& left, const String& right)
    {
        return left.m_string > right.m_string;
    }

    inline bool operator>=(const String& left, const String& right)
    {
        return left.m_string >= right.m_string;
    }

    inline String operator+(const String& left, const String& right)
    {
        return String(left.m_string + right.m_string);
    }
    inline String operator+(String&& left, String&& right)
    {
        return String(std::move(left.m_string) + std::move(right.m_string));
    }
    inline String operator+(String&& left, const String& right)
    {
        return String(std::move(left.m_string) + right.m_string);
    }
    inline String operator+(const String& left, String&& right)
    {
        return String(left.m_string + std::move(right.m_string));
    }

    TGUI_API std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const String& str);
    TGUI_API std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t>& os, const String& str);


    // UTF-8 function are defined in the header so that they can be enabled/disabled based on
    // the compiler settings without having to recompile TGUI with a different c++ standard.
#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
    inline String::String(const std::u8string& str) :
        m_string(str.begin(), str.end())
    {
    }

    inline String::String(char8_t utfChar)
        : m_string(1, static_cast<char>(utfChar))
    {
    }

    inline String::String(const char8_t* str)
        : String{std::u8string{str}}
    {
    }

    inline String::String(std::size_t count, char8_t ch)
        : m_string(count, static_cast<char>(ch))
    {
    }

    inline String::String(const std::u8string& str, std::size_t pos)
        : String{std::u8string(str, pos)}
    {
    }

    inline String::String(const std::u8string& str, std::size_t pos, std::size_t count)
        : String{std::u8string(str, pos, count)}
    {
    }

    inline String::String(const char8_t* str, std::size_t count)
        : String{std::u8string{str, count}}
    {
    }

    inline String::String(std::initializer_list<char8_t> chars)
        : String(std::u8string(chars.begin(), chars.end()))
    {
    }

    inline String::String(std::u8string::const_iterator first, std::u8string::const_iterator last)
        : String{std::u8string(first, last)}
    {
    }

    inline String::operator std::u8string() const
    {
        return asUtf8();
    }

    inline String& String::assign(std::size_t count, char8_t ch)
    {
        m_string.assign(count, static_cast<char>(ch));
        return *this;
    }

    inline String& String::assign(const std::u8string& str)
    {
        return *this = str;
    }

    inline String& String::assign(const std::u8string& str, std::size_t pos, std::size_t count)
    {
        return *this = {str, pos, count};
    }

    inline String& String::assign(std::u8string&& str)
    {
        return *this = std::move(str);
    }

    inline String& String::assign(const char8_t* str, std::size_t count)
    {
        return *this = {str, count};
    }

    inline String& String::assign(const char8_t* str)
    {
        return *this = str;
    }

    inline String& String::assign(std::initializer_list<char8_t> chars)
    {
        return *this = chars;
    }

    inline String& String::assign(std::u8string::const_iterator first, std::u8string::const_iterator last)
    {
        return *this = {first, last};
    }

    inline String& String::insert(std::size_t index, std::size_t count, char8_t ch)
    {
        m_string.insert(index, count, static_cast<char>(ch));
        return *this;
    }

    inline String& String::insert(std::size_t index, const std::u8string& str)
    {
        m_string.insert(index, String{str}.m_string);
        return *this;
    }

    inline String& String::insert(std::size_t index, const std::u8string& str, std::size_t pos, std::size_t count)
    {
        m_string.insert(index, String{str, pos, count}.m_string);
        return *this;
    }

    inline String& String::insert(std::size_t index, const char8_t* str, std::size_t count)
    {
        m_string.insert(index, String{str, count}.m_string);
        return *this;
    }

    inline String& String::insert(std::size_t index, const char8_t* str)
    {
        m_string.insert(index, String{str}.m_string);
        return *this;
    }

    inline String::iterator String::insert(String::const_iterator pos, char8_t ch)
    {
        return m_string.insert(pos, static_cast<char>(ch));
    }

    inline String::iterator String::insert(String::const_iterator pos, std::size_t count, char8_t ch)
    {
        return m_string.insert(pos, count, static_cast<char>(ch));
    }

    inline String::iterator String::insert(String::const_iterator pos, std::initializer_list<char8_t> chars)
    {
        auto tmpStr = String{chars};
        return m_string.insert(pos, tmpStr.begin(), tmpStr.end());
    }

    inline String::iterator String::insert(String::const_iterator pos, std::u8string::const_iterator first, std::u8string::const_iterator last)
    {
        auto tmpStr = String{first, last};
        return m_string.insert(pos, tmpStr.begin(), tmpStr.end());
    }

    inline String& String::append(std::size_t count, char8_t ch)
    {
        return append(String(count, ch));
    }

    inline String& String::append(const std::u8string& str)
    {
        return append(String{str});
    }

    inline String& String::append(const std::u8string& str, std::size_t pos, std::size_t count)
    {
        return append(String{str, pos, count});
    }

    inline String& String::append(const char8_t* str, std::size_t count)
    {
        return append(String{str, count});
    }

    inline String& String::append(const char8_t* str)
    {
        return append(String{str});
    }

    inline String& String::append(std::initializer_list<char8_t> chars)
    {
        return append(String{chars});
    }

    inline String& String::append(std::u8string::const_iterator first, std::u8string::const_iterator last)
    {
        return append(String{first, last});
    }

    inline int String::compare(const std::u8string& str) const noexcept
    {
        return m_string.compare(String{str}.m_string);
    }

    inline int String::compare(std::size_t pos1, std::size_t count1, const std::u8string& str) const
    {
        return m_string.compare(pos1, count1, String{str}.m_string);
    }

    inline int String::compare(std::size_t pos1, std::size_t count1, const std::u8string& str, std::size_t pos2, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, String{str, pos2, count2}.m_string);
    }

    inline int String::compare(const char8_t* s) const
    {
        return m_string.compare(String{s}.m_string);
    }

    inline int String::compare(std::size_t pos1, std::size_t count1, const char8_t* s) const
    {
        return m_string.compare(pos1, count1, String{s}.m_string);
    }

    inline int String::compare(std::size_t pos1, std::size_t count1, const char8_t* s, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, String{s, count2}.m_string);
    }

    inline String& String::replace(std::size_t pos, std::size_t count, const std::u8string& str)
    {
        m_string.replace(pos, count, String{str}.m_string);
        return *this;
    }

    inline String& String::replace(const_iterator first, const_iterator last, const std::u8string& str)
    {
        m_string.replace(first, last, String{str}.m_string);
        return *this;
    }

    inline String& String::replace(std::size_t pos, std::size_t count, const std::u8string& str, std::size_t pos2, std::size_t count2)
    {
        m_string.replace(pos, count, String{str, pos2, count2}.m_string);
        return *this;
    }

    inline String& String::replace(const_iterator first, const_iterator last, std::u8string::const_iterator first2, std::u8string::const_iterator last2)
    {
        m_string.replace(first, last, String{first2, last2}.m_string);
        return *this;
    }

    inline String& String::replace(std::size_t pos, std::size_t count, const char8_t* cstr, std::size_t count2)
    {
        m_string.replace(pos, count, String{cstr, count2}.m_string);
        return *this;
    }

    inline String& String::replace(const_iterator first, const_iterator last, const char8_t* cstr, std::size_t count2)
    {
        m_string.replace(first, last, String{cstr, count2}.m_string);
        return *this;
    }

    inline String& String::replace(std::size_t pos, std::size_t count, const char8_t* cstr)
    {
        m_string.replace(pos, count, String{cstr}.m_string);
        return *this;
    }

    inline String& String::replace(const_iterator first, const_iterator last, const char8_t* cstr)
    {
        m_string.replace(first, last, String{cstr}.m_string);
        return *this;
    }

    inline String& String::replace(std::size_t pos, std::size_t count, std::size_t count2, char8_t ch)
    {
        m_string.replace(pos, count, String(count2, ch).m_string);
        return *this;
    }

    inline String& String::replace(const_iterator first, const_iterator last, std::size_t count2, char8_t ch)
    {
        m_string.replace(first, last, String(count2, ch).m_string);
        return *this;
    }

    inline String& String::replace(const_iterator first, const_iterator last, std::initializer_list<char8_t> chars)
    {
        m_string.replace(first, last, String{chars}.m_string);
        return *this;
    }

    inline void String::resize(std::size_t count, char8_t ch)
    {
        m_string.resize(count, static_cast<char>(ch));
    }

    inline std::size_t String::find(const std::u8string& str, std::size_t pos) const noexcept
    {
        return m_string.find(String{str}.m_string, pos);
    }

    inline std::size_t String::find(const char8_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find(String{s, count}.m_string, pos);
    }

    inline std::size_t String::find(const char8_t* s, std::size_t pos) const
    {
        return m_string.find(String{s}.m_string, pos);
    }

    inline std::size_t String::find(char8_t ch, std::size_t pos) const noexcept
    {
        return m_string.find(static_cast<char>(ch), pos);
    }

    inline std::size_t String::find_first_of(const std::u8string& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(String{str}.m_string, pos);
    }

    inline std::size_t String::find_first_of(const char8_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_of(String{s, count}.m_string, pos);
    }

    inline std::size_t String::find_first_of(const char8_t* s, std::size_t pos) const
    {
        return m_string.find_first_of(String{s}.m_string, pos);
    }

    inline std::size_t String::find_first_of(char8_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(static_cast<char>(ch), pos);
    }

    inline std::size_t String::find_first_not_of(const std::u8string& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(String{str}.m_string, pos);
    }

    inline std::size_t String::find_first_not_of(const char8_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_not_of(String{s, count}.m_string, pos);
    }

    inline std::size_t String::find_first_not_of(const char8_t* s, std::size_t pos) const
    {
        return m_string.find_first_not_of(String{s}.m_string, pos);
    }

    inline std::size_t String::find_first_not_of(char8_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(static_cast<char>(ch), pos);
    }

    inline std::size_t String::rfind(const std::u8string& str, std::size_t pos) const noexcept
    {
        return m_string.rfind(String{str}.m_string, pos);
    }

    inline std::size_t String::rfind(const char8_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.rfind(String{s, count}.m_string, pos);
    }

    inline std::size_t String::rfind(const char8_t* s, std::size_t pos) const
    {
        return m_string.rfind(String{s}.m_string, pos);
    }

    inline std::size_t String::rfind(char8_t ch, std::size_t pos) const noexcept
    {
        return m_string.rfind(static_cast<char>(ch), pos);
    }

    inline std::size_t String::find_last_of(const std::u8string& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(String{str}.m_string, pos);
    }

    inline std::size_t String::find_last_of(const char8_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_of(String{s, count}.m_string, pos);
    }

    inline std::size_t String::find_last_of(const char8_t* s, std::size_t pos) const
    {
        return m_string.find_last_of(String{s}.m_string, pos);
    }

    inline std::size_t String::find_last_of(char8_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(static_cast<char>(ch), pos);
    }

    inline std::size_t String::find_last_not_of(const std::u8string& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(String{str}.m_string, pos);
    }

    inline std::size_t String::find_last_not_of(const char8_t* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_not_of(String{s, count}.m_string, pos);
    }

    inline std::size_t String::find_last_not_of(const char8_t* s, std::size_t pos) const
    {
        return m_string.find_last_not_of(String{s}.m_string, pos);
    }

    inline std::size_t String::find_last_not_of(char8_t ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(static_cast<char8_t>(ch), pos);
    }

    inline std::basic_ostream<char8_t>& operator<<(std::basic_ostream<char8_t>& os, const String& str)
    {
        os << std::u8string(str);
        return os;
    }
#endif

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_STRING_HPP
