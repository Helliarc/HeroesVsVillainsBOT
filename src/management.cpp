#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
#include "management.h"

/*All functions here define the specific management function definitions to manage the RVB BOT.*/

namespace RVB_m {

    void updateGuildRoles(dpp::cluster& bot, dpp::snowflake GID, std::unordered_map<dpp::snowflake, dpp::role_map>& connectedGuildRoles) {
        bot.roles_get(GID,
            [&bot, GID, &connectedGuildRoles](const dpp::confirmation_callback_t& event) {
                if (event.is_error()) {
                    std::cout << "Error collecting Guild Roles. " << event.http_info.body << std::endl;
                }
                else {
                    connectedGuildRoles.erase(GID);

                    auto gRoles = std::get<dpp::role_map>(event.value);
                    auto guild = *dpp::find_guild(GID);
                    std::pair<dpp::snowflake, dpp::role_map> pair(guild.id, gRoles);

                    connectedGuildRoles.insert(pair);

                    for (auto it : connectedGuildRoles) {
                        auto guildID = it.first;
                        auto roles = it.second;
                        bool red = false;
                        bool blue = false;
                        bool civilian = false;
                        bool rerun = false;

                        if (guildID == GID) {
                            for (auto it1 : roles) {
                                auto roleID = it1.first;
                                auto roleName = it1.second.name;

                                if (roleName == "Red") {
                                    red = true;
                                }
                                if (roleName == "Blue") {
                                    blue = true;
                                }
                                if (roleName == "Civilian") {
                                    civilian = true;
                                }
                            }
                        }

                        if (red == false || blue == false || civilian == false) {
                            rerun = true;
                        }

                        if (red == false) {
                            std::cout << "Calling the Build Roles Function to build role: Red" << std::endl;
                            bool built = RVB_m::buildRole(bot, GID, "Red");  //create the necessary roles for the BOT
                            red = built;
                        }
                        if (blue == false) {
                            std::cout << "Calling the Build Roles Function to build role: Blue" << std::endl;
                            bool built = RVB_m::buildRole(bot, GID, "Blue");  //create the necessary roles for the BOT
                            blue = built;
                        }
                        if (civilian == false) {
                            std::cout << "Calling the Build Roles Function to build role: Civilian" << std::endl;
                            bool built = RVB_m::buildRole(bot, GID, "Civilian");  //create the necessary roles for the BOT
                            civilian = built;
                        }

                        if (rerun == true) {
                            std::cout << "Recursion is happening!!! Hopefully only once..." << std::endl;
                            updateGuildRoles(bot, GID, connectedGuildRoles);
                        }
                    }
                }
            }
        );
    };

    //void buildChannels(dpp::cluster& bot, dpp::snowflake GID) {
    //    dpp::channel channel = dpp::channel()
    //        .set_name("Test")
    //        .set_flags(dpp::c_category)
    //        ;

    //    /* add overwrite for @everyone role denying all permissions.
    //    channel.add_permission_overwrite(role_id, 0, dpp::role_permissions, 0);
    //    */

    //};

    bool buildRole(dpp::cluster& bot, dpp::snowflake GID, std::string roleName)
    {

            enum class Colors {
                Blue = 0000555,
                Red = 850000,
                Civilian = 928454
            };

            dpp::role role = dpp::role()
                .set_name(roleName)
                .set_guild_id(GID)
                ;

            if (roleName == "Red") {
                role.set_color(static_cast<int>(Colors::Red));
            }
            if (roleName == "Blue") {
                role.set_color(static_cast<int>(Colors::Blue));
            }
            if (roleName == "Civilian") {
                role.set_color(static_cast<int>(Colors::Civilian));
            }

            bot.role_create(role,
                [](const dpp::confirmation_callback_t& event) {
                    if (event.is_error()) {
                        std::cout << "Error creating the role." << event.http_info.body << std::endl;
                        return false;
                    }
                    else {
                        auto value = std::get<dpp::role>(event.value);
                        std::cout << "Success creating role: " << value.name << std::endl;
                        return true;
                    }
                });
    };
}