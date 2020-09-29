// ToDo: реализовать ввод вывод в файлы по аргументу cmd
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <sys\stat.h>
#include <cctype>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#define DBG if(0)

const char INPUT[]    = "input.txt";
const char SOUTPUT[]  = "straight_output.txt";
const char ROUTPUT[]  = "reverse_output.txt";
const char FULLTEXT[] = "full_text.txt";

//TODO починить я

struct String
{
    char* chLine;
    int length;
};

//!---------------------------------------------------
//! gets size of file in bytes
//!
//! @param [in] fileName-name of file or filepath
//!
//! @return size of file in bytes
//!
//! @note size of file in bytes often is bigger than
//!       number of char symbols in file
//!----------------------------------------------------

int getFileSize (const char* fileName);

//!-------------------------------------------------------
//!         reads data from file to storage
//!
//! @param  [in] fileName-name of file or filepath
//!
//! @return storage consisting data from file
//!
//! @note   returns string that is not normal for c
//!         format of string is
//!-------------------------------------------------------

char* readToStorage (const char* fileName);

//!---------------------------------------------------------------------------
//!         counts number of input symbols in input string
//!
//! @param  [in] storage-buffer consisting string
//! @param  [in] symb-symbol which we find
//!
//! @return number of string
//!
//!---------------------------------------------------------------------------

int countSymb (const char* storage,const char symb);

//!---------------------------------------------------------------------------
//!         deletes every double symbol from input and returns size of new storage without double symb;
//!
//! @param  [in] storage-buffer consisting string
//! @param  [in] symb-symbol which we want to delete
//!
//! @return size of new storage without double symb;
//!
//!---------------------------------------------------------------------------

int deleteDoubleSymb (const char* storage,const char symb);

//!---------------------------------------------------------------------------
//!         deletes every double symbol from input and returns size of new storage without double symb;
//!
//! @param  [in] storage-buffer consisting string
//! @param  [in] symb-symbol which we want to delete
//!
//! @return size of new storage without double symb;
//!
//!---------------------------------------------------------------------------

int deleteSymb (const char* storage,const char symb);

//!--------------------------------------------------------------------------
//!         converts sting to array of Strings
//!
//! @param  [in] storage buffer consisting string
//!
//! @param  [in] nStr    number of string
//!
//! @return array of Strings
//!
//!---------------------------------------------------------------------------

struct String* makeText (const char* storage, const int nStr);

//!---------------------------------------------------------------------------
//!         compares strings from beginning
//!
//! @param  [in] str1 first string
//! @param  [in] str2 second string
//!
//! @return negative number if str1 <  str2
//!         positive number if str1 >  str2
//!         zero            if str1 == str2
//!---------------------------------------------------------------------------

int strCompareStraight (const char* str1, const char* str2);

//!---------------------------------------------------------------------------
//!         compares strings from ending
//!
//! @param  [in] str1 first string
//! @param  [in] str2 second string
//!
//! @return negative number if str1 <  str2
//!         positive number if str1 >  str2
//!         zero            if str1 == str2
//!---------------------------------------------------------------------------

int strCompareReverse (const struct String* str1, const struct String* str2);

//!---------------------------------------------------------------------------
//!         comparator for sorting using strCompareStraight
//!
//! @param  [in] first  member for comparing
//! @param  [in] second member for comparing
//!
//! @return negative number if str1 <  str2
//!         positive number if str1 >  str2
//!         zero            if str1 == str2
//!----------------------------------------------------------------------------

int straightComparator (const void* member1, const void* member2);

//!---------------------------------------------------------------------------
//!         comparator for sorting using strCompareReverse
//!
//! @param  [in] first  member for comparing
//! @param  [in] second member for comparing
//!
//! @return negative number if str1 <  str2
//!         positive number if str1 >  str2
//!         zero            if str1 == str2
//!---------------------------------------------------------------------------

int reverseComporator  (const void* member1, const void* member2);

//!--------------------------------------------------------------------------
//!        writes text from storage to file
//!
//! @param [in] storage buffer with text
//! @param [in] nStr number of strings in buffer
//! @param [in] fileName name of file where text will be written
//!
//!--------------------------------------------------------------------------

void storageOutput (const char* storage, const int nCh, const char* fileName);

//!--------------------------------------------------------------------------
//!        writes text from text to file from beginning of every string
//!
//! @param [in] text array of strings
//! @param [in] nCh number of strings in buffer
//! @param [in] fileName name of file where text will be written
//!
//!--------------------------------------------------------------------------

void textOutputStraight (struct String* text,const int nStr, const char* fileName);

//!--------------------------------------------------------------------------
//!        writes text from text to file from ending of every string
//!
//! @param [in] text array of strings
//! @param [in] nStr number of strings in buffer
//! @param [in] fileName name of file where text will be written
//!
//!--------------------------------------------------------------------------

void textOutputReverse  (struct String* text,const int nStr, const char* fileName);

//!-----------------------------------------------------------------------------------
//!         reads string from file and deletes every '\r' and double '\n' from it
//!
//! @param [in] fileName-name of file  from which we read
//!
//! @return pointer ti char which is string we read
//!------------------------------------------------------------------------------------

char* prepareStorage (const char* fileName, int* nCh, int* nStr);

//!-----------------------------------------------------------------------------------------
//!        sorts array of Strings
//! @param [in] text-pointer to string array
//! @param [in] beg-beginning index
//! @param [in] en-ending index
//!-----------------------------------------------------------------------------------------------

void quickSort (struct String* text, int beg, int en, int (*compare) (const void *, const void *));

//!-------------------------------------------------------------------------------------
//!        swaps strings
//! @param [in] text-array of Strings
//! @param [in] l-left index
//! @param [in] f-right index
//!--------------------------------------------------------------------------------------

void sw (struct String* text, int l, int r);

//!--------------------------------------------------------------------------------------
//! gets strings which are filenames
//!
//! @param args - number of arguments
//! @param argv - array of strings
//! @param finput - pointer to input file
//! @param fsoutput - pointer to output file with straight sorting
//! @param froutput - pointer to output file with reverse sorting
//! @param fstorage - pointer to output file with text
//!
//!---------------------------------------------------------------------------------------

void getFileNames (int args, char* argv[], char** finput, char** fsoutput, char** froutput, char** fstorage);

int myisalpha (char symb);

//!-----------------------------------------------
//! unit tests
//!-----------------------------------------------

void testGetFileSize (const char* fileName, const int exampleSize, int testN);
void testReadToStorage (const char* fileName, const char* exampleStr, int nTest);
void testStrCompareStraight (const char* str1, const char* str2, int res, int nTest);
void testStrCompareReverse (const struct String* str1, const struct String* str2, int res, int nTest);
void testQuickSort (struct String* text, int beg, int en, int (*compare) (const void *, const void *), struct String* example, int nTest);
void tests();

int main(int argc, char *argv[])
{

    setlocale (LC_ALL, "Russian");

    char* finput   = "";
    char* fsoutput = "";
    char* froutput = "";
    char* fstorage = "";

    tests();

    getFileNames ( argc, argv, &finput, &fsoutput, &froutput, &fstorage);

    int nCh = 0, nStr = 0;

    char* storage = prepareStorage ((const char*)finput, &nCh, &nStr);

    struct String* text = makeText (storage, nStr);

    qsort (text, nStr, sizeof(struct String), straightComparator );

    textOutputStraight (text, nStr, fsoutput);

    printf("%s", fsoutput);

    //qsort (text, nStr, sizeof(struct String), reverseComporator );

    quickSort (text, 0, nStr - 1, reverseComporator);

    textOutputStraight (text, nStr, froutput);

    storageOutput (storage, nCh, fstorage);

    free (storage);
    free (text);

    return 0;
}

//---------------------------------------------------------------------

int getFileSize (const char* fileName)
{
    assert (fileName != NULL);

    struct stat buff = {};
    stat( fileName, &buff);
    return buff.st_size;

}

//----------------------------------------------------------------------

char* readToStorage (const char* fileName)
{
    assert (fileName != NULL);

    FILE* input = fopen (fileName, "rt");

    int fileSz = getFileSize(fileName);
    char* buffer   = (char*) calloc (fileSz + 2 , sizeof (*buffer));

    int nCh = fread (buffer, sizeof(char), fileSz, input);
    *(buffer + nCh) = '\n';
    *(buffer + nCh + 1) = '\0';

    fclose(input);

    return buffer;
}

//------------------------------------------------------------------------

int countSymb (const char* storage, const char symb)
{

    assert (storage != NULL);

    int nStr = 0;

    int ind = -1;

    char* pointerToSymb = NULL;
    while ( (pointerToSymb = strchr(storage + ind + 1, symb))!= NULL)
    {
        nStr++;
        ind = pointerToSymb - storage;
    }
    return nStr;

}

//-------------------------------------------------------------------------

int deleteDoubleSymb (const char* storage, const char symb)
{
    assert (storage != NULL);

    char* read  = (char*) storage;
    char* write = (char*) storage;
    int nSymb = 0;

    if (symb == '\0')
        while (*read != '\0')
            nSymb++;

    else

        while (*read != '\0')
        {

            while (*read == symb && *(read+1) == symb )
                read++;

            *write++ = *read++;
            nSymb++;

        }

        *write = '\0';

    return nSymb;
}

//------------------------------------------------------------------------

int deleteSymb (const char* storage,const char symb)
{
    assert (storage != NULL);

    char* read  = (char*) storage;
    char* write = (char*) storage;
    int nSymb = 0;

    if (symb == '\0')
        while (*read != '\0')
            nSymb++;

    else

        while (*read != '\0')
        {

            while (*read == symb)
                read++;

            *write++ = *read++;
            nSymb++;

        }
        *write = '\0';

    return nSymb + 1;
}


//-------------------------------------------------------------------------

int strCompareStraight (const char* str1, const char* str2)
{
    assert (str1 != NULL);
    assert (str2 != NULL);

    const char* read1 = str1;
    const char* read2 = str2;

    while (1)
    {
        while (!(isalpha(*(read1))) && (*(read1) != '\n') && !(isspace(*read1)))
            read1++;

        while (!(isalpha(*(read2))) && (*(read2) != '\n') && !(isspace(*read2)))
            read2++;

        unsigned char tempSymb1 = (unsigned char) tolower (*read1);
        unsigned char tempSymb2 = (unsigned char) tolower (*read2);

        if (tempSymb1 == '\n' || tempSymb2 == '\n')
            return tempSymb1 - tempSymb2;

        if ((tempSymb1) == (tempSymb2))
        {
            read1++;
            read2++;
            continue;
        }

        return tempSymb1 - tempSymb2;

    }
}

//-------------------------------------------------------------------------------------

int strCompareReverse (const String* str1, const String* str2)
{

    assert (str1 != NULL);
    assert (str2 != NULL);

    int nCh1 = str1->length;
    int nCh2 = str2->length;
    const char* read1 = str1->chLine + nCh1 - 1;
    const char* read2 = str2->chLine + nCh2 - 1;


    while (1)
    {
        while (!(isalpha(*(read1))) && (nCh1 > 1) && !(isspace(*read1)))
        {
            read1--;
            nCh1--;
        }

        while (!(isalpha(*(read2))) && (nCh2 > 1) && !(isspace(*read2)))
        {
            read2--;
            nCh2--;
        }

        unsigned char tempSymb1 = (unsigned char) tolower (*read1);
        unsigned char tempSymb2 = (unsigned char) tolower (*read2);

        if ((nCh1 == 1) || (nCh2 == 1))
            return tempSymb1 - tempSymb2;

        if ((tempSymb1) == (tempSymb2))
        {
            read1--;
            read2--;
            continue;
        }

        return tempSymb1 - tempSymb2;

    }
}

//-----------------------------------------------------

struct String* makeText (const char* storage, const int nStr)
{

    assert (storage != NULL);

    char*  read  = (char*) storage;
    //printf("%s",read);
    struct String* tempText   = (struct String*) calloc (nStr, sizeof(*tempText));

    struct String* returnText = tempText;

    int nChInStr = 0;


    while (*read != '\0')
    {

        if (*read == '\n')
        {

            tempText->chLine = read - nChInStr ;
            tempText->length = nChInStr + 1;
            tempText++;
            nChInStr = -1;

        }


        nChInStr++;
        read++;

    }
    return returnText;
}

//---------------------------------------------------------------------------------------------

int straightComparator (const void* member1, const void* member2)
{
    assert (member1 != NULL);
    assert (member2 != NULL);

    return strCompareStraight (((struct String*) member1)->chLine, ((struct String*) member2)->chLine);
}

//----------------------------------------------------------------------------------------------

int reverseComporator  (const void* member1, const void* member2)
{
    assert (member1 != NULL);
    assert (member2 != NULL);

    return strCompareReverse ((struct String*) member1, (struct String*) member2);
}

//------------------------------------------------------------------------------------------------

void storageOutput (const char* storage, const int nCh, const char* fileName)
{
    assert (storage != NULL);
    assert (fileName != NULL);

    FILE* output = fopen (fileName, "wb");

    fwrite (storage, sizeof(char), nCh, output);

    fclose (output);
}

//--------------------------------------------------------------------------------------------------

void textOutputStraight (struct String* text, const int nStr, const char* fileName)
{
    assert (text != NULL);
    assert (fileName != NULL);

    FILE* output = fopen (fileName, "wb");
    struct String* tempText = text;

    for( int i = 0; i < nStr; i++)
    {
        char* temp = tempText->chLine;
        fwrite (tempText->chLine, sizeof(char), tempText->length, output);
        tempText++;
    }
    fclose (output);
}

//---------------------------------------------------------------------------------------------------

char* prepareStorage (const char* fileName, int* nCh, int* nStr)
{
    assert (fileName != NULL);

    char* storage = readToStorage (fileName);
    //deleteSymb (storage, '\r');
    *nCh = deleteDoubleSymb (storage, '\n');
    *nStr = countSymb (storage, '\n');
    return storage;
}

//------------------------------------------------------------------------------------------------------

void testGetFileSize (const char* fileName, const int exampleSize, int testN)
{
    int Sz = getFileSize (fileName);
    (exampleSize == Sz) ? :
        printf ("test number %d:read of file failed\n", testN);
}

//----------------------------------------------------------------------

void sw (struct String* text, int l, int r) {

    assert (text);
    struct String t = text[l];
    text[l] = text[r];
    text[r] = t;
}

//-----------------------------------------------------------------------

void quickSort(String v[], int left, int right, int (*compare) (const void *, const void *))
{
    assert (v);

    if (left >= right)
        return;

    sw (v, left, (left+right)/2);
    int last = left;

    for(int i = left + 1; i <= right; i++)

        if (compare(v + i, v + left) < 0)
            sw (v, ++last, i);

    sw (v, left, last);

    quickSort (v, left    , last - 1, compare);
    quickSort (v, last + 1, right   , compare);
}

//----------------------------------------------------------------------------------------

void testReadToStorage (const char* fileName, const char* exampleStr, int nTest)
{
    (!strcmp(readToStorage (fileName), exampleStr)) ? :
        printf ("reading failed test number: %d\n", nTest);
}

//-----------------------------------------------------------------------------------------

void testStrCompareStraight (const char* str1, const char* str2, int res, int nTest)
{
    int res1 = strCompareStraight (str1, str2);
    if (res1 != 0)
        res1 = res1 / abs (res1);
    (!(res1 - res) ) ? :
        printf ("compairing failed test number: %d\n", nTest);
}

//-------------------------------------------------------------------------------------------

void testStrCompareReverse (const struct String* str1, const struct String* str2, int res, int nTest)
{
    int res1 = strCompareReverse(str1, str2);
    if (res1 != 0)
        res1 = res1 / abs (res1);
    (!(res1 - res) ) ? :
        printf ("compairing failed test number: %d\n", nTest);
}

//-------------------------------------------------------------------------------------------------

void testQuickSort (struct String* text, int beg, int en, int (*compare) (const void *, const void *), struct String* exampleText, int nTest)
{
    quickSort (text, beg, en, compare);
    int i = beg;

    while (compare(text + i,exampleText + i))
        i++;

    (!(i-en - 1) ) ? :
        printf ("sorting failed test number: %d\n", nTest);
}

//-----------------------------------------------------------------------------------------------

void getFileNames (int args, char* argv[], char** finput, char** fsoutput, char** froutput, char** fstorage)
{
    if (args >= 2)
        *finput = argv[1];
    else
        *finput = (char*) INPUT;

    if (args >= 3)
        *fsoutput = argv[2];
    else
        *fsoutput = (char*) SOUTPUT;

    if (args >= 4)
        *froutput = argv[3];
    else
        *froutput = (char*) ROUTPUT;

    if (args >= 5)
        *fstorage = argv[4];
    else
        *fstorage = (char*) FULLTEXT;


}

//-------------------------------------------------------------------------------

int myisalpha (char symb)
{
    return (tolower(symb) != 'я') ? isalpha (symb) : 1;
}

void tests()
{
    testGetFileSize( "ex1.txt",3 ,1);
    testGetFileSize( "ex2.txt",7 ,2);
    testGetFileSize( "ex3.txt",10,3);

    testReadToStorage( "ex1.txt", "aaa\n",4);
    testReadToStorage( "ex2.txt", "aaa\naa\n",5);

    testStrCompareStraight ("aaaa" ,"abaa", -1, 6);
    testStrCompareStraight ("aaa a c","aaaa",  -1, 7);

}
