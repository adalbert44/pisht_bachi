#include "drawing.h"

void drawHex(GLuint texture, ld cx, ld cy, ld r = 100)
{

    glPushMatrix();
        glBegin(GL_POLYGON);
            glColor4f(0.367, 0.785, 0.05, 0.9);
            glVertex2f(r/2 + cx, -r * cos(PI/6) + cy);
            glVertex2f(cx + r, cy);
            glVertex2f(r/2 + cx, +r * cos(PI/6) + cy);
            glVertex2f(-r/2 + cx, +r * cos(PI/6) + cy);
            glVertex2f(cx - r, cy);
            glVertex2f(-r/2 + cx, -r * cos(PI/6) + cy);
        glEnd();
        glLineWidth(5);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
        glColor4f(1,1,1,1);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(cx - 2*r/3, cy - 2*r/3 + 7);
            glTexCoord2f(1, 0); glVertex2f(cx + 2*r/3, cy - 2*r/3 + 7);
            glTexCoord2f(1, 1); glVertex2f(cx + 2*r/3, cy + 2*r/3 + 7);
            glTexCoord2f(0, 1); glVertex2f(cx - 2*r/3, cy + 2*r/3 + 7);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glBegin(GL_LINES);
        glColor3f(0,0,0);
        glVertex2f(r/2 + cx + 1, -1 -r * cos(PI/6) + cy);
        glVertex2f(cx + r + 1, cy);
        glVertex2f(cx + r + 1, cy);
        glVertex2f(r/2 + cx + 1, 1 +r * cos(PI/6) + cy);
        glVertex2f(r/2 + cx + 1, 1 +r * cos(PI/6) + cy);
        glVertex2f(-1 -r/2 + cx, 1 + r * cos(PI/6) + cy);
        glVertex2f(-1 -r/2 + cx, 1 + r * cos(PI/6) + cy);
        glVertex2f(cx - r - 1, cy);
        glVertex2f(cx - r - 1, cy);
        glVertex2f(-1 -r/2 + cx, -1 -r * cos(PI/6) + cy);
        glVertex2f(-1 -r/2 + cx, -1 -r * cos(PI/6) + cy);
        glVertex2f(r/2 + cx + 1, -1 -r * cos(PI/6) + cy);
    glEnd();

}
