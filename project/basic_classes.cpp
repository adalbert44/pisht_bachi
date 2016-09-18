#include "all_includes.h"
#include "basic_classes.h"


///Ініціалізація глобальних змінних
std::vector<std::string> name[200];
std::vector<GLuint> fort_sprite(200);
int used_generals[200];
std::map <std::string, GLuint> general_sprite;

/// метод для генерації наступного генерала із списку
string new_name(int color)
{
	return name[color][used_generals[color]++];
}

/// клас міста
Town :: Town(int x, int y, int color)
{
    this->x = x;
    this->y = y;
    this->color = color;
    this->sprite = fort_sprite[color];
}

/// клас генерала
General::General(Town town)
{
    this->x = town.x;
    this->y = town.y;
    this->color = town.color;
    this->name = new_name(color);
    this->sprite = general_sprite[this->name];
    this->turns_left = 2;
}

/// клас фортеці
Fort::Fort(General gen)
{
    this->x = gen.x;
    this->y = gen.y;
    this->color = gen.color;
    this->sprite = fort_sprite[this->color];
    // TODO: знищувати генерала після побудови фортеці
}
	// конструктор від координат клітинки та кольору нації
Fort::Fort(int x, int y, int color)
{
    this->x = x;
    this->y = y;
    this->color = color;
    this->sprite = fort_sprite[color];
}

/// клас клітинки


Cell::Cell()
{
    this->color = 0;
    this->general = NULL;
    this->fort = NULL;
    this->town = NULL;
    this->relief = EMPTY;
}
