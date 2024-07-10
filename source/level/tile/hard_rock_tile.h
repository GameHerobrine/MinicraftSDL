#ifndef LEVEL_TILE_HARD_ROCK_TILE_H_
#define LEVEL_TILE_HARD_ROCK_TILE_H_

void hardrocktile_render(TileID id, Screen* screen, Level* level, int x, int y);
void hardrocktile_tick(TileID id, Level* level, int xt, int yt);
void hardrocktile_hurt(TileID id, Level* level, int x, int y, Mob* source, int dmg, int attackDir);
#endif /* LEVEL_TILE_HARD_ROCK_TILE_H_ */
