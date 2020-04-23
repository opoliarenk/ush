#include "../inc/ush.h"

static void pop_front_var(t_var **head) {
    t_var *buf = NULL;

    if (head != NULL) {
        buf = (*head)->next;
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

static void pop_specific(t_var **list, int index) {
    t_var *buf = *list;
    t_var *temp = NULL;
    int size = variable_list_len(list);

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

	t_var *buf1 = *list;
	mx_printstr("\nXXXXXXXXXXXDOXXXXXXXXXXXX\n");
	while (buf1) {
		mx_printstr(buf1->name_of_data);
		mx_printstr("=");
		mx_printstr(buf1->data);
		mx_printstr("\t");
		buf1 = buf1->next;
	}
	mx_printstr("\nXXXXXXXXXXXXXXXXXXXXXXXXX\n");

	while (name[i]) {
		unsetenv(name[i]);
		while (p) {
			if (mx_strcmp(p->name_of_data, name[i]) == 0)
				pop_specific(list, index);
			p = p->next;
			index++;
		}
		index = 0;
		p = *list;
		i++;
	}

	t_var *buf2 = *list;
	mx_printstr("\nXXXXXXXXXXXPOSLEXXXXXXXXX\n");
	while (buf2) {
		mx_printstr(buf2->name_of_data);
		mx_printstr("=");
		mx_printstr(buf2->data);
		mx_printstr("\t");
		buf2 = buf2->next;
	}
	mx_printstr("\nXXXXXXXXXXXXXXXXXXXXXXXXX\n");
}
