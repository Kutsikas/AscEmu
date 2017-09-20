--
-- Move more Data to db
--

REPLACE INTO `gossip_menu` (`gossip_menu`, `text_id`, `Comment`) VALUES
	(1095, 50000, 'DalaranGuard');

REPLACE INTO `gossip_menu_items` (`id`, `item_order`, `menu_option`, `icon`, `point_of_interest`, `next_gossip_menu`, `next_gossip_text`) VALUES
	(1095, 1, 183, 0, 0, 1099, 13976),
	(1095, 2, 164, 0, 0, 1105, 14010),
	(1095, 3, 151, 0, 0, 1108, 14007),
	(1095, 4, 182, 0, 434, 0, 14003),
	(1095, 5, 172, 0, 0, 1105, 13977),
	(1095, 6, 233, 0, 0, 1105, 13977),
	(1095, 7, 153, 0, 435, 0, 10086),
	(1095, 8, 158, 0, 436, 0, 10095),
	(1095, 9, 160, 0, 0, 1112, 14002),
	(1095, 10, 180, 0, 493, 0, 14004),
	(1095, 11, 162, 0, 0, 1115, 10090),
	(1095, 12, 232, 0, 0, 1119, 10056),
	(1095, 13, 169, 0, 437, 0, 10083),
	(1095, 14, 176, 0, 0, 1122, 10082),
	(1095, 15, 184, 0, 0, 1132, 10173),
	(1099, 15, 253, 0, 438, 0, 13961),
	(1099, 16, 254, 0, 439, 0, 13960),
	(1099, 17, 255, 0, 440, 0, 13969),
	(1105, 18, 256, 0, 441, 0, 13973),
	(1105, 19, 258, 0, 442, 0, 13972),
	(1108, 20, 260, 0, 443, 0, 14005),
	(1108, 21, 261, 0, 444, 0, 14006),
	(1108, 22, 262, 0, 445, 0, 13974),
	(1112, 24, 257, 0, 446, 0, 13992),
	(1112, 25, 259, 0, 447, 0, 13993),
	(1112, 26, 262, 0, 448, 0, 13974),
	(1115, 3, 151, 0, 0, 1108, 14007),
	(1115, 9, 160, 0, 0, 1112, 14002),
	(1115, 74, 263, 0, 490, 0, 14009),
	(1119, 18, 256, 0, 441, 0, 13973),
	(1119, 19, 258, 0, 442, 0, 13972),
	(1119, 22, 262, 0, 445, 0, 13974),
	(1119, 27, 264, 0, 449, 0, 13971),
	(1119, 28, 265, 0, 450, 0, 13970),
	(1119, 29, 266, 0, 451, 0, 13980),
	(1119, 30, 267, 0, 452, 0, 13968),
	(1119, 31, 268, 0, 453, 0, 13967),
	(1119, 32, 269, 0, 454, 0, 13966),
	(1119, 33, 270, 0, 455, 0, 13965),
	(1119, 34, 230, 0, 456, 0, 14174),
	(1119, 74, 263, 0, 490, 0, 14009),
	(1122, 35, 175, 0, 0, 1119, 14018),
	(1122, 36, 96, 0, 457, 0, 13999),
	(1122, 37, 178, 0, 0, 1125, 13996),
	(1122, 76, 95, 0, 492, 0, 60059),
	(1125, 52, 81, 0, 469, 0, 13995),
	(1125, 53, 82, 0, 470, 0, 13994),
	(1125, 54, 83, 0, 0, 1128, 13991),
	(1125, 55, 84, 0, 471, 0, 13990),
	(1125, 56, 85, 0, 472, 0, 13989),
	(1125, 57, 86, 0, 473, 0, 13988),
	(1125, 58, 87, 0, 474, 0, 13987),
	(1125, 59, 88, 0, 475, 0, 13986),
	(1125, 60, 89, 0, 476, 0, 13985),
	(1125, 61, 94, 0, 477, 0, 13984),
	(1125, 62, 90, 0, 478, 0, 13982),
	(1125, 63, 91, 0, 479, 0, 13983),
	(1125, 64, 92, 0, 482, 0, 13982),
	(1125, 65, 93, 0, 481, 0, 13981),
	(1128, 24, 257, 0, 446, 0, 13992),
	(1128, 25, 259, 0, 447, 0, 13993),
	(1132, 38, 271, 0, 0, 1135, 14117),
	(1132, 39, 272, 0, 458, 0, 14112),
	(1132, 40, 273, 0, 0, 1105, 14108),
	(1132, 41, 274, 0, 459, 0, 10159),
	(1132, 42, 275, 0, 460, 0, 14106),
	(1132, 43, 276, 0, 461, 0, 14105),
	(1132, 44, 277, 0, 462, 0, 13984),
	(1132, 45, 278, 0, 463, 0, 14103),
	(1132, 46, 279, 0, 464, 0, 14102),
	(1132, 47, 280, 0, 465, 0, 14104),
	(1132, 48, 281, 0, 466, 0, 14100),
	(1132, 49, 283, 0, 467, 0, 14110),
	(1132, 50, 284, 0, 0, 1139, 14113),
	(1132, 51, 285, 0, 468, 0, 14095),
	(1132, 52, 282, 0, 461, 0, 14105),
	(1135, 66, 286, 0, 482, 0, 14112),
	(1135, 67, 287, 0, 483, 0, 14111),
	(1135, 68, 288, 0, 484, 0, 14111),
	(1135, 69, 289, 0, 485, 0, 14109),
	(1135, 70, 290, 0, 486, 0, 14109),
	(1139, 71, 291, 0, 487, 0, 14098),
	(1139, 72, 292, 0, 488, 0, 14097),
	(1139, 73, 293, 0, 489, 0, 14096);

--
-- Update world_db_version
--
UPDATE `world_db_version` SET `LastUpdate` = '2017-09-20_01_gossip_menu_tables' WHERE `LastUpdate` = '2017-09-18_02_gossip_menu_tables';