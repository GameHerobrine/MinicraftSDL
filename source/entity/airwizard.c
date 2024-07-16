#include <entity/airwizard.h>
#include <game.h>
#include <gfx/screen.h>
#include <gfx/color.h>
#include <entity/_entity_caller.h>

void airwizard_create(AirWizard* wizard){
	mob_create(wizard);
	wizard->mob.entity.type = AIRWIZARD;
	wizard->mob.entity.x = random_next_int(&wizard->mob.entity.random, 64*16);
	wizard->mob.entity.y = random_next_int(&wizard->mob.entity.random, 64*16);
	wizard->mob.health = wizard->mob.maxHealth = 2000;

	wizard->xa = wizard->ya = 0;
	wizard->randomWalkTime = 0;
	wizard->attackDelay = 0;
	wizard->attackTime = 0;
	wizard->attackType = 0;
}

void airwizard_tick(AirWizard* wizard){
	mob_tick(wizard);

	if(wizard->attackDelay > 0){
		wizard->mob.dir = (wizard->attackDelay - 45) / 4 % 4;
		wizard->mob.dir = (wizard->mob.dir * 2 % 4) + (wizard->mob.dir / 2);
		if(wizard->attackDelay < 45) wizard->mob.dir = 0;
		--wizard->attackDelay;
		if(wizard->attackDelay == 0){
			wizard->attackType = 0;
			if(wizard->mob.health < 1000) wizard->attackType = 1;
			if(wizard->mob.health < 200) wizard->attackType = 2;
			wizard->attackTime = 60 * 2;
		}
		return;
	}

	if(wizard->attackTime > 0){
		--wizard->attackTime;
		/*
		 * double dir = attackTime * 0.25 * (attackTime % 2 * 2 - 1);
			double speed = (0.7) + attackType * 0.2;
			level.add(new Spark(this, Math.cos(dir) * speed, Math.sin(dir) * speed));
		*/
		//TODO: spark
		return;
	}

	int speed = (wizard->mob.tickTime % 4) == 0 ? 0 : 1;
	if(!mob_move(wizard, wizard->xa * speed, wizard->ya * speed) || random_next_int(&wizard->mob.entity.random, 100) == 0){
		wizard->randomWalkTime = 30;
		wizard->xa = random_next_int(&wizard->mob.entity.random, 3) - 1;
		wizard->ya = random_next_int(&wizard->mob.entity.random, 3) - 1;
	}

	if(wizard->randomWalkTime > 0){
		--wizard->randomWalkTime;
		if(game_player->mob.entity.level == wizard->mob.entity.level && wizard->randomWalkTime == 0){
			int xd = game_player->mob.entity.x - wizard->mob.entity.x;
			int yd = game_player->mob.entity.y - wizard->mob.entity.y;

			if(random_next_int(&wizard->mob.entity.random, 4) == 0 && xd*xd + yd*yd < 50 * 50){
				if(wizard->attackDelay == 0 && wizard->attackTime == 0){
					wizard->attackDelay = 60*2;
				}
			}

		}
	}
}

void airwizard_doHurt(AirWizard* wizard, int damage, int attackDir){
	mob_doHurt(wizard, damage, attackDir);

	if(wizard->attackDelay == 0 && wizard->attackTime == 0){
		wizard->attackDelay = 60*2;
	}
}
void airwizard_render(AirWizard* wizard, Screen* screen){
	int xt = 8;
	int yt = 14;

	int flip1 = (wizard->mob.walkDist >> 3) & 1;
	int flip2 = (wizard->mob.walkDist >> 3) & 1;

	if(wizard->mob.dir == 1) xt += 2;
	if(wizard->mob.dir > 1){
		flip1 = 0;
		flip2 = ((wizard->mob.walkDist >> 4) & 1);
		if(wizard->mob.dir == 2) flip1 = 1;
		xt += 4 + ((wizard->mob.walkDist >> 3) & 1) * 2;
	}

	int xo = wizard->mob.entity.x - 8;
	int yo = wizard->mob.entity.y - 11;

	int col1 = getColor4(-1, 100, 500, 555);
	int col2 = getColor4(-1, 100, 500, 532);

	if(wizard->mob.health < 200){
		if(wizard->mob.tickTime / 3 % 2 == 0){
			col1 = getColor4(-1, 500, 100, 555);
			col2 = getColor4(-1, 500, 100, 532);
		}
	}else if(wizard->mob.health < 1000){
		if(wizard->mob.tickTime / 5 % 4 == 0){
			col1 = getColor4(-1, 500, 100, 555);
			col2 = getColor4(-1, 500, 100, 532);
		}
	}

	if(wizard->mob.hurtTime > 0){
		col1 = getColor4(-1, 555, 555, 555);
		col2 = getColor4(-1, 555, 555, 555);
	}

	render_screen(screen, xo + 8 * flip1, yo + 0, xt + yt * 32, col1, flip1);
	render_screen(screen, xo + 8 - 8 * flip1, yo + 0, xt + 1 + yt * 32, col1, flip1);
	render_screen(screen, xo + 8 * flip2, yo + 8, xt + (yt + 1) * 32, col2, flip2);
	render_screen(screen, xo + 8 - 8 * flip2, yo + 8, xt + 1 + (yt + 1) * 32, col2, flip2);
}

void airwizard_touchedBy(AirWizard* wizard, Entity* entity){
	if(entity->type == PLAYER){
		call_entity_hurt(entity, wizard, 3, wizard->mob.dir);
	}
}
void airwizard_die(AirWizard* wizard){
	mob_die(wizard);
	//TODO won if (level.player != null) {
	//	level.player.score += 1000;
	//	level.player.gameWon();
	//}
	//TODO sounds Sound.bossdeath.play();
}
