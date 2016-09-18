#ifndef CLASSES_H

    #define CLASSES_H
    #include "all_includes.h"


    //void init(vector<string> name[200], map<string, Sprite>& general_sprite);
    string new_name(int);

    class Town
    {
    public:
        int x, y, color;
        Sprite sprite;

        // конструктор міста від координат клітинки та кольору нації
        Town(int, int, int);
    };

    class General
    {
    public:
        int x, y, color, turns_left;
        string name;
        Sprite sprite;

        // конструктор від рідного міста генерала
        General(Town);
    };

    class Fort
    {
    public:
        int x, y, color;
        Sprite sprite;

        // конструктор від генерала, який побудував фортецю
        Fort(General);
        // конструктор від координат клітинки та кольору нації
        Fort(int, int, int);
    };

    class Cell
    {
    public:
        int color;
        General *general;
        Fort *fort;
        Town *town;
        Relief relief;


        // автоматичний конструктор пустої клітинки
        Cell();
    };

#endif // CLASSES_H
