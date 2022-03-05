#include "management.h"
#include "rvbenvars.h"

namespace RVB_m {

	void roleCheck(dpp::cluster& bot, dpp::snowflake& GID) {
		bot.roles_get(GID,
			[&bot, GID](const dpp::confirmation_callback_t& event) {
				if (event.is_error()) {
					std::cout << "Error collecting Guild Roles. " << event.http_info.body << std::endl;
				}
				else {
                    auto gRoles = std::get<dpp::role_map>(event.value);

                    bool red = false;
                    bool blue = false;
                    bool neutral = false;

                    for (auto& it : gRoles) {
                        
                        if (it.second.name == RVB_e::roleRed.name) {  
                            red = true;
                        }
                        if (it.second.name == RVB_e::roleBlue.name) {
                            blue = true;
                        }
                        if (it.second.name == RVB_e::roleNeutral.name) {
                            neutral = true;
                        }
                    }

                    if (!red) {
                        RVB_e::roleRed.set_guild_id(GID);

                        bot.role_create(RVB_e::roleRed,
                            [](const dpp::confirmation_callback_t& event) {
                                if (event.is_error()) {
                                    std::cout << "Error creating the role." << event.http_info.body << std::endl;
                                }
                                else {
                                    auto value = std::get<dpp::role>(event.value);
                                    std::cout << "Success creating role: " << value.name << std::endl;
                                }
                            }); 
                        return;
                    }
                    if (!blue) {
                        RVB_e::roleBlue.set_guild_id(GID);

                        bot.role_create(RVB_e::roleBlue,
                            [](const dpp::confirmation_callback_t& event) {
                                if (event.is_error()) {
                                    std::cout << "Error creating the role." << event.http_info.body << std::endl;
                                }
                                else {
                                    auto value = std::get<dpp::role>(event.value);
                                    std::cout << "Success creating role: " << value.name << std::endl;
                                }
                            });
                        return;
                    }
                    if (!neutral) {
                        RVB_e::roleNeutral.set_guild_id(GID);

                        bot.role_create(RVB_e::roleNeutral,
                            [](const dpp::confirmation_callback_t& event) {
                                if (event.is_error()) {
                                    std::cout << "Error creating the role." << event.http_info.body << std::endl;
                                }
                                else {
                                    auto value = std::get<dpp::role>(event.value);
                                    std::cout << "Success creating role: " << value.name << std::endl;
                                }
                            });
                        return;
                    }
                    if (red && blue && neutral) {

                    }
				}
			});
	}

    void categoryCreate(dpp::cluster& bot, dpp::snowflake GID)
    {
        bot.channels_get(GID,
            [&bot, GID](const dpp::confirmation_callback_t& event) {
                if (event.is_error()) {
                    std::cout << "Error collecting Guild Channels. " << event.http_info.body << std::endl;
                }
                else {
                    auto gChannels = std::get<dpp::channel_map>(event.value);
                    auto guild = *dpp::find_guild(GID);
                    auto gRoles = guild.roles;

                    bool red = false;
                    dpp::snowflake redID;
                    bool blue = false;
                    dpp::snowflake blueID;
                    bool home = false;
                    dpp::snowflake homeID;

                    for (auto& it : gChannels) {

                        if (it.second.name == RVB_e::categoryRed.name) {
                            red = true;
                        }
                        if (it.second.name == RVB_e::categoryBlue.name) {
                            blue = true;
                        }
                        if (it.second.name == RVB_e::categoryHome.name) {
                            home = true;
                        }
                    }

                    for (auto& it : gRoles) {
                        dpp::role role = *dpp::find_role(it);
                        if (role.name == RVB_e::roleNeutral.name) {
                            homeID = role.id;
                        }
                        if (role.name == RVB_e::roleRed.name) {
                            redID = role.id;
                        }
                        if (role.name == RVB_e::roleBlue.name) {
                            blueID = role.id;
                        }
                    }

                    if (!home) {
                        auto category = RVB_e::categoryHome;
                        category.guild_id = GID;
                        category.add_permission_overwrite(GID,0,0,dpp::role_permissions::p_view_channel);
                        bot.channel_create(category,
                            [&bot](const dpp::confirmation_callback_t& event) {
                                if (event.is_error()) {
                                    std::cout << "Error creating the category." << event.http_info.body << std::endl;
                                }
                                else {
                                    auto guildChannel = std::get<dpp::channel>(event.value);
                                    std::cout << "Success creating category: " << guildChannel.name << std::endl;
                                    
                                    auto channelG = RVB_e::channelGeneral;
                                    auto channelC = RVB_e::channelCommand;
                                    channelG.set_parent_id(guildChannel.id);
                                    channelG.guild_id = guildChannel.guild_id;
                                    channelC.set_parent_id(guildChannel.id);
                                    channelC.guild_id = guildChannel.guild_id;

                                    bot.channel_create(channelG,
                                        [](const dpp::confirmation_callback_t& event) {
                                            if (event.is_error()) {
                                                std::cout << "Error creating the channel." << event.http_info.body << std::endl;
                                            }
                                            else {
                                                auto guildChannel = std::get<dpp::channel>(event.value);
                                                std::cout << "Success creating channel: " << guildChannel.name << std::endl;
                                            }
                                        });

                                    bot.channel_create(channelC,
                                        [](const dpp::confirmation_callback_t& event) {
                                            if (event.is_error()) {
                                                std::cout << "Error creating the channel." << event.http_info.body << std::endl;
                                            }
                                            else {
                                                auto guildChannel = std::get<dpp::channel>(event.value);
                                                std::cout << "Success creating channel: " << guildChannel.name << std::endl;
                                            }
                                        });
                                }
                            });
                        return;
                    }

                    if (!red) {
                        auto category = RVB_e::categoryRed;
                        category.guild_id = GID;
                        category.add_permission_overwrite(GID, 0, 0, dpp::role_permissions::p_view_channel);
                        category.add_permission_overwrite(redID, 0, dpp::role_permissions::p_view_channel, 0);
                        category.add_permission_overwrite(blueID, 0, 0, dpp::role_permissions::p_view_channel);
                        bot.channel_create(category,
                            [&bot](const dpp::confirmation_callback_t& event) {
                                if (event.is_error()) {
                                    std::cout << "Error creating the category." << event.http_info.body << std::endl;
                                }
                                else {
                                    auto guildChannel = std::get<dpp::channel>(event.value);
                                    std::cout << "Success creating category: " << guildChannel.name << std::endl;

                                    auto channelG = RVB_e::channelGeneral;
                                    auto channelC = RVB_e::channelCommand;
                                    channelG.set_parent_id(guildChannel.id);
                                    channelG.guild_id = guildChannel.guild_id;
                                    channelC.set_parent_id(guildChannel.id);
                                    channelC.guild_id = guildChannel.guild_id;

                                    bot.channel_create(channelG,
                                        [](const dpp::confirmation_callback_t& event) {
                                            if (event.is_error()) {
                                                std::cout << "Error creating the channel." << event.http_info.body << std::endl;
                                            }
                                            else {
                                                auto guildChannel = std::get<dpp::channel>(event.value);
                                                std::cout << "Success creating channel: " << guildChannel.name << std::endl;
                                            }
                                        });

                                    bot.channel_create(channelC,
                                        [](const dpp::confirmation_callback_t& event) {
                                            if (event.is_error()) {
                                                std::cout << "Error creating the channel." << event.http_info.body << std::endl;
                                            }
                                            else {
                                                auto guildChannel = std::get<dpp::channel>(event.value);
                                                std::cout << "Success creating channel: " << guildChannel.name << std::endl;
                                            }
                                        });
                                }
                            });
                        return;
                    }
                    if (!blue) {
                        auto category = RVB_e::categoryBlue;
                        category.guild_id = GID;
                        category.add_permission_overwrite(GID, 0, 0, dpp::role_permissions::p_view_channel);
                        category.add_permission_overwrite(blueID, 0, dpp::role_permissions::p_view_channel, 0);
                        category.add_permission_overwrite(redID, 0, 0, dpp::role_permissions::p_view_channel);
                        bot.channel_create(category,
                            [&bot](const dpp::confirmation_callback_t& event) {
                                if (event.is_error()) {
                                    std::cout << "Error creating the category." << event.http_info.body << std::endl;
                                }
                                else {
                                    auto guildChannel = std::get<dpp::channel>(event.value);
                                    std::cout << "Success creating category: " << guildChannel.name << std::endl;

                                    auto channelG = RVB_e::channelGeneral;
                                    auto channelC = RVB_e::channelCommand;
                                    channelG.set_parent_id(guildChannel.id);
                                    channelG.guild_id = guildChannel.guild_id;
                                    channelC.set_parent_id(guildChannel.id);
                                    channelC.guild_id = guildChannel.guild_id;

                                    bot.channel_create(channelG,
                                        [](const dpp::confirmation_callback_t& event) {
                                            if (event.is_error()) {
                                                std::cout << "Error creating the channel." << event.http_info.body << std::endl;
                                            }
                                            else {
                                                auto guildChannel = std::get<dpp::channel>(event.value);
                                                std::cout << "Success creating channel: " << guildChannel.name << std::endl;
                                            }
                                        });

                                    bot.channel_create(channelC,
                                        [](const dpp::confirmation_callback_t& event) {
                                            if (event.is_error()) {
                                                std::cout << "Error creating the channel." << event.http_info.body << std::endl;
                                            }
                                            else {
                                                auto guildChannel = std::get<dpp::channel>(event.value);
                                                std::cout << "Success creating channel: " << guildChannel.name << std::endl;
                                            }
                                        });
                                }
                            });
                        return;
                    }


                    if (red && blue && home) {

                    }
                }
            });
    }
    void openInvite(dpp::cluster& bot, dpp::snowflake GID)
    {
        auto guild = *dpp::find_guild(GID);
        auto gChannels = guild.channels;
        dpp::channel parentChannel;
        dpp::channel invitationChannel;

        for (auto& it : gChannels) {
            auto channel = *dpp::find_channel(it);
            if (channel.name == RVB_e::categoryHome.name) {
                parentChannel = channel;
            }
        }

        for (auto& it : gChannels) {
            auto channel = *dpp::find_channel(it);
            if (channel.name == RVB_e::channelCommand.name) {
                if (channel.parent_id == parentChannel.id) {
                    invitationChannel = channel;
                }
            }
        }

        dpp::embed embedInvitation = dpp::embed().
            set_color(0xFFFF00).
            set_title("Heroes Vs. Villains!!!").
            set_url("").
            set_author("", "", "").
            set_image("https://images-wixmp-ed30a86b8c4ca887773594c2.wixmp.com/f/afeef1b9-a594-4c64-ab26-a795b288f8d1/d4ymqjl-50667870-0822-4133-9186-61990ccb9eac.jpg/v1/fill/w_900,h_675,q_75,strp/red_and_blue___yin_yang_by_comasleeper_d4ymqjl-fullview.webp?token=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJ1cm46YXBwOjdlMGQxODg5ODIyNjQzNzNhNWYwZDQxNWVhMGQyNmUwIiwiaXNzIjoidXJuOmFwcDo3ZTBkMTg4OTgyMjY0MzczYTVmMGQ0MTVlYTBkMjZlMCIsIm9iaiI6W1t7ImhlaWdodCI6Ijw9Njc1IiwicGF0aCI6IlwvZlwvYWZlZWYxYjktYTU5NC00YzY0LWFiMjYtYTc5NWIyODhmOGQxXC9kNHltcWpsLTUwNjY3ODcwLTA4MjItNDEzMy05MTg2LTYxOTkwY2NiOWVhYy5qcGciLCJ3aWR0aCI6Ijw9OTAwIn1dXSwiYXVkIjpbInVybjpzZXJ2aWNlOmltYWdlLm9wZXJhdGlvbnMiXX0.YN6qKArKCbyBpfXhHnCmMrZDEcAOwAocIyz63I6jpF4").
            set_footer(dpp::embed_footer().set_text("Choose a side: ")).
            set_timestamp(time(NULL));

        dpp::message messageInvitation(invitationChannel.id, embedInvitation);
            messageInvitation.add_component(dpp::component()
                .add_component(
                    dpp::component().set_label("hero")
                    .set_style(dpp::cos_primary)
                    .set_id("hero"))
                .add_component(
                    dpp::component().set_label("villain")
                    .set_style(dpp::cos_danger)
                    .set_id("villain"))
                .add_component(
                    dpp::component().set_label("civilian")
                    .set_style(dpp::cos_secondary)
                    .set_id("civilian"))
            );

        bot.message_create(messageInvitation,
            [&bot](const dpp::confirmation_callback_t& event) {
                if (event.is_error()) {
                    std::cout << "Error creating message." << event.http_info.body << std::endl;
                }
                else {
                    std::cout << "Success creating message: " << std::endl;
                }
            }
        );
    }

    void roleClick(dpp::cluster& bot, dpp::button_click_t event) {
        dpp::guild guild = *dpp::find_guild(event.command.guild_id);
        auto gRoles = guild.roles;
        dpp::role roleRed{};
        dpp::role roleBlue{};
        dpp::role roleCivilian{};

        for (auto& it : gRoles) {
            dpp::role role = *dpp::find_role(it);
            if (role.name == RVB_e::roleNeutral.name) {
                roleCivilian = role;
            }
            if (role.name == RVB_e::roleRed.name) {
                roleRed = role;
            }
            if (role.name == RVB_e::roleBlue.name) {
                roleBlue = role;
            }
        }

        bool isRed = false;
        bool isBlue = false;
        bool isCivilian = false;

        for (auto& r : event.command.member.roles) {
            if (r == roleRed.id) {
                isRed = true;
            }
            if (r == roleBlue.id) {
                isBlue = true;
            }
            if (r == roleCivilian.id) {
                isCivilian = true;
            }
        }

        if (isRed == false && isBlue == false) {

            if (event.custom_id == "hero") {

                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, roleBlue.id,
                    [roleBlue, event](const dpp::confirmation_callback_t& event1) {
                    if (event1.is_error()) {
                        std::cout << "Error changing guild member role." << event1.http_info.body << std::endl;
                    }
                    else {
                        std::cout << "Success assigning member role: " << roleBlue.name << std::endl;
                        event.edit_response(dpp::message("Success becoming a Hero...").set_flags(dpp::m_ephemeral));
                    }
                });
            }

            if (event.custom_id == "villain") {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, roleRed.id,
                    [roleRed, event](const dpp::confirmation_callback_t& event1) {
                    if (event1.is_error()) {
                        std::cout << "Error changing guild member role." << event1.http_info.body << std::endl;
                    }
                    else {
                        std::cout << "Success assigning member role: " << roleRed.name << std::endl;
                        event.edit_response(dpp::message("Success becoming a Villain...").set_flags(dpp::m_ephemeral));
                    }
                });
            }

            if (event.custom_id == "civilian") {
                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, roleCivilian.id,
                    [roleCivilian, event](const dpp::confirmation_callback_t& event1) {
                    if (event1.is_error()) {
                        std::cout << "Error changing guild member role." << event1.http_info.body << std::endl;
                    }
                    else {
                        std::cout << "Success assigning member role: " << roleCivilian.name << std::endl;
                        event.edit_response(dpp::message("Success becoming a Civilian...").set_flags(dpp::m_ephemeral));
                    }
                });
            }
        }

        if (isRed == true) {
            if (event.custom_id == "hero") {
                event.edit_response(dpp::message("You are already a villain... **You cannot change roles after choosing one**").set_flags(dpp::m_ephemeral));
            }
            if (event.custom_id == "villain") {
                event.edit_response(dpp::message("You are already a villain...").set_flags(dpp::m_ephemeral));
            }
            if (event.custom_id == "civilian") {
                bot.guild_member_delete_role(event.command.guild_id, event.command.member.user_id, roleRed.id,
                    [roleRed](const dpp::confirmation_callback_t& event1) {
                        if (event1.is_error()) {
                            std::cout << "Error removing guild member role." << event1.http_info.body << std::endl;
                        }
                        else {
                            std::cout << "Success removing guild member role: " << roleRed.name << std::endl;
                        }
                    });

                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, roleCivilian.id,
                    [roleCivilian, event](const dpp::confirmation_callback_t& event1) {
                        if (event1.is_error()) {
                            std::cout << "Error changing guild member role." << event1.http_info.body << std::endl;
                        }
                        else {
                            std::cout << "Success assigning member role: " << roleCivilian.name << std::endl;
                            event.edit_response(dpp::message("Success becoming a Civilian...").set_flags(dpp::m_ephemeral));
                        }
                    });
            }
        }

        if (isBlue == true) {
            if (event.custom_id == "hero") {
                event.edit_response(dpp::message("You are already a Hero...").set_flags(dpp::m_ephemeral));
            }
            if (event.custom_id == "villain") {
                event.edit_response(dpp::message("You are already a Hero... **You cannot change roles after choosing one**").set_flags(dpp::m_ephemeral));
            }
            if (event.custom_id == "civilian") {
                bot.guild_member_delete_role(event.command.guild_id, event.command.member.user_id, roleBlue.id,
                    [roleBlue](const dpp::confirmation_callback_t& event1) {
                        if (event1.is_error()) {
                            std::cout << "Error removing guild member role." << event1.http_info.body << std::endl;
                        }
                        else {
                            std::cout << "Success removing guild member role: " << roleBlue.name << std::endl;
                        }
                    });

                bot.guild_member_add_role(event.command.guild_id, event.command.member.user_id, roleCivilian.id,
                    [roleCivilian, event](const dpp::confirmation_callback_t& event1) {
                    if (event1.is_error()) {
                        std::cout << "Error changing guild member role." << event1.http_info.body << std::endl;
                    }
                    else {
                        std::cout << "Success assigning member role: " << roleCivilian.name << std::endl;
                        event.edit_response(dpp::message("Success becoming a Civilian...").set_flags(dpp::m_ephemeral));
                    }
                });
            }
        }
    }
}
