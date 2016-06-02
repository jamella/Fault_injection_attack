//
// Created by xiangyu zhang on 6/2/16.
//

#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
class Parser
{
    friend class constructor;
public:
    Parser() = default;
    ~Parser() = default;
    Parser(const std::string &);
    void show_gate_info() const;


private:
    std::map<std::string, int> gateInfo;
    const std::string path;

    std::string find_gateName(const std::string&) const;
    std::string find_gateIn(const std::string& ) const;
    void show_map(const std::map<std::string, int>&) const;

};

Parser::Parser(const std::string& path)
{
    std::fstream infile(path);
    std::string info;
    while(getline(infile, info))
    {
        std::cout << "info: " << info << std::endl;
        auto gate_name = find_gateName(info);
        auto gate_fanin = std::stoi(find_gateIn(info));
        gateInfo.insert(std::pair<std::string, int>(gate_name, gate_fanin));
    }
}


std::string Parser::find_gateName(const std::string& info) const
{
    std::smatch result;
    std::regex pattern("([a-zA-Z0-9]*)(:)([0-9]*)");
    std::regex_search(info, result, pattern);
    return result[1].str();
}

std::string Parser::find_gateIn(const std::string &info) const
{
    std::smatch result;
    std::regex pattern("([a-zA-Z0-9]*)(:)([0-9]*)");
    std::regex_search(info, result, pattern);
    return result[3].str();
}


void Parser::show_gate_info() const
{
    show_map(gateInfo);
}

void Parser::show_map(const std::map<std::string, int>& target) const
{
    for(auto i: target)
    {
        std::cout << i.first << " == " << i.second << std::endl;
    }
}
#endif //PARSER_PARSER_H

