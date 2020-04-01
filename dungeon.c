/*

Austin Sypolt
CS431

Game Enhancement Features: 
For a general theme of the game I would suggest possibly making it a mining
adventure game. You can find and collect things and add them to an inventory,
such as valuable gems, easter eggs, and possibly weapons to fight the wumpus.
This would require a lot more implementation of items across the map and many
more different rooms to be added. As for the inventory, the various items could
be labeled with item IDs, and if an array with those IDs is checked next to that
array position, the user would have the item in their inventory.

*/

#define _DEFAULT_SOURCE
#include <dirent.h>
#include <fcntl.h>
#include <locale.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_NAME 50

int health = 99;
int level  = 1;
char name_buf[MAX_NAME];
int name_len;
char *name = &name_buf[0];

static const char* global_filter_name = ".dungeon";

int nameFilter(const struct dirent *entry) {
    return strstr(entry->d_name, global_filter_name) != NULL;
}

void save_game()
{
  uint16_t sep = 0xFFFF;
  int fd = open(".game", O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
  write(fd, &level, sizeof(level));
  write(fd, &sep, sizeof(sep));
  write(fd, &health, sizeof(health));
  write(fd, &sep, sizeof(sep));
  write(fd, name_buf, name_len);
  close(fd);
}

void load_game() 
{
  // load the game from the save file
  // would be useful, e.g. when a user logs back in
  uint16_t sep = 0xFFFF;
  int fd = open(".game", O_CREAT|O_RDONLY|O_TRUNC, S_IRUSR|S_IWUSR);
  read(fd, &level, sizeof(level));
  read(fd, &sep, sizeof(sep));
  read(fd, &health, sizeof(health));
  read(fd, &sep, sizeof(sep));
  read(fd, name_buf, name_len);
  close(fd);
}

void describe()
{
  FILE *f;
  char s;
  f=fopen(".dungeon","r");
  printf("***********\n");
  while((s=fgetc(f))!=EOF) {
    printf("%c",s);
  }
  printf("***********\n");
  fclose(f);
}


int main(void)
{
  setlocale(LC_ALL, "");
  printf("What is your name, brave adventurer? ");
  fgets(name_buf, MAX_NAME, stdin);
  char *pos;
  if ((pos=strchr(name_buf, '\n')) != NULL) { *pos = '\0'; }
  name_len = strlen(name_buf);
  printf("Welcome, %s\n", name);

  printf("If you would like to load a previously saved game, press 1. Otherwise, a new one will be created.\n");
    fgets(name_buf, MAX_NAME, stdin);
    if(name_buf == "1"){
        load_game();
    }

  save_game();

  struct dirent **namelist;
  int n;

  n = scandir(".", &namelist, nameFilter, alphasort);  
  if (n == -1) {
    exit(EXIT_FAILURE);
  } else if (n == 1) {
    describe();  // will read and print the room description
  } else {}

  free(namelist);
  return 0;
}