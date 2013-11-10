#include <stdio.h>

char work[1000];
char input[1000];
char abc[27];
int cnt[26];
char fname[20];


/*
  __ _                                 
 / _(_)_  ___ __   __ _ _ __ ___   ___ 
| |_| \ \/ / '_ \ / _` | '_ ` _ \ / _ \
|  _| |>  <| | | | (_| | | | | | |  __/
|_| |_/_/\_\_| |_|\__,_|_| |_| |_|\___|
                                       
fixname - force file name to be no more than 8 alpha chars

*/
fixname(char *name){
char *p = name;
char *f = fname;
int s;
 
if (strrchr(name,'\\')){
	p = (char *) strrchr(name,'\\');
	p++;
}

if (strrchr(name,'/')){
	p = (char*)strrchr(name,'/');
	p++;
}

for (s=0; ((s<8) && (*p)) ; s++){
  if (( (*p >='A') && (*p<='Z')) || ( (*p >='a') && (*p<='z')))
  {
    *f = *p;
	f++;
	p++;
  }
 }
 strcpy(f,".cq");
}


/*
   
  __                
 / _|_ __ ___  __ _ 
| |_| '__/ _ \/ _` |
|  _| | |  __/ (_| |
|_| |_|  \___|\__, |
                 |_|

		 freq - print frequency distribution in puzzle, from
		 first to last.
   
   */
freq(){
  int i,j,big;
  
  big=0;
  printf ("FREQ:");
  for (i=0;i<26;i++){
    if (cnt[i] > big){
      big = cnt[i];
    }
  }
  for (j=big;j>0;j--){
    
    for (i=0;i<26;i++){
      if (cnt[i] == j){
	printf ("%c",'a'+i);
      }
    }
  }
  
  printf ("\n\n");
}

/*
                   _      
 ___  ___ ___   __| | ___ 
/ __|/ __/ _ \ / _` |/ _ \
\__ \ (_| (_) | (_| |  __/
|___/\___\___/ \__,_|\___|
                          

scode - display alphabet/code table
*/
scode(){
  int i,j,big;
  
  big=0;
  printf ("Code:\n");
  
  for (i=0;i<26;i++){
    printf ("%c",'a'+i);
  }
  printf ("\n");
  for (i=0;i<26;i++){
    printf ("%c",abc[i]);
  }
  printf ("\n\n");
}


/*
                          
  ___ ___  __ ___   _____ 
 / __/ __|/ _` \ \ / / _ \
| (__\__ \ (_| |\ V /  __/
 \___|___/\__,_| \_/ \___|
                          

csave save work to file cfile in current directory
*/

csave (char *cfile){
  
  FILE *OUT;
	fixname(cfile);
	OUT = fopen (fname,"wt");
  
  if (OUT){
    printf ("Saving work to %s.\n",cfile);
    fprintf (OUT, "%s\n%s\n",input,abc);
    fclose (OUT);
  }else{
    printf ("Could not save work to %s.\n",fname);
  }
  
}


/*
                         _ 
  ___ _ __ ___  __ _  __| |
 / __| '__/ _ \/ _` |/ _` |
| (__| | |  __/ (_| | (_| |
 \___|_|  \___|\__,_|\__,_|
                           

cread read puzzle from file cfile in current directory
*/

cread (char *cfile){
  
  char tinp[1000],*c,*t,*w;
  int i,mrk=0;
  
  FILE *IN;

  fixname (cfile);
  IN = fopen (fname,"rt");
  
  t=tinp;
  c=input;
  
  if (IN){
    printf ("Recovering work from %s.\n",fname);
    fgets(tinp,sizeof(tinp),IN);
    fgets(abc,sizeof(abc),IN);
    
    for (i=0;i<26;i++){
      cnt[i]=0;
    }
    
    
    fclose (IN);
    for (i=0;i<strlen(tinp);i++){
      t = &tinp[i];
      if ((*t>='a') && (*t<='z')){
	*c = *t;
	mrk = 1;
	c++;
      } else {
	if ((*t>='A') && (*t<='Z')){
	  *c = 'a' + (*t-'A');
	  mrk=1;
	  c++;
	} else {
	  if (mrk == 1){
	    *c = ' ';
	    c++;
	    mrk=0;
	  }
	}
      }
    }
    
    *c = '\0';
    c=input;
    
    for (i = 0; i<=strlen(c);i++){
      if ((c[i]>='a') && (c[i]<='z')){
	cnt[c[i]-'a']++;
      }
    }
    
    
    printf ("\nINPUT :%s\n",input);
    
    freq();
    
    trans();
    
    
  }else{
    printf ("Could not read work in %s.\n",cfile);
  }
  
}


/*
            _   _       
  __ _  ___| |_(_)_ __  
 / _` |/ _ \ __| | '_ \ 
| (_| |  __/ |_| | | | |
 \__, |\___|\__|_|_| |_|
 |___/                  

getin - ask for new code from user

*/

getin(){
  char tinp[1000],*c,*t,*w;
  int i,mrk=0;
  
  printf ("Code String? ");
  gets(tinp);
  
  t=tinp;
  c=input;
  for (i=0;i<26;i++){
    cnt[i]=0;
    abc[i]='.';
  }
  
  abc[26]=0;
  
  for (i=0;i<strlen(tinp);i++){
    t = &tinp[i];
    if ((*t>='a') && (*t<='z')){
      *c = *t;
      mrk = 1;
      c++;
    } else {
      if ((*t>='A') && (*t<='Z')){
	*c = 'a' + (*t-'A');
	mrk=1;
	c++;
      } else {
	if (mrk == 1){
	  *c = ' ';
	  c++;
	  mrk=0;
	}
      }
    }
  }
  
  *c = '\0';
  c=input;
  
  for (i = 0; i<=strlen(c);i++){
    if ((c[i]>='a') && (c[i]<='z')){
      cnt[c[i]-'a']++;
    }
  }
  
  
  printf ("\nINPUT :%s\n",input);
  
  freq();
  
  trans();
  
}


/*
     _               _      
  __| | ___ ___   __| | ___ 
 / _` |/ __/ _ \ / _` |/ _ \
| (_| | (_| (_) | (_| |  __/
 \__,_|\___\___/ \__,_|\___|
                            

dcode - update code table according to user input
        letter "a" code letter equals crypt "b".
	Clear letter by sending in "aa" pair.

	rejects already used letters. (that is if 
	you've said q = c, then you can't make j = c

*/

dcode(char *cd) {
  
  char a,b;
  
  if (strlen(cd) != 2) {
    return;
  }
  
  a=*cd++;
  b=*cd;
  
  if ( (a >='A') && (a<='Z')){
    a = 'a' + a - 'A';
  }
  
  if ( (b >='A') && (b<='Z')){
    b = 'a' + b - 'A';
  }
  if ( !((a >='a') && (a<='z')) ||!((b >='a') && (b<='z'))) {
    return;
  }
  
  
  if (a == b){
    abc[a-'a']='.';
    printf ("resetting %c\n",a);
  }else{
    
    if (!strchr(abc,b)){
      abc[a-'a']=b;
      printf ("%c<-%c\n",a,b);
    }else{
      printf ("No: %c already in code.\n",b);
    }
  }
  
}



/*
 _                       
| |_ _ __ __ _ _ __  ___ 
| __| '__/ _` | '_ \/ __|
| |_| | | (_| | | | \__ \
 \__|_|  \__,_|_| |_|___/
                         

trans - use current code table to display translation so far
*/

trans(){
  int i;
  char *c = input;
  
  printf ("PLAIN :");
  for (i=0;i<strlen(input);i++){
    if ((c[i]>='a') && (c[i]<='z')){
      printf ("%c",abc[c[i]-'a']);
    }else{
      printf (" ");
    }
  }
  printf ("\n\n");
}



/*
                 _       
 _ __ ___   __ _(_)_ __  
| '_ ` _ \ / _` | | '_ \ 
| | | | | | (_| | | | | |
|_| |_| |_|\__,_|_|_| |_|
                         

main 
*/

main (int argc, char *argv[]) {
  
  char code[200];
  
  /*start*/
  
  printf ("\n\nJoel's Good Enough CryptoQuip tool.\n('?' for usage)\n\n ");
  if (argc>1){
    cread (argv[1]);
  }else{
    getin();
  }
  while (1){
    printf ("\n? ");    
    scanf ("%s",code);
    /*gets(code);*/
    if (strlen(code) == 2){
      dcode(code);
      printf ("\nINPUT :%s\n",input);
      trans();
    }else{
      
      if (!strcmp ("quit",code)) {
	printf ("\n\nThanks for trying Good Enough CryptoQuip tool.\n");
	printf (" Joel Peter Anderson / 1998 \n\tvisit the UTA project at http://members.aol.com/jpklingon/uta\n\n");
	exit(13);
      }
      
      if (!strcmp ("new",code)) {
	getin();
      }
      
      if (!strcmp ("code",code)) {
	scode();
      }
      
      if (!strcmp ("save",code)) {
	scanf ("%s",code);	
	csave (code);
      }
      
      if (!strcmp ("read",code)) {
	scanf ("%s",code);	
	cread (code);
      }
      
      if (!strcmp ("freq",code)) {
	freq();
      }
      
      if (!strcmp ("?",code)) {
	printf ("\n");
	printf ("CQ - simple cryptoquip solver\n");
	printf ("   new   - reenter code\n");
	printf ("   reset - clear code\n");
	printf ("   freq  - show letters in order of use\n");
	printf ("   quit  - quit program\n");
	printf ("   ab    - replace all occurences of a with b\n");
	printf ("   aa    - clear setting for a\n");
	printf ("   code  - show translation table\n");
	printf ("   save file - save work to a file\n");
	printf ("   read file - read work from a file\n");
	printf ("   ?     - this listing\n");
	printf ("\n");
      }
      
      if (!strcmp ("reset",code)) {
	int i;
	for (i=0;i<26;i++){
	  abc[i]='.';
	}
	printf ("INPUT :%s\n",input);
	trans();
	
      }
      
      
    }
  }
}
