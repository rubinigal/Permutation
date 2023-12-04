#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_WORD_LENGTH 100
int permutation(char* str, char* word);
void remove_char(char *str, int index);

int main(int argc, char *argv[]) 
{
  char *input_file_name = argv[1];
  char *search_word = argv[2];  
  char line[MAX_LINE_LENGTH];
  FILE *input_file = fopen(input_file_name, "r"); /*opening the file with the name that we got*/

  if (argc != 3) /*incorrect number of arguments*/
  {
    fprintf(stderr, "Error: incorrect number of arguments\n");
    exit(1);
  }
 
  if (!input_file) /*failed to open the file*/
  {
    fprintf(stderr, "Error: failed to open input file\n");
    exit(2);
  }

  fseek(input_file, 0, SEEK_END); 
  if (ftell(input_file) == 0) /*file is empty*/
  {
    fprintf(stderr, "The file is empty\n");
    exit(3);
  }

  while (fgets(line, MAX_LINE_LENGTH, input_file)) /*loop that get every time a line in a file*/
  {
    int line_length = strlen(line);
    int search_word_length = strlen(search_word);
    int i, j;
    char found_word[MAX_WORD_LENGTH];

    for (i = 0; i < line_length - search_word_length + 1; ++i) /*loop that runs until you wont find the word*/
    {
      int match = 1;
      int found_word_index = 0;

      if (permutation(&line[i], search_word)) /*checking the word for permutation, it returns 0 if true*/
      {
        match = 0;
      }
    

      if (match) /*we found the word that we want and now we need to print it*/
      { 
        for (j = i; j < (search_word_length + i); ++j) /*printing the found permutation word*/
        {
          found_word[found_word_index++] = line[j];
        }
        found_word[found_word_index] = '\0';
        printf("%s\n", found_word);
      }
    }
  }

  if (ferror(input_file)) /*checking if we got errors while reading the file*/
  {
    fprintf(stderr, "Error: failed to read input file\n");
    exit(4);
  }

  fclose(input_file);
  return 0;
}

int permutation(char *str, char *word)
{
    char word_copy[MAX_WORD_LENGTH];
    int i,j;
    int length = strlen(word);

    for ( i = 0; i <= length; i++) /*copy the string*/
    {
        word_copy[i] = word[i];
    }
    

    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length; j++)
        {
            if (str[i] == word_copy[j])
            {
                remove_char(word_copy, j); /*we remove the char that we found in the word and that will prevent duplicants of the same char*/
                break;
            }  
        }
        if (j == length) /*we are using break in the loop before that means that if one of the chars of the word didnt got found j will reach the end of the loop*/
        {
            return 1;
        }
        
    }

    return 0;
}

void remove_char(char str[], int index) /*as the name says removing one char that we want*/
{
  int i;
  int length = strlen(str);
  for (i = index; i < length - 1; ++i) 
  {
    str[i] = str[i + 1];
  }
  str[length - 1] = '\0';
}
