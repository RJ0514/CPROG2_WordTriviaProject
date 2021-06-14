#include "trivia_DECULAWAN-SY.c"  //modify this to reflect the filename that you used for your solution.

int
main()
{
   arrMatrix gameboard;
   int nRows, nCols;
   int opt;
   char cDump;
   wordList aEntries;
   int nElem = 0;
   int test;
   strWord fname;
   
   do
   {
     printf("Main Menu\n");
     printf("1 - Game Phase\n");
     printf("2 - Maintenance Phase\n");
	 printf("3 - Exit\n");
    
	 scanf("%d%c", &opt, &cDump);
   
     switch (opt)
	 {
	     case 1: do
		         {
		           printf("How many rows for the board? ");
		           scanf("%d", &nRows);
				   printf("How many columns for the board? ");
		           scanf("%d%c", &nCols, &cDump);
				   
				   printf("Enter filename for source of trivia: ");
				   scanf("%s", fname);
				   import(fname, aEntries, &nElem);
				   
				   test = initBoard(gameboard, nRows, nCols, aEntries, nElem);
                 } while (test == 0 || !(nRows > 0 && nRows <= 10) || 
				         !(nCols > 0 && nCols <= 10));
				 play(gameboard, nRows, nCols, aEntries, nElem);
				 break;
		 case 2: maintenance();
         case 3: break;
         default: printf("Invalid option\n");
     }
   } while (opt != 3);	

   return 0;                 				 
}
