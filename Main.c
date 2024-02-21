#include <stdio.h>
#include "StrList.h" // Ensure this is the correct header file for the StrList implementation
#define MAX_STR_SIZE 256



int main() {
    int choice, index = 0;
    char str[MAX_STR_SIZE]; // Assuming MAX_STR_SIZE is defined, e.g., #define MAX_STR_SIZE 256
    StrList *list = StrList_alloc(); // Allocate and initialize the list

    while ( 1) { // Loop until 0 is entered to exit
    scanf("%d",&choice);
        switch (choice) {
            case 1: // Case for inserting strings at the end
                int count;
        scanf("%d",&count);
        for (size_t i = 0; i < count; i++)
        {
            scanf("%s",str);
            StrList_insertLast(list,str);
        }
        break;
            case 2: // ENTER_AT_INDEX
                scanf("%d %s", &index, str);
                StrList_insertAt(list, str, index);
                break;
            case 3: // PRINT
                StrList_print(list);
                break;
            case 4: // LENGTH
                printf("%zu\n", StrList_size(list)); // Assuming a function returning list length
                break;
            case 5: // PRINT_AT_INDEX
                scanf("%d", &index);
                StrList_printAt(list, index);
                break;
            case 6: // AMOUNT_OF_CHARS
                printf("%d\n",StrList_printLen(list)); // Assuming this function exists
                break;
            case 7: // PRINT_ALL_TIMES
                scanf("%s", str);
                printf("%d\n",StrList_count(list, str)); // Assuming this counts and prints occurrences of str
                break;
            case 8: // DELETE_ALL_TIMES
                scanf("%s", str);
                StrList_remove(list, str);
                break;
            case 9: // DELETE_AT_INDEX
                scanf("%d", &index);
                StrList_removeAt(list, index);
                break;
            case 10: // REVERSE
                StrList_reverse(list);
                break;
            case 11: // CLEAR
                StrList_free(list); // Assuming this clears the list
                break;
            case 12: // SORT
                StrList_sort(list);
                break;
            case 13: // CHECK_SORTED
                if (StrList_isSorted(list)) {
                    printf("true\n");
                } else {
                    printf("false\n");
                }
                break;
           
              case 0:return 0;
              default: break;
        }
    }


    StrList_free(list); // Free the list before exiting
    return 0;
}