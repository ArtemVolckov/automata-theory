#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "regex.hpp"

TEST_CASE("Compilation") {
    Regex regex;

    SECTION("Parser exceptions") {
        REQUIRE_THROWS_AS(regex.compile("|"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("a|"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("|a"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("?"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("..."), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("...a"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("{"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("}"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("a{"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("}a"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("{}"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("a{}a"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("a{-1}"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("a{1238490123804}"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("a{a}"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("("), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile(")"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("(asdf"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("asdf)"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("(<name1)"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("(<name1>"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("(<name1>)"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("%|"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("|%"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("?%"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("...%"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("%("), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("(%"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("%)"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile(")%"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("%<"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile(">%"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("%(%<name>a)"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("(<name>a%)%"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("(%<%name>a)"), std::invalid_argument);
    }
    SECTION("Ast exceptions") {
        REQUIRE_THROWS_AS(regex.compile("(<name1>a)|(<name1>b)"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("(<name1>a)(<name1>b)"), std::invalid_argument);
        REQUIRE_THROWS_AS(regex.compile("(<name1>(<name1>))"), std::invalid_argument);
    }
    SECTION("Successful cases") {
        REQUIRE_NOTHROW(regex.compile("(<name1>A){5}"));
        REQUIRE_NOTHROW(regex.compile("(<name1>(<name2>a|b|c))"));
        REQUIRE_NOTHROW(regex.compile("abcd"));
        REQUIRE_NOTHROW(regex.compile("(abc)|a"));
        REQUIRE_NOTHROW(regex.compile("(abcd)?"));
        REQUIRE_NOTHROW(regex.compile("(abcd)..."));
        REQUIRE_NOTHROW(regex.compile("(abcd){5}"));
        REQUIRE_NOTHROW(regex.compile(""));
        REQUIRE_NOTHROW(regex.compile("()"));
        REQUIRE_NOTHROW(regex.compile("((()))"));
        REQUIRE_NOTHROW(regex.compile("a{2}|b...|c?"));
        REQUIRE_NOTHROW(regex.compile("%|%"));
        REQUIRE_NOTHROW(regex.compile("%?%"));
        REQUIRE_NOTHROW(regex.compile("%...%"));
        REQUIRE_NOTHROW(regex.compile("%"));
        REQUIRE_NOTHROW(regex.compile("%%"));
        REQUIRE_NOTHROW(regex.compile("%%%"));
        REQUIRE_NOTHROW(regex.compile("."));
        REQUIRE_NOTHROW(regex.compile(".."));
        REQUIRE_NOTHROW(regex.compile("(hi((<name1>abcd|111))|GG)"));
    }
}

TEST_CASE("Match and Search") {
    Regex regex;
    RegexData data;
    
    SECTION("Match") {
        REQUIRE_THROWS_AS(regex.match("", data), std::logic_error);
        REQUIRE_THROWS_AS(regex.match("...", "", data), std::invalid_argument);

        regex.compile("");
        REQUIRE(regex.match("", data));
        REQUIRE(!regex.match("hello", data));
        
        regex.compile("(abc)|(a...)");
        REQUIRE(regex.match("", data));
        REQUIRE(regex.match("abc", data));
        REQUIRE(regex.match("aaaaaaaaaaaa", data));
        REQUIRE(!regex.match("abca", data));

        REQUIRE(regex.match("a|b|c", "a", data));
        REQUIRE(!regex.match("abc", data));
    }
    SECTION("Search") {
        REQUIRE_THROWS_AS(regex.search("", data), std::logic_error);
        REQUIRE_THROWS_AS(regex.search("...", "", data), std::invalid_argument);

        regex.compile("a...");
        REQUIRE(regex.search("", data));
        REQUIRE(regex.search("aaaaaa", data));

        REQUIRE(regex.search("abcd", "abcd.........", data));
        REQUIRE(!regex.search("abc", data));
    }
}

TEST_CASE("Regex data") {
    Regex regex;
    RegexData data;
    
    SECTION("Exceptions") {
        int size = data.size();
        REQUIRE_THROWS_AS(data[size], std::out_of_range);
    }

    SECTION("Match") {
        regex.compile("(<1st_group>a...)");
        REQUIRE(regex.match("", data));        
        
        REQUIRE(regex.match("HELLO", "HELLO", data));
        REQUIRE(data.get_matched_string() == "HELLO");
        REQUIRE(data.size() == 0);

        REQUIRE(regex.match("(<name1>abcd...)", "abcddd", data));
        REQUIRE(data.get_matched_string() == "abcddd");
        REQUIRE(data.size() == 1);
        REQUIRE(data[0].first == "name1");
        REQUIRE(data[0].second == "abcddd");
    }
    SECTION("Search") {
        REQUIRE(regex.search("(ab(c|d...))", "abhaha", data));
        REQUIRE(data.get_matched_string() == "ab");
        REQUIRE(data.size() == 0);

        REQUIRE(regex.search("(<name1>(a|b)(<name2>c))", "acccc", data));
        REQUIRE(data.get_matched_string() == "ac");
        REQUIRE(data.size() == 2);
        REQUIRE(data[0].first == "name2");
        REQUIRE(data[0].second == "c");
        REQUIRE(data[1].first == "name1");
        REQUIRE(data[1].second == "ac");

        REQUIRE(regex.search("(<name1>(a|b)(<name2>c...))", "b", data));
        REQUIRE(data.get_matched_string() == "b");
        REQUIRE(data.size() == 2);
        REQUIRE(data[0].first == "name2");
        REQUIRE(data[0].second == "");
        REQUIRE(data[1].first == "name1");
        REQUIRE(data[1].second == "b");
    }
}

TEST_CASE("Compiled DFA conversations") {
    SECTION("RE recovery") {

    }
}
