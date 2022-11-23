#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
  
static GLfloat yRot = 0.0f;
static GLfloat xRot = 0.0f;
GLUquadricObj *pObj;

int angle = 360;
int flagPernaCaminhada=0;
int flagCaminhada=0;
int flagAcenar=0;
int flagJoelhoD=0;
int flagQuadrilD=0;
int flagJoelhoE=0;
int flagQuadrilE=0;
int flagZerarAceno=0;
int flagChutarE=0;
int flagChutarD=0;
int acenarMao =0;
int rotacaoOmbroE = 0;
int rotacaoCotoveloE = 0;
int rotacaoJoelhoD = 0;
int rotacaoQuadrilD = 0;
int rotacaoJoelhoE = 0;
int rotacaoQuadrilE = 0;

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


void giraOmbroE(){
    glRotatef((GLfloat)-rotacaoOmbroE, 0,0,1); 
}
void giraCotoveloE(){
    glRotatef((GLfloat)-rotacaoCotoveloE, 0,0,1); 
}
void giraJoelhoD(){
    glRotatef((GLfloat)-rotacaoJoelhoD, 1,0,0); 
}
void giraQuadrilD(){
    glRotatef((GLfloat)-rotacaoQuadrilD, 1,0,0); 
}
void giraJoelhoE(){
    glRotatef((GLfloat)-rotacaoJoelhoE, 1,0,0); 
}
void giraQuadrilE(){
    glRotatef((GLfloat)-rotacaoQuadrilE, 1,0,0); 
}


void DesenhaCorpo(){
    //CABECA
    glColor3ub(200,200,200);
    glTranslatef(0,1.2,0.0);
    glPushMatrix(); 
        glutSolidSphere(0.15,26,13);   
	glPopMatrix();

    //BUSTO
    glColor3ub(128,128,128);
    glTranslatef(0,-0.4,0.0);
    glPushMatrix();
        glScalef(1.8,1.0,1.2);
        glutSolidSphere(0.3,26,13);  
        glScalef(1.8,1.0,1.2);
	glPopMatrix();

    glTranslatef(0,-0.3,0.0);
    glPushMatrix();
        glScalef(1.8,1.0,1.2);
        glutSolidSphere(0.3*0.8,26,13);  
	glPopMatrix();

    //PELVIS
    glColor3ub(200,200,200);
    glTranslatef(0,-0.2,0.0);
    glPushMatrix(); 
        glRotatef(90,0,0,1);
        glScalef(0.4,1.1,0.5);
        glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix(); 
        glScalef(0.3,0.9,0.5);
        glutSolidCube(0.5);
    glPopMatrix();
}
void DesenhaBracoEsquerdo(void){
    glPushMatrix();  
        //OMBRO
        glTranslatef(-0.58,0.65,0.0);
        giraOmbroE(); 
        glPushMatrix(); 
            glColor3ub(128,128,128);
            glutSolidSphere(0.14,26,13);   
        glPopMatrix();

        //BRAÇO
        glTranslatef(0,-0.25,0.0);
        glPushMatrix(); 
            glColor3ub(255,255,255);
            glScalef(0.5,1.9,0.5);
            glutSolidCube(0.3); 
        glPopMatrix();

        //COTOVELO 
        glTranslatef(0,-0.33,0.0);  
        giraCotoveloE(); 
        glPushMatrix(); 
            glColor3ub(128,128,128);
            glutSolidSphere(0.12,26,13); 
        glPopMatrix();
        
        
         //ANTEBRAÇO
        glTranslatef(0,-0.34,0.0);
        glPushMatrix(); 
            glColor3ub(255,255,255);
            glScalef(0.5,1.2,0.5);
            glutSolidCube(0.4); 
        glPopMatrix();

        //MAO
        glTranslatef(0,-0.19,0.0);
        glPushMatrix(); 
            glColor3ub(128,128,128);
            glRotatef(90,1,0,0);
		    gluCylinder(pObj,0.05,0.05,0.1,26,13);
        glPopMatrix();

    glPopMatrix();
}
void DesenhaBracoDireito(void){
        glPushMatrix();//0, 0.3, 0   
        //OMBRO
        glTranslatef(0.58,0.65,0.0);
        glPushMatrix(); 
            glColor3ub(128,128,128);
            glutSolidSphere(0.14,26,13);   
        glPopMatrix();

        //BRAÇO
        glTranslatef(0,-0.25,0.0);
        glPushMatrix(); 
            glColor3ub(255,255,255);
            glScalef(0.5,1.9,0.5);
            glutSolidCube(0.3); 
        glPopMatrix();

        //COTOVELO 
        glTranslatef(0,-0.33,0.0); 
        glPushMatrix(); 
            glColor3ub(128,128,128);
            glutSolidSphere(0.12,26,13); 
           
        glPopMatrix();
        
         //ANTEBRAÇO
        glTranslatef(0,-0.34,0.0);
        glPushMatrix(); 
            glColor3ub(255,255,255);
            glScalef(0.5,1.2,0.5);
            glutSolidCube(0.4); 
        glPopMatrix();

        //MAO
        glTranslatef(0,-0.19,0.0);
        glPushMatrix(); 
            glColor3ub(128,128,128);
            glRotatef(90,1,0,0);
		    gluCylinder(pObj,0.05,0.05,0.1,26,13);
        glPopMatrix();

    glPopMatrix();

}
void DesenhaPernaDireita(){
    glPushMatrix(); //0, 0.3, 0   
        //QUADRIL
        glTranslatef(0.19,-0.15,0.0); 
        giraQuadrilD();
        glPushMatrix(); 
            glColor3ub(128,128,128);
            glutSolidSphere(0.11,26,13);   
        glPopMatrix();

        //COXA
        glTranslatef(0,-0.29,0.0);
        glPushMatrix(); 
            glColor3ub(255,255,255);
            glScalef(0.5,1.6,0.5);
            glutSolidCube(0.3); 
	    glPopMatrix();

        //JOELHO
        glTranslatef(0,-0.28,0.0);
        giraJoelhoD();
        glPushMatrix(); 
            glColor3ub(128,128,128);
            glutSolidSphere(0.11,26,13);   
        glPopMatrix();

        //CANELA
        glTranslatef(0,-0.36,0.0);
        glPushMatrix(); 
            glColor3ub(255,255,255);
            glScalef(0.5,1.4,0.5);
            glutSolidCube(0.4); 
	    glPopMatrix();

        //PÉ
         glTranslatef(0,-0.3,0.0);
        glPushMatrix(); 
            glRotatef(90,0,0,1);
            glScalef(0.3,0.9,1.5);
            glutSolidCube(0.2);
        glPopMatrix();
    glPopMatrix();
}
void DesenhaPernaEsquerda(){
    glPushMatrix();   
        glPushMatrix(); //0, 0.3, 0   
        //QUADRIL
        glTranslatef(-0.19,-0.15,0.0); 
        giraQuadrilE();
        glPushMatrix(); 
            glColor3ub(128,128,128);
            glutSolidSphere(0.11,26,13);   
        glPopMatrix();

        //COXA
        glTranslatef(0,-0.29,0.0); 
        glPushMatrix(); 
            glColor3ub(255,255,255);
            glScalef(0.5,1.6,0.5);
            glutSolidCube(0.3); 
	    glPopMatrix();

        //JOELHO
        glTranslatef(0,-0.28,0.0);
        giraJoelhoE();
        glPushMatrix(); 
            glColor3ub(128,128,128);
            glutSolidSphere(0.11,26,13);   
        glPopMatrix();

        //CANELA
        glTranslatef(0,-0.36,0.0);  
        glPushMatrix(); 
            glColor3ub(255,255,255);
            glScalef(0.5,1.4,0.5);
            glutSolidCube(0.4); 
	    glPopMatrix();

        //PÉ
         glTranslatef(0,-0.3,0.0);
        glPushMatrix(); 
            glRotatef(90,0,0,1);
            glScalef(0.3,0.9,1.5);
            glutSolidCube(0.2);
        glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}


void acenar(){
    if(rotacaoOmbroE<=80){
        rotacaoOmbroE = (rotacaoOmbroE + 1) % angle;
    }else{
        if(!acenarMao){
            rotacaoCotoveloE = (rotacaoCotoveloE + 1) % angle;
            if(rotacaoCotoveloE>60) acenarMao=1;
        }else{
            rotacaoCotoveloE = (rotacaoCotoveloE - 1) % angle;
            if(rotacaoCotoveloE==0) acenarMao=0;
        }
    }
    usleep(10000);
    glutPostRedisplay();
}
void zerarAceno(){
    if(rotacaoCotoveloE!=0) rotacaoCotoveloE = (rotacaoCotoveloE - 1) % angle;
    else if(rotacaoOmbroE!=0)rotacaoOmbroE = (rotacaoOmbroE - 1) % angle;
    else flagZerarAceno=0;
    usleep(10000);
    glutPostRedisplay();
}
void chutarD(){
    if(!flagJoelhoD){
        if(rotacaoJoelhoD>-65) rotacaoJoelhoD = (rotacaoJoelhoD - 2) % angle;
        else if(rotacaoJoelhoD==-66) flagJoelhoD=1;
    }else{
        if(rotacaoJoelhoD!=0) rotacaoJoelhoD = (rotacaoJoelhoD + 2) % angle;
        else{
            if(!flagQuadrilD){
                if(rotacaoQuadrilD<56) rotacaoQuadrilD = (rotacaoQuadrilD + 2) % angle;
                else if(rotacaoQuadrilD==56) flagQuadrilD=1;
            }else{
                if(rotacaoQuadrilD!=0) rotacaoQuadrilD = (rotacaoQuadrilD - 1) % angle;
                else{flagJoelhoD=0;flagQuadrilD=0;flagChutarD=0;flagCaminhada=!flagCaminhada;}
            }
        }
    }
    glutPostRedisplay();
}
void chutarE(){
    if(!flagJoelhoE){
        if(rotacaoJoelhoE==-66) flagJoelhoE=1;
        else rotacaoJoelhoE = (rotacaoJoelhoE - 2) % angle;
    }else{
        if(rotacaoJoelhoE!=0) rotacaoJoelhoE = (rotacaoJoelhoE + 2) % angle;
        else{
            if(!flagQuadrilE){
                if(rotacaoQuadrilE<56) rotacaoQuadrilE = (rotacaoQuadrilE + 2) % angle;
                else if(rotacaoQuadrilE==56) flagQuadrilE=1;
            }else{
                if(rotacaoQuadrilE!=0) rotacaoQuadrilE = (rotacaoQuadrilE - 1) % angle;
                else{flagJoelhoE=0;flagQuadrilE=0;flagChutarE=0;flagCaminhada=!flagCaminhada;}
            }
        }
    }
    // usleep(1000);
    glutPostRedisplay();
}


// Called to draw scene  
void RenderScene(void){  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
    // Save the matrix state and do the rotations  
    glPushMatrix();
        glTranslatef(0.0f, 0.0f, -5.0f);  
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);  

        glPushMatrix();
        pObj = gluNewQuadric();  
        gluQuadricNormals(pObj, GLU_SMOOTH);      

        DesenhaCorpo();
        DesenhaPernaDireita();
        DesenhaPernaEsquerda();
        DesenhaBracoDireito();
        DesenhaBracoEsquerdo();
    
        if(flagAcenar) acenar();
        if(flagZerarAceno) zerarAceno();
        if(flagChutarD) chutarD();
        if(flagChutarE) chutarE();


        glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();  

}    


// Respond to arrow keys (rotate snowman)
void SpecialKeys(int key, int x, int y){  
    if(key==GLUT_KEY_LEFT) yRot-=5.0f;  
    if(key==GLUT_KEY_RIGHT) yRot+=5.0f;
    if(key==GLUT_KEY_UP) xRot-=5.0f; 
    if(key==GLUT_KEY_DOWN) xRot+=5.0f;  
    if(key==GLUT_KEY_F1) flagAcenar=!flagAcenar;
    if(key==GLUT_KEY_F2){
        flagZerarAceno=1;
        acenarMao=0;
        flagAcenar=0;
    }
    if(key==GLUT_KEY_F3) flagChutarD=1;
    if(key==GLUT_KEY_F4) flagChutarE=1;
    
    xRot = (GLfloat)((const int)xRot % 360);  
    yRot = (GLfloat)((const int)yRot % 360);  
  
    // Refresh the Window  
    glutPostRedisplay();  
}


int main(int argc, char *argv[]){
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(1800, 1200);  
    glutCreateWindow("Robot: Julia Retore"); 
    glutReshapeFunc(ChangeSize); 
    glutDisplayFunc(RenderScene);   
    glutSpecialFunc(SpecialKeys);      
    SetupRC();  
    glutMainLoop();   
      
    return 0; 
}
