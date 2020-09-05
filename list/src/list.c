#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _BSD_SOURCE
#define _XOPEN_SOURCE        /* or any value < 500 */

#if 0
short search_on(int *array, short l_pos, short h_pos, int elm)
{
    short middle = (l_pos + h_pos) / 2;
    printf("%d is the middle btw %d and %d\n", middle, l_pos, h_pos);

    if (array[middle] == elm)
    {
        printf("-->%d is at the index index: %d\n", elm, middle);
        return middle;
    }
    if (middle <= l_pos && middle >= h_pos)
    {
        printf("-->%d not found\n", elm);
        return -1;
    }
    if (elm < array[middle]) {
        //printf("rec lower on %d and %d\n", l_pos, middle - 1);
        search_on(array, l_pos, middle - 1, elm);
    }
    else if (elm > array[middle]) {
        //printf("rec higher on %d and %d\n", middle + 1, h_pos);
        search_on(array, middle + 1, h_pos, elm);
    }
    return -1;
}
#endif

short search_on1(int *array, short l_pos, short h_pos, int elm)
{
    if (array[l_pos] == elm)
    {
        printf("-->%d is at the index: %d\n", elm, l_pos);
        return l_pos;
    }
    else if (l_pos == h_pos && array[l_pos] != elm)
    {
        printf("-->%d not found\n", elm);
        return -1;
    }

    short middle = (l_pos + h_pos) / 2;
    //printf("%d is the middle btw %d and %d\n", middle, l_pos, h_pos);

    if (elm <= array[middle]) {
        //printf("rec lower on %d and %d\n", l_pos, middle);
        search_on1(array, l_pos, middle, elm);
    }
    else if (elm > array[middle]) {
        //printf("rec higher on %d and %d\n", middle + 1, h_pos);
        search_on1(array, middle + 1, h_pos, elm);
    }

    return -1;
}


short find_dicho(int *array, short size, int elm)
{
    return search_on1(array, 0, size - 1, elm);
}

short find_elm(int *array, short size, int elm)
{
    for (short i = 0; i < size; i++) {
        if (elm == array[i])
            return i;
    }
    return -1;
}

int sup_elm(int *array, int *size, int elm)
{
    short pos = find_elm(array, *size, elm);
    if (pos == -1)
        return -1;
    for (short i = pos; i < *size - 1; i++) {
        array[i] = array[i + 1];
    }
    (*size)--;
    return 0;
}


int insert_elm(int *array, short size, int elm)
{
    short i;
    for (i = size; i > 0; i--) {
        array[i] = array[i - 1];
        if (elm >= array[i - 1])
            break;
    }
    array[i] = elm;
    return 0;
}

int bubble_sort(int *array, short size)
{
    if (size == 0)
        return 0;

    int tmp;
    int iter = 0;
    for (int j = 0; j < size - 1; j++) {
        for (short i = 0; i < size - j - 1; i++)
        {
            iter++;
            if (array[i] > array[i + 1])
            {
                tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
            }
        }
        //for (int i = 0; i < size; i++) {
        //    printf("%d, ", array[i]);
        //}
        //printf("\n");
    }
    return iter;
}

int selection_sort(int *array, short size)
{

    int iter = 0;
    int index_min;
    int min;
    for (short i = 0; i < size - 2; i++)
    {
        min = array[i];
        index_min = i;
        for (short j = i + 1; j < size; j++)
        {
            iter++;
            if (array[j] < min)
            {
                min = array[j];
                index_min = j;
            }
        }

        if (min != array[i])
        {
            array[index_min] = array[i];
            array[i] = min;
        }
        //for (int i = 0; i < size; i++) {
        //    printf("%d, ", array[i]);
        //}
        //printf("\n");
    }
    return iter;
}

int insertion_sort(int *array, int size)
{
    if (size == 0 || size == 1)
        return 0;

    int iter = 0;
    int min;
    //int uarray[] = {100, 5, 8, 4, 3, 2, 55, 0, 78, 7};
    for (short i = 1; i < size; i++)
    {
        min = array[i];
        for (short j = i; j >= 0; j--)
        {
            iter++;
            if (min < array[j])
            {
                array[j + 1] = array[j];
                array[j] = min;

            }
            if (min > array[j])
            {
                break;
            }
        }

        //for (int i = 0; i < size; i++) {
        //    printf("%d, ", array[i]);
        //}
        //printf("\n");
    }
    return iter;
}

int main(int agrc, char *argv[])
{
    int array[20];
    int a_size = 0;

    sup_elm(array, &a_size, 5);

    insert_elm(array, a_size++, 5);
    insert_elm(array, a_size++, 6);
    insert_elm(array, a_size++, 3);
    insert_elm(array, a_size++, 11);
    insert_elm(array, a_size++, 15);
    insert_elm(array, a_size++, 0);


    for (int i = 0; i < a_size; i++) {
        printf("%d, ", array[i]);
    }
    printf("\n");

    printf("\n");
    find_dicho(array, a_size, 8);
    find_dicho(array, a_size, 0);
    find_dicho(array, a_size, 11);
    find_dicho(array, a_size, -1);
    find_dicho(array, a_size, 19);
    printf("\n");

    /*Sort algo*/
    int capacity = 100;
    int uarray[capacity];
    int iter = 0;
    int tmp;
    for (int i = 0; i < capacity; i++)
    {
        while (1)
        {
            iter++;
            tmp = random() * 7 % capacity * 100;
            if (find_elm(uarray, i, tmp) == -1)
            {
                uarray[i] = tmp;
                break;
            }
        }
    }
    printf("iter to create the list : %d\n", iter);

    int ua_size = sizeof(uarray) / sizeof(int);

    iter = selection_sort(uarray, ua_size); 
    printf("selection sort for %d elem : %d\n", ua_size, iter);

    iter = bubble_sort(uarray, ua_size); 
    printf("bubble sort for %d elem : %d\n", ua_size, iter);

    iter = insertion_sort(uarray, ua_size);
    printf("insertion sort for %d elem : %d\n", ua_size, iter);

    return 0;
}
