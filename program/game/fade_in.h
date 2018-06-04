#ifndef FADE_IN
#define FADE_IN

void fade_in_circle(int background_handle,int enemy_handle);
void fade_in_alpha(int scrollx, int scrolly, int *map,int *map2, int character_number, int animation_control, bool is_right, bool is_move);
void fade_in_dungeon(int scrollx, int scrolly, int *map, int *map2, int character_number, int animation_control, bool is_right, bool is_move);
void fade_in_town(int town_image);

//‰~i‰~‚Ì“à‘¤‚Í•`‰æ–³‚µAŠO‘¤‚Í•F‚É•`‰æj‚Ì•`‰æ
void draw_reverse_circle(int pos_x,int pos_y,int radius);

#endif