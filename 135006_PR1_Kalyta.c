#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data_Struct {
  int Hodnota_ID;
  int Hodnota_zn;
  int Hodnota_1;
  double Hodnota_2;
  struct Data_Struct *next;
} Data_Struct;

typedef struct Parse_Struct {
  char Poznamka_ID[7];
  double Poznamka_N1;
  int Poznamka_Hodina;
  int Poznamka_Minuta;
  char Poznamka_T[15];
  struct Parse_Struct *next;
} Parse_Struct;

typedef struct Combined_Struct {
  Data_Struct *data;
  Parse_Struct *parse;
  char Id_Mer_Modulu[7];
  struct Combined_Struct *next;
} Combined_Struct;

void v1_funkcia(FILE **data, FILE **parse, FILE **delimiter);
void h_funkcia(FILE **delimiter);
void n_funkcia(FILE **data, FILE **parse, FILE **delimiter, int **data_num1,
               int **data_num2, int **data_num3, double **data_num4,
               int *data_size, char ***parse_lines, int *parse_size,
               char ***delimiter_strings, int *delimiter_size);
void q_funkcia(int **data_num1, int **data_num2, int **data_num3,
               double **data_num4, int *data_size, char ***parse_lines,
               int *parse_size, char ***delimiter_strings, int *delimiter_size);
void w_funkcia(int **data_num1, int **data_num2, int **data_num3,
               double **data_num4, int *data_size, char ***parse_lines,
               int *parse_size, char ***delimiter_strings, int *delimiter_size);
void e_funkcia(char ***parse_lines, int *parse_size);
void v2_funkcia(int *data_num1, int *data_num2, int *data_num3,
                double *data_num4, int data_size, char **parse_lines,
                int parse_size, char **delimiter_strings, int delimiter_size);
void m_funkcia(FILE *data, FILE *parse, Combined_Struct **CombinedList);
void a_funkcia(FILE *data, FILE *parse, Combined_Struct **CombinedList);
void s_funkcia(FILE *data, FILE *parse, Combined_Struct **CombinedList);
void d_funkcia(FILE *data, FILE *parse, Combined_Struct **CombinedList);
void k_funkcia(FILE **data, FILE **parse, FILE **delimiter, int **data_num1, int **data_num2, int **data_num3, double **data_num4, char ***parse_lines, char ***delimiter_strings, Combined_Struct **CombinedList);

void v1_funkcia(FILE **data, FILE **parse, FILE **delimiter) {
  if (*data == NULL) {
    *data = fopen("data.txt", "r");
  }
  if (*parse == NULL) {
    *parse = fopen("parse.txt", "r");
    if (*parse == NULL) {
      fclose(*data);
      *data = NULL;
    }
  }
  if (*delimiter == NULL) {
    *delimiter = fopen("string.txt", "r");
    if (*delimiter == NULL) {
      fclose(*data);
      fclose(*parse);
      *data = NULL;
      *parse = NULL;
    }
  }
  char id_mer_modulu[7], poznamka[128];
  int num1, num2, num3;
  double num4;

  while ((fscanf(*data, "%d %d %d %lf", &num1, &num2, &num3, &num4) == 4) &&
         (fscanf(*delimiter, "%6s", id_mer_modulu) == 1) &&
         fgets(poznamka, sizeof(poznamka), *parse) != NULL) {
    printf("ID.mer.module: %s\nHodnota 1: %d\nHodnota 2: %g\nPoznamka: %s\n",
           id_mer_modulu, num3, num4, poznamka);
  }

  rewind(*data);
  rewind(*parse);
  rewind(*delimiter);
}

void h_funkcia(FILE **delimiter) {
  if (*delimiter == NULL) {
    *delimiter = fopen("string.txt", "r");
    if (*delimiter == NULL) {
      return;
    }
  } else {
    rewind(*delimiter);
  }

  int counter[256] = {0};
  int symbol;
  while ((symbol = fgetc(*delimiter)) != EOF) {
    if ((symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z') ||
        (symbol >= '0' && symbol <= '9')) {
      counter[symbol]++;
    }
  }

  for (symbol = 'A'; symbol <= 'Z'; symbol++) {
    if (counter[symbol] > 0) {
      printf("%c: %d\n", symbol, counter[symbol]);
    }
  }
  for (symbol = 'a'; symbol <= 'z'; symbol++) {
    if (counter[symbol] > 0) {
      printf("%c: %d\n", symbol, counter[symbol]);
    }
  }
  for (symbol = '0'; symbol <= '9'; symbol++) {
    if (counter[symbol] > 0) {
      printf("%c: %d\n", symbol, counter[symbol]);
    }
  }
}

void n_funkcia(FILE **data, FILE **parse, FILE **delimiter, int **data_num1,
               int **data_num2, int **data_num3, double **data_num4,
               int *data_size, char ***parse_lines, int *parse_size,
               char ***delimiter_strings, int *delimiter_size) {
  int tmp_num1, tmp_num2, tmp_num3;
  double tmp_num4;
  int data_records = 0;
  rewind(*data);
  while (fscanf(*data, "%d %d %d %lf", &tmp_num1, &tmp_num2, &tmp_num3,
                &tmp_num4) == 4) {
    data_records++;
  }

  char line[256];
  int parse_records = 0;
  rewind(*parse);
  while (fgets(line, sizeof(line), *parse) != NULL) {
    parse_records++;
  }

  char tmp_string[10];
  int delimiter_records = 0;
  rewind(*delimiter);
  while (fscanf(*delimiter, "%6s", tmp_string) == 1) {
    delimiter_records++;
  }

  int max_records = data_records;
  if (parse_records > max_records)
    max_records = parse_records;
  if (delimiter_records > max_records)
    max_records = delimiter_records;

  *data_num1 = (int *)malloc(data_records * sizeof(int));
  *data_num2 = (int *)malloc(data_records * sizeof(int));
  *data_num3 = (int *)malloc(data_records * sizeof(int));
  *data_num4 = (double *)malloc(data_records * sizeof(double));
  *data_size = data_records;

  *parse_lines = (char **)malloc(parse_records * sizeof(char *));
  *parse_size = parse_records;

  *delimiter_strings = (char **)malloc(delimiter_records * sizeof(char *));
  *delimiter_size = delimiter_records;

  rewind(*data);
  int i = 0;
  while (i < data_records && fscanf(*data, "%d %d %d %lf", &tmp_num1, &tmp_num2,
                                    &tmp_num3, &tmp_num4) == 4) {
    (*data_num1)[i] = tmp_num1;
    (*data_num2)[i] = tmp_num2;
    (*data_num3)[i] = tmp_num3;
    (*data_num4)[i] = tmp_num4;
    i++;
  }

  rewind(*parse);
  i = 0;
  while (i < parse_records && fgets(line, sizeof(line), *parse) != NULL) {
    int len = strlen(line);
    (*parse_lines)[i] = (char *)malloc((len + 1) * sizeof(char));
    strcpy((*parse_lines)[i], line);
    i++;
  }

  rewind(*delimiter);
  i = 0;
  while (i < delimiter_records && fscanf(*delimiter, "%6s", tmp_string) == 1) {
    int length = strlen(tmp_string);
    (*delimiter_strings)[i] = (char *)malloc((length + 1) * sizeof(char));
    strcpy((*delimiter_strings)[i], tmp_string);
    i++;
  }
}

void q_funkcia(int **data_num1, int **data_num2, int **data_num3,
               double **data_num4, int *data_size, char ***parse_lines,
               int *parse_size, char ***delimiter_strings,
               int *delimiter_size) {
  if (*data_num1 == NULL || *data_num2 == NULL || *data_num3 == NULL ||
      *data_num4 == NULL || *parse_lines == NULL ||
      *delimiter_strings == NULL) {
    printf("Q: Arrays are not created.\n");
    return;
  }

  int Y;
  if (scanf("%d", &Y) != 1) {
    printf("Error.\n");
    return;
  }
  getchar();
  int Y_index = Y - 1;

  char delimiter_input[10];
  if (fgets(delimiter_input, sizeof(delimiter_input), stdin) == NULL) {
    printf("Error.\n");
    return;
  }
  /*delimiter_input[strcspn(delimiter_input, "\n")] = '\0';*/

  int num1, num2, num3;
  double num4;
  if (scanf("%d %d %d %lf", &num1, &num2, &num3, &num4) != 4) {
    printf("Error.\n");
    return;
  }
  getchar();

  char parse_input[256];
  if (fgets(parse_input, sizeof(parse_input), stdin) == NULL) {
    printf("Error.\n");
    return;
  }
  /*parse_input[strcspn(parse_input, "\n")] = '\0';*/

  if (Y_index > *data_size) {
    Y_index = *data_size;
  }
  if (Y_index < 0) {
    Y_index = 0;
  }

  int new_size = *data_size + 1;
  *data_num1 = realloc(*data_num1, new_size * sizeof(int));
  *data_num2 = realloc(*data_num2, new_size * sizeof(int));
  *data_num3 = realloc(*data_num3, new_size * sizeof(int));
  *data_num4 = realloc(*data_num4, new_size * sizeof(double));

  *parse_lines = realloc(*parse_lines, (*parse_size + 1) * sizeof(char *));
  if (*parse_lines == NULL)
    printf("Failed.\n");

  *delimiter_strings =
      realloc(*delimiter_strings, (*delimiter_size + 1) * sizeof(char *));
  if (*delimiter_strings == NULL)
    printf("Failed.\n");

  if (Y_index < *data_size) {
    memmove(&(*data_num1)[Y_index + 1], &(*data_num1)[Y_index],
            (*data_size - Y_index) * sizeof(int));
    memmove(&(*data_num2)[Y_index + 1], &(*data_num2)[Y_index],
            (*data_size - Y_index) * sizeof(int));
    memmove(&(*data_num3)[Y_index + 1], &(*data_num3)[Y_index],
            (*data_size - Y_index) * sizeof(int));
    memmove(&(*data_num4)[Y_index + 1], &(*data_num4)[Y_index],
            (*data_size - Y_index) * sizeof(double));
  }
  if (Y_index < *parse_size) {
    memmove(&(*parse_lines)[Y_index + 1], &(*parse_lines)[Y_index],
            (*parse_size - Y_index) * sizeof(char *));
  }
  if (Y_index < *delimiter_size) {
    memmove(&(*delimiter_strings)[Y_index + 1], &(*delimiter_strings)[Y_index],
            (*delimiter_size - Y_index) * sizeof(char *));
  }

  (*data_num1)[Y_index] = num1;
  (*data_num2)[Y_index] = num2;
  (*data_num3)[Y_index] = num3;
  (*data_num4)[Y_index] = num4;

  (*parse_lines)[Y_index] = malloc((strlen(parse_input) + 1) * sizeof(char));
  strcpy((*parse_lines)[Y_index], parse_input);

  (*delimiter_strings)[Y_index] =
      malloc((strlen(delimiter_input) + 1) * sizeof(char));
  strcpy((*delimiter_strings)[Y_index], delimiter_input);

  (*data_size)++;
  (*parse_size)++;
  (*delimiter_size)++;
}

void w_funkcia(int **data_num1, int **data_num2, int **data_num3,
               double **data_num4, int *data_size, char ***parse_lines,
               int *parse_size, char ***delimiter_strings,
               int *delimiter_size) {
  if (*data_num1 == NULL || *data_num2 == NULL || *data_num3 == NULL ||
      *data_num4 == NULL || *parse_lines == NULL ||
      *delimiter_strings == NULL) {
    printf("W: Arrays are not created.\n");
    return;
  }

  char id_input[256];
  if (fgets(id_input, sizeof(id_input), stdin) == NULL) {
    printf("Error.\n");
    return;
  }
  id_input[strcspn(id_input, "\n")] = '\0';

  int deleted_records = 0, i;
  for (i = 0; i < *delimiter_size;) {
    if (strcmp((*delimiter_strings)[i], id_input) == 0) {
      free((*delimiter_strings)[i]);
      free((*parse_lines)[i]);

      if (i < *delimiter_size - 1) {
        memmove(&(*delimiter_strings)[i], &(*delimiter_strings)[i + 1],
                (*delimiter_size - i - 1) * sizeof(char *));
        memmove(&(*parse_lines)[i], &(*parse_lines)[i + 1],
                (*parse_size - i - 1) * sizeof(char *));
        memmove(&(*data_num1)[i], &(*data_num1)[i + 1],
                (*data_size - i - 1) * sizeof(int));
        memmove(&(*data_num2)[i], &(*data_num2)[i + 1],
                (*data_size - i - 1) * sizeof(int));
        memmove(&(*data_num3)[i], &(*data_num3)[i + 1],
                (*data_size - i - 1) * sizeof(int));
        memmove(&(*data_num4)[i], &(*data_num4)[i + 1],
                (*data_size - i - 1) * sizeof(double));
      }

      (*delimiter_size)--;
      (*parse_size)--;
      (*data_size)--;

      if (*delimiter_size > 0) {
        *delimiter_strings =
            realloc(*delimiter_strings, (*delimiter_size) * sizeof(char *));
      } else {
        free(*delimiter_strings);
        *delimiter_strings = NULL;
      }

      if (*parse_size > 0) {
        *parse_lines = realloc(*parse_lines, (*parse_size) * sizeof(char *));
      } else {
        free(*parse_lines);
        *parse_lines = NULL;
      }

      if (*data_size > 0) {
        *data_num1 = realloc(*data_num1, (*data_size) * sizeof(int));
        *data_num2 = realloc(*data_num2, (*data_size) * sizeof(int));
        *data_num3 = realloc(*data_num3, (*data_size) * sizeof(int));
        *data_num4 = realloc(*data_num4, (*data_size) * sizeof(double));
      } else {
        free(*data_num1);
        *data_num1 = NULL;
        free(*data_num2);
        *data_num2 = NULL;
        free(*data_num3);
        *data_num3 = NULL;
        free(*data_num4);
        *data_num4 = NULL;
      }

      deleted_records++;
    } else {
      i++;
    }
  }
  printf("W: Vymazalo sa: %d zaznamov!\n", deleted_records);
}

void e_funkcia(char ***parse_lines, int *parse_size) {
  if (*parse_lines == NULL) {
    printf("E: Arrays are not created.\n");
    return;
  }

  char search_word[256];
  if (fgets(search_word, sizeof(search_word), stdin) == NULL) {
    printf("Error.\n");
    return;
  }

  search_word[strcspn(search_word, "\n")] = '\0';

  int found = 0, i;
  for (i = 0; i < *parse_size; i++) {
    if (strstr((*parse_lines)[i], search_word) != NULL) {
      printf("%s", (*parse_lines)[i]);
      found = 1;
    }
  }

  if (!found)
    printf("Records are not founded.\n");
}

void v2_funkcia(int *data_num1, int *data_num2, int *data_num3,
                double *data_num4, int data_size, char **parse_lines,
                int parse_size, char **delimiter_strings, int delimiter_size) {
  if (data_num1 == NULL || data_num2 == NULL || data_num3 == NULL ||
      data_num4 == NULL || parse_lines == NULL || delimiter_strings == NULL ||
      data_size == 0 || parse_size == 0 || delimiter_size == 0) {
    printf("V2: Unfilled arrays.\n");
    return;
  }

  int max_records = data_size;
  if (parse_size > max_records)
    max_records = parse_size;
  if (delimiter_size > max_records)
    max_records = delimiter_size;
  int i;

  for (i = 0; i < max_records; i++) {
    printf("ID. mer. modulu: ");
    if (i < delimiter_size && delimiter_strings[i] != NULL &&
        strlen(delimiter_strings[i]) > 0) {
      printf("%s\n", delimiter_strings[i]);
    } else {
      printf("-\n");
    }

    printf("Hodnota 1: ");
    if (i < data_size) {
      printf("%d\n", data_num3[i]);
    } else {
      printf("0\n");
    }

    printf("Hodnota 2: ");
    if (i < data_size) {
      printf("%g\n", data_num4[i]);
    } else {
      printf("0.0\n");
    }

    printf("Poznamka: ");
    if (i < parse_size && parse_lines[i] != NULL &&
        strlen(parse_lines[i]) > 0) {
      printf("%s", parse_lines[i]);
      /* if (parse_lines[i][strlen(parse_lines[i])-1] != '\n') {
           printf("\n");
       }*/
    } else {
      printf("####\n");
    }
    printf("\n");
  }
}

void m_funkcia(FILE *data, FILE *parse, Combined_Struct **CombinedList) {
  if (data == NULL || parse == NULL) {
    printf("M: File not opened.\n");
    return;
  }

  int Hodnota_ID, Hodnota_zn, Hodnota_1;
  double Hodnota_2;

  char line[256];
  int count = 0;
  rewind(data);
  rewind(parse);

  Combined_Struct *head = NULL;
  Combined_Struct *tail = NULL;

  while (fscanf(data, "%d %d %d %lf", &Hodnota_ID, &Hodnota_zn, &Hodnota_1,
                &Hodnota_2) == 4 &&
         fgets(line, sizeof(line), parse)) {
    Data_Struct *newData = (Data_Struct *)malloc(sizeof(Data_Struct));
    newData->Hodnota_ID = Hodnota_ID;
    newData->Hodnota_zn = Hodnota_zn;
    newData->Hodnota_1 = Hodnota_1;
    newData->Hodnota_2 = Hodnota_2;
    newData->next = NULL;

    Parse_Struct *newParse = (Parse_Struct *)malloc(sizeof(Parse_Struct));
    char Poznamka_ID[7] = {0};
    double Poznamka_N1 = 0.0;
    int Poznamka_Hodina = 0;
    int Poznamka_Minuta = 0;
    char Poznamka_T[15] = {0};

    int fields =
        sscanf(line, "%[^#]#%lf#%2d#%2d#%[^#]#", Poznamka_ID, &Poznamka_N1,
               &Poznamka_Hodina, &Poznamka_Minuta, Poznamka_T);

    if (fields >= 1)
      strcpy(newParse->Poznamka_ID, Poznamka_ID);
    else
      strcpy(newParse->Poznamka_ID, Poznamka_ID);

    newParse->Poznamka_N1 = (fields >= 2) ? Poznamka_N1 : 0.0;
    newParse->Poznamka_Hodina = (fields >= 3) ? Poznamka_Hodina : 0;
    newParse->Poznamka_Minuta = (fields >= 4) ? Poznamka_Minuta : 0;
    if (fields >= 5)
      strcpy(newParse->Poznamka_T, Poznamka_T);
    else
      strcpy(newParse->Poznamka_T, "");
    newParse->next = NULL;

    Combined_Struct *newCombined =
        (Combined_Struct *)malloc(sizeof(Combined_Struct));
    newCombined->data = newData;
    newCombined->parse = newParse;
    strcpy(newCombined->Id_Mer_Modulu, Poznamka_ID);
    newCombined->next = NULL;

    if (tail) {
      tail->next = newCombined;
    } else {
      head = newCombined;
    }
    tail = newCombined;

    count++;
  }

  *CombinedList = head;
  printf("Nacitalo sa: %d zaznamov.\n", count);
}

void v3_funkcia(FILE *data, FILE *parse, FILE *delimiter,
                Combined_Struct **CombinedList) {
  if (data == NULL || parse == NULL || delimiter == NULL ||
      *CombinedList == NULL) {
    printf("V3: Unfilled linked list.\n");
    return;
  }

  Combined_Struct *current = *CombinedList;

  while (current != NULL) {
    if (strlen(current->Id_Mer_Modulu) > 0) {
      printf("Id. mer. modulu: %s\n", current->Id_Mer_Modulu);
    } else {
      printf("ID. mer. modulu: -\n");
    }

    printf("Hodnota 1: %d\n", current->data->Hodnota_1);
    printf("Hodnota 2: %.4lf\n", current->data->Hodnota_2);

    if (strlen(current->parse->Poznamka_ID) > 0) {
      printf("Poznamka ID: %s\n", current->parse->Poznamka_ID);
    } else {
      printf("Poznamka ID: NaN\n");
    }

    if (current->parse->Poznamka_N1 > 0.0) {
      printf(
          "Poznamka C: %d : %d => %.4lf\n",
          (current->parse->Poznamka_Hodina > 0 ? current->parse->Poznamka_Hodina
                                               : -1),
          (current->parse->Poznamka_Minuta > 0 ? current->parse->Poznamka_Minuta
                                               : -1),
          current->parse->Poznamka_N1);
    } else {
      printf("Poznamka C: -1 : -1 => -1\n");
    }

    if (strlen(current->parse->Poznamka_T) > 0) {
      printf("Poznamka T: %s\n", current->parse->Poznamka_T);
    } else {
      printf("Poznamka T: NaN\n");
    }
    printf("\n");

    current = current->next;
  }
}

void a_funkcia(FILE *data, FILE *parse, Combined_Struct **CombinedList) {
  int Y;
  if (scanf("%d", &Y) != 1) {
    printf("Error.\n");
    return;
  }
  getchar();

  char Id_Mer_Modulu[7];
  if (fgets(Id_Mer_Modulu, sizeof(Id_Mer_Modulu), stdin) == NULL) {
    printf("Error.\n");
    return;
  }

  int Hodnota_ID, Hodnota_zn, Hodnota_1;
  double Hodnota_2;
  if (scanf("%d %d %d %lf", &Hodnota_ID, &Hodnota_zn, &Hodnota_1, &Hodnota_2) !=
      4) {
    printf("Error.\n");
    return;
  }
  getchar();

  char parse_input[256];
  if (fgets(parse_input, sizeof(parse_input), stdin) == NULL) {
    printf("Error.\n");
    return;
  }

  char Poznamka_ID[7] = "";
  double Poznamka_N1 = 0.0;
  int Poznamka_Hodina = -1, Poznamka_Minuta = -1;
  char Poznamka_T[15] = "";
  int fields =
      sscanf(parse_input, "%[^#]#%lf#%2d%2d#%[^#]", Poznamka_ID, &Poznamka_N1,
             &Poznamka_Hodina, &Poznamka_Minuta, Poznamka_T);

  Data_Struct *newData = (Data_Struct *)malloc(sizeof(Data_Struct));
  newData->Hodnota_ID = Hodnota_ID;
  newData->Hodnota_zn = Hodnota_zn;
  newData->Hodnota_1 = Hodnota_1;
  newData->Hodnota_2 = Hodnota_2;
  newData->next = NULL;

  Parse_Struct *newParse = (Parse_Struct *)malloc(sizeof(Parse_Struct));
  if (newParse == NULL) {
    free(newData);
    return;
  }
  strcpy(newParse->Poznamka_ID, (fields >= 1) ? Poznamka_ID : "NaN");
  newParse->Poznamka_N1 = (fields >= 2) ? Poznamka_N1 : -1.0;
  newParse->Poznamka_Hodina = (fields >= 3) ? Poznamka_Hodina : -1;
  newParse->Poznamka_Minuta = (fields >= 4) ? Poznamka_Minuta : -1;
  strcpy(newParse->Poznamka_T, (fields >= 5) ? Poznamka_T : "NaN");
  newParse->next = NULL;

  Combined_Struct *newCombined =
      (Combined_Struct *)malloc(sizeof(Combined_Struct));
  if (newCombined == NULL) {
    free(newData);
    free(newParse);
    return;
  }
  newCombined->data = newData;
  newCombined->parse = newParse;
  strcpy(newCombined->Id_Mer_Modulu, Id_Mer_Modulu);
  newCombined->next = NULL;

  if (*CombinedList == NULL || Y <= 1) {
    newCombined->next = *CombinedList;
    *CombinedList = newCombined;
  } else {
    Combined_Struct *current = *CombinedList;
    int index = 1;
    while (current->next != NULL && index < Y - 1) {
      current = current->next;
      index++;
    }
    newCombined->next = current->next;
    current->next = newCombined;
  }
}

void s_funkcia(FILE* data, FILE* parse, Combined_Struct **CombinedList) {
    if (*CombinedList == NULL) {
        printf("S: Linked list is not created.\n");
        return;
    }

    char Id_Mer_Modulu[7];
    if (fgets(Id_Mer_Modulu, sizeof(Id_Mer_Modulu), stdin) == NULL) {
        printf("Error.\n");
        return;
    }

    int deleted_records = 0;
    Combined_Struct* current = *CombinedList;
    Combined_Struct* prev = NULL; // Pointer on the previous element

    while (current != NULL) {
        if(strcmp(Id_Mer_Modulu, current->Id_Mer_Modulu) == 0) {
            Combined_Struct* deletion = current;

            if (prev == NULL) {
                *CombinedList = current->next;
            } else {
                prev->next = current->next;
            }

            current = current->next;

            free(deletion->data);
            free(deletion->parse);
            free(deletion);
            deleted_records++;
        } else {
            prev = current;
            current = current->next;
        }
    }

    printf("S: Vymazalo sa: %d zaznamov!\n", deleted_records);
}

void d_funkcia(FILE* data, FILE* parse, Combined_Struct **CombinedList) {
    int c1, c2;
    scanf("%d %d", &c1, &c2);
    if (c1 <= 0 || c2 <= 0) {
        printf("Error. C1 and C2 should be more than zero.\n");
        return;
    }

    Combined_Struct* current_1 = *CombinedList;
    Combined_Struct* current_2 = *CombinedList;
    int current_index_c1 = 1;
    int current_index_c2 = 1;

    while (current_1 != NULL && current_index_c1 < c1) {
        current_1 = current_1->next;
        current_index_c1++;
    }

    while (current_2 != NULL && current_index_c2 < c2) {
        current_2 = current_2->next;
        current_index_c2++;
    }

    if (current_1 == NULL || current_2 == NULL) {
        printf("Error.\n");
        return;
    }

    char temp[7];
    strcpy(temp, current_1->Id_Mer_Modulu);
    strcpy(current_1->Id_Mer_Modulu, current_2->Id_Mer_Modulu);
    strcpy(current_2->Id_Mer_Modulu, temp);

    Data_Struct* temp_data = current_1->data;
    current_1->data = current_2->data;
    current_2->data = temp_data;

    Parse_Struct* temp_parse = current_1->parse;
    current_1->parse = current_2->parse;
    current_2->parse = temp_parse;
}

void k_funkcia(FILE **data, FILE **parse, FILE **delimiter, int** data_num1, int** data_num2, int** data_num3, double** data_num4, char*** parse_lines, char*** delimiter_strings,  Combined_Struct **CombinedList) {
    if (*data_num1 != NULL) {
        free(*data_num1);
        *data_num1 = NULL;
    }
    if (*data_num2 != NULL) {
        free(*data_num2);
        *data_num2 = NULL;
    }
    if (*data_num3 != NULL) {
        free(*data_num3);
        *data_num3 = NULL;
    }
    if (*data_num4 != NULL) {
        free(*data_num4);
        *data_num4 = NULL;
    }

    if (*parse_lines != NULL) {
        for (int i = 0; (*parse_lines)[i] != NULL; i++) {
            free((*parse_lines)[i]);
        }
        free(*parse_lines);
        parse_lines = NULL;
    }

    if (*delimiter_strings != NULL) {
        for (int i = 0; (*delimiter_strings)[i] != NULL; i++) {
            free((*delimiter_strings)[i]);
        }
        free(*delimiter_strings);
        delimiter_strings = NULL;
    }

    if (*data != NULL) {
        fclose(*data);
        *data = NULL;
    }

    if (*parse != NULL) {
        fclose(*parse);
        *parse = NULL;
    }

    if (*delimiter != NULL) {
        fclose(*delimiter);
        *delimiter = NULL;
    }
    Combined_Struct* current = *CombinedList;
    Combined_Struct* next;

    while (current != NULL) {
        next = current->next;
        if (current->data != NULL) {
            free(current->data);
        }
        if (current->parse != NULL) {
            free(current->parse);
        }

        free(current);
        current = next;
    }
    *CombinedList = NULL;
}

int main() {
  FILE *data = NULL, *parse = NULL, *delimiter = NULL;
  char input1[10], input2[10];

  int *data_num1 = NULL;
  int *data_num2 = NULL;
  int *data_num3 = NULL;
  double *data_num4 = NULL;
  int data_size = 0;

  char **parse_lines = NULL;
  int parse_size = 0;

  char **delimiter_strings = NULL;
  int delimiter_size = 0;

  Combined_Struct *CombinedList = NULL;

  while (1) {
    if (fgets(input1, sizeof(input1), stdin) == NULL) {
      printf("Input error.\n");
      break;
    }
    input1[strcspn(input1, "\n")] = '\0';

    if (strcmp(input1, "v") == 0) {
      if (fgets(input2, sizeof(input2), stdin) == NULL) {
        continue;
      }
      input2[strcspn(input2, "\n")] = '\0';
      if (strcmp(input2, "1") == 0) {
        v1_funkcia(&data, &parse, &delimiter);
      } else if (strcmp(input2, "2") == 0) {
        v2_funkcia(data_num1, data_num2, data_num3, data_num4, data_size,
                   parse_lines, parse_size, delimiter_strings, delimiter_size);
      } else if (strcmp(input2, "3") == 0) {
        v3_funkcia(data, parse, delimiter, &CombinedList);
      }
    } else if (strcmp(input1, "h") == 0) {
      h_funkcia(&delimiter);
    } else if (strcmp(input1, "n") == 0) {
      n_funkcia(&data, &parse, &delimiter, &data_num1, &data_num2, &data_num3,
                &data_num4, &data_size, &parse_lines, &parse_size,
                &delimiter_strings, &delimiter_size);
    } else if (strcmp(input1, "q") == 0) {
      q_funkcia(&data_num1, &data_num2, &data_num3, &data_num4, &data_size,
                &parse_lines, &parse_size, &delimiter_strings, &delimiter_size);
    } else if (strcmp(input1, "w") == 0) {
      w_funkcia(&data_num1, &data_num2, &data_num3, &data_num4, &data_size,
                &parse_lines, &parse_size, &delimiter_strings, &delimiter_size);
    } else if (strcmp(input1, "e") == 0) {
      e_funkcia(&parse_lines, &parse_size);
    } else if (strcmp(input1, "m") == 0) {
      m_funkcia(data, parse, &CombinedList);
    } else if (strcmp(input1, "a") == 0) {
      a_funkcia(data, parse, &CombinedList);
    } else if (strcmp(input1, "s") == 0) {
        s_funkcia(data, parse, &CombinedList);
    } else if (strcmp(input1, "d") == 0) {
        d_funkcia(data, parse, &CombinedList);
    } else if (strcmp(input1, "k") == 0) {
        k_funkcia(&data, &parse, &delimiter,  &data_num1, &data_num2, &data_num3, &data_num4, &parse_lines, &delimiter_strings, &CombinedList);
    } else {
      printf("Nespravne volba vypisu.\n");
    }
  }
  return 0;
}
