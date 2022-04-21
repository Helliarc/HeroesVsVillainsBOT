#pragma once
#include <string>
#include <dpp/dpp.h>

namespace RVB_e {
	/*Stored Role names to allow changing of names at a later time*/
	std::string nameRoleRed = "Villain";
	std::string nameRoleBlue = "Hero";
	std::string nameRoleNeutral = "Civilian";

	/*There are 3 BASE roles that belong to this BOT(Red/Blue/Neutral)*/
	dpp::role roleRed = dpp::role().set_name(nameRoleRed).set_color(0xd50000);
	dpp::role roleBlue = dpp::role().set_name(nameRoleBlue).set_color(0x1565c0);
	dpp::role roleNeutral = dpp::role().set_name(nameRoleNeutral).set_color(0xfbce07);

	/*There are 3 categories that belong to this BOT(Red/Blue/faction), and each category has 2 channels(general/command_center)*/
	dpp::channel categoryRed = dpp::channel().set_name(nameRoleRed + " lair").set_flags(dpp::CHANNEL_CATEGORY).set_position(3);
	dpp::channel categoryBlue = dpp::channel().set_name(nameRoleBlue + " base").set_flags(dpp::CHANNEL_CATEGORY).set_position(3);
	dpp::channel categoryHome = dpp::channel().set_name(nameRoleNeutral + " home").set_flags(dpp::CHANNEL_CATEGORY).set_position(3);

	/*There are 2 channels specifically created for BOT interaction(General/command center), guild moderators can add any additional channels that they want*/
	dpp::channel channelGeneral = dpp::channel().set_name("general").set_flags(dpp::CHANNEL_TEXT).set_topic("General Discussion                 ***DO NOT EDIT/DELETE THIS CHANNEL***  This channel is required for the Faction BOT to operate");
	dpp::channel channelCommand = dpp::channel().set_name("command-center").set_flags(dpp::CHANNEL_TEXT).set_topic("So many CHOICES!                 ***DO NOT EDIT/DELETE THIS CHANNEL***  This channel is required for the Faction BOT to operate");


}
