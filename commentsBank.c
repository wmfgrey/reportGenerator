/******************************* commentsBank.c *****************************************
*****************************************************************************************
 
  DESCRIPTION:	 1) Give pupils mark for effort, behaviour, level attainment
		 and so on. 
		 2) Generate reports for each pupil based on marks given.  Randomly 
		selects comments from each category. 
			 						
  AUTHOR(S):	 William Grey
		 w.m.f.grey@gmail.com

  DEVELOPMENT:   First written: 24th September 2012
   
  REQUIREMENTS:	 1) List of students: <first name> <surname> <gender> 
       
    						   
  TO COMPILE:    gcc commentsBank.c -o commentsBank -Wall -lm
  
  EXAMPLE:  	 ./commentsBank -grades classList.txt classListOut.txt < intest.txt
                 ./commentsBank -reports classListOut.txt bank.txt reports.txt

Pronoun:

  ^ Name
  ~ he /she
  $ He / She
  + him / her
  * his / her
			 				
*****************************************************************************************
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define VERSION "0.1"
#define DATE    "24th September 2012"
#define MAX_NAME_LENGTH 1000
#define MAX_PUPILS_PER_CLASS 100
#define MAX_LINE_LENGTH 2000
#define MAX_WORD_LENGTH 100
#define MAX_NUM_COMMENTS 1000
#define MAX_NUM_CRITERIA 13
#define NUM_GRADES 5

typedef struct {
 char classfile[MAX_NAME_LENGTH];
 char gradesfile[MAX_NAME_LENGTH];
 char reportfile[MAX_NAME_LENGTH];
 char bankfile[MAX_NAME_LENGTH];
 int rflag;
 int gflag;
 int num_criteria;
} clparse ;


void read_clinput(int, char **, clparse *);
int read_class_list (clparse *);
int gen_report (clparse *);
FILE *openfile(char *, char *);
int rnd(int);
char *pronoun_gender(char *, char *, char *);
char *str_replace(char *, char *, char *);

int main(int argc, char *argv[])
{

 clparse clinput;
 
/*****************************************
   Reading in user-defined variables
   from the command line and performing 
   error checking.
 ******************************************/
 
 read_clinput(argc, argv, &clinput);

/*****************************************
   Reading in data from class lists.
 ******************************************/
  
 if(clinput.gflag == 1)
  read_class_list(&clinput); 
  
/*****************************************
   Generating reports
 ******************************************/

 if(clinput.rflag == 1)
  gen_report(&clinput); 
 
 return (EXIT_SUCCESS);

}

/*********************************************************************************
*********************************************************************************/

/* returns a random number between 1 and a specified maximum number */

int rnd( int max ) {
 
 return (rand() % max) + 1;

} 

/*********************************************************************************
*********************************************************************************/

/* Open files in preparation for reading or writing */

FILE *openfile(char *filename, char *rw)
{
 
 FILE *fp;
 
 if ( !strcmp(rw, "r") ){
 
  fp = fopen(filename, "r");
  if ( fp == NULL ){
   fprintf( stderr, "Error opening file %s\n", filename);
   exit(EXIT_FAILURE); 
  }
  
 }
 
 else if ( !strcmp(rw, "a") ){
 
  fp = fopen(filename, "a");
  if ( fp == NULL ){
   fprintf( stderr, "Error creating %s\n", filename);
   exit(EXIT_FAILURE); 
  }
 
 }
 
 return fp;

}

/*********************************************************************************
*********************************************************************************/

/* Read in class lists and issue grades */

int read_class_list (clparse *clinput)
{

 FILE *fclass, *fgrades;
 char pupil_record[MAX_LINE_LENGTH];
 char surname[MAX_NAME_LENGTH];
 char firstname[MAX_NAME_LENGTH];
 char gender[MAX_NAME_LENGTH];
 int i;
 int marks[MAX_NUM_CRITERIA]; 

 char *grades[]={"effort", 
                 "attainment",
                 "progress", 
                 "level", 
                 "behaviour",
                 "punctuality",
                 "organisation",
                 "independent_enquirer",
                 "creative_thinker",
                 "reflective_learner",
                 "team_worker",
                 "self_manager",
                 "effective_participant"};

 fclass = openfile(clinput->classfile, "r");
 fgrades = openfile(clinput->gradesfile, "a");

 while (fgets(pupil_record, MAX_LINE_LENGTH, fclass) != NULL){
  sscanf(pupil_record,"%s %s %s",firstname, surname, gender); 
  fprintf(stderr,"%s %s\n",firstname, surname);
  
  for(i=0;i<clinput->num_criteria;i++){
   fprintf(stderr,"%s= ",grades[i]);
   scanf("%d",&marks[i]);
  }

  fprintf(stderr,"\n");
  
  fprintf(fgrades,"%s %s %s",firstname, surname, gender);
  for(i=0;i<clinput->num_criteria;i++) fprintf(fgrades," %d", marks[i]);
  fprintf(fgrades,"\n");
 
 }
 	  
 fclose(fclass);
 fclose(fgrades);
 return (EXIT_SUCCESS);

}


/*********************************************************************************
*********************************************************************************/

/* Generate reports based on grades */

int gen_report (clparse *clinput)
{
 
 FILE *fgrades, *freport, *fbank;
 char bank_record[MAX_LINE_LENGTH];
 char pupil_record[MAX_LINE_LENGTH];
 char comment_all[MAX_LINE_LENGTH][MAX_NUM_COMMENTS];
 char hash[1], criteria[MAX_LINE_LENGTH];
 char *pch;
 int grade, grade_all[MAX_NUM_COMMENTS], criteria_all[MAX_NUM_COMMENTS];
 int i, j, k, total_num_comments, selected_comment;
 char surname[MAX_NAME_LENGTH];
 char firstname[MAX_NAME_LENGTH];
 char gender[MAX_NAME_LENGTH];
 int marks[MAX_NUM_CRITERIA];
 int comments_num[NUM_GRADES+1][MAX_NUM_CRITERIA+1];
 int comment_index[NUM_GRADES+1][MAX_NUM_CRITERIA+1];
 char *dest;
 char str[MAX_LINE_LENGTH];
 char *p;
  
 fgrades = openfile(clinput->gradesfile, "r");
 freport = openfile(clinput->reportfile, "a");
 fbank = openfile(clinput->bankfile, "r");
 
 /* Read in comments bank*/
 
 i=0;
 
 
 
 while (fgets(bank_record, MAX_LINE_LENGTH, fbank) != NULL){
  if (bank_record[0]!='#'){
   strcpy(comment_all[i],bank_record);
   grade_all[i]=grade;

   if (!strncasecmp(criteria,"effort",4)) criteria_all[i]=1;  
   else if (!strncasecmp(criteria,"attainment",4)) criteria_all[i]=2;
   else if (!strncasecmp(criteria,"progress",4)) criteria_all[i]=3;
   else if (!strncasecmp(criteria,"level",4)) criteria_all[i]=4;
   else if (!strncasecmp(criteria,"behaviour",4)) criteria_all[i]=5;
   else if (!strncasecmp(criteria,"punctuality",4)) criteria_all[i]=6;
   else if (!strncasecmp(criteria,"organisation",4)) criteria_all[i]=7;
   else if (!strncasecmp(criteria,"independent_enquirer",4)) criteria_all[i]=8;
   else if (!strncasecmp(criteria,"creative_thinker",4)) criteria_all[i]=9;
   else if (!strncasecmp(criteria,"reflective_learner",4)) criteria_all[i]=10;
   else if (!strncasecmp(criteria,"team_worker",4)) criteria_all[i]=11;
   else if (!strncasecmp(criteria,"self_manager",4)) criteria_all[i]=12;
   else if (!strncasecmp(criteria,"effective_participant",4)) criteria_all[i]=13;

  /*printf("%d %s %d %s",grade_all[i], criteria, criteria_all[i], comment_all[i]); */
   i++;  
  }
  else{
   sscanf(bank_record,"%s %s %d",hash, criteria ,&grade); 
  /* fprintf(stderr,"%s %d \n", criteria, grade); */
  }    
 }
 
 /* calculate how many comments there are per
    grade and per criteria.  This is needed for 
    input into the random function.  */

 total_num_comments=i;
 
 for (i=0; i<NUM_GRADES+1; i++){ 
  for (j=0; j<clinput->num_criteria+1; j++){
    comments_num[i][j]=0;
    comment_index[i][j]=-999;
  }
 }

 for (k=0;k<total_num_comments;k++){
  comments_num[grade_all[k]][criteria_all[k]]++; 
  if (comment_index[grade_all[k]][criteria_all[k]] == -999)
    comment_index[grade_all[k]][criteria_all[k]]=k;
 }
 
 
 /*for (i=0; i<NUM_GRADES+1; i++)
  for (j=0; j<clinput->num_criteria+1; j++)
    fprintf(stdout,"%d %d %d %d\n",i,j,comment_index[i][j], comments_num[i][j]); 
 
  fprintf(stdout,"comments total: %d\n",total_num_comments); */  
  
 
 

 while (fgets(pupil_record, MAX_LINE_LENGTH, fgrades) != NULL){
  
 /* Read in pupil grades */
 
 pch = strtok (pupil_record," \t");
  i=0;
  j=0;
  while (pch != NULL)
  {
    if (i==0) strcpy(firstname,pch);
    if (i==1) strcpy(surname,pch);
    if (i==2) strcpy(gender,pch);

    if (i==j+3){
     marks[j]=atoi(pch);
     j++;
    }

    /* printf ("%s %s %s %d\n",pch, firstname, surname, marks[0]); */

    pch = strtok (NULL, " \t");
    i++; 
  }
  
 

  fprintf(freport,"%s %s %s",firstname, surname, gender);
  for(k=0;k<clinput->num_criteria;k++) fprintf(freport," %d", marks[k]);
  fprintf(freport,"\n");

  /* look at pupils grades then allocate 
     random but relevant comment */
  
  
  for (j=0; j<clinput->num_criteria; j++){
  
   if( comments_num[marks[j]][j+1] != 0 ){
    
    selected_comment=rnd(comments_num[marks[j]][j+1]); 
    /*fprintf(stdout,"%d %d %d %d\n",j,marks[j],comments_num[marks[j]][j+1],selected_comment);*/
   
   
    strcpy(str,comment_all[comment_index[marks[j]][j+1]+selected_comment-1]);
   /* fprintf(stdout,"%s ",str); */
   
    dest=pronoun_gender(gender,firstname,str);
     
     p = strchr(dest,'\n');
    *p = '\0';
     
    fprintf(freport,"%s ",dest);
     
    /* fputs(dest,freport); */
    
   }
      
  }
  

  fprintf(freport,"\n\n");
  
 }
 
 

 fclose(fgrades);
 fclose(freport);
 fclose(fbank);
  

 return (EXIT_SUCCESS);

}

/*********************************************************************************
*********************************************************************************/

 /* Reading in user-defined variables
   from the command line and calculating
   derived variables. */

void read_clinput(int argc, char **argv, clparse *clinput)
{

 int print_usage=0;
 
 /* Set up default parameters */
  
 clinput->rflag=0;
 clinput->gflag=0;
 clinput->num_criteria=7;
 
 if (argc < 4) print_usage=1;
 
 else if( (!strncasecmp(argv[ 1 ], "-grades",   2) || 
      !strncasecmp(argv[ 1 ], "--grades",  3)) && (argc < 4)) print_usage=1;
 
 else if( (!strncasecmp(argv[ 1 ], "-reports",   2) || 
      !strncasecmp(argv[ 1 ], "--reports",  3)) && (argc < 5)) print_usage=1;
 
 /*else if (strncasecmp(argv[ 1 ], "-reports",   2) == 0 ||
          strncasecmp(argv[ 1 ], "--reports",  3)  == 0||
          strncasecmp(argv[ 1 ], "-grades",   2)  == 0||
          strncasecmp(argv[ 1 ], "--grades",  3) == 0) print_usage=1;*/

 if (print_usage) {
  fprintf(stderr,"Usage: %s [options]\n",argv[0]);
  fprintf(stderr,"options:\n\n");
  fprintf(stderr," -grades  <class list file (in)> <grade list file (out)> [num_criteria]\n");  	
  fprintf(stderr," -reports <grade list file (in)> <comments bank file (in)>  <report file out> [num_criteria]\n");
  exit(EXIT_FAILURE);
 }  

 if( !strncasecmp(argv[ 1 ], "-grades",   2) || 
     !strncasecmp(argv[ 1 ], "--grades",  3)) {
    clinput->gflag=1;
    strcpy(clinput->classfile, argv[ 2 ]);
    strcpy(clinput->gradesfile, argv[ 3 ]);
    if (argc==5) clinput->num_criteria=atoi(argv[ 4 ]);
    }

if( !strncasecmp(argv[ 1 ], "-reports",   2) || 
     !strncasecmp(argv[ 1 ], "--reports",  3)) {
    clinput->rflag=1;
    strcpy(clinput->gradesfile, argv[ 2 ]);
    strcpy(clinput->bankfile, argv[ 3 ]);
    strcpy(clinput->reportfile, argv[ 4 ]);
    if (argc==6) clinput->num_criteria=atoi(argv[ 5 ]);
    }

}

/*********************************************************************************
*********************************************************************************/

/* Applies the correct 
    pronoun based on gender. */

char *pronoun_gender(char *gender, char *name, char *str)
{
  
  char *dest;
  
 dest=str_replace(str, " ", " ");
  
 if ( strstr(str, "$name$") !=NULL ) dest=str_replace(str, "$name$", name);
  
  if((strcmp(gender,"M")==0) && (strstr(dest,"$shehe$")!=NULL)) 
   strcpy(dest,str_replace(dest, "$shehe$", "he"));   
  else if((strcmp(gender,"F")==0) && (strstr(dest,"$shehe$")!=NULL)) 
    strcpy(dest,str_replace(dest, "$shehe$", "she"));
  
  if((strcmp(gender,"M")==0) && (strstr(dest,"$SheHe$")!=NULL)) 
   strcpy(dest,str_replace(dest, "$SheHe$", "He"));   
  else if((strcmp(gender,"F")==0) && (strstr(dest,"$SheHe$")!=NULL)) 
    strcpy(dest,str_replace(dest, "$SheHe$", "She"));

  if((strcmp(gender,"M")==0) && (strstr(dest,"$herhim$")!=NULL)) 
   strcpy(dest,str_replace(dest, "$herhim$", "him"));   
  else if((strcmp(gender,"F")==0) && (strstr(dest,"$herhim$")!=NULL)) 
    strcpy(dest,str_replace(dest, "$herhim$", "her")); 
  
  if((strcmp(gender,"M")==0) && (strstr(dest,"$herhis$")!=NULL)) 
   strcpy(dest,str_replace(dest, "$herhis$", "his"));   
  else if((strcmp(gender,"F")==0) && (strstr(dest,"$herhis$")!=NULL)) 
    strcpy(dest,str_replace(dest, "$herhis$", "her")); 

 if((strcmp(gender,"M")==0) && (strstr(dest,"$HerHis$")!=NULL)) 
   strcpy(dest,str_replace(dest, "$HerHis$", "His"));   
  else if((strcmp(gender,"F")==0) && (strstr(dest,"$HerHis$")!=NULL)) 
    strcpy(dest,str_replace(dest, "$HerHis$", "Her")); 

  /*  fprintf(stdout,"%s ",dest); */

  return dest;

}

/*********************************************************************************
*********************************************************************************/

/* Routine for replace part of a string is taken from:
http://stackoverflow.com/questions/779875/what-is-the-function-to-replace-string-in-c 
*/

char *str_replace(char *orig, char *rep, char *with) {
    char *result; 
    char *ins;    
    char *tmp;   
    int len_rep;  
    int len_with; 
    int len_front; 
    int count;    

    if (!orig)
        return NULL;
    if (!rep || !(len_rep = strlen(rep)))
        return NULL;
    if (!(ins = strstr(orig, rep))) 
        return NULL;
    if (!with)
        with = "";
    len_with = strlen(with);

    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = (tmp + len_rep);
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; 
    }
    strcpy(tmp, orig);
    return result;
}

