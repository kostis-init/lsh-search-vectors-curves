#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "hasher.h"
#include "LSH.h"
#include "Point.h"

static FILE* temp_file = NULL;
LSH *lsh;

void test_PointHasher(void) {
    //check signleton and selectedGrids array size.
    auto phasher = new PointHasher(4,6);
    //ensure selected has 4 elements
    CU_ASSERT(phasher->selectedGrids[3] < phasher->gridPoolSize);
    auto temp = phasher->gridPool;
    auto phasher2 = new PointHasher(6,9);
    //ensure selected has 6 elements
    CU_ASSERT(phasher2->selectedGrids[5] < phasher->gridPoolSize);
    CU_ASSERT(temp == phasher2->gridPool);
}

//check that near points lie on the same bucket.
//This depends on the window size (currently 100).
void test_HashNonAmplified(void) {
    auto phasher = new PointHasher(5,2);
    int M = pow(2,int(32/5));
    Point *point = new Point("1");
    //
    //
    point->addCoordinateLast(-2000.1);
    point->addCoordinateLast(9000.1);
    int bucket = phasher->hash(point,1);
    CU_ASSERT(bucket < M && bucket > 0);
    Point *point2 = new Point("2");
    point2->addCoordinateLast(-2010.1);
    point2->addCoordinateLast(9015.1);
    int bucket2 = phasher->hash(point2,1);
    CU_ASSERT(bucket2 < M && bucket2 > 0);
    //ensure they lie on the same bucket. This can fail with small
    //propability because we the whole process is random.
    CU_ASSERT(bucket2 == bucket);

}

//not impemented.
void test_HashAmplified(void) {
    auto phasher = new PointHasher(4,3);
    int M = pow(2,int(32/4));
    Point *point[100];
    int buckets[100];
    for (int i=0;i < 100; i++){
       point[i] = new Point("432432");
       //add every point around 1244 + (0-50)
       point[i]->addCoordinateLast((rand() % 50) + 1244);
       point[i]->addCoordinateLast((rand() % 50) + 1244);
       //buckets[i] = *phasher(point[i]);
       printf("%d\n",buckets[i]);
    }
}

int init_suite1(void)
{
   if (NULL == (temp_file = fopen("testPoinHasher.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

int main(void) {
   CU_pSuite pSuite = NULL;
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if ((NULL == CU_add_test(pSuite, "test of PointHasher constructor", test_PointHasher))||
       (NULL == CU_add_test(pSuite, "test of hash(obj,hashIndex) ", test_HashNonAmplified)))
      {
      CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
