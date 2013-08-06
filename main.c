#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL.h"

#include "quaternion.h"
#include "maze.h"

int tabbed_out;

maze m;

void init(void) {
  tabbed_out = 0;
  
  m.w = 4;
  m.h = 3;
  m.d = 5;
  m.cells = malloc(m.w*m.h*m.d*sizeof(cell));
  init_maze(&m);
  generate_maze(&m,0,0,0);
  
  //
  
  glClearColor(0.1, 0, 0.3, 0);
  glEnable(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_LIGHTING);
  glShadeModel(GL_FLAT);
  glEnable(GL_LIGHT0);
  
  glViewport(0, 0, 640, 480);
  
  glMatrixMode(GL_PROJECTION);
  gluPerspective(60.0, 4.0/3.0, 0.5, 1024.0);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

float t = 0;

void draw_wall(cube_side dir) {
  switch(dir) {
  case cube_front:
    glNormal3f(0,0,1);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f( 0.5,-0.5,-0.5);
    glVertex3f( 0.5, 0.5,-0.5);
    glVertex3f(-0.5, 0.5,-0.5);
    break;
  case cube_back:
    glNormal3f(0,0,-1);
    glColor3f(1,0,0);
    glVertex3f(-0.5,-0.5,0.5);
    glVertex3f(-0.5, 0.5,0.5);
    glVertex3f( 0.5, 0.5,0.5);
    glVertex3f( 0.5,-0.5,0.5);
    break;
  case cube_left:
    glNormal3f(1,0,0);
    glColor3f(1,0,0);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f(-0.5, 0.5,-0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5,-0.5, 0.5);
    break;
  case cube_right:
    glNormal3f(-1,0,0);
    glColor3f(1,0,0);
    glVertex3f(0.5,-0.5,-0.5);
    glVertex3f(0.5,-0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5,-0.5);
    break;
  case cube_bottom:
    glNormal3f(0,1,0);
    glColor3f(1,0,0);
    glVertex3f(-0.5,-0.5, 0.5);
    glVertex3f( 0.5,-0.5, 0.5);
    glVertex3f( 0.5,-0.5,-0.5);
    glVertex3f(-0.5,-0.5,-0.5);
    break;
  case cube_top:
    glNormal3f(0,-1,0);
    glColor3f(1,0,0);
    glVertex3f(-0.5,0.5, 0.5);
    glVertex3f(-0.5,0.5,-0.5);
    glVertex3f( 0.5,0.5,-0.5);
    glVertex3f( 0.5,0.5, 0.5);
    break;
  }
}

void update(float dt) {
  //printf("%f\n", dt);
  t += dt*60;
}

void draw(void) {
  int x,y,z;
  cube_side d;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();
  glTranslatef(0,0,-7);
  glRotatef(t,0,1,0);
  glRotatef(t,0,0,0.3);
  glTranslatef(-(m.w-1)/2.0,-(m.h-1)/2.0,-(m.d-1)/2.0);
  
  for(x=0; x<m.w; x++) {
    for(y=0; y<m.h; y++) {
      for(z=0; z<m.d; z++) {
	glPushMatrix();
	glTranslatef(x,y,z);
	for(d=0; d<6; d++) {
	  if(m.cells[cell_array(m.w,m.h,x,y,z)].wall[d]) {
	    glBegin(GL_QUADS);
	    draw_wall(d);
	    glEnd();
	  }
	}
	glPopMatrix();
      }
    }
  }
  
  SDL_GL_SwapBuffers();
}

void handle_event(SDL_Event event) {
  
}

int main(int argc, char *argv[]) {
  SDL_Surface *screen;
  SDL_Event event;
  Uint32 last_draw_time, time_difference, target_delay;
  int ignore_mouse_events;
  
  target_delay = 16; // aim for 1000/16 = 62 fps
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
  SDL_WM_GrabInput(SDL_GRAB_ON);
  ignore_mouse_events = 1; // warping the mouse produces a huge mouse movement
  
  init();
  draw();
  
  while(1) {
    // immediately after drawing
    last_draw_time = SDL_GetTicks();
    
    // There may be multiple events per tick
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_QUIT:
	exit(0);
	break;
      case SDL_KEYDOWN:
	switch(event.key.keysym.sym) {
	case SDLK_ESCAPE:
	  exit(0);
	  break;
	case SDLK_TAB:
	  tabbed_out = !tabbed_out;
	  if(tabbed_out) {
	    SDL_ShowCursor(1);
	    SDL_WM_GrabInput(SDL_GRAB_OFF);
	  }
	  else {
	    SDL_ShowCursor(0);
	    SDL_WM_GrabInput(SDL_GRAB_ON);
	    ignore_mouse_events = 1;
	  }
	  break;
	}
      case SDL_MOUSEMOTION:
	if(tabbed_out) break;
	if(ignore_mouse_events) {
	  ignore_mouse_events--;
	  //break;
	}
      default:
	handle_event(event);
	break;
      }
    }
    
    // update
    //printf("%d time_difference\n", time_difference);
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
    draw();
  }
  
  return EXIT_SUCCESS;
}
