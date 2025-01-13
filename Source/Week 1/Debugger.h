#pragma once

#include <iostream>
#include "EnumMsg.h"

class Debugger
{
public:
static void Print(std::string msg, EnumMsg type = EnumMsg::DEFAULT) {
        switch (type)
        {
        case EnumMsg::WARNING:
            std::cout << "\033[33m";
            break;
        case EnumMsg::ERROR:
            std::cout << "\033[31m";
            break;
        case EnumMsg::SUCCESS:
            std::cout << "\033[32m";
            break;
        default:
            break;
        }

        std::cout << msg << "\033[0m" << std::endl;
    }
};