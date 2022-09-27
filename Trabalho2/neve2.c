// gcc neve2.c -lglut -lGL -lGLU -lm -o fireworks_glut
#include <GL/glut.h>  // Header File For The GLUT Library 
#include <GL/gl.h>	  // Header File For The OpenGL32 Library
#include <GL/glu.h>	  // Header File For The GLu32 Library
#include <math.h>
#include <unistd.h>

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
    particles[i].z = (rand()%5);  //varia de  0 à 5
    particles[i].gravity = (float)((rand() %10) +2) /100000.0; //varia entre 0.00002 e 0.00007
    particles[i].size = (float)((rand() % 5)+5)/1000.0; //varia entre 0.005 e 0.0010
}

// Inicializa todos os flocos de neve
void InitNeve(int pause){
  int i;
  for(i=0;i<NUM_PARTICLES;i++) InitFloco(i);
}


/* The main drawing function. */
void DrawGLScene(){
  int i, ative_particles=0;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
  glLoadIdentity();				// Reset The View
  glTranslatef(0.0f,0.0f,-4.0f);		// Move particles 6.0 units into the screen
	
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
  glEnd();

  // swap buffers to display, since we're double buffered.
  glutSwapBuffers();
  // usleep(20000);

  // if(!ative_particles) InitNeve(1); // reset particles
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) {
  if (key == ESCAPE){ 
	glutDestroyWindow(window); 
	exit(0);                   
  }

}

void SpecialKeys(int key, int x, int y){  
  if(key==GLUT_KEY_LEFT) if(angl>235) angl-=5;
  if(key==GLUT_KEY_RIGHT) if(angl<295) angl+=5;  
  
    // Refresh the Window  
    glutPostRedisplay();  
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix
  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window
  glMatrixMode(GL_MODELVIEW);

  InitNeve(0); // first firework
}

int main(int argc, char **argv) {  
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  glutInitWindowSize(640, 480);  
  glutInitWindowPosition(0, 0);  
  window = glutCreateWindow("Nevezinha");  
  glutSpecialFunc(SpecialKeys);  

  glutDisplayFunc(&DrawGLScene);  
  glutFullScreen();
  glutIdleFunc(&DrawGLScene);
  // glutReshapeFunc(&ReSizeGLScene);
  glutKeyboardFunc(&keyPressed);
  InitGL(640, 480);
  glutMainLoop();  

  return 0;
}
