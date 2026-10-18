#ifndef ARRAY_OPERATIONS_H
#define ARRAY_OPERATIONS_H

#include <stddef.h>

/**
 * Traverses the array 'src' of length 'size' and copies its elements into 'dest'.
 *
 * @param src           Pointer to source array (read-only)
 * @param size          Number of valid elements in 'src'
 * @param dest          Pointer to destination array
 * @param dest_capacity Maximum capacity of 'dest' array
 * @return              Number of elements copied (size) on success, or -1 on error.
 *                      Error conditions: src is NULL, dest is NULL, size < 0, or dest_capacity < size.
 */
int traverse_array(const int src[], int size, int dest[], int dest_capacity);

/**
 * Inserts 'element' at 0-based 'index' into array 'arr'.
 * Elements at and after 'index' are shifted one position to the right.
 *
 * @param arr      Pointer to the array
 * @param size     Current number of elements in 'arr'
 * @param capacity Maximum total capacity of 'arr'
 * @param index    0-based position at which to insert (0 <= index <= size)
 * @param element  The integer value to insert
 * @return         New array size (size + 1) on success, or -1 on error.
 *                      Error conditions: arr is NULL, capacity <= 0, size < 0,
 *                      size >= capacity, index < 0, or index > size.
 */
int insert_at_index(int arr[], int size, int capacity, int index, int element);

/**
 * Deletes the element at 0-based 'index' from array 'arr'.
 * Elements after 'index' are shifted one position to the left.
 *
 * @param arr   Pointer to the array
 * @param size  Current number of elements in 'arr'
 * @param index 0-based position of element to delete (0 <= index < size)
 * @return      New array size (size - 1) on success, or -1 on error.
 *              Error conditions: arr is NULL, size <= 0, index < 0, or index >= size.
 */
int delete_at_index(int arr[], int size, int index);

/**
 * Searches for 'target' element in array 'arr'.
 *
 * @param arr    Pointer to the array (read-only)
 * @param size   Current number of elements in 'arr'
 * @param target Integer value to search for
 * @return       0-based index of first occurrence of 'target' if found, or -1 if not found / invalid params.
 */
int find_element(const int arr[], int size, int target);

#endif /* ARRAY_OPERATIONS_H */
