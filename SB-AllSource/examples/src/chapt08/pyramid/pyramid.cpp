// Pyramid.cpp
// Demonstrates Simple Texture Mapping
// OpenGL SuperBible
// Richard S. Wright Jr.
#include "../../shared/gltools.h"   // GLTools
#include "../../shared/math3d.h"    // 3D Math Library
#include <stdlib.h>

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat extraradius = 0.0f;

// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
    {
    GLfloat fAspect;

    // Prevent a divide by zero
    if(h == 0)
        h = 1;

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
    ImGui_ImplGLUT_ReshapeFunc(w, h);
    }


// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
    {
    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;
    
    // Light values and coordinates
    GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat	 lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };

    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    
    // Load texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    pBytes = gltLoadTGA("stone.tga", &iWidth, &iHeight, &iComponents, &eFormat);
    glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(pBytes);
    
    }

// Respond to arrow keys
void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		xRot-= 5.0f;

	if(key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
                
        xRot = (GLfloat)((const int)xRot % 360);
        yRot = (GLfloat)((const int)yRot % 360);


    ImGui_ImplGLUT_SpecialFunc(key, x, y);
	// Refresh the Window
	glutPostRedisplay();
	}


void TimerFunction(int value)
{
    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}

// Called to draw scene
void RenderScene(void)
    {

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    {
        ImGui::Begin("Set Ambient Light");
        // Light values
        // Bright white light
        // General BeginCombo() API, you have full control over your selection data and display type.
        // (your selection data could be an index, a pointer to the object, an id for the object, a flag stored in the object itself, etc.)
        const char* items[] = { "Modulate", "Replace"};
        static const char* item_current = items[0];            // Here our selection is a single pointer stored outside the object.
        if (ImGui::BeginCombo("Texture Env Mode", item_current, 0)) // The second parameter is the label previewed before opening the combo.
        {

            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                bool is_selected = (item_current == items[n]);
                if (ImGui::Selectable(items[n], is_selected))
                    item_current = items[n];
                if (is_selected)
                    ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
            }
            if (item_current == items[0]) {
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
            }
            if (item_current == items[1]) {
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

            }

            ImGui::EndCombo();
        }

        {
            const char* items[] = { "Linear", "Nearest" };
            static const char* item_current = items[0];            // Here our selection is a single pointer stored outside the object.
            if (ImGui::BeginCombo("Min Filter", item_current, 0)) // The second parameter is the label previewed before opening the combo.
            {

                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    bool is_selected = (item_current == items[n]);
                    if (ImGui::Selectable(items[n], is_selected))
                        item_current = items[n];
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
                }
                if (item_current == items[0]) {
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                }
                if (item_current == items[1]) {
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                }

                ImGui::EndCombo();
            }
        }

        {
            const char* items[] = { "Linear", "Nearest" };
            static const char* item_current = items[0];            // Here our selection is a single pointer stored outside the object.
            if (ImGui::BeginCombo("Mag Filter", item_current, 0)) // The second parameter is the label previewed before opening the combo.
            {

                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    bool is_selected = (item_current == items[n]);
                    if (ImGui::Selectable(items[n], is_selected))
                        item_current = items[n];
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
                }
                if (item_current == items[0]) {
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                }
                if (item_current == items[1]) {
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                }

                ImGui::EndCombo();
            }
        }
        {
            ImGui::SliderFloat("Extra Camera Radius", &extraradius, -4.0f, 100.0f);
        }


        ImGui::End();
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glEnable(GL_TEXTURE_2D);

    M3DVector3f vNormal;
    M3DVector3f vCorners[5] = { { 0.0f, .80f, 0.0f },     // Top           0
                              { -0.5f, 0.0f, -.50f },    // Back left     1
                              { 0.5f, 0.0f, -0.50f },    // Back right    2
                              { 0.5f, 0.0f, 0.5f },      // Front right   3
                              { -0.5f, 0.0f, 0.5f }};    // Front left    4
                              
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Save the matrix state and do the rotations
    glPushMatrix();
        // Move object back and do in place rotation
        glTranslatef(0.0f, -0.25f, -4.0f - extraradius);
        glRotatef(xRot, 1.0f, 0.0f, 0.0f);
        glRotatef(yRot, 0.0f, 1.0f, 0.0f);

        // Draw the Pyramid
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_TRIANGLES);
            // Bottom section - two triangles
            glNormal3f(0.0f, -1.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3fv(vCorners[2]);
            
            glTexCoord2f(0.0f, 0.0f);
            glVertex3fv(vCorners[4]);
            
            glTexCoord2f(0.0f, 1.0f);
            glVertex3fv(vCorners[1]);
            
            
            glTexCoord2f(1.0f, 1.0f);
            glVertex3fv(vCorners[2]);
            
            glTexCoord2f(1.0f, 0.0f);
            glVertex3fv(vCorners[3]);
            
            glTexCoord2f(0.0f, 0.0f);
            glVertex3fv(vCorners[4]);
            
            // Front Face
            m3dFindNormal(vNormal, vCorners[0], vCorners[4], vCorners[3]);
            glNormal3fv(vNormal);
            glTexCoord2f(0.5f, 1.0f);
            glVertex3fv(vCorners[0]);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3fv(vCorners[4]);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3fv(vCorners[3]);
            
            // Left Face
            m3dFindNormal(vNormal, vCorners[0], vCorners[1], vCorners[4]);
            glNormal3fv(vNormal);
            glTexCoord2f(0.5f, 1.0f);
            glVertex3fv(vCorners[0]);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3fv(vCorners[1]);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3fv(vCorners[4]);

            // Back Face
            m3dFindNormal(vNormal, vCorners[0], vCorners[2], vCorners[1]);
            glNormal3fv(vNormal);
            glTexCoord2f(0.5f, 1.0f);
            glVertex3fv(vCorners[0]);
            
            glTexCoord2f(0.0f, 0.0f);
            glVertex3fv(vCorners[2]);
            
            glTexCoord2f(1.0f, 0.0f);
            glVertex3fv(vCorners[1]);
            
            // Right Face
            m3dFindNormal(vNormal, vCorners[0], vCorners[3], vCorners[2]);
            glNormal3fv(vNormal);
            glTexCoord2f(0.5f, 1.0f);
            glVertex3fv(vCorners[0]);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3fv(vCorners[3]);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3fv(vCorners[2]);
        glEnd();
    

    // Restore the matrix state
    glPopMatrix();

    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());


    // Buffer swap
    glutSwapBuffers();
    }



int main(int argc, char *argv[])
    {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Textured Pyramid");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(33, TimerFunction, 1);
    SetupRC();


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGLUT_Init();

    // inlining of ImGui_ImplGLUT_InstallFuncs();
    glutMotionFunc(ImGui_ImplGLUT_MotionFunc);
    glutPassiveMotionFunc(ImGui_ImplGLUT_MotionFunc);
#ifdef __FREEGLUT_EXT_H__
    glutMouseWheelFunc(ImGui_ImplGLUT_MouseWheelFunc);
#endif
    glutMouseFunc(ImGui_ImplGLUT_MouseFunc);
    glutKeyboardFunc(ImGui_ImplGLUT_KeyboardFunc);
    glutKeyboardUpFunc(ImGui_ImplGLUT_KeyboardUpFunc);
    glutSpecialUpFunc(ImGui_ImplGLUT_SpecialUpFunc);

    ImGui_ImplOpenGL2_Init();


    glutMainLoop();
    
    return 0;
    }
    
    
  
