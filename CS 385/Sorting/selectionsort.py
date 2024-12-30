def swap(lst, a, b):
    lst[a], lst[b] = lst[b], lst[a]

# Selection Sort finds the smallest element
# in the list and swaps it with the element
# at the front of the list (if the smallest
# element is not already there).  Then the
# whole process is repeated on the (unsorted)
# rest of the list.
def selection_sort(lst):
    n = len(lst)
    for i in range(n - 1):
        # Searching for the smallest element
        # in the unsorted part of the list:
        min_index = i
        for j in range(i + 1, n):
            if lst[j] < lst[min_index]:
                min_index = j
        # Swapping the smallest element with
        # the one at the front of the unsorted
        # part of the list (if necessary):
        if min_index != i:
            swap(lst, i, min_index)

def selection_sort_rec_helper(lst, i, n):
    if i >= n - 1:
        return
    # Searching for the smallest element
    # in the unsorted part of the list:
    min_index = i
    for j in range(i + 1, n):
        if lst[j] < lst[min_index]:
            min_index = j
    # Swapping the smalest element with
    # the one at the front of the list
    # (if necessary):
    if min_index != i:
        swap(lst, i, min_index)
    # Recursion on the rest of the list:
    selection_sort_rec_helper(lst, i + 1, n)

def selection_sort_rec(lst):
    selection_sort_rec_helper(lst, 0, len(lst))

lst = [3, 2, 4, 1, 5]
selection_sort(lst)
print(lst)

lst = [3, 2, 4, 1, 5]
selection_sort_rec(lst)
print(lst)
