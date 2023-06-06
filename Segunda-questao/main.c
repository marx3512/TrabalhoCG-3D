#include <windows.h>
#include <GL/freeglut.h>
#include <GL/glut.h>

#define tamanhoTela 500
#define tamanhoBule 1.2f

float rotacaoY = 0.0f;
float brilhoBule = 80.0f;

float materialBule[3][3] = {
    {1.0f, 1.0f, 0.2f, 1.0f}, //Ambiente
    {0.8f, 0.8f, 0.3f, 1.0f}, //Difusa
    {1.0f, 1.0f, 1.0f, 1.0f}  //Especular
};

void rotacionarBule(){
    rotacaoY += 0.4f;

    glutPostRedisplay();

    glutTimerFunc(16, rotacionarBule, 0);
}

void iluminacao(){

    float luzGlobal[4] = {0.25f, 0.25f, 0.25f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobal);

    float luz[4][4] = {
        {1.0, 1.5, 0.5, 0.0},  //Posicao
        {0.8, 0.8, 0.8, 1.0},  //Difusa
        {0.5, 1.0, 1.0, 1.0},  //Especular
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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    iluminacao();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    //Superior esquerdo
    glViewport( 0.f, tamanhoTela / 2.f, tamanhoTela / 2.f, tamanhoTela / 2.f );
    glPushMatrix();
    gluLookAt(0.0, 0.0, 0.6,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glRotatef(rotacaoY, 0.0f, 1.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT, &materialBule[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &materialBule[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &materialBule[2][0]);
    glMaterialf(GL_FRONT, GL_SHININESS, brilhoBule);

    glutSolidTeapot(tamanhoBule);
    glPopMatrix();

    //Inferior esquerdo
    glViewport( 0.f, 0.f, tamanhoTela / 2.f, tamanhoTela / 2.f );
    glPushMatrix();
    gluLookAt(0.0, 0.6, 0.05,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glRotatef(rotacaoY, 0.0f, 1.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT, &materialBule[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &materialBule[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &materialBule[2][0]);
    glMaterialf(GL_FRONT, GL_SHININESS, brilhoBule);

    glutSolidTeapot(tamanhoBule);
    glPopMatrix();

    //Superior direito
    glViewport( tamanhoTela / 2.f, tamanhoTela / 2.f, tamanhoTela / 2.f, tamanhoTela / 2.f );
    glPushMatrix();
    gluLookAt(0.6, 0.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glRotatef(rotacaoY, 0.0f, 1.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT, &materialBule[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &materialBule[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &materialBule[2][0]);
    glMaterialf(GL_FRONT, GL_SHININESS, brilhoBule);

    glutSolidTeapot(tamanhoBule);
    glPopMatrix();

    //Inferior direito
    glMatrixMode(GL_PROJECTION);
    glViewport( tamanhoTela / 2.f, 0.f, tamanhoTela / 2.f, tamanhoTela / 2.f );
    glPushMatrix();

    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 500.0);
    gluLookAt(1.8, 1.5, 2.5,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(rotacaoY, 0.0f, 1.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT, &materialBule[0][0]);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &materialBule[1][0]);
    glMaterialfv(GL_FRONT, GL_SPECULAR, &materialBule[2][0]);
    glMaterialf(GL_FRONT, GL_SHININESS, brilhoBule);

    glutSolidTeapot(tamanhoBule);
    glPopMatrix();


    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Resposta exercicio 5");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, rotacionarBule, 0);
    glutMainLoop();
    return 0;
}
