#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LIMIT 100000

/**
 * @brief      	Converts the ciphered character to the original. 
 *
 * @param     	coefficient   The coefficient is the number to deduct of original
 * @param      	originalChar  The original character is the ciphered character to be unciphered.
 *
 * @return     	The unciphered character.
 */
char generateCharacter( int coefficient, char originalChar )
{
	char newChar = originalChar - coefficient;
	if( originalChar >= 'a' && originalChar <= 'z' )
	{
		if( newChar < 'a' )
		{
			int diff = 'a' - newChar;
			newChar = 'z' - diff + 1;
		}
	}
	else if( originalChar >= 'A' && originalChar <= 'Z' ) 
	{
		if( newChar < 'A' )
		{
			int diff = 'A' - newChar;
			newChar = 'Z' - diff + 1;
		}
	}
	else 
	{
		newChar = originalChar;
	}

	return newChar;
}

/**
 * @brief 		Generate and saves in a output file the uncipher message.
 * 
 * @param 		shift number of digits to shift
 * @param 		inputFile pointer for input file to read the ciphered message
 * 
 * @return 		0 in sucess, 1 in otherwise
 */
int uncipher( int shift, FILE * inputFile )
{
    FILE * outputFile = fopen( "build/unciphered", "w" ); // opens a new file to save de coded message
 
    if( outputFile == NULL )
    {
        	printf( "Error in output file creation\n" );
        	return 1;
   	}
	
	char cipheredBuffer[BUFFER_LIMIT]; // array to cipheredBufferize 100 characters of the original file content. The last one char is '\0'.
	char uncipheredCipheredBuffer[BUFFER_LIMIT];  // array to cipheredBufferize 100 characters of the encrypted file content. The last one char is '\0'.
    while( fscanf( inputFile, "%s", cipheredBuffer ) > 0 )
	{
		int i;
		for( i = 0; cipheredBuffer[ i ] != '\0'; i++ )
		{
			if( cipheredBuffer[ i ] != ' ' )
			{
				uncipheredCipheredBuffer[ i ] = generateCharacter( shift, cipheredBuffer[ i ] );
			} else 
			{
				uncipheredCipheredBuffer[ i ] = cipheredBuffer[ i ];
			}
		}
		uncipheredCipheredBuffer[ i ] = '\0';
		fprintf( outputFile, "%s ", uncipheredCipheredBuffer ); 
		
	}
	fprintf( outputFile, "\n" );
	fclose( outputFile );
	return 0;

}

int main( int argc, char * argv[] )
{
	if( argc != 2 )
	{
		printf( "Invalid Arguments!\n" );
		return 1;
	}

	FILE * inputCipheredFile;

	int shift = 1;
	char is_right = 'n';

	while ( is_right != 'y' && shift < 26 ) // the user should be identify what the shift is, according of the print on screen.
											// 	if the user can't identify the shift then the program finishes with no output 
	{
		inputCipheredFile = fopen( argv[1], "r" );

		int sucess = uncipher( shift, inputCipheredFile );

		if( sucess == 0 )
		{
			printf( ">>> Read the following file and answer the next question <<< \n");

			printf( "\n>>>> Unciphered file content begin <<<\n");
			system( "cat build/unciphered" );
			printf( "\n>>>> Unciphered file content end <<<\n");
			
			printf( "\n>>>> Is that shift the correctly? (y if yes, n in otherwise) <<<<\n" );
			scanf( " %c", &is_right );
		}

		shift++;
		fclose( inputCipheredFile );
	}

	if( shift < 26 )
	{
		printf( "\n>>>> The shift value is: %i <<<<\n", shift );
	} else 
	{
		printf( "\n>>>> Exiting without an answer <<<<\n" );
		system( "rm build/unciphered" );
	}
	
	return 0;
}