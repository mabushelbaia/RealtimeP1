#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define M_PI 3.14159265358979323846

void display()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the border
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.95f, -0.65f);
    glVertex2f(-0.95f, 0.65f);
    glVertex2f(0.95f, 0.65f);
    glVertex2f(0.95f, -0.65f);
    glEnd();

    // Draw the line
    glLineWidth(5.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.65f);
    glVertex2f(0.0f, 0.65f);
    glEnd();

    // Draw the outer circle
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(5.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 360; i++)
    {
        glVertex2f(0.22f * cos(i * M_PI / 180.0f), 0.22f * sin(i * M_PI / 180.0f));
    }
    glEnd();

    // Draw the inner circle
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(5.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 360; i++)
    {
        glVertex2f(0.12f * cos(i * M_PI / 180.0f), 0.12f * sin(i * M_PI / 180.0f));
    }
    glEnd();

    // Draw the circle border
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 360; i++)
    {
        glVertex2f(0.22f * cos(i * M_PI / 180.0f), 0.22f * sin(i * M_PI / 180.0f));
    }
    glEnd();
    // Draw players
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < 5; i++)
    {
        float x, y;
        if (i == 0) // Center player
        {
            x = 0.0f;
            y = 0.0f;
        }
        else if (i < 3) // Left half
        {
            x = -0.5f + (float)i * 0.25f;
            y = -0.3f + (float)rand() / RAND_MAX * 0.6f;
        }
        else // Right half
        {
            x = 0.25f + (float)(i - 3) * 0.25f;
            y = -0.3f + (float)rand() / RAND_MAX * 0.6f;
        }

        // Draw player
        glColor3f(1.0f, 0.0f, 0.0f);
        glLineWidth(5.0f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= 360; i++)
        {
            glVertex2f(0.05f * cos(i * M_PI / 180.0f) + x, 0.05f * sin(i * M_PI / 180.0f) + y);
        }
        glEnd();

        // Draw player number
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos2f(x - 0.01f, y - 0.025f);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0' + i + 1);
    }

    // Swap the buffers to display the result
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(2000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hockey Field");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -0.75, 0.75, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}