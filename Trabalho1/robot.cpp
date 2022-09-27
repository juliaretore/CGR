
#include <GL/glut.h>
  
static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;
GLUquadricObj *pObj;


// Change viewing volume and viewport.  Called when window is resized  
void ChangeSize(int w, int h){  
    GLfloat fAspect;  
  
    // Prevent a divide by zero  
    if(h==0) h=1;  
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
}  
   
// This function does any needed initialization on the rendering context.  Here it sets up and initializes the lighting for the scene.  
void SetupRC(){  
    // Light values and coordinates  
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };  
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  
    GLfloat  lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };  
  
    glEnable(GL_DEPTH_TEST);    // Hidden surface removal  
    glFrontFace(GL_CCW);        // Counter clock-wise polygons face out  
    glEnable(GL_CULL_FACE);     // Do not calculate inside  
  
    // Enable lighting  
    glEnable(GL_LIGHTING);  
  
    // Setup and enable light 0  
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);  
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);  
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);  
    glEnable(GL_LIGHT0);  
  
    // Enable color tracking  
    glEnable(GL_COLOR_MATERIAL);  
      
    // Set Material properties to follow glColor values  
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  
  
    // Black blue background  
    glClearColor(0.25f, 0.25f, 0.50f, 1.0f);  

}  
  
// Respond to arrow keys (rotate snowman)
void SpecialKeys(int key, int x, int y){  
    if(key==GLUT_KEY_LEFT) yRot-=5.0f;  
    if(key==GLUT_KEY_RIGHT) yRot+=5.0f;
    if(key==GLUT_KEY_UP) xRot-=5.0f; 
    if(key==GLUT_KEY_DOWN) xRot+=5.0f;   
                  
    xRot = (GLfloat)((const int)xRot % 360);  
    yRot = (GLfloat)((const int)yRot % 360);  
  
    // Refresh the Window  
    glutPostRedisplay();  
}


void DrawSphere(float x, float y, float r){
    glPushMatrix(); 
        glTranslatef(x,y,0.0);
        glutSolidSphere(r,26,13);   
	glPopMatrix();
}

void DrawBust(float x, float y, float r){
    glPushMatrix(); 
        glTranslatef(x,y,0.0);
        glScalef(1.8,1.0,1.2);
        glColor3ub(128,128,128);
        glutSolidSphere(r,26,13);   
	glPopMatrix();

    glPushMatrix(); 
        glTranslatef(x,y-0.3,0.0);
        glScalef(1.8,1.0,1.2);
        glColor3ub(128,128,128);
        glutSolidSphere(r*0.8,26,13);   
	glPopMatrix();
}

void DrawCube(float x, float y, float height, float prop){
    glPushMatrix(); 
        glTranslatef(x,y,0.0);
        glScalef(0.5,prop,0.5);
        glutSolidCube(height); 
	glPopMatrix();
}

void DrawPelvis(float x, float y){
    glPushMatrix(); 
        glTranslatef(x,y,0.0);
        glRotatef(90,0,0,1);
        glScalef(0.4,1.1,0.5);
        glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(x,y,0.0);
        glScalef(0.3,0.9,0.5);
        glutSolidCube(0.5);
    glPopMatrix();
}


void DrawFeet(float x, float y){
    glPushMatrix(); 
        glTranslatef(x,y,0.0);
        glRotatef(90,0,0,1);
        glScalef(0.3,0.9,1.5);
        glutSolidCube(0.2);
    glPopMatrix();
}

void DrawHand(float x, float y){
    glPushMatrix(); 
        glTranslatef(x,y,0.0);
        glRotatef(90,1,0,0);

		gluCylinder(pObj,0.05,0.05,0.1,26,13);
    glPopMatrix();

}

// Called to draw scene  
void RenderScene(void){  
    // glClearColor(0.2f, 0.6f, 1.0f, 0.4f);
    // Clear the window with current clearing color  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();

	// Move object back and do in place rotation  
	glTranslatef(0.0f, -1.0f, -5.0f);  
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);  

	// Draw something  
	pObj = gluNewQuadric();  
	gluQuadricNormals(pObj, GLU_SMOOTH);      

    //Head
    glColor3ub(200,200,200);
    DrawSphere(0.0, 2.2, 0.15);

    //Bust
    glColor3ub(128,128,128);
    DrawBust(0.0,1.8,0.3);

    //Left Arm
    glColor3ub(128,128,128);
    DrawSphere(-0.58, 1.95, 0.14);
    DrawSphere(-0.58, 1.37, 0.12);

    glColor3ub(255,255,255);
    DrawCube(-0.58, 1.7, 0.3, 1.9);
    DrawCube(-0.58, 1.03, 0.4, 1.2);

    //Left Arm
    glColor3ub(128,128,128);
    DrawSphere(0.58, 1.95, 0.14);
    DrawSphere(0.58, 1.37, 0.12);

    glColor3ub(255,255,255);
    DrawCube(0.58, 1.7, 0.3, 1.9);
    DrawCube(0.58, 1.03, 0.4, 1.2);

    //Hands
    glColor3ub(128,128,128);
    DrawHand(0.58, 0.84);
    DrawHand(-0.58, 0.84);

    //Pelvis
    glColor3ub(255,255,255);
    DrawPelvis(0.0, 1.3);

    //Left Leg
    glColor3ub(128,128,128);
    DrawSphere(-0.19, 1.12, 0.11);
    DrawSphere(-0.19, 0.55, 0.11);

    glColor3ub(255,255,255);
    DrawCube(-0.19, 0.83, 0.3, 1.6);
    DrawCube(-0.19, 0.19, 0.4, 1.4);

    //Right Leg
    glColor3ub(128,128,128);
    DrawSphere(0.19, 1.12, 0.11);
    DrawSphere(0.19, 0.55, 0.11);

    glColor3ub(255,255,255);
    DrawCube(0.19, 0.83, 0.3, 1.6);
    DrawCube(0.19, 0.19, 0.4, 1.4);
    

    //Feets
    glColor3ub(128,128,128);
    DrawFeet(0.19, -0.1);
    DrawFeet(-0.19, -0.1);

         
    // Restore the matrix state  
    glPopMatrix();  
  
    // Buffer swap  
    glutSwapBuffers();  

}    


int main(int argc, char *argv[]){
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(1800, 1200);  
    glutCreateWindow("Robot: Julia Retore"); 
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();   
      
    return 0; 
}
