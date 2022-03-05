#include "initialization.h"

namespace RVB_i {

    void startupVerification(dpp::cluster& bot) {
        bot.global_commands_get(
            [&bot](const dpp::confirmation_callback_t& event) {
                if (event.is_error()) {
                    std::cout << "Error collecting GLOBAL slash commands: " << event.http_info.body << std::endl;
                }
                else {
                    bool initSet = false;
                    dpp::slashcommand_map t = std::get<dpp::slashcommand_map>(event.value);
                    std::cout << "Success collecting GLOBAL slash commands" << std::endl;
                    for (const auto& it : t) {
                        if (it.second.name == "init") {
                            std::cout << "The globalINIT command has already been registered." << std::endl;
                            initSet = true;
                        }
                    };
                    if (initSet == false) {
                        dpp::slashcommand init;
                        /*May wish to return and add permissions to this SlashCommand here(Admin Only Command)*/
                        init.set_name("init")
                            .set_description("This command initializes the bot.")
                            .set_application_id(bot.me.id);

                        bot.global_command_create(init,
                            [&](const dpp::confirmation_callback_t& event) {
                                if (event.is_error()) {
                                    std::cout << "error creating slash command" << event.http_info.body << std::endl;
                                }
                                else {
                                    std::cout << "Success creating slash command" << std::endl;
                                }
                            });
                    }
                    return;
                }
            }
        );
    };


    void createCommands(dpp::cluster& bot, dpp::snowflake& GID) {
        
        std::vector<dpp::slashcommand> cmdList{

            dpp::slashcommand().set_name("getuser")
            .set_description("This command gets the user info of a user")
            .set_application_id(bot.me.id)
            .add_option(dpp::command_option(dpp::co_string, "user", "The username of the user", true)),

           dpp::slashcommand().set_name("getroles")
           .set_description("Get the guild roles.")
           .set_application_id(bot.me.id),

            dpp::slashcommand().set_name("invitemessage")
           .set_description("Print the roles map of all guilds.")
           .set_application_id(bot.me.id),

            dpp::slashcommand().set_name("createchannels")
           .set_description("Creates the guild Channels for the BOT")
           .set_application_id(bot.me.id),

        };

        bot.guild_bulk_command_create(cmdList, GID,
            [&bot](const dpp::confirmation_callback_t& event) {
                if (event.is_error()) {
                    std::cout << "error creating slash command list: " << event.http_info.body << std::endl;
                }
                else {
                    std::cout << "Success creating bulk slash commands!" << std::endl;
                }
            });
    };

}
