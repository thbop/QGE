#include "qge.h"


int main() {
    CreateWindow( "Hello World OpenGL", 640, 480 );

    /* Loop until the user closes the window */
    while ( !WindowShouldClose() )
    {
        /* Render here */
        glClear( GL_COLOR_BUFFER_BIT );

        glBegin( GL_TRIANGLES );
            glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
            glVertex2f( -1.0f, -1.0f );

            glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
            glVertex2f( 0.0f, 1.0f );

            glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
            glVertex2f( 1.0f, -1.0f );
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers( ctx.window );

        /* Poll for and process events */
        glfwPollEvents();
    }

    CloseWindow();
    return 0;
}