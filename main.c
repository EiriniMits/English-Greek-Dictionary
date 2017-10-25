#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define d(i,j) dd[(i) * (m+2) + (j) ]
#define min(x,y) ((x) < (y) ? (x) : (y))
#define min3(a,b,c) ((a)< (b) ? min((a),(c)) : min((b),(c)))
#define min4(a,b,c,d) ((a)< (b) ? min3((a),(c),(d)) : min3((b),(c),(d)))
void add(char *g,char *e);
void change(char *g,char *e,char *l);
void removeline(char *g);
void transword(char *g);
void transline(char *g);
int levenshtein(char *s, char* t, int n, int m);
void minimun(char *g);
void copy();
void save();

/*
 * @author Eirini Mitsopoulou
 */


int main(void)
{
    int choice;
    char choice2[2];
    char *g,*e,*l;
    g= (char *)calloc(20,sizeof(char)); //Dunamikh desmeush mnhmhs
    e= (char *)calloc(20,sizeof(char));
    l= (char *)calloc(200,sizeof(char));
    copy(); // dhmiourgei arxeio replical.txt opou apothikeuei to lejiko kai ekei tha ginoun oi opoies allages
    printf("         -- Menu --            \n");
    printf("1. Insert New Term in the Dictionary\n");
    printf("2. Edit term\n");
    printf("3. Delete term\n");
    printf("4. Translate Word\n");
    printf("5. Translate sentence\n");
    printf("6. Exit\n\n");
    printf("Enter your choice (1-6)\n");
    scanf("%d",&choice);
    while(choice !=6){
        if(choice == 1){
                printf("Give a Greek Word:\n");
                scanf("%s",g);
                printf("Give an English Word:\n");
                scanf("%s",e);
                add(g,e); //pros8etei 1 le3h me thn metafrash ths
        }
        else if(choice == 2){
                printf("Give an English or a Greek Word to Update Term:\n");
                scanf("%s",g);
                printf("Give English Word:\n");
                scanf("%s",e);
                printf("Give Greek Word:\n");
                scanf("%s",l);
                change(g,e,l); // tropopoiei th le3h
        }
        else if(choice == 3){
                printf("Give an English or a Greek Word to Delete Term:\n");
                scanf("%s",g);
                removeline(g); //diagrafei th le3h
        }
        else if(choice == 4){
                printf("Give an English or a Greek Word\n");
                scanf("%s",g);
                transword(g); // metafrazei th le3h
        }
        else if(choice == 5){
                printf("Give an English or a Greek Sentence:\n");
                scanf("%s",l);
                transline(l); //metafrazei th frash
        }
        printf("         -- Menu --            \n");
        printf("1. Insert New Term in the Dictionary\n");
        printf("2. Edit term\n");
        printf("3. Delete term\n");
        printf("4. Translate Word\n");
        printf("5. Translate sentence\n");
        printf("6. Exit\n\n");
        printf("Enter your choice (1-6)\n");
        scanf("%d",&choice);
    }
     printf("Do you want to save the changes? ('Y'/'N')");
     scanf("%s",choice2);
     if(choice2[0] == 'y' || choice2[0] == 'Y'){
                save(); // apo8hkeuei tis allages sto dictionary.txt
                printf("Changes saved to the dictionary successfully!\n");
     }
     printf("   -- Telos Programmatos --   ");

}

void copy(){
    FILE *fp,*fp1;
    char *line;
    line = (char *)calloc(20,sizeof(char));
    fp = fopen("dictionary.txt", "r");
    if(fp == NULL)
        printf("dictionary.txt file does not exist.");
    else
    {
        fp1 = fopen("replical.txt", "w");
            while (fgets(line, 80, fp) != NULL){ // mexri to keimeno na teliwsei
                        fscanf(fp,"%s",line); //diamazei thn le3h se kathe grammh
                        fputc('\n',fp1);
                        fputs(line,fp1); // thn antigrafei sto allo arxeio
                }
                fclose(fp1);
    }
       fclose(fp);
}

void save(){
    FILE *fp,*fp1;
    char *line;
    line = (char *)calloc(20,sizeof(char));
    fp = fopen("replical.txt", "r");
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {
        fp1 = fopen("dictionary.txt", "w");
            while (fgets(line, 80, fp) != NULL){
                        fscanf(fp,"%s",line);
                        fputc('\n',fp1);
                        fputs(line,fp1);
                }
                fclose(fp1);
    }
       fclose(fp);
       remove("replical.txt");
}


void add(char *g,char *e){
    FILE *fp;
    char *line;
    line = (char *)calloc(20,sizeof(char));
    fp = fopen("replical.txt","r");
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {
        while (!feof(fp)) { // mexri na teliwsei to keimeno to arxeiou
            fscanf(fp,"%s",line);
                if(strcmp(g,line)==0){ // an h lejh pou eisagoume einai idia me kapoia apo to le3iko
                    printf("The word %s already exists in the dictionary\n",line);
                    fclose (fp);
                    return;
                }
        }
        fclose (fp);
    }
    fp = fopen("replical.txt","a");
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {//grafei tis le3eis sto telos tou arxeiou
        fputc('\n',fp);
        fputs(g,fp);
        fputc('\n',fp);
        fputs(e,fp);
        fclose (fp);
    }
    printf("The word added in the dictionary successfully! \n");
}


void minimun(char *g){
    FILE *fp;
    char *line;
    int k,min=100,i=1,l,m=0,n=0,j;
    line = (char *)calloc(20,sizeof(char));
    fp = fopen("replical.txt","r");
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {
        while (!feof(fp)) {
            fscanf(fp,"%s",line);
                    k=levenshtein(g,line,strlen(g),strlen(line)); //psaxnei poses einai oi grammatikes diafores meta3u twn le3ewn
                    if(k<min ){ // psaxnei ton min ari8mo twn diaforwn
                        min = k;
                        l = i; //apo8hkeuei th grammh pou brike th le3h me to min ari8mo twn diaforwn
                    }
                    i++;
        }
    }
    fclose (fp);
    i=1;
    j=1;
    fp = fopen("replical.txt","r");
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {
        while (!feof(fp)) {
            fscanf(fp,"%s",line);
                    k=levenshtein(g,line,strlen(g),strlen(line));
                    if(k==min && j!=l && i==1 ){ // briskei th deuterh lejh pou exei to min ari8mo twn diaforwn
                        n = j;
                        i++;
                    }
                    if(k==min && i==2 && j!=n ){// briskei th trith lejh pou exei to min ari8mo twn diaforwn
                        m = j;
                        i++;
                    }
                    if(i==3)
                        break;
                    j++;
        }
    }
    fclose (fp);
    i=1;
    fp = fopen("replical.txt","r");
    printf("Maybe the word is:\n");
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {// emfanizei tis le3eis
        while (!feof(fp)) {
            fscanf(fp,"%s",line);
            if(i == l)
                printf("%s\n",line);
            if(i == n)
                printf("%s\n",line);
            if(i == m)
                printf("%s\n",line);
            i++;
        }
        fclose (fp);
    }

}


int levenshtein(char *s, char* t, int n, int m){
    int *dd, *DA;
    int i, j, cost, k, i1,j1,DB;

    DA = (int*) malloc( 256 * sizeof(int));
    dd = (int*) malloc ((n+2)*(m+2)*sizeof(int));

    d(0,0) = n + m;
    for(i = 0; i < n+1; i++) {
      d(i+1,1) = i ;
      d(i+1,0) = n + m;
    }
    for(j = 0; j<m+1; j++) {
      d(1,j+1) = j ;
      d(0,j+1) = n + m;
    }
    for(k = 0; k < 256; k++) DA[k] = 0;
    for(i = 1; i< n+1; i++) {
      DB = 0;
      for(j = 1; j< m+1; j++) {
        i1 = DA[t[j-1]];
        j1 = DB;
        cost = ((s[i-1]==t[j-1])?0:1);
        if(cost==0) DB = j;
        d(i+1,j+1) =
          min4(d(i,j)+cost,
              d(i+1,j) + 1,
              d(i,j+1)+1,
              d(i1,j1) + (i-i1-1) + 1 + (j-j1-1));
      }
      DA[s[i-1]] = i;
    }
    cost = d(n+1,m+1); //briskei to poso twn grammatikwn diaforwn twn le3ewn
    free(dd);
    return cost;
}

void change(char *g,char *e,char *l){
    FILE *fp, *fp1;
    char *line;
    line = (char *)calloc(20,sizeof(char));
    int i=1,delete_line=0;

    fp = fopen("replical.txt", "r");
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {
        fp1 = fopen("replical2.txt", "w"); //dhmiourgei ena boh8htiko arxeio
         while (fgets(line, 80, fp) != NULL) {
            fscanf(fp,"%s",line);
                if(strcmp(g,line)==0){ //otan brei h le3h mesa sto le3iko
                        fputc('\n',fp1);
                        fputs(e,fp1); // antigrafei sto boh8htiko arxeio thn tropopoihmenh le3h
                        delete_line = i; // swzei h seira pou thn brike
                }
                else{
                        fputc('\n',fp1);
                        fputs(line,fp1); //antigrafei sto boh8htiko arxeio kai to upoloipo le3iko
                }
                i++;
        }
        if( delete_line == 0){//an h le3h den uparxei sto le3iko
            printf("The word you want to delete doesn't exist in the dictionary\n");
            minimun(g); //emfanizei ths 3 pio kontines le3eis grammatika sth le3h pou bothike
            return;
        }
        fclose (fp1);
    }
    fclose(fp);
    if(delete_line % 2 == 0) // an h le3h einai agglikh
        delete_line = delete_line -1; //swzei h seira pou einai h metafrash ths
    else // an h le3h einai ellhnikh
        delete_line = delete_line +1;
    fp = fopen("replical.txt", "w");
    i=1;
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {
        fp1 = fopen("replical2.txt", "r");
            while (fgets(line, 80, fp1) != NULL){
                if(i==delete_line){ // otan brei th seira ths metafrashs ths
                    fputc('\n',fp);
                    fputs(l,fp); //antigrafei sto arxiko arxeio thn tropoihmenh metafrash ths le3hs
                    i++;
                }
                else{
                        fscanf(fp1,"%s",line);
                        fputc('\n',fp);
                        fputs(line,fp);
                        i++;
                }
            }
       fclose(fp1);
       remove("replical2.txt");// diagrafei to boh8htiko arxeio
    }
    fclose(fp);
    printf("The word edited successfully!\n");
}


void removeline(char *g){
    FILE *fp, *fp1;
    char *line;
    line = (char *)calloc(20,sizeof(char));
    int i=1,delete_line=0;

    fp = fopen("replical.txt", "r");
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {
        fp1 = fopen("replical2.txt", "w");
         while (fgets(line, 80, fp) != NULL) {
            fscanf(fp,"%s",line);
                if(strcmp(g,line)==0){
                        delete_line = i; //briskei th seira ths le3hs pou prepei na diagrafei
                }
                else{
                        fputc('\n',fp1);
                        fputs(line,fp1); //antigrafei sto bohthitiko arxeio olo to le3iko ektos apo thn le3i pou prepei na diagrafei
                }
                i++;
        }
        if( delete_line == 0){ //an h le3h den uparxei
            printf("The word you want to delete doesn't exist in the dictionary\n");
            minimun(g);
            return;
        }
        fclose (fp1);
    }
    fclose(fp);
    if(delete_line % 2 == 0){ //briskei h grammh pou einai h metafrash ths le3hs pros diagrafh
        delete_line = delete_line -1;
    }
    fp = fopen("replical.txt", "w");
    i=1;
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {
        fp1 = fopen("replical2.txt", "r");
            while (fgets(line, 80, fp1) != NULL){
                if(i==delete_line){
                    i++;
                }
                else{
                        fscanf(fp1,"%s",line);
                        fputc('\n',fp);
                        fputs(line,fp); //antigrafei sto arxiko arxeio olo to le3iko ektos apo thn metafrasmenh le3i pou prepei na diagrafei
                        i++;
                }
            }
       fclose(fp1);
       remove("replical2.txt");
    }
    fclose(fp);
    printf("H lejh afairefike me epituxia! \n");
}


void transword(char *g){
    FILE *fp;
    char *line;
    line = (char *)calloc(20,sizeof(char));
    int i=1,delete_line=0;

    fp = fopen("replical.txt", "r");
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {
         while (fgets(line, 80, fp) != NULL) {
            fscanf(fp,"%s",line);
                if(strcmp(g,line)==0){
                        delete_line = i; // briskw th grammh pou einai h le3h pou thelw na metagrasw
                }
                i++;
        }
        if( delete_line == 0){
            printf("The word you want to translate doesn't exist in the dictionary\n");
            minimun(g);
            return;
        }
    }
    fclose(fp);
    if(delete_line % 2 == 0)//briskw th grammh pou einai h metafrash ths
        delete_line = delete_line -1;
    else
        delete_line = delete_line +1;
    fp = fopen("replical.txt", "r");
    i=0;
    if(fp == NULL)
        printf("replical.txt file does not exist.");
    else
    {
            while (fgets(line, 80, fp) != NULL){
                if(i==delete_line)//emfanizw thn metafrash
                    printf("The translation of: %s is: %s\n", g,line);
                i++;
            }
    }
    fclose(fp);

}

void transline(char *g){
  char * pch;
  FILE *fp;
  char *line;
  line = (char *)calloc(20,sizeof(char));
  int i=1,delete_line=0;
  pch = strtok(g," "); //kanw split th frash, th xwrizw se le3eis

  while (pch != NULL) {//pernw le3h le3h th frash kai th metafrazw me ton idio tropo opws kai sthn sunarthsh transword
            fp = fopen("replical.txt", "r");
            if(fp == NULL)
                printf("replical.txt file does not exist.");
            else
            {
                 while (fgets(line, 80, fp) != NULL) {
                    fscanf(fp,"%s",line);
                        if(strcmp(pch,line)==0){
                                delete_line = i;
                        }
                        i++;
                }
                if( delete_line == 0){
                    printf("The word %s doesn't exist in the dictionary\n",pch);
                    minimun(g);
                    return;
                }
            }
            fclose(fp);
            if(delete_line % 2 == 0)
                delete_line = delete_line -1;
            else
                delete_line = delete_line +1;
            fp = fopen("replical.txt", "r");
            i=0;
            if(fp == NULL)
                printf("replical.txt file does not exist.");
            else
            {
                    while (fgets(line, 80, fp) != NULL){
                        if(i==delete_line)
                            printf("%s",line);
                        i++;
                    }
            }
            fclose(fp);
            pch = strtok (NULL, " ");
  }
}
