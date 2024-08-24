#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <stdexcept>

class RegexData;

class Regex {
    private:
        bool is_compiled = false;
        struct MinNdfaImpl;
        MinNdfaImpl* pMinNdfaImpl = nullptr;
        bool group_match(int grop_dfa_num, std::string_view string_to_check, int& position, RegexData& data);

    public:
        ~Regex();

        void compile(std::string_view cregex);

        bool match(std::string_view string_to_match, RegexData& data);
        bool match(std::string_view cregex, std::string_view string_to_match, RegexData& data);

        bool search(std::string_view string_to_search, RegexData& data);
        bool search(std::string_view cregex, std::string_view string_to_search, RegexData& data);
};

class RegexData {
    private:
        std::string matched_string;
        // Vector of pairs (group name, group value)
        std::vector<std::pair<std::string, std::string>> captured_groups;
        
        void add_captured_group(std::string name, std::string value) {
            captured_groups.emplace_back(name, value);
        }

    public:
        std::string get_matched_string() const {
            return matched_string;
        }
        std::pair<std::string, std::string> operator[](size_t index) const {
            if (index < captured_groups.size()) 
                return captured_groups[index];
            else 
                throw std::out_of_range("Index out of range");
        }
        auto begin() { return captured_groups.begin(); }
        auto end()   { return captured_groups.end();   }
        auto begin() const { return captured_groups.begin(); }
        auto end()   const { return captured_groups.end();   }

        size_t size() const {
            return captured_groups.size();
        }

        friend class Regex;
};
