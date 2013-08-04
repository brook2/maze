#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL.h"

#include "quaternion.h"

// note: what happens when the main loop is running slightly slower than the delay we wanted to reach has not been tested (we want to get a slightly slower framerate than usual but still moving at the same speed)

// need to make rotation based on quaternions
// and movement based on those

float pitch, yaw, roll;
float xpos, ypos, zpos;
int forwardkey, backkey, leftkey, rightkey, upkey, downkey, banklkey, bankrkey;

quaternion q, q1, q2, q3, q4;
GLfloat m[16];

static void draw_screen( void )
{
    /* Our angle of rotation. */
    static float angle = 0.0f;

    /*
     * EXERCISE:
     * Replace this awful mess with vertex
     * arrays and a call to glDrawElements.
     *
     * EXERCISE:
     * After completing the above, change
     * it to use compiled vertex arrays.
     *
     * EXERCISE:
     * Verify my windings are correct here ;).
     */
    static GLfloat v0[] = { -1.0f, -1.0f,  1.0f };
    static GLfloat v1[] = {  1.0f, -1.0f,  1.0f };
    static GLfloat v2[] = {  1.0f,  1.0f,  1.0f };
    static GLfloat v3[] = { -1.0f,  1.0f,  1.0f };
    static GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
    static GLfloat v5[] = {  1.0f, -1.0f, -1.0f };
    static GLfloat v6[] = {  1.0f,  1.0f, -1.0f };
    static GLfloat v7[] = { -1.0f,  1.0f, -1.0f };
    static GLubyte red[]    = { 255,   0,   0, 255 };
    static GLubyte green[]  = {   0, 255,   0, 255 };
    static GLubyte blue[]   = {   0,   0, 255, 255 };
    static GLubyte white[]  = { 255, 255, 255, 255 };
    static GLubyte yellow[] = {   0, 255, 255, 255 };
    static GLubyte black[]  = {   0,   0,   0, 255 };
    static GLubyte orange[] = { 255, 255,   0, 255 };
    static GLubyte purple[] = { 255,   0, 255,   0 };

    /* Clear the color and depth buffers. */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_DEPTH_TEST );

    /* We don't want to modify the projection matrix. */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    /* Move down the z-axis. */
    /* Rotate. */
    //glRotatef( pitch, 1.0, 0.0, 0.0 );
    //glRotatef( yaw, 0.0, 1.0, 0.0 );
    q1 = quaternion_axis_angle(1, 0, 0, pitch*2*3.14159*(1/360.0));
    q2 = quaternion_axis_angle(0, 1, 0, yaw*2*3.14159*(1/360.0));
    q3 = quaternion_axis_angle(0, 0, 1, roll*2*3.14159*(1/360.0));
    q4 = quaternion_multiply(q1, quaternion_multiply(q2, q3));
    pitch = 0;
    yaw = 0;
    roll = 0;
    q = quaternion_multiply(q4, q); // swap?
    quaternion_rotation_matrix(q, m);
    glMultMatrixf(m);
    
    //glTranslatef( 0.0, 0.0, -5);
    glTranslatef( xpos, ypos, zpos);
    
    //q = quaternion_axis_angle(1, 0, 0, angle*2*3.14159*(1/360.0));
    //quaternion_rotation_matrix(q, m);
    srand(time(0));
    //glRotatef(-1*angle, 1, 0, 0);
    //glMultMatrixf(m);
    //glMultMatrixf(m);

    //    if( should_rotate ) {

        if( ++angle > 360.0f ) {
            angle = 0.0f;
        }

	//    }
    
	int x,y,z;
	srand(73);
	for(x=-10;x<=10;x++){
	for(y=-10;y<=10;y++){
	for(z=-10;z<=10;z++){

	    glPushMatrix();
	    glTranslatef(x*2,y*2,z*2);

    /* Send our triangle data to the pipeline. */
    glBegin( GL_TRIANGLES );

     if(rand()%7==3){
    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( blue );
    glVertex3fv( v2 );
	} if(rand()%7==3){

    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( blue );
    glVertex3fv( v2 );
    glColor4ubv( white );
    glVertex3fv( v3 );
	} if(rand()%7==3){

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( black );
    glVertex3fv( v5 );
    glColor4ubv( orange );
    glVertex3fv( v6 );
	} if(rand()%7==3){

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( orange );
    glVertex3fv( v6 );
    glColor4ubv( blue );
    glVertex3fv( v2 );
	} if(rand()%7==3){

    glColor4ubv( black );
    glVertex3fv( v5 );
    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( purple );
    glVertex3fv( v7 );
	} if(rand()%7==3){

    glColor4ubv( black );
    glVertex3fv( v5 );
    glColor4ubv( purple );
    glVertex3fv( v7 );
    glColor4ubv( orange );
    glVertex3fv( v6 );
	} if(rand()%7==3){

    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( white );
    glVertex3fv( v3 );
	} if(rand()%7==3){

    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( white );
    glVertex3fv( v3 );
    glColor4ubv( purple );
    glVertex3fv( v7 );
	} if(rand()%7==3){

    glColor4ubv( white );
    glVertex3fv( v3 );
    glColor4ubv( blue );
    glVertex3fv( v2 );
    glColor4ubv( orange );
    glVertex3fv( v6 );
	} if(rand()%7==3){

    glColor4ubv( white );
    glVertex3fv( v3 );
    glColor4ubv( orange );
    glVertex3fv( v6 );
    glColor4ubv( purple );
    glVertex3fv( v7 );
	} if(rand()%7==3){

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( red );
    glVertex3fv( v0 );
    glColor4ubv( yellow );
    glVertex3fv( v4 );
	} if(rand()%7==3){

    glColor4ubv( green );
    glVertex3fv( v1 );
    glColor4ubv( yellow );
    glVertex3fv( v4 );
    glColor4ubv( black );
    glVertex3fv( v5 );
     }
    glEnd( );

	    glPopMatrix();
}
}
}

    /*
     * EXERCISE:
     * Draw text telling the user that 'Spc'
     * pauses the rotation and 'Esc' quits.
     * Do it using vetors and textured quads.
     */

    /*
     * Swap the buffers. This this tells the driver to
     * render the next frame from the contents of the
     * back-buffer, and to set all rendering operations
     * to occur on what was the front-buffer.
     *
     * Double buffering prevents nasty visual tearing
     * from the application drawing on areas of the
     * screen that are being updated at the same time.
     */
    SDL_GL_SwapBuffers( );
}

void update(float dt) {
  printf("%f\n", dt);
  float movespeed = 12;
  float turnspeed = 0.5*360.0;

  float x,y,z;
  
  if(forwardkey && !backkey) {
    x = 0; y = 0; z = 1;
    quaternion_rotate_vector(q, &x, &y, &z);
    xpos += x*movespeed*dt;
    ypos += y*movespeed*dt;
    zpos += z*movespeed*dt;
  }
  if(backkey && !forwardkey) zpos -= movespeed*dt;
  if(leftkey && !rightkey) xpos -= movespeed*dt;
  if(rightkey && !leftkey) xpos += movespeed*dt;
  if(upkey && !downkey) ypos += movespeed*dt;
  if(downkey && !upkey) ypos -= movespeed*dt;
  if(banklkey && !bankrkey) roll += turnspeed*dt;
  if(bankrkey && !banklkey) roll -= turnspeed*dt;
}

void draw() {
  //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  draw_screen();
  
  //SDL_GL_SwapBuffers();
}

int main(int argc, char *argv[]) {
  SDL_Surface *screen;
  SDL_Event event;
  Uint32 last_draw_time, time_difference, target_delay;
  int ignore_mouse_events;
  
  target_delay = 16;
  time_difference = target_delay;
  
  if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }
  atexit(SDL_Quit);
  
  screen = SDL_SetVideoMode(640, 480, 16, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL);
  if(screen == NULL) {
    fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
    exit(1);
  }
  
  SDL_ShowCursor(0);
  SDL_WM_GrabInput( SDL_GRAB_ON );
  ignore_mouse_events = 1; // warping the mouse produces a huge mouse movement
  
  q = quaternion_axis_angle(0, 0, 0, 0);
  pitch = 0;
  yaw = 0;
  xpos = 0;
  ypos = 0;
  zpos = 0;
  forwardkey = 0;
  backkey = 0;
  leftkey = 0;
  rightkey = 0;
  upkey = 0;
  downkey = 0;
  
    /* Our shading model--Gouraud (smooth). */
    glShadeModel( GL_SMOOTH );

    /* Culling. */
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );

    /* Set the clear color. */
    glClearColor( 0, 0, 0, 0 );

    /* Setup our viewport. */
    glViewport( 0, 0, 640, 480 );

    /*
     * Change to the projection matrix and set
     * our viewing volume.
     */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    /*
     * EXERCISE:
     * Replace this with a call to glFrustum.
     */
    gluPerspective( 60.0, 640.0/480.0, 1.0, 1024.0 );
    
    float motion_factor = 0.05*2*3.14159;
  
  while(1) {
    // immediately after drawing
    last_draw_time = SDL_GetTicks();
    
    // There may be multiple events per tick
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_QUIT:
	exit(0);
	break;
      case SDL_MOUSEMOTION:
	if(!ignore_mouse_events) {
	  pitch += event.motion.yrel*motion_factor;
	  yaw += event.motion.xrel*motion_factor;
	}
	else
	  ignore_mouse_events--;
	break;
      case SDL_KEYDOWN:
	switch(event.key.keysym.sym) {
	case SDLK_ESCAPE:
	  exit(0);
	  break;
	case SDLK_a:
	  leftkey = 1;
	  break;
	case SDLK_d:
	  rightkey = 1;
	  break;
	case SDLK_w:
	  forwardkey = 1;
	  break;
	case SDLK_s:
	  backkey = 1;
	  break;
	case SDLK_r:
	  upkey = 1;
	  break;
	case SDLK_f:
	  downkey = 1;
	  break;
	case SDLK_q:
	  banklkey = 1;
	  break;
	case SDLK_e:
	  bankrkey = 1;
	  break;
	}
	break;
      case SDL_KEYUP:
	switch(event.key.keysym.sym) {
	case SDLK_a:
	  leftkey = 0;
	  break;
	case SDLK_d:
	  rightkey = 0;
	  break;
	case SDLK_w:
	  forwardkey = 0;
	  break;
	case SDLK_s:
	  backkey = 0;
	  break;
	case SDLK_r:
	  upkey = 0;
	  break;
	case SDLK_f:
	  downkey = 0;
	  break;
	case SDLK_q:
	  banklkey = 0;
	  break;
	case SDLK_e:
	  bankrkey = 0;
	  break;
	}
	break;
      }
    }
    
    // update
    printf("%d time_difference\n", time_difference);
    update(time_difference/1000.0);
    
    // delay
    time_difference = SDL_GetTicks() - last_draw_time;
    if(time_difference < target_delay) {
      SDL_Delay(target_delay - time_difference);
      time_difference = SDL_GetTicks() - last_draw_time;
    }
    else {
      fprintf(stderr, "%d\n", time_difference);
    }
    
    // draw
    //DrawPixel(screen, rand()%640, rand()%480, rand()%255, rand()%255, rand()%255);
    draw();
  }
  
  return EXIT_SUCCESS;
}
