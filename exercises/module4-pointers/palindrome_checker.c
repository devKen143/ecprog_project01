#include <stdio.h>

/*
    Function: isPalindrome
    Uses two pointers:
    - left starts at the beginning of the array.
    - right starts at the end of the array.
    The pointers move toward each other while comparing values.
    If a mismatch is found, the array is not a palindrome.
*/

int isPalindrome(int *arr, int size) {
    int *left = arr;
    int *right = arr + size - 1;

    while (left < right) {
        if (*left != *right)
            return 0;

        left++;
        right--;
    }

    return 1;
}

int main() {
  
    int arr1[] = {1, 2, 3, 2, 1};
    int arr2[] = {5, 4, 4, 5};
    int arr3[] = {1, 2, 3, 4, 5};
    int arr4[] = {7};
    int arr5[] = {9, 9};
    int arr6[] = {3, 7};
    int arr7[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};

    printf("Test 1: %s\n", isPalindrome(arr1, 5) ? "PALINDROME" : "NOT PALINDROME");
    printf("Test 2: %s\n", isPalindrome(arr2, 4) ? "PALINDROME" : "NOT PALINDROME");
    printf("Test 3: %s\n", isPalindrome(arr3, 5) ? "PALINDROME" : "NOT PALINDROME");
    printf("Test 4: %s\n", isPalindrome(arr4, 1) ? "PALINDROME" : "NOT PALINDROME");
    printf("Test 5: %s\n", isPalindrome(arr5, 2) ? "PALINDROME" : "NOT PALINDROME");
    printf("Test 6: %s\n", isPalindrome(arr6, 2) ? "PALINDROME" : "NOT PALINDROME");
    printf("Test 7: %s\n", isPalindrome(arr7, 9) ? "PALINDROME" : "NOT PALINDROME");

    return 0;
}
