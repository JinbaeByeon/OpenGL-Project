#include <random>
#include <time.h>

#include "map.h"
#include "default_value.h"
#include "util.h"

Map::Map() :Width(Width_Map), Height(Height_Map)
{
	srand((unsigned)time(NULL));
	Ground tmp(Width, Height);
	ground = tmp;

	int tmp_X;
	int tmp_Z;


	potions = new Potion_g*[Num_Potion];
	potions[0] = new Potion_g(2300, 0, 1000);
	potions[1] = new Potion_g(2000, 0, -1000);
	potions[2] = new Potion_g(-2300, 0, 1000);
	potions[3] = new Potion_g(-2300, 0, -1000);
	potions[4] = new Potion_g(0, 0, -1000);

	vaccines = new Vaccine_g*[Num_Vaccine];
	vaccines[0] = new Vaccine_g(-650, 0, 2300);
	vaccines[1] = new Vaccine_g(-2300, 0, -900);
	vaccines[2] = new Vaccine_g(-400, 0, -400);
	vaccines[3] = new Vaccine_g(2300, 0, -1800);


	trees = new Tree*[Num_Tree];
	trees[0] = new Tree(2000, 0, 0);
	trees[1] = new Tree(1300, 0, 600);
	trees[2] = new Tree(1100, 0, 2000);
	trees[3] = new Tree(0, 0, 1000);
	trees[4] = new Tree(-400, 0, 2200);
	trees[5] = new Tree(-2000, 0, 2000);
	trees[6] = new Tree(-2000, 0, -800);
	trees[7] = new Tree(0, 0, -400);
	trees[8] = new Tree(-800, 0, -1500);
	trees[9] = new Tree(800, 0, -1500);


	//for (int i = 0; i < Num_Tree; i++) {
	//	tmp_X = -Width / 2 + rand() % Width;
	//	tmp_Z = -Height / 2 + rand() % Height;
	//	for (int j = 0; j < i; j++) {
	//		while (true == trees[j]->collide(tmp_X, 0, tmp_Z)) {
	//			j = 0;
	//			tmp_X = -Width / 2 + rand() % Width;
	//			tmp_Z = -Height / 2 + rand() % Height;
	//		}
	//	}
	//	trees[i] = new Tree(tmp_X, 0, tmp_Z);
	//}

	int xSize = 500, zSize = 500;

	containers = new Container*[Num_Container];
	containers[0] = new Container(2100, 0, 1300, 90);
	containers[1] = new Container(700, 0, 2100, 0);
	containers[2] = new Container(0, 0, 0, 90);
	containers[3] = new Container(-1700, 0, 500, 0);
	containers[4] = new Container(-2100, 0, -1300, 90);
	containers[5] = new Container(2100, 0, -1300, 90);
	containers[6] = new Container(0, 0, -2100, 0);
	containers[7] = new Container(-1000, 0, 2100, 0);


	//for (int i = 0; i < Num_Container; i++) {
	//	tmp_X = (-Width / 2 + xSize) + rand() % (Width - xSize);
	//	tmp_Z = (-Height / 2 + zSize) + rand() % (Height - zSize);
	//	for (int j = 0; j < i; j++) {
	//		while (true == containers[j]->inContainer(tmp_X, 0, tmp_Z)&&(tmp_X<-1000||tmp_X>1000)&& (tmp_Z<-1000 || tmp_Z>1000)) {
	//			j = 0;
	//			tmp_X = -Width / 2 + rand() % Width;
	//			tmp_Z = -Height / 2 + rand() % Height;
	//		}
	//		for (int k = 0; k < Num_Tree; k++) {
	//			while (true == trees[k]->collide(tmp_X, 0, tmp_Z)) {
	//				j = 0;
	//				tmp_X = -Width / 2 + rand() % Width;
	//				tmp_Z = -Height / 2 + rand() % Height;
	//			}
	//		}
	//	}
	//	containers[i] = new Container(tmp_X, 0, tmp_Z, 0);
	//}

}

Map::Map(const int w,const int h) :Width(w), Height(h)
{
	srand((unsigned)time(NULL));
	Ground tmp(w, h);
	ground = tmp;

	trees = new Tree*[Num_Tree];
	int tmp_X;
	int tmp_Z;

	for (int i = 0; i < Num_Tree; i++) {
		tmp_X = -w / 2 + rand() % w;
		tmp_Z = -h / 2 + rand() % h;
		for (int j = 0; j < i; j++) {
			while (true == trees[j]->collide(tmp_X, 0, tmp_Z)) {
				j = 0;
				tmp_X = -w / 2 + rand() % w;
				tmp_Z = -h / 2 + rand() % h;
			}
		}
		trees[i] = new Tree(tmp_X, 0, tmp_Z);
	}

	int xSize = 500, zSize = 500;

	containers = new Container*[Num_Container];

	for (int i = 0; i < Num_Container; i++) {
		tmp_X = (-Width / 2 + xSize) + rand() % (Width - xSize);
		tmp_Z = (-Height / 2 + zSize) + rand() % (Height - zSize);
		for (int j = 0; j < i; j++) {
			while (true == containers[j]->inContainer(tmp_X, 0, tmp_Z)) {
				j = 0;
				tmp_X = -Width / 2 + rand() % Width;
				tmp_Z = -Height / 2 + rand() % Height;
			}
			for (int k = 0; k < Num_Tree; k++) {
				while (true == trees[k]->collide(tmp_X, 0, tmp_Z)) {
					j = 0;
					tmp_X = -Width / 2 + rand() % Width;
					tmp_Z = -Height / 2 + rand() % Height;
				}
			}
		}
		containers[i] = new Container(tmp_X, 0, tmp_Z,0);
	}
}

void Map::draw(unsigned int texture_container,unsigned int texture_ground) const
{
	ground.draw(texture_ground);

	for (int i = 0; i < Num_Tree; i++)
		trees[i]->draw();

	for (int i = 0; i < Num_Container; i++)
		containers[i]->draw(texture_container);
	
	for (int i = 0; i < Num_Vaccine; i++)
		vaccines[i]->draw();

	for (int i = 0; i < Num_Potion; i++)
		potions[i]->draw();

}

bool Map::collide_Tree(int x, int y, int z) const
{
	for (int i = 0; i < Num_Tree; i++)
		if (trees[i]->collide(x, y, z))
			return true;
	return false;
}

bool Map::collide_Object(int x, int y, int z) const
{
	for (int i = 0; i < Num_Tree; i++)
		if (trees[i]->collide(x, y, z))
			return true;
	for (int i = 0; i < Num_Container; i++)
		if (containers[i]->inContainer(x, y, z))
			return true;

	return false;
}

Map::~Map()
{
	for (int i = 0; i < Num_Tree; ++i)
		delete[i] trees[i];
	for (int i = 0; i < Num_Container; ++i)
		delete[i] containers[i];
	for (int i = 0; i < Num_Vaccine; ++i)
		delete[i] vaccines[i];
	for (int i = 0; i < Num_Potion; ++i)
		delete[i] potions[i];


	delete[] trees;
	delete[] containers;
	delete[] vaccines;
	delete[] potions;

}