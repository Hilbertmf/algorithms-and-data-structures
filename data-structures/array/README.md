# Array
## Advantages of arrays:
- Random access of elements using array index
- Easy access to all elements
- Traversal through the array becomes easy using a single loop
## Disadvantages of arrays:
- Allows a fixed number of elements to be entered which is decided at the time of declaration. Unlike a linked list, an array in C is not dynamic
- Insertion and deletion of elements can be costly since the elements are needed to be managed in accordance with the new memory allocation (you have to create a new array)
## Initializing an array:
- Basic declaration and initialization:
```C
int arr[5] = {0, 1, 2, 3, 4};
int arr[] = {0, 1, 2, 3, 4};
```
- Initializig all elements w/ zero:
```C
int arr[5] = {0};
```
- First elements with values and the rest is zero:
```C
int arr[5] = {1, 2, 3};
```
- Initializing random elements and the rest is zero:  
```C
int arr[10] = {[0] = 1, [4] = 2, [6] = 3};
```
