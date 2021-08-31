
class Container {
public:
	Container();
	Container(int x, int y, int z, int yRotate);
	void draw(unsigned int texture) const;
	bool inContainer(const float x, const float y,const float z) const;
	int getSize_X() const;
	int getSize_Y() const;
	int getSize_Z() const;
	int getX() { return x; }
	int getY() { return y; }
	int getZ() { return z; }
	int getyRotate() { return yRotate; }

private:
	float x, y, z;
	int xSize, ySize, zSize;
	int yRotate;
};