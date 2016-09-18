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

        // ����������� ���� �� ��������� ������� �� ������� �����
        Town(int, int, int);
    };

    class General
    {
    public:
        int x, y, color, turns_left;
        string name;
        Sprite sprite;

        // ����������� �� ������ ���� ��������
        General(Town);
    };

    class Fort
    {
    public:
        int x, y, color;
        Sprite sprite;

        // ����������� �� ��������, ���� ��������� �������
        Fort(General);
        // ����������� �� ��������� ������� �� ������� �����
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


        // ������������ ����������� ����� �������
        Cell();
    };

#endif // CLASSES_H
