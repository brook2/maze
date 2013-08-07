// License: GPLv3

#include "maze.h"

int cell_array(int w,int h,int x,int y,int z) {
  return x + w*(y + h*z);
}

neighbour directions[6] = {
  {cube_front,0,0,-1},
  {cube_back,0,0,1},
  {cube_left,-1,0,0},
  {cube_right,1,0,0},
  {cube_top,0,1,0},
  {cube_bottom,0,-1,0},
};

cube_side direction_opposite(cube_side side) {
  switch(side) {
  case cube_front: return cube_back;
  case cube_back: return cube_front;
  case cube_left: return cube_right;
  case cube_right: return cube_left;
  case cube_top: return cube_bottom;
  case cube_bottom: return cube_top;
  }
}

void init_maze(maze *m) {
  int w,h,d;
  
  int x,y,z;
  
  cell empty_cell = {0, {1,1,1,1,1,1}};
  
  w = m->w; h = m->h; d = m->d;
  
  for(x=0;x<w;x++) {
    for(y=0;y<h;y++) {
      for(z=0;z<d;z++) {
	m->cells[cell_array(w,h,x,y,z)] = empty_cell;
      }
    }
  }
}

void generate_maze(maze *m, int x, int y, int z) {
  int w,h,d;
  
  int i, j;
  int dir;
  
  neighbour swap;
  neighbour adj[6];
  int neighbours = 0;
  
  cell *c;
  
  w = m->w; h = m->h; d = m->d;
  
  m->cells[cell_array(w,h,x,y,z)].visited = 1;
  
  for(i = 0; i < 6; i++) {
    adj[neighbours] = directions[i];
    adj[neighbours].x+=x;
    adj[neighbours].y+=y;
    adj[neighbours].z+=z;
    if(0 <= adj[neighbours].x &&
       adj[neighbours].x < m->w &&
       0 <= adj[neighbours].y &&
       adj[neighbours].y < m->h &&
       0 <= adj[neighbours].z &&
       adj[neighbours].z < m->d) {
      neighbours++;
    }
  }
  
  // knuth shuffle
  for(i = 0; i < neighbours; i++) {
    j = random()%(neighbours-i);
    if(i==j) continue;
    
    swap = adj[i];
    adj[i] = adj[j];
    adj[j] = swap;
  }
  
  while(neighbours--) {
    dir = adj[neighbours].dir;
    c = &m->cells[cell_array(w,h,adj[neighbours].x,adj[neighbours].y,adj[neighbours].z)];
    if(!c->visited) {
      c->visited = 1;
      
      m->cells[cell_array(w,h,x,y,z)].wall[dir] = 0;
      c->wall[direction_opposite(dir)] = 0;
      
      generate_maze(m, x+directions[dir].x, y+directions[dir].y, z+directions[dir].z);
    }
  }
}
