#include "Item.h"

class Character {

	int hp = 100;
	float x;
	float y;
	float z;
	float alpha = 1;
	float ceta = 0;
	float leg_ceta = 0;
	float arm_ceta = 0;

	int state = 1;			// 1,2,3 : 권총, 화염방사기, 수류탄 들고있는 무기
	int x_e = 1;
	int z_e = 1;
	int leg_e = 1;
	int arm_e = 1;
	int yRotate = 0;
	int xRotate = 0;
	int state_Eye = 1;
	int collision_side = 0;

	Gun* gun;
	pSound sound;
	bool isShot = false;
	
	int Num_Pistol = 1;
	int Num_Flame = 0;
	int Num_Grenade = 0;
	int Num_Potion = 0;
	int Num_Vaccine = 0;

public:

	Character(float x, float y, float z) :x(x), y(y), z(z),state(0) {};
	Character():x(0),y(0),z(0) {}
	void draw();
	void update(int yRotate, int xRotate);
	void move(float vx, float vy, float vz);
	int collision(float, float, float, int, int, int);
	bool collision_item(float, float, float, int);
	bool collision_bullet(float, float, float, float, float, float);
	bool collision_bullet(float, float, float);
	void setcollision(int);
	int getcollision() { return collision_side; }
	void set_item(int);
	void update_gun();
	void shot();
	void stop_shot();
	void setGun(int);
	int getGun() { return state; }
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setHp(int n);
	int getHp() { return hp; }
	int getVaccine() { return Num_Vaccine; }
	void change_stateEye();
};