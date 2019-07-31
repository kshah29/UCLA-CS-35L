#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <errno.h>

int optionf = 0 ; //stores 1 if option f is passed 

// frocmp function here compares two frobnicated char arrays 
int frocmp (char const * strA, char const * strB)
{
  //loops as long as both the chars are equal
  while(*strA == *strB)
    {
      //If they reach a space, both are equal
      if (*strA == ' ') return 0 ;
      strA++ ;
      strB++;
    }

  // if reaches here, it means they are not equal
  char charA = *strA ^ 42 ; //XOR with 00101010 ->2+8+32=42
  char charB = *strB ^ 42 ; //XOR with 00101010 ->2+8+32=42 

  //if option f is used, then case insensitive comparision is made
  if(optionf == 1)
    {               
      if (charA < CHAR_MAX && charA > CHAR_MIN) charA = toupper(charA) ;
      if (charB < CHAR_MAX && charB > CHAR_MIN) charB = toupper(charB) ;
    }
  
  //if two char are not equal, then it compares the frobnicated values
  //if a string is a subtring of another, then longer one is greater 
  if (*strA == ' ' || charA > charB) return 1;
  if (*strB == ' ' || charA < charB) return -1;
}


//Function compare used within qsort-> this function
//typecasts the void * to char * and calls frocmp function
int compare (const void* A, const void* B)
{
  const char * a =  * (const char**)A ;
  const char * b =  * (const char**)B;
  return frocmp(a,b);
}



int main (int argc, char* argv[])
{
  //checks whether optionf is passed. If it is passed,
  //global varible optionf will be set to 1
  if(argc == 2)
    {
      if(strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'f')
	  optionf = 1 ;
    }

  //Using fstat to get the size of the file. 
  struct stat sbuf ;
  int error = fstat(0, &sbuf) ;
  if (error < 0) //there was error while getting information
    {
      fprintf(stderr, "Error while getting input") ;
      exit(1);
    }
  
  long int Cfilesize = (long) sbuf.st_size ; //stores current filesize
  long int Pfilesize ; //stores previous current filesize 
  int isfile  ; // will tell whether the input is from file

  //Cfilesize is 0 if stdin is not a file
  //isfile will be set to 1, if stdin is file
  if(Cfilesize == 0)
    isfile = 0;
  else
    isfile = 1 ;


  // current stores one character at a time from the buffer 
  char  current = 'z' ;
  ssize_t canread = read(0, &current, 1) ;
  if (canread == -1)
    {
      fprintf(stderr,"Error reading \n") ;
      fprintf(stderr,"Errno: %i\n",errno) ;
      exit(1) ;

    }

  // word acts like a buffer and gets everything from stdin
  //If stdin is a file, then the size of the file is obtained and that
  //much memory is allocated from the start
  //If stdin is not a file, then it is given space to hold 1 char
  char * word ;
  if (isfile)
    word = (char*) malloc(Cfilesize * sizeof(char*));
  else
    word = (char*) malloc(sizeof(char*));

  //checking for errors
  if(word == NULL)
    {
      fprintf(stderr, "Error while allocating memory");
      exit(1);
    }

  int wordIndex = 0; // to keep track of characters
  int wordptrIndex = 0; // to keep track of number ofwords
  

  //this loop reads everything from stdin and put it inside word []
  while(canread != 0)
  {
    if (current == EOF)
      {
	if ( wordIndex == 0 )  // Exit if stdin is empty
	  {
	    fprintf(stderr, "Error while getting input") ;
	    exit (1);
	  }
	break;
      }

    // If current is space, then add the current inside word[]
    // and increment wordptrIndex - no. of words
    if (current == ' ')
      {
	if (wordIndex != 0)
	  if (word[wordIndex - 1] != ' ')
	    {
	      word[wordIndex] = current;
	      wordptrIndex++;
	    }
      }
    else // if current is not space, add the current inside word[] 
      word[wordIndex] = current;

    //resizing word to make space for another character if input is not a file
    if(!isfile)
      word = (char*) realloc(word, sizeof(char*) * (wordIndex+1) );

    //if input is a file and the size of the file changed then, 
    //resize word to make space for another characters
    if (isfile)
      {
        Pfilesize = Cfilesize ;
    //    Cfilesize = (long) sbuf.st_size ;
        if(Pfilesize != Cfilesize)
          word = (char*) realloc(word, sizeof(char*) * Cfilesize);
      }

    // checking for errors
    if(word == NULL)
      {
	fprintf(stderr, "Error while re-allocating memory");
	exit(1);
      }

    //updating index of word and getting new char from stdin
    wordIndex++; 
    canread = read(0, &current, 1) ;
    if (canread == -1)
      {
	fprintf(stderr,"Error reading \n") ;
	fprintf(stderr,"Errno: %i\n",errno) ;
	exit(1) ;
      }
    
  }//end of while
    
  //wordIndex will now represent total no. of characters 
  //if the last character in the the file was not a
  //space, then add the space at the end  
  if(word[wordIndex - 1] != ' ')
  {
	word[wordIndex] = ' ' ;
	wordptrIndex ++ ;
  }
  
  //allocating memory to point to different words 
  char ** wordptr = (char**) malloc(sizeof(char*) * wordptrIndex);
  if(wordptr == NULL)
    {
      fprintf(stderr, "Error while allocating memory");
      exit(1);
    }

  char* eachword = word;
  if(eachword == NULL)
    {
      fprintf(stderr, "Error while allocating memory");
      exit(1);
    }

  // We assign individual words from char * words to wordptr 
  for(int i=0; i < wordptrIndex; i++)
  {
	wordptr[i] = eachword;
	if (i + 1 == wordptrIndex)
		break;
	
	while ( (*eachword) != ' ')
		eachword++;
	
	eachword++;
  }
  
  
  int i=0; //for transversing through an individual word
  int j=0; //for transversing through wordptr - different words 


  //sort the list of frobnicated words obtained from stdin
  qsort(wordptr, wordptrIndex, sizeof(char*), compare) ;

  ssize_t canwrite ; //stores whether print was successful
  
  //Printing each character of word from wordptr  
  for (i=0; i < wordptrIndex ; i++)
    {
      for ( j=0; j < wordIndex ; j++)
	{
	  canwrite = write(1, &(wordptr[i][j]), 1) ;
	  if (canwrite == -1)
	    {
	      fprintf(stderr,"Error writing \n") ;
	      fprintf(stderr,"Errno: %i\n",errno) ;
	      exit(1) ;
	    }
	  if (wordptr[i][j] == ' ')break ;
	}
    }
  
  // Deallocate memory
  free(word);
  free(wordptr);
    
  exit(0) ;
}
