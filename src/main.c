#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define M_PI 3.14159265358979323846

int score1 = 0, score2 = 0;
char score1_str[10], score2_str[10];
int player1 = 0, player2 = 0, player3 = 0, player4 = 0;
char player1_str[10], player2_str[10], player3_str[10], player4_str[10];
int referee = 0;
char referee_str[10];

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
        // player 1 in the left
        if (i == 0)
        {
            x = -0.5f;
            y = 0.0f;
        }
        // player 2 in the left
        else if (i == 1)
        {
            x = -0.8f;
            y = 0.0f;
        }

        // player 3 in the right
        else if (i == 2)
        {
            x = 0.5f;
            y = 0.0f;
        }

        // player 4 in the right
        else if (i == 3)
        {
            x = 0.8f;
            y = 0.0f;
        }

        // player 5 in the center
        else
        {
            x = 0.0f;
            y = 0.0f;
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

    // Draw score board and in the board draw the score of each team starting from 0
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.2f, 0.6f);
    glVertex2f(-0.2f, 0.8f);
    glVertex2f(0.2f, 0.8f);
    glVertex2f(0.2f, 0.6f);
    glEnd();

    // Draw the score of team 1
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(-0.1f, 0.7f);
    // display the score of team 1
    sprintf(score1_str, "%d", score1);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *)score1_str);
    // Draw the score of team 2
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(0.1f, 0.7f);
    sprintf(score2_str, "%d", score2);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *)score2_str);

    // Swap the buffers to display the result
    glutSwapBuffers();
}

void update_screen()
{
    score1 = rand() % 10;
    score2 = rand() % 10;
    glutPostRedisplay();
    glutTimerFunc(1000.0f / 60.0f, update_screen, 0);
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
    glutTimerFunc(0, update_screen, 0);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}