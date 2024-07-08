#include "player.h"
#include "mob.h"
#include <level/tile/tileids.h>
#include <inputhandler.h>

void player_create(Player* player){
	mob_create(&player->mob);
	player->mob.entity.type = PLAYER;
	player->attackTime = player->attackTime = 0;
	player->stamina = player->staminaRecharge = player->staminaRechargeDelay = 0;
	player->score = 0;
	player->onStairDelay = 0;
	player->invulnerableTime = 0;

	player->mob.entity.x = 24;
	player->mob.entity.y = 24;
	player->stamina = player->maxStamina = 10;

	//TODO inventory
}
void player_tick(Player* player){
	mob_tick(&player->mob);
	if(player->invulnerableTime > 0) --player->invulnerableTime;

	int x = player->mob.entity.x;
	int y = player->mob.entity.y;

	unsigned char tile = level_get_tile(player->mob.entity.level, x >> 4, y >> 4);
	if(tile == STAIRS_DOWN || tile == STAIRS_UP){
		if(player->onStairDelay == 0){
			//TODO changeLevel
			player->onStairDelay = 10;
			return;
		}
		player->onStairDelay = 10;
	}else{
		if(player->onStairDelay > 0) --player->onStairDelay;
	}

	if(player->stamina <= 0 && player->staminaRechargeDelay == 0 && player->staminaRecharge == 0){
		player->staminaRechargeDelay = 40;
	}

	if(player->staminaRechargeDelay > 0){
		--player->staminaRechargeDelay;
	}

	if(player->staminaRechargeDelay == 0){
		++player->staminaRecharge;
		/*TODO: if (isSwimming()) {
			staminaRecharge = 0;
		}
		while (staminaRecharge > 10) {
			staminaRecharge -= 10;
			if (stamina < maxStamina) stamina++;
		}*/
	}

	int xa = 0;
	int ya = 0;
	if(up.down) --ya;
	if(down.down) ++ya;
	if(left.down) --xa;
	if(right.down) ++xa;

	/*TODO:
	 * if (isSwimming() && tickTime % 60 == 0) {
			if (stamina > 0) {
				stamina--;
			} else {
				hurt(this, 1, dir ^ 1);
			}
		}
	*/

	if(player->staminaRechargeDelay % 2 == 0){
		mob_move(&player->mob, xa, ya);
	}

	/*TODO:
	 * if (input.attack.clicked) {
			if (stamina == 0) {

			} else {
				stamina--;
				staminaRecharge = 0;
				attack();
			}
		}
		if (input.menu.clicked) {
			if (!use()) {
				game.setMenu(new InventoryMenu(this));
			}
		}
		if (attackTime > 0) attackTime--;
	*/
}
void player_render(Player* player, Screen* screen){
	int xt = 0;
	int yt = 14;

	int flip1 = (player->mob.walkDist >> 3) & 1;
	int flip2 = (player->mob.walkDist >> 3) & 1;

	if(player->mob.dir == 1){
		xt += 2;
	}

	if(player->mob.dir > 1){
		flip1 = 0;
		flip2 = ((player->mob.walkDist >> 4) & 1);
		if(player->mob.dir == 2) flip1 = 1;
		xt += 4 + ((player->mob.walkDist >> 3) & 1) * 2;
	}

	int xo = player->mob.entity.x - 8;
	int yo = player->mob.entity.y - 11;

	if(call_entity_isSwimming(player)){
		yo += 4;
		int waterColor = getColor4(-1, -1, 115, 335);
		if(player->mob.tickTime / 8 % 2 == 0){
			waterColor = getColor4(-1, 335, 5, 115);
		}

		render_screen(screen, xo + 0, yo + 3, 5+13*32, waterColor, 0);
		render_screen(screen, xo + 8, yo + 3, 5+13*32, waterColor, 1);
	}

	if(player->attackTime > 0 && player->attackDir == 1){
		render_screen(screen, xo + 0, yo - 4, 6+13*32, getColor4(-1, 555, 555, 555), 0);
		render_screen(screen, xo + 8, yo - 4, 6+13*32, getColor4(-1, 555, 555, 555), 1);
		//TODO attackItem != null ? attackItem.renderIcon()
	}

	int col = getColor4(-1, 100, 220, 532);
	if(player->mob.hurtTime > 0) col = getColor4(-1, 555, 555, 555);

	//TODO if(activeItem is Furniture) yt += 2;
	render_screen(screen, xo + 8 * flip1, yo + 0, xt + yt*32, col, flip1);
	render_screen(screen, xo + 8 - 8 * flip1, yo + 0, xt + 1 + yt*32, col, flip1);
	if(!call_entity_isSwimming(player)){
		render_screen(screen, xo + 8 * flip2, yo + 8, xt + (yt + 1) * 32, col, flip2);
		render_screen(screen, xo + 8 - 8 * flip2, yo + 8, xt + 1 + (yt + 1) * 32, col, flip2);
	}
	if(player->attackTime > 0 && player->attackDir == 2){
		render_screen(screen, xo - 4, yo, 7 + 13*32, getColor4(-1, 555, 555, 555), 1);
		render_screen(screen, xo - 4, yo + 8, 7 + 13*32, getColor4(-1, 555, 555, 555), 3);

		/* TODO:
			if (attackItem != null) {
				attackItem.renderIcon(screen, xo - 4, yo + 4);
			}
		*/
	}

	if(player->attackTime > 0 && player->attackDir == 3){
		render_screen(screen, xo + 8 + 4, yo, 7 + 13 * 32, getColor4(-1, 555, 555, 555), 0);
		render_screen(screen, xo + 8 + 4, yo + 8, 7 + 13 * 32, getColor4(-1, 555, 555, 555), 2);
		/* TODO:
			if (attackItem != null) {
				attackItem.renderIcon(screen, xo + 8 + 4, yo + 4);
			}
		*/
	}

	if(player->attackTime > 0 && player->attackDir == 0){
		render_screen(screen, xo + 0, yo + 8 + 4, 6 + 13 * 32, getColor4(-1, 555, 555, 555), 2);
		render_screen(screen, xo + 8, yo + 8 + 4, 6 + 13 * 32, getColor4(-1, 555, 555, 555), 3);
		/*TODO: if (attackItem != null) {
			attackItem.renderIcon(screen, xo + 4, yo + 8 + 4);
		}*/
	}

	/* TODO:
		if (activeItem instanceof FurnitureItem) {
			Furniture furniture = ((FurnitureItem) activeItem).furniture;
			furniture.x = x;
			furniture.y = yo;
			furniture.render(screen);

		}*/





}
char player_findStartPos(Player* player, Level* level){
	Random* random = &player->mob.entity.random;
	while(1){
		int x = random_next_int(random, level->w);
		int y = random_next_int(random, level->h);

		if(level_get_tile(level, x, y) == GRASS){
			player->mob.entity.x = x * 16 + 8;
			player->mob.entity.y = y * 16 + 8;
			return 1;
		}
	}
}
