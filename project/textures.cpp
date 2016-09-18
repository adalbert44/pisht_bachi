#include "textures.h"
#include "basic_classes.h"


GLuint Load(GLuint& temp, std::string b)
{
    char b1[300]{};
    for (int i=0; i<(int)b.size(); i++)
    b1[i]=b[i];
    temp = ilLoadImage(b1);
    glGenTextures(1, &temp);
    glBindTexture (GL_TEXTURE_2D, temp);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//Вирівнювання текстури по байту
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return temp;
}

void LoadAll()
{
    GLuint tex;
    name[0].pb("Napoleon Bonapart");
    Load(tex, "generals\\France\\Napoleon.png");
    general_sprite[name[0][0]] = tex;
    name[0].pb("Karl the Great");
    Load(tex, "generals\\France\\Karl the Great.png");
    general_sprite[name[0][1]] = tex;
    name[0].pb("Francisk II");
    Load(tex, "generals\\France\\Francisk.png");
    general_sprite[name[0][2]] = tex;
    name[1].pb("Otto fon Bismark");
    Load(tex, "generals\\Germany\\Otto fon Bismark.png");
    general_sprite[name[1][0]] = tex;
    name[1].pb("Angela Merkel");
    Load(tex, "generals\\Germany\\Merkel.png");
    general_sprite[name[1][1]] = tex;
    name[1].pb("Adolf Hitler");
    Load(tex, "generals\\Germany\\Hitler.png");
    general_sprite[name[1][2]] = tex;
    name[2].pb("Bohdan Hmelnitskiy");
    Load(tex, "generals\\Ukraine\\Hmelnitskiy.png");
    general_sprite[name[2][0]] = tex;
    name[2].pb("Volodymyr Velykiy");
    Load(tex, "generals\\Ukraine\\Volodymyr.png");
    general_sprite[name[2][1]] = tex;
    name[2].pb("Petro Poroshenko");
    Load(tex, "generals\\Ukraine\\Poroshenko.png");
    general_sprite[name[2][2]] = tex;
    name[2].pb("Ivan Mazepa");
    Load(tex, "generals\\Ukraine\\Mazepa.png");
    general_sprite[name[2][3]] = tex;
    name[2].pb("Stepan Bandera");
    Load(tex, "generals\\Ukraine\\Bandera.png");
    general_sprite[name[2][4]] = tex;
    name[3].pb("Iosif Stalin");
    Load(tex, "generals\\Russia\\Stalin.png");
    general_sprite[name[3][0]] = tex;
    name[3].pb("Katerina II");
    Load(tex, "generals\\Russia\\Katerina.png");
    general_sprite[name[3][1]] = tex;
    name[3].pb("Petr I");
    Load(tex, "generals\\Russia\\Petr.png");
    general_sprite[name[3][2]] = tex;
    name[4].pb("Avraam Linkoln");
    Load(tex, "generals\\USA\\Linkoln.png");
    general_sprite[name[4][0]] = tex;
    name[4].pb("Barak Obama");
    Load(tex, "generals\\USA\\Obama.png");
    general_sprite[name[4][1]] = tex;
    name[4].pb("George Washington");
    Load(tex, "generals\\USA\\Washington.png");
    general_sprite[name[4][2]] = tex;
    name[5].pb("Elizabeth II");
    Load(tex, "generals\\USA\\Elizabeth.png");
    general_sprite[name[5][0]] = tex;
    name[5].pb("Richard Lionheart");
    Load(tex, "generals\\USA\\Richard.png");
    general_sprite[name[5][1]] = tex;
    name[5].pb("Richard Lionheart");
    Load(tex, "generals\\USA\\Richard.png");
    general_sprite[name[5][1]] = tex;


}


