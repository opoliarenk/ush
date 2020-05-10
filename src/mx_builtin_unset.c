#include "../inc/ush.h"

static void pop_front_var(t_var **head) {
    t_var *buf = NULL;

    if (head != NULL) {
        buf = (*head)->next;
        free(buf->data);
        free(buf->name_of_data);
        free(*head);
        *head = buf;
    }
}

static int variable_list_len(t_var **head) {
    t_var *p = (*head);
    int len = 0;

    while (p != NULL) {
        len += 1;
        p = p->next;
    }
    return len;
}

static void pop_specific(t_var **list, int index, int size) {
    t_var *buf = *list;
    t_var *temp = NULL;

    if ((*list != NULL) && (list != NULL)) {
        if (size - 1 >= index) {
            if (index == 0)
                pop_front_var(list);
            else {
                while (index > 1) {
                    buf = buf->next;
                    index--;
                }
                temp = buf->next->next;
                free(buf->next->data);
                free(buf->next->name_of_data);
                free(buf->next);
                buf->next = temp;
            }
        }
    }
}

void mx_builtin_unset(char **name, t_var **list) {
	int index = 0;
	int i = 1;
	t_var *p = *list;
	int size = variable_list_len(list);

	while (name[i]) {
		unsetenv(name[i]);
		while (p) {
			if (mx_strcmp(p->name_of_data, name[i]) == 0)
				pop_specific(list, index, size);
			p = p->next;
			index++;
		}
		index = 0;
		p = *list;
		i++;
	}
}
