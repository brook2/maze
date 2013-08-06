typedef enum {
  cube_front = 0,
  cube_back = 1,
  cube_left = 2,
  cube_right = 3,
  cube_top = 4,
  cube_bottom = 5
} cube_side;

typedef struct {
  int visited;
  int wall[6];
} cell;

typedef struct {
  int w,h,d;
  cell *cells;
} maze;

typedef struct {
  cube_side dir;
  int x, y, z;
} neighbour;

neighbour directions[6];

int cell_array(int w,int h,int x,int y,int z);

void init_maze(maze *m);

cube_side direction_opposite(cube_side side);
void generate_maze(maze *m, int x, int y, int z);
