#include "initialization.h"
#include "management.h"

#include <dpp/dpp.h>
#include <iostream>

#include "../envars.h"

int main()
{
    dpp::cluster bot(TOKEN);

    bot.on_interaction_create([&bot](const dpp::interaction_create_t& event) {
        if (event.command.type == dpp::it_application_command) {
            auto cmd_data = std::get<dpp::command_interaction>(event.command.data);
            auto GID = event.command.guild_id;

            if (cmd_data.name == "init") {
                RVB_i::createCommands(bot, GID);                            //create the slash commands necessary for RVB BOT monitoring.
                RVB_m::roleCheck(bot, GID);                                 //initializes the roles check/creation

                event.reply("Initializing the RedVsBlue BOT...");
            }
            if (cmd_data.name == "createchannels") {
                RVB_m::categoryCreate(bot, GID);                            //initializes the channels check/creation

                event.reply("Creating the RedVsBlue channels...");
            }

            if (cmd_data.name == "invitemessage") {
                RVB_m::openInvite(bot, GID);
                event.reply(dpp::ir_channel_message_with_source, dpp::message("Posting the Faction selection message").set_flags(dpp::m_ephemeral));
            }
        };
    });

    bot.on_button_click([&bot](const dpp::button_click_t& event) {

        if (event.custom_id == "hero") {
            event.reply(dpp::ir_channel_message_with_source, dpp::message("Attempting to become a Hero...").set_flags(dpp::m_ephemeral));
            RVB_m::roleClick(bot, event);
        }

        if (event.custom_id == "villain") {
            event.reply(dpp::ir_channel_message_with_source, dpp::message("Attempting to become a Villain...").set_flags(dpp::m_ephemeral));
            RVB_m::roleClick(bot, event);
        }

        if (event.custom_id == "civilian") {
            event.reply(dpp::ir_channel_message_with_source, dpp::message("Attempting to become a Civilian...").set_flags(dpp::m_ephemeral));
            RVB_m::roleClick(bot, event);
        }
    });

    bot.on_guild_role_create([&bot](const dpp::guild_role_create_t& event) {
        auto guild = *event.creating_guild;
        auto GID = guild.id;
        
        RVB_m::roleCheck(bot, GID);
    });

    bot.on_channel_create([&bot](const dpp::channel_create_t& event) {
        auto guild = *event.creating_guild;
        auto GID = guild.id;
        auto channel = *event.created;

        if (channel.flags == dpp::CHANNEL_CATEGORY) {
            RVB_m::categoryCreate(bot, GID);
        }
    });


    /* Register Global slash command in on_ready */
    bot.on_ready([&bot](const dpp::ready_t& event) {
        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {
        
        }
        
        bot.log(dpp::ll_info, "Logged in as " + bot.me.username);
        /*set initial environment of Global Slash commands that enable the use of the BOT*/
        RVB_i::startupVerification(bot);
        
    });


    /* Output simple log messages to stdout */
    bot.on_log(dpp::utility::cout_logger());

    /* Start the bot */
    bot.start(false);

    return 0;
}
