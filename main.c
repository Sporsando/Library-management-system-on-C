#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>


typedef int8_t i8;
typedef uint8_t u8;
typedef uint16_t u16;
typedef int16_t i16;

#define maxAmountOfBooks 1000
#define maxStringLength 50
#define fgetsAdder 2

#define messageSelectCorrectOption printf("Select correct option (1-5)!\n")

#define columnSeparator " |"
#define columnSeparatorLength (sizeof(columnSeparator) / sizeof(char)) - 1
#define edgeID_TITLE maxIdLength + columnSeparatorLength
#define edgeTITLE_AUTHOR(currentLibrary) edgeID_TITLE + (titleLength > (currentLibrary)->maxBookTitleLength) ? titleLength : (currentLibrary)->maxBookTitleLength + columnSeparatorLength
#define edgeAUTHOR_CATEGORY(currentLibrary) edgeTITLE_AUTHOR((currentLibrary)) + (authorLength > (currentLibrary)->maxBookAuthorLength) ? authorLength : (currentLibrary)->maxBookAuthorLength + columnSeparatorLength

#define selectCorrectId printf("Select correct id (1-%d)!\n", maxAmountOfBooks); \
	inputId(currentLibrary); \
	return

#define selectCorrectOption messageSelectCorrectOption; \
        inputOption(currentLibrary); \
        return


#define CLEAR_STDIN char input; \
    while ((input = getchar()) != '\n' && input != EOF)


const u8 titleLength = (sizeof("TITLE") / sizeof(char)) - 1;
const u8 authorLength = (sizeof("AUTHOR") / sizeof(char)) - 1;
const u8 categoryLength = (sizeof("CATEGORY") / sizeof(char)) - 1;
const u8 maxIdLength = (u8)(floor(log10(abs(maxAmountOfBooks))) + 1);

typedef struct
{
    char title[maxStringLength];
    char author[maxStringLength];
    char category[maxStringLength];
    bool isEmpty;

} book;

typedef struct 
{
    char title[maxStringLength + fgetsAdder];
    char author[maxStringLength + fgetsAdder];
    char category[maxStringLength + fgetsAdder];
    i16 inputBookId;
    u8 inputTitleLength;
    u8 inputAuthorLength;
    u8 inputCategoryLength;
} inputBook;

typedef struct
{
    book books[maxAmountOfBooks];
    inputBook currentInputBook;
    u16 currentBooksAmount;
    u16 maxBookTitleLength;
    u16 maxBookAuthorLength;
    u16 maxBookCategoryLength;
    u16 edgeIdTitle;
    u16 edgeTitleAuthor;
    u16 edgeAuthorCategory;
} library;

bool isBookIdInBoundaries(i8 bookIdToCheck)
{
    if (bookIdToCheck < 0 || bookIdToCheck >= maxAmountOfBooks)
    {
        return false;
    }
    return true;
}

void copyString(char stringForCopy[], char stringToCopy[], u8 stringForCopyLength, u8 stringToCopyLength)
{
    if (stringForCopyLength >= stringToCopyLength)
    {
        for (u8 i = 0; i < stringForCopyLength; ++i)
        {
            stringForCopy[i] = stringToCopy[i];
        }
    } else
    {
        printf("Not enough place to copy!\n");
    }
}

int findStringLength(char stringFind[])
{
    int length = 0;
    while (stringFind[length] != '\0' && stringFind[length] != '\n') length++;
    return length;
}

bool in(char string[], u16 stringLength, char characterToCheck)
{
    for (u16 i = 0; i < stringLength; ++i)
    {
        if (characterToCheck == string[i])
        {
            return true;
        }
    }
    return false;
}

u8 typecastCharToDigit(char charToCast)
{
    return (u8)(charToCast - '0');
}

void printInstructions(void)
{
    printf("1. Add Book\n");
    printf("2. Display Books\n");
    printf("3. Search Book\n");
    printf("4. Delete Book\n");
    printf("5. Exit\n");
}

void startingGreeting(void)
{
    printf("Welcome to library management system!\n");
    printInstructions();

}


i16 findSlashNInString(char *string, u16 stringLength) 
{
    for (i16 i = 0; i < stringLength; ++i) 
    {
	if (string[i] == '\n') 
	{
	    return i;
	}
    }
    return -1;
}


i16 tryParseStringToInt(char *string, u16 stringLength)
{
    i16 parsedString = 0;
    for (u16 i = 0; i < stringLength; ++i) 
    {
	if (in("0123456789", 10, string[i]) == false) 
	{
	    return -1;
	}
	parsedString += typecastCharToDigit(string[i]) * (i8)round(pow(10, stringLength - 1 - i)); 

    }
    return parsedString;
}

void addBook(library *currentLibrary, i16 bookId, char bookTitle[], char bookAuthor[], char bookCategory[], u8 bookTitleLength, u8 bookAuthorLength, u8 bookCategoryLength)
{

    copyString(currentLibrary->books[bookId].title, bookTitle, maxStringLength, bookTitleLength); //currentLibrary->books[bookId].title = bookTitle
    copyString(currentLibrary->books[bookId].author, bookAuthor, maxStringLength, bookAuthorLength); //currentLibrary->books[bookId].author = bookAuthor
    copyString(currentLibrary->books[bookId].category, bookCategory, maxStringLength, bookCategoryLength); //currentLibrary->books[bookId].category = bookCategory
    printf("Book added successfully!\n");
    currentLibrary->books[bookId].isEmpty = false;
    currentLibrary->currentBooksAmount++; 
}

void searchBook(library *currentLibrary, i16 bookId) 
{
    if (currentLibrary->books[bookId].isEmpty == true) 
    {
	printf("There is no book on that ID!\n");
	return;
    }
    printf("Book ID: %d\n", bookId);
    printf("Title: %s\n", currentLibrary->books[bookId].title);
    printf("Author: %s\n", currentLibrary->books[bookId].author);
    printf("Category: %s\n", currentLibrary->books[bookId].category);
}

void printCharacterSpecificAmount(u16 amount, char characterToPrint)
{
    for (u16 i = 0; i < amount; i++)
    {
        printf("%c", characterToPrint);
    }
}

void findMaxBookValuesLength(library *currentLibrary)
{
    for (u16 i = 0; i < maxAmountOfBooks; ++i)
    {
        if (currentLibrary->books[i].isEmpty == false)
        {
            int lengthTitle = findStringLength(currentLibrary->books[i].title);
            int lengthAuthor = findStringLength(currentLibrary->books[i].author);
            int lengthCategory = findStringLength(currentLibrary->books[i].category);

            if (lengthTitle > currentLibrary->maxBookTitleLength)
            {
                currentLibrary->maxBookTitleLength = lengthTitle;
            }

            if (lengthAuthor > currentLibrary->maxBookAuthorLength)
            {
                currentLibrary->maxBookAuthorLength = lengthAuthor;
            }

            if (lengthCategory > currentLibrary->maxBookCategoryLength)
            {
                currentLibrary->maxBookCategoryLength = lengthCategory;
            }
        }

    }
}

void printCorrectAmountSpaces(i16 numToCheck)
{
    if (numToCheck >= 0)
    {
        printCharacterSpecificAmount(numToCheck, ' ');
    }
}

void addCorrectValueToFinal(i16 numToCheck, i16 otherNum, u16 *finalLength)
{
    if (numToCheck >= 0)
    {
        *finalLength += numToCheck + otherNum;
    } else
    {
        *finalLength += otherNum;
    }
}

void printCorrectSpacesId(u16 currentId) //PROBABLY HARDCODED WITH 2 SPACES BETWEEN COLUMNS
{
    if (currentId < 10)
    {
	printCorrectAmountSpaces(maxIdLength - 1);
    } else if (currentId < 100)
    {
	printCorrectAmountSpaces(maxIdLength - 2);
    } else if (currentId < 1000)
    {
	printCorrectAmountSpaces(maxIdLength - 3);
    }
    printf("%s", columnSeparator);
}

void printRowDashes(u16 amountToPrint, library *currentLibrary)
{
    for (u16 i = 0; i < amountToPrint; ++i)
    {
        if (i == currentLibrary->edgeIdTitle || i == currentLibrary->edgeTitleAuthor || i == currentLibrary->edgeAuthorCategory || i == amountToPrint - 1)
        {
            printf("|");
        } else
        {
            printf("-");
        }
    }
}

void findNewLibraryEdges(library *currentLibrary)
{
    currentLibrary->edgeIdTitle = maxIdLength + columnSeparatorLength - 1;
    currentLibrary->edgeTitleAuthor = maxIdLength + columnSeparatorLength - 1;
    currentLibrary->edgeAuthorCategory = 0;
 
    if (titleLength > currentLibrary->maxBookTitleLength)
    {
        currentLibrary->edgeTitleAuthor += titleLength;
    } else
    {
        currentLibrary->edgeTitleAuthor += currentLibrary->maxBookTitleLength;
    }
    currentLibrary->edgeTitleAuthor += columnSeparatorLength;

    currentLibrary->edgeAuthorCategory += currentLibrary->edgeTitleAuthor;
    if (authorLength > currentLibrary->maxBookAuthorLength)
    {
        currentLibrary->edgeAuthorCategory += authorLength;
    } else
    {
        currentLibrary->edgeAuthorCategory += currentLibrary->maxBookAuthorLength;
    }
    currentLibrary->edgeAuthorCategory += columnSeparatorLength;
}

void printBooksAlignment(library *currentLibrary)
{
    u16 finalTableLength = 0;
    printf("ID");
    printCorrectAmountSpaces(maxIdLength - 2);
    printf("%sTITLE", columnSeparator);
    finalTableLength += (maxIdLength + columnSeparatorLength + 5);
    findMaxBookValuesLength(currentLibrary);
    printCorrectAmountSpaces(currentLibrary->maxBookTitleLength - 5);
    addCorrectValueToFinal(currentLibrary->maxBookTitleLength - 5, columnSeparatorLength, &finalTableLength);

    printf("%sAUTHOR", columnSeparator);
    finalTableLength += authorLength;
    printCorrectAmountSpaces(currentLibrary->maxBookAuthorLength - 6);
    addCorrectValueToFinal(currentLibrary->maxBookAuthorLength - 6, columnSeparatorLength, &finalTableLength);

    printf("%sCATEGORY", columnSeparator);
    finalTableLength += categoryLength;
    printCorrectAmountSpaces(currentLibrary->maxBookCategoryLength - 8);
    addCorrectValueToFinal(currentLibrary->maxBookCategoryLength - 8, columnSeparatorLength, &finalTableLength);

    printf("%s", columnSeparator);
    printf("\n");
    //print line after id, title, author etc
    findNewLibraryEdges(currentLibrary);
    printRowDashes(finalTableLength, currentLibrary);
    printf("\n");
}


void printBooks(library *currentLibrary)
{
    if (currentLibrary->currentBooksAmount == 0) 
    {
	printf("There is no books in library! Add some!\n");
	return;
    }
    printBooksAlignment(currentLibrary);
    for (u16 i = 0; i < maxAmountOfBooks; ++i)
    {
        if (currentLibrary->books[i].isEmpty == false)
        {
            printf("%u", i + 1);
            printCorrectSpacesId(i);
            printf("%s", currentLibrary->books[i].title);
            u8 titleLength = (sizeof("TITLE") / sizeof(char)) - 1;
            if (currentLibrary->maxBookTitleLength > titleLength)
            {
                printCharacterSpecificAmount(currentLibrary->maxBookTitleLength - findStringLength(currentLibrary->books[i].title), ' ');
            } else
            {
                printCharacterSpecificAmount(titleLength - findStringLength(currentLibrary->books[i].title), ' ');
            }
            printf("%s", columnSeparator);
            printf("%s", currentLibrary->books[i].author);
            if (currentLibrary->maxBookAuthorLength > authorLength)
            {
                printCharacterSpecificAmount(currentLibrary->maxBookAuthorLength - findStringLength(currentLibrary->books[i].author), ' ');
            } else
            {
                printCharacterSpecificAmount(authorLength - findStringLength(currentLibrary->books[i].author), ' ');
            }
            printf("%s", columnSeparator);
            printf("%s", currentLibrary->books[i].category);
            if (currentLibrary->maxBookCategoryLength > categoryLength)
            {
                printCharacterSpecificAmount(currentLibrary->maxBookCategoryLength - findStringLength(currentLibrary->books[i].category), ' ');
            } else
            {
                printCharacterSpecificAmount(categoryLength - findStringLength(currentLibrary->books[i].category), ' ');
            }
            printf("%s", columnSeparator);
            printf("\n");
        }
    }



}

void inputId(library *currentLibrary)
{
    printf("Enter Book ID: ");
    char userInput;
    char idMembers[maxIdLength + fgetsAdder]; //+2 because \n and \0
    fgets(idMembers, maxIdLength + fgetsAdder, stdin);

    i16 slashNPos = findSlashNInString(idMembers, maxIdLength + fgetsAdder);
    if (slashNPos == -1) 
    {
	CLEAR_STDIN;
	selectCorrectId;
    }

    i16 bookId = tryParseStringToInt(idMembers, slashNPos);
    if (slashNPos == 0 || bookId == -1 || bookId == 0)
    {
	selectCorrectId;
    }
    bookId--;
   currentLibrary->currentInputBook.inputBookId = bookId;
    
    
}



void inputString(library *currentLibrary, u8 choosedInput) //1 - title, 2 - author, 3 - category 
{
    switch (choosedInput) 
    {
    case 1:
	printf("Enter Book Title (max %d symbols): ", maxStringLength);
	fgets(currentLibrary->currentInputBook.title, maxStringLength + fgetsAdder, stdin);
	break;
    case 2:
	printf("Enter Book Author (max %d symbols): ", maxStringLength);
	fgets(currentLibrary->currentInputBook.author, maxStringLength + fgetsAdder, stdin);
	break;
    case 3:
	printf("Enter Book Category (max %d symbols): ", maxStringLength);
	fgets(currentLibrary->currentInputBook.category, maxStringLength + fgetsAdder, stdin);
	break;
    }


    i16 slashNPos;
    switch (choosedInput) 
    {
    case 1:
	slashNPos = findSlashNInString(currentLibrary->currentInputBook.title, maxStringLength + fgetsAdder);
	break;
    case 2:
	slashNPos = findSlashNInString(currentLibrary->currentInputBook.author, maxStringLength + fgetsAdder);
	break;
    case 3:
	slashNPos = findSlashNInString(currentLibrary->currentInputBook.category, maxStringLength + fgetsAdder);
	break;
    }
    if (slashNPos == 0) 
    {
	switch (choosedInput) 
	{
	case 1:
	    printf("Enter correct book title!\n");
	    break;
	case 2:
	    printf("Enter correct book author!\n");
	    break;
	case 3:
	    printf("Enter correct book category!\n");
	    break;
	}
	inputString(currentLibrary, choosedInput);
	return;
    }

    if (slashNPos == -1) 
    {
	switch (choosedInput) 
	{
	case 1:
	    printf("Enter correct book title (max %d symbols)!\n", maxStringLength);
	    break;
	case 2:
	    printf("Enter correct book author (max %d symbols)!\n", maxStringLength);
	    break;
	case 3:
	    printf("Enter correct book category (max %d symbols)!\n", maxStringLength);
	    break;
	}
	CLEAR_STDIN;
	inputString(currentLibrary, choosedInput);
	return;
    }
    switch (choosedInput) 
    {
    case 1:
	currentLibrary->currentInputBook.inputTitleLength = findStringLength(currentLibrary->currentInputBook.title);
	currentLibrary->currentInputBook.title[slashNPos] = '\0';
	break;
    case 2:
	currentLibrary->currentInputBook.inputAuthorLength = findStringLength(currentLibrary->currentInputBook.author);
	currentLibrary->currentInputBook.author[slashNPos] = '\0';
	break;
    case 3:
	currentLibrary->currentInputBook.inputCategoryLength = findStringLength(currentLibrary->currentInputBook.category);
	currentLibrary->currentInputBook.category[slashNPos] = '\0';
	break;
    }

}

void inputBookValues(library *currentLibrary) 
{
    inputId(currentLibrary);
    if (currentLibrary->books[currentLibrary->currentInputBook.inputBookId].isEmpty == false) 
    {
	printf("There is a book on that ID!\n");
	inputBookValues(currentLibrary);
	return;
    }
 
    inputString(currentLibrary, 1);
    inputString(currentLibrary, 2);
    inputString(currentLibrary, 3);
}

void inputOption(library *currentLibrary)
{
    printf("Enter option (1-5): ");
    char userBuffer[3]; //HARDCODED!
    fgets(userBuffer, 3, stdin);
    if (userBuffer[0] == '\n' || in("12345", 5, userBuffer[0]) == false)
    {
	selectCorrectOption;
    }
    if (userBuffer[1] != '\n')
    {
        CLEAR_STDIN;
	selectCorrectOption;
    }

    switch (userBuffer[0])
    {
    case '1':
	if (currentLibrary->currentBooksAmount == maxAmountOfBooks)
	{
	    printf("Library is already full!\n");
	    break;
	}
	inputBookValues(currentLibrary);
	addBook(currentLibrary, currentLibrary->currentInputBook.inputBookId, currentLibrary->currentInputBook.title, currentLibrary->currentInputBook.author, currentLibrary->currentInputBook.category, currentLibrary->currentInputBook.inputTitleLength, currentLibrary->currentInputBook.inputAuthorLength, currentLibrary->currentInputBook.inputCategoryLength);
        break;
    case '2':
	printBooks(currentLibrary);
        break;
    case '3':
	inputId(currentLibrary);
	searchBook(currentLibrary, currentLibrary->currentInputBook.inputBookId);
        break;
    case '4':
	
        break;
    case '5':
	exit(0);
    }
}

void deleteBook(library *currentLibrary, i16 bookId) 
{
    currentLibrary->books[bookId].isEmpty = true;
    currentLibrary->currentBooksAmount++;
}

int main(void)
{
    //initializing variables
    library mainLibrary;
    mainLibrary.currentBooksAmount = 0;
    mainLibrary.maxBookTitleLength = 0;
    mainLibrary.maxBookAuthorLength = 0;
    mainLibrary.maxBookCategoryLength = 0;
    mainLibrary.edgeIdTitle = maxIdLength + columnSeparatorLength - 1;
    mainLibrary.edgeTitleAuthor = maxIdLength + columnSeparatorLength - 1;
    mainLibrary.edgeAuthorCategory = 0;
    for (u16 i = 0; i < maxAmountOfBooks; ++i)
    {
        mainLibrary.books[i].isEmpty = true;
    }
    startingGreeting();
    while (1) 
    {
	inputOption(&mainLibrary);
    }

    //IN INPUT THE ID VALUE WILL GET DICREMENT: e.g. "ENTER BOOK ID (1-100)" WILL OUTPUT ONLY 0-99 values!
    // there is no matter for any input from user, because program only reads first character (and some concrete other)!
    //addBook(&mainLibrary, 1, "testBook", "me", "sci-fi", (sizeof("testbook") / sizeof(char)), (sizeof("me") / sizeof(char)), (sizeof("sci-fi") / sizeof(char)));
    //addBook(&mainLibrary, 30, "anotherTestBook", "director", "psychological", (sizeof("anotherTestBook") / sizeof(char)), (sizeof("director") / sizeof(char)), (sizeof("psychological") / sizeof(char)));
    //addBook(&mainLibrary, 73, "anotheranotherBook", "person", "drama", (sizeof("anotheranotherBook") / sizeof(char)), (sizeof("person") / sizeof(char)), (sizeof("drama") / sizeof(char)));
    //addBook(&mainLibrary, 35, "someBook", "people", "comedy", (sizeof("someBook") / sizeof(char)), (sizeof("people") / sizeof(char)), (sizeof("comedy") / sizeof(char)));

    return 0;
}
