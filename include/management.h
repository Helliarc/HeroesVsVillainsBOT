#pragma once
#include <dpp/dpp.h>

namespace RVB_m {

	void roleCheck(dpp::cluster& bot, dpp::snowflake& GID);
	void categoryCreate(dpp::cluster& bot, dpp::snowflake GID);
	void openInvite(dpp::cluster& bot, dpp::snowflake GID);
	void roleClick(dpp::cluster& bot, dpp::button_click_t event);
	
}
