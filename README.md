#Status of Project
-------------------------------------------------------
1. Working through DB Schema to:

  A. Track BOT user stats (Health, Alignment, Time-as(Alignment), Options(receive PMs, Pings, Notifications))
  
  B. Track Guild stats (Guild alignment weight(Finding Faction-only guilds), # of Guilds with BOT active, Average AGE of Guilds(What's the reach depth))
  
  C. Track Alignment stats (Health, Member count, Options, Buffs/Debuffs)
  
  
2. Design planning BOT to interact with DB by:
  A. Maintaining User Roles (Users will retain roles when moving to another server, prevents signing up for both factions under the same log-in)
  B. Initiating User role-selection (Limit when users can change roles(Once per week, pending feedback)
  C. Retaining User Roles (When user quits guild they cannot re-join and choose a faction immediately.  Users must opt for "Immediate Removal" from DB, at which time their User ID is placed on a hold for (30 days, pending feedback) until they can pick a faction again.
  
 3. Changing the Channel Layouts:
  A. No longer creating the Faction Categories
  B. Creating 2 channels under 1 Category (Category is ${BOT_NAME}, Channel names are ${CHANNEL_ONE} and ${CHANNEL_TWO})
  C. Need fancy presentation, to make it look "pretty"
  D. ${CHANNEL_ONE} does not require a role selected, this is the channel where users select a role and get messages from the BOT. 
  E. ${CHANNEL_TWO} default requires a role unless Guild Admin decides otherwise. 
  F. Roles remain as-is, 3 roles: 
    1. ${ROLE1} = Hero
    2. ${ROLE2} = Villain
    3. ${ROLE3} = Civilian  # Civilian Role is the retainer role for users who go "AFK" or who don't wish to participate directly, they maintain perks of the system but cannot interact in faction events.




# Immediate Feedback (Please update as you find, or fix yourself!)
-------------------------------------------------------
- Comments Comments Comments!!!!!!!!

- My environmental global variables are in a .h instead of a file, but I've designed it so that it should be relatively easy to implement into a file.

- I need to refine the embed to be designed better, a better picture source and the text displays on the embed, I just wanted an embed to show.

- I have some naming conventions I need to go through and clarify, I use hero/villain interchangeably with blue/red.  I was attempting to design around allowing guilds to make their own faction names, but without the benefit of SQL knowledge/experience, I need to hold off on that for a while, so I'm converting all of my verbiage to hero/villain from red/blue.
