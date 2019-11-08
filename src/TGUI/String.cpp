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


#include <TGUI/String.hpp>
#include <TGUI/Utf.hpp>

#include <cctype> // tolower, toupper, isspace

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    const decltype(std::string::npos) String::npos = std::string::npos;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool isWhitespace(char character)
    {
        if (character == ' ' || character == '\t' || character == '\r' || character == '\n')
            return true;
        else
            return false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool isWhitespace(char32_t character)
    {
        if (character >= 128)
            return false;
        else
            return isWhitespace(static_cast<char>(character));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int String::toInt(int defaultValue) const
    {
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
        int value;
        const char* cstr = m_string.c_str();
        if (std::from_chars(&cstr[0], &cstr[m_string.length()], value).ec == std::errc{})
            return value;
        else
            return defaultValue;
#else
        try
        {
            return std::stoi(m_string);
        }
        catch (const std::exception&)
        {
            return defaultValue;
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    unsigned int String::toUInt(unsigned int defaultValue) const
    {
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
        unsigned int value;
        const char* cstr = m_string.c_str();
        if (std::from_chars(&cstr[0], &cstr[m_string.length()], value).ec == std::errc{})
            return value;
        else
            return defaultValue;
#else
        try
        {
            return static_cast<unsigned int>(std::stoi(m_string));
        }
        catch (const std::exception&)
        {
            return defaultValue;
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float String::toFloat(float defaultValue) const
    {
#if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
        float value;
        const char* cstr = m_string.c_str();
        if (std::from_chars(&cstr[0], &cstr[m_string.length()], value).ec == std::errc{})
            return value;
        else
            return defaultValue;
#else
        try
        {
            return std::stof(m_string);
        }
        catch (const std::exception&)
        {
            return defaultValue;
        }
#endif
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String String::trim() const
    {
        const auto firstIt = std::find_if(m_string.begin(), m_string.end(), [](char c) { return !std::isspace(static_cast<unsigned char>(c)); });
        if (firstIt == m_string.end())
            return {};

        const auto lastIt = std::find_if(m_string.rbegin(), m_string.rend(), [](char c) { return !std::isspace(static_cast<unsigned char>(c)); }).base();
        return {firstIt, lastIt};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String String::toLower() const
    {
        String str = *this;
        for (char& c : str.m_string)
        {
            if (static_cast<unsigned char>(c) < 128)
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }

        return str;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String String::toUpper() const
    {
        String str = *this;
        for (char& c : str.m_string)
        {
            if (static_cast<unsigned char>(c) < 128)
                c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }

        return str;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String& String::replace(const String& searchFor, const String& replaceWith)
    {
        std::size_t step = replaceWith.length();
        std::size_t len = searchFor.length();
        std::size_t pos = find(searchFor);

        // Replace each occurrence of search
        while (pos != npos)
        {
            replace(pos, len, replaceWith);
            pos = find(searchFor, pos + step);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::String(const std::wstring& str)
    {
        m_string.reserve(str.length()+1); // Minimum size needed
        utf::convertWidetoUtf8(str, m_string);
    }

    String::String(const std::u16string& str)
    {
        m_string.reserve(str.length()+1); // Minimum size needed
        utf::convertUtf16toUtf8(str, m_string);
    }

    String::String(const std::u32string& str)
    {
        m_string.reserve(str.length()+1); // Minimum size needed
        utf::convertUtf32toUtf8(str, m_string);
    }

    String::String(char ansiChar)
        : m_string(1, ansiChar)
    {
    }

    String::String(wchar_t wideChar) :
        String(static_cast<char32_t>(wideChar))
    {
    }

    String::String(char16_t wideChar) :
        String(static_cast<char32_t>(wideChar))
    {
    }

    String::String(char32_t wideChar)
    {
        utf::encodeCharUtf8(wideChar, m_string);
    }

    String::String(const wchar_t* str)
        : String{std::wstring(str)}
    {
    }

    String::String(const char16_t* str)
        : String{std::u16string(str)}
    {
    }

    String::String(const char32_t* str)
        : String{std::u32string(str)}
    {
    }

    String::String(std::size_t count, char ansiChar)
        : m_string(count, ansiChar)
    {
    }

    String::String(const std::string& str, std::size_t pos)
        : String{std::string(str, pos)}
    {
    }

    String::String(const std::string& str, std::size_t pos, std::size_t count)
        : String{std::string(str, pos, count)}
    {
    }

    String::String(const char* str, std::size_t count)
        : String{std::string{str, count}}
    {
    }

    String::String(std::initializer_list<char> chars)
        : String(std::string(chars.begin(), chars.end()))
    {
    }

    String::String(std::initializer_list<wchar_t> chars)
        : String(std::wstring(chars.begin(), chars.end()))
    {
    }

    String::String(std::initializer_list<char16_t> chars)
        : String(std::u16string(chars.begin(), chars.end()))
    {
    }

    String::String(std::initializer_list<char32_t> chars)
        : String(std::u32string(chars.begin(), chars.end()))
    {
    }

    String::String(std::string::const_iterator first, std::string::const_iterator last)
        : String{std::string(first, last)}
    {
    }

    String::String(std::wstring::const_iterator first, std::wstring::const_iterator last)
        : String{std::wstring(first, last)}
    {
    }

    String::String(std::u16string::const_iterator first, std::u16string::const_iterator last)
        : String{std::u16string(first, last)}
    {
    }

    String::String(std::u32string::const_iterator first, std::u32string::const_iterator last)
        : String{std::u32string(first, last)}
    {
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::String(const sf::String& str)
    {
        const std::basic_string<sf::Uint8>& strUtf8 = str.toUtf8();
        m_string.assign(strUtf8.begin(), strUtf8.end());
    }

    String::operator sf::String() const
    {
        return sf::String::fromUtf8(m_string.begin(), m_string.end());
    }

    String::operator std::wstring() const
    {
        return toWideString();
    }

    String::operator std::u16string() const
    {
        return toUtf16();
    }

    String::operator std::u32string() const
    {
        return toUtf32();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::wstring String::toWideString() const
    {
        std::wstring output;
        output.reserve(m_string.length() + 1); // Can be larger than required
        sf::Utf8::toWide(m_string.begin(), m_string.end(), std::back_inserter(output));
        return output;
    }

    std::u16string String::toUtf16() const
    {
        std::u16string output;
        output.reserve(m_string.length() + 1); // Can be larger than required
        sf::Utf8::toUtf16(m_string.begin(), m_string.end(), std::back_inserter(output));
        return output;
    }

    std::u32string String::toUtf32() const
    {
        std::u32string output;
        output.reserve(m_string.length() + 1); // Can be larger than required
        sf::Utf8::toUtf32(m_string.begin(), m_string.end(), std::back_inserter(output));
        return output;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String& String::assign(std::size_t count, char ch)
    {
        m_string.assign(count, ch);
        return *this;
    }

    String& String::assign(const std::string& str)
    {
        return *this = str;
    }

    String& String::assign(const String& str)
    {
        m_string.assign(str.m_string);
        return *this;
    }

    String& String::assign(const std::string& str, std::size_t pos, std::size_t count)
    {
        return *this = {str, pos, count};
    }

    String& String::assign(const String& str, std::size_t pos, std::size_t count)
    {
        m_string.assign(str.m_string, pos, count);
        return *this;
    }

    String& String::assign(std::string&& str)
    {
        return *this = std::move(str);
    }

    String& String::assign(String&& str)
    {
        m_string.assign(std::move(str.m_string));
        return *this;
    }

    String& String::assign(const char* str, std::size_t count)
    {
        return *this = {str, count};
    }

    String& String::assign(const char* str)
    {
        return *this = str;
    }

    String& String::assign(std::initializer_list<char> chars)
    {
        return *this = chars;
    }

    String& String::assign(std::string::const_iterator first, std::string::const_iterator last)
    {
        return *this = {first, last};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::reference String::at(std::size_t pos)
    {
        return m_string.at(pos);
    }

    String::const_reference String::at(std::size_t pos) const
    {
        return m_string.at(pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::const_reference String::operator [](std::size_t index) const
    {
        return m_string[index];
    }

    String::reference String::operator [](std::size_t index)
    {
        return m_string[index];
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::reference String::front()
    {
        return m_string.front();
    }

    String::const_reference String::front() const
    {
        return m_string.front();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::reference String::back()
    {
        return m_string.back();
    }

    String::const_reference String::back() const
    {
        return m_string.back();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const char* String::data() const noexcept
    {
        return m_string.data();
    }

    const char* String::c_str() const noexcept
    {
        return m_string.c_str();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::iterator String::begin() noexcept
    {
        return m_string.begin();
    }

    String::const_iterator String::begin() const noexcept
    {
        return m_string.begin();
    }

    String::const_iterator String::cbegin() const noexcept
    {
        return m_string.cbegin();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::iterator String::end() noexcept
    {
        return m_string.end();
    }

    String::const_iterator String::end() const noexcept
    {
        return m_string.end();
    }

    String::const_iterator String::cend() const noexcept
    {
        return m_string.cend();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::reverse_iterator String::rbegin() noexcept
    {
        return m_string.rbegin();
    }

    String::const_reverse_iterator String::rbegin() const noexcept
    {
        return m_string.rbegin();
    }

    String::const_reverse_iterator String::crbegin() const noexcept
    {
        return m_string.crbegin();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String::reverse_iterator String::rend() noexcept
    {
        return m_string.rend();
    }

    String::const_reverse_iterator String::rend() const noexcept
    {
        return m_string.rend();
    }

    String::const_reverse_iterator String::crend() const noexcept
    {
        return m_string.crend();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::clear() noexcept
    {
        m_string.clear();
    }

    bool String::empty() const noexcept
    {
        return m_string.empty();
    }

    std::size_t String::size() const noexcept
    {
        return m_string.size();
    }

    std::size_t String::length() const noexcept
    {
        return m_string.length();
    }

    std::size_t String::max_size() const noexcept
    {
        return m_string.max_size();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::reserve(std::size_t newCap)
    {
        m_string.reserve(newCap);
    }

    std::size_t String::capacity() const noexcept
    {
        return m_string.capacity();
    }

    void String::shrink_to_fit()
    {
        m_string.shrink_to_fit();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String& String::insert(std::size_t index, std::size_t count, char ch)
    {
        m_string.insert(index, count, ch);
        return *this;
    }

    String& String::insert(std::size_t index, const std::string& str)
    {
        m_string.insert(index, str);
        return *this;
    }

    String& String::insert(std::size_t index, const String& str)
    {
        m_string.insert(index, str.m_string);
        return *this;
    }

    String& String::insert(std::size_t index, const std::string& str, std::size_t pos, std::size_t count)
    {
        m_string.insert(index, str, pos, count);
        return *this;
    }

    String& String::insert(std::size_t index, const String& str, std::size_t pos, std::size_t count)
    {
        m_string.insert(index, str.m_string, pos, count);
        return *this;
    }

    String& String::insert(std::size_t index, const char* str, std::size_t count)
    {
        m_string.insert(index, str, count);
        return *this;
    }

    String& String::insert(std::size_t index, const char* str)
    {
        m_string.insert(index, str);
        return *this;
    }

    String::iterator String::insert(const_iterator pos, char ch)
    {
        return m_string.insert(pos, ch);
    }

    String::iterator String::insert(const_iterator pos, std::size_t count, char ch)
    {
        return m_string.insert(pos, count, ch);
    }

    String::iterator String::insert(const_iterator pos, std::initializer_list<char> chars)
    {
        // This function requires GCC 9.1, older libstdc++ versions had an insert function with iterator instead of const_iterator
        //return m_string.insert(pos, chars);

        const auto tmpStr = String{chars};
        return m_string.insert(pos, tmpStr.begin(), tmpStr.end());
    }

    String::iterator String::insert(const_iterator pos, std::string::const_iterator first, std::string::const_iterator last)
    {
        return m_string.insert(pos, first, last);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String& String::erase(std::size_t index, std::size_t count)
    {
        m_string.erase(index, count);
        return *this;
    }

    String::iterator String::erase(const_iterator position)
    {
        return m_string.erase(position);
    }

    String::iterator String::erase(const_iterator first, const_iterator last)
    {
        return m_string.erase(first, last);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::push_back(char ch)
    {
        m_string.push_back(ch);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::pop_back()
    {
        m_string.pop_back();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String& String::append(std::size_t count, char ch)
    {
        m_string.append(count, ch);
        return *this;
    }

    String& String::append(const std::string& str)
    {
        return append(String{str});
    }

    String& String::append(const String& str)
    {
        m_string.append(str.m_string);
        return *this;
    }

    String& String::append(const std::string& str, std::size_t pos, std::size_t count)
    {
        return append(String{str, pos, count});
    }

    String& String::append(const String& str, std::size_t pos, std::size_t count)
    {
        m_string.append(str.m_string, pos, count);
        return *this;
    }

    String& String::append(const char* str, std::size_t count)
    {
        return append(String{str, count});
    }

    String& String::append(const char* str)
    {
        return append(String{str});
    }

    String& String::append(std::initializer_list<char> chars)
    {
        return append(String{chars});
    }

    String& String::append(std::string::const_iterator first, std::string::const_iterator last)
    {
        return append(String{first, last});
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String& String::operator+=(const String& str)
    {
        m_string += str.m_string;
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int String::compare(const std::string& str) const noexcept
    {
        return m_string.compare(str);
    }

    int String::compare(const String& str) const noexcept
    {
        return m_string.compare(str.m_string);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const std::string& str) const
    {
        return m_string.compare(pos1, count1, str);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const String& str) const
    {
        return m_string.compare(pos1, count1, str.m_string);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const std::string& str, std::size_t pos2, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, str, pos2, count2);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const String& str, std::size_t pos2, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, str.m_string, pos2, count2);
    }

    int String::compare(const char* s) const
    {
        return m_string.compare(s);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const char* s) const
    {
        return m_string.compare(pos1, count1, s);
    }

    int String::compare(std::size_t pos1, std::size_t count1, const char* s, std::size_t count2) const
    {
        return m_string.compare(pos1, count1, s, count2);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String& String::replace(std::size_t pos, std::size_t count, const std::string& str)
    {
        m_string.replace(pos, count, str);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const String& str)
    {
        m_string.replace(pos, count, str.m_string);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const std::string& str)
    {
        m_string.replace(first, last, str);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const String& str)
    {
        m_string.replace(first, last, str.m_string);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const std::string& str, std::size_t pos2, std::size_t count2)
    {
        m_string.replace(pos, count, str, pos2, count2);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const String& str, std::size_t pos2, std::size_t count2)
    {
        m_string.replace(pos, count, str.m_string, pos2, count2);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::string::const_iterator first2, std::string::const_iterator last2)
    {
        m_string.replace(first, last, first2, last2);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const char* cstr, std::size_t count2)
    {
        m_string.replace(pos, count, cstr, count2);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const char* cstr, std::size_t count2)
    {
        m_string.replace(first, last, cstr, count2);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, const char* cstr)
    {
        m_string.replace(pos, count, cstr);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, const char* cstr)
    {
        m_string.replace(first, last, cstr);
        return *this;
    }

    String& String::replace(std::size_t pos, std::size_t count, std::size_t count2, char ch)
    {
        m_string.replace(pos, count, count2, ch);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::size_t count2, char ch)
    {
        m_string.replace(first, last, count2, ch);
        return *this;
    }

    String& String::replace(const_iterator first, const_iterator last, std::initializer_list<char> chars)
    {
        m_string.replace(first, last, chars);
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    String String::substr(std::size_t pos, std::size_t count) const
    {
        return {m_string.substr(pos, count)};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::copy(char* dest, std::size_t count, std::size_t pos) const
    {
        return m_string.copy(dest, count, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::resize(std::size_t count)
    {
        m_string.resize(count);
    }

    void String::resize(std::size_t count, char ch)
    {
        m_string.resize(count, ch);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::swap(String& other)
    {
        m_string.swap(other.m_string);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::find(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.find(str, pos);
    }

    std::size_t String::find(const String& str, std::size_t pos) const noexcept
    {
        return m_string.find(str.m_string, pos);
    }

    std::size_t String::find(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find(s, pos, count);
    }

    std::size_t String::find(const char* s, std::size_t pos) const
    {
        return m_string.find(s, pos);
    }

    std::size_t String::find(char ch, std::size_t pos) const noexcept
    {
        return m_string.find(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::find_first_of(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(str, pos);
    }

    std::size_t String::find_first_of(const String& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(str.m_string, pos);
    }

    std::size_t String::find_first_of(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_of(s, pos, count);
    }

    std::size_t String::find_first_of(const char* s, std::size_t pos) const
    {
        return m_string.find_first_of(s, pos);
    }

    std::size_t String::find_first_of(char ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_of(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::find_first_not_of(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(str, pos);
    }

    std::size_t String::find_first_not_of(const String& str, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(str.m_string, pos);
    }

    std::size_t String::find_first_not_of(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_first_not_of(s, pos, count);
    }

    std::size_t String::find_first_not_of(const char* s, std::size_t pos) const
    {
        return m_string.find_first_not_of(s, pos);
    }

    std::size_t String::find_first_not_of(char ch, std::size_t pos) const noexcept
    {
        return m_string.find_first_not_of(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::rfind(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.rfind(str, pos);
    }

    std::size_t String::rfind(const String& str, std::size_t pos) const noexcept
    {
        return m_string.rfind(str.m_string, pos);
    }

    std::size_t String::rfind(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.rfind(s, pos, count);
    }

    std::size_t String::rfind(const char* s, std::size_t pos) const
    {
        return m_string.rfind(s, pos);
    }

    std::size_t String::rfind(char ch, std::size_t pos) const noexcept
    {
        return m_string.rfind(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::find_last_of(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(str, pos);
    }

    std::size_t String::find_last_of(const String& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(str.m_string, pos);
    }

    std::size_t String::find_last_of(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_of(s, pos, count);
    }

    std::size_t String::find_last_of(const char* s, std::size_t pos) const
    {
        return m_string.find_last_of(s, pos);
    }

    std::size_t String::find_last_of(char ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_of(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::size_t String::find_last_not_of(const std::string& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(str, pos);
    }

    std::size_t String::find_last_not_of(const String& str, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(str.m_string, pos);
    }

    std::size_t String::find_last_not_of(const char* s, std::size_t pos, std::size_t count) const
    {
        return m_string.find_last_not_of(s, pos, count);
    }

    std::size_t String::find_last_not_of(const char* s, std::size_t pos) const
    {
        return m_string.find_last_not_of(s, pos);
    }

    std::size_t String::find_last_not_of(char ch, std::size_t pos) const noexcept
    {
        return m_string.find_last_not_of(ch, pos);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const String& str)
    {
        os << std::string(str);
        return os;
    }

    std::basic_ostream<wchar_t>& operator<<(std::basic_ostream<wchar_t>& os, const String& str)
    {
        os << std::wstring(str);
        return os;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
