#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <cmath>

// --- variavel ---
GLfloat charX = 0.0f;
GLfloat charY = 0.5f;
GLfloat charZ = 0.0f;

// Camera --------------------------------------------------
GLfloat cameraYaw = 0.0f;
GLfloat cameraPitch = 0.0f;
//-- camera minecraft motion
int lastMouseX = 0;
int lastMouseY = 0;
bool firstMouse = true;
GLfloat fAspect;

// pular --------------------------------------------
bool isJumping = false;
GLfloat jumpVelocity = 0.0f;
GLfloat gravity = -0.05f;

// GLfloat animatedCubeX = -10.f;
// GLfloat slideSpeed = 0.1f;
GLfloat cubeRotationAngle = 0.0f;


void updatemouse(float newx, float newy){

}
// --- Drawing Functions ---
void drawPlane()
{
    glColor3f(0.0f, 0.93f, 0.0f); // Gray color
    glBegin(GL_QUADS);
    for (float x = -20.0f; x < 20.0f; x += 1.0f)
    {
        for (float z = -20.0f; z < 20.0f; z += 1.0f)
        {
            glVertex3f(x, 0.0f, z);
            glVertex3f(x, 0.0f, z + 1.0f);
            glVertex3f(x + 1.0f, 0.0f, z + 1.0f);
            glVertex3f(x + 1.0f, 0.0f, z);
        }
    }
    glEnd();
}

void drawTree()
{
    // caule
    glColor3f(0.5f, 0.25f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 1.5f, 0.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // folhas
    glColor3f(0.0f, 0.4f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, 0.0f);
    glutSolidCube(2.3f);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 3.5f, 0.0f);
    glutSolidCube(1.5f);
    glPopMatrix();

    // Maçã Redonda
    glColor3f(0.5f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(-1.2f, 3.0f, 1.0f);
    glutSolidSphere(0.25f, 20, 20);
    glPopMatrix();

    // Caule Maçã
    glColor3f(0.f, 0.f, 0.f);
    glPushMatrix();
    glTranslatef(-1.2f, 3.2f, 1.0f);
    glScalef(0.1f, 0.25f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawCharacter()
{
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for the character = STEVE
    glPushMatrix();
    // Move the character to its current position
    glTranslatef(charX, charY, charZ);
    glutSolidCube(1.0f); // Draw the cube
    glPopMatrix();
}

void drawRotatingCube()
{
    glColor3f(1.0f, 0.f, 0.f); // Red color
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, -5.0f);
    glRotatef(cubeRotationAngle, 1.0f, 1.0f, 0.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// --- Main Rendering and Camera Logic ---
void Desenha(void)
{
    GLfloat lightPosition[] = { 10.0f, 15.0f, 10.0f, 1.0f };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // Calculate the camera's target point based on mouse rotation
    GLfloat targetX = charX + cos(cameraYaw * M_PI / 180.0f);
    GLfloat targetY = charY + sin(cameraPitch * M_PI / 180.0f) + 1.0f;
    GLfloat targetZ = charZ - sin(cameraYaw * M_PI / 180.0f);

    // Position the camera behind the character and look at the calculated target
    gluLookAt(charX, 2.0f, charZ + 5.0f, // Camera position, changed from 1.0f to 2.0f
              targetX, targetY, targetZ, // Point the camera is looking at
              0.0f, 1.0f, 0.0f);         // Up vector

    drawPlane();

    // Draw the tree in a fixed location
    glPushMatrix();
    glTranslatef(5.0f, 0.0f, -5.0f);
    drawTree();
    glPopMatrix();

    drawCharacter();

    drawRotatingCube();

    glutSwapBuffers();
}

// --- Event Handlers ---
void EspecificaParametrosVisualizacao(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, fAspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void update(int value)
{
    if (isJumping)
    {
        charY += jumpVelocity;
        jumpVelocity += gravity;

        if (charY <= 0.5f)
        {
            charY = 0.5f;
            isJumping = false;
            jumpVelocity = 0.0f;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void animateRotatingCube(int value)
{
    // Increment the rotation angle for a spinning effect
    cubeRotationAngle += 1.0f;
    if (cubeRotationAngle > 360.0f)
    {
        cubeRotationAngle -= 360.0f;
    }

    glutPostRedisplay(); // Redraw the scene
    // Call the timer function again to continue the animation
    glutTimerFunc(16, animateRotatingCube, 0);
}

// minecraft camera follows mouse function - craft
void mouseMotion(int x, int y)
{
    if (firstMouse)
    {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false;
    }

    float xoffset = x - lastMouseX;
    float yoffset = lastMouseY - y;
    lastMouseX = x;
    lastMouseY = y;

    float sensitivity = 0.2f;
    cameraYaw += xoffset * sensitivity;
    
    cameraPitch += yoffset * sensitivity;
    updatemouse(xoffset,yoffset);


    if (cameraPitch > 89.0f)
    {
        cameraPitch = 89.0f;
    }
    if (cameraPitch < -89.0f)
    {
        cameraPitch = -89.0f;
    }

    glutPostRedisplay();
}

void GerenciaTeclado(unsigned char key, int x, int y)
{
    GLfloat moveSpeed = 0.5f;

    switch (key)
    {
    case 'w':
        charZ -= moveSpeed;
        break;
    case 's':
        charZ += moveSpeed;
        break;
    case 'a':
        charX -= moveSpeed;
        break;
    case 'd':
        charX += moveSpeed;
        break;
    case ' ': // Jump
        if (!isJumping)
        {
            isJumping = true;
            jumpVelocity = 0.5f;
        }
        break;
    }
    glutPostRedisplay();
}

void AlteraTamanhoJanela(GLint largura, GLint altura)
{
    if (altura == 0)
        altura = 1;
    glViewport(0, 0, largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)largura / (GLfloat)altura, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void Inicializa(void)
{
    glClearColor(0.5f, 0.5f, 0.9f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);       // Enable lighting
    glEnable(GL_COLOR_MATERIAL); // Enable color material
    glEnable(GL_LIGHT0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Third-Person Controller with All Features");

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(GerenciaTeclado);
    glutPassiveMotionFunc(mouseMotion);

    Inicializa();

    glutTimerFunc(16, update, 0);
    glutTimerFunc(16, animateRotatingCube, 0);

    glutMainLoop();
    return 0;
}
