#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stb_image.h>
#include <SOIL/SOIL.h>

float zoom = 1.0f;

float materialBola[3][3] = {
    {0.3f, 0.0f, 0.0f, 1.0f}, //Ambiente
    {0.8f, 0.2f, 0.2f, 1.0f}, //Difusa
    {1.0f, 0.5f, 0.5f, 1.0f}  //Especular
};

float materialBule[3][3] = {
    {1.0f, 1.0f, 0.2f, 1.0f}, //Ambiente
    {0.8f, 0.8f, 0.3f, 1.0f}, //Difusa
    {1.0f, 0.5f, 0.5f, 1.0f}  //Especular
};

float materialRosca[3][3] = {
    {0.2f, 1.0f, 0.3f, 1.0f}, //Ambiente
    {0.2f, 0.2f, 0.3f, 1.0f}, //Difusa
    {1.0f, 0.5f, 0.5f, 1.0f}  //Especular
};

float materialParede[3][3] = {
    {0.0f, 1.0f, 1.0f, 1.0f}, //Ambiente
    {0.2f, 0.2f, 0.3f, 1.0f}, //Difusa
    {0.0f, 0.0f, 0.5f, 1.0f}  //Especular
};

float materialChao[3][3] = {
    {0.0f, 1.0f, 1.0f, 1.0f}, //Ambiente
    {0.5f, 0.2f, 0.3f, 1.0f}, //Difusa
    {0.0f, 0.0f, 0.5f, 1.0f}  //Especular
};

void iluminacao(){

    float luz[4][4] = {
        {2.0, 2.0, 0.0, 0.0},  //Posicao
        {0.5, 0.5, 0.5, 1.0},  //Difusa
        {0.5, 0.5, 0.5, 1.0},  //Especular
        {0.4, 0.4, 0.4, 1.0}   //Ambiente
    };

    glLightfv(GL_LIGHT0, GL_POSITION, &luz[0][0]);
    glLightfv(GL_LIGHT0, GL_AMBIENT, &luz[3][0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, &luz[1][0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, &luz[2][0]);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

int init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    iluminacao();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, 1.0, 0.1, 100.0);

    gluLookAt(2.0, 1.5, 3.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glScalef(zoom, zoom, zoom);

    //Desenhar uma esfera
    glPushMatrix();
    glTranslatef(-0.4, -0.2, -0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, &materialBola[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &materialBola[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &materialBola[2][0]);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0f); //Brilho

    glutSolidSphere(0.4f, 40, 40);
    glPopMatrix();

    //Desenhar um donut
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(0.7, 0.0, 0.4);

    glMaterialfv(GL_FRONT, GL_AMBIENT, &materialRosca[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &materialRosca[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &materialRosca[2][0]);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);

    glutSolidTorus(0.1f, 0.5f, 100.0f, 100.0f);
    glPopMatrix();

    //Chao
    glPushMatrix();
    glTranslatef(0.3, -0.65, 0.45);
    glScalef(4.7, 0.5, 5.0);

    glMaterialfv(GL_FRONT, GL_AMBIENT, &materialChao[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &materialChao[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &materialChao[2][0]);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);

    glutSolidCube(0.5f);
    glPopMatrix();

    //Parede esquerda
    glColor3f(0.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-1.0, -0.27, 0.37);
    glScalef(0.5, 2.0, 5.3);

    glMaterialfv(GL_FRONT, GL_AMBIENT, &materialParede[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &materialParede[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &materialParede[2][0]);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);

    glutSolidCube(0.5f);
    glPopMatrix();

    //Parede direita
    glColor3f(0.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.23, -0.27, -0.8);
    glScalef(5.0, 2.0, 0.5);

    glMaterialfv(GL_FRONT, GL_AMBIENT, &materialParede[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &materialParede[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &materialParede[2][0]);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);

    glutSolidCube(0.5f);
    glPopMatrix();

    //Desenhar um bule
    glPushMatrix();
    glRotatef(65.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1.0f, -0.2f, 0.4f);

    glMaterialfv(GL_FRONT, GL_AMBIENT, &materialBule[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &materialBule[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &materialBule[2][0]);
    glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);
    glCullFace(GL_FRONT);
    glutSolidTeapot(0.4f);
    glPopMatrix();

    glFlush();
}

void teclaApertada(unsigned char key, int x, int y){
    if(key == 'w'){
        zoom = zoom * 1.1f;
    }
    if(key == 's'){
        zoom = zoom * 0.9f;
    }

    glutPostRedisplay();
}


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Resposta exercicio 5");

    init();
    glutKeyboardFunc(teclaApertada);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
