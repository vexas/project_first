#ifndef GAME_PLAYER
#define GAME_PLAYER
#include <string>
#include <iostream>

class player {
private:
	int player_char;
	int level;
	int exp;
	int next_exp;
	int pre_exp;
	int max_hp;
	int break_power;
	int speed_power;
	int guard_power;
	int hp;
	int break_cnt;
	int attack_cnt;
	int guard_cnt;
	std::string name;
	
	


public:
	player();
	void set_parameter(int player_character);
	~player();
	int speed_attack();
	int break_attack();
	int guard_attack();
	int player_level();
	int player_next_exp();
	int player_exp();
	int player_hp();
	int player_hp_max();
	int player_hp_percentage();
	int break_count();
	int attack_count();
	int guard_count();
	void damage(int damage);
	void break_increment();
	void attack_increment();
	void guard_increment();
	void break_decrement();
	void attack_decrement();
	void guard_decrement();
	bool is_skill();
	int skill_attack();
	std::string player_name();
	void level_up(int random_hp,int random_spd,int random_bre,int random_gua);
	bool is_level_up();
	void exp_gain();
	void hp_heal();
	int enemy_hand_decided(int random_number);

};

#endif
