

#include "all_includes.h"
#include "drawing.h"
#include "textures.h"
#include "basic_classes.h"


int width, height;

GLuint tex;

void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    width = w;
    height = h;
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Display()
{
    glLoadIdentity();
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(0.0, width, height, 0.0, 0.f, -1.f);
    //cout << 1 << "\n";
    glPushMatrix();
        drawHex(11, 200, 200, 100);
    glPopMatrix();

    glutSwapBuffers();
}

void Idle()
{

    glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("ds");

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    glutIdleFunc(Idle);
    glutKeyboardFunc(Keyboard);

    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
    ilSetInteger(IL_KEEP_DXTC_DATA, IL_TRUE);
    ilutEnable(ILUT_GL_AUTODETECT_TEXTURE_TARGET);
    ilutEnable(ILUT_OPENGL_CONV);
    ilutEnable(ILUT_GL_USE_S3TC);


    glutFullScreen();

    LoadAll();

    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glutMainLoop();

    return 0;
}

