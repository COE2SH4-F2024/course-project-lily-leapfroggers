#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
/*
• Initialize the sizeArray and sizeList data members.
• Allocate an array on the heap with the size specified by sizeArray.
• The default sizeArray is 200. You may change it as needed.
*/    

    arrayCapacity = 200;
    listSize = 0;
    aList = new objPos[arrayCapacity];

}

objPosArrayList::~objPosArrayList()
{
/*
• Deallocate all heap data members
• Defense against memory leakage
*/

    delete[] aList;
}

int objPosArrayList::getSize() const
{
/*
▪ Returns the size of the list (i.e. sizeList)
▪ NOT the sizeArray (Array Capacity!!)
*/
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
/*
Inserting thisPos as a new objPos element to the head of the list
▪ Do you need to “shift” the elements? Think about it.
*/

    if(listSize == arrayCapacity)
    {
        //("Array is Full");
        return;
    }

    // Shifting/Pushing all elements back by one slot
    // Overwriting the value in i+1 position with that in i position
    for(int i=listSize; i>0; i--)
    {
        aList[i] = aList[i-1]; // Shifting all elements towards the tail to create space at the head
    }
    // aList[0] is ready to be OVERWRITTEN by incoming value

    aList[0] = thisPos; // Inserting the element at the head, index: 0
    listSize++;     // Increase the size of the List by one
}

void objPosArrayList::insertTail(objPos thisPos)
{
/*
▪ Inserting thisPos as a new objPos element to the tail of the list
▪ Do you need to “shift” the elements? Think about it.
*/
    if(listSize == arrayCapacity)
    {
        return;
    }
    
    aList[listSize] = thisPos;  // Inserting the element at the tail, index: sizeList
    listSize++;     // Increase the size of the List by one

}

void objPosArrayList::removeHead()
{
/*
▪ Remove the head element from the list
▪ Do you need to “shift” the elements? Think about it.
*/
    if(listSize == 0)
    {
        return;
    }

    for(int i=0; i<listSize-1; i++)
    {
        aList[i] = aList[i+1];  // Shifting towards the head, element i replaced by element i+1
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
/*
▪ Remove the tail element from the list
▪ Do you need to “shift” the elements? Think about it.
*/
    if(listSize == 0)
    {
        return;
    }

    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
/*
▪ Return a copy of the objPos element at the head of the list
*/
return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
/*
▪ Return a copy of the objPos element at the tail of the list
*/
return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
/*
▪ Return a copy of the n-th objPos element from the list, where n is specified by index.
*/
    return aList[index];
}