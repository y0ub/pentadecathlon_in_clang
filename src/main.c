#include <stdio.h>
#include <stdlib.h>

const int kedge_len = 32;

// cell[y][x] == 0 => dead
// cell[y][x] == 1 => arrive
typedef struct Field
{
  char cell[kedge_len][kedge_len];
} Field;

void print_map(Field *map)
{
  system("clear");
  for (int y = 0; y < kedge_len; ++y) {
    for (int x = 0; x < kedge_len; ++x) {
      putchar(map -> cell[y][x] ? '_' : '#');
      putchar(' ');
    }
    putchar('\n');
  }
}

Field current;
Field next;

void init()
{
  for (int i = 0; i < 10; ++i)
    current.cell[16][i + 10] = 1;
}

int get_num_around_arrive(int x, int y)
{
  int count = 0;
  for (int i = -1; i < 2; ++i) {
    for (int j = -1; j < 2; ++j) {
      if (i == 0 && j == 0)
        continue;
      count += current.cell[(y + i) & 0x1F][x + j];
    }
  }
  return count;
}

int main(int argc, char *argv[])
{
  init();
  for (;;) {
    for (int i = 0; i < 100000000; ++i);
    print_map(&current);
    for (int y = 0; y < kedge_len; ++y) {
      for (int x = 0; x < kedge_len; ++x) {
        int count = get_num_around_arrive(x, y);
        // count == 2 || 3 => arrive
        // count == 3 && dead => arrive
        // else => dead
        if (count == 2)
          next.cell[y][x] = current.cell[y][x] & current.cell[y][x];
        else
          next.cell[y][x] = 0;
        if (count == 3)
          next.cell[y][x] = 1; 
      }
    }
    current = next;
  }

  return 0;
}
