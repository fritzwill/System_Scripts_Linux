/* list.c */

#include "list.h"

/* Internal Function Prototypes */

static struct node*	reverse(struct node *curr, struct node *next);
static struct node *	msort(struct node *head, node_compare f);
static void		split(struct node *head, struct node **left, struct node **right);
static struct node *	merge(struct node *left, struct node *right, node_compare f);

/**
 * Create list.
 *
 * This allocates a list that the user must later deallocate.
 * @return  Allocated list structure.
 */
struct list *	list_create() {
    struct list * newList = malloc(sizeof(struct list));
    if (newList == NULL){ // checks if allocation fails
        return NULL;
    }
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

/**
 * Delete list.
 *
 * This deallocates the given list along with the nodes inside the list.
 * @param   l	    List to deallocate.
 * @return  NULL pointer.
 */
struct list *	list_delete(struct list *l) {
    node_delete(l->head, true);
    free(l);
    return NULL;
}

/**
 * Push front.
 *
 * This adds a new node containing the given string to the front of the list.
 * @param   l	    List structure.
 * @param   s	    String.
 */
void		list_push_front(struct list *l, char *s) {
    struct node * newNode = node_create(s, l->head);
    l->head = newNode;
    (l->size)++;
    if (l->size == 1) l->tail = newNode;
}

/**
 * Push back.
 *
 * This adds a new node containing the given string to the back of the list.
 * @param   l	    List structure.
 * @param   s	    String.
 */
void		list_push_back(struct list *l, char *s) {
    struct node * newNode = node_create(s, NULL);
    if (l->size == 0){
        l->head = newNode;
        l->tail = newNode;
        (l->size)++;
    }
    else {
        (l->tail)->next = newNode;
        l->tail = newNode;
        (l->size)++;
    }
}

/**
 * Dump list to stream.
 *
 * This dumps out all the nodes in the list to the given stream.
 * @param   l	    List structure.
 * @param   stream  File stream.
 */
void		list_dump(struct list *l, FILE *stream) {
    struct node * ptr = l->head;
    while (ptr != NULL){
        node_dump(ptr, stream);
        ptr = ptr->next;
    }
}

/**
 * Convert list to array.
 *
 * This copies the pointers to nodes in the list to a newly allocate array that
 * the user must later deallocate.
 * @param   l	    List structure.
 * @return  Allocate array of pointers to nodes.
 */
struct node **	list_to_array(struct list *l) {
    struct node ** arr = malloc(l->size*sizeof(struct node *));
    arr[0] = l->head;
    for (int i = 1; i < l->size; i++){
        arr[i] = arr[i-1]->next;
    }
    return arr;
}

/**
 * Sort list using qsort.
 *
 * This sorts the list using the qsort function from the standard C library.
 * @param   l	    List structure.
 * @param   f	    Node comparison function.
 */
void		list_qsort(struct list *l, node_compare f) {
    struct node ** arr = list_to_array(l);
    qsort(arr, l->size, sizeof(struct node *), f);
    l->head = arr[0];
    l->tail = arr[(l->size) - 1];
    for (int i = 0; i < (l->size) - 1; i++){
        arr[i]->next = arr[i+1];
    }
    arr[(l->size) - 1]->next = NULL;
    free(arr);
}

/**
 * Reverse list.
 *
 * This reverses the list.
 * @param   l	    List structure.
 */
void		list_reverse(struct list *l) {
    l->tail = l->head;
    l-> head = reverse(l->head, NULL);
}

/**
 * Reverse node.
 *
 * This internal function recursively reverses the node.
 * @param   curr    The current node.
 * @param   prev    The previous node.
 * @return  The new head of the singly-linked list.
 */
struct node*	reverse(struct node *curr, struct node *prev) {
    if (curr->next == NULL){
        curr->next = prev;
        return curr;
    }
    struct node * ptr = curr->next;
    curr->next = prev;
    curr = reverse(ptr, curr);
    return curr;
}

/**
 * Sort list using merge sort.
 *
 * This sorts the list using a custom implementation of merge sort.
 * @param   l	    List structure.
 * @param   f	    Node comparison function.
 */
void		list_msort(struct list *l, node_compare f) {\
    l->head = msort(l->head, f);
    struct node * ptr;
    ptr = l->head;
    while (ptr->next) ptr = ptr->next;
    l->tail = ptr;   
}

/**
 * Performs recursive merge sort.
 *
 * This internal function performs a recursive merge sort on the singly-linked
 * list starting with head.
 * @param   head    The first node in a singly-linked list.
 * @param   f	    Node comparison function.
 * @return  The new head of the list.
 */
struct node *	msort(struct node *head, node_compare f) {
    if (head == NULL) return head;
    if (head->next == NULL) return head;
    struct node * left = NULL;
    struct node * right = NULL;
    split(head, &left, &right);
    left = msort(left, f);
    right = msort(right, f);
    head = merge(left, right, f);
    return head;
}

/**
 * Splits the list.
 *
 * This internal function splits the singly-linked list starting with head into
 * left and right sublists.
 * @param   head    The first node in a singly-linked list.
 * @param   left    The left sublist.
 * @param   right   The right sublist.
 */
void		split(struct node *head, struct node **left, struct node **right){
    struct node * fast = head;
    struct node * slow = head;
    struct node * tail = head;
    fast = fast->next->next;
    slow = slow->next;
    while (fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
        tail = tail->next;
    }
    *left = head;
    *right = slow;
    tail->next = NULL;
}

/**
 * Merge sublists.
 *
 * This internal function merges the left and right sublists into one ordered
 * list.
 * @param   left    The left sublist.
 * @param   right   The right sublist.
 * @param   f	    Node comparison function.
 * @return  The new head of the list.
 */
struct node *	merge(struct node *left, struct node *right, node_compare f) {
    if (right == NULL) return left;
    else if (left == NULL) return right;
    struct node * complete = NULL;
    struct node * helpL = left;
    struct node * helpR = right;
    struct node * head = NULL;
    int counter = 0;
    while (helpL != NULL || helpR != NULL){
        if (helpL == NULL){
            helpR = helpR->next;
            complete->next = right;
            right = helpR;
            complete = complete->next;
            counter++;
        }
        else if (helpR == NULL){
            helpL = helpL->next;
            complete->next = left;
            left = helpL;
            complete = complete->next;
            counter++;
        }
        else if (f(&helpL, &helpR) <= 0){
            if (counter == 0){
                complete = helpL;
                head = complete;
                helpL = helpL->next;
                left = helpL;
            }
            else {
                helpL = helpL->next;
                complete->next = left;
                left = helpL;
                complete = complete->next;
            }
            counter++;
        }
        else {
            if (counter == 0){
                complete = helpR;
                head = complete;
                helpR = helpR->next;
                right = helpR;
            }
            else {
                helpR = helpR->next;
                complete->next = right;
                right = helpR;
                complete = complete->next;
            }
            counter++;
        }
    }
    complete->next = NULL;
    return head;
}
