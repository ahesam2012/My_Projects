#include <stdio.h>
#include <string.h>
#define FILE_NOT_FOUND  1
#define BAD_ARGS        2
#define MAX_FILESIZE    5000
#define MAX_WORD_CNT    750
#define MAX_WORD_LEN    35 //Supercalifragilisticexpialidocious
#define true 1
#define false 0
typedef int bool;
typedef char* String;


// RETURNS THE NUMBER OF WORDS IN A TEXTFILE
	int countWords(FILE* f){ 
	char string[27000];
	char c;
	int i = 0;
	while ((c = fgetc(f)) != EOF){
    	string[i] = c;
    	i++;
	}   
	char* token = strtok(string, " ,.-'\n'");
	int num = 0;
	while(token != NULL){
    	num++;
    	token = strtok (NULL, " ,.-'\n'");
	} //printing the token
   return num;
}

// CHECKS IF A STRING CONTAINS A CERTAIN CHARACTER,    
// RETURNS TRUE IF IT DOES, FALSE OTHERWISE
_Bool contains_UN(char str[]){
    int size = strlen(str);
    for(int i = 0; i<size; i++){
        if(str[i] == ',' || str[i] == '.' || str[i] == ';' || str[i] == '"'){
            return true;
        }
    }
    return false;
}

// THE METHOD TO PRINT OUT THE RESULTS FOR PART C
void display_results(String array[MAX_WORD_LEN][MAX_WORD_CNT], int size1, int index, int flag, String type, int sizesCopy[35][2]){
    String array2[size1];
    int Newsize = size1;
    array2[0] = array[index][0];
    
    // JUST REMOVING DUPLICATES BEFORE SHOWING RESULTS
    int k = 1;
    for(int i = 1; i<size1; i++){
        String word1 = array2[k-1];
        String word2 = array[index][i];
        int result = strcmp(word1, word2);
        if(result == 0){
            Newsize--;
            continue;
        }
        else {
            array2[k] = array[index][i];
            k++; 
        }
    }
    
    for(int s = 0; s<Newsize; s++){
        if(s < Newsize - 2){
            printf("\"%s\", ", array2[s]);
        }
        else if(s == Newsize - 2){
            printf("\"%s\" and ", array2[s]);
        }
        else {
            printf("\"%s\")", array2[s]);
        }
    }
    
    if(flag == 1){
        return;
    }
    printf("\n");
}


// A FUNCTION TO DISPLAY RESULTS FOR PART B
void Display_resultsB(int size, int sizesCopy[35][2]){
        int array[size];
        double median;
        int k = 0;
        for(int i = 0; i<35; i++){
            if(sizesCopy[i][1] != 0){
            	array[k] = sizesCopy[i][0];
            	k++;
            }
        }
        if(size == 1 || size == 2){
            if(size == 1){
                median = array[0];
                printf("Median word length: %.1f", median);
                return;
            }
            else{
                median = (array[0] + array[1])/2;
                printf("Median word length: %.1f", median);
                return;
            }
        }
        else if(size%2 == 0){
            int num = size/2;
            int num2 = num-1;
            double number = array[num] + array[num2];
            median = number/2;
        }
        else {
            int number = size/2;
            median = array[number];
        }
    printf("Median word length: %.1f", median);
    printf("\n");
   	return;
}


// A FUCNTION THAT DISPLAYS RESULTS FOR PART A
void Display_resultsA(int array[35][2]){
	int sizes[35][2];
	for(int i = 0; i<MAX_WORD_LEN; i++){
		sizes[i][0] = array[i][0];
		sizes[i][1] = array[i][1];
	}
	for(int i = 0; i<MAX_WORD_LEN; i++){
		if(sizes[i][1] != 0){
			if(sizes[i][0] >= 10 && sizes[i][1] >= 10) printf("Count[%d]=%d;", sizes[i][0], sizes[i][1]);
            else if(sizes[i][0] >= 10 && sizes[i][1] < 10) printf("Count[%d]=0%d;", sizes[i][0], sizes[i][1]);
            else if(sizes[i][0] < 10 && sizes[i][1] >= 10) printf("Count[0%d]=%d;", sizes[i][0], sizes[i][1]);
            else printf("Count[0%d]=0%d;", sizes[i][0], sizes[i][1]);
            printf("\n");
		}
	}
}


// A FUNCTION THAT TELLS THE PROGRAM WHICH PART TO OUTPUT RESULTS FOR, BASED ON ARGUMENTS PASSED
// RETURNS "A" FOR PARTA, "B" FOR PART B AND "C" FOR PART C
String find_part(int argc, String argv[]){
    if(argc == 3 && strcmp(argv[1], "--infile") == 0){
        return "A";
    }
    else if(argc == 4){
        for(int i = 0; i<argc; i++){
            if(strcmp(argv[i], "--sort") == 0){
                return "B";
            }
        }
    }
    else if(argc == 5){
        int foundCount = 0;
        for(int i = 0; i<argc; i++){
            if(strcmp(argv[i], "--sort") == 0){
                foundCount++;
                break;
            }
        }
        for(int i = 0; i<argc; i++){
            if(strcmp(argv[i], "--print-words") == 0){
                foundCount++;
                break;
            }
        }
        if(foundCount == 2){
            return "C";
        }
    }
    return "WRONG ARGS!";
}


// A FUNCTION THAT RETURNS THE FILENAME AFTER IT FINDS IT IN THE ARRAY OF ARGUMENTS
String Find_file(int argc, String argv[]){
    String filename;
    for(int i = 0; i<argc; i++){
        if(strcmp(argv[i], "--infile") == 0){
            filename =  argv[i+1];
            return filename;
        }
    }
    return "BADFILE348759837fhejej";
}

// A FUNCTION TO PRINT A 2D INTEGER ARRAY MADE FOR TESTING PURPOSES
void display_array(int array[35][2], int size){
    printf("{");
    for(int i = 0; i<size; i++){
        if(i < size - 1) printf("(%d, %d), ", array[i][0], array[i][1]);
        else printf("(%d, %d)}", array[i][0], array[i][1]);
    }
}





