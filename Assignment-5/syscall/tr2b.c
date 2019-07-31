#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
  //checking if enough arguments were passed
  if(argc != 3)
    {
      fprintf(stderr,"Not enough arguments. \n") ;
      exit(-1) ;
    }

  //getting arguments from command line for both the strings
  char* string1 = argv[1] ;
  char* string2 = argv[2] ;

  //getting size for both the strings
  int size1 = 0;
  for(; string1[size1] != '\0' ; size1 ++) ;
  int size2 = 0;
  for(; string2[size2] != '\0' ; size2 ++) ;

  //checking if the both the strings are the same size 
  if(size1 != size2)
    {
      fprintf(stderr,"Size of both the strings are not same. \n") ;
      exit(-1) ;
    }

  
  int print = 0 ; //acts like a bool value, stores if char printed
  char c = getchar() ; //char stores one character from stdin  


  //while loop gets each char from stdin and prints the                      
  //proper char for that until EOF is reached 
  while (c != EOF)
    {
      //checking if char has a replacement
      for(int i=0 ; i<size1 ; i++ )
	{
	  if (c == string1[i])
	    {
	      putchar(string2[i]);
	      print = 1;
	      break ;
	    }
	}

      //if replacement was not found, print the original char
      if (print == 0)
	putchar(c) ;

      //sets the values to default and gets stdin for next loop
      print = 0	;
      c = getchar() ;
    }
  return 0;
}
