#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <stdlib.h>

using namespace Eigen;
using namespace std;

Vector3f P0, Pref, Vprime, n, u, v, blf, tlf, trf, brf, blr, tlr, trr, brr;
Vector4f first_point, second_point, third_point;
float near, far, width, height, w_width, w_height;

//reading in camera specs
void readCameraSpecs(){
    cin >> P0[0] >> P0[1] >> P0[2]
        >> Pref[0] >> Pref[1] >> Pref[2]
        >> Vprime[0] >> Vprime[1] >> Vprime[2]
        >> near >> far >> width >> height;
}

//print for 3 element vector
void print(Vector3f vec){
    cout << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")" << endl;
}

//print for 4 element vector
void print(Vector4f vec){
    cout << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ", " << vec[3] << ")" << endl;
}

//calculate frustum points
void calculateFrustum(){
    
    Vector3f NP_origin (0,0,0 -near);
    Vector3f FP_origin(0,0,0-far);
    float vpWidth = width/2;
    float vpHeight = height/2;
    
    blf << NP_origin[0] - vpWidth, NP_origin[1] - vpHeight, NP_origin[2];
    tlf << NP_origin[0] - vpWidth, NP_origin[1] + vpHeight, NP_origin[2];
    trf << NP_origin[0] + vpWidth, NP_origin[1] + vpHeight, NP_origin[2];
    brf << NP_origin[0] + vpWidth, NP_origin[1] - vpHeight, NP_origin[2];
   
    float angle_height = atan(vpHeight/near);
    float angle_Width = atan(vpWidth/near);
    float farHeight = tan(angle_height) * far;
    float farWidth = tan(angle_Width) * far;
    
    blr << FP_origin[0] - farWidth, FP_origin[1] - farHeight, FP_origin[2];
    tlr << FP_origin[0] - farWidth, FP_origin[1] + farHeight, FP_origin[2];
    trr << FP_origin[0] + farWidth, FP_origin[1] + farHeight, FP_origin[2];
    brr << FP_origin[0] + farWidth, FP_origin[1] - farHeight, FP_origin[2];
    
}

//calculate world coords to view coords matrix
Matrix4f getM_w_v(){
    Matrix4f T;
    T << 1, 0, 0, -P0[0],
         0, 1, 0, -P0[1],
         0, 0, 1, -P0[2],
         0, 0, 0, 1;
    Matrix4f R;
    R << u[0], u[1], u[2], 0,
         v[0], v[1], v[2], 0,
         n[0], n[1], n[2], 0,
         0, 0, 0, 1;
    Matrix4f M_w_v = R*T;
    return M_w_v;
}

//calculate homogenising matrix
Matrix4f getM_p(){
    Matrix4f M_p;
    M_p << near, 0, 0, 0,
           0, near, 0, 0,
           0, 0, 1, 0,
           0, 0, -1, 0;
    return M_p;
}

//calculate normalization matrix
Matrix4f getM_c_ns(){
   
    float xwMin = 0 - (width/2);
    float xwMax = 0 + (width/2);
    float ywMin = 0 - (height/2);
    float ywMax = 0 + (height/2);
    float zNear = -near;
    float zFar  = -far;
    
    Matrix4f M_c_ns;
    M_c_ns << (2/(xwMax-xwMin)), 0, 0, (-((xwMax+xwMin)/(xwMax-xwMin))),
            0, (2/(ywMax-ywMin)), 0, (-((ywMax+ywMin)/(ywMax-ywMin))),
            0, 0, (-2/(zNear - zFar)), ((zNear+zFar)/(zNear-zFar)),
            0, 0, 0, 1;
    return M_c_ns;
}

void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glShadeModel(GL_FLAT);
}

void displayFcn(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);
  glLoadIdentity();
  glLineWidth(1.0);
    
    glBegin(GL_LINE_LOOP);
        glColor3f(0.0, 1.0, 0.0);
        glVertex4f(first_point[0], first_point[1], first_point[2], first_point[3]);
        glVertex4f(second_point[0], second_point[1], second_point[2], second_point[3]);
        glVertex4f(third_point[0], third_point[1], third_point[2], third_point[3]);
    glEnd();
  
    glFlush();
    glutSwapBuffers();
}

void reshapeFcn(GLint newWidth, GLint newHeight){
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode (GL_MODELVIEW);
}

int main(int argc, char** argv){

    //read in the camera specs
    readCameraSpecs();
    
    //get query number
    int query;
    cin >> query;
    
    //compute n -> Zv, u, v -> Yv
    n = (P0-Pref).normalized();
    u = Vprime.cross(n).normalized();
    v = n.cross(u);
    
    //query 1
    if(query == 1){
        print(n);
        exit(0);
    }
    
    //query 2
    if(query == 2){
        print(v);
        exit(0);
    }
    
    
    //query 3
    if(query == 3){
        calculateFrustum();
        print(blf);
        print(tlf);
        print(trf);
        print(brf);
        print(blr);
        print(tlr);
        print(trr);
        print(brr);
        exit(0);
    }
    
    //query 4 and 5
    if(query == 4 || query == 5){
        Vector4f point;
        cin >> point[0] >> point[1] >> point[2];
        point[3] = 1;
        point = getM_w_v() * point;
        print(point);
    }
    
    //query 6
    if(query == 6){
        Vector4f point;
        cin >> point[0] >> point[1] >> point[2];
        point[3] = 1;
        
        //composite matrix
        Matrix4f M = getM_c_ns() * getM_p() * getM_w_v();
        point = M*point;
        print(point);
        
    }
    
    //query 7
    if(query == 7){
        
        cin >> first_point[0] >> first_point[1] >> first_point[2]
        >> second_point[0] >> second_point[1] >> second_point[2]
        >> third_point[0] >> third_point[1] >> third_point[2]
        >> w_width >> w_height;
        
        //convert WC of triangle to NDC
        Matrix4f M = getM_c_ns() * getM_p() * getM_w_v();
        first_point[3] = 1;
        second_point[3] = 1;
        third_point[3] = 1;
        first_point = M*first_point;
        second_point = M*second_point;
        third_point = M*third_point;
        
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(50,100);
        glutInitWindowSize(w_width, w_height);
        glutCreateWindow("camsys");
        
        init();
        glutDisplayFunc(displayFcn);
        glutReshapeFunc(reshapeFcn);
        glutMainLoop();
        
    }
    
    
}
