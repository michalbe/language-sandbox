#ifndef LINKED_POINT_H
#define LINKED_POINT_H

  struct Point {
    int x;
    int y;
    struct Point *next;
  };

void push(struct Point **item, int x, int y);
int pop(struct Point **item, int *x, int *y);
int last(struct Point **item, int *x, int *y);
// remove & return first
int shift(struct Point **head, int *x, int *y);
// push as first
void unshift(struct Point** head, int x, int y);

#endif

#ifndef NULL
#define NULL 0
#endif
