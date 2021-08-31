class Zombie {

	float x;
	float y;
	float z;
	float alpha = 1;
	int ceta = 0;
	float leg_ceta = 0;
	float arm_ceta = 0;
	int hp = 30;

	int x_e = 1;
	int z_e = 1;
	int leg_e = 1;
	int arm_e = 1;
	bool Collision = false;
	int Move;	//1.2.3.4 ¿Þ,¿À,µÚ,¾Õ
	int Move_count = 0;

public:

	Zombie(float x, float y, float z) :x(x), y(y), z(z) {};
	Zombie() {}
	void draw();
	bool update(float vx, float vy, float vz);
	void move(float vx, float vy, float vz);
	bool attack();
	void collision(float, float, float, int, int, int);
	void set_collision(int n) { Collision = n; }
	bool get_collision() { return Collision; }
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setHp(int n);

};