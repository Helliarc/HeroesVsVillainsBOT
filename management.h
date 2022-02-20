#pragma once

/*All functions here forward declare the specific management function definitions to manage the RVB BOT.*/

namespace RVB_m {

	void updateGuildRoles(dpp::cluster& bot, dpp::snowflake GID, std::unordered_map<dpp::snowflake, dpp::role_map>& connectedGuildRoles);

	//void buildChannels(dpp::cluster& bot, dpp::snowflake GID);

	bool buildRole(dpp::cluster& bot, dpp::snowflake GID, std::string roleName);
}