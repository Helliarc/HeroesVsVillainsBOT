#pragma once
#include <dpp/dpp.h>

/*All functions here define the initialization parameters and data to start the RVB BOT.
  To update guild slash commands available to RVB BOT, update this file.
  On Release, guild command create will need manual update to Global Command create.
*/

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
             .add_option(dpp::command_option(dpp::co_string, "user", "The username of the user", true)
             ),
            dpp::slashcommand().set_name("getroles")
            .set_description("Get the guild roles.")
            .set_application_id(bot.me.id),
             dpp::slashcommand().set_name("prm")
            .set_description("Print the roles map of all guilds.")
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

    void firstMessages(dpp::cluster& bot, dpp::snowflake GID) {

        bot.channels_get(GID,
            [&bot](const dpp::confirmation_callback_t& event) {
                if (event.is_error()) {
                    std::cout << "Error getting Guild Channels | " << event.http_info.body << std::endl;
                }
                else {
                    bool channelverify = false;
                    auto channels = std::get<dpp::channel_map>(event.value);

                    for (auto it : channels) {
                        if (it.second.name == "verify") {
                            channelverify = true;
                            dpp::embed embed = dpp::embed().
                                set_color(0xFFFF00).
                                set_title("RedVsBlue").
                                set_url("").
                                set_author("", "", "").
                                set_image("https://images-wixmp-ed30a86b8c4ca887773594c2.wixmp.com/f/afeef1b9-a594-4c64-ab26-a795b288f8d1/d4ymqjl-50667870-0822-4133-9186-61990ccb9eac.jpg/v1/fill/w_900,h_675,q_75,strp/red_and_blue___yin_yang_by_comasleeper_d4ymqjl-fullview.webp?token=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJ1cm46YXBwOjdlMGQxODg5ODIyNjQzNzNhNWYwZDQxNWVhMGQyNmUwIiwiaXNzIjoidXJuOmFwcDo3ZTBkMTg4OTgyMjY0MzczYTVmMGQ0MTVlYTBkMjZlMCIsIm9iaiI6W1t7ImhlaWdodCI6Ijw9Njc1IiwicGF0aCI6IlwvZlwvYWZlZWYxYjktYTU5NC00YzY0LWFiMjYtYTc5NWIyODhmOGQxXC9kNHltcWpsLTUwNjY3ODcwLTA4MjItNDEzMy05MTg2LTYxOTkwY2NiOWVhYy5qcGciLCJ3aWR0aCI6Ijw9OTAwIn1dXSwiYXVkIjpbInVybjpzZXJ2aWNlOmltYWdlLm9wZXJhdGlvbnMiXX0.YN6qKArKCbyBpfXhHnCmMrZDEcAOwAocIyz63I6jpF4").
                                set_footer(dpp::embed_footer().set_text("Choose a side: ")).
                                set_timestamp(time(NULL));



                            bot.message_create(
                                dpp::message(it.first, embed)
                                .add_component(dpp::component()
                                    .add_component(
                                        dpp::component().set_label("Blue")
                                        .set_style(dpp::cos_primary)
                                        .set_id("blue"))
                                    .add_component(
                                        dpp::component().set_label("Red")
                                        .set_style(dpp::cos_danger)
                                        .set_id("red"))
                                    .add_component(
                                        dpp::component().set_label("Civilian")
                                        .set_style(dpp::cos_secondary)
                                        .set_id("civilian"))
                                )
                            );
                        }
                    }
                    if (!channelverify) {
                        //create verify channel
                    }
                }
            });
    };
}