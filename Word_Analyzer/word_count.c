#include <unistd.h>
#include <"word_count_My.h">
#include <stdio.h>
#include <string.h>
#define MAX_WORD_LEN    35
#define MAX_WORD_CNT    750
typedef char* String;

int
real_main(int argc, char *argv[]) {
    if(argc < 3){
        printf("program: missing '--infile <filename> [--sort] [--print-words]'\n");
        return 1;
    }
    FILE* fp;
    FILE* fp2;
    String filename = Find_file(argc, argv);
    String PartType = "";
   
    int wordCounter = 0; // JUST A COUNTER THAT COUNTS THE WORD LENGTHS WITH AT LEATS 1 FREQUENCY

    if(strcmp(find_part(argc, argv), "A") == 0){
        PartType = "A";
    }
    else if(strcmp(find_part(argc, argv), "B") == 0){
        PartType = "B";
    }
    else if(strcmp(find_part(argc, argv), "C") == 0){
        PartType = "C";
    }
    else{
        return 1;
    }
    fp = fopen(filename, "r");
    fp2 = fopen(filename, "r");
    if(access(filename,F_OK) == -1){
        printf("unable to open 'badfile.txt' for reading\n");
        return 1;
    }
    int size = countWords(fp2); // A VARIABLE CONTAINING THE NUMBER OF WORDS IN THE FILE
    if(size == 0 && strcmp(PartType, "B") == 0){
         printf("Median word length: 0.0\n");      
         return 0;
    }
    else if(size == 0 && (strcmp(PartType, "C") == 0 || strcmp(PartType, "A") == 0)){
        return 0;
    }
    
    char str[size][MAX_WORD_LEN];
    
    for(int i = 0; i<size; i++){
        for(int j = 0; j<MAX_WORD_LEN; j++){
            str[i][j] = '\0';
        }
    }
    
        for(int i = 0; i<size; i++){
            fscanf(fp, "%s", str[i]);                                                           
            if(contains_UN(str[i])){
            char* token = strtok(str[i], ",.-;");
            while(token != NULL){
                token = strtok (NULL, ",.-;");
            }
        }
    }

    
    fclose(fp);
    String list[MAX_WORD_LEN][MAX_WORD_CNT];
    int sizes[MAX_WORD_LEN][2];
    int sizesCopy[MAX_WORD_LEN][2];

    for(int i = 0; i<MAX_WORD_LEN; i++){
        sizes[i][0] = i+1;
    }
    for(int i = 0; i<size; i++){
        sizes[strlen(str[i]) - 1][1] = sizes[strlen(str[i]) - 1][1] + 1;
    }
    for(int i = 0; i<MAX_WORD_LEN; i++){
        sizesCopy[i][0] = sizes[i][0];
        sizesCopy[i][1] = sizes[i][1]; 
    }
    for(int i = 0; i<MAX_WORD_LEN; i++){
        if(sizesCopy[i][1] != 0) wordCounter++;
    }
    
    // SORTING THE WORD COUNTERS BY LARGEST FIRST (HIGHEST FREQUENCY TO LOWEST)
    for(int k = 0; k<MAX_WORD_LEN; k++){
        for(int i = 0; i<MAX_WORD_LEN; i++){
            if(sizes[i][1] < sizes[i+1][1]){
                int temp1 = sizes[i][0];
                int temp2 = sizes[i][1];
                sizes[i][0] = sizes[i+1][0];
                sizes[i][1] = sizes[i+1][1];
                sizes[i+1][0] = temp1;
                sizes[i+1][1] = temp2;
            }
        }
    }

    // PUTTING THE DATA OF THE WORDS INTO AN ARRAY: list
    for(int i = 0; i<MAX_WORD_LEN; i++){
        for(int k = 0; k<size; k++){
            if(strlen(str[k]) == (i+1)){
                int j = 0;
                while(list[i][j] != NULL){
                    j++;
                }
                list[i][j] = str[k];
            }
        }
    }
    
    // SORTING IN ALPHANUMERICAL ORDER (THE LIST THAT CONTAINS THE WORDS)
    for(int i = 0; i<MAX_WORD_LEN; i++){
        int listSize = sizesCopy[i][1];
        if(listSize != 0){
            for(int k = 0; k<listSize; k++){
                for(int j = 0; j<listSize-1; j++){
                    if(list[i][j] != NULL && list[i][j+1] != NULL && strcmp(list[i][j], list[i][j+1]) > 0){
                        String temp = list[i][j];
                        list[i][j] = list[i][j+1];
                        list[i][j+1] = temp;
                    }
                }
            }
        }
    }
    
   // DISPLAYING RESULTS ACCORDING TO PART "C" OF THE ASSIGNMENT, SORTED AND WITH WORDS
    for(int i = 0; i<MAX_WORD_LEN; i++){
        if(!sizes[i][1] == 0 && strcmp(PartType, "C") == 0){
            int flag = 0;
            if(sizes[i+1][1] == 0){
                flag = 1;
            }
            if(sizes[i][0] >= 10 && sizes[i][1] >= 10) printf("Count[%d]=%d; (words: ", sizes[i][0], sizes[i][1]);
            else if(sizes[i][0] >= 10 && sizes[i][1] < 10) printf("Count[%d]=0%d; (words: ", sizes[i][0], sizes[i][1]);
            else if(sizes[i][0] < 10 && sizes[i][1] >= 10) printf("Count[0%d]=%d; (words: ", sizes[i][0], sizes[i][1]);
            else printf("Count[0%d]=0%d; (words: ", sizes[i][0], sizes[i][1]);
            int num = sizes[i][1];
            int num2 = sizes[i][0] - 1;
            int aftersize = num;
            display_results(list, aftersize, num2, flag, PartType, sizesCopy);
        }
        else if(!sizes[i][1] == 0 && strcmp(PartType, "B") == 0){
            if(sizes[i][0] >= 10 && sizes[i][1] >= 10) printf("Count[%d]=%d;", sizes[i][0], sizes[i][1]);
            else if(sizes[i][0] >= 10 && sizes[i][1] < 10) printf("Count[%d]=0%d;", sizes[i][0], sizes[i][1]);
            else if(sizes[i][0] < 10 && sizes[i][1] >= 10) printf("Count[0%d]=%d;", sizes[i][0], sizes[i][1]);
            else printf("Count[0%d]=0%d;", sizes[i][0], sizes[i][1]);
            printf("\n");
        }
    }
    if(strcmp(PartType, "B") == 0){
        Display_resultsB(wordCounter, sizesCopy);
        return 0;
    }
    else if(strcmp(PartType, "A") == 0){
        Display_resultsA(sizesCopy);
        return 0;
    }
    fclose(fp2);
    printf("\n");
    return 0;
}


#ifndef TEST
int
main(int argc, char *argv[]) {
    return real_main(argc, argv);
}
#endif
