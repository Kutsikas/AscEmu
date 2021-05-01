-- FIX: Wrong remove of these properties in PR #850
REPLACE INTO `creature_properties` (`entry`, `build`, `killcredit1`, `killcredit2`, `male_displayid`, `female_displayid`, `male_displayid2`, `female_displayid2`, `name`, `subname`, `info_str`, `type_flags`, `type`, `family`, `rank`, `encounter`, `base_attack_mod`, `range_attack_mod`, `leader`, `minlevel`, `maxlevel`, `faction`, `minhealth`, `maxhealth`, `mana`, `scale`, `npcflags`, `attacktime`, `attack_school`, `mindamage`, `maxdamage`, `can_ranged`, `rangedattacktime`, `rangedmindamage`, `rangedmaxdamage`, `respawntime`, `armor`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `combat_reach`, `bounding_radius`, `auras`, `boss`, `money`, `invisibility_type`, `walk_speed`, `run_speed`, `fly_speed`, `extra_a9_flags`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `spell_flags`, `modImmunities`, `isTrainingDummy`, `guardtype`, `summonguard`, `spelldataid`, `vehicleid`, `rooted`, `questitem1`, `questitem2`, `questitem3`, `questitem4`, `questitem5`, `questitem6`, `waypointid`) VALUES
(41200, 15595, 0, 0, 22903, 11686, 0, 0, 'Generic Bunny - PRK', '', '', 1048576, 10, 0, 0, 0, 0, 0, 0, 60, 60, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(44775, 15595, 0, 0, 22903, 11686, 0, 0, 'Generic Bunny - PRK (Large AOI)', '', '', 1048576, 10, 0, 0, 0, 0, 0, 0, 60, 60, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(46464, 15595, 0, 0, 22903, 33005, 0, 0, 'Generic Bunny - PRK - Extra-Small', '', '', 1048576, 10, 0, 0, 0, 0, 0, 0, 60, 60, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(39519, 15595, 0, 0, 22903, 11686, 0, 0, 'Cosmetic Trigger - PRK', '', '', 0, 10, 0, 0, 0, 0, 0, 0, 70, 70, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(35374, 15595, 0, 0, 20570, 11686, 0, 0, 'Generic Trigger LAB - Multiphase', '', '', 0, 10, 0, 0, 0, 0, 0, 0, 60, 60, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(34795, 15595, 0, 0, 1126, 11686, 0, 0, 'Tree Fire Trigger', '', '', 1048576, 10, 0, 0, 0, 0, 0, 0, 1, 1, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(44140, 15595, 0, 0, 22712, 11686, 0, 0, 'PetWait Trigger', '', '', 1048576, 10, 0, 0, 0, 0, 0, 0, 1, 1, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(43718, 15595, 0, 0, 20570, 11686, 0, 0, 'Generic Trigger LAB (Gigantic AOI)', '', '', 0, 10, 0, 0, 0, 0, 0, 0, 60, 60, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(43594, 15595, 0, 0, 22712, 17188, 0, 0, 'Bravo Company Trigger', '', '', 1048576, 10, 0, 0, 0, 0, 0, 0, 1, 1, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(43515, 15595, 0, 0, 22712, 11686, 0, 0, 'Moonbrook Player Trigger', '', '', 1048576, 10, 0, 0, 0, 0, 0, 0, 1, 1, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(41318, 15595, 0, 0, 169, 11686, 0, 0, 'Cave In Triggers', '', '', 1048576, 10, 0, 0, 0, 0, 0, 0, 1, 1, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(50373, 15595, 0, 0, 20570, 25268, 0, 0, 'Deathknell Grave Target', '', '', 0, 10, 0, 0, 0, 0, 0, 0, 1, 1, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '', 0, 0, 0, 2.5, 8, 14, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(40350, 15595, 0, 0, 20570, 11686, 0, 0, 'Generic Trigger LAB', '', '', 0, 10, 0, 0, 0, 0, 0, 0, 60, 60, 35, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, '0', 0, 0, 0, 2.5, 8, 14, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- FIX invisibility_type for freshly added properties
UPDATE `creature_properties` SET `invisibility_type` = 15 WHERE `entry`IN(41200, 44775, 46464, 39519, 35374, 34795, 44140, 43718, 43594, 43515, 41318, 50373, 40350);

-- update world_db_version
REPLACE INTO `world_db_version` VALUES ('68', '20210413-00_creature_properties');