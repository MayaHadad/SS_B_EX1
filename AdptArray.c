#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;




PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc=printFunc_;
	return pArr;
}

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; i++)
	{
        if((pArr->pElemArr)[i])
		    pArr->delFunc((pArr->pElemArr)[i]);
	}
	free(pArr->pElemArr);
	free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	if (pArr == NULL)
		return FAIL;

    // Extend Array
    if (idx >= pArr->ArrSize){
        PElement* newElemArr = (PElement*)realloc(pArr->pElemArr, (idx + 1) * sizeof(PElement));
        if (newElemArr == NULL) {
            return FAIL;
        }
        pArr->pElemArr = newElemArr;
        // set the newly allocated elements to NULL
        memset(pArr->pElemArr + pArr->ArrSize, 0, (idx + 1 - pArr->ArrSize) * sizeof(PElement));
        pArr->ArrSize = idx + 1;
    }
	
    // Delete Previous Elem
    if (pArr->pElemArr[idx]){
        pArr->delFunc(pArr->pElemArr[idx]);
    }
	pArr->pElemArr[idx] = pArr->copyFunc(pNewElem);
	return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int index){
    if (pArr==NULL || index>=pArr->ArrSize)
        return NULL;

    if (pArr->pElemArr[index])
        return pArr->copyFunc(pArr->pElemArr[index]);
    
    return NULL;
}

int GetAdptArraySize(PAdptArray pArr){
    if (pArr==NULL)
        return FAIL;
    return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr){
    if (pArr==NULL)
        return;
    
    for (int i = 0; i < pArr->ArrSize; i++)
    {
        if (pArr->pElemArr[i])
            pArr->printFunc(pArr->pElemArr[i]);
    }
}


