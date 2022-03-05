#pragma once
#include<dpp/dpp.h>
#include<iostream>

namespace RVB_i {

    void startupVerification(dpp::cluster& bot);
    void createCommands(dpp::cluster& bot, dpp::snowflake& GID);
}
