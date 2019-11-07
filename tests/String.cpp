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

#include "Tests.hpp"
#include <TGUI/String.hpp>

TEST_CASE("[String]")
{
    tgui::String str;

    std::string s("abcde");
    std::wstring ws(L"\u03b1\u03b2\u03b3\u03b4\u03b5");
    std::u16string u16s(u"\u03b1\u03b2\u03b3\u03b4\u03b5");
    std::u32string u32s(U"\u03b1\u03b2\u03b3\u03b4\u03b5");

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
    std::u8string u8s(u8"\u03b1\u03b2\u03b3\u03b4\u03b5");
#endif

    SECTION("Constructor")
    {
        REQUIRE(tgui::String().empty());

        REQUIRE(tgui::String(s) == "abcde");
        REQUIRE(tgui::String(std::string("xyz")) == "xyz");
        REQUIRE(tgui::String(std::wstring(L"\U00010348")) == L"\U00010348");
        REQUIRE(tgui::String(std::u16string(u"\U00010348")) == u"\U00010348");
        REQUIRE(tgui::String(std::u32string(U"\U00010348")) == U"\U00010348");

        REQUIRE(tgui::String('x') == 'x');
        REQUIRE(tgui::String(L'\x20AC') == L'\x20AC');
        REQUIRE(tgui::String(u'\x20AC') == u'\x20AC');
        REQUIRE(tgui::String(U'\x10348') == U'\x10348');

        REQUIRE(tgui::String("xyz") == "xyz");
        REQUIRE(tgui::String(L"\U00010348") == L"\U00010348");
        REQUIRE(tgui::String(u"\U00010348") == u"\U00010348");
        REQUIRE(tgui::String(U"\U00010348") == U"\U00010348");

        REQUIRE(tgui::String(3, 'x') == "xxx");
        REQUIRE(tgui::String(std::string("abcde"), 3) == "de");
        REQUIRE(tgui::String(std::string("abcde"), 1, 3) == "bcd");
        REQUIRE(tgui::String("abcde", 3) == "abc");

        REQUIRE(tgui::String({'a', 'b', 'c'}) == "abc");
        REQUIRE(tgui::String({L'\x03b1', L'\x03b2', L'\x03b3'}) == L"\u03b1\u03b2\u03b3");
        REQUIRE(tgui::String({u'\x03b1', u'\x03b2', u'\x03b3'}) == u"\u03b1\u03b2\u03b3");
        REQUIRE(tgui::String({U'\x03b1', U'\x03b2', U'\x03b3'}) == U"\u03b1\u03b2\u03b3");

        REQUIRE(tgui::String(s.begin(), s.end()) == "abcde");
        REQUIRE(tgui::String(ws.begin(), ws.end()) == L"\u03b1\u03b2\u03b3\u03b4\u03b5");
        REQUIRE(tgui::String(u16s.begin(), u16s.end()) == u"\u03b1\u03b2\u03b3\u03b4\u03b5");
        REQUIRE(tgui::String(u32s.begin(), u32s.end()) == U"\u03b1\u03b2\u03b3\u03b4\u03b5");

        REQUIRE(tgui::String(sf::String("xyz")) == "xyz");

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        REQUIRE(tgui::String(u8"\U00010348") == u8"\U00010348");
        REQUIRE(tgui::String(std::u8string(u8"\U00010348")) == u8"\U00010348");
        REQUIRE(tgui::String(u8"\u03b1\u03b2\u03b3\u03b4\u03b5", 6) == u8"\u03b1\u03b2\u03b3");
        REQUIRE(tgui::String(std::u8string(u8"\u03b1\u03b2\u03b3\u03b4\u03b5"), 6) == u8"\u03b4\u03b5");
        REQUIRE(tgui::String(std::u8string(u8"\u03b1\u03b2\u03b3\u03b4\u03b5"), 2, 6) == u8"\u03b2\u03b3\u03b4");
#endif
    }

    SECTION("Conversions")
    {
        REQUIRE(sf::String(tgui::String(L"\u03b1\u03b2\u03b3\u03b4\u03b5")) == sf::String::fromUtf32(u32s.begin(), u32s.end()));

        REQUIRE(std::string(tgui::String("xyz")) == "xyz");
        REQUIRE(std::wstring(tgui::String(U"\u20AC")) == L"\u20AC");
        REQUIRE(std::u16string(tgui::String(U"\U00010348")) == u"\U00010348");
        REQUIRE(std::u32string(tgui::String(U"\U00010348")) == U"\U00010348");

        REQUIRE(tgui::String("xyz").toAnsiString() == "xyz");
        REQUIRE(tgui::String(U"\u20AC").toWideString() == L"\u20AC");
        REQUIRE(tgui::String(U"\U00010348").toUtf16() == u"\U00010348");
        REQUIRE(tgui::String(U"\U00010348").toUtf32() == U"\U00010348");

        // Will work for older and newer compilers as it will either use std::string or std::u8string
        REQUIRE(tgui::String(u8"\U00010348").toUtf8() == u8"\U00010348");

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        REQUIRE(std::u8string(tgui::String(U"\U00010348")) == u8"\U00010348");
#endif
    }

    SECTION("assign")
    {
        tgui::String str2 = "abc";
        REQUIRE(str.assign(str2) == "abc");
        REQUIRE(str.assign(3, 'x') == "xxx");
        REQUIRE(str.assign(std::string("xyz")) == "xyz");
        REQUIRE(str.assign(std::string("abcde"), 3) == "de");
        REQUIRE(str.assign(std::string("abcde"), 1, 3) == "bcd");
        REQUIRE(str.assign(tgui::String("abcde"), 2, 2) == "cd");
        REQUIRE(str.assign(tgui::String("xyz")) == "xyz");
        REQUIRE(str.assign("abcde", 3) == "abc");
        REQUIRE(str.assign("xyz") == "xyz");
        REQUIRE(str.assign({'a', 'b', 'c'}) == "abc");
        REQUIRE(str.assign(s.begin(), s.end()) == "abcde");

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        REQUIRE(str.assign(u8"\U00010348") == u8"\U00010348");
        REQUIRE(str.assign(u8"\u03b1\u03b2\u03b3\u03b4\u03b5", 6) == u8"\u03b1\u03b2\u03b3");
        REQUIRE(str.assign(std::u8string(u8"\U00010348")) == u8"\U00010348");
        REQUIRE(str.assign(std::u8string(u8"\u03b1\u03b2\u03b3\u03b4\u03b5"), 6) == u8"\u03b4\u03b5");
        REQUIRE(str.assign(std::u8string(u8"\u03b1\u03b2\u03b3\u03b4\u03b5"), 2, 6) == u8"\u03b2\u03b3\u03b4");
#endif
    }

    SECTION("Accessing characters")
    {
        tgui::String str1 = "abc";
        const tgui::String str2(u8"\u03b1\u03b2\u03b3", 6);

        SECTION("at")
        {
            REQUIRE(str1.at(0) == 'a');
            REQUIRE(str2.at(0) == '\xce');
            REQUIRE(str2.at(1) == '\xb1');
            REQUIRE(str2.toUtf32().at(0) == U'\x03b1');

            str1.at(0) = U'd';
            REQUIRE(str1.at(0) == U'd');
        }

        SECTION("operator[]")
        {
            REQUIRE(str1[1] == 'b');
            REQUIRE(str2[2] == '\xce');
            REQUIRE(str2[3] == '\xb2');
            REQUIRE(str2.toUtf32()[1] == U'\x03b2');

            str1[1] = 'e';
            REQUIRE(str1[1] == 'e');
        }

        SECTION("front")
        {
            REQUIRE(str1.front() == 'a');
            REQUIRE(str2.front() == '\xce');
            REQUIRE(str2.toUtf32().front() == U'\x03b1');

            str1.front() = 'd';
            REQUIRE(str1.front() == 'd');
        }

        SECTION("back")
        {
            REQUIRE(str1.back() == 'c');
            REQUIRE(str2.back() == '\xb3');
            REQUIRE(str2.toUtf32().back() == U'\x03b3');

            str1.back() = 'f';
            REQUIRE(str1.back() == 'f');
        }

        SECTION("data")
        {
            REQUIRE(str1.data()[1] == 'b');
            REQUIRE(str2.data()[2] == '\xce');
            REQUIRE(str2.data()[3] == '\xb2');
            REQUIRE(str2.toUtf32().data()[1] == U'\x03b2');

#if __cplusplus >= 201703L
            str1.data()[1] = 'e';
            REQUIRE(str1.data()[1] == 'e');
#endif
        }

        SECTION("c_str")
        {
            REQUIRE(str1.c_str()[1] == 'b');
            REQUIRE(str2.c_str()[2] == '\xce');
            REQUIRE(str2.c_str()[3] == '\xb2');
            REQUIRE(str2.toUtf32().c_str()[1] == U'\x03b2');
        }

        SECTION("begin / end")
        {
            REQUIRE(*str1.begin() == 'a');
            REQUIRE(*(str2.begin() + 4) == '\xce');
            REQUIRE(*(str2.begin() + 5) == '\xb3');
            REQUIRE(*(str2.toUtf32().begin() + 2) == U'\x03b3');

            *(str1.begin() + 1) = 'e';
            REQUIRE(*(str1.begin() + 1) == 'e');

            REQUIRE(str1.begin() + 3 == str1.end());
            REQUIRE(str2.begin() + 6 == str2.end());
        }

        SECTION("cbegin / cend")
        {
            REQUIRE(*str1.cbegin() == 'a');
            REQUIRE(*(str2.cbegin() + 4) == '\xce');
            REQUIRE(*(str2.cbegin() + 5) == '\xb3');
            REQUIRE(*(str2.toUtf32().cbegin() + 2) == U'\x03b3');

            REQUIRE(str1.cbegin() + 3 == str1.cend());
            REQUIRE(str2.cbegin() + 6 == str2.cend());
        }

        SECTION("rbegin / rend")
        {
            REQUIRE(*str1.rbegin() == 'c');
            REQUIRE(*(str2.rbegin() + 4) == '\xb1');
            REQUIRE(*(str2.rbegin() + 5) == '\xce');
            REQUIRE(*(str2.toUtf32().rbegin() + 2) == U'\x03b1');

            *(str1.rbegin() + 1) = 'e';
            REQUIRE(*(str1.rbegin() + 1) == 'e');

            REQUIRE(str1.rbegin() + 3 == str1.rend());
            REQUIRE(str2.rbegin() + 6 == str2.rend());
        }

        SECTION("crbegin / crend")
        {
            REQUIRE(*str1.crbegin() == 'c');
            REQUIRE(*(str2.crbegin() + 4) == '\xb1');
            REQUIRE(*(str2.crbegin() + 5) == '\xce');
            REQUIRE(*(str2.toUtf32().crbegin() + 2) == U'\x03b1');

            REQUIRE(str1.crbegin() + 3 == str1.crend());
            REQUIRE(str2.crbegin() + 6 == str2.crend());
        }

        SECTION("substr")
        {
            REQUIRE(str1.substr(1, 1) == "b");
            REQUIRE(str2.substr(2, 2) == "\xce\xb2");
            REQUIRE(str2.substr(2, 2).toUtf32() == U"\u03b2");
        }
    }

    SECTION("Size")
    {
        REQUIRE(tgui::String().max_size() <= tgui::String::npos);

        REQUIRE(str.empty());

        str = "abc";
        REQUIRE(!str.empty());
        REQUIRE(str.size() == 3);
        REQUIRE(str.length() == 3);

        str = u8"\u03b1\u03b2\u03b3";
        REQUIRE(!str.empty());
        REQUIRE(str.size() == 6);
        REQUIRE(str.length() == 6);

        str.shrink_to_fit();
        str.reserve(200);
        REQUIRE(str.capacity() >= 200);

        str.clear();
        REQUIRE(str.empty());
    }

    SECTION("insert")
    {
        str = "^$"; REQUIRE(str.insert(1, 3, 'x') == "^xxx$");
        str = "^$"; REQUIRE(str.insert(1, std::string("xyz")) == "^xyz$");
        str = "^$"; REQUIRE(str.insert(1, tgui::String("xyz")) == "^xyz$");
        str = "^$"; REQUIRE(str.insert(1, std::string("abcde"), 3) == "^de$");
        str = "^$"; REQUIRE(str.insert(1, std::string("abcde"), 1, 3) == "^bcd$");
        str = "^$"; REQUIRE(str.insert(1, tgui::String("abcde"), 2, 2) == "^cd$");
        str = "^$"; REQUIRE(str.insert(1, "abcde", 3) == "^abc$");
        str = "^$"; REQUIRE(str.insert(1, "xyz") == "^xyz$");
        str = "^$"; str.insert(str.begin() + 1, 'x'); REQUIRE(str == "^x$");
        str = "^$"; str.insert(str.begin() + 1, 3, 'x'); REQUIRE(str == "^xxx$");
        str = "^$"; str.insert(str.begin() + 1, {'a', 'b', 'c'}); REQUIRE(str == "^abc$");
        str = "^$"; str.insert(str.begin() + 1, s.begin(), s.end()); REQUIRE(str == "^abcde$");

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        str = "^$"; REQUIRE(str.insert(1, u8"\U00010348") == u8"^\U00010348$");
        str = "^$"; REQUIRE(str.insert(1, u8"\u03b1\u03b2\u03b3\u03b4\u03b5", 6) == u8"^\u03b1\u03b2\u03b3$");
        str = "^$"; REQUIRE(str.insert(1, std::u8string(u8"\U00010348")) == u8"^\U00010348$");
        str = "^$"; REQUIRE(str.insert(1, std::u8string(u8"\u03b1\u03b2\u03b3\u03b4\u03b5"), 6) == u8"^\u03b4\u03b5$");
        str = "^$"; REQUIRE(str.insert(1, std::u8string(u8"\u03b1\u03b2\u03b3\u03b4\u03b5"), 2, 6) == u8"^\u03b2\u03b3\u03b4$");
        str = "^$"; REQUIRE(str.insert(1, 3, u8'\x13') == u8"^\u0013\u0013\u0013$");
        str = "^$"; str.insert(str.begin() + 1, 3, u8'\x13'); REQUIRE(str == u8"^\u0013\u0013\u0013$");
        str = "^$"; str.insert(str.begin() + 1, u8'\x13'); REQUIRE(str == u8"^\u0013$");
        str = "^$"; str.insert(str.begin() + 1, {u8'\x41', u8'\x42', u8'\x43'}); REQUIRE(str == u8"^\u0041\u0042\u0043$");
        str = "^$"; str.insert(str.begin() + 1, u8s.begin(), u8s.end()); REQUIRE(str == u8"^\u03b1\u03b2\u03b3\u03b4\u03b5$");
#endif
    }

    SECTION("erase")
    {
        str = "ABCDEFGHIJK";
        REQUIRE(str.erase(2, 3) == "ABFGHIJK");

        const auto it = str.erase(str.begin() + 3);
        REQUIRE(str == "ABFHIJK");

        str.erase(it, it + 2);
        REQUIRE(str == "ABFJK");
    }

    SECTION("push_back / pop_back")
    {
        str.push_back('_');
        REQUIRE(str == "_");
        str.push_back('2');
        REQUIRE(str == "_2");
        str.pop_back();
        REQUIRE(str == "_");
    }

    SECTION("append")
    {
        str = "@"; REQUIRE(str.append("xyz") == "@xyz");
        str = "@"; REQUIRE(str.append("abcde", 3) == "@abc");
        str = "@"; REQUIRE(str.append(std::string("xyz")) == "@xyz");
        str = "@"; REQUIRE(str.append(std::string("abcde"), 3) == "@de");
        str = "@"; REQUIRE(str.append(std::string("abcde"), 1, 3) == "@bcd");
        str = "@"; REQUIRE(str.append(3, 'x') == "@xxx");
        str = "@"; REQUIRE(str.append({'a', 'b', 'c'}) == "@abc");
        str = "@"; REQUIRE(str.append(s.begin(), s.end()) == "@abcde");
        str = "@"; REQUIRE(str.append(tgui::String("xyz")) == "@xyz");
        str = "@"; REQUIRE(str.append(tgui::String("abcde"), 2, 2) == "@cd");

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        str = "@"; REQUIRE(str.append(u8"\U00010348") == u8"@\U00010348");
        str = "@"; REQUIRE(str.append(u8"\u03b1\u03b2\u03b3\u03b4\u03b5", 6) == u8"@\u03b1\u03b2\u03b3");
        str = "@"; REQUIRE(str.append(std::u8string(u8"\U00010348")) == u8"@\U00010348");
        str = "@"; REQUIRE(str.append(std::u8string(u8"\u03b1\u03b2\u03b3\u03b4\u03b5"), 6) == u8"@\u03b4\u03b5");
        str = "@"; REQUIRE(str.append(std::u8string(u8"\u03b1\u03b2\u03b3\u03b4\u03b5"), 2, 6) == u8"@\u03b2\u03b3\u03b4");
        str = "@"; REQUIRE(str.append(3, u8'\x13') == u8"@\u0013\u0013\u0013");
        str = "@"; REQUIRE(str.append({u8'\x41', u8'\x42', u8'\x43'}) == u8"@\u0041\u0042\u0043");
        str = "@"; REQUIRE(str.append(u8s.begin(), u8s.end()) == L"@\u03b1\u03b2\u03b3\u03b4\u03b5");
#endif
    }

    SECTION("operator+=")
    {
        str = "@"; REQUIRE((str += "xyz") == "@xyz");
        str = "@"; REQUIRE((str += L"\U00010348") == L"@\U00010348");
        str = "@"; REQUIRE((str += u"\U00010348") == u"@\U00010348");
        str = "@"; REQUIRE((str += U"\U00010348") == U"@\U00010348");

        str = "@"; REQUIRE((str += std::string("xyz")) == "@xyz");
        str = "@"; REQUIRE((str += std::wstring(L"\U00010348")) == L"@\U00010348");
        str = "@"; REQUIRE((str += std::u16string(u"\U00010348")) == u"@\U00010348");
        str = "@"; REQUIRE((str += std::u32string(U"\U00010348")) == U"@\U00010348");

        str = "@"; REQUIRE((str += 'x') == "@x");
        str = "@"; REQUIRE((str += L'\x20AC') == L"@\u20AC");
        str = "@"; REQUIRE((str += u'\x20AC') == u"@\u20AC");
        str = "@"; REQUIRE((str += U'\x10348') == U"@\U00010348");

        str = "@"; REQUIRE((str += {'a', 'b', 'c'}) == "@abc");
        str = "@"; REQUIRE((str += {L'\x03b1', L'\x03b2', L'\x03b3'}) == L"@\u03b1\u03b2\u03b3");
        str = "@"; REQUIRE((str += {u'\x03b1', u'\x03b2', u'\x03b3'}) == u"@\u03b1\u03b2\u03b3");
        str = "@"; REQUIRE((str += {U'\x03b1', U'\x03b2', U'\x03b3'}) == U"@\u03b1\u03b2\u03b3");

        str = "@"; REQUIRE((str += tgui::String("xyz")) == "@xyz");

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        str = "@"; REQUIRE((str += u8"\U00010348") == u8"@\U00010348");
        str = "@"; REQUIRE((str += std::u8string(u8"\U00010348")) == u8"@\U00010348");
        str = "@"; REQUIRE((str += u'\x13') == u"@\u0013");
        str = "@"; REQUIRE((str += {u8'\x41', u8'\x42', u8'\x43'}) == u8"@\u0041\u0042\u0043");
#endif
    }

    SECTION("compare")
    {
        str = U"\u03b1\u03b2\u03b3";

        REQUIRE(str.compare("xyz") > 0);
        REQUIRE(str.compare(L"\u03b1\u03b2\u03b3") == 0);
        REQUIRE(str.compare(u"\u03b1\u03b2") > 0);
        REQUIRE(str.compare(U"\u03b1\u03b2\u03b3\u03b4") < 0);

        REQUIRE(str.compare(1, 2, "yz") > 0);
        REQUIRE(str.compare(2, 4, L"\u03b2\u03b3") == 0);
        REQUIRE(str.compare(2, 4, u"\u03b2") > 0);
        REQUIRE(str.compare(2, 4, U"\u03b2\u03b3\u03b4") < 0);

        REQUIRE(str.compare(0, 2, "xyz", 2) > 0);

        REQUIRE(str.compare(std::string("xyz")) > 0);
        REQUIRE(str.compare(std::wstring(L"\u03b1\u03b2\u03b3")) == 0);
        REQUIRE(str.compare(std::u16string(u"\u03b1\u03b2")) > 0);
        REQUIRE(str.compare(std::u32string(U"\u03b1\u03b2\u03b3\u03b4")) < 0);

        REQUIRE(str.compare(1, 2, std::string("yz")) > 0);
        REQUIRE(str.compare(2, 4, std::wstring(L"\u03b2\u03b3")) == 0);
        REQUIRE(str.compare(2, 4, std::u16string(u"\u03b2")) > 0);
        REQUIRE(str.compare(2, 4, std::u32string(U"\u03b2\u03b3\u03b4")) < 0);

        REQUIRE(str.compare(0, 2, std::string("yz"), 1, 2) > 0);
        REQUIRE(str.compare(0, 4, std::wstring(L"\u03b4\u03b1\u03b2\u03b3"), 2, 4) == 0);
        REQUIRE(str.compare(0, 4, std::u16string(u"\u03b4\u03b1\u03b2\u03b3"), 2, 2) > 0);
        REQUIRE(str.compare(0, 4, std::u32string(U"\u03b4\u03b1\u03b2\u03b3"), 2, 6) < 0);

        REQUIRE(str.compare(tgui::String(U"\u03b1\u03b2\u03b3\u03b4")) < 0);
        REQUIRE(str.compare(2, 4, tgui::String(U"\u03b2\u03b3\u03b4")) < 0);
        REQUIRE(str.compare(0, 4, tgui::String(U"\u03b4\u03b1\u03b2\u03b3"), 2, 6) < 0);

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        REQUIRE(str.compare(u8"\u03b1\u03b2\u03b3") == 0);
        REQUIRE(str.compare(2, 4, u8"\u03b2\u03b3") == 0);
        REQUIRE(str.compare(0, 4, u8"\u03b1\u03b2\u03b3", 4) == 0);
        REQUIRE(str.compare(std::u8string(u8"\u03b1\u03b2\u03b3")) == 0);
        REQUIRE(str.compare(2, 4, std::u8string(u8"\u03b2\u03b3")) == 0);
        REQUIRE(str.compare(0, 4, std::u8string(u8"\u03b4\u03b1\u03b2\u03b3"), 2, 4) == 0);
#endif
    }

    SECTION("replace")
    {
        str = "^ab$"; REQUIRE(str.replace(1, 2, std::string("abc")) == "^abc$");
        str = "^ab$"; REQUIRE(str.replace(1, 2, tgui::String(U"\u03b1\u03b2\u03b3")) == U"^\u03b1\u03b2\u03b3$");
        str = "^ab$"; REQUIRE(str.replace(str.begin() + 1, str.begin() + 3, std::string("abc")) == U"^abc$");
        str = "^ab$"; REQUIRE(str.replace(str.begin() + 1, str.begin() + 3, tgui::String(U"\u03b1\u03b2\u03b3")) == U"^\u03b1\u03b2\u03b3$");
        str = "^ab$"; REQUIRE(str.replace(1, 2, std::string("abcde"), 1, 3) == U"^bcd$");
        str = "^ab$"; REQUIRE(str.replace(1, 2, tgui::String(U"\u03b1\u03b2\u03b3\u03b4\u03b5"), 2, 6) == U"^\u03b2\u03b3\u03b4$");
        str = "^ab$"; REQUIRE(str.replace(str.begin() + 1, str.begin() + 3, s.begin() + 1, s.begin() + 4) == U"^bcd$");
        str = "^ab$"; REQUIRE(str.replace(1, 2, "abcde", 3) == U"^abc$");
        str = "^ab$"; REQUIRE(str.replace(str.begin() + 1, str.begin() + 3, "abcde", 3) == U"^abc$");
        str = "^ab$"; REQUIRE(str.replace(1, 2, "abc") == U"^abc$");
        str = "^ab$"; REQUIRE(str.replace(str.begin() + 1, str.begin() + 3, "abc") == U"^abc$");
        str = "^ab$"; REQUIRE(str.replace(1, 2, 3, 'b') == U"^bbb$");
        str = "^ab$"; REQUIRE(str.replace(str.begin() + 1, str.begin() + 3, 3, 'b') == U"^bbb$");
        str = "^ab$"; REQUIRE(str.replace(str.begin() + 1, str.begin() + 3, {'a', 'b', 'c'}) == U"^abc$");

        str = "^ab:abc:abc:bc$"; REQUIRE(str.replace("abc", "xyz") == "^ab:xyz:xyz:bc$");

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        str = "^ab$"; REQUIRE(str.replace(1, 2, u8"\u03b1\u03b2\u03b3") == U"^\u03b1\u03b2\u03b3$");
        str = "^ab$"; REQUIRE(str.replace(1, 2, u8"\u03b1\u03b2\u03b3\u03b4\u03b5", 6) == U"^\u03b1\u03b2\u03b3$");
        str = "^ab$"; REQUIRE(str.replace(str.begin() + 1, str.begin() + 3, u8"\u03b1\u03b2\u03b3") == U"^\u03b1\u03b2\u03b3$");
        str = "^ab$"; REQUIRE(str.replace(str.begin() + 1, str.begin() + 3, u8"\u03b1\u03b2\u03b3\u03b4\u03b5", 6) == U"^\u03b1\u03b2\u03b3$");
        str = "^ab$"; REQUIRE(str.replace(1, 2, std::u8string(u8"\u03b1\u03b2\u03b3")) == U"^\u03b1\u03b2\u03b3$");
        str = "^ab$"; REQUIRE(str.replace(1, 2, std::u8string(u8"\u03b1\u03b2\u03b3\u03b4\u03b5"), 2, 6) == U"^\u03b2\u03b3\u03b4$");
        str = "^ab$"; REQUIRE(str.replace(str.begin() + 1, str.begin() + 3, std::u8string(u8"\u03b1\u03b2\u03b3")) == U"^\u03b1\u03b2\u03b3$");
#endif
    }

    SECTION("copy")
    {
        char chars[7];
        chars[6] = '$';
        str = U"\u03b1\u03b2\u03b3\u03b4\u03b5";
        REQUIRE(str.copy(chars, 6, 2) == 6);
        REQUIRE(std::string(chars, 7) == "\xce\xb2\xce\xb3\xce\xb4$");
    }

    SECTION("resize")
    {
        str = "@"; str.resize(3); REQUIRE(str == std::string("@\x00\x00", 3));
        str = "@"; str.resize(3, '_'); REQUIRE(str == "@__");
    }

    SECTION("swap")
    {
        tgui::String str1 = "abc";
        tgui::String str2 = U"\u03b1\u03b2\u03b3\u03b4\u03b5";
        str1.swap(str2);
        REQUIRE(str1 == U"\u03b1\u03b2\u03b3\u03b4\u03b5");
        REQUIRE(str2 == "abc");
    }

    SECTION("find")
    {
        str = U"abc\u03b4\u03b5\u03b6\u03b7";

        REQUIRE(str.find("bc") == 1);
        REQUIRE(str.find("bcd", 1, 2) == 1);
        REQUIRE(str.find(std::string("bc")) == 1);
        REQUIRE(str.find(tgui::String(U"c\u03b4")) == 2);
        REQUIRE(str.find('c') == 2);

        REQUIRE(str.find_first_of("bc") == 1);
        REQUIRE(str.find_first_of("bcd", 1, 2) == 1);
        REQUIRE(str.find_first_of(std::string("bc")) == 1);
        REQUIRE(str.find_first_of(tgui::String(U"c\u03b4")) == 2);
        REQUIRE(str.find_first_of('c') == 2);

        REQUIRE(str.find_first_not_of("bc") == 0);
        REQUIRE(str.find_first_not_of("bcd", 1, 2) == 3);
        REQUIRE(str.find_first_not_of(std::string("bc")) == 0);
        REQUIRE(str.find_first_not_of(tgui::String(U"c\u03b4")) == 0);
        REQUIRE(str.find_first_not_of('c') == 0);

        REQUIRE(str.find_last_of("bc") == 2);
        REQUIRE(str.find_last_of("bcd", 5, 2) == 2);
        REQUIRE(str.find_last_of(std::string("bc")) == 2);
        REQUIRE(str.find_last_of(tgui::String("ac\xb5")) == 6);
        REQUIRE(str.find_last_of('c') == 2);

        REQUIRE(str.find_last_not_of("bc") == 10);
        REQUIRE(str.find_last_not_of("bcd", 5, 2) == 5);
        REQUIRE(str.find_last_not_of(std::string("bc")) == 10);
        REQUIRE(str.find_last_not_of(tgui::String("ac\xb5")) == 10);
        REQUIRE(str.find_last_not_of('c') == 10);

        REQUIRE(str.rfind("bc") == 1);
        REQUIRE(str.rfind("bcd", 5, 2) == 1);
        REQUIRE(str.rfind(std::string("bc")) == 1);
        REQUIRE(str.rfind(tgui::String(U"c\u03b4")) == 2);
        REQUIRE(str.rfind('c') == 2);

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        REQUIRE(str.find(u8"c\u03b4") == 2);
        REQUIRE(str.find(u8"c\u03b4\u03b5", 1, 3) == 2);
        REQUIRE(str.find(std::u8string(u8"c\u03b4")) == 2);
        REQUIRE(str.find(u8'b') == 1);
        REQUIRE(str.find_first_of(u8"c\u03b4") == 2);
        REQUIRE(str.find_first_of(u8"c\u03b4\u03b5", 1, 3) == 2);
        REQUIRE(str.find_first_of(std::u8string(u8"c\u03b4")) == 2);
        REQUIRE(str.find_first_of(u8'b') == 1);
        REQUIRE(str.find_first_not_of(u8"c\u03b4") == 0);
        REQUIRE(str.find_first_not_of(u8"c\u03b4\u03b5", 1, 3) == 1);
        REQUIRE(str.find_first_not_of(std::u8string(u8"c\u03b4")) == 0);
        REQUIRE(str.find_first_not_of(u8'b') == 0);
        REQUIRE(str.find_last_of(u8"c\u03b4") == 9); // \xce appears in both \u03b4 and \u03b7
        REQUIRE(str.find_last_of(u8"c\u03b5\u03b6", 7, 5) == 7);
        REQUIRE(str.find_last_of(std::u8string(u8"c\u03b4")) == 9); // \xce appears in both \u03b4 and \u03b7
        REQUIRE(str.find_last_of(u8'b') == 1);
        REQUIRE(str.find_last_not_of(u8"c\u03b4") == 10);
        REQUIRE(str.find_last_not_of(u8"c\u03b4\u03b5", 7, 5) == 1);
        REQUIRE(str.find_last_not_of(std::u8string(u8"c\u03b4")) == 10);
        REQUIRE(str.find_last_not_of(u8'b') == 10);
        REQUIRE(str.rfind(u8"c\u03b4") == 2);
        REQUIRE(str.rfind(u8"c\u03b4\u03b5", 5, 3) == 2);
        REQUIRE(str.rfind(std::u8string(u8"c\u03b4")) == 2);
        REQUIRE(str.rfind(u8'b') == 1);
#endif
    }

    SECTION("Comparison operators")
    {
        SECTION("ASCII strings")
        {
            tgui::String str1 = "abc";
            tgui::String str2 = "xyz";

            SECTION("True")
            {
                REQUIRE(str1 == str1);
                REQUIRE(str1 == "abc");
                REQUIRE("abc" == str1);
                REQUIRE(str1 == std::string("abc"));
                REQUIRE(std::string("abc") == str1);

                REQUIRE(str1 != str2);
                REQUIRE(str1 != "xyz");
                REQUIRE("xyz" != str1);
                REQUIRE(str1 != std::string("xyz"));
                REQUIRE(std::string("xyz") != str1);

                REQUIRE(str1 < str2);
                REQUIRE(str1 < "xyz");
                REQUIRE("abc" < str2);
                REQUIRE(str1 < std::string("xyz"));
                REQUIRE(std::string("abc") < str2);

                REQUIRE(str1 <= str2);
                REQUIRE(str1 <= "xyz");
                REQUIRE("abc" <= str2);
                REQUIRE(str1 <= std::string("xyz"));
                REQUIRE(std::string("abc") <= str2);

                REQUIRE(str2 > str1);
                REQUIRE(str2 > "abc");
                REQUIRE("xyz" > str1);
                REQUIRE(str2 > std::string("abc"));
                REQUIRE(std::string("xyz") > str1);

                REQUIRE(str2 >= str1);
                REQUIRE(str2 >= "abc");
                REQUIRE("xyz" >= str1);
                REQUIRE(str2 >= std::string("abc"));
                REQUIRE(std::string("xyz") >= str1);
            }

            SECTION("False")
            {
                REQUIRE(!(str1 == str2));
                REQUIRE(!(str1 == "xyz"));
                REQUIRE(!("xyz" == str1));
                REQUIRE(!(str1 == std::string("xyz")));
                REQUIRE(!(std::string("xyz") == str1));

                REQUIRE(!(str1 != str1));
                REQUIRE(!(str1 != "abc"));
                REQUIRE(!("abc" != str1));
                REQUIRE(!(str1 != std::string("abc")));
                REQUIRE(!(std::string("abc") != str1));

                REQUIRE(!(str2 < str1));
                REQUIRE(!(str2 < "abc"));
                REQUIRE(!("xyz" < str1));
                REQUIRE(!(str2 < std::string("abc")));
                REQUIRE(!(std::string("xyz") < str1));

                REQUIRE(!(str2 <= str1));
                REQUIRE(!(str2 <= "abc"));
                REQUIRE(!("xyz" <= str1));
                REQUIRE(!(str2 <= std::string("abc")));
                REQUIRE(!(std::string("xyz") <= str1));

                REQUIRE(!(str1 > str2));
                REQUIRE(!(str1 > "xyz"));
                REQUIRE(!("abc" > str2));
                REQUIRE(!(str1 > std::string("xyz")));
                REQUIRE(!(std::string("abc") > str2));

                REQUIRE(!(str1 >= str2));
                REQUIRE(!(str1 >= "xyz"));
                REQUIRE(!("abc" >= str2));
                REQUIRE(!(str1 >= std::string("xyz")));
                REQUIRE(!(std::string("abc") >= str2));
            }
        }

        SECTION("Unicode strings")
        {
            tgui::String str1 = U"\u03b1\u03b2";
            tgui::String str2 = U"\u03b3\u03b4";

            SECTION("True")
            {
                REQUIRE(str1 == str1);
                REQUIRE(str1 == L"\u03b1\u03b2");
                REQUIRE(str1 == u"\u03b1\u03b2");
                REQUIRE(str1 == U"\u03b1\u03b2");
                REQUIRE(L"\u03b1\u03b2" == str1);
                REQUIRE(u"\u03b1\u03b2" == str1);
                REQUIRE(U"\u03b1\u03b2" == str1);
                REQUIRE(str1 == std::wstring(L"\u03b1\u03b2"));
                REQUIRE(str1 == std::u16string(u"\u03b1\u03b2"));
                REQUIRE(str1 == std::u32string(U"\u03b1\u03b2"));
                REQUIRE(std::wstring(L"\u03b1\u03b2") == str1);
                REQUIRE(std::u16string(u"\u03b1\u03b2") == str1);
                REQUIRE(std::u32string(U"\u03b1\u03b2") == str1);

                REQUIRE(str1 != str2);
                REQUIRE(str1 != L"\u03b3\u03b4");
                REQUIRE(str1 != u"\u03b3\u03b4");
                REQUIRE(str1 != U"\u03b3\u03b4");
                REQUIRE(L"\u03b3\u03b4" != str1);
                REQUIRE(u"\u03b3\u03b4" != str1);
                REQUIRE(U"\u03b3\u03b4" != str1);
                REQUIRE(str1 != std::wstring(L"\u03b3\u03b4"));
                REQUIRE(str1 != std::u16string(u"\u03b3\u03b4"));
                REQUIRE(str1 != std::u32string(U"\u03b3\u03b4"));
                REQUIRE(std::wstring(L"\u03b3\u03b4") != str1);
                REQUIRE(std::u16string(u"\u03b3\u03b4") != str1);
                REQUIRE(std::u32string(U"\u03b3\u03b4") != str1);

                REQUIRE(str1 < str2);
                REQUIRE(str1 < L"\u03b3\u03b4");
                REQUIRE(str1 < u"\u03b3\u03b4");
                REQUIRE(str1 < U"\u03b3\u03b4");
                REQUIRE(L"\u03b1\u03b2" < str2);
                REQUIRE(u"\u03b1\u03b2" < str2);
                REQUIRE(U"\u03b1\u03b2" < str2);
                REQUIRE(str1 < std::wstring(L"\u03b3\u03b4"));
                REQUIRE(str1 < std::u16string(u"\u03b3\u03b4"));
                REQUIRE(str1 < std::u32string(U"\u03b3\u03b4"));
                REQUIRE(std::wstring(L"\u03b1\u03b2") < str2);
                REQUIRE(std::u16string(u"\u03b1\u03b2") < str2);
                REQUIRE(std::u32string(U"\u03b1\u03b2") < str2);

                REQUIRE(str1 <= str2);
                REQUIRE(str1 <= L"\u03b3\u03b4");
                REQUIRE(str1 <= u"\u03b3\u03b4");
                REQUIRE(str1 <= U"\u03b3\u03b4");
                REQUIRE(L"\u03b1\u03b2" <= str2);
                REQUIRE(u"\u03b1\u03b2" <= str2);
                REQUIRE(U"\u03b1\u03b2" <= str2);
                REQUIRE(str1 <= std::wstring(L"\u03b3\u03b4"));
                REQUIRE(str1 <= std::u16string(u"\u03b3\u03b4"));
                REQUIRE(str1 <= std::u32string(U"\u03b3\u03b4"));
                REQUIRE(std::wstring(L"\u03b1\u03b2") <= str2);
                REQUIRE(std::u16string(u"\u03b1\u03b2") <= str2);
                REQUIRE(std::u32string(U"\u03b1\u03b2") <= str2);

                REQUIRE(str2 > str1);
                REQUIRE(str2 > L"\u03b1\u03b2");
                REQUIRE(str2 > u"\u03b1\u03b2");
                REQUIRE(str2 > U"\u03b1\u03b2");
                REQUIRE(L"\u03b3\u03b4" > str1);
                REQUIRE(u"\u03b3\u03b4" > str1);
                REQUIRE(U"\u03b3\u03b4" > str1);
                REQUIRE(str2 > std::wstring(L"\u03b1\u03b2"));
                REQUIRE(str2 > std::u16string(u"\u03b1\u03b2"));
                REQUIRE(str2 > std::u32string(U"\u03b1\u03b2"));
                REQUIRE(std::wstring(L"\u03b3\u03b4") > str1);
                REQUIRE(std::u16string(u"\u03b3\u03b4") > str1);
                REQUIRE(std::u32string(U"\u03b3\u03b4") > str1);

                REQUIRE(str2 >= str1);
                REQUIRE(str2 >= L"\u03b1\u03b2");
                REQUIRE(str2 >= u"\u03b1\u03b2");
                REQUIRE(str2 >= U"\u03b1\u03b2");
                REQUIRE(L"\u03b3\u03b4" >= str1);
                REQUIRE(u"\u03b3\u03b4" >= str1);
                REQUIRE(U"\u03b3\u03b4" >= str1);
                REQUIRE(str2 >= std::wstring(L"\u03b1\u03b2"));
                REQUIRE(str2 >= std::u16string(u"\u03b1\u03b2"));
                REQUIRE(str2 >= std::u32string(U"\u03b1\u03b2"));
                REQUIRE(std::wstring(L"\u03b3\u03b4") >= str1);
                REQUIRE(std::u16string(u"\u03b3\u03b4") >= str1);
                REQUIRE(std::u32string(U"\u03b3\u03b4") >= str1);

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
                REQUIRE(str1 == u8"\u03b1\u03b2");
                REQUIRE(u8"\u03b1\u03b2" == str1);
                REQUIRE(str1 == std::u8string(u8"\u03b1\u03b2"));
                REQUIRE(std::u8string(u8"\u03b1\u03b2") == str1);
                REQUIRE(str1 != u8"\u03b3\u03b4");
                REQUIRE(u8"\u03b3\u03b4" != str1);
                REQUIRE(str1 != std::u8string(u8"\u03b3\u03b4"));
                REQUIRE(std::u8string(u8"\u03b3\u03b4") != str1);
                REQUIRE(str1 < u8"\u03b3\u03b4");
                REQUIRE(u8"\u03b1\u03b2" < str2);
                REQUIRE(str1 < std::u8string(u8"\u03b3\u03b4"));
                REQUIRE(std::u8string(u8"\u03b1\u03b2") < str2);
                REQUIRE(str1 <= u8"\u03b3\u03b4");
                REQUIRE(u8"\u03b1\u03b2" <= str2);
                REQUIRE(str1 <= std::u8string(u8"\u03b3\u03b4"));
                REQUIRE(std::u8string(u8"\u03b1\u03b2") <= str2);
                REQUIRE(str2 > u8"\u03b1\u03b2");
                REQUIRE(u8"\u03b3\u03b4" > str1);
                REQUIRE(str2 > std::u8string(u8"\u03b1\u03b2"));
                REQUIRE(std::u8string(u8"\u03b3\u03b4") > str1);
                REQUIRE(str2 >= u8"\u03b1\u03b2");
                REQUIRE(u8"\u03b3\u03b4" >= str1);
                REQUIRE(str2 >= std::u8string(u8"\u03b1\u03b2"));
                REQUIRE(std::u8string(u8"\u03b3\u03b4") >= str1);
#endif
            }

            SECTION("False")
            {
                REQUIRE(!(str1 == str2));
                REQUIRE(!(str1 == L"\u03b3\u03b4"));
                REQUIRE(!(str1 == u"\u03b3\u03b4"));
                REQUIRE(!(str1 == U"\u03b3\u03b4"));
                REQUIRE(!(L"\u03b3\u03b4" == str1));
                REQUIRE(!(u"\u03b3\u03b4" == str1));
                REQUIRE(!(U"\u03b3\u03b4" == str1));
                REQUIRE(!(str1 == std::wstring(L"\u03b3\u03b4")));
                REQUIRE(!(str1 == std::u16string(u"\u03b3\u03b4")));
                REQUIRE(!(str1 == std::u32string(U"\u03b3\u03b4")));
                REQUIRE(!(std::wstring(L"\u03b3\u03b4") == str1));
                REQUIRE(!(std::u16string(u"\u03b3\u03b4") == str1));
                REQUIRE(!(std::u32string(U"\u03b3\u03b4") == str1));

                REQUIRE(!(str1 != str1));
                REQUIRE(!(str1 != L"\u03b1\u03b2"));
                REQUIRE(!(str1 != u"\u03b1\u03b2"));
                REQUIRE(!(str1 != U"\u03b1\u03b2"));
                REQUIRE(!(L"\u03b1\u03b2" != str1));
                REQUIRE(!(u"\u03b1\u03b2" != str1));
                REQUIRE(!(U"\u03b1\u03b2" != str1));
                REQUIRE(!(str1 != std::wstring(L"\u03b1\u03b2")));
                REQUIRE(!(str1 != std::u16string(u"\u03b1\u03b2")));
                REQUIRE(!(str1 != std::u32string(U"\u03b1\u03b2")));
                REQUIRE(!(std::wstring(L"\u03b1\u03b2") != str1));
                REQUIRE(!(std::u16string(u"\u03b1\u03b2") != str1));
                REQUIRE(!(std::u32string(U"\u03b1\u03b2") != str1));

                REQUIRE(!(str2 < str1));
                REQUIRE(!(str2 < L"\u03b1\u03b2"));
                REQUIRE(!(str2 < u"\u03b1\u03b2"));
                REQUIRE(!(str2 < U"\u03b1\u03b2"));
                REQUIRE(!(L"\u03b3\u03b4" < str1));
                REQUIRE(!(u"\u03b3\u03b4" < str1));
                REQUIRE(!(U"\u03b3\u03b4" < str1));
                REQUIRE(!(str2 < std::wstring(L"\u03b1\u03b2")));
                REQUIRE(!(str2 < std::u16string(u"\u03b1\u03b2")));
                REQUIRE(!(str2 < std::u32string(U"\u03b1\u03b2")));
                REQUIRE(!(std::wstring(L"\u03b3\u03b4") < str1));
                REQUIRE(!(std::u16string(u"\u03b3\u03b4") < str1));
                REQUIRE(!(std::u32string(U"\u03b3\u03b4") < str1));

                REQUIRE(!(str2 <= str1));
                REQUIRE(!(str2 <= L"\u03b1\u03b2"));
                REQUIRE(!(str2 <= u"\u03b1\u03b2"));
                REQUIRE(!(str2 <= U"\u03b1\u03b2"));
                REQUIRE(!(L"\u03b3\u03b4" <= str1));
                REQUIRE(!(u"\u03b3\u03b4" <= str1));
                REQUIRE(!(U"\u03b3\u03b4" <= str1));
                REQUIRE(!(str2 <= std::wstring(L"\u03b1\u03b2")));
                REQUIRE(!(str2 <= std::u16string(u"\u03b1\u03b2")));
                REQUIRE(!(str2 <= std::u32string(U"\u03b1\u03b2")));
                REQUIRE(!(std::wstring(L"\u03b3\u03b4") <= str1));
                REQUIRE(!(std::u16string(u"\u03b3\u03b4") <= str1));
                REQUIRE(!(std::u32string(U"\u03b3\u03b4") <= str1));

                REQUIRE(!(str1 > str2));
                REQUIRE(!(str1 > L"\u03b3\u03b4"));
                REQUIRE(!(str1 > u"\u03b3\u03b4"));
                REQUIRE(!(str1 > U"\u03b3\u03b4"));
                REQUIRE(!(L"\u03b1\u03b2" > str2));
                REQUIRE(!(u"\u03b1\u03b2" > str2));
                REQUIRE(!(U"\u03b1\u03b2" > str2));
                REQUIRE(!(str1 > std::wstring(L"\u03b3\u03b4")));
                REQUIRE(!(str1 > std::u16string(u"\u03b3\u03b4")));
                REQUIRE(!(str1 > std::u32string(U"\u03b3\u03b4")));
                REQUIRE(!(std::wstring(L"\u03b1\u03b2") > str2));
                REQUIRE(!(std::u16string(u"\u03b1\u03b2") > str2));
                REQUIRE(!(std::u32string(U"\u03b1\u03b2") > str2));

                REQUIRE(!(str1 >= str2));
                REQUIRE(!(str1 >= L"\u03b3\u03b4"));
                REQUIRE(!(str1 >= u"\u03b3\u03b4"));
                REQUIRE(!(str1 >= U"\u03b3\u03b4"));
                REQUIRE(!(L"\u03b1\u03b2" >= str2));
                REQUIRE(!(u"\u03b1\u03b2" >= str2));
                REQUIRE(!(U"\u03b1\u03b2" >= str2));
                REQUIRE(!(str1 >= std::wstring(L"\u03b3\u03b4")));
                REQUIRE(!(str1 >= std::u16string(u"\u03b3\u03b4")));
                REQUIRE(!(str1 >= std::u32string(U"\u03b3\u03b4")));
                REQUIRE(!(std::wstring(L"\u03b1\u03b2") >= str2));
                REQUIRE(!(std::u16string(u"\u03b1\u03b2") >= str2));
                REQUIRE(!(std::u32string(U"\u03b1\u03b2") >= str2));

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
                REQUIRE(!(str1 == u8"\u03b3\u03b4"));
                REQUIRE(!(u8"\u03b3\u03b4" == str1));
                REQUIRE(!(str1 == std::u8string(u8"\u03b3\u03b4")));
                REQUIRE(!(std::u8string(u8"\u03b3\u03b4") == str1));
                REQUIRE(!(str1 != u8"\u03b1\u03b2"));
                REQUIRE(!(u8"\u03b1\u03b2" != str1));
                REQUIRE(!(str1 != std::u8string(u8"\u03b1\u03b2")));
                REQUIRE(!(std::u8string(u8"\u03b1\u03b2") != str1));
                REQUIRE(!(str2 < u8"\u03b1\u03b2"));
                REQUIRE(!(u8"\u03b3\u03b4" < str1));
                REQUIRE(!(str2 < std::u8string(u8"\u03b1\u03b2")));
                REQUIRE(!(std::u8string(u8"\u03b3\u03b4") < str1));
                REQUIRE(!(str2 <= u8"\u03b1\u03b2"));
                REQUIRE(!(u8"\u03b3\u03b4" <= str1));
                REQUIRE(!(str2 <= std::u8string(u8"\u03b1\u03b2")));
                REQUIRE(!(std::u8string(u8"\u03b3\u03b4") <= str1));
                REQUIRE(!(str1 > u8"\u03b3\u03b4"));
                REQUIRE(!(u8"\u03b1\u03b2" > str2));
                REQUIRE(!(str1 > std::u8string(u8"\u03b3\u03b4")));
                REQUIRE(!(std::u8string(u8"\u03b1\u03b2") > str2));
                REQUIRE(!(str1 >= u8"\u03b3\u03b4"));
                REQUIRE(!(u8"\u03b1\u03b2" >= str2));
                REQUIRE(!(str1 >= std::u8string(u8"\u03b3\u03b4")));
                REQUIRE(!(std::u8string(u8"\u03b1\u03b2") >= str2));
#endif
            }
        }
    }

    SECTION("operator+")
    {
        tgui::String str2 = U"\u03b4";

        str = "@"; REQUIRE(str + "xyz" == "@xyz");
        str = "@"; REQUIRE(str + L"\U00010348" == L"@\U00010348");
        str = "@"; REQUIRE(str + u"\U00010348" == u"@\U00010348");
        str = "@"; REQUIRE(str + U"\U00010348" == U"@\U00010348");

        str = "@"; REQUIRE("xyz" + str == "xyz@");
        str = "@"; REQUIRE(L"\U00010348" + str == L"\U00010348@");
        str = "@"; REQUIRE(u"\U00010348" + str == u"\U00010348@");
        str = "@"; REQUIRE(U"\U00010348" + str == U"\U00010348@");

        str = "@"; REQUIRE(str + std::string("xyz") == "@xyz");
        str = "@"; REQUIRE(str + std::wstring(L"\U00010348") == L"@\U00010348");
        str = "@"; REQUIRE(str + std::u16string(u"\U00010348") == u"@\U00010348");
        str = "@"; REQUIRE(str + std::u32string(U"\U00010348") == U"@\U00010348");

        str = "@"; REQUIRE(std::string("xyz") + str == "xyz@");
        str = "@"; REQUIRE(std::wstring(L"\U00010348") + str == L"\U00010348@");
        str = "@"; REQUIRE(std::u16string(u"\U00010348") + str == u"\U00010348@");
        str = "@"; REQUIRE(std::u32string(U"\U00010348") + str == U"\U00010348@");

        str = "@"; REQUIRE(str + 'x' == "@x");
        str = "@"; REQUIRE(str + L'\x20AC' == L"@\u20AC");
        str = "@"; REQUIRE(str + u'\x20AC' == u"@\u20AC");
        str = "@"; REQUIRE(str + U'\x10348' == U"@\U00010348");

        str = "@"; REQUIRE('x' + str == "x@");
        str = "@"; REQUIRE(L'\x20AC' + str == L"\u20AC@");
        str = "@"; REQUIRE(u'\x20AC' + str == u"\u20AC@");
        str = "@"; REQUIRE(U'\x10348' + str == U"\U00010348@");

        str = "@"; REQUIRE(str + str2 == U"@\u03b4");
        str = "@"; REQUIRE(str2 + str == U"\u03b4@");
        str = "@"; REQUIRE(str + tgui::String(U"\U00010348") == U"@\U00010348");
        str = "@"; REQUIRE(tgui::String(U"\U00010348") + str == U"\U00010348@");
        str = "@"; REQUIRE(tgui::String(U"\U00010348") + tgui::String(U"\u03b4") == U"\U00010348\u03b4");

        REQUIRE(tgui::String("@") + "xyz" == "@xyz");
        REQUIRE(tgui::String("@") + L"\U00010348" == L"@\U00010348");
        REQUIRE(tgui::String("@") + u"\U00010348" == u"@\U00010348");
        REQUIRE(tgui::String("@") + U"\U00010348" == U"@\U00010348");

        REQUIRE("xyz" + tgui::String("@") == "xyz@");
        REQUIRE(L"\U00010348" + tgui::String("@") == L"\U00010348@");
        REQUIRE(u"\U00010348" + tgui::String("@") == u"\U00010348@");
        REQUIRE(U"\U00010348" + tgui::String("@") == U"\U00010348@");

        REQUIRE(tgui::String("@") + s == "@abcde");
        REQUIRE(tgui::String("@") + ws == L"@\u03b1\u03b2\u03b3\u03b4\u03b5");
        REQUIRE(tgui::String("@") + u16s == u"@\u03b1\u03b2\u03b3\u03b4\u03b5");
        REQUIRE(tgui::String("@") + u32s == U"@\u03b1\u03b2\u03b3\u03b4\u03b5");

        REQUIRE(s + tgui::String("@") == "abcde@");
        REQUIRE(ws + tgui::String("@") == L"\u03b1\u03b2\u03b3\u03b4\u03b5@");
        REQUIRE(u16s + tgui::String("@") == u"\u03b1\u03b2\u03b3\u03b4\u03b5@");
        REQUIRE(u32s + tgui::String("@") == U"\u03b1\u03b2\u03b3\u03b4\u03b5@");

        REQUIRE(tgui::String("@") + std::string("xyz") == "@xyz");
        REQUIRE(tgui::String("@") + std::wstring(L"\U00010348") == L"@\U00010348");
        REQUIRE(tgui::String("@") + std::u16string(u"\U00010348") == u"@\U00010348");
        REQUIRE(tgui::String("@") + std::u32string(U"\U00010348") == U"@\U00010348");

        REQUIRE(std::string("xyz") + tgui::String("@") == "xyz@");
        REQUIRE(std::wstring(L"\U00010348") + tgui::String("@") == L"\U00010348@");
        REQUIRE(std::u16string(u"\U00010348") + tgui::String("@") == u"\U00010348@");
        REQUIRE(std::u32string(U"\U00010348") + tgui::String("@") == U"\U00010348@");

        REQUIRE(tgui::String("@") + 'x' == "@x");
        REQUIRE(tgui::String("@") + L'\x20AC' == L"@\u20AC");
        REQUIRE(tgui::String("@") + u'\x20AC' == u"@\u20AC");
        REQUIRE(tgui::String("@") + U'\x10348' == U"@\U00010348");

        REQUIRE('x' + tgui::String("@") == "x@");
        REQUIRE(L'\x20AC' + tgui::String("@") == L"\u20AC@");
        REQUIRE(u'\x20AC' + tgui::String("@") == u"\u20AC@");
        REQUIRE(U'\x10348' + tgui::String("@") == U"\U00010348@");

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        str = "@"; REQUIRE(str + u8"\U00010348" == u8"@\U00010348");
        str = "@"; REQUIRE(u8"\U00010348" + str == u8"\U00010348@");
        str = "@"; REQUIRE(str + std::u8string(u8"\U00010348") == u8"@\U00010348");
        str = "@"; REQUIRE(std::u8string(u8"\U00010348") + str == u8"\U00010348@");
        str = "@"; REQUIRE(str + u8'\x13' == u"@\u0013");
        str = "@"; REQUIRE(u'\x13' + str == u"\u0013@");
        REQUIRE(tgui::String("@") + u8"\U00010348" == u8"@\U00010348");
        REQUIRE(u8"\U00010348" + tgui::String("@") == u8"\U00010348@");
        REQUIRE(tgui::String("@") + std::u8string(u8"\U00010348") == u8"@\U00010348");
        REQUIRE(std::u8string(u8"\U00010348") + tgui::String("@") == u8"\U00010348@");
        REQUIRE(tgui::String("@") + u'\x13' == u"@\u0013");
        REQUIRE(u'\x13' + tgui::String("@") == u"\u0013@");
#endif
    }

    SECTION("operator<<")
    {
        std::stringbuf streambuf;
        std::ostream ostream(&streambuf);
        ostream << "abc";
        REQUIRE(streambuf.str() == "abc");

        std::wstringbuf wstreambuf;
        std::wostream wostream(&wstreambuf);
        wostream << L"\u03b1\u03b2\u03b3";
        REQUIRE(wstreambuf.str() == L"\u03b1\u03b2\u03b3");

#if defined(__cpp_lib_char8_t) && (__cpp_lib_char8_t >= 201811L)
        std::basic_stringbuf<char8_t> u8streambuf;
        std::basic_ostream<char8_t> u8ostream(&u8streambuf);
        u8ostream << u8"\u03b1\u03b2\u03b3";
        REQUIRE(u8streambuf.str() == u8"\u03b1\u03b2\u03b3");
#endif
    }

    SECTION("toInt")
    {
        str = "123";
        REQUIRE(str.toInt() == 123);

        str = "text";
        REQUIRE(str.toInt() == 0);
        REQUIRE(str.toInt(-5) == -5);
    }

    SECTION("toFloat")
    {
        str = "0.5";
        REQUIRE(str.toFloat() == 0.5f);

        str = "text";
        REQUIRE(str.toFloat() == 0);
        REQUIRE(str.toFloat(-3.5f) == -3.5f);
    }

    SECTION("trim")
    {
        str = "\t xyz\r\n";
        REQUIRE(str.trim() == "xyz");

        str = "a";
        REQUIRE(str.trim() == "a");

        str = "";
        REQUIRE(str.trim() == "");
    }

    SECTION("toLower")
    {
        str = "aBCdEfgHIJ";
        REQUIRE(str.toLower() == "abcdefghij");
    }

    SECTION("toUpper")
    {
        str = "aBCdEfgHIJ";
        REQUIRE(str.toUpper() == "ABCDEFGHIJ");
    }


    SECTION("Helper functions")
    {
        SECTION("isWhitespace")
        {
            REQUIRE(tgui::isWhitespace(' '));
            REQUIRE(tgui::isWhitespace('\t'));
            REQUIRE(tgui::isWhitespace('\r'));
            REQUIRE(tgui::isWhitespace('\n'));
            REQUIRE(!tgui::isWhitespace('x'));

            REQUIRE(tgui::isWhitespace(U' '));
            REQUIRE(tgui::isWhitespace(U'\t'));
            REQUIRE(tgui::isWhitespace(U'\r'));
            REQUIRE(tgui::isWhitespace(U'\n'));
            REQUIRE(!tgui::isWhitespace(U'x'));
        }
    }
}
