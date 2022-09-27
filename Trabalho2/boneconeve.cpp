// gcc boneconeve.c -lglut -lGL -lGLU -lm && ./a.out
#include <GL/glut.h>
  #include <GL/gl.h>	  // Header File For The OpenGL32 Library
#include <GL/glu.h>	  // Header File For The GLu32 Library
#include <math.h>
#include <unistd.h>
static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;

#define ESCAPE 27
#define NUM_PARTICLES 6000
int angl=265;

struct s_pf {
  float x, y, z, veloc_x, veloc_y, gravity, size, velocity;
} particles[NUM_PARTICLES];

int window; 


//Inicializa um floquinho
void InitFloco(int i){
    // float velocity = (float)(rand()%100)/5000.0; 
    particles[i].velocity = (float)(rand()%100)/5000.0; 
    int angle = (rand()%10) + angl;
    particles[i].veloc_x = cos((M_PI*angle/180.0))*particles[i].velocity;
    particles[i].veloc_y = sin((M_PI*angle/180.0))*particles[i].velocity;
    particles[i].x = ((rand()%40)-20) /10.0; //varia de -20.0 à 20.0
    particles[i].y = 2.5; 
    particles[i].z = (float)((rand()%100)-50)/10.0;  //varia de  0 à 5
    particles[i].gravity = (float)((rand() %10) +2) /100000.0; //varia entre 0.00002 e 0.00007
    particles[i].size = (float)((rand() % 5)+5)/1000.0; //varia entre 0.005 e 0.0010
}

// Inicializa todos os flocos de neve
void InitNeve(int pause){
  int i;
  for(i=0;i<NUM_PARTICLES;i++) InitFloco(i);
}

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


// Called to draw scene  
void RenderScene(void){  
    GLUquadricObj *pObj;
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
    //  gluQuadricOrientation(pObj, GLU_OUTSIDE);
	gluQuadricNormals(pObj, GLU_SMOOTH);

    // Color: white  
	glColor3f(1.0f, 1.0f, 1.0f);  

	// Head 
	glPushMatrix(); // save transform matrix state
		glTranslatef(0.0f, 1.5f, 0.0f);
		gluSphere(pObj, 0.24f, 26, 13);
	glPopMatrix(); // restore transform matrix state

    // Mid Body 
	glPushMatrix(); 
		glTranslatef(0.0f, 1.05f, 0.0f);
		gluSphere(pObj, 0.35f, 26, 13);
	glPopMatrix(); 

    // Bottom Body 
	glPushMatrix(); 
		glTranslatef(0.0f, 0.45f, 0.0f);
		gluSphere(pObj, 0.5f, 26, 13);
	glPopMatrix(); 

    // Color: orange
	glColor3f(1.0f, 0.4f, 0.51f);  

	// Nose
	glPushMatrix();
		glTranslatef(0.0f, 1.5f, 0.2f);
		gluCylinder(pObj, 0.04f, 0.0f, 0.3f, 26, 13);  
	glPopMatrix();  

    // Color: black
    glColor3f(0.1,0.1,0.1);

    // Left eye
	glPushMatrix();
		glTranslatef(0.1f, 1.55f, 0.2f);
        gluSphere(pObj,0.03,8,8);
	glPopMatrix();  
    
    // Right eye
    glPushMatrix();
		glTranslatef(-0.1f, 1.55f, 0.2f);
        gluSphere(pObj,0.03,8,8);
	glPopMatrix();  

    // Buttoms
    glPushMatrix();
		glTranslatef(0.0f, 0.6f, 0.47f);
        gluSphere(pObj,0.03,8,8);
	glPopMatrix(); 

    glPushMatrix();
		glTranslatef(0.0f, 0.5f, 0.49f);
        gluSphere(pObj,0.03,8,8);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(0.0f, 1.15f, 0.33f);
        gluSphere(pObj,0.03,8,8);
	glPopMatrix(); 

    glPushMatrix();
		glTranslatef(0.0f, 1.05f, 0.34f);
        gluSphere(pObj,0.03,8,8);
	glPopMatrix(); 


    // Color: Brown
    glColor3f(0.5f, 0.35f, 0.05f);

    // Left Arm
    glPushMatrix();
		glTranslatef(0.0f,1.2f,0.0f);
        glRotatef(60,0,1,0);
        gluCylinder(pObj,0.04,0.002,0.8,26,13);
	glPopMatrix(); 

    glPushMatrix();
		glTranslatef(0.52f,1.2f,0.3f);
        glRotatef(55,1,0,0);
        gluCylinder(pObj,0.017,0.001,0.15,26,13);
	glPopMatrix(); 

    glPushMatrix();
		glTranslatef(0.52f,1.2f,0.3f);
        glRotatef(-55,1,0,0);
        glRotatef(55,0,1,0);
        gluCylinder(pObj,0.012,0.001,0.15,26,13);
	glPopMatrix(); 


    // Right Arm
    glPushMatrix();
		glTranslatef(0.0f,1.2f,0.0f);
        glRotatef(-60,0,1,0);
        gluCylinder(pObj,0.04,0.002,0.8,26,13);
	glPopMatrix(); 

    glPushMatrix();
		glTranslatef(-0.52f,1.2f,0.3f);
        glRotatef(55,1,0,0);
        gluCylinder(pObj,0.017,0.001,0.15,26,13);
	glPopMatrix(); 

    glPushMatrix();
		glTranslatef(-0.52f,1.2f,0.3f);
        glRotatef(-55,1,0,0);
        glRotatef(-55,0,1,0);
        gluCylinder(pObj,0.012,0.001,0.15,26,13);
	glPopMatrix(); 


    // Color: black
    glColor3f(0.1,0.1,0.1);

    // Hat
    glPushMatrix();
		glTranslatef(0.0f,1.93f,0.0f);
        glRotatef(90,1,0,0);
        gluCylinder(pObj,0.18f,0.18f,0.38f,26,13);
	glPopMatrix(); 

    glPushMatrix();
		glTranslatef(0.0f,1.93f,0.0f);
        glRotatef(-90,1,0,0);
        gluDisk(pObj,0.0f,0.18f,26,13);
	glPopMatrix(); 

    glPushMatrix();
		glTranslatef(0.0f,1.67f,0.0f);
        glRotatef(90,1,0,0);
        gluDisk(pObj,0.0f,0.3f,26,13);
	glPopMatrix(); 

    glPushMatrix();
		glTranslatef(0.0f,1.67f,0.0f);
        glRotatef(-90,1,0,0);
        gluDisk(pObj,0.0f,0.3f,26,13);
	glPopMatrix(); 


    // Color: red
    glColor3f(1.0,0.0,0.0);
    glPushMatrix();
		glTranslatef(0.0f,1.72f,0.0f);
        glRotatef(90,1,0,0);
        gluCylinder(pObj,0.19,0.19f,0.05f,26,13);
	glPopMatrix();

    // Scarf
    glPushMatrix();
		glTranslatef(0.0f,1.36f,0.0f);
        glRotatef(90,1,0,0);
        gluCylinder(pObj,0.22f,0.22f,0.1f,26,13);
	glPopMatrix();

    glPushMatrix();
		glTranslatef(0.12f, 1.34f, 0.18f);
        glRotatef(50,1,0,0);
        glRotatef(40,0,1,0);
        gluCylinder(pObj,0.01f,0.03f,0.3f,26,13);
	glPopMatrix();

   glColor3f(0.9f, 1.0f, 1.0f);        
int i;
for(i=0;i<NUM_PARTICLES;i++) {
      int angle = (rand()%10) + angl;
      particles[i].veloc_x = cos((M_PI*angle/180.0))*particles[i].velocity;
      particles[i].veloc_y = sin((M_PI*angle/180.0))*particles[i].velocity;
      particles[i].veloc_y -= particles[i].gravity; //quero que caiam com grav dif
      particles[i].x += particles[i].veloc_x;
      particles[i].y += particles[i].veloc_y;

      // desenhando cada floquinho
      glPushMatrix();
        glTranslatef(particles[i].x, particles[i].y, particles[i].z);
        glutSolidSphere(particles[i].size, 13, 13);
      glPopMatrix();

      //caso chegou em baixo da tela, começar de novo
      if(particles[i].y<-2)InitFloco(i);     
  }



    // Restore the matrix state  
    glPopMatrix();  
  
    // Buffer swap  
    glutSwapBuffers();  

}    



int main(int argc, char *argv[]){
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(1000, 900);  
    glutCreateWindow("Boneco de Neve: Julia Retore");  
    glutReshapeFunc(ChangeSize);  
    glutSpecialFunc(SpecialKeys);
        InitNeve(0);

    glutDisplayFunc(RenderScene);  
    glutIdleFunc(&RenderScene);
    
    SetupRC();  
    glutMainLoop();  
      
    return 0; 
}
