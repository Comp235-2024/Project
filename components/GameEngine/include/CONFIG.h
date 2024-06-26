/**
 * @file CONFIG.h
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#ifndef A2_CONFIG_H
#define A2_CONFIG_H


#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 1024

#define WELCOME_STATE_DURATION 2.0
#define WELCOME_BG_IMAGE_PATH "../../assets/images/welcome_bg.jpg"
#define WELCOME_CHAR_SIZE 30
#define FONT_PATH "../../assets/fonts/MartianMonoNerdFontPropo-Regular.ttf"

#define MENU_BG_IMAGE_PATH "../../assets/images/menu_bg.jpg"
#define MENU_CHAR_TITLE_SIZE 35
#define MENU_CHAR_SIZE 26

#define GAME_BG_IMAGE_PATH "../../assets/images/grass_game_bg.jpg"
#define MENU_ICON_PATH "../../assets/images/menu_icon.png"

#define PLAYER_KNIGHT_IMAGE_PATH "../../assets/images/frames/knight_f_idle_anim_f0.png"
#define PLAYER_WIZARD_IMAGE_PATH "../../assets/images/frames/wizzard_m_idle_anim_f0.png"
#define CHEST_IMAGE_PATH "../../assets/images/frames/chest_empty_open_anim_f0.png"
#define WALL_IMAGE_PATH "../../assets/images/frames/wall_mid.png"
#define SKELETON_IMAGE_PATH "../../assets/images/frames/skelet_idle_anim_f0.png"
#define OGRE_IMAGE_PATH "../../assets/images/frames/ogre_idle_anim_f0.png"
#define DOOR_IMAGE_PATH "../../assets/images/frames/doorS_leaf_closed.png"
#define LEVER_IMAGE_PATH "../../assets/images/frames/lever_left.png"
#define MONEY_IMAGE_PATH "../../assets/images/money.png"

#pragma region MapCreator
#define CELL_SIZE 32
#define SIDEBAR_RATIO 0.15
#define SIDEBAR_ITEM_RATIO 0.8
#define SIDEBAR_ITEM_PADDING 0.01
#define BOTTOMBAR_BUTTON_WIDTH_RATIO 0.25
#define BOTTOMBAR_BUTTON_HEIGHT_RATIO 0.8

#pragma endregion

#define IMAGES_PATH "../../assets/images/frames/"


#define MUSIC1_PATH "../../assets/audios/music1.ogg"
#define MUSIC2_PATH "../../assets/audios/2.ogg"
#define MUSIC3_PATH "../../assets/audios/3.ogg"
#define MUSIC4_PATH "../../assets/audios/4.ogg"
#define DEFAULT_MUSIC_VOL 5.f
#endif//A2_CONFIG_H
