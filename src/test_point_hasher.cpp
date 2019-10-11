#include <set>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "hasher.h"
#include "LSH.h"
#include "Point.h"
#include "ui.h"

static FILE* temp_file = NULL;
LSH *lsh;

void test_PointHasher(void) {
    //check signleton and selectedGrids array size.
    auto phasher = new PointHasher(4,6,100);
    //ensure selected has 4 elements
    CU_ASSERT(phasher->selectedGrids[3] < phasher->gridPoolSize);
    auto temp = phasher->gridPool;
    auto phasher2 = new PointHasher(6,9,100);
    //ensure selected has 6 elements
    CU_ASSERT(phasher2->selectedGrids[5] < phasher->gridPoolSize);
    CU_ASSERT(temp == phasher2->gridPool);
}

//check that near points lie on the same bucket.
//This depends on the window size (currently 100).
void test_HashNonAmplified(void) {
    auto phasher = new PointHasher(5,2,100);
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

void test_HashAmplified(void) {
   //first dataset (kostis)
   lsh = new LSH();
   //all points are around 0-120 approx
   lsh->setInputFileGiven(true);
   lsh->setInputFilename("../src/very_small_input_for_testing");
   lsh->setData(parseInputFilePoints(lsh->getInputFilename()));
   auto dataset = lsh->getData();
   auto numDim = dataset->getDimension();
   auto points = dataset->getPoints();
   //printf("min is %f and max is %f",dataset->getMinCoordinate(),dataset->getMaxCoordinate());
   //because the window is bigger than the biggest coordinate of a
   // data point (131), all points should lie on the same bucket. 
   //reset pool - we have another dataset, we reconstruct the pool.
   PointHasher::gridPool = nullptr;
   auto phasher = new PointHasher(5,numDim,dataset->getMaxCoordinate()+1);
   set<size_t> uniqueBuckets;
   for (auto p: points) {
      uniqueBuckets.insert((*phasher)(p));
   }
   CU_ASSERT(uniqueBuckets.size() == 1);
   //second dataset (instructor's)
   lsh = new LSH();
   lsh->setInputFileGiven(true);
   lsh->setInputFilename("../src/testdata/input_small_id");
   lsh->setData(parseInputFilePoints(lsh->getInputFilename()));
   dataset = lsh->getData();
   numDim = dataset->getDimension();
   points = dataset->getPoints();
   printf("min is %f and max is %f",dataset->getMinCoordinate(),dataset->getMaxCoordinate()-100);  uniqueBuckets.clear();
   //reset pool - we have another dataset, we reconstruct the pool.
   phasher->gridPool = nullptr;
   //max-min - 40 is a good windows size ( max -min = 180 here).
   phasher = new PointHasher(7,numDim,dataset->getMaxCoordinate()-100);
   uniqueBuckets.clear();
   int i = 0;
   for (auto p: points) {
      uniqueBuckets.insert((*phasher)(p));
      i++;
   }
   printf("elems in set = %d and data set size = %d\n",uniqueBuckets.size(),dataset->getSize());
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

int main(int argc,char *argv[]) {
   CU_pSuite pSuite = NULL;
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }
   if ((NULL == CU_add_test(pSuite, "test of PointHasher constructor", test_PointHasher))||
       (NULL == CU_add_test(pSuite, "test of hash(obj,hashIndex) ", test_HashNonAmplified)) || 
       (NULL == CU_add_test(pSuite,"test amplified hash func",test_HashAmplified)))
      {
      CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}