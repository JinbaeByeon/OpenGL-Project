

class FlameThrower_g{
	float x;
	float y;
	float z;
	bool Draw = false;
public:
	void draw();
	FlameThrower_g() {};
	FlameThrower_g(int x, int y, int z) :x(x), y(y), z(z) {}
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setDraw() { Draw = true; y = -500; }
	

};

class Grenade_g {
	float x;
	float y;
	float z;
	bool Draw = false;
public:
	void draw();
	Grenade_g() {};
	Grenade_g(int x, int y, int z) :x(x), y(y), z(z) {}
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setDraw() { Draw = true; y = -500; }

};

class Potion_g {
	float x;
	float y;
	float z;
	bool Draw = false;
public:
	void draw();
	Potion_g() {};
	Potion_g(int x, int y, int z) :x(x), y(y), z(z) {}
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setDraw() { Draw = true; y = -500; }

};
class Vaccine_g {
	float x;
	float y;
	float z;
	bool Draw = false;
public:
	Vaccine_g() {};
	Vaccine_g(int x, int y, int z);
	void draw();
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setDraw() { Draw = true;  y = -500; }

};

