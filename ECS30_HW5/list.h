/*
 * list.h
 * Foraynia Wu / SID: 913241587
 * An implementation of a Linked List containg Coordinates
 */

#ifndef _LIST_H_
#define _LIST_H_

#include "coordinate.h"

#include <stdio.h>

struct ListNode;

typedef struct {
    struct ListNode* head;
    int size;
} List;

typedef struct ListNode {
    Coordinate data;
    struct ListNode* next;
} ListNode;

/*
 * Output:
 *      Returns a newly allocated List
 * Summary:
 *      Allocates space for an empty new List and returns it
 */
List* ConstructList();

/*
 * Input:
 *      FILE* fp, a file pointer pointing to a read-only open file
 * Output:
 *      Returns a newly alllocated list
 * Summary:
 *      Reads coordinates from a file and puts them in a new List
 */
List* ReadList(FILE* fp);

/*
 * Input:
 *      List* list, the List to delete
 * Summary:
 *      Calls free on every node to deallocate memory
 *      used by the nodes of the List, then deallocates
 *      the list itself
 */
void DeleteList(List* list);

/*
 * Input:
 *      List* list, a List to add data to
 *      Coordinate data, data to add to the list
 * Output:
 *      The size of list after adding data
 * Summary:
 *      Adds data to the front of list
 */
int PushFrontList(List* list, Coordinate data);

/*
 * Input:
 *      List* list, a List to print
 * Summary:
 *      Prints elements from list, starting with the head
 */
void PrintList(List* list);

/*
 * Input:
 *      Coordinate data, data for the ListNode
 *      ListNode* node, the next node after the ListNode
 * Output:
 *      A ListNode* to a newly allocated ListNode
 * Summary:
 *      Allocates space for a ListNode and initializes its
 *      data and node members
 */
ListNode* ConstructListNode(Coordinate data, ListNode* node);

#endif  /* _LIST_H_ */
