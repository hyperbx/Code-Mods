using System.Numerics;
using System.Runtime.InteropServices;

public class HeightFieldConfigClass
{
    public enum LayerType : sbyte
    {
        LAYER_NONE = 0,
        LAYER_SOLID = 1,
        LAYER_LIQUID = 2,
        LAYER_THROUGH = 3,
        LAYER_CAMERA = 4,
        LAYER_SOLID_ONEWAY = 5,
        LAYER_SOLID_THROUGH = 6,
        LAYER_SOLID_TINY = 7,
        LAYER_SOLID_DETAIL = 8,
        LAYER_LEAF = 9,
        LAYER_LAND = 10,
        LAYER_RAYBLOCK = 11,
        LAYER_EVENT = 12,
        LAYER_RESERVED13 = 13,
        LAYER_RESERVED14 = 14,
        LAYER_PLAYER = 15,
        LAYER_ENEMY = 16,
        LAYER_ENEMY_BODY = 17,
        LAYER_GIMMICK = 18,
        LAYER_DYNAMICS = 19,
        LAYER_RING = 20,
        LAYER_CHARACTER_CONTROL = 21,
        LAYER_PLAYER_ONLY = 22,
        LAYER_DYNAMICS_THROUGH = 23,
        LAYER_ENEMY_ONLY = 24,
        LAYER_SENSOR_PLAYER = 25,
        LAYER_SENSOR_RING = 26,
        LAYER_SENSOR_GIMMICK = 27,
        LAYER_SENSOR_LAND = 28,
        LAYER_SENSOR_ALL = 29,
        LAYER_RESERVED30 = 30,
        LAYER_RESERVED31 = 31
    }

    public enum MaterialType : sbyte
    {
        MAT_NONE = 0,
        MAT_STONE = 1,
        MAT_EARTH = 2,
        MAT_WOOD = 3,
        MAT_GRASS = 4,
        MAT_IRON = 5,
        MAT_SAND = 6,
        MAT_LAVA = 7,
        MAT_GLASS = 8,
        MAT_SNOW = 9,
        MAT_NO_ENTRY = 10,
        MAT_ICE = 11,
        MAT_WATER = 12,
        MAT_SEA = 13,
        MAT_DAMAGE = 14,
        MAT_DEAD = 15,
        MAT_FLOWER0 = 16,
        MAT_FLOWER1 = 17,
        MAT_FLOWER2 = 18,
        MAT_AIR = 19,
        MAT_DEADLEAVES = 20,
        MAT_WIREMESH = 21,
        MAT_DEAD_ANYDIR = 22,
        MAT_DAMAGE_THROUGH = 23,
        MAT_DRY_GRASS = 24,
        MAT_RELIC = 25,
        MAT_GIANT = 26,
        MAT_GRAVEL = 27,
        MAT_MUD_WATER = 28,
        MAT_SAND2 = 29,
        MAT_SAND3 = 30
    }

    [StructLayout(LayoutKind.Explicit, Size = 5)]
    public struct HeightFieldConfigData
    {
        [FieldOffset(0)] public LayerType layer;
        [FieldOffset(1)] public MaterialType material;
        [FieldOffset(2)] public bool notStand;
        [FieldOffset(3)] public bool wall;
        [FieldOffset(4)] public bool parkour;
    }

    [StructLayout(LayoutKind.Explicit, Size = 1275)]
    public struct HeightFieldConfig
    {
        [FieldOffset(0)] public HeightFieldConfigData data__arr0;
        [FieldOffset(5)] public HeightFieldConfigData data__arr1;
        [FieldOffset(10)] public HeightFieldConfigData data__arr2;
        [FieldOffset(15)] public HeightFieldConfigData data__arr3;
        [FieldOffset(20)] public HeightFieldConfigData data__arr4;
        [FieldOffset(25)] public HeightFieldConfigData data__arr5;
        [FieldOffset(30)] public HeightFieldConfigData data__arr6;
        [FieldOffset(35)] public HeightFieldConfigData data__arr7;
        [FieldOffset(40)] public HeightFieldConfigData data__arr8;
        [FieldOffset(45)] public HeightFieldConfigData data__arr9;
        [FieldOffset(50)] public HeightFieldConfigData data__arr10;
        [FieldOffset(55)] public HeightFieldConfigData data__arr11;
        [FieldOffset(60)] public HeightFieldConfigData data__arr12;
        [FieldOffset(65)] public HeightFieldConfigData data__arr13;
        [FieldOffset(70)] public HeightFieldConfigData data__arr14;
        [FieldOffset(75)] public HeightFieldConfigData data__arr15;
        [FieldOffset(80)] public HeightFieldConfigData data__arr16;
        [FieldOffset(85)] public HeightFieldConfigData data__arr17;
        [FieldOffset(90)] public HeightFieldConfigData data__arr18;
        [FieldOffset(95)] public HeightFieldConfigData data__arr19;
        [FieldOffset(100)] public HeightFieldConfigData data__arr20;
        [FieldOffset(105)] public HeightFieldConfigData data__arr21;
        [FieldOffset(110)] public HeightFieldConfigData data__arr22;
        [FieldOffset(115)] public HeightFieldConfigData data__arr23;
        [FieldOffset(120)] public HeightFieldConfigData data__arr24;
        [FieldOffset(125)] public HeightFieldConfigData data__arr25;
        [FieldOffset(130)] public HeightFieldConfigData data__arr26;
        [FieldOffset(135)] public HeightFieldConfigData data__arr27;
        [FieldOffset(140)] public HeightFieldConfigData data__arr28;
        [FieldOffset(145)] public HeightFieldConfigData data__arr29;
        [FieldOffset(150)] public HeightFieldConfigData data__arr30;
        [FieldOffset(155)] public HeightFieldConfigData data__arr31;
        [FieldOffset(160)] public HeightFieldConfigData data__arr32;
        [FieldOffset(165)] public HeightFieldConfigData data__arr33;
        [FieldOffset(170)] public HeightFieldConfigData data__arr34;
        [FieldOffset(175)] public HeightFieldConfigData data__arr35;
        [FieldOffset(180)] public HeightFieldConfigData data__arr36;
        [FieldOffset(185)] public HeightFieldConfigData data__arr37;
        [FieldOffset(190)] public HeightFieldConfigData data__arr38;
        [FieldOffset(195)] public HeightFieldConfigData data__arr39;
        [FieldOffset(200)] public HeightFieldConfigData data__arr40;
        [FieldOffset(205)] public HeightFieldConfigData data__arr41;
        [FieldOffset(210)] public HeightFieldConfigData data__arr42;
        [FieldOffset(215)] public HeightFieldConfigData data__arr43;
        [FieldOffset(220)] public HeightFieldConfigData data__arr44;
        [FieldOffset(225)] public HeightFieldConfigData data__arr45;
        [FieldOffset(230)] public HeightFieldConfigData data__arr46;
        [FieldOffset(235)] public HeightFieldConfigData data__arr47;
        [FieldOffset(240)] public HeightFieldConfigData data__arr48;
        [FieldOffset(245)] public HeightFieldConfigData data__arr49;
        [FieldOffset(250)] public HeightFieldConfigData data__arr50;
        [FieldOffset(255)] public HeightFieldConfigData data__arr51;
        [FieldOffset(260)] public HeightFieldConfigData data__arr52;
        [FieldOffset(265)] public HeightFieldConfigData data__arr53;
        [FieldOffset(270)] public HeightFieldConfigData data__arr54;
        [FieldOffset(275)] public HeightFieldConfigData data__arr55;
        [FieldOffset(280)] public HeightFieldConfigData data__arr56;
        [FieldOffset(285)] public HeightFieldConfigData data__arr57;
        [FieldOffset(290)] public HeightFieldConfigData data__arr58;
        [FieldOffset(295)] public HeightFieldConfigData data__arr59;
        [FieldOffset(300)] public HeightFieldConfigData data__arr60;
        [FieldOffset(305)] public HeightFieldConfigData data__arr61;
        [FieldOffset(310)] public HeightFieldConfigData data__arr62;
        [FieldOffset(315)] public HeightFieldConfigData data__arr63;
        [FieldOffset(320)] public HeightFieldConfigData data__arr64;
        [FieldOffset(325)] public HeightFieldConfigData data__arr65;
        [FieldOffset(330)] public HeightFieldConfigData data__arr66;
        [FieldOffset(335)] public HeightFieldConfigData data__arr67;
        [FieldOffset(340)] public HeightFieldConfigData data__arr68;
        [FieldOffset(345)] public HeightFieldConfigData data__arr69;
        [FieldOffset(350)] public HeightFieldConfigData data__arr70;
        [FieldOffset(355)] public HeightFieldConfigData data__arr71;
        [FieldOffset(360)] public HeightFieldConfigData data__arr72;
        [FieldOffset(365)] public HeightFieldConfigData data__arr73;
        [FieldOffset(370)] public HeightFieldConfigData data__arr74;
        [FieldOffset(375)] public HeightFieldConfigData data__arr75;
        [FieldOffset(380)] public HeightFieldConfigData data__arr76;
        [FieldOffset(385)] public HeightFieldConfigData data__arr77;
        [FieldOffset(390)] public HeightFieldConfigData data__arr78;
        [FieldOffset(395)] public HeightFieldConfigData data__arr79;
        [FieldOffset(400)] public HeightFieldConfigData data__arr80;
        [FieldOffset(405)] public HeightFieldConfigData data__arr81;
        [FieldOffset(410)] public HeightFieldConfigData data__arr82;
        [FieldOffset(415)] public HeightFieldConfigData data__arr83;
        [FieldOffset(420)] public HeightFieldConfigData data__arr84;
        [FieldOffset(425)] public HeightFieldConfigData data__arr85;
        [FieldOffset(430)] public HeightFieldConfigData data__arr86;
        [FieldOffset(435)] public HeightFieldConfigData data__arr87;
        [FieldOffset(440)] public HeightFieldConfigData data__arr88;
        [FieldOffset(445)] public HeightFieldConfigData data__arr89;
        [FieldOffset(450)] public HeightFieldConfigData data__arr90;
        [FieldOffset(455)] public HeightFieldConfigData data__arr91;
        [FieldOffset(460)] public HeightFieldConfigData data__arr92;
        [FieldOffset(465)] public HeightFieldConfigData data__arr93;
        [FieldOffset(470)] public HeightFieldConfigData data__arr94;
        [FieldOffset(475)] public HeightFieldConfigData data__arr95;
        [FieldOffset(480)] public HeightFieldConfigData data__arr96;
        [FieldOffset(485)] public HeightFieldConfigData data__arr97;
        [FieldOffset(490)] public HeightFieldConfigData data__arr98;
        [FieldOffset(495)] public HeightFieldConfigData data__arr99;
        [FieldOffset(500)] public HeightFieldConfigData data__arr100;
        [FieldOffset(505)] public HeightFieldConfigData data__arr101;
        [FieldOffset(510)] public HeightFieldConfigData data__arr102;
        [FieldOffset(515)] public HeightFieldConfigData data__arr103;
        [FieldOffset(520)] public HeightFieldConfigData data__arr104;
        [FieldOffset(525)] public HeightFieldConfigData data__arr105;
        [FieldOffset(530)] public HeightFieldConfigData data__arr106;
        [FieldOffset(535)] public HeightFieldConfigData data__arr107;
        [FieldOffset(540)] public HeightFieldConfigData data__arr108;
        [FieldOffset(545)] public HeightFieldConfigData data__arr109;
        [FieldOffset(550)] public HeightFieldConfigData data__arr110;
        [FieldOffset(555)] public HeightFieldConfigData data__arr111;
        [FieldOffset(560)] public HeightFieldConfigData data__arr112;
        [FieldOffset(565)] public HeightFieldConfigData data__arr113;
        [FieldOffset(570)] public HeightFieldConfigData data__arr114;
        [FieldOffset(575)] public HeightFieldConfigData data__arr115;
        [FieldOffset(580)] public HeightFieldConfigData data__arr116;
        [FieldOffset(585)] public HeightFieldConfigData data__arr117;
        [FieldOffset(590)] public HeightFieldConfigData data__arr118;
        [FieldOffset(595)] public HeightFieldConfigData data__arr119;
        [FieldOffset(600)] public HeightFieldConfigData data__arr120;
        [FieldOffset(605)] public HeightFieldConfigData data__arr121;
        [FieldOffset(610)] public HeightFieldConfigData data__arr122;
        [FieldOffset(615)] public HeightFieldConfigData data__arr123;
        [FieldOffset(620)] public HeightFieldConfigData data__arr124;
        [FieldOffset(625)] public HeightFieldConfigData data__arr125;
        [FieldOffset(630)] public HeightFieldConfigData data__arr126;
        [FieldOffset(635)] public HeightFieldConfigData data__arr127;
        [FieldOffset(640)] public HeightFieldConfigData data__arr128;
        [FieldOffset(645)] public HeightFieldConfigData data__arr129;
        [FieldOffset(650)] public HeightFieldConfigData data__arr130;
        [FieldOffset(655)] public HeightFieldConfigData data__arr131;
        [FieldOffset(660)] public HeightFieldConfigData data__arr132;
        [FieldOffset(665)] public HeightFieldConfigData data__arr133;
        [FieldOffset(670)] public HeightFieldConfigData data__arr134;
        [FieldOffset(675)] public HeightFieldConfigData data__arr135;
        [FieldOffset(680)] public HeightFieldConfigData data__arr136;
        [FieldOffset(685)] public HeightFieldConfigData data__arr137;
        [FieldOffset(690)] public HeightFieldConfigData data__arr138;
        [FieldOffset(695)] public HeightFieldConfigData data__arr139;
        [FieldOffset(700)] public HeightFieldConfigData data__arr140;
        [FieldOffset(705)] public HeightFieldConfigData data__arr141;
        [FieldOffset(710)] public HeightFieldConfigData data__arr142;
        [FieldOffset(715)] public HeightFieldConfigData data__arr143;
        [FieldOffset(720)] public HeightFieldConfigData data__arr144;
        [FieldOffset(725)] public HeightFieldConfigData data__arr145;
        [FieldOffset(730)] public HeightFieldConfigData data__arr146;
        [FieldOffset(735)] public HeightFieldConfigData data__arr147;
        [FieldOffset(740)] public HeightFieldConfigData data__arr148;
        [FieldOffset(745)] public HeightFieldConfigData data__arr149;
        [FieldOffset(750)] public HeightFieldConfigData data__arr150;
        [FieldOffset(755)] public HeightFieldConfigData data__arr151;
        [FieldOffset(760)] public HeightFieldConfigData data__arr152;
        [FieldOffset(765)] public HeightFieldConfigData data__arr153;
        [FieldOffset(770)] public HeightFieldConfigData data__arr154;
        [FieldOffset(775)] public HeightFieldConfigData data__arr155;
        [FieldOffset(780)] public HeightFieldConfigData data__arr156;
        [FieldOffset(785)] public HeightFieldConfigData data__arr157;
        [FieldOffset(790)] public HeightFieldConfigData data__arr158;
        [FieldOffset(795)] public HeightFieldConfigData data__arr159;
        [FieldOffset(800)] public HeightFieldConfigData data__arr160;
        [FieldOffset(805)] public HeightFieldConfigData data__arr161;
        [FieldOffset(810)] public HeightFieldConfigData data__arr162;
        [FieldOffset(815)] public HeightFieldConfigData data__arr163;
        [FieldOffset(820)] public HeightFieldConfigData data__arr164;
        [FieldOffset(825)] public HeightFieldConfigData data__arr165;
        [FieldOffset(830)] public HeightFieldConfigData data__arr166;
        [FieldOffset(835)] public HeightFieldConfigData data__arr167;
        [FieldOffset(840)] public HeightFieldConfigData data__arr168;
        [FieldOffset(845)] public HeightFieldConfigData data__arr169;
        [FieldOffset(850)] public HeightFieldConfigData data__arr170;
        [FieldOffset(855)] public HeightFieldConfigData data__arr171;
        [FieldOffset(860)] public HeightFieldConfigData data__arr172;
        [FieldOffset(865)] public HeightFieldConfigData data__arr173;
        [FieldOffset(870)] public HeightFieldConfigData data__arr174;
        [FieldOffset(875)] public HeightFieldConfigData data__arr175;
        [FieldOffset(880)] public HeightFieldConfigData data__arr176;
        [FieldOffset(885)] public HeightFieldConfigData data__arr177;
        [FieldOffset(890)] public HeightFieldConfigData data__arr178;
        [FieldOffset(895)] public HeightFieldConfigData data__arr179;
        [FieldOffset(900)] public HeightFieldConfigData data__arr180;
        [FieldOffset(905)] public HeightFieldConfigData data__arr181;
        [FieldOffset(910)] public HeightFieldConfigData data__arr182;
        [FieldOffset(915)] public HeightFieldConfigData data__arr183;
        [FieldOffset(920)] public HeightFieldConfigData data__arr184;
        [FieldOffset(925)] public HeightFieldConfigData data__arr185;
        [FieldOffset(930)] public HeightFieldConfigData data__arr186;
        [FieldOffset(935)] public HeightFieldConfigData data__arr187;
        [FieldOffset(940)] public HeightFieldConfigData data__arr188;
        [FieldOffset(945)] public HeightFieldConfigData data__arr189;
        [FieldOffset(950)] public HeightFieldConfigData data__arr190;
        [FieldOffset(955)] public HeightFieldConfigData data__arr191;
        [FieldOffset(960)] public HeightFieldConfigData data__arr192;
        [FieldOffset(965)] public HeightFieldConfigData data__arr193;
        [FieldOffset(970)] public HeightFieldConfigData data__arr194;
        [FieldOffset(975)] public HeightFieldConfigData data__arr195;
        [FieldOffset(980)] public HeightFieldConfigData data__arr196;
        [FieldOffset(985)] public HeightFieldConfigData data__arr197;
        [FieldOffset(990)] public HeightFieldConfigData data__arr198;
        [FieldOffset(995)] public HeightFieldConfigData data__arr199;
        [FieldOffset(1000)] public HeightFieldConfigData data__arr200;
        [FieldOffset(1005)] public HeightFieldConfigData data__arr201;
        [FieldOffset(1010)] public HeightFieldConfigData data__arr202;
        [FieldOffset(1015)] public HeightFieldConfigData data__arr203;
        [FieldOffset(1020)] public HeightFieldConfigData data__arr204;
        [FieldOffset(1025)] public HeightFieldConfigData data__arr205;
        [FieldOffset(1030)] public HeightFieldConfigData data__arr206;
        [FieldOffset(1035)] public HeightFieldConfigData data__arr207;
        [FieldOffset(1040)] public HeightFieldConfigData data__arr208;
        [FieldOffset(1045)] public HeightFieldConfigData data__arr209;
        [FieldOffset(1050)] public HeightFieldConfigData data__arr210;
        [FieldOffset(1055)] public HeightFieldConfigData data__arr211;
        [FieldOffset(1060)] public HeightFieldConfigData data__arr212;
        [FieldOffset(1065)] public HeightFieldConfigData data__arr213;
        [FieldOffset(1070)] public HeightFieldConfigData data__arr214;
        [FieldOffset(1075)] public HeightFieldConfigData data__arr215;
        [FieldOffset(1080)] public HeightFieldConfigData data__arr216;
        [FieldOffset(1085)] public HeightFieldConfigData data__arr217;
        [FieldOffset(1090)] public HeightFieldConfigData data__arr218;
        [FieldOffset(1095)] public HeightFieldConfigData data__arr219;
        [FieldOffset(1100)] public HeightFieldConfigData data__arr220;
        [FieldOffset(1105)] public HeightFieldConfigData data__arr221;
        [FieldOffset(1110)] public HeightFieldConfigData data__arr222;
        [FieldOffset(1115)] public HeightFieldConfigData data__arr223;
        [FieldOffset(1120)] public HeightFieldConfigData data__arr224;
        [FieldOffset(1125)] public HeightFieldConfigData data__arr225;
        [FieldOffset(1130)] public HeightFieldConfigData data__arr226;
        [FieldOffset(1135)] public HeightFieldConfigData data__arr227;
        [FieldOffset(1140)] public HeightFieldConfigData data__arr228;
        [FieldOffset(1145)] public HeightFieldConfigData data__arr229;
        [FieldOffset(1150)] public HeightFieldConfigData data__arr230;
        [FieldOffset(1155)] public HeightFieldConfigData data__arr231;
        [FieldOffset(1160)] public HeightFieldConfigData data__arr232;
        [FieldOffset(1165)] public HeightFieldConfigData data__arr233;
        [FieldOffset(1170)] public HeightFieldConfigData data__arr234;
        [FieldOffset(1175)] public HeightFieldConfigData data__arr235;
        [FieldOffset(1180)] public HeightFieldConfigData data__arr236;
        [FieldOffset(1185)] public HeightFieldConfigData data__arr237;
        [FieldOffset(1190)] public HeightFieldConfigData data__arr238;
        [FieldOffset(1195)] public HeightFieldConfigData data__arr239;
        [FieldOffset(1200)] public HeightFieldConfigData data__arr240;
        [FieldOffset(1205)] public HeightFieldConfigData data__arr241;
        [FieldOffset(1210)] public HeightFieldConfigData data__arr242;
        [FieldOffset(1215)] public HeightFieldConfigData data__arr243;
        [FieldOffset(1220)] public HeightFieldConfigData data__arr244;
        [FieldOffset(1225)] public HeightFieldConfigData data__arr245;
        [FieldOffset(1230)] public HeightFieldConfigData data__arr246;
        [FieldOffset(1235)] public HeightFieldConfigData data__arr247;
        [FieldOffset(1240)] public HeightFieldConfigData data__arr248;
        [FieldOffset(1245)] public HeightFieldConfigData data__arr249;
        [FieldOffset(1250)] public HeightFieldConfigData data__arr250;
        [FieldOffset(1255)] public HeightFieldConfigData data__arr251;
        [FieldOffset(1260)] public HeightFieldConfigData data__arr252;
        [FieldOffset(1265)] public HeightFieldConfigData data__arr253;
        [FieldOffset(1270)] public HeightFieldConfigData data__arr254;
    }

}