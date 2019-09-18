/*
 * list.c
 * Foraynia Wu / SID: 913241587
 * A list of function definations used to modify 
 * lists of coordinates
 */

#include "list.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Output:
 *      Returns a newly allocated List
 * Summary:
 *      Allocates space for an empty new List and returns it
 */
List* ConstructList() {
    List* result = (List*) malloc(sizeof(List));
    if (result != (List*) NULL) {
        result->head = (ListNode*) NULL;
        result->size = 0;
    }
    return result;
}

/*
 * Input:
 *      FILE* fp, a file pointer pointing to a read-only open file
 * Output:
 *      Returns a newly alllocated list
 * Summary:
 *      Reads coordinates from a file and puts them in a new List
 */
List* ReadList(FILE* fp) {
    int row, col;
    List* result;
    if (fp == (FILE*) NULL) {
        printf("ReadList Error: NULL parameter passed.\n");
        exit(EXIT_FAILURE);
    }
    result = ConstructList();
    while (fscanf(fp, "%d %d", &row, &col) == 2) {
        PushFrontList(result, ConstructCoordinate(row, col));
    }
    return result;
}

/*
 * Input:
 *      List* list, the List to delete
 * Summary:
 *      Calls free on every node to deallocate memory
 *      used by the nodes of the List, then deallocates
 *      the list itself
 */
void DeleteList(List* list) {
    ListNode* current_node = list->head;
    while (current_node != (ListNode*) NULL) {
        ListNode* next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    free(list);
    return;
}

/*
 * Input:
 *      List* list, a List to add data to
 *      Coordinate data, data to add to the list
 * Output:
 *      Returns the size of list after adding data
 * Summary:
 *      Adds a data to the front of list
 */
int PushFrontList(List* list, Coordinate data) {
    ListNode* new_node = ConstructListNode(data, list->head);
    if (new_node != (ListNode*) NULL) {
        list->head = new_node;
        list->size++;
    }
    return list->size;
}

/*
 * Input:
 *      List* list, a List to print
 * Summary:
 *      Prints elements from list, starting with the head
 */
void PrintList(List* list) {
    int i;
    for (i = 0; i < list->size; i +=1){
        printf("Coordinate: (%d,%d)\n", list->head->data.x, list->head->data.y);
            list->head = list->head->next;
    }
}

/*
 * Input:
 *      Coordinate data, data for the ListNode
 *      ListNode* node, the next node after the ListNode
 * Output:
 *      Returns a ListNode* to a newly allocated ListNode
 * Summary:
 *      Allocates space for a ListNode and initializes its
 *      data and node members
 */
ListNode* ConstructListNode(Coordinate data, ListNode* node) {
    ListNode* list_node = (ListNode*) malloc(sizeof(ListNode));
    if (list_node != (ListNode*) NULL) {
        list_node->data = data;
        list_node->next = node;
    }
    return list_node;
}
