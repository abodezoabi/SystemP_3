#include <stdio.h>
#include "StrList.h"
#include <string.h> 
#include <stdlib.h> 

// Define a Node structure for the linked list. Each node contains a string and a pointer to the next node.
typedef struct Node {
    char* data; // Pointer to a string (dynamically allocated).
    struct Node* next; // Pointer to the next node in the list.
} Node;

// Define the StrList structure. It represents a linked list with a head pointer and a size counter.
typedef struct _StrList {
    Node* head; // Pointer to the first node in the list.
    size_t size; // The number of elements in the list.
} StrList;

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList)); // Dynamically allocate memory for a StrList structure.
    if (list) { // If memory allocation was successful,
        list->head = NULL; // initialize the head to NULL (empty list),
        list->size = 0; // and set the size to 0.
    }
    return list; // Return a pointer to the newly created list.
}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList* list) {
   if (list == NULL) {
        return; // If the list pointer is NULL, do nothing.
    }

    Node* current = list->head; // Start with the first node.
    for (int i = 0; i < list->size; i++) {
        if (current == NULL) {
            break; // Stop the loop if we've reached the end of the list.
        }
        Node* next = current->next; // Remember the next node.
        free(current->data); // Free the string data of the current node.
        free(current); // Free the current node itself.
        current = next; // Move to the next node.
    }
    list->head=NULL;
    list->size=0;
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList* StrList) {
    return StrList->size; // Return the size field of the list structure.
}

/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList* StrList,const char* data) {
    StrList_insertAt(StrList, data, StrList_size(StrList)); // Delegate to StrList_insertAt, using the current size as the index to insert at the end.
}

/*
* Inserts an element at given index
*/
void StrList_insertAt(StrList* StrList,const char* data,int index) {
    if (index < 0 || index > StrList->size) return; // If the index is out of bounds, return immediately.

    Node *newNode = (Node *) malloc(sizeof(Node)); // Allocate memory for a new Node.
    newNode->data = strdup(data); // Duplicate the string and store its pointer in the node.

    if (index == 0) { // If inserting at the head,
        newNode->next = StrList->head; // the new node's next pointer is the current head.
        StrList->head = newNode; // The new node becomes the new head.
    } else { // If inserting not at the head,
        Node *current = StrList->head; // find the node after which to insert.
        for (int i = 0; i < index - 1; i++) { // Iterate to find the correct position.
            current = current->next;
        }
        newNode->next = current->next; // Insert the new node in the list.
        current->next = newNode;
    }
    StrList->size++; // Increment the size of the list.
}

/*
 * Returns the StrList first data.
 */
char* StrList_firstData(const StrList* StrList){
    if (StrList->head != NULL) { // If the list is not empty,
        return StrList->head->data; // return the data of the first node.
    }
    return NULL; // Otherwise, return NULL.
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList* StrList){
    const Node* n = StrList->head;
    while (n) {
        printf("%s", n->data);
        if (n->next) {
            printf(" "); // a space between words
        }
        n = n->next;
    }
    printf("\n");
}

/*
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList* Strlist,int index) {
    if (index < 0 || index >= Strlist->size) { return;} // If index is out of bounds, do nothing.

    Node *temp = Strlist->head; // Start from the head.
    for (int i = 0; i < index;i++) { // Iterate to find the node at the given index.
        temp = temp->next;
    }
    printf("%s\n", temp->data); // Print the data of the node at the given index.
}

/*
 * Return the amount of chars in the list.
*/
int StrList_printLen(const StrList* Strlist) {
    int ans = 0; // Initialize the character count.
    Node *temp = Strlist->head; // Start from the head.
    while (temp != NULL) { // While there are nodes to process,
        ans += strlen(temp->data); // add the length of the current node's data to the total,
        temp = temp->next; // and move to the next node.
    }
    return ans; // Return the total character count.
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList* StrList, const char* data){
    int ans = 0; // Initialize the count of occurrences.
    for (Node* temp = StrList->head; temp != NULL; temp = temp->next) { // Iterate through each node in the list,
        if (strcmp(temp->data, data) == 0) { // if the current node's data matches the given string,
            ans++; // increment the count.
        }
    }
    return ans; // Return the total count of occurrences.
}

/*
Given a string and a list, remove all the appearances of this string in the list.
*/
void StrList_remove(StrList* StrList, const char* data){
    Node **temp = &StrList->head; // Pointer to pointer to traverse the list without losing the head
    while (*temp != NULL) { // Iterate over the list
        Node *n = *temp; // Temporary node pointer for easier manipulation
        if (strcmp(n->data, data) == 0) { // If the current node's data matches the target string
            *temp = n->next; // Bypass the current node
            free(n->data); // Free the memory allocated for the data
            free(n); // Free the node itself
            StrList->size--; // Decrement the size of the list
        } else {
            temp = &n->next; // Move to the next node
        }
    }
}

/*
Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList* StrList, int index){
    if (index < 0 || index >= StrList->size || StrList->head == NULL) return; // Boundary check

    Node *temp; // Temporary node to delete a node
    if (index == 0) { // If removing the head
        temp = StrList->head; // Temp points to head
        StrList->head = StrList->head->next; // Head is moved to next node
    } else {
        Node* n = StrList->head; // Start from the head
        for (int i = 0; i < index - 1;i++) { // Traverse to the node before the one to be removed
            n = n->next;
        }
        temp = n->next; // Temp points at the node to be removed
        n->next = n->next->next; // skip the node to be removed
    }
    free(temp->data); // Free the data of the node
    free(temp); // Free the node itself
    StrList->size--; // Decrease the size of the list

}

/*
* Checks if two StrLists have the same elements
* returns 0 if not and any other number if yes
*/
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    if (StrList1->size != StrList2->size) return 0; // Check if sizes are unequal
    if(StrList1->head==NULL && StrList2->head==NULL) return 1;
    if(StrList1->size==0 && StrList2->size==0) return 1;
    

    Node* n1 = StrList1->head; // Pointer to traverse first list
    Node* n2 = StrList2->head; // Pointer to traverse second list
    while (n1 != NULL && n2 != NULL) { // Iterate as long as both lists have elements
        if (strcmp(n1->data, n2->data) != 0) { // Compare data of both nodes
            return 0; // If mismatch found, return 0
        }
        n1 = n1->next; // Move to next node in first list
        n2 = n2->next; // Move to next node in second list
    }
    return 1; // If end reached with no mismatches, return 1
}

/*
 * Clones the given StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList* StrList_clone(const StrList* Strlist) {
    StrList* clone = StrList_alloc(); // Allocate memory for the clone
    if (clone == NULL) return NULL; // If allocation fails, return NULL

    Node* n = Strlist->head; // Pointer to traverse the original list
    for (int index = 0; n != NULL; n = n->next,index++) { // Iterate over the list
        StrList_insertAt(clone, n->data, index); // Insert each element into the clone
    }
    return clone; // Return the cloned list
}

/*
 * Reverses the given StrList.
 */
void StrList_reverse( StrList* StrList) {
    Node *prev = NULL, *current = StrList->head, *temp = NULL; // Initialize pointers for reversal

    while (current != NULL) { // Traverse the list
        temp = current->next;  // Save next node
        current->next = prev; // Reverse current node's pointer
        prev = current; // Move prev pointer forward
        current = temp; // Move current pointer to next node
    }
    StrList->head = prev; // Set head to the last node encountered
}

/*
 * Sort the given list in lexicographical order
 */
void StrList_sort( StrList* StrList){
    if (!StrList || !StrList->head || !StrList->head->next) return; // Check if list is empty or has only one element

    Node* temp = NULL;
    Node* next = NULL;
    Node* prev = NULL;
    Node* curnt = StrList->head; // Start sorting from the head

    while (curnt != NULL) { // Traverse the list
        next = curnt->next; // Save the next node
        if (!temp || strcmp(curnt->data, temp->data) <= 0) { // Insert at the beginning or middle
            curnt->next = temp;
            temp = curnt;
        } else { // Find correct position for insertion
            prev = temp;
            while (prev->next != NULL && strcmp(curnt->data, prev->next->data) > 0) {
                prev = prev->next;
            }
            curnt->next = prev->next;
            prev->next = curnt;
        }
        curnt = next; // Move to the next node
    }

    StrList->head = temp; // Update the head of the list
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted, 0 otherwise
 */
int StrList_isSorted(StrList* list){

    StrList* clone = StrList_clone(list); // Clone the list for comparison
    StrList_sort(clone); // Sort the cloned list
    int isEqual = StrList_isEqual(list, clone); // Check if original and sorted clone are equal
   free(clone); // Free the cloned list

    return isEqual; // Return comparison result
}
