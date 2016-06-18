// DZ_TUI.cpp : Defines the entry point for the console application.
//

#include "all_includes.h"

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

	Town(int x, int y, int color)
	{
	    this->x = x;
	    this->y = y;
        this->color = color;
        this->sprite = fort_sprite[color];
	}
};

class General
{
public:
	int x, y, color, turns_left;
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
		this->sprite = fort_sprite[this->color];
	}
	Fort(int x, int y, int color)
	{
		this->x = x;
		this->y = y;
		this->color = color;
		this->sprite = fort_sprite[color];
	}
};

class Cell
{
public:
	int color;
	General *general;
	Fort *fort;
	Town *town;

	Cell()
	{
	    this->color = 0;
	    this->general = NULL;
        this->fort = NULL;
        this->town = NULL;
	}
};

enum players_regime
{
    READ_FROM_FILE,
    PLAYER_PLAYER,
    PLAYER_COMPUTER
};

pair<int,int> moves[6] = {{-1,0}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1} };

