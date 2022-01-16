// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_settings.h"
#include "scene_menu_object.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"
// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.
extern float music_volume;
extern float effect_volume;
/* Define your static vars / function prototypes below. */
static Button vol_up_btn, vol_down_btn, back_btn;
static Button ef_vol_up_btn, ef_vol_down_btn;
// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
static void init() {

	ef_vol_up_btn = button_create(560, 600, 50, 50, "Assets/plus.png", "Assets/plus_hovered.png");
	ef_vol_down_btn = button_create(180, 600, 50, 50, "Assets/minus.png", "Assets/minus_hovered.png");
	
	vol_up_btn = button_create(560, 200, 50, 50, "Assets/plus.png", "Assets/plus_hovered.png");
	vol_down_btn = button_create(180, 200, 50, 50, "Assets/minus.png", "Assets/minus_hovered.png");
	
	back_btn = button_create(10, 10, 50, 50, "Assets/back.png", "Assets/back_hovered.png");
	/*
	gameTitle = load_bitmap("Assets/title.png");
	gameTitleW = al_get_bitmap_width(gameTitle);
	gameTitleH = al_get_bitmap_height(gameTitle);
	stop_bgm(menuBGM);
	menuBGM = play_bgm(themeMusic, music_volume);
	*/
}
static void draw(void) {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	al_draw_textf(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2,
		610,
		ALLEGRO_ALIGN_CENTER,
		"%.0f",10 * effect_volume);
	al_draw_text(
		menuFont,
		al_map_rgb(0, 255, 255),
		SCREEN_W / 2,
		550,
		ALLEGRO_ALIGN_CENTER,
		"Effect volume");

	al_draw_textf(
		menuFont,
		al_map_rgb(255, 255, 255),
		SCREEN_W / 2,
		210,
		ALLEGRO_ALIGN_CENTER,
		"%.0f", 10 * music_volume);
	al_draw_text(
		menuFont,
		al_map_rgb(0, 255, 255),
		SCREEN_W / 2,
		150,
		ALLEGRO_ALIGN_CENTER,
		"Music volume");


	drawButton(vol_up_btn);
	drawButton(vol_down_btn);
	drawButton(back_btn);
	drawButton(ef_vol_up_btn);
	drawButton(ef_vol_down_btn);
}
static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	
	vol_up_btn.hovered = buttonHover(vol_up_btn, mouse_x, mouse_y);
	vol_down_btn.hovered = buttonHover(vol_down_btn, mouse_x, mouse_y);
	
	back_btn.hovered = buttonHover(back_btn, mouse_x, mouse_y);
	
	ef_vol_up_btn.hovered = buttonHover(ef_vol_up_btn, mouse_x, mouse_y);
	ef_vol_down_btn.hovered = buttonHover(ef_vol_down_btn, mouse_x, mouse_y);
}
static void on_mouse_down() {
	
	if (vol_up_btn.hovered && music_volume < 1)
		music_volume += 0.1;
	
	if (vol_down_btn.hovered && music_volume > 0.2)
		music_volume -= 0.1;
	
	if (ef_vol_up_btn.hovered && effect_volume < 1)
		effect_volume += 0.1;
	
	if (ef_vol_down_btn.hovered && effect_volume > 0.2)
		effect_volume -= 0.1;

	if (back_btn.hovered)
		game_change_scene(scene_menu_create());
}
static void destroy(void) {
	
	al_destroy_bitmap(vol_up_btn.default_img);
	al_destroy_bitmap(vol_up_btn.hovered_img);
	al_destroy_bitmap(vol_down_btn.default_img);
	al_destroy_bitmap(vol_down_btn.hovered_img);
	
	al_destroy_bitmap(ef_vol_up_btn.default_img);
	al_destroy_bitmap(ef_vol_up_btn.hovered_img);
	al_destroy_bitmap(ef_vol_down_btn.default_img);
	al_destroy_bitmap(ef_vol_down_btn.hovered_img);

	al_destroy_bitmap(back_btn.hovered_img);
	al_destroy_bitmap(back_btn.default_img);

}

// The only function that is shared across files.
Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}