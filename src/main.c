// originally made by Hana Fathiyah 13520047

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "finder/move.h"
#include "pcolor/pcolor.h"

bool result[255][255];
int eqCounter = 0;

bool isPositionMatch(char* str, Position pos, Direction dir, Size s, char matrix[255][255]){
    Position currentPos = pos;
    int length = 0;
    int stringLength = strlen(str) - 1;

    while(isPositionValid(currentPos, s)) {
        eqCounter++;
        if(str[length] == matrix[currentPos.row][currentPos.col]){
            length++;
        }else{
            return false;
        }

        if(length == stringLength){
            return true;
        }

        currentPos = move(currentPos, dir);
    }

    return false;
}

void setTableFlag(int length, Position pos, Direction dir){
    Position currentPos = pos;
    int i = 0;

    while(i < length) {
        result[currentPos.row][currentPos.col] = true;
        i++;
        currentPos = move(currentPos, dir);
    }
}

void checkWord(char* str, char matrix[255][255], Size s) {
    for(int i = 0; i < s.rows; i++){
        for(int j = 0; j < s.cols; j++){
            result[i][j] = false;
        }
    }

    int strlength = strlen(str);

    for(int i = 0; i < s.rows; i++){
        for(int j = 0; j < s.cols; j++){
            Position pos;
            pos.row = i;
            pos.col = j;

            for(int k = 0; k < 8; k++){
                if(isPositionMatch(str, pos, k, s, matrix)) {
                    setTableFlag(strlength-1, pos, k);
                }
            }
        }
    }
};

int main () {
    printf("WORD SEARCH GAME ENGINE\n");
    printf("originally made by Hana Fathiyah\n\n");
    char file_names[255];
    printf("insert file's name: ");
    scanf("%s",file_names);
        

  FILE *game_file = fopen(file_names, "r");

  if(!game_file){
    printf("The file that you want to open is not exist.\n");
    return false;
  }

  char word_list[255][255];
  char game_matrix[255][255];
  char line[255];
  bool next_line_of_matrix = true;
  int game_row = 0;
  int game_column = 0;
  int word_count = 0;

  while(next_line_of_matrix) {
      fscanf(game_file,"%[^\n]\n",line);

      if(line[1] == ' ') {
          game_column = 0;
          for(int i = 0; i < (int) strlen(line); i++) {
              if(line[i] != ' ') {
                  game_matrix[game_row][game_column] = line[i]; 
                  game_column++;
              }
          }

          game_row++;
      } else {
          next_line_of_matrix = false;
          strcpy(word_list[word_count], line);
          word_count++;
      }
  } 

  while(!feof(game_file)) {
      fscanf(game_file,"%[^\n]\n",line);
      strcpy(word_list[word_count],line);
      word_count++;
  }

  Size matrix;
  matrix.cols=game_column - 1;
  matrix.rows=game_row;
  fclose(game_file);
  
  int display[255][255];
  for(int i = 0; i < matrix.rows; i++) {
      for(int j = 0; j < matrix.cols; j++) {
          display[i][j] = -1;
      }
  }
  int game_coloring = 0;
  int cnt_alpha_match = 0;
  for(int i = 0; i < word_count; i++){
      checkWord(word_list[i], game_matrix, matrix);
      for(int i = 0; i < matrix.rows; i++){
          for(int j=0; j < matrix.cols; j++){
             if(result[i][j]){
                 display[i][j] = game_coloring;
                 //printf("%c", game_matrix[i][j]);
             } else {
                 //printf("-");
             }
             if (j < matrix.cols - 1) {
                 //printf(" ");
             }
             cnt_alpha_match++;
          }
          //printf("\n");
      }
      //printf("\n\n");
      game_coloring++;
  }
  
  for(int i = 0; i < matrix.rows; i++) {
      for(int j = 0; j < matrix.cols; j++) {
        if (display[i][j] >= 0) {
            if (display[i][j] % 6 == 0) {
                print_red(game_matrix[i][j]);
            } else if (display[i][j] % 6 == 1) {
                print_green(game_matrix[i][j]);
            } else if (display[i][j] % 6 == 2) {
                print_yellow(game_matrix[i][j]);
            } else if (display[i][j] % 6 == 3) {
                print_blue(game_matrix[i][j]);
            } else if (display[i][j] % 6 == 4) {
                print_magenta(game_matrix[i][j]);
            } else if (display[i][j] % 6 == 5) {
                print_cyan(game_matrix[i][j]);
            }
        } else {
            printf("%c", game_matrix[i][j]);
        }
        if (j < matrix.cols - 1) {
            printf(" ");
        }
      }
    printf("\n");
  }

  printf("Jumlah perbandingan: %d\n", eqCounter);
}