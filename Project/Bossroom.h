
class Bossroom {
public:
	Bossroom() :isOpen(false),yRotate(0) {};
	void draw() const;
	void update();
	void door_open();
private:
	bool isOpen;
	int yRotate;
};