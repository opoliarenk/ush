#include "../inc/libmx.h"

void swaper(t_list *lst) {
    void *buf = NULL;
    
    buf = lst->data;
    lst->data = lst->next->data;
    lst->next->data = buf;
}

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    int size = mx_list_size(lst);
    int i = 0;
    int j = 0;
    t_list *start = lst;

    while (j <= size) {
        while (i < size - 1) {
            if (cmp(start->data, start->next->data) == 1)
                swaper(start);
            start = start->next;
            i++;
        }
        i = 0;
        start = lst;
        j++;
    }
    return lst;
}
