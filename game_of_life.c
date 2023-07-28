#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

const int N = 27;
const int M = 82;

void rend_field(const int N, const int M, char pole[][M]);
void draw_field(const int N, const int M, char pole[][M]);
void scan(const int N, const int M, char pole[][M], char copypole[][M],
          int *count);
void scan_centre(int i, int j, char pole[][M], char copypole[][M], int *count);
void copy(char pole[][M], char copypole[][M]);
void rend_field_speedmode(int speedmode);
void rend_field_speedmode_f(int speedmode);
void draw_end();

int main() {
  char pole[N][M];
  char copypole[N][M];
  int b = 1, count = 0;
  int speed = 200000, speedmode = 5;
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= M; j++)
      scanf("%c", &pole[i][j]);
  }
  FILE *f;
  f = freopen("/dev/tty", "r", stdin);
  initscr();
  noecho();
  nodelay(stdscr, TRUE);
  while (b > 0) {
    rend_field(N, M, copypole);
    rend_field_speedmode(speedmode);
    scan(N, M, pole, copypole, &count);
    copy(pole, copypole);
    draw_field(N, M, pole);
    char command = getch();
    if ((command == 'w' || command == 'W') && (speedmode < 9)) {
      speed /= 2;
      speedmode++;
    }
    if ((command == 's' || command == 'S') && (speedmode > 1)) {
      speed *= 2;
      speedmode--;
    }
    b = count;
    count = 0;
    if (command == 'q' || command == 'Q') {
      b = -1;
    }
    if (b == 0)
      usleep(2000000);
    else
      usleep(speed);
    refresh();
    clear();
  }
  endwin();
  printf("\x1B[2J\x1B[H");
  rend_field_speedmode_f(speedmode);
  draw_end();
  fclose(f);
  return 0;
}

void rend_field(const int N, const int M, char pole[][M]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if ((i == 0) || (i == N - 1))
        pole[i][j] = '_';
      else if ((j == 0) || (j == M - 1))
        pole[i][j] = '|';
      else
        pole[i][j] = ' ';
    }
  }
}

void rend_field_speedmode(int speedmode) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < M; j++) {
      if (i == 0) {
        printw("_");
      } else if ((j == 0) || (j == M - 1)) {
        printw("|");
      } else if (i == 1 && j == 14) {
        printw("SPEED UP: W            SPEED DOWN: S          EXIT: Q");
        j = j + 52;
      } else if (i == 2 && j == 14) {
        printw("CURRENT SPEED MODE: %d  (min mode = 1     max mode = 9)",
               speedmode);
        j = j + 53;
      } else {
        printw(" ");
      }
    }
    printw("\n");
  }
}

void rend_field_speedmode_f(int speedmode) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < M; j++) {
      if (i == 0 || i == 3) {
        printf("_");
      } else if ((j == 0) || (j == M - 1)) {
        printf("|");
      } else if (i == 1 && j == 14) {
        printf("SPEED UP: W            SPEED DOWN: S         quick: Q");
        j = j + 52;
      } else if (i == 2 && j == 14) {
        printf("CURRENT SPEED MODE: %d  (min mode = 1     max mode = 9)",
               speedmode);
        j = j + 53;
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void draw_end() {
  for (int i = 0; i < M; i++) {
    if (i == 0 || i == M - 1) {
      printf("|");
    } else {
      printf(" ");
    }
  }
  printf("\n");
  printf("|                   #####       ###      #    #    #######           "
         "            |\n");
  printf("|                  #     #     #   #    # #  # #   #######           "
         "            |\n");
  printf("|                 #       #   #     #   # #  # #   ##                "
         "            |\n");
  printf("|                 #           #     #   #  ##  #   ##                "
         "            |\n");
  printf("|                 #           #     #   #      #   ##                "
         "            |\n");
  printf("|                 #           #######   #      #   #######           "
         "            |\n");
  printf("|                 #     ###   #     #   #      #   ##                "
         "            |\n");
  printf("|                 #      #    #     #   #      #   ##                "
         "            |\n");
  printf("|                 ##     #    #     #   #      #   ##                "
         "            |\n");
  printf("|                  ##   ##    #     #   #      #   #######           "
         "            |\n");
  printf("|                   ####      #     #   #      #   #######           "
         "            |\n");
  for (int i = 0; i < M; i++) {
    if (i == 0 || i == M - 1) {
      printf("|");
    } else {
      printf(" ");
    }
  }
  printf("\n");
  printf("|                     ####    #     #  ######  #######               "
         "            |\n");
  printf("|                    #    #   #     #  ######  #      #              "
         "            |\n");
  printf("|                   #      #  #     #  ##      #      #              "
         "            |\n");
  printf("|                   #      #  #     #  ##      #      #              "
         "            |\n");
  printf("|                   #      #  #     #  ##      #     #               "
         "            |\n");
  printf("|                   #      #  #     #  ######  ######                "
         "            |\n");
  printf("|                   #      #  #     #  ##      #     #               "
         "            |\n");
  printf("|                   #      #  #     #  ##      #     #               "
         "            |\n");
  printf("|                   #      #  #     #  ##      #     #               "
         "            |\n");
  printf("|                    #    #    #   #   ######  #     #               "
         "            |\n");
  printf("|                     ####      ###    ######  #     #               "
         "            |\n");
  for (int i = 0; i < M; i++) {
    if (i == 0 || i == M - 1) {
      printf("|");
    } else {
      printf(" ");
    }
  }
  printf("\n");
  for (int i = 0; i < M; i++)
    printf("_");
  printf("\n");
}

void draw_field(const int N, const int M, char pole[][M]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      printw("%c", pole[i][j]);
    }
    printw("\n");
  }
}

void scan(const int N, const int M, char pole[][M], char copypole[][M],
          int *count) {
  for (int i = 1; i < N - 1; i++) {
    for (int j = 1; j < M - 1; j++) {
      scan_centre(i, j, pole, copypole, count);
    }
  }
}

void scan_centre(int i, int j, char pole[][M], char copypole[][M], int *count) {
  int k = 0;
  int xx, yy;
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      xx = j - 1 + x;
      yy = i - 1 + y;
      if (xx < 1)
        xx = M - 2;
      if (yy < 1)
        yy = N - 2;
      if (xx > M - 2)
        xx = 1;
      if (yy > N - 2)
        yy = 1;
      if (y != 1 || x != 1) {
        if (pole[yy][xx] == '#')
          k++;
      }
    }
  }
  if (pole[i][j] == ' ') {
    if (k == 3) {
      copypole[i][j] = '#';
      *count = *count + 1;
    } else {
      copypole[i][j] = ' ';
    }
  }
  if (pole[i][j] == '#') {
    if (k == 3 || k == 2) {
      copypole[i][j] = '#';
    } else {
      copypole[i][j] = ' ';
      *count = *count + 1;
    }
  }
}

void copy(char pole[][M], char copypole[][M]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      pole[i][j] = copypole[i][j];
    }
  }
}
