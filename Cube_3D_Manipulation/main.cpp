#include <GL/freeglut.h>
#include <cmath>

// Globals vairable for camera control
int lastX = 0;
int lastY = 0;
float cameraYaw = 0.0f;
float cameraPitch = 0.0f;
float cameraDistance = 100.0f;

// Camera configuration
void setupCamera() {
    glTranslatef(0.0f, 0.0f, -cameraDistance);
    glRotatef(-cameraPitch, 1.0f, 0.0f, 0.0f);
    glRotatef(-cameraYaw, 0.0f, 1.0f, 0.0f);
}

// Renderization
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    setupCamera(); 

    // Desenhar o cubo
    glColor3f(0.0, 1.0, 0.0);  // Cube color - For this example i chose green color.
    glutSolidCube(20.0);       // Cube with 20 of dimension

    // Edges drawing
    glColor3f(0.0, 0.0, 0.0); // Cube edges color - For this example i chose black color.
    glutWireCube(20.0);       // Edges with 20 of dimension

    glutSwapBuffers();
}

// Mouse movement and camera 
void updateCamera(int x, int y) {
    int deltaX = x - lastX;
    int deltaY = y - lastY;

    lastX = x;
    lastY = y;

    cameraYaw += deltaX * 0.1f;
    cameraPitch += deltaY * 0.1f;


    // Limit pitch angle between -90 and 90 degrees to avoid inversions
    if (cameraPitch > 90.0f) cameraPitch = 90.0f;
    if (cameraPitch < -90.0f) cameraPitch = -90.0f;

    glutPostRedisplay(); // Redesenhar a cena
}

// Window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 1000.0); // Defining the perspective
    glMatrixMode(GL_MODELVIEW);
}

// Updating the movement
void onMouseMove(int x, int y) {
    updateCamera(x, y);
}

// Initialize 
void onMouseClick(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        lastX = x;
        lastY = y;
    }
}

// Mouse Wheel movement and camera 
void onMouseWheel(int wheel, int direction, int x, int y) {
    if (direction == 1)
        cameraDistance -= 5.0f;
    else
        cameraDistance += 5.0f;

    if (cameraDistance < 10.0f)
        cameraDistance = 10.0f;

    glutPostRedisplay(); // Scene redrawing
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cube 3D simple manipulation with the mouse");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.5, 0.7, 1.0, 1.0); // Background color 

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(onMouseMove);
    glutMouseFunc(onMouseClick);
    glutMouseWheelFunc(onMouseWheel); 

    glutMainLoop();

    return 0;
}
