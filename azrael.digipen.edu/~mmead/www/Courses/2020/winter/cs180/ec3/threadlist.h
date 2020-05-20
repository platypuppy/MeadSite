#include <stdbool.h> /* bool */

/* Max length of labels, including NUL character */
#define LABEL_SIZE 16

/* Cache list node */
typedef struct tl_node
{
	char label[LABEL_SIZE];
	int value;
	struct tl_node* next;
}tl_node;

/* Prototypes */
void tl_insert(int value, const char *label);
void tl_insert_values(int *values, int count, const char *label);
void tl_remove(int value);
void tl_remove_values(int *values, int count);
void tl_resetlist(void);
tl_node * const *tl_getlist(void);
void tl_uselocks(bool enable);
void tl_destroy(tl_node *list);

/* Provided for you. DO NOT modify the code in threadlist.c */
void tl_dump(const tl_node *list);
