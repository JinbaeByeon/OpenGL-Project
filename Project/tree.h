
class Tree{
public:
	Tree() :x(0), y(0), z(0),size(80) {};
	Tree(float x, float y, float z);
	void draw() const;
	bool collide(int x, int y, int z)const;
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }


private:
	float x, y, z;
	int size;
};