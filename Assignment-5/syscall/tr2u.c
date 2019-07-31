#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

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

  //char stores one character from stdin
  char c ;

  //canread stores the result of reading
  ssize_t canread = read(0, &c, 1) ;
  if (canread == -1)
    {
      fprintf(stderr,"Error reading \n") ;
      exit(-1) ;
    }

  //canwrite stores the result of writing
  char  s; //stores the output char
  ssize_t canwrite ;
  int print = 0 ; //acts like a bool value, stores if char printed


  //while loop gets each char from stdin and prints the
  //proper char for that until EOF is reached
  //canread stores 0 when finished reading
  while (canread > 0)
    {
      //checking if char has a replacement
      for(int i=0 ; i<size1 ; i++ )
	{
	  if (c == string1[i])
	    {
	      print = 1 ;
	      s = string2[i] ;
	      canwrite = write(1, &s, 1) ;
	      if (canwrite == -1)
		{
		  fprintf(stderr,"Error writing \n") ;
		  exit(-1);
		}
	      else if (canwrite == 0)
		{
		  fprintf(stderr,"Did not print anything\n") ;
		  exit(-1);
		}
	      break ;
	    }
	} //end of for loop

      //if replacement was not found, print the original char
      if (print == 0)
	{
	  s = c ;
	  canwrite = write(1, &s, 1) ;
	  if (canwrite == -1)
	    {
	      fprintf(stderr,"Error writing \n") ;
	      exit(-1) ;
	    }
	}
      
      //sets the values to default and gets stdin for next loop 
      print = 0;
      canread = read(0, &c, 1) ;
      if (canread == -1)
	{
	  fprintf(stderr,"Error reading \n") ;
	  exit(-1) ;
	}
    }
  return 0;
}
