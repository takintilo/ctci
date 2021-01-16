#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void URLify(char *string, int originalLength) {
  int oldIndex;
  /* int newLength = (&string)[1] - string; */
  /* int newIndex = newLength - 2; // minus an extra 1 due to null terminator \0
   */
  int newLength = strlen(string);
  int newIndex = newLength - 1;
  for (oldIndex = originalLength - 1; oldIndex >= 0; --oldIndex) {
    if (string[oldIndex] == ' ') {
      string[newIndex--] = '0';
      string[newIndex--] = '2';
      string[newIndex--] = '%';
    } else {
      string[newIndex--] = string[oldIndex];
    }
  }
}

int main() {

  char string[] = "Mr John Smith    ";
  URLify(string, 13);

  printf("%s\n", string);

  return 0;
}
