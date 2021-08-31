#include <gl/glut.h>
#include "tree.h"
#include "ground.h"
#include "container.h"
#include "Item_ground.h"

class Map {
public:
	Map();
	Map(const int w,const int h);
	~Map();
	void draw(unsigned int texture_container, unsigned int texture_ground)const;
	Tree** getTree() { return trees; }
	Container** getContainer() { return containers; }
	Vaccine_g** getVaccine() { return vaccines; }
	Potion_g** getPotion() { return potions; }

	bool collide_Tree(int x, int y, int z) const;
	bool collide_Object(int x, int y, int z) const;
private:
	Ground ground;
	Tree** trees;
	Container** containers;
	Vaccine_g** vaccines;
	Potion_g** potions;


	int Width;
	int Height;
};