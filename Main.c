#include <stdio.h>
#include "StrList.h" 
#define MAX_STR_SIZE 256



int main() {
    int command, index = 0;
    char str[MAX_STR_SIZE]; 
    StrList *list = StrList_alloc(); // Allocate and initialize the list

    while ( 1) { // Loop until 0 is entered to exit
    scanf("%d",&command);
        switch (command) {
            case 1: // Case for inserting strings at the end
                int count;
        scanf("%d",&count);
        for (size_t i = 0; i < count; i++)
        {
            scanf("%s",str);
            StrList_insertLast(list,str);
        }
        break;
            case 2: 
                scanf("%d %s", &index, str);
                StrList_insertAt(list, str, index);
                break;
            case 3: 
                StrList_print(list);
                break;
            case 4: 
                printf("%zu\n", StrList_size(list));
                break;
            case 5: 
                scanf("%d", &index);
                StrList_printAt(list, index);
                break;
            case 6: 
                printf("%d\n",StrList_printLen(list));
                break;
            case 7: 
                scanf("%s", str);
                printf("%d\n",StrList_count(list, str)); 
                break;
            case 8: 
                scanf("%s", str);
                StrList_remove(list, str);
                break;
            case 9: 
                scanf("%d", &index);
                StrList_removeAt(list, index);
                break;
            case 10: 
                StrList_reverse(list);
                break;
            case 11: 
                StrList_free(list); 
                break;
            case 12: 
                StrList_sort(list);
                break;
            case 13: 
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
