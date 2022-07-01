#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// Advantages of arrays:
// Random access of elements using array index
// Easy access to all elements
// Traversal through the array becomes easy using a single loop
// Sorting becomes easy as it can be accomplished by writing less lines of code

// Disadvantages of arrays:
// Allows a fixed number of elements to be entered which is decided at the time
// of declaration. Unlike a linked list, an array in C is not dynamic
// Insertion and deletion of elements can be costly since the elements are needed
// to be managed in accordance with the new memory allocation

int main()
{
  int aux;
//  Initializing arrays:
// All elements with zero:
  int arr[5] = {0};
// first elements with values and the rest is zero:
  int arr1[5] = {1, 2, 3};
// initializing random elements and the rest is zero:
  int arr2[10] = {[0] = 1, [4] = 2, [6] = 3};

  // for (int i = 0; i < 5; i++)
  // {
  //   printf("arr[%d] = %d\n", i, arr[i]);
  // }

  // for (int i = 0; i < 5; i++)
  // {
  //   printf("arr1[%d] = %d\n", i, arr1[i]);
  // }

  // for (int i = 0; i < 10; i++)
  // {
  //   printf("arr2[%d] = %d\n", i, arr2[i]);
  // }

// exampĺe problem: reverse an array

  int nums[] = {34, 56, 54, 32, 67, 89, 90, 32, 21};

  for (int i = 0; i < 9; i++)
  {
    printf("nums[%d] = %d\n", i, nums[i]);
  }
  
  printf("reversing...\n");

  int numsReversed[9];

  for (int i = 0; i < 9; i++)
  {
    numsReversed[i] = nums[8 - i];
    printf("numReversed[%d] = %d\n", i, numsReversed[i]);
  }
  
  // another way:
  for (int i = 8; i >= 0; i--)
  {
    printf("num[%d] = %d\n", i, nums[i]);
  }
  
// example problem: find repeated digits in a number

  char str[255];
  scanf("%s", str);

  int length = strlen(str);
  bool stop = false;
  for (int i = 0; i < length && !stop; i++)
  {
    for (int j = i+1; j < length && !stop; j++)
    {
      if (str[i] == str[j])
      {
        printf("YES!! WE'VE FOUND A REPEATED DIGIT!\n");
        stop = true;
        break;
      }
      
    }
    if (stop)
    {
      break;
    }
        
    if (i == length - 1)
    {
      printf("NO REPEATED DIGIT FOUND\n");
    }
    
  }
  
  return 0;
}