#include <stdio.h>

int main(void){
  int age = 30;
  const double Pi = 3.1416;

  printf("Integer age is located at: 0x%x\n", &age);
  printf("Double pi is located at: 0x%x\n", &Pi);

  return 0;
}
