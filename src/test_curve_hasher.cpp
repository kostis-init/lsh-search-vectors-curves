#define private public
#include <random>
#include <set>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "hasher.h"
#include "LSH.h"
#include "Point.h"
#include "Curve.h"


static FILE* temp_file = NULL;
LSH<CurveHasher> *lsh;
using namespace std;

void test_CurveHasher() {
    auto chasher = new CurveHasher(2,10,10);
    for (int i =0; i < 2; i++)
        CU_ASSERT(chasher->shiftedGrid[i] < 2.0);
    chasher = new CurveHasher(7,10,10);
    for (int i =0; i < 7; i++)
        CU_ASSERT(chasher->shiftedGrid[i] < 7.0);
}

void test_snap() {
    auto chasher = new CurveHasher(2,3,3);    
    auto delta = 4 * 2 * 3 ;
    auto point = new Point("1");
    point->addCoordinateLast(90.4329482); point->addCoordinateLast(14.5342342);
    auto snaped = chasher->snap(point);
    //double precision may be inaccurate so 
    //ensure we are approximately near the expected results.
    CU_ASSERT(fabs(snaped[0] - 4.0 * double(delta)) < 2.0);
    CU_ASSERT(fabs(snaped[1] - 1.0 * double(delta)) < 2.0);
    //create four points that should lie on the same grid curve
    //but have different coordinates
    auto point2 = new Point("2");
    point2->addCoordinateLast(14.955); point2->addCoordinateLast(102.1344);
    auto point3 = new Point("3");
    point3->addCoordinateLast(28.0002); point3->addCoordinateLast(94.000772);
    auto point4 = new Point("4");
    point4->addCoordinateLast(34.9933); point4->addCoordinateLast(100.000772);
    auto point5 = new Point("5");
    point5->addCoordinateLast(24.94203482); point5->addCoordinateLast(96.432984);
    snaped = chasher->snap(point2);
    auto snaped2 = chasher->snap(point3);
    auto snaped3 = chasher->snap(point4);
    auto snaped4 = chasher->snap(point5);
    CU_ASSERT(snaped[0] == snaped2[0] && snaped3[0] == snaped4[0]);
    CU_ASSERT(snaped[0] == snaped3[0] && snaped2[0] == snaped4[0]);
    CU_ASSERT(snaped[1] == snaped2[1] && snaped3[1] == snaped4[1]);
    CU_ASSERT(snaped[1] == snaped3[1] && snaped2[1] == snaped4[1]);
    //create two points that should NOT lie on the same grid curve
    point = new Point("6");
    point->addCoordinateLast(14.955); point->addCoordinateLast(102.1344);
    point3 = new Point("7");
    point3->addCoordinateLast(5.0002); point3->addCoordinateLast(66.000772);
    snaped = chasher->snap(point);
    snaped2 = chasher->snap(point3);
    CU_ASSERT(snaped[0] != snaped2[0] && snaped[1] != snaped2[1]);
}

void test_Hash() {
    int curveLen = 50;
    int numCurves = 20;
    vector<Point> pointVec;
    vector<Curve> curveVec;
    int lower = 0; 
    int upper = 1000;
    uniform_real_distribution<double> dist(lower,upper);
    default_random_engine re;
    for (int j=0; j < numCurves; j++) {
        for (int i=0; i < curveLen; i++) 
            pointVec.push_back(*(new Point(vector<double> (dist(re),dist(re)))));
        curveVec.push_back(*(new Curve(pointVec)));
    }
    //delta 4 * 2 * 50 = 400
    auto chasher = new CurveHasher(2,50,50);
    size_t bucket;
    set<size_t> buckets;
    Point *prev,*curr = nullptr;
    int sum =0;
    for (int i=0; i < numCurves; i++) {
        //chasher->snap(&curveVec.at(i));
        //bucket = (*chasher)(&curveVec.at(i));
        curr = chasher->vectorize(chasher->snap(&curveVec.at(i)));
        if (prev != nullptr)
            if (*prev == *curr)
                sum++;
        //buckets.insert(bucket);
        prev = curr;
    }
    //printf("\nbucket last is %d\n",bucket);
    //printf("bucket count is %d\n",buckets.size());
    printf("sum of consecutive equal points is  %d\n",sum);
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
   if ((NULL == CU_add_test(pSuite, "test of CurveHasher constructor", test_CurveHasher))||
       (NULL == CU_add_test(pSuite, "test of round Coordinate", test_snap)) || 
       (NULL == CU_add_test(pSuite,"test amplified hash func",test_Hash)))
      {
      CU_cleanup_registry();
      return CU_get_error();
   }
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
