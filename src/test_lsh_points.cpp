#include <ctime>
#include <limits>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "LSH.h"
#include "parse_files.h"
#include "search.h"

static FILE* temp_file = NULL;
using namespace std;


LSH *LoadInput(string inputFilename,string queryFilename) {
    auto lsh = new LSH();
    lsh->setInputFilename(inputFilename);
    lsh->setData(parseInputFilePoints(lsh->getInputFilename()));
    //TODO: change this when we have a good formula for window.
    //change this value to experiment with performance of LSH.
    lsh->getDataset()->setMean(112);
    lsh->setHashTableStruct(new PointHashTableStruct(lsh->getNumOfHashTables(), lsh->getDataset()->getSize(),lsh->getNumOfFunctions(),lsh->getDataset()->getDimension(),lsh->getDataset()->getMean()));
    auto points = lsh->getDataset()->getData();
    for (auto & point : points)
        lsh->getHashTableStruct()->addToAllHashTables(point);
    lsh->setQueryFilename(queryFilename);
    lsh->setQueryData(parseQueryFilePoints(lsh->getQueryFilename()));
    return lsh;
}

void DoQueries(LSH *lsh) {
    auto hts = lsh->getHashTableStruct()->getAllHashTables();
    auto hashers = lsh->getHashTableStruct()->getHashers();
    int numOfHashTables = lsh->getNumOfHashTables();
    int querySize = lsh->getQueryData()->getSize();
    auto data = lsh->getDataset()->getData();
    auto queryData = lsh->getQueryData()->getData();
    clock_t meanSearchLSH = 0;
    clock_t meanSearchBF = 0;
    double maxAF = numeric_limits<double>::min();
    double averageAF = 0;
    int averageAFCount = 0;
    for (int i = 0; i < querySize; ++i) {
        Point* queryPoint = (Point*)queryData.at(i);
        Point* nnPoint;
        double distanceLSH;
        double distanceBF;
        clock_t begin = clock();
        search_LSH(&nnPoint, &distanceLSH, numOfHashTables, hashers, queryPoint, hts);
        clock_t end = clock();
        meanSearchLSH += (end-begin);
        begin = clock();
        search_BruteForce(&nnPoint, &distanceBF, data, queryPoint);
        end = clock();
        meanSearchBF += (end-begin);
        double AF;
        if ((AF = distanceLSH/distanceBF) > maxAF) 
            maxAF = AF;
        if (distanceLSH) {//compute only if > 0
            averageAF += distanceLSH/distanceBF;
            averageAFCount++;
        }
    }
    cout << "meanTimeSearchLSH " << meanSearchLSH/querySize << " meanTimeSearchBF " << meanSearchBF/querySize << " and maxAF = " << maxAF << " and averageAF " << averageAF/averageAFCount << endl;
}

void test_File(string inputFilename,string queryFilename) {
    auto lsh = LoadInput(inputFilename,queryFilename);
    DoQueries(lsh);
}

void test_LSHPoints() {
    test_File("../src/testdata/input_small_id","../src/testdata/query_small_id");
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
   if ((NULL == CU_add_test(pSuite, "test of PointHasher constructor", test_LSHPoints)))
         {
         CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
