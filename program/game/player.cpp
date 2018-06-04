#include "player.h"
#include "DxLib.h"
#include "../support/Support.h"

player::player() {

}

player::~player() {

}

void player::set_parameter(int player_character) {
	player_char = player_character;
	break_cnt = 0;
	attack_cnt = 0;
	guard_cnt = 0;
	switch (player_character) {
	case 0:
		level = 1;
		exp = 0;
		next_exp = 10;
		pre_exp = 10;
		max_hp = 150;
		hp = 150;
		break_power = 60;
		speed_power = 60;
		guard_power = 60;
		name = "勇者";
		break;
	case 1:
		level = 1;
		exp = 0;
		next_exp = 10;
		pre_exp = 10;
		max_hp = 100;
		hp = 100;
		break_power = 90;
		speed_power = 40;
		guard_power = 80;
		name = "魔法使い";
		break;
	case 2:
		level = 1;
		exp = 0;
		next_exp = 10;
		pre_exp = 10;
		max_hp = 200;
		hp = 200;
		break_power = 40;
		speed_power = 40;
		guard_power = 80;
		name = "騎士";
		break;
	case -1:
		level = 1;
		exp = 5;
		next_exp = 0;
		max_hp = 80;
		hp = 80;
		break_power = 40;
		speed_power = 20;
		guard_power = 20;
		name = "コッコー";
		break;
	case -2:
		level = 1;
		exp = 9;
		next_exp = 0;
		max_hp = 100;
		hp = 100;
		break_power = 30;
		speed_power = 50;
		guard_power = 20;
		name = "ウルフ";
		break;
	case -3:
		level = 1;
		exp = 7;
		next_exp = 0;
		max_hp = 70;
		hp = 70;
		break_power = 30;
		speed_power = 30;
		guard_power = 50;
		name = "ゴースト";
		break;
	default:
		break;
	};
}

int player::break_attack() {
	return this->break_power;
}

int player::speed_attack() {
	return this->speed_power;
}

int player::guard_attack() {
	return this->guard_power;
}

int player::player_level() {
	return this->level;
}

int player::player_next_exp() {
	return this->next_exp;
}
int player::player_exp() {
	return this->exp;
}

int player::player_hp() {
	return this->hp;
}

int player::player_hp_max() {
	return this->max_hp;
}

int player::player_hp_percentage() {
	return int(float(this->hp) / this->max_hp * 100);
}

int player::break_count() {
	return this->break_cnt;
}

int player::attack_count() {
	return this->attack_cnt;
}

int player::guard_count() {
	return this->guard_cnt;
}

void player::damage(int damage) {
	this->hp -= damage;
}

void player::break_increment() {
	this->break_cnt++;
	if (this->break_cnt >= 9) {
		this->break_cnt = 9;
	}
}

void player::attack_increment() {
	this->attack_cnt++;
	if (this->attack_cnt >= 9) {
		this->attack_cnt = 9;
	}
}

void player::guard_increment() {
	this->guard_cnt++;
	if (this->guard_cnt >= 9) {
		this->guard_cnt = 9;
	}
}

void player::break_decrement() {
	if (this->player_char == 1) {
		this->break_cnt -= 2;
	}
	else {
		this->break_cnt--;
	}
}

void player::attack_decrement() {
	if (this->player_char == 0) {
		this->attack_cnt -= 2;
	}
	else {
		this->attack_cnt--;
	}
}

void player::guard_decrement() {
	if (this->player_char == 2) {
		this->guard_cnt -= 2;
	}
	else {
		this->guard_cnt--;
	}
}

bool player::is_skill() {
	switch (this->player_char) {
	case 0:
		if (break_cnt >= 1 && attack_cnt >= 2 && guard_cnt >= 1) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 1:
		if (break_cnt >= 2 && attack_cnt >= 1 && guard_cnt >= 1) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 2:
		if (break_cnt >= 1 && attack_cnt >= 1 && guard_cnt >= 2) {
			return true;
		}
		else {
			return false;
		}
		break;
	default:
		return false;
		break;
	}
}

int player::skill_attack() {
	switch (player_char) {
	case 0:
		this->hp += this->speed_power;
		if (this->hp > this->max_hp) {
			this->hp = this->max_hp;
		}
		return this->speed_power * 2;
		break;
	case 1:
		return this->break_power * 3;
		break;
	case 2:
		if (this->max_hp - this->hp > this->guard_power) {
			return this->max_hp - this->hp;
		}
		else {
			return this->guard_power;
		}
		break;
	default:
		return 0;
		break;
	}
}

std::string player::player_name() {
	return this->name;
}

void player::level_up(int random_hp,int random_spd,int random_bre,int random_gua) {
	this->level += 1;
	this->next_exp = (this->level * 13 + this->pre_exp * 1.3) / 2;
	this->pre_exp = this->next_exp;

	switch (this->player_char) {
	case 0:
		this->max_hp += 45 + random_hp;
		this->speed_power += 21 + random_spd;
		this->break_power += 21 + random_bre;
		this->guard_power += 21 + random_gua;
		break;
	case 1:
		this->max_hp += 30 + random_hp;
		this->speed_power += 14 + random_spd;
		this->break_power += 30 + random_bre;
		this->guard_power += 28 + random_gua;
		break;
	case 2:
		this->max_hp += 60 + random_hp;
		this->speed_power += 14 + random_spd;
		this->break_power += 14 + random_bre;
		this->guard_power += 28 + random_gua;
		break;
	default:
		break;
	}
}

bool player::is_level_up() {
	if (this->next_exp == 0) {
		return true;
	}
	else {
		return false;
	}
}

void player::exp_gain() {
	this->exp += 1;
	this->next_exp -= 1;
}

void player::hp_heal() {
	this->hp = this->max_hp;
}

int player::enemy_hand_decided(int random_number) {
	switch (this->player_char) {
	case -1:
		//コッコー
		if (random_number <= 70) {
			return 0;
		}
		else if (random_number <= 90) {
			return 1;
		}
		else if (random_number <= 100) {
			return 2;
		}
		break;
	case -2:
		//ウルフ
		if (random_number <= 70) {
			return 1;
		}
		else if (random_number <= 90) {
			return 0;
		}
		else if (random_number <= 100) {
			return 2;
		}
		break;
	case -3:
		//ゴースト
		if (random_number <= 70) {
			return 2;
		}
		else if (random_number <= 90) {
			return 1;
		}
		else if (random_number <= 100) {
			return 0;
		}
		break;
	default:
		return 0;
		break;
	}
}