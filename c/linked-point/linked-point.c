#include "linked-point.h"

void push(struct Point **item, int x, int y){
    struct Point *current;
    struct Point *endItem;

    current = *item;

    /* See if the passed value is a Point */
    if (current)
    {
        /* See if this is the last Point in the list */
        if (current->next == NULL)
        {
            /* This is the last item, so create a new Point to go on the end */

            /* Allocate memory for the new Point */
            endItem = malloc(sizeof(struct Point));

            /* Set the value */
            endItem->x = x;
            endItem->y = y;

            /* Set the pointer to the next item to be NULL (there isn't a next,
            this will be the last item) */
            endItem->next  = NULL;

            /* Set the next pointer in the last item to the new item, making
            the new item now the last one */
            current->next = endItem;

            return;
        }
        else
        {
            /* This is not the last item, recurse to the next one */
            return push(¤t->next, x, y);
        }
    }

    /* There are no Points in the list, so create a new Point and it will be
    the first in the list */
    endItem = malloc(sizeof(struct Point));

    /* Set the value */
    endItem->x = x;
    endItem->y = y;

    /* Set the pointer to the next item to be NULL (there isn't a next, this
    will be the last item) */
    endItem->next  = NULL;

    /* Set the passed pointer to point to the new Point */
    *item = endItem;
}

int pop (struct Point **item, int *x, int *y)
{
    struct Point *current;

    current = *item;

    if (current)
    {
        /* See if the current item specifies a proceding item */
        if (current->next)
        {
            /* There is a next item, so see if it is the last one */
            if (current->next->next == NULL)
            {
                /* The next item is the last one, so get its value */
                *x = current->next->x;
                *y = current->next->y;

                /* Free the memory reserved for the last item */
                free(current->next);

                /* Remove the pointer to the last item */
                current->next = NULL;

                return 0;
            }

            /* Move on to the next item */
            return pop(¤t->next, x, y);
        }

        /* There aren't any more items, this is the last one and therefore also the first */
        *x = current->next->x;
        *y = current->next->y;

        /* Release the memory reserved for it */
        free(*item);

        /* Set the head Point to NULL */
        *item = NULL;

        return 0;
    }

    /* There are no items in the list */
    x = NULL;
    y = NULL;

    return -1;
}

int shift(struct Point **head, int *x, int *y)
{
    struct Point *firstPoint;

    firstPoint = *head;

    /* See if there is a first Point */
    if (firstPoint == NULL)
    {
        /* There isn't, so return -1*/
        return -1;
    }

    /* Set the passed pointer, the pointer to the first Point in the list, to the next Point */
    *head = firstPoint->next;

    /* Get the value from the first Point before we free() it */
    *x = firstPoint->x;
    *y = firstPoint->y;

    /* Deallocate the first Point */
    free(firstPoint);

    /* Return 0, all ok */
    return 0;
}

void unshift(struct Point** head, int x, int y)
{
    /* Declare and reserve memory for the new item */
    struct Point* newPoint = malloc(sizeof(struct Point));

    /* Se the new Point's value */
    newPoint->x = x;
    newPoint->y = y;

    /* Set the next item to be the item that was previously first */
    newPoint->next = *head;

    /* Set the pointer to the first item to this new item */
    *head = newPoint;
}
