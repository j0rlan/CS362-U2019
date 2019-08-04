#ifndef DOMINION_ASSERT_H
#define DOMINION_ASSERT_H

// a is tested value, b is expected value

void assertTrue(int a, int b){
   if (a == b){
      printf("success\n");
   }
   else {
      printf("failure: %d\n", a);
   }
}

void assertFalse(int a, int b){
   if (a == b){
      printf("failure\n");
   }
   else {
      printf("success: %d != %d\n", a, b);
   }
}

#endif
