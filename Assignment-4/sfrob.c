#include <stdio.h>
#include <stdlib.h>


// frocmp function here compares two frobnicated char arrays 
int frocmp (char const * a, char const * b)
{
  while(*a == *b)
    {
      if (*a == ' ') return 0 ;
      a++;
      b++;
    }


  // if reaches here, it means they are not equal
  char charA = *a ^ 42 ; //XOR with 00101010 ->2+8+32=42
  char charB = *b ^ 42 ; //XOR with 00101010 ->2+8+32=42 

  //if two char are not equal, then it compares the frobnicated values
  //if a string is a subtring of another, then longer one is greater 
  if (*b == ' ' || charA > charB) return 1;
  if (*a == ' ' || charA < charB) return -1;
}


//Function compare used within qsort-> this function
//typecasts the void * to char * and calls frocmp function
int compare (const void* A, const void* B)
{
  const char * a =  * (const char**)A ;
  const char * b =  * (const char**)B;
  return frocmp(a,b);
}



int main ()
{
  // word acts like a buffer and gets everything from stdin
  char * word = (char*) malloc(sizeof(char*));
   if(word == NULL)                                                                       
    {                                                                                   
      fprintf(stderr, "Error while allocating memory");                                 
      exit(0);                                                                          
    }
  
  int wordIndex = 0; // to keep track of characters
  int wordptrIndex = 0; // to keep track of number ofwords
  
   //stores one charcater at a time obtained from stdin
  char current = getchar() ;
  

  //this loop reads everything from stdin and put it inside word []
  while(current != EOF)
  {
	
    if (current == EOF)
      {
	if ( wordIndex == 0 )  // Exit if stdin is empty
	  {
	    exit (1);
	    fprintf(stderr, "Error while getting input") ;
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

    //resizing word to make space for another character
    word = (char*) realloc(word, sizeof(char*) * (wordIndex+1) );
    if(word == NULL)
      {
	fprintf(stderr, "Error while re-allocating memory");
	exit(0);
      }
    
	wordIndex++;
	current = getchar() ;

  }//end of while
    

  //if the last character in the the file was not a
  //space, then add the space at the end  
  if(current == EOF && wordIndex - 1 != ' ')
  {
	word[wordIndex] = ' ' ;
	wordptrIndex ++ ;
  }
  
  //allocating memory to point to different words 
  char ** wordptr = (char**) malloc(sizeof(char*) * wordptrIndex);
  if(wordptr == NULL)                                                                 
    {                                                                                   
      fprintf(stderr, "Error while allocating memory");                                 
      exit(0);                                                                          
    }
  
  char* eachword = word;

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

  
  //Printing each character of word from wordptr  
  for (i=0; i < wordptrIndex ; i++)// printf("%s\n",wordptr[wordptrIndex]);
    {
      for ( j=0; j < wordIndex ; j++)
	{
	  putchar(wordptr[i][j]) ;
	  if (wordptr[i][j] == ' ')break ;
	}
    }
  
  // Deallocate memory
  free(word);
  free(wordptr);

  exit (0) ;
  
}
