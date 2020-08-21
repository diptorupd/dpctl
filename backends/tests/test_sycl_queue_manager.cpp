#include "dppl_sycl_queue_interface.h"
#include "dppl_error_codes.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace dppl;

namespace
{
    void foo (size_t & num)
    {
        void *q1, *q2;

        DPPLSetAsCurrentQueue(&q1, dppl_sycl_device_type::DPPL_CPU, 0);
        DPPLSetAsCurrentQueue(&q2, dppl_sycl_device_type::DPPL_GPU, 0);
        // Capture the number of active queues in first
        DPPLGetNumActivatedQueues(num);
        DPPLRemoveCurrentQueue();
        DPPLRemoveCurrentQueue();
        DPPLDeleteQueue(q1);
        DPPLDeleteQueue(q2);
    }

    void bar (size_t & num)
    {
        void *q1;

        DPPLSetAsCurrentQueue(&q1, sycl_device_type::DPPL_GPU, 0);
        // Capture the number of active queues in second
        DPPLGetNumActivatedQueues(num);
        DPPLRemoveCurrentQueue();
        DPPLDeleteQueue(q1);
    }
}

struct TestDPPLSyclQueuemanager : public ::testing::Test
{

};

TEST_F (TestDPPLSyclQueuemanager, CheckGetNumPlatforms)
{
    size_t nPlatforms;
    auto ret = qmgr.getNumPlatforms(nPlatforms);
    EXPECT_EQ(DPPL_SUCCESS, ret);
}

TEST_F (TestDPPLSyclQueuemanager, CheckGetNumActivatedQueues)
{
    size_t num0, num1, num2, num4;
    void *q;

    // Add a queue to main thread
    qmgr.setAsCurrentQueue(&q, dppl_sycl_device_type::DPPL_CPU, 0);

    std::thread first (foo, std::ref(qmgr), std::ref(num1));
    std::thread second (bar, std::ref(qmgr), std::ref(num2));

    // synchronize threads:
    first.join();
    second.join();

    // Capture the number of active queues in first
    DPPLGetNumActivatedQueues(num0);
    DPPLRemoveCurrentQueue();
    DPPLGetNumActivatedQueues(num4);

    // Verify what the expected number of activated queues each time a thread
    // called getNumActivatedQueues.
    EXPECT_EQ(num0, 1);
    EXPECT_EQ(num1, 2);
    EXPECT_EQ(num2, 1);
    EXPECT_EQ(num4, 0);

    DPPLDeleteQueue(q);
}

int
main (int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
