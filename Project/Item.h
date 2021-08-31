#include "Sound.h"

class Gun {
protected:

	float x;
	float y;
	float z;
	int state;
	int reloading;
	float bullet[1000][4][2];
	int num_bullet;
	pSound sound;

public:
	//Gun() :x(0), y(0), z(0) {};
	//Gun(float vx,float vy,float vz) :x(vx), y(vy), z(vz) {};
	virtual void draw() const = 0;
	virtual void shot(float x, float y, float z) = 0;
	virtual void update() = 0;
	virtual void draw_bullet() = 0;
	virtual void clear() = 0;
	virtual void stop_shot() = 0;
};

class Pistol : public Gun {

public:
	Pistol();
	Pistol(float vx, float vy, float vz);
	virtual void draw() const;
	virtual void shot(float x, float y, float z);
	virtual void update();
	virtual void draw_bullet();
	virtual void clear();
	virtual void stop_shot();
private:
	bool animation;
	int angle;

};

class FlameThrower : public Gun {

public:
	FlameThrower();
	FlameThrower(float vx, float vy, float vz);
	virtual void draw() const;
	virtual void shot(float x, float y, float z);
	virtual void update();
	virtual void draw_bullet();
	virtual void clear();
	virtual void stop_shot();
private:
	bool isShot;
};

class Grenade : public Gun {
public:
	Grenade();
	Grenade(float vx, float vy, float vz);
	virtual void draw() const;
	virtual void shot(float x, float y, float z);
	virtual void update();
	virtual void draw_bullet();
	virtual void clear();
	virtual void stop_shot();

};

class Potion {
	float x;
	float y;
	float z;
public:
	void draw();

};
class Vaccine {
	float x;
	float y;
	float z;
public:
	Vaccine() {};
	Vaccine(int x, int y, int z);
	void draw();
};


void cylinder(GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat radius, GLfloat h);