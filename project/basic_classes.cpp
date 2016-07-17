// тут усі базові класи,окрім класу гри
//

#include "all_includes.h"

vector<string> name[200], fort_sprite(200);
int used_generals[200];
map <string, string> general_sprite;

/// метод для генерації масиву генералів певної нації
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

/// метод для генерації наступного генерала із списку
string new_name(int color)
{
	return name[color][used_generals[color]++];
}

/// клас міста
class Town
{
public:
	int x, y, color;
	Sprite sprite;
	
	// конструктор міста від координат клітинки та кольору нації
	Town(int x, int y, int color)
	{
	    this->x = x;
	    this->y = y;
        this->color = color;
        this->sprite = fort_sprite[color];
	}
};

/// клас генерала
class General
{
public:
	int x, y, color, turns_left;
	string name;
	Sprite sprite;

	// конструктор від рідного міста генерала
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

/// клас фортеці
class Fort
{
public:
	int x, y, color;
	Sprite sprite;

	// конструктор від генерала, який побудував фортецю
	Fort(General gen)
	{
		this->x = gen.x;
		this->y = gen.y;
		this->color = gen.color;
		this->sprite = fort_sprite[this->color];
		// TODO: знищувати генерала після побудови фортеці
	}
	// конструктор від координат клітинки та кольору нації
	Fort(int x, int y, int color)
	{
		this->x = x;
		this->y = y;
		this->color = color;
		this->sprite = fort_sprite[color];
	}
};

/// клас клітинки
class Cell
{
public:
	int color;
	General *general;
	Fort *fort;
	Town *town;
	// TODO: тип клітинки: гори, рівнини, моря !!!
	
	// автоматичний конструктор пустої клітинки
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

