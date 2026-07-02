#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>


typedef int8_t i8;
typedef uint8_t u8;
typedef uint16_t u16;
typedef int16_t i16;




#define maxAmountOfBooks 100
#define maxStringLength 30
#define columnSeparator " |"
#define columnSeparatorLength (sizeof(columnSeparator) / sizeof(char)) - 1
#define edgeID_TITLE 3 + columnSeparatorLength
#define edgeTITLE_AUTHOR(currentLibrary) edgeID_TITLE + (titleLength > (currentLibrary)->maxBookTitleLength) ? titleLength : (currentLibrary)->maxBookTitleLength + columnSeparatorLength
#define edgeAUTHOR_CATEGORY(currentLibrary) edgeTITLE_AUTHOR((currentLibrary)) + (authorLength > (currentLibrary)->maxBookAuthorLength) ? authorLength : (currentLibrary)->maxBookAuthorLength + columnSeparatorLength

#define CLEAR_STDIN char input; \
    while ((input = getchar()) != '\n' && input != EOF)

#define messageSelectCorrectOption printf("Select correct option (1-5)!\n")

const u8 titleLength = (sizeof("TITLE") / sizeof(char)) - 1;
const u8 authorLength = (sizeof("AUTHOR") / sizeof(char)) - 1;
const u8 categoryLength = (sizeof("CATEGORY") / sizeof(char)) - 1;
const u8 maxIdLength = (u8)(floor(log10(abs(maxAmountOfBooks))) + 1);

typedef struct
{
    bool isEmpty;
    char title[maxStringLength];
    char author[maxStringLength];
    char category[maxStringLength];

} book;

typedef struct
{
    int currentBooksAmount;
    book books[maxAmountOfBooks];
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

bool isLibraryFull(library *currentLibrary)
{
    if (currentLibrary->currentBooksAmount == maxAmountOfBooks)
    {
        return true;
    }
    return false;
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
    while (stringFind[length] != '\0') length++;
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

u8 typecastCharToInt(char charToCast)
{
    return (u8)(charToCast - '0');
}

void printInstructions()
{
    printf("1. Add Book\n");
    printf("2. Display Books\n");
    printf("3. Search Book\n");
    printf("4. Delete Book\n");
    printf("5. Exit\n");
}

void startingGreeting()
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

void inputId(library *currentLibrary)
{
    printf("Enter book ID: ");
    char userInput;
    char idMembers[maxIdLength + 2]; //+2 because \n and \0
    fgets(idMembers, maxIdLength + 2, stdin);
    for (i16 i = 0; i < maxIdLength + 2; ++i) 
    {
        printf("%d\n", idMembers[i]);
    }
    /*
    while ((userInput = getchar()) != '\n')
    {
        if (charactersCounter > maxIdLength || in("123456789", 9, userInput) == false)
        {
            printf("Select correct id (1-%d)!\n", maxAmountOfBooks);
            CLEAR_STDIN;
            inputId(currentLibrary);
            return;
        }
        idMembers[charactersCounter] = userInput;
        charactersCounter++;
    }
    */
    i16 slashNPos = findSlashNInString(idMembers, maxIdLength + 1);
    if (slashNPos == -1) 
    {
	    printf("Select correct id (1-%d)!\n", maxAmountOfBooks);
	    CLEAR_STDIN;
	    inputId(currentLibrary);
	    return;
    }

    if (slashNPos == 0) 
    {
	    printf("Select correct id (1-%d)!\n", maxAmountOfBooks);
	    inputId(currentLibrary);
	    return;
    }


    switch (slashNPos)
    {
    case 1:
        printf("%d", typecastCharToInt(idMembers[0])); //WORKED CORRECTLY, BUT NEED TO USE THIS ID
        break;
    case 2: //SIMILAR TO CASE 1 BUT idMembers[0] AFTER CAST NEED TO MUPTILY BY 10 (*10)
        break;
    case 3: //SIMILAR TO CASE 1 BUT idMembers[0] AFTER CAST NEED TO MUPTILY BY 10 (*100) AND idMembers[1] * 10
        break;
    }

   /* 
    if (isLibraryFull(currentLibrary))
    {
        printf("Library is already full!\n");
        return;
    }

    if (isBookIdInBoundaries(bookId) == false)
    {
        printf("Incorrect book id!\n");
        return;
    }

    if (currentLibrary->books[bookId].isEmpty == false)
    {
        printf("Place on this id is not empty!\n");
        return;
    }
    */
}

void inputOption(library *currentLibrary)
{
    printf("Enter option (1-5): ");
    char userBuffer[3]; //HARDCODED!
    fgets(userBuffer, 3, stdin);
    if (userBuffer[0] == '\n')
    {
        messageSelectCorrectOption;
        inputOption(currentLibrary);
        return;
    }
    if (userBuffer[1] != '\n')
    {
        messageSelectCorrectOption;
        CLEAR_STDIN;
        inputOption(currentLibrary);
        return;
    }
    if (in("12345", 5, userBuffer[0]) == false)
    {
        messageSelectCorrectOption;
        inputOption(currentLibrary);
        return;
    }

    switch (userBuffer[0])
    {
    case '1':
        inputId(currentLibrary);
        break;
    case '2':
        break;
    case '3':
        break;
    case '4':
        break;
    case '5':
        break;

    }
}

void printCharacterSpecificAmount(u16 amount, char characterToPrint)
{
    for (u16 i = 0; i < amount; i++)
    {
        printf("%c", characterToPrint);
    }
}

void addBook(library *currentLibrary, i8 bookId, char bookTitle[], char bookAuthor[], char bookCategory[], u8 bookTitleLength, u8 bookAuthorLength, u8 bookCategoryLength)
{


    copyString(currentLibrary->books[bookId].author, bookAuthor, maxStringLength, bookAuthorLength); //currentLibrary->books[bookId].author = bookAuthor
    copyString(currentLibrary->books[bookId].title, bookTitle, maxStringLength, bookTitleLength); //currentLibrary->books[bookId].author = bookAuthor
    copyString(currentLibrary->books[bookId].category, bookCategory, maxStringLength, bookCategoryLength); //currentLibrary->books[bookId].author = bookAuthor
    currentLibrary->books[bookId].isEmpty = false;
    currentLibrary->currentBooksAmount--; // and there will be another function deleteBook, which will increment this value
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
        *finalLength += numToCheck;
    } else
    {
        *finalLength += otherNum;
    }
}

void printCorrectSpacesId(u16 currentId) //PROBABLY HARDCODED WITH 2 SPACES BETWEEN COLUMNS
{
    if (currentId < 10)
    {
        printf("  %s", columnSeparator);
    } else if (currentId < 100)
    {
        printf(" %s", columnSeparator);
    } else
    {
        printf(" |");
    }
}

void printRowDashes(u16 amountToPrint, library *currentLibrary)
{
    for (u16 i = 0; i < amountToPrint; ++i)
    {
        if (i == currentLibrary->edgeIdTitle || i == currentLibrary->edgeTitleAuthor || i == currentLibrary->edgeAuthorCategory)
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
    printf("ID %sTITLE", columnSeparator);
    finalTableLength += (3 + columnSeparatorLength + 5);
    findMaxBookValuesLength(currentLibrary);
    printCorrectAmountSpaces(currentLibrary->maxBookTitleLength - 5);
    addCorrectValueToFinal(currentLibrary->maxBookTitleLength - 5, columnSeparatorLength, &finalTableLength);
    printf("%sAUTHOR", columnSeparator);
    finalTableLength += (columnSeparatorLength + authorLength);
    printCorrectAmountSpaces(currentLibrary->maxBookAuthorLength - 6);
    addCorrectValueToFinal(currentLibrary->maxBookAuthorLength - 6, columnSeparatorLength, &finalTableLength);
    printf("%sCATEGORY", columnSeparator);
    finalTableLength += (columnSeparatorLength + categoryLength);
    printCorrectAmountSpaces(currentLibrary->maxBookCategoryLength - 8);
    addCorrectValueToFinal(currentLibrary->maxBookCategoryLength - 8, columnSeparatorLength, &finalTableLength);
    printf("%s", columnSeparator);
    printf("\n");
    finalTableLength++;
    findNewLibraryEdges(currentLibrary);
    printRowDashes(finalTableLength, currentLibrary);
    printf("|");
    printf("\n");
}

void printBooks(library *currentLibrary)
{
    printBooksAlignment(currentLibrary);
    for (u16 i = 0; i < maxAmountOfBooks; ++i)
    {
        if (currentLibrary->books[i].isEmpty == false)
        {
            printf("%u", i);
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




int main()
{
    //initializing variables
    library mainLibrary;
    mainLibrary.currentBooksAmount = 0;
    mainLibrary.maxBookTitleLength = 0;
    mainLibrary.maxBookAuthorLength = 0;
    mainLibrary.maxBookCategoryLength = 0;
    mainLibrary.edgeIdTitle = 3 + columnSeparatorLength - 1;
    mainLibrary.edgeTitleAuthor = 3 + columnSeparatorLength - 1;
    mainLibrary.edgeAuthorCategory = 0;
    for (u16 i = 0; i < maxAmountOfBooks; ++i)
    {
        mainLibrary.books[i].isEmpty = true;
    }
    startingGreeting();
    inputOption(&mainLibrary);
    //IN INPUT THE ID VALUE WILL GET DICREMENT: e.g. "ENTER BOOK ID (1-100)" WILL OUTPUT ONLY 0-99 values!
    // there is no matter for any input from user, because program only reads first character (and some concrete other)!
    addBook(&mainLibrary, 1, "testBook", "me", "sci-fi", (sizeof("testbook") / sizeof(char)), (sizeof("me") / sizeof(char)), (sizeof("sci-fi") / sizeof(char)));
    addBook(&mainLibrary, 30, "anotherTestBook", "director", "psychological", (sizeof("anotherTestBook") / sizeof(char)), (sizeof("director") / sizeof(char)), (sizeof("psychological") / sizeof(char)));
    addBook(&mainLibrary, 73, "anotheranotherBook", "person", "drama", (sizeof("anotheranotherBook") / sizeof(char)), (sizeof("person") / sizeof(char)), (sizeof("drama") / sizeof(char)));
    addBook(&mainLibrary, 35, "someBook", "people", "comedy", (sizeof("someBook") / sizeof(char)), (sizeof("people") / sizeof(char)), (sizeof("comedy") / sizeof(char)));

    printBooks(&mainLibrary);



    return 0;
}
