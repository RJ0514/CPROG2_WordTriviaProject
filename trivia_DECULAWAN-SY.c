/* Put your declaration of original work here. */
/********************************************************************************************************* This is to certify that this 
project is my own work, based on my personal efforts in studying and applying the concepts learned. I have constructed 
the functions and their respective algorithms and corresponding code by myself. The program was run, tested, and 
debugged by my own efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the work of 
other students and/or persons.
 				DECULAWAN, RYAN JAY D. DLSU ID# 12074039
				SY, MON JERICHO, DLSU ID# 12034401
*********************************************************************************************************/
/* Make sure that the main() is not in this file. */

#include "trivia.h"
#include <windows.h>
/* You can add other data structures here.
   
   You are expected to implement other functions not listed
   in the trivia.h here. Do not forget to include internal 
   documentation. For functions with long (many lines) of code,
   make sure to also include inline comments to discuss your
   algorithm.
*/

void deleteClue(wordList aEntries, int nElem);
/* Given a row in gameboard with n number of columns, this function
   checks each element of A[] either for a * or a - character.
   If the '*' is found it stops searching and signals that the player
   already has a correct answer in a row. It also checks if the 
   number of wrong is equal to the n number of rows. (Signifies that each line has '-').
   If the wrong and rows are equal, the game should end.
 
 	Code: RJD
   @param A - 1 Row of gameboard
   @param n - number of Columns
*/
int check2D(char A[],int n)
{
	int i, wrong = 0;
	for(i=0;i<n;i++)
	{
		if(A[i] == '*')
			return 1;
		else if(A[i] == '-')
			wrong++;
	}
	if(wrong == n)
		return 0;
	else
		return 2; 
}

/*This function is used to take input from the user
	@param str - Address of a character array to store the inputs of the user. 
*/
void
getLongString(char str[]) 
{  char ch;
   int i = 0;

   do
   {
	   scanf("%c", &ch);
	   if (ch != '\n')
	   {
	      str[i] = ch;
		  i++;
       }
	   else str[i] = '\0';
   } while (ch != '\n');
}


/* Implement the functions listed in trivia.h here. 
   Read through the comments to know what the function is
   supposed to accomplish.  Note that the function names
   may not exactly be performing the whole task indicated
   in the mp specs.  For example, some may not have the 
   getting of input be part of the function, instead it 
   could be somewhere else and was just passed to the 
   function as parameter.
   
   Provided below are examples of the comments before 
   each function.  
*/

/* This function scans for input from a text file given
	str1 and str2 as string containers. Function to check
	if the word existsis not yet included
	@param fp - File that is currently accessed.
	@param str1 - 1st String Container.
	@pararm str2 - 2nd String Contatiner.
	CODE: RJD
*/
int			
getLongInput(FILE *fp, char str1[], char str2[])
{  char ch;
   int n1 = 0, i = 0;
   do
   {
	   fscanf(fp,"%c", &ch);
	   if (ch != '\n' && ch != ':' && ch != '\0')
	   {
	      str1[i] = ch;
		  i++;
		  n1+=1; 
       }
       /*If what is scanned is ':' stop scanning.*/
		else if(ch == ':' || ch == '\n')
			str1[i] = '\0';
		else	/*Preventing garbage values to be detected*/
			return 0;
   } while (ch != ':' && ch!= '\n'); 
   i = 0;
   
   /*ASSUMING THAT: Object: <Answer>\n or <Relation>: <RelValue>\n
   If there is atleast 1 valid input detected above, we proceed to 
   get either the answer or the relValue.
   */
    if(n1>0)
    {
		do
	    {
		   fscanf(fp,"%c", &ch);
		   if (ch != '\n')
		   {
		   	
		   		if(n1 == 1)
		   		{
		    		str2[i] = ch;
			  		i++;
				}
				n1 = 1;
	       }
		   else
				str2[i] = '\0';

	    } while (ch != '\n');
	}
	else
		return 0;
	
	return 1;
}

/*	Given the temp struct, aEntries, index of existing word, 
	and the number of elements this function gets the word and clues 
	and asks the user if the word should be replaced or not. 
	If the user wants it replaced then the word at that index will be 
	updated, if not then the word is skipped from scanning.
	CODE: RJD
*/
void wordExists(FILE* fp ,struct triviaTag temp, wordList aEntries, int nIndex, int nElem)
{
	int nChoice, nClues = 0,nValid = 0;
	strWord temp1, temp2;
	do{
		printf("Alert! %s already exists in aEntries!\n",temp.answer);
		printf("Do you want to replace its contents?\n");
		printf("[1]Yes\n");
		printf("[2]No\n");
		scanf("%d",&nChoice);
	}while(nChoice < 1 || nChoice > 2);
	fflush(stdin);			
	/*If user wants to replace*/
	
	if(nChoice == 1)
	{
		/*store sa temp yung contents then store it sa aEntries*/
		//We want it to stop scanning when it sees \n as the first word
		/*Problemo: Update this to new way of getting input or once the user wants to replace
				then also change conditions in scanning forr clues.
		*/
		do
		{
			nValid = getLongInput(fp,temp1,temp2); 
			if(nValid > 0)
			{
				strcpy(temp.clueList[nClues].relation, temp1);
				strcpy(temp.clueList[nClues].relValue, temp2);
				///Increment numClues
				nClues+=1;
			}
				
		}while(nValid > 0);	
		/*Assignment statements*/
		
		temp.numClues = nClues;
		aEntries[nIndex] = temp;
	}
	else
	{
		do
		{
			nValid = getLongInput(fp,temp1,temp2); 
			if(nValid > 0)
			{
				strcpy(temp.clueList[nClues].relation, temp1);
				strcpy(temp.clueList[nClues].relValue, temp2);
				nClues+=1;
			}
				
		}while(nValid > 0);	
	}
}

/* Given the filename stored in fname, this function
   loads the entries of the text file and ADDS them to
   the array aEntries. The number of elements should be
   updated in pElem. For each trivia word in the file 
   that already exists in aEntries, the user is asked if 
   he wants to keep the one in the array or replace it 
   with the one from the text file.
 
   @param fname - the string filename, including the extension
   @param aEntries - the array of words with the corresponding clues
   @param pElem - the address where the number of elements are 
                  to be updated
    CODE: RJD
*/

void
import(strWord fname, wordList aEntries, int * pElem)
{
	/*I dont think this workds*/
	FILE *fp;
	struct triviaTag temp; 
	strWord wSpace,temp1,temp2;
	
	int nIndex, nClues = 0, nElem = *pElem;
	int nValid = 0, nExit = 0, nExists = 0;
	int del1;
	fp = fopen(fname, "r");
	
	/*There must be a prompt for when the user wants to replce the word which already exists*/
	/*Problem Resolved: yung while na yan dapat may additional condition, pag di pa puno yung aEntries.*/
	
	if(fp != NULL)
	{
		do
		{
			fflush(stdin);
			/*While it is able to scan for answers.*/
			del1 = getLongInput(fp, wSpace, temp1);
			if(del1 != 0) /*kinukuha niya is Object: Snorlax or Kind of: Heavy -- Dapat sana hati sa dalawa.*/
			{
				/*Assuming that the first entry has "Object: ", We store the string after it.*/
				if(strcmp(wSpace,"Object") == 0)
					strcpy(temp.answer, temp1);
				/*Now we need to check if it exists.*/
				nIndex = searchWord(temp1, aEntries, nElem);
				if(nIndex != -1)
				{
					wordExists(fp,temp,aEntries,nIndex,nElem);
					nExists = 1;
					nElem--;
					/*PROBLEM: KAPAG NAG NO DI DAPAT MAGIINCREASE ANG NELEM*/
				}
			}
			else
				nExit = 1;
			if(nExists != 1)
			{
				do
				{
					if(getLongInput(fp,temp1,temp2) > 0)
					{
						strcpy(temp.clueList[nClues].relation, temp1);
						strcpy(temp.clueList[nClues].relValue, temp2);
						///Increment numClues
						nClues++;
					}
					else
						nValid = 1;
				}while(nValid == 0);
				
				/*Assignment statement and Increment elements*/
				temp.numClues = nClues;
				aEntries[nElem] = temp;
				nElem+=1;
			}
			nExists = 0;
			nValid = 0;
			nClues = 0;
		
		//If the next line is \n and the following line is \n exit.		
		}while(nExit == 0 && nElem < CAP);	
			*pElem = nElem - 1;
		fclose(fp);
	}
	else
		printf("Error File\n\n");
}

/* Given a row of gameboard, this function
  checks if a letter is already used
	
   @param rowLetters - the characters initialized in one row.
   @param nCols - the number columns to be initialized in gameboard
   @param checkLet - the character to be checked if it already exists.
   CODE: RJD
*/
int checkFirstLetter(char rowLetters[], char checkLet, int nCols)
{
	int i, isPresent = 0;
	for(i=0;i<nCols;i++)
	{
		if(rowLetters[i] == checkLet)
			isPresent = 1;
	}
	return isPresent;
}

/* This function initializes the gameboard with nRows by
   nCols number of characters based on the contents of 
   aEntries.  The use member field is also updated to
   signify that this entry is already used in the board
   for the current game.  The function returns 1 if the
   board can be fully initialized with unique entries based
   on the needed dimension. Otherwise, the function returns 0.

   @param gameboard - 2D array of characters containing the
                      first letters of the answer
   @param nRows - the number rows to be initialized in gameboard
   @param nCols - the number columns to be initialized in gameboard
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
   @return 1 if successful initialization of the gameboard, 0 otherwise
   CODE: RJD
*/
int 	
initBoard(arrMatrix gameboard, int nRows, int nCols,	
              wordList aEntries, int nElem)
{			
	int i, j, isPresent = 0, entryIndex = 0, numElem = 0;
	/*For the Random index*/
	int randIndex, lowBound = 0, upBound = nElem, nValid = 1, ctr = 0;

	if(nElem <= 0)
		return 0;
			
	if(upBound > 0)
		upBound -=1;	
	srand(time(NULL));
		
	for(i=0;i<nRows;i++)
	{
		for(j=0;j<nCols;j++)
		{	
			do		
			{	
				randIndex = (rand() % (upBound - lowBound + 1)) + lowBound;	//0 1 2
				
				/*If the Random word is still not yet used in any row.*/
				if(nValid != 0 && aEntries[randIndex].use == 0)
				{	
					//Check if the first letter is already present in the current row.
					if(checkFirstLetter(gameboard[i],aEntries[randIndex].answer[0],nCols) == 0)	
					{
						entryIndex = randIndex;
						numElem++;
						isPresent = 0;
						/*Since there exists a valid word we can stop checking.*/
						nValid = 0;
					}
				}
				else
					ctr++;
				
				/*The Rarest CASE:*/
				if(ctr >= nElem * 500)
				{
					printf("What? Someone reached this level?\n\n");
					Sleep(4000);
					printf("Anyway, Welcome! This is the RAREST Version of this game\n\n");
					Sleep(3000);
					printf("As you will see, the gameboard will be initialized yet it's missing a Letter.\n\nEither that or I'm just messing with you.\n\n");
					Sleep(3000);
					printf("What are the Chances you might ask?\n\n");
					Sleep(3000);
					printf("Well it depends on the number of elements in aEntries.\n\n");
					Sleep(3000);
					printf("THE PROBABILITY OF THIS IS 1/%d if my math is correct\n\n", nElem * 500);
					Sleep(3000);
					printf("I'd be best if you use the exit and play again.\n\n");
					Sleep(3000);
					printf("What? Are u accusing me of doing this to prevent some kind of error?\n\n");
					Sleep(3000);					
					printf("Nonono. This only means that you are very lucky! Now go start the game again or \nif you really want to test this out.. go ahead!\nif it initializes correctly, then YOUR LUCK IS OVER 9000!!\n\nHave fun!\n");
					Sleep(2000);
					
					nValid = 0;
					j = nCols;
				}
			}while(nValid == 1);	//while all aEntries is yet to be checked.
			
			if(isPresent == 0){				//If letter is not present.
				gameboard[i][j] = aEntries[entryIndex].answer[0];
				aEntries[entryIndex].use = i + 1;
			}
			nValid = 1;
			ctr = 0;
		}
	}
	if(numElem < (nRows * nCols))
		return 0;
	else
		return 1;
}

/*	This Functions displays the gameboard given nRows annd nCols
 	@param gameboard - the 2D array of characters.
    @param nRows - the number of rows in gameboard.
    @param nCols - the number of columns in gameboard.
    CODE: MJS
*/
void displayTable(arrMatrix gameboard, int nRows, int nCols)
{
	int i,j;
	for(i=0;i<nRows;i++)
	{
		for(j=0;j<nCols;j++)
		{
			printf("%c ",gameboard[i][j]);
		}
		printf("\n");
	}
}

/* This function facilitates the game play of the user,
   including determining when the game ends. 
   @param gameboard - the 2D array of characters.
   @param nRows - the number of rows in gameboard.
   @param nCols - the number of columns in gameboard.
   @param aEntries - the array of words with the corresponding clues.
   @param nElem - the number of elements in aEntries.   
   CODE: RJD
*/   
void 
play(arrMatrix gameboard, int nRows, int nCols,
          wordList aEntries, int nElem)
{
	int nChoice = 0;
	int i,j, indexWord, iCoord, jCoord;
	int nCurrentRow = 1, nValidRow = 0;	
	int nCorrect = 0, over = -1, nExit = 0;
	int checkWord;
	char firstLetter;
	strWord playAnswer;
	
	//For randomizing clues.
	int randomIndex, randomClue;
	int lowBound = 0, upBound;
	srand(time(NULL));
	char cdump;
	
	int nPlayed = 0;
	do{
		/*While the User wants to play the game.*/
		if(nPlayed > 0)
			initBoard(gameboard,nRows,nCols,aEntries,nElem);
		printf("You can exit the current game anytime using '*'\n\n");
		/*Final adjustments: Exit whenverr, Add print designs. delay could also work.*/
		do{
			displayTable(gameboard,nRows,nCols);
			
			/*Choose a Letter.*/
			do{	
				printf("Choose a letter from row %d\n",nCurrentRow);
				scanf("%c%c",&firstLetter, &cdump);
				
				/*Check if the input exists in the current row.*/
				for(i=0;i<nCols;i++)
				{
					/*If the player wants to exit*/
					if(firstLetter == '*')
					{
						i = nCols;
						over = 1;
						nValidRow = 2;	
					}
						
					/*Check for the input and collect the index of the word in aEntries.*/
					if(firstLetter == '-')
						nValidRow = 0;
					else if(firstLetter == gameboard[nCurrentRow - 1][i])
					{			
						nValidRow = 1;
						for(j=0;j<nElem;j++)
						{
							if(nCurrentRow == aEntries[j].use && firstLetter == aEntries[j].answer[0])
							{
								indexWord = j;
								j=nElem;
							}
							
						}
						/*Store the gameboard coordinates of the Letter and exit the loop. */
						iCoord = nCurrentRow - 1;
						jCoord = i;
						i = nCols;
						upBound = aEntries[indexWord].numClues - 1 ;
					}
						
				}
				fflush(stdin);
			}while(nValidRow == 0);
			
			/*If the player did not choose to exit the first time he was asked for input*/
			if(nValidRow != 2)
			{
				randomIndex = rand() % (upBound - lowBound + 1) + lowBound;
				randomClue = randomIndex;
				
				/*Display a random Relation: Relation Value.*/
				printf("Hint:\n");
				printf("%s %s\n",aEntries[indexWord].clueList[randomClue].relation, aEntries[indexWord].clueList[randomClue].relValue);
				printf("Answer:\n");
				getLongString(playAnswer);
				
				/*If the player wants to exit*/
				if(strcmp(playAnswer, "*") == 0)
				{
					nExit = 1;
					over = 1;
				}
				
				/*Checking for correct/wrong answers.*/
				if(nExit !=1)
				{
					/*Check if the input of the user exists.*/
					checkWord = searchWord(playAnswer,aEntries,nElem);
					if(checkWord != -1)
					{
						if(aEntries[checkWord].use == nCurrentRow)
						{
							gameboard[iCoord][jCoord] = '*';	
						}
						else
							gameboard[iCoord][jCoord] = '-';
					}
					else
						gameboard[iCoord][jCoord] = '-';
					
					/*Winning or Losing Conditions.*/
					if(check2D(gameboard[nCurrentRow - 1],nCols) == 1)
					{
						nCorrect+=1;
						nCurrentRow+=1;
					}
					if(check2D(gameboard[nCurrentRow - 1],nCols) == 0)
						over = 1;
					
					/*If each row has an '*' */
					if(nCorrect == nRows)
						over = 0;
						
					nValidRow = 0;
				}
			}
			
		}while(over == -1);
		
		if(over == 0)
			printf("You win!\n");
		else if(over == 1)
			printf("You Lose.\n");
		
		do{
			printf("Do you want to play again?\n");
			printf("[1] Yes\n");
			printf("[2] No\n");
			scanf("%d",&nChoice);
			fflush(stdin);
		}while(nChoice != 1 && nChoice != 2);
		fflush(stdin);
		
		//Whether player wants to play again or not, incrmeent the number of times played.
		nPlayed+=1;
		/*If the player wants to play again, reset all used flags and counters.*/
		if(nChoice == 1)
		{
			nExit = 0;
			nCorrect = 0;
			nChoice = 0;
			over = -1;
			nCurrentRow = 1;
			
			/*Reset the table values.*/
			for(i=0;i<nRows;i++)
			{
				for(j=0;j<nCols;j++)
					if(gameboard[i][j] == '*' || gameboard[i][j] == '-')
						gameboard[i][j] = 'A';
			}
			
			/*Set all use values to 0.*/
			for(i=0;i<nElem;i++)
			{
				if(aEntries[i].use > 0)
					aEntries[i].use = 0;
			}
			
		}
		else if(nChoice == 2)
			nChoice = 1;
				
	}while(nChoice == 0);
}

/* This function shows the menu options in the maintenance
   phase as well as call the functions (like listWords(), 
   addWord(), etc.) that are relevant to the chosen option.   
   CODE: MJS
*/
void maintenance()	
{
	int nChoice, nIndex, nElem = 0, nValid = 0;
	wordList aEntries;
	char cdump, chrinp;
	strWord userInput;
	do{
		nChoice = 0;
		printf("What would you like to do?\n");
        printf("1. Add Word\n2. Add Trivia\n3. Modify Entry\n--------------\n4. View Words\n5, View Clues\n--------------\n6. Delete Word (Including Trivia)\n7. Delete Trivia\n--------------\n8. Export Entries\n9. Import Entries\n--------------\n10. Exit\n");
		scanf("%d%c", &nChoice, &cdump);
		fflush(stdin);
		sortEntries(aEntries,nElem);

		if(nElem > 0){
		switch(nChoice){
			case 1: addWord(aEntries, &nElem);
					break;
			case 2: listWords(aEntries,nElem);   
					do{
						printf("Which word would you like to edit? (Input the number beside it):\n");
						scanf("%d%c",&nIndex,&cdump);
						fflush(stdin);
					}while(nIndex < 0 || nIndex > nElem);
					nIndex-=1;
					addTrivia(&aEntries[nIndex]);	
					break;
			case 3: listWords(aEntries,nElem);
					do{
						printf("Type a valid word (not the number beside it) to edit: ");
						getLongString(userInput);
						nIndex = searchWord(userInput,aEntries,nElem);
						if(nIndex != -1)
							nValid = 1;
						else
							nValid = 0;
					}while(nValid == 0);
					modifyEntry(&aEntries[nIndex]);
					break;
			case 4: viewWords(aEntries,nElem);
					break;
			case 5: listWords(aEntries,nElem);
					do{
						printf("Type in a valid word (not the number beside it) you want to view: ");
						getLongString(userInput);
						nIndex = searchWord(userInput,aEntries,nElem);
					}while(nIndex < 0);
					displayAllClues(aEntries[nIndex].clueList, aEntries[nIndex].numClues);
					break;
			case 6: listWords(aEntries, nElem);
					deleteWord(aEntries, &nElem);	
					break;
			case 7: listWords(aEntries,nElem);
					deleteClue(aEntries,nElem);
					break;
			case 8: printf("Input the file name (INCLUDING THE EXTENSION): ");
					getLongString(userInput);
					export(userInput,aEntries,nElem);
					break;
			case 9: printf("Input the file name (INCLUDING THE EXTENSION): ");
					getLongString(userInput);
					import(userInput,aEntries,&nElem);
					break;
			case 10: printf("Would you like to export your changes to the file first before exiting?: ");
					 scanf("%c%c", &chrinp, &cdump);
					 if(chrinp == 'y'){
						printf("Input the file name (INCLUDING THE EXTENSION): ");
						getLongString(userInput);
						export(userInput,aEntries,nElem);
						break;
					 } else
					 break;
			default: printf("INVALID OPTION. \n");
					break;
			}
		} else{
			switch(nChoice){
			case 1: addWord(aEntries, &nElem);
					break; 	
			case 9:  printf("Input the file name (INCLUDING THE EXTENSION): ");
					getLongString(userInput);
					import(userInput,aEntries,&nElem);
					break;
			case 10: break;
			default: printf("\nAdd something to use this entry.\n");
					 break;
			}

		}
	
	}while(nChoice != 10);
	
}

/* This function returns the index where the key was found
   in aEntries. If not found, the function returns -1.
   @param key - the word or phrase to look for
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
   @return the index where key was found, -1 otherwise
   CODE: BOTH (Same Approach)
*/
int 
searchWord(strWord key, wordList aEntries, int nElem)
{
	int i, isFound = 0;
	for(i=0;i<nElem;i++)
	{
		if(strcmp(aEntries[i].answer, key) == 0)
		{
			isFound = i;
			return isFound;
		}
	}
	return -1;
}

/* This function displays the list of words (without the clues)
   in aEntries. 
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
   CODE: BOTH (Same Approach)
*/ 
void 
listWords(wordList aEntries, int nElem)
{
	int i;
	for(i=0;i<nElem;i++)
		printf("[%d] %s\n",i+1,aEntries[i].answer);		
	
}

/* This function will ask the user to input the word, calls
   searchWord() to check if the word is unique.  If unique, this
   word is added, the addTrivia() is called, and the
   number of elements is updated. Other error checking (as 
   indicated in the MP specs requirements) are also done.

   @param aEntries - the array of words with the corresponding clues
   @param pElem - the address where the number of elements are 
                  to be updated
    CODE: RJD
*/
void 
addWord(wordList aEntries, int * pElem)		
{
	int isValid = 0;
	strWord temp;
	int nElem = *pElem;
	printf("%d\n",nElem);
	while(isValid != 1){
		printf("Add a word: ");
		getLongString(temp); 
		
		/*If the words is not found in aEntries and there is still space in the number of elements */
		if(searchWord(temp,aEntries,nElem) == -1 && nElem < CAP){
			//nElem+=1;
			strcpy(aEntries[nElem].answer, temp);
			addTrivia(&aEntries[nElem]);
			isValid = 1;
			nElem++;
		}
	}
		*pElem = nElem;
}

/* This function will ask the user for the relation and
   relation value as store it in the clueList member field
   in *oneEntry, as long as the array can still accommodate
   more data and as long as the user still wants to add
   more entries. If there are existing clues already, new
   entries are added (not overwritten). The member field
   numClues is also updated.

   @param oneEntry - address to the structure containing the
                     array of clues and the number of clues,
					 among other data
	CODE: BOTH (Same Approach)
*/
void 
addTrivia(struct triviaTag * oneEntry)		
{
	int clues = oneEntry->numClues;
	int addMore = 1;
	char option[2],cdump;
	
	do{
		printf("Number of clues in word [%s]: %d\n",oneEntry->answer,clues);
		/*Take in Relation and RelValue*/
		printf("Input the Relation: ");
		getLongString(oneEntry->clueList[clues].relation); 
		printf("Input the Relation Value: ");
		getLongString(oneEntry->clueList[clues].relValue); 
																										
		clues++;
		
		/*Give the option to user for adding another clue*/
		printf("Do you want to add another clue? ");
		printf("(Y for Yes and N for No): ");
		scanf("%s%c",option,&cdump);

		/*Even if the user says yes and the number of clues is already MAX, 
			program should exit the function*/
		if(clues < MAX && (strcmp(option, "N") == 0 || strcmp(option, "n") == 0) )
			addMore = 0;
		else
			addMore = 1;
		fflush(stdin);
	}while(addMore == 1);	
	oneEntry->numClues = clues; 	
}

/* This function will ask the user for which part of the
   information in *oneEntry that will be modified (word or
   clue). The required input, including appropriate error
   checking as indicated in the specs, is done in this
   function.  The user is allowed to modify multiple parts
   of *oneEntry, until the user chooses to finish the 
   editing. For the clues, only modification can be done.
   That is, deletion or addition is not allowed here.

   @param oneEntry - address to the structure containing the
                     words, array of clues and the number of clues,
					 among other data
	CODE: RJD
*/

void 
modifyEntry(struct triviaTag * oneEntry)
{
	int nChoice =0, i ,clueIndex = 0, relChoice = 0, nValid = 0;
	//Menu:
	do{
		printf("Welcome to Modify Entry. The word you are trying to access is %s\n\n",oneEntry->answer);
		printf("What do you want to edit?\n");
		printf("[1] Word\n");
		printf("[2] Clues\n");
		printf("[3] Return\n");
		
		scanf("%d",&nChoice);
		
		//Modify a Word.
		if(nChoice == 1)
		{
		fflush(stdin);
			printf("Replacing %s\n", oneEntry->answer);
			getLongString(oneEntry->answer);
		}
		
		//Modify a Clue
		else if(nChoice == 2)
		{
			fflush(stdin);
			//Display the list of Clues.
			for(i = 0; i<oneEntry->numClues;i++)
				printf("%d %s %s\n",i+1 ,oneEntry->clueList[i].relation, oneEntry->clueList[i].relValue);
			
			//Ask the user until a valid clue number is provided.
			do{
				printf("Indicate the Clue number you wish to access.\n");
				scanf("%d", &clueIndex);
				
			}while(clueIndex <= 0 || clueIndex > oneEntry->numClues);
		clueIndex-=1;
			
			
			while(nValid == 0)
			{	
				printf("What do you want to edit?\n");
				printf("[1] Relation\n");
				printf("[2] Relation Value\n");
				scanf("%d", &relChoice);
				if(relChoice >= 1 && relChoice <= 2)
					nValid = 1;
			}
			
				fflush(stdin);
				if(relChoice == 1){
					fflush(stdin);
					getLongString(oneEntry->clueList[clueIndex].relation);
				}
				else if(relChoice == 2){
					fflush(stdin);
					getLongString(oneEntry->clueList[clueIndex].relValue);
				}
			nValid = 0;
		}
		fflush(stdin);
	}while(nChoice != 3);
}

/* This function will ask the user to input the word and the "index" of
   the relation and relation value that will be deleted.  
   If deletion is successful (i.e., the Clue was found), the
   number of clues in aEntries should also be updated.

   @param aEntries - the array of words with the corresponding clues
   @param pElem - the address where the number of elements are 
                  to be updated
	CODE: RJD
*/
void 
deleteClue(wordList aEntries, int nElem)
{
	int i,indexDel = -1, indexDelClue = -1, confirmDel = 0;
	char cdump;
	strWord wordDel;
	
	do{
		printf("Enter a valid word you want to check:\n");
		getLongString(wordDel);
		indexDel = searchWord(wordDel,aEntries,nElem);
	}while(indexDel < 0);
	
	fflush(stdin);
	printf("Word Selected: %s\n",aEntries[indexDel].answer);
	displayAllClues(aEntries[indexDel].clueList, aEntries[indexDel].numClues);
	
	/*Ask the user what clue to delete*/
	do{
		if(aEntries[indexDel].numClues > 0)
		{
			printf("Enter the clue number you would like to delete:\n");
			scanf("%d%c",&indexDelClue, &cdump);
		}
		fflush(stdin);
	}while(indexDelClue < 0 || indexDelClue > aEntries[indexDel].numClues);
	indexDelClue-=1;
	
	printf("Do you confirm deletion?\n [1] Yes\n [2] No\n");
	scanf("%d%c",&confirmDel, &cdump);
	
	if(confirmDel == 1)
		{
		/*Perform deletion and sort it. Also decrease the number of clues*/
			for(i = indexDelClue; i< aEntries[indexDel].numClues - 1;i++)
				aEntries[indexDel].clueList[i] = aEntries[indexDel].clueList[i+1];
			aEntries[indexDel].numClues-=1;
		}
	else
		fflush(stdin);
	
}

/* This function will ask the user to input the word (or phrase)
   that will be deleted.  Calls to other functions, like 
   searchWord(), as needed by the function, will be done.
   If deletion is successful (i.e., the word was found), the
   number of elements in pElem should also be updated.

   @param aEntries - the array of words with the corresponding clues
   @param pElem - the address where the number of elements are 
                  to be updated
    CODE: RJD
*/
void 
deleteWord(wordList aEntries, int *pElem)
{
	int i;
	strWord delWord;
	
	int nIndexDel = -1;
	printf("Input Word to Delete:\n");
	getLongString(delWord);

	nIndexDel = searchWord(delWord, aEntries,*pElem);
	
	/*Perform adjustments and decrease number of elements*/
	if(nIndexDel != -1)
	{
		for(i=nIndexDel; i<*pElem - 1;i++)
		{
			aEntries[i] = aEntries[i+1];
		}
		*pElem-=1;
	}
	if(*pElem == 0)
		printf("There are no words.\n");
}

/* This function displays all information per element in aEntries.
   Part of the solution is to call the other function/s, like 
   viewEntry(), as needed by the function.
 
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
   CODE: BOTH (Same Approach)
*/
void 
viewWords(wordList aEntries, int nElem)
{	
	int i = 0, exit = 0;
	char viewMenu[2];
	
	do
	{
		if(nElem!=0)
		{
			viewEntry(aEntries[i]);
			printf("Press N for next\n");
			printf("Press P for Previous\n");
			printf("Press X for exit\n");
			
			scanf("%s",viewMenu);
			
			/*Conditions to prevent access of garbage data.*/
			if((strcmp(viewMenu,"N") == 0 || strcmp(viewMenu, "n") == 0) && i + 1 <nElem)
				i++;
			else if((strcmp(viewMenu,"P") == 0 || strcmp(viewMenu, "p") == 0) && i - 1 >= 0)
				i--;
			else if(strcmp(viewMenu,"X") == 0 || strcmp(viewMenu, "x") == 0)
				exit = 1;
		}
		else
			exit = 1;
	}while(exit != 1);	
}

/* This function displays all information in entry.
   Part of the solution is to call the other function/s, like 
   displayAllClues(), as needed by the function.
 
   @param entry - structure containing the word and the clues, 
                  among other data
    CODE: BOTH (Same Approach)
*/
void
viewEntry(struct triviaTag entry)
{
	printf("%s",entry.answer);			
	printf("\n");
	displayAllClues(entry.clueList, entry.numClues);
}

/* This function displays numClues number of elements from aList.

   @param aList - array of relation and relation values
   @param numClues - number of elements in aList
   CODE: BOTH (Same Approach)
*/
void displayAllClues(arrClues aList, int numClues)
{
	int i;
	
	if(numClues > 0)
		for(i=0;i<numClues;i++)
			printf("[%d]%s  %s\n",i + 1,aList[i].relation,aList[i].relValue);
	else
		printf("There no clues.\n");
}

/* Given the filename stored in fname, this function
   overwrites the contents of the text file with the contents 	
   if the array aEntries. Contents of aEntries and nElem will 
   not change in this function.
 
   @param fname - the string filename, including the extension
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
	CODE: RJD
*/
void
export(strWord fname, wordList aEntries, int nElem)
{
	FILE *fp;
	int i,j;
	fp = fopen(fname,"w");
	if(fp!=NULL)
	{
		/*For all elements in aEntries.*/
		for(i=0;i<nElem;i++)
		{
			fprintf(fp,"Object: %s\n",aEntries[i].answer);
			for(j=0;j<aEntries[i].numClues;j++)
			{
				//This Assumes that the clues don't have ':'
				fprintf(fp, "%s: %s", aEntries[i].clueList[j].relation, aEntries[i].clueList[j].relValue);
				fprintf(fp,"\n");
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
}


/*	This function swaps the information between 2 structures.
	@param aptr - address of the first structure
	@param bptr - address of the 2nd structure.
   CODE: BOTH (Same Approach)
*/
void swapforSort(struct triviaTag * aptr, struct triviaTag * bptr)
{
	struct triviaTag temp;
	temp = *aptr;
	*aptr = *bptr;
	*bptr = temp;
}

/* This function sorts the contents of aEntries in increasing
   order (based on ASCII value). The solution to this function
   should be an IMPLEMENTATION of a sorting algorithm, NOT by
   calling a sort function from some C library.
   
   @param aEntries - the array of words with the corresponding clues
   @param nElem - the number of elements in aEntries
   CODE: RJD
*/

void 
sortEntries(wordList aEntries, int nElem)
{
	int i,j,sIndex;
	strWord smallest;
	/*Cocompare natin is aEntries[i].answer*/
	for(i=0;i<nElem - 1;i++)
	{
		sIndex = i;
		
		/*Selection Sort*/
		for(j = i + 1;j < nElem;j++)			
		{
			if(strcmp(aEntries[j].answer,aEntries[sIndex].answer) < 0)
			{
				sIndex = j;
				strcpy(smallest,aEntries[j].answer);
			}
		}
		swapforSort(&aEntries[i], &aEntries[sIndex]);	//--Swapping functions using a temp variable
	}
}
