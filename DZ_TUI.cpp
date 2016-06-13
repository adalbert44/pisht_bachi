// DZ_TUI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

vector<string> name[200], fort_sprite(200);
int used_generals[200];
map <string, string> general_sprite;

void init()
{
	freopen("generals.dat", "r", stdin);
	for (int i = 0; i < 6; i++)
	{
		int n;
		cin >> n;
		for (int j = 0; j < n; j++)
		{
			string s, t;
			cin >> s;
			name[i].pb(s);
			cin >> t;
			general_sprite[s] = t;
		}
		random_shuffle(name[i].begin(), name[i].end());
	}
}

string new_name(int color)
{
	return name[color][used_generals[color]++];
}

class Town
{
public:
	int x, y, color;
	Sprite sprite;
};

class General
{
public:
	int x, y, color,  turns_left;
	string name;
	Sprite sprite;
	General(Town town)
	{
		this->x = town.x;
		this->y = town.y;
		this->color = town.color;
		this->name = new_name(color);
		this->sprite = general_sprite[this->name];
		this->turns_left = 2;
	}
};

class Fort
{
public:
	int x, y, color;
	Sprite sprite;
	Fort(General gen)
	{
		this->x = gen.x;
		this->y = gen.y;
		this->color = gen.color;
		this->sprite = fort_sprite[color];
	}
};

class Cell
{
public:
	int type;
	General general;
	Fort fort;
	Town town;
};

class Game
{
public:
	int type;
	Cell field[100][100];
};

int main()
{
	srand(unsigned(time(NULL)));
	printf("Hello world\n");
	system("pause");
    return 0;
}

