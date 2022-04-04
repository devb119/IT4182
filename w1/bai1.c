#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "libfdr/jrb.h"

JRB dict;
char stopWords[50][50];
char properNouns[100][50];
int countDict[500][100];
int n=0;
int properNounsNum = 0;
int stopWordsNum;

int containsNumber(char s[]){
    for(int i=0; i<strlen(s); i++){
        if(isdigit(s[i])){
            return 1;
        }
    }
    return 0;
}

int isStopWord(char s[]){
    for(int i=0; i<stopWordsNum; i++){
        if(strcasecmp(s, stopWords[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int isProperNoun(char s[]){
    for(int i=0; i<properNounsNum; i++){
        if(strcasecmp(s, properNouns[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void toLowerCase(char s[]){
    for(int i=0; i<strlen(s); i++){
        s[i] = tolower(s[i]);
    }
}

void readProperNouns(){
    FILE *f = fopen("vanban.txt", "r");
    char lastWord[30];
    strcpy(lastWord, "");
    while(!feof(f)){
        char s[30];
        fscanf(f, "%s", s);
        if(strlen(lastWord) != 0){
            if(lastWord[strlen(lastWord) - 1] != "." && isupper(s[0])){
                int lastIdx = strlen(s) - 1;
                if(!isalpha(s[strlen(s)-1])){
                    memmove(&s[lastIdx], &s[lastIdx + 1], strlen(s) - lastIdx);
                }
                strcpy(properNouns[properNounsNum], s);
                properNounsNum++;
            }
        }
        strcpy(lastWord, s);
    }
}

void readFile(){
    FILE *f = fopen("vanban.txt", "r");
    int line = 1;
    while (!feof(f))
    {
        char s[200];
        fgets(s, 200, f);
        if(s[strlen(s)-1] == '\n'){
            s[strlen(s) - 1] = '\0';
        }
        char *word = strtok(s, "(),. ");
        char wordCopy[20];
        while(word){
            strcpy(wordCopy,word);
            toLowerCase(wordCopy);
            if(!isStopWord(wordCopy) && !containsNumber(wordCopy) && !isProperNoun(wordCopy)){
                JRB node = jrb_find_str(dict, wordCopy);
                if(!node){
                    char *key = strdup(wordCopy);
                    jrb_insert_str(dict, key, (Jval){.i = n});
                    node = jrb_find_str(dict, wordCopy);
                    countDict[node->val.i][0] = 1;
                    countDict[node->val.i][1] = line;
                    n++;
                }else{
                    int nodeIdx = node->val.i;
                    // Tang so lan xuat hien len 1
                    countDict[nodeIdx][0]++;
                    // pos la vi tri chen them dong trong mang
                    int pos = countDict[nodeIdx][0];
                    countDict[nodeIdx][pos] = line;
                }
            }
            word = strtok(NULL, "(),. ");
        }
        line++;
    }
    fclose(f);
}

int readStopWord(){
    FILE *f = fopen("stopw.txt", "r");
    int i = 0;
    while(!feof(f)){
        char s[10];
        fscanf(f, "%s", s);
        strcpy(stopWords[i],s);
        i++;
    }
    stopWordsNum = i;
    return i;
}

void printResult(){
    JRB ptr;
    jrb_traverse(ptr, dict){
        printf("%s ", ptr->key.s);
        int nodeIdx = ptr->val.i;
        int appearances = countDict[nodeIdx][0];
        for(int i=0; i<appearances+1; i++){
            printf("%d, ", countDict[nodeIdx][i]);
        }
        printf("\n");
    }
}

int main(){
    FILE *f = fopen("vanban.txt", "r");
    dict = make_jrb();
    readProperNouns();
    readStopWord();
    readFile();
    printResult();
    return 0;
}