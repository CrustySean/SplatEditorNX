#include "cache.hpp"

using namespace brls::literals;

static const std::string weburl = "https://leanny.github.io/splat2/gear/";
static const std::string weburl_weapons = "https://leanny.github.io/splat2/weapons/";
static const std::string weburl_sub = "https://leanny.github.io/splat2/subspe/";
static const std::string weburl_clothes = "https://leanny.github.io/splat2/gear/";

#define S_WEAPONSPREFIX "Wst_"
#define S_SUBSPREFIX "Wsp_"
#define S_CLOTHESPREFIX "Clt_"
#define S_HEADPREFIX "Hed_"
#define S_SHOESPREFIX "Shs_"

/* Automatically generated trough the weaponsJson.py script. */
std::unordered_map<std::string, int> weapons {
    {"Wst_Shooter_Short_00", 0},
    {"Wst_Shooter_Short_01", 1},
    {"Wst_Shooter_Short_02", 2},
    {"Wst_Shooter_First_00", 10},
    {"Wst_Shooter_First_01", 11},
    {"Wst_Shooter_First_02", 12},
    {"Wst_Shooter_Precision_00", 20},
    {"Wst_Shooter_Precision_01", 21},
    {"Wst_Shooter_Blaze_00", 30},
    {"Wst_Shooter_Blaze_01", 31},
    {"Wst_Shooter_Blaze_02", 32},
    {"Wst_Shooter_Normal_00", 40},
    {"Wst_Shooter_Normal_01", 41},
    {"Wst_Shooter_Normal_02", 42},
    {"Wst_Shooter_Normal_H", 45},
    {"Wst_Shooter_Normal_Oct", 46},
    {"Wst_Shooter_Gravity_00", 50},
    {"Wst_Shooter_Gravity_01", 51},
    {"Wst_Shooter_Gravity_02", 52},
    {"Wst_Shooter_QuickMiddle_00", 60},
    {"Wst_Shooter_QuickMiddle_01", 61},
    {"Wst_Shooter_QuickMiddle_02", 62},
    {"Wst_Shooter_Expert_00", 70},
    {"Wst_Shooter_Expert_01", 71},
    {"Wst_Shooter_Expert_02", 72},
    {"Wst_Shooter_Heavy_00", 80},
    {"Wst_Shooter_Heavy_01", 81},
    {"Wst_Shooter_Long_00", 90},
    {"Wst_Shooter_Long_01", 91},
    {"Wst_Shooter_BlasterShort_00", 200},
    {"Wst_Shooter_BlasterShort_01", 201},
    {"Wst_Shooter_BlasterShort_02", 202},
    {"Wst_Shooter_BlasterMiddle_00", 210},
    {"Wst_Shooter_BlasterMiddle_01", 211},
    {"Wst_Shooter_BlasterMiddle_H", 215},
    {"Wst_Shooter_BlasterLong_00", 220},
    {"Wst_Shooter_BlasterLong_01", 221},
    {"Wst_Shooter_BlasterLong_02", 222},
    {"Wst_Shooter_BlasterLightShort_00", 230},
    {"Wst_Shooter_BlasterLightShort_01", 231},
    {"Wst_Shooter_BlasterLight_00", 240},
    {"Wst_Shooter_BlasterLight_01", 241},
    {"Wst_Shooter_BlasterLight_02", 242},
    {"Wst_Shooter_BlasterLightLong_00", 250},
    {"Wst_Shooter_BlasterLightLong_01", 251},
    {"Wst_Shooter_TripleQuick_00", 300},
    {"Wst_Shooter_TripleQuick_01", 301},
    {"Wst_Shooter_TripleQuick_02", 302},
    {"Wst_Shooter_TripleMiddle_00", 310},
    {"Wst_Shooter_TripleMiddle_01", 311},
    {"Wst_Shooter_TripleMiddle_02", 312},
    {"Wst_Shooter_Flash_00", 400},
    {"Wst_Shooter_Flash_01", 401},
    {"Wst_Roller_Compact_00", 1000},
    {"Wst_Roller_Compact_01", 1001},
    {"Wst_Roller_Normal_00", 1010},
    {"Wst_Roller_Normal_01", 1011},
    {"Wst_Roller_Normal_02", 1012},
    {"Wst_Roller_Normal_H", 1015},
    {"Wst_Roller_Heavy_00", 1020},
    {"Wst_Roller_Heavy_01", 1021},
    {"Wst_Roller_Heavy_02", 1022},
    {"Wst_Roller_Hunter_00", 1030},
    {"Wst_Roller_Hunter_01", 1031},
    {"Wst_Roller_BrushMini_00", 1100},
    {"Wst_Roller_BrushMini_01", 1101},
    {"Wst_Roller_BrushMini_02", 1102},
    {"Wst_Roller_BrushNormal_00", 1110},
    {"Wst_Roller_BrushNormal_01", 1111},
    {"Wst_Roller_BrushNormal_02", 1112},
    {"Wst_Roller_BrushNormal_H", 1115},
    {"Wst_Charger_Quick_00", 2000},
    {"Wst_Charger_Quick_01", 2001},
    {"Wst_Charger_Quick_02", 2002},
    {"Wst_Charger_Normal_00", 2010},
    {"Wst_Charger_Normal_01", 2011},
    {"Wst_Charger_Normal_02", 2012},
    {"Wst_Charger_Normal_H", 2015},
    {"Wst_Charger_NormalScope_00", 2020},
    {"Wst_Charger_NormalScope_01", 2021},
    {"Wst_Charger_NormalScope_02", 2022},
    {"Wst_Charger_Long_00", 2030},
    {"Wst_Charger_Long_01", 2031},
    {"Wst_Charger_LongScope_00", 2040},
    {"Wst_Charger_LongScope_01", 2041},
    {"Wst_Charger_Light_00", 2050},
    {"Wst_Charger_Light_01", 2051},
    {"Wst_Charger_Light_02", 2052},
    {"Wst_Charger_Keeper_00", 2060},
    {"Wst_Charger_Keeper_01", 2061},
    {"Wst_Slosher_Strong_00", 3000},
    {"Wst_Slosher_Strong_01", 3001},
    {"Wst_Slosher_Strong_02", 3002},
    {"Wst_Slosher_Strong_H", 3005},
    {"Wst_Slosher_Diffusion_00", 3010},
    {"Wst_Slosher_Diffusion_01", 3011},
    {"Wst_Slosher_Launcher_00", 3020},
    {"Wst_Slosher_Launcher_01", 3021},
    {"Wst_Slosher_Launcher_02", 3022},
    {"Wst_Slosher_Bathtub_00", 3030},
    {"Wst_Slosher_Bathtub_01", 3031},
    {"Wst_Slosher_Washtub_00", 3040},
    {"Wst_Slosher_Washtub_01", 3041},
    {"Wst_Spinner_Quick_00", 4000},
    {"Wst_Spinner_Quick_01", 4001},
    {"Wst_Spinner_Quick_02", 4002},
    {"Wst_Spinner_Standard_00", 4010},
    {"Wst_Spinner_Standard_01", 4011},
    {"Wst_Spinner_Standard_02", 4012},
    {"Wst_Spinner_Standard_H", 4015},
    {"Wst_Spinner_Hyper_00", 4020},
    {"Wst_Spinner_Hyper_01", 4021},
    {"Wst_Spinner_Downpour_00", 4030},
    {"Wst_Spinner_Downpour_01", 4031},
    {"Wst_Spinner_Serein_00", 4040},
    {"Wst_Spinner_Serein_01", 4041},
    {"Wst_Twins_Short_00", 5000},
    {"Wst_Twins_Short_01", 5001},
    {"Wst_Twins_Short_02", 5002},
    {"Wst_Twins_Normal_00", 5010},
    {"Wst_Twins_Normal_01", 5011},
    {"Wst_Twins_Normal_02", 5012},
    {"Wst_Twins_Normal_H", 5015},
    {"Wst_Twins_Gallon_00", 5020},
    {"Wst_Twins_Gallon_01", 5021},
    {"Wst_Twins_Gallon_02", 5022},
    {"Wst_Twins_Dual_00", 5030},
    {"Wst_Twins_Dual_01", 5031},
    {"Wst_Twins_Stepper_00", 5040},
    {"Wst_Twins_Stepper_01", 5041},
    {"Wst_Umbrella_Normal_00", 6000},
    {"Wst_Umbrella_Normal_01", 6001},
    {"Wst_Umbrella_Normal_H", 6005},
    {"Wst_Umbrella_Wide_00", 6010},
    {"Wst_Umbrella_Wide_01", 6011},
    {"Wst_Umbrella_Wide_02", 6012},
    {"Wst_Umbrella_Compact_00", 6020},
    {"Wst_Umbrella_Compact_01", 6021},
    {"Wst_Umbrella_Compact_02", 6022},
};

std::unordered_map<std::string, int> sub {
   {"Wst_Bomb_Splash", 0},
   {"Wst_Bomb_Suction", 1},
   {"Wst_Bomb_Quick", 2},
   {"Wst_Bomb_Curling", 3},
   {"Wst_Bomb_Robo", 4},
   {"Wst_TimerTrap", 5},
   {"Wst_Sprinkler", 6},
   {"Wst_PoisonFog", 7},
   {"Wst_PointSensor", 8},
   {"Wst_Shield", 9},
   {"Wst_Flag", 10},
   {"Wst_Bomb_Piyo", 11},
   {"Wst_Bomb_Tako", 12},
   {"Wst_Bomb_MissionSplash", 1000},
   {"Wst_Bomb_MissionCurling", 1100},
   {"Wst_Bomb_MissionRobo", 1200},
   {"Wst_Bomb_RivalSplash", 2000},
   {"Wst_Bomb_EnemyOctaSplash", 2010},
   {"Wst_Bomb_EnemyCurling", 2100},
   {"Wst_Bomb_EnemySuction", 2200},
   {"Wst_Bomb_LastBossSplash", 2300},
   {"Wst_Bomb_LastBossSuction", 2400},
   {"Wst_Bomb_RivalOctaSplash", 3000},
   {"Wst_Bomb_RivalOctaQuick", 3100},
   {"Wst_Bomb_RivalOctaCurling", 3200},
   {"Wst_Bomb_RivalOctaRobo", 3300},
   {"Wst_PoisonBall", 4000},
   {"Wst_Bomb_Chase", 4001},
   {"Wst_VictoryClam", 5000},
};

std::unordered_map<std::string, int> specials {
   {"Wst_SuperMissile", 0},
   {"Wst_SuperArmor", 1},
   {"Wst_LauncherSplash", 2},
   {"Wst_LauncherSuction", 3},
   {"Wst_LauncherQuick", 4},
   {"Wst_LauncherCurling", 5},
   {"Wst_LauncherRobo", 6},
   {"Wst_WaterCutter", 7},
   {"Wst_Jetpack", 8},
   {"Wst_SuperLanding", 9},
   {"Wst_RainCloud", 10},
   {"Wst_AquaBall", 11},
   {"Wst_SuperBubble", 12},
   {"Wst_Shachihoko", 13},
   {"Wst_RainCloudEnemy", 15},
   {"Wst_MissileMissilePosition", 16},
   {"Wst_SuperBall", 17},
   {"Wst_SuperStamp", 18},
   {"Wst_BigLaser", 19},
};

std::unordered_map<std::string, int> clt {
   {"FST001", 2},
   {"FST002", 3},
   {"TES000", 1000},
   {"TES001", 1001},
   {"TES003", 1003},
   {"TES004", 1004},
   {"TES005", 1005},
   {"TES006", 1006},
   {"TES007", 1007},
   {"TES008", 1008},
   {"TES009", 1009},
   {"TES010", 1010},
   {"TES011", 1011},
   {"TES012", 1012},
   {"TES013", 1013},
   {"TES014", 1014},
   {"TES015", 1015},
   {"TES016", 1016},
   {"TES017", 1017},
   {"TES018", 1018},
   {"TES019", 1019},
   {"TES020", 1020},
   {"TES021", 1021},
   {"TES022", 1022},
   {"TES023", 1023},
   {"TES026", 1026},
   {"TES027", 1027},
   {"TES028", 1028},
   {"TES029", 1029},
   {"TES030", 1030},
   {"TES031", 1031},
   {"TES032", 1032},
   {"TES033", 1033},
   {"TES034", 1034},
   {"TES035", 1035},
   {"TES036", 1036},
   {"TES037", 1037},
   {"TES038", 1038},
   {"TES039", 1039},
   {"TES040", 1040},
   {"TES041", 1041},
   {"TES042", 1042},
   {"TES043", 1043},
   {"TES044", 1044},
   {"TES045", 1045},
   {"TES046", 1046},
   {"TES047", 1047},
   {"TES048", 1048},
   {"TES049", 1049},
   {"TES050", 1050},
   {"TES051", 1051},
   {"TES052", 1052},
   {"TES053", 1053},
   {"TES054", 1054},
   {"TES055", 1055},
   {"TES056", 1056},
   {"TES057", 1057},
   {"TES058", 1058},
   {"TES059", 1059},
   {"TES060", 1060},
   {"TES061", 1061},
   {"TEL000", 2000},
   {"TEL001", 2001},
   {"TEL002", 2002},
   {"TEL003", 2003},
   {"TEL004", 2004},
   {"TEL005", 2005},
   {"TEL006", 2006},
   {"TEL007", 2007},
   {"TEL008", 2008},
   {"TEL009", 2009},
   {"TEL010", 2010},
   {"TEL011", 2011},
   {"TEL012", 2012},
   {"TEL013", 2013},
   {"TEL014", 2014},
   {"TEL015", 2015},
   {"TEL016", 2016},
   {"TEL017", 2017},
   {"TEL018", 2018},
   {"TEL019", 2019},
   {"TEL020", 2020},
   {"TEL021", 2021},
   {"TEL022", 2022},
   {"TEL023", 2023},
   {"TEL024", 2024},
   {"TLY000", 3000},
   {"TLY001", 3001},
   {"TLY002", 3002},
   {"TLY003", 3003},
   {"TLY004", 3004},
   {"TLY005", 3005},
   {"TLY006", 3006},
   {"TLY007", 3007},
   {"TLY008", 3008},
   {"TLY009", 3009},
   {"TLY010", 3010},
   {"TLY011", 3011},
   {"TLY012", 3012},
   {"TLY013", 3013},
   {"PLO000", 4000},
   {"PLO001", 4001},
   {"PLO002", 4002},
   {"PLO003", 4003},
   {"PLO004", 4004},
   {"PLO005", 4005},
   {"PLO006", 4006},
   {"PLO007", 4007},
   {"PLO008", 4008},
   {"JKT000", 5000},
   {"JKT001", 5001},
   {"JKT002", 5002},
   {"JKT003", 5003},
   {"JKT004", 5004},
   {"JKT005", 5005},
   {"JKT006", 5006},
   {"JKT007", 5007},
   {"JKT008", 5008},
   {"JKT009", 5009},
   {"JKT010", 5010},
   {"JKT011", 5011},
   {"JKT012", 5012},
   {"JKT013", 5013},
   {"JKT014", 5014},
   {"JKT015", 5015},
   {"JKT016", 5016},
   {"JKT017", 5017},
   {"JKT018", 5018},
   {"JKT019", 5019},
   {"JKT020", 5020},
   {"JKT021", 5021},
   {"JKT022", 5022},
   {"JKT023", 5023},
   {"JKT024", 5024},
   {"JKT025", 5025},
   {"JKT026", 5026},
   {"JKT027", 5027},
   {"JKT028", 5028},
   {"JKT029", 5029},
   {"JKT030", 5030},
   {"JKT031", 5031},
   {"JKT032", 5032},
   {"JKT033", 5033},
   {"JKT034", 5034},
   {"JKT035", 5035},
   {"JKT036", 5036},
   {"JKT037", 5037},
   {"JKT038", 5038},
   {"JKT039", 5039},
   {"JKT040", 5040},
   {"JKT041", 5041},
   {"JKT042", 5042},
   {"JKT043", 5043},
   {"JKT044", 5044},
   {"TNK000", 6000},
   {"TNK001", 6001},
   {"TNK003", 6003},
   {"TNK004", 6004},
   {"TNK005", 6005},
   {"TNK006", 6006},
   {"SWT000", 7000},
   {"SWT001", 7001},
   {"SWT002", 7002},
   {"SWT003", 7003},
   {"SWT004", 7004},
   {"SWT005", 7005},
   {"SWT006", 7006},
   {"SWT007", 7007},
   {"SWT008", 7008},
   {"SWT009", 7009},
   {"SWT010", 7010},
   {"SWT011", 7011},
   {"SWT012", 7012},
   {"SWT013", 7013},
   {"SWT014", 7014},
   {"SWT015", 7015},
   {"SHT000", 8000},
   {"SHT001", 8001},
   {"SHT002", 8002},
   {"SHT003", 8003},
   {"SHT004", 8004},
   {"SHT005", 8005},
   {"SHT006", 8006},
   {"SHT007", 8007},
   {"SHT008", 8008},
   {"SHT009", 8009},
   {"SHT010", 8010},
   {"SHT011", 8011},
   {"SHT012", 8012},
   {"SHT013", 8013},
   {"SHT014", 8014},
   {"SHT015", 8015},
   {"SHT017", 8017},
   {"SHT018", 8018},
   {"SHT019", 8019},
   {"SHT020", 8020},
   {"SHT021", 8021},
   {"SHT022", 8022},
   {"SHT023", 8023},
   {"SHT024", 8024},
   {"SHT025", 8025},
   {"SHT026", 8026},
   {"SHT027", 8027},
   {"SHT028", 8028},
   {"SHT029", 8029},
   {"VST000", 9000},
   {"VST001", 9001},
   {"VST002", 9002},
   {"VST003", 9003},
   {"VST004", 9004},
   {"VST005", 9005},
   {"VST007", 9007},
   {"VST008", 9008},
   {"VST009", 9009},
   {"PRK000", 10000},
   {"PRK001", 10001},
   {"PRK002", 10002},
   {"PRK004", 10004},
   {"PRK005", 10005},
   {"PRK006", 10006},
   {"PRK007", 10007},
   {"PRK008", 10008},
   {"PRK009", 10009},
   {"PRK010", 10010},
   {"PRK011", 10011},
   {"COP100", 21000},
   {"COP101", 21001},
   {"COP102", 21002},
   {"COP103", 21003},
   {"COP104", 21004},
   {"COP105", 21005},
   {"COP106", 21006},
   {"COP107", 21007},
   {"COP108", 21008},
   {"COP109", 21009},
   {"COP110", 21010},
   {"CRC000", 22000},
   {"HAP002", 23000},
   {"AMB000", 25000},
   {"AMB001", 25001},
   {"AMB002", 25002},
   {"AMB003", 25003},
   {"AMB004", 25004},
   {"AMB005", 25005},
   {"AMB006", 25006},
   {"AMB007", 25007},
   {"AMB008", 25008},
   {"AMB009", 25009},
   {"AMB010", 25010},
   {"HAP001", 26000},
   {"MSN000", 27000},
   {"MSN004", 27004},
   {"MSN101", 27101},
   {"MSN104", 27104},
   {"MSN105", 27105},
   {"MSN106", 27106},
};

std::unordered_map<std::string, int> heads {
   {"Hed_FST000", 1},
   {"Hed_CAP000", 1000},
   {"Hed_CAP001", 1001},
   {"Hed_CAP002", 1002},
   {"Hed_CAP003", 1003},
   {"Hed_CAP004", 1004},
   {"Hed_CAP005", 1005},
   {"Hed_CAP006", 1006},
   {"Hed_CAP007", 1007},
   {"Hed_CAP008", 1008},
   {"Hed_CAP009", 1009},
   {"Hed_CAP010", 1010},
   {"Hed_CAP011", 1011},
   {"Hed_CAP012", 1012},
   {"Hed_CAP014", 1014},
   {"Hed_CAP018", 1018},
   {"Hed_CAP019", 1019},
   {"Hed_CAP020", 1020},
   {"Hed_CAP021", 1021},
   {"Hed_CAP023", 1023},
   {"Hed_CAP024", 1024},
   {"Hed_CAP025", 1025},
   {"Hed_CAP026", 1026},
   {"Hed_CAP027", 1027},
   {"Hed_NCP000", 2000},
   {"Hed_NCP001", 2001},
   {"Hed_NCP002", 2002},
   {"Hed_NCP003", 2003},
   {"Hed_NCP004", 2004},
   {"Hed_NCP005", 2005},
   {"Hed_NCP006", 2006},
   {"Hed_NCP008", 2008},
   {"Hed_NCP009", 2009},
   {"Hed_NCP010", 2010},
   {"Hed_NCP011", 2011},
   {"Hed_EYE000", 3000},
   {"Hed_EYE001", 3001},
   {"Hed_EYE002", 3002},
   {"Hed_EYE003", 3003},
   {"Hed_EYE004", 3004},
   {"Hed_EYE005", 3005},
   {"Hed_EYE006", 3006},
   {"Hed_EYE007", 3007},
   {"Hed_EYE008", 3008},
   {"Hed_EYE009", 3009},
   {"Hed_EYE010", 3010},
   {"Hed_EYE011", 3011},
   {"Hed_EYE012", 3012},
   {"Hed_EYE013", 3013},
   {"Hed_EYE014", 3014},
   {"Hed_EYE015", 3015},
   {"Hed_EYE016", 3016},
   {"Hed_EYE017", 3017},
   {"Hed_EYE018", 3018},
   {"Hed_EYE019", 3019},
   {"Hed_EYE020", 3020},
   {"Hed_HAT000", 4000},
   {"Hed_HAT001", 4001},
   {"Hed_HAT002", 4002},
   {"Hed_HAT003", 4003},
   {"Hed_HAT004", 4004},
   {"Hed_HAT005", 4005},
   {"Hed_HAT006", 4006},
   {"Hed_HAT007", 4007},
   {"Hed_HAT008", 4008},
   {"Hed_HAT009", 4009},
   {"Hed_HAT010", 4010},
   {"Hed_HAT011", 4011},
   {"Hed_HAT012", 4012},
   {"Hed_HAT013", 4013},
   {"Hed_HAT014", 4014},
   {"Hed_HDP000", 5000},
   {"Hed_HDP001", 5001},
   {"Hed_HDP002", 5002},
   {"Hed_HDP003", 5003},
   {"Hed_HDP004", 5004},
   {"Hed_HDP005", 5005},
   {"Hed_HDP006", 5006},
   {"Hed_VIS000", 6000},
   {"Hed_VIS001", 6001},
   {"Hed_VIS002", 6002},
   {"Hed_VIS003", 6003},
   {"Hed_VIS004", 6004},
   {"Hed_MET000", 7000},
   {"Hed_MET002", 7002},
   {"Hed_MET004", 7004},
   {"Hed_MET005", 7005},
   {"Hed_MET006", 7006},
   {"Hed_MET007", 7007},
   {"Hed_MET008", 7008},
   {"Hed_MET009", 7009},
   {"Hed_MET010", 7010},
   {"Hed_MET011", 7011},
   {"Hed_MSK000", 8000},
   {"Hed_MSK001", 8001},
   {"Hed_MSK002", 8002},
   {"Hed_MSK003", 8003},
   {"Hed_MSK004", 8004},
   {"Hed_MSK005", 8005},
   {"Hed_MSK006", 8006},
   {"Hed_MSK007", 8007},
   {"Hed_MSK008", 8008},
   {"Hed_MSK009", 8009},
   {"Hed_MSK010", 8010},
   {"Hed_MSK011", 8011},
   {"Hed_MSK012", 8012},
   {"Hed_MSK013", 8013},
   {"Hed_HBD001", 9001},
   {"Hed_HBD002", 9002},
   {"Hed_HBD003", 9003},
   {"Hed_HBD004", 9004},
   {"Hed_HBD005", 9005},
   {"Hed_HBD007", 9007},
   {"Hed_HBD008", 9008},
   {"Hed_ACC001", 10000},
   {"Hed_COP100", 21000},
   {"Hed_COP101", 21001},
   {"Hed_COP102", 21002},
   {"Hed_COP103", 21003},
   {"Hed_COP104", 21004},
   {"Hed_COP105", 21005},
   {"Hed_COP106", 21006},
   {"Hed_COP107", 21007},
   {"Hed_COP108", 21008},
   {"Hed_COP109", 21009},
   {"Hed_CRC000", 22000},
   {"Hed_HAP000", 24000},
   {"Hed_HAP001", 24001},
   {"Hed_HAP002", 24002},
   {"Hed_HAP003", 24003},
   {"Hed_HAP004", 24004},
   {"Hed_HAP005", 24005},
   {"Hed_HAP006", 24006},
   {"Hed_HAP007", 24007},
   {"Hed_HAP008", 24008},
   {"Hed_HAP009", 24009},
   {"Hed_HAP010", 24010},
   {"Hed_HAP011", 24011},
   {"Hed_HAP012", 24012},
   {"Hed_HAP013", 24013},
   {"Hed_HAP014", 24014},
   {"Hed_HAP015", 24015},
   {"Hed_AMB000", 25000},
   {"Hed_AMB001", 25001},
   {"Hed_AMB002", 25002},
   {"Hed_AMB003", 25003},
   {"Hed_AMB004", 25004},
   {"Hed_AMB005", 25005},
   {"Hed_AMB006", 25006},
   {"Hed_AMB007", 25007},
   {"Hed_AMB008", 25008},
   {"Hed_AMB009", 25009},
   {"Hed_AMB010", 25010},
   {"Hed_MSN000", 27000},
   {"Hed_MSN004", 27004},
   {"Hed_MSN101", 27101},
   {"Hed_MSN104", 27104},
   {"Hed_MSN105", 27105},
   {"Hed_MSN106", 27106},
   {"Hed_MSN107", 27107},
   {"Hed_MSN108", 27108},
};

std::unordered_map<std::string, int> shs {
   {"Shs_FST000", 1},
   {"Shs_SLO000", 1000},
   {"Shs_SLO001", 1001},
   {"Shs_SLO002", 1002},
   {"Shs_SLO003", 1003},
   {"Shs_SLO004", 1004},
   {"Shs_SLO005", 1005},
   {"Shs_SLO006", 1006},
   {"Shs_SLO007", 1007},
   {"Shs_SLO008", 1008},
   {"Shs_SLO009", 1009},
   {"Shs_SLO010", 1010},
   {"Shs_SLO011", 1011},
   {"Shs_SLO012", 1012},
   {"Shs_SLO013", 1013},
   {"Shs_SLO014", 1014},
   {"Shs_SLO015", 1015},
   {"Shs_SLO016", 1016},
   {"Shs_SLO017", 1017},
   {"Shs_SLO018", 1018},
   {"Shs_SLO019", 1019},
   {"Shs_SLO020", 1020},
   {"Shs_SHI000", 2000},
   {"Shs_SHI001", 2001},
   {"Shs_SHI002", 2002},
   {"Shs_SHI003", 2003},
   {"Shs_SHI004", 2004},
   {"Shs_SHI005", 2005},
   {"Shs_SHI006", 2006},
   {"Shs_SHI008", 2008},
   {"Shs_SHI009", 2009},
   {"Shs_SHI010", 2010},
   {"Shs_SHI011", 2011},
   {"Shs_SHI012", 2012},
   {"Shs_SHI013", 2013},
   {"Shs_SHI014", 2014},
   {"Shs_SHI015", 2015},
   {"Shs_SHI016", 2016},
   {"Shs_SHI017", 2017},
   {"Shs_SHI018", 2018},
   {"Shs_SHI019", 2019},
   {"Shs_SHI020", 2020},
   {"Shs_SHI021", 2021},
   {"Shs_SHI022", 2022},
   {"Shs_SHI023", 2023},
   {"Shs_SHI024", 2024},
   {"Shs_SHI025", 2025},
   {"Shs_SHI026", 2026},
   {"Shs_SHI027", 2027},
   {"Shs_SHI028", 2028},
   {"Shs_SHI029", 2029},
   {"Shs_SHI030", 2030},
   {"Shs_SHI031", 2031},
   {"Shs_SHI032", 2032},
   {"Shs_SHI033", 2033},
   {"Shs_SHI034", 2034},
   {"Shs_SHI035", 2035},
   {"Shs_SHI036", 2036},
   {"Shs_SHI037", 2037},
   {"Shs_SHI038", 2038},
   {"Shs_SHI039", 2039},
   {"Shs_SHI040", 2040},
   {"Shs_SHI041", 2041},
   {"Shs_SHT000", 3000},
   {"Shs_SHT001", 3001},
   {"Shs_SHT002", 3002},
   {"Shs_SHT003", 3003},
   {"Shs_SHT004", 3004},
   {"Shs_SHT005", 3005},
   {"Shs_SHT006", 3006},
   {"Shs_SHT007", 3007},
   {"Shs_SHT008", 3008},
   {"Shs_SHT009", 3009},
   {"Shs_SHT010", 3010},
   {"Shs_SHT011", 3011},
   {"Shs_SHT012", 3012},
   {"Shs_SHT013", 3013},
   {"Shs_SHT014", 3014},
   {"Shs_SHT015", 3015},
   {"Shs_SHT016", 3016},
   {"Shs_SHT017", 3017},
   {"Shs_SHT018", 3018},
   {"Shs_SHT019", 3019},
   {"Shs_SDL000", 4000},
   {"Shs_SDL001", 4001},
   {"Shs_CFS000", 4002},
   {"Shs_CFS001", 4003},
   {"Shs_SDL003", 4007},
   {"Shs_SDL004", 4008},
   {"Shs_SDL005", 4009},
   {"Shs_SDL006", 4010},
   {"Shs_SDL007", 4011},
   {"Shs_SDL008", 4012},
   {"Shs_SDL009", 4013},
   {"Shs_TRS000", 5000},
   {"Shs_TRS001", 5001},
   {"Shs_TRS002", 5002},
   {"Shs_BOT000", 6000},
   {"Shs_BOT001", 6001},
   {"Shs_BOT002", 6002},
   {"Shs_BOT003", 6003},
   {"Shs_BOT004", 6004},
   {"Shs_BOT005", 6005},
   {"Shs_BOT006", 6006},
   {"Shs_BOT007", 6007},
   {"Shs_BOT008", 6008},
   {"Shs_BOT009", 6009},
   {"Shs_BOT010", 6010},
   {"Shs_BOT011", 6011},
   {"Shs_BOT012", 6012},
   {"Shs_BOT013", 6013},
   {"Shs_BOT014", 6014},
   {"Shs_BOT015", 6015},
   {"Shs_BOT016", 6016},
   {"Shs_BOT017", 6017},
   {"Shs_BOT018", 6018},
   {"Shs_SLP000", 7000},
   {"Shs_SLP001", 7001},
   {"Shs_SLP002", 7002},
   {"Shs_SLP003", 7003},
   {"Shs_LTS000", 8000},
   {"Shs_LTS001", 8001},
   {"Shs_LTS002", 8002},
   {"Shs_LTS003", 8003},
   {"Shs_LTS004", 8004},
   {"Shs_LTS005", 8005},
   {"Shs_LTS006", 8006},
   {"Shs_LTS007", 8007},
   {"Shs_LTS008", 8008},
   {"Shs_LTS010", 8010},
   {"Shs_LTS011", 8011},
   {"Shs_LTS009", 8009},
   {"Shs_LTS012", 8012},
   {"Shs_COP101", 21001},
   {"Shs_COP102", 21002},
   {"Shs_COP103", 21003},
   {"Shs_COP104", 21004},
   {"Shs_COP105", 21005},
   {"Shs_COP106", 21006},
   {"Shs_CRC000", 22000},
   {"Shs_HAP000", 23000},
   {"Shs_HAP001", 23001},
   {"Shs_HAP002", 23002},
   {"Shs_HAP003", 23003},
   {"Shs_HAP004", 23004},
   {"Shs_HAP005", 23005},
   {"Shs_HAP006", 23006},
   {"Shs_HAP007", 23007},
   {"Shs_AMB000", 25000},
   {"Shs_AMB001", 25001},
   {"Shs_AMB002", 25002},
   {"Shs_AMB003", 25003},
   {"Shs_AMB004", 25004},
   {"Shs_AMB005", 25005},
   {"Shs_AMB006", 25006},
   {"Shs_AMB007", 25007},
   {"Shs_AMB008", 25008},
   {"Shs_AMB009", 25009},
   {"Shs_AMB010", 25010},
   {"Shs_MSN000", 27000},
   {"Shs_MSN004", 27004},
   {"Shs_MSN101", 27101},
   {"Shs_MSN104", 27104},
   {"Shs_MSN105", 27105},
   {"Shs_MSN106", 27106},
};
/* End of the generated code. */

void Cache::DownloadImage(const std::string& url, const std::string& path) {
    try {
        Downloader* dwfile = new Downloader();
        brls::Logger::info("Downloading image... ({})", url);

        dwfile->DownloadFile(url, path);
        brls::Logger::info("Image downloaded and saved to {}", path);
        
        delete dwfile;
    } catch (std::exception& exc) {
        brls::Logger::error("Exception while downloading icon, {}", exc.what());
    }
}

void Cache::CreateDirectory() {
    if (!std::filesystem::exists(g_defaultPath + "/Cache")) {
        std::filesystem::create_directories(g_defaultPath + "/Cache");
    }
}

void Cache::Init() {
    Cache::CreateDirectory();
}

std::string Cache::isInRangeWeapons(u32 id) {
    std::string path;
    union {
        s32 i;
        u32 u;
    } a;

    a.u = id;

    try {
        for (auto& i : weapons) {
            if (i.second == a.i) {
                Cache::tryGetImage("weapons", i.first, i.second);
                path = g_defaultPath + "/Cache/" + i.first + ".png";
            }
        }

        if (path == "") {
            brls::Logger::info("Not found in range");
            path = "sdmc:/SplatEditor/Cache/unknown.png";
        }
        
    } catch (std::exception& exc) {
        brls::Logger::error("Exception while checking weapons, {}", exc.what());
    }

    return path;
}

std::string Cache::isInRangeSub(u32 id) {
    std::string path;
    union {
        int32_t i; 
        uint32_t u;
    } a;

    a.u = id;
    brls::Logger::info("Value: Uint: {} || Int: {} ", a.u, a.i);

    try {
        for (auto& i : sub) {
            if (i.second == a.i) {
                path = g_defaultPath + "/Cache/" + i.first + ".png";
            }
        }

        if (path == "") {
            brls::Logger::info("Not found in range");
            path = "sdmc:/SplatEditor/Cache/unknown.png";
        }
        
    } catch (std::exception& exc) {
        brls::Logger::error("Exception while checking weapons, {}", exc.what());
    }

    return path;
}

std::string Cache::isInRangeSpecials(u32 id) {
    std::string path;
    union {
        int32_t i; 
        uint32_t u;
    } a;

    a.u = id;
    brls::Logger::info("Value: Uint: {} || Int: {} ", a.u, a.i);

    try {
        for (auto& i : specials) {
            if (i.second == a.i) {
                path = g_defaultPath + "/Cache/" + i.first + ".png";
            }
        }

        if (path == "") {
            brls::Logger::info("Not found in range");
            path = "sdmc:/SplatEditor/Cache/unknown.png";
        }
        
    } catch (std::exception& exc) {
        brls::Logger::error("Exception while checking weapons, {}", exc.what());
    }

    return path;
}

std::string Cache::isInRangeClothes(u32 id) {
    std::string path;
    union {
        int32_t i; 
        uint32_t u;
    } a;

    a.u = id;
    brls::Logger::info("Value: Uint: {} || Int: {} ", a.u, a.i);

    try {
        for (auto& i : clt) {
            if (i.second == a.i) {
                path = g_defaultPath + "/Cache/" + i.first + ".png";
            }
        }

        if (path == "") {
            brls::Logger::info("Not found in range");
            path = "sdmc:/SplatEditor/Cache/unknown.png";
        }
        
    } catch (std::exception& exc) {
        brls::Logger::error("Exception while checking weapons, {}", exc.what());
    }

    return path;
}

std::string Cache::isInRangeHead(u32 id) {
    std::string path;
    union {
        int32_t i; 
        uint32_t u;
    } a;

    a.u = id;
    brls::Logger::info("Value: Uint: {} || Int: {} ", a.u, a.i);

    try {
        for (auto& i : heads) {
            if (i.second == a.i) {
                path = g_defaultPath + "/Cache/" + i.first + ".png";
            }
        }

        if (path == "") {
            brls::Logger::info("Not found in range");
            path = "sdmc:/SplatEditor/Cache/unknown.png";
        }
        
    } catch (std::exception& exc) {
        brls::Logger::error("Exception while checking weapons, {}", exc.what());
    }

    return path;
}

std::string Cache::isInRangeShoes(u32 id) {
    std::string path;
    union {
        int32_t i; 
        uint32_t u;
    } a;

    a.u = id;
    brls::Logger::info("Value: Uint: {} || Int: {} ", a.u, a.i);

    try {
        for (auto& i : shs) {
            if (i.second == a.i) {
                path = g_defaultPath + "/Cache/" + i.first + ".png";
            }
        }

        if (path == "") {
            brls::Logger::info("Not found in range");
            path = "sdmc:/SplatEditor/Cache/unknown.png";
        }
        
    } catch (std::exception& exc) {
        brls::Logger::error("Exception while checking weapons, {}", exc.what());
    }

    return path;
}

void Cache::DownloadNecessary() {
    brls::Logger::info("Downloading Images...");

    try {
        Downloader* dwfile = new Downloader();

        dwfile->DownloadFile("https://raw.githubusercontent.com/Leanny/leanny.github.io/master/splat2/weapons/OctWeaponIcon_02.png", "sdmc:/SplatEditor/Cache/OctWeaponIcon_02.png");
        dwfile->DownloadFile("https://cdn.wikimg.net/en/splatoonwiki/images/thumb/9/91/S2_Icon_Cash.png/48px-S2_Icon_Cash.png", "sdmc:/SplatEditor/Cache/48px-S2_Icon_Cash.png");
        dwfile->DownloadFile("https://cdn.wikimg.net/en/splatoonwiki/images/c/cf/S_Icon_Super_Sea_Snail.png", "sdmc:/SplatEditor/Cache/S_Icon_Super_Sea_Snail.png");
        dwfile->DownloadFile("https://www.pngall.com/wp-content/uploads/9/Black-Star-PNG-Free-Image.png", "sdmc:/SplatEditor/Cache/Black-Star-PNG-Free-Image.png");
        dwfile->DownloadFile("https://raw.githubusercontent.com/Leanny/leanny.github.io/master/splat2/weapons/questionmark2.png", "sdmc:/SplatEditor/Cache/questionmark2.png");

        rename("sdmc:/SplatEditor/Cache/OctWeaponIcon_02.png", "sdmc:/SplatEditor/Cache/unknown.png");
        rename("sdmc:/SplatEditor/Cache/48px-S2_Icon_Cash.png", "sdmc:/SplatEditor/Cache/money.png");
        rename("sdmc:/SplatEditor/Cache/S_Icon_Super_Sea_Snail.png", "sdmc:/SplatEditor/Cache/sseasnails.png");
        rename("sdmc:/SplatEditor/Cache/Black-Star-PNG-Free-Image.png", "sdmc:/SplatEditor/Cache/star.png");
        rename("sdmc:/SplatEditor/Cache/questionmark2.png", "sdmc:/SplatEditor/Cache/test.png");

        delete dwfile;

    } catch (std::exception& exc) {
        brls::Logger::error("Exception while downloading icon, {}", exc.what());
    }
}

bool Cache::tryGetImage(const std::string& type, const std::string& weapon, u32 id) {
    if (!Utilities::HasWifi()) {
        brls::Logger::error("No Wifi");
        return false;
    }

    std::ifstream ifs;
    ifs.open(std::string(BRLS_RESOURCES) + Utilities::format_string("download/d_%s.json", type.c_str()));
    if (!ifs.is_open()) {
        brls::Logger::error("Could not open d_%s.json", type.c_str());
        return false;
    }

    try {
        using json = nlohmann::json;
        json j;
        ifs >> j;

        auto p = Utilities::format_string("https://leanny.github.io/splat2/%s/%s.png", type.c_str(), weapon.c_str());
        brls::Logger::info("Downloading {}", p);

        for (auto& i : j) {
            brls::Logger::info("Checking {}", i["url"].get<std::string>());
            if (i["url"].get<std::string>() == p) {
                brls::Logger::info("found!");

                if (std::filesystem::exists(i["sdpath"].get<std::string>())) {
                    brls::Logger::info("already exists");
                    return true;
                }

                Cache::DownloadImage(i["url"].get<std::string>(), i["sdpath"].get<std::string>());
            }
        }

        ifs.close();

    } catch (std::exception& exc) {
        brls::Logger::error("Exception while checking weapons, {}", exc.what());
        return false;
    }

    return false;
}
