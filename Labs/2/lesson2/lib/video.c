#include "io.c"
#include "kbd.c"

int i,index1,index2;



//scrolling
void scrollDown(){
  char* vidmem = (char *) 0xb8000;
  int linesToScroll,indexTMP;
  index1=0;

  if(i>=3840){
    linesToScroll=(i-4000)/160+1;
    index2=linesToScroll*160;
    i=3840;
    for(;index2<=4000;index1++,index2++){
      vidmem[index1]=vidmem[index2];
    }
    for(;index1<=4000;index1++){
      vidmem[index1]=0x00;
      vidmem[++index1]=" ";
      
    }
  }
}

//print a char.
void putc(char oneChar){
  char* vidmem = (char *) 0xb8000;
  if (!i){
    i=0;
  };
  if(oneChar=='\177'){
    i-=2;
    vidmem[i]=" ";
    i++;
    vidmem[i]=0x00;
    i--;
  }
  
  else{
    vidmem[i]=oneChar;
    i++;
    vidmem[i]=0x7;
    i++;
  }
};

//Prints a string.Based on putc function.
void puts(char *string){
  int j;

  j=0;
  while (string[j]){
    putc(string[j]);
    j++;
  };
  NewLine();
  scrollDown();
  return;
};

//Pass on to a new line
void NewLine(){
 
 i+=160-i%160;
};

void gets(char *myString){
  //char myString[256];
  char oneChar;
  int k;
  k=0;

  oneChar=getchar();
  while(oneChar!='\n'){
    putc(oneChar);
    if (oneChar=='\177'){
      myString[--k]='\0';
     //k++;
    }
    else{
      myString[k]=oneChar;
      k++;  
    }
    
    oneChar=getchar();
  }
  myString[k]='\0';
  NewLine();
  scrollDown();
};

/****************************************/
void clrscr(){
  char* vidmem = (char *) 0xb8000;
  while(i>0){
    vidmem[i]=" ";
    i--;
    vidmem[i]=0x00;
    i--;
  }
  i=0;
};

int strcmp(char* str1, char* str2){
  int i,j;
  i=0;j=0;
  while(str1[i] || str2[j]){
    if (str1[i]!=str2[j]){
      return 0;
    }
    i++;j++;
  }
  return 1;
};
/*************************************/

void commandPrompt(){

    char* vidmem = (char *) 0xb8000;
    char myString[256];


    puts("Your order, Master:");
    gets(myString);
    if (strcmp(myString,"clrscr")){
      clrscr();
    }
    else{
      puts("You typed:");
      puts(myString);
      NewLine();
      scrollDown();
    }
};