#pragma once
#include <dpp/dpp.h>

/*These function Definitions provide utility to the RVB bot ONLY
  These function Definitions are random and ugly to limit code clutter in Main().
*/

namespace RVB_u {



    void getGuildRoleIDs(dpp::snowflake& roleIDRed, dpp::snowflake& roleIDBlue, dpp::snowflake& roleIDVerified, std::unordered_map<dpp::snowflake, dpp::role_map>& connectedGuildRoles, dpp::snowflake GID) {

        for (auto it : connectedGuildRoles) {
            auto guildID = it.first;
            auto roles = it.second;
            bool guildPresent = false;
            bool rolePresent = false;

            if (guildID == GID) {
                guildPresent = true;
                for (auto it1 : roles) {
                    auto roleID = it1.first;
                    auto roleName = it1.second.name;

                    if (roleName == "Red") {
                        roleIDRed = roleID;
                    }
                    if (roleName == "Blue") {
                        roleIDBlue = roleID;
                    }
                    if (roleName == "Civilian") {
                        roleIDVerified = roleID;
                    }
                }
            }
        }
    }
}