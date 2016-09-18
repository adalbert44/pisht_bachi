#include "all_includes.h"
#include "basic_classes.h"


/// ����� ��� ��������� ������ �������� ����� �����
/*void init(vector<string> name[200], map<string, Sprite>& general_sprite)
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
}*/

/// ����� ��� ��������� ���������� �������� �� ������
string new_name(int color)
{
	return name[color][used_generals[color]++];
}

/// ���� ����
Town :: Town(int x, int y, int color)
{
    this->x = x;
    this->y = y;
    this->color = color;
    this->sprite = fort_sprite[color];
}

/// ���� ��������
General::General(Town town)
{
    this->x = town.x;
    this->y = town.y;
    this->color = town.color;
    this->name = new_name(color);
    this->sprite = general_sprite[this->name];
    this->turns_left = 2;
}

/// ���� �������
Fort::Fort(General gen)
{
    this->x = gen.x;
    this->y = gen.y;
    this->color = gen.color;
    this->sprite = fort_sprite[this->color];
    // TODO: ��������� �������� ���� �������� �������
}
	// ����������� �� ��������� ������� �� ������� �����
Fort::Fort(int x, int y, int color)
{
    this->x = x;
    this->y = y;
    this->color = color;
    this->sprite = fort_sprite[color];
}

/// ���� �������


Cell::Cell()
{
    this->color = 0;
    this->general = NULL;
    this->fort = NULL;
    this->town = NULL;
    this->relief = EMPTY;
}
