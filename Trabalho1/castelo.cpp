
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

void DrawTower(float x, float y, float z){
    glColor3f(0.7f, 0.7f, 0.7f); 
    glPushMatrix(); 
        glTranslatef(x,y,z);
        glRotatef(90, 1,0,0);
		gluCylinder(pObj,0.3,0.3,0.9,26,13);
	glPopMatrix(); 

	glColor3f(0.75f, 0.75f, 0.75f); 
    glPushMatrix(); 
        glTranslatef(x, y+0.1, z);
        glRotatef(90, 1,0,0);
		gluCylinder(pObj,0.35,0.35,0.3,26,13);
	glPopMatrix(); 

	glColor3f(0.3f, 0.3f, 0.3f); 
    glPushMatrix(); 
        glTranslatef(x, y+0.4, z);
        glRotatef(90, 1,0,0);
		gluCylinder(pObj,0.0,0.35,0.3,26,13);
	glPopMatrix();
}

void DrawSurface(float x1, float x2, float y1, float y2, float z){
    glBegin(GL_QUADS);
    glVertex3f(x1, y1, z);
    glVertex3f(x1, y2, z);
    glVertex3f(x2, y2, z);
    glVertex3f(x2, y1, z);
    glEnd();
}

void DrawSurfaceWall(float x1, float x2, float y1, float y2, float z){
    glColor3f(0.5f, 0.5f, 0.5f); 
    DrawSurface(x2/2-0.4, x2, y1, y2, z);
    DrawSurface(x1, x2, ((y1+y2)/2), y2, z);
    DrawSurface(x1, x1/2+0.4, y1, y2, z);
}

void DrawWall(float x1, float x2, float y1, float y2, float z1, float z2){
    //paredes
    DrawSurfaceWall(x1, x2, y1, y2, z1);
    glPushMatrix(); 
        glRotatef(180, 0,1,0);
        DrawSurfaceWall(x1, x2, y1, y2, -z2);
    glPopMatrix();

    glPushMatrix(); 
        glRotatef(90,1,0,0);
        //tampa de cima
        DrawSurface(x1, x2, z1, z2, -0.7);
        //chao nas laterais
        DrawSurface(x1, ((x1+x2)/2)-0.1, z1, z2, -0.1);	
        DrawSurface(((x1+x2)/2)+0.1, x2, z1, z2, -0.1);	
    glPopMatrix();

    glPushMatrix(); 
        glRotatef(-90,1,0,0);
        // chao
        DrawSurface(x1, ((x1+x2)/2)-0.1, z1, z2, 0.1);	
        DrawSurface(((x1+x2)/2)+0.1, x2, z1, z2, 0.1);	
    glPopMatrix();

    glPushMatrix(); 
        glRotatef(90,0,1,0);
        //tampas laterais
        DrawSurface(z1, z2, y1, y2, ((x1+x2)/2)+0.1);	
        DrawSurface(z1, z2, y2, y1, ((x1+x2)/2)-0.1);	
    glPopMatrix();
}

void DrawGrass(){
    glColor3f(0.0f, 1.0f, 0.0f); 
    glBegin(GL_QUADS);
        glVertex3f(8, 0.1, 8);
        glVertex3f(8, 0.1, -8);
        glVertex3f(-8, 0.1, -8);
        glVertex3f(-8, 0.1, 8);
    glEnd();
}
  
void DrawTree(float height, float r,float x, float z){
    glColor3f(0.5f, 0.35f, 0.05f);
    glPushMatrix(); 
        glTranslatef(x,0.1,z);
        glRotatef(-90, 1,0,0);
        gluCylinder(pObj, r, r, 0.3, 26, 13);
    glPopMatrix();

    glColor3f(0.2f, 1.0f, 0.0f); 
    glPushMatrix(); 
        glTranslatef(x,0.3,z);
        glRotatef(-90, 1,0,0);
        gluCylinder(pObj, r+0.15, 0.0, height, 26, 13);
    glPopMatrix();

    glPushMatrix(); 
        glTranslatef(x,0.5,z);
        glRotatef(-90, 1,0,0);
        gluCylinder(pObj, r+0.1, 0.0, height, 26, 13);
    glPopMatrix();
}

// Called to draw scene  
void RenderScene(void){  
    glClearColor(0.2f, 0.6f, 1.0f, 0.4f);
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

    DrawGrass();

    DrawTower(-1, 1,  1);
    DrawTower(-1, 1, -1);
    DrawTower( 1, 1,  1);
    DrawTower( 1, 1, -1);

    DrawWall(-1, 1, 0.1, 0.7, -1.2, -0.8);
    DrawWall(-1, 1, 0.1, 0.7, 0.8, 1.2); 
    glPushMatrix(); 
        glRotatef(90, 0,1,0);
        DrawWall(-1, 1, 0.1, 0.7, -1.2, -0.8);
        DrawWall(-1, 1, 0.1, 0.7, 0.8, 1.2);
    glPopMatrix();

    DrawTree(0.4, 0.03, -1.4, 1.4);
    DrawTree(0.5, 0.06, -1.8, 1.9);
    DrawTree(0.5, 0.05, 1.4, 1.6);
    DrawTree(0.4, 0.07, -1.5, -1.7);
    DrawTree(0.5, 0.06, 0.6, -1.9);
    DrawTree(0.2, 0.05, 0.2, -2.3);
          
    // Restore the matrix state  
    glPopMatrix();  
  
    // Buffer swap  
    glutSwapBuffers();  

}    


int main(int argc, char *argv[]){
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(1800, 1200);  
    glutCreateWindow("Castelo: Julia Retore"); 
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);  
    glutDisplayFunc(RenderScene);  
    SetupRC();  
    glutMainLoop();   
      
    return 0; 
}
