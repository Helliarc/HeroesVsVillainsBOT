
#include <dpp/dpp.h>
#include <dpp/nlohmann/json.hpp>

#include "../../envars.h"
#include "utility.h"
#include "initialization.h"
#include "management.h"

#include <iostream>
#include <fstream>
#include <unordered_map>

int main()
{
    std::unordered_map<dpp::snowflake, dpp::role_map> connectedGuildRoles{};

    try {

        dpp::cluster bot(ROLESTOKEN, dpp::intents::i_all_intents);

        bot.on_ready([&bot](const dpp::ready_t& event) {
            bot.log(dpp::ll_info, "Logged in as " + bot.me.username);

            RVB_i::startupVerification(bot);  //When bot resets, this is the first thing the RVB Bot does

        });

        bot.on_button_click([&bot, &connectedGuildRoles](const dpp::button_click_t& event) {
            auto GID = event.command.guild_id;
            auto commandUser = event.command.member;

            if (event.custom_id == "blue") {
                event.reply(dpp::ir_channel_message_with_source, dpp::message("Attempting to join the ***Blue*** team...").set_flags(dpp::m_ephemeral));
                dpp::snowflake roleIDRed{};
                dpp::snowflake roleIDBlue{};
                dpp::snowflake roleIDCivilian{};
                RVB_u::getGuildRoleIDs(roleIDRed, roleIDBlue, roleIDCivilian, connectedGuildRoles, GID);                
                bool isRed = false;
                bool isBlue = false;

                for (auto r : commandUser.roles) {
                    if (r == roleIDRed) {
                        isRed = true;
                    }
                    if (r == roleIDBlue) {
                        isBlue = true;
                    }
                }

                if (isRed == false && isBlue == false) {
                    bot.guild_member_add_role(GID, commandUser.user_id, roleIDBlue,
                        [commandUser, roleIDBlue, event](const dpp::confirmation_callback_t& event1) {
                            if (event1.is_error()) {
                                std::cout << "Error changing guild member role." << event1.http_info.body << std::endl;
                            }
                            else {
                                std::cout << "Success assigning member: " << commandUser.user_id << " the role: " << roleIDBlue << std::endl;
                                event.edit_response(dpp::message("Success joining the ***Blue*** team...").set_flags(dpp::m_ephemeral));
                            }
                        });
                }

                if (isRed == true) {
                    event.edit_response(dpp::message("You are on team ***Red***! Get out of here you SPY!!! **You cannot change roles after choosing one**").set_flags(dpp::m_ephemeral));
                }

                if (isBlue == true) {
                    event.edit_response(dpp::message("You are already on the ***Blue*** team.").set_flags(dpp::m_ephemeral));
                }
            }

            if (event.custom_id == "red") {
                event.reply(dpp::ir_channel_message_with_source, dpp::message("Attempting to join the ***Red*** team...").set_flags(dpp::m_ephemeral));
                dpp::snowflake roleIDRed{};
                dpp::snowflake roleIDBlue{};
                dpp::snowflake roleIDCivilian{};
                RVB_u::getGuildRoleIDs(roleIDRed, roleIDBlue, roleIDCivilian, connectedGuildRoles, GID);
                bool isBlue = false;
                bool isRed = false;
                for (auto r : commandUser.roles) {
                    if (r == roleIDBlue) {
                        isBlue = true;
                    }
                    if (r == roleIDRed) {
                        isRed = true;
                    }
                }

                if (isBlue == false && isRed == false) {
                    bot.guild_member_add_role(GID, commandUser.user_id, roleIDRed,
                        [commandUser, roleIDRed, event](const dpp::confirmation_callback_t& event1) {
                            if (event1.is_error()) {
                                std::cout << "Error changing guild member role." << event1.http_info.body << std::endl;
                            }
                            else {
                                std::cout << "Success assigning member: " << commandUser.user_id << " the role: " << roleIDRed << std::endl;
                                event.edit_response(dpp::message("Success joining the ***Red*** team...").set_flags(dpp::m_ephemeral));
                            }
                        });
                }
                
                if (isBlue == true) {
                    event.edit_response(dpp::message("You are on team ***Blue***! Get out of here you SPY!!! **You cannot change roles after choosing one**").set_flags(dpp::m_ephemeral));
                }

                if (isRed == true) {
                    event.edit_response(dpp::message("You are already on the ***Red*** team.").set_flags(dpp::m_ephemeral));
                }
            }
        });

        bot.on_interaction_create([&](const dpp::interaction_create_t event) {
            if (event.command.type == dpp::it_application_command) {
                auto cmd_data = std::get<dpp::command_interaction>(event.command.data);
                auto GID = event.command.guild_id;

                if (cmd_data.name == "init") {
                    RVB_i::createCommands(bot, GID);                                        //create the slash commands necessary for the RVB BOT to run.
                    RVB_i::firstMessages(bot, GID);                                         //generate the first messages the RVB BOT sends to the Guild.
                    RVB_m::updateGuildRoles(bot, GID, connectedGuildRoles);                 //check/create/store the roles for the RVB BOT
                }

                if (cmd_data.name == "prm") {
                    for (auto it : connectedGuildRoles) {
                        std::cout << "GID: " << it.first;
                        for (auto it2 : it.second)
                        {
                            std::cout << "Role Name: " << it2.second.name << std::endl;
                        }
                    }
                }

                if (cmd_data.name == "getuser") {
                    auto intArgs = cmd_data.options;
                    auto targetMemberName = std::get<std::string>(intArgs[0].value);

                    if (auto ptr = dpp::find_guild(GID)) {
                        dpp::guild g = *ptr;
                        auto members = g.members;
                        auto mstring = members;
                        auto membercount = g.member_count;

                        std::cout << "Total amount of members in Guild: " << membercount << std::endl;

                        for (auto it : members)
                        {
                            if (it.first == 0) {
                                //std::cout << "Found an invalid member in list..." << std::endl;
                            }
                            else {
                                auto userID = it.first;
                                auto member = dpp::find_guild_member(GID, userID);
                                auto jmember = member.build_json();
                                auto memberRoles = member.roles;

                                std::cout << member.user_id << std::endl;

                                if (member.user_id == 313218687874367488) {

                                    nlohmann::json jroles(member.build_json());
                                    std::ofstream jmem("memberJSON.txt");
                                    jmem << jroles;

                                }

                                bot.user_get(userID,
                                    [targetMemberName, member](const dpp::confirmation_callback_t event) {
                                        if (event.is_error()) {
                                            std::cout << "Error: user does not exist." << std::endl;
                                        }
                                        else {
                                            auto user = std::get<dpp::user_identified>(event.value);

                                            bool userMatch = false; 
                                            if (targetMemberName == user.username) {
                                                userMatch = true;
                                            }
                                            else if (targetMemberName == member.nickname) {
                                                userMatch = true;
                                            }
                                            else {
                                                userMatch = false;
                                            }

                                            if (userMatch) {
                                                std::cout << "Found user: " << user.username << std::endl;
                                                std::string x = (member.nickname != "") ? member.nickname : user.username;
                                                std::cout << "Guild member name: " << x << std::endl;
                                                std::cout << "Member Roles: ";

                                                for (auto it : member.roles) {
                                                    dpp::role tempRole = *dpp::find_role(it);
                                                    std::cout << tempRole.name << ": " << it << " | ";
                                                }
                                                std::cout << std::endl;
                                            }
                                        }
                                    });
                            }
                        }
                    }
                 };
            }

         });

        bot.on_message_create([&bot](const dpp::message_create_t& event) {
            if (event.msg.content == "!ping") {
                bot.message_create(dpp::message(event.msg.channel_id, "Pong!"));
            }
            });

        bot.on_log([](const dpp::log_t& event) {
            if (event.severity > dpp::ll_trace) {
                std::cout << dpp::utility::loglevel(event.severity) << ": " << event.message << "\n";
            }
            });

        bot.start(false);
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
