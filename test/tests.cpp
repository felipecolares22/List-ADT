#include <iterator>             // std::begin(), std::end()
#include <functional>           // std::function
#include <algorithm>            // std::min_element
#include <vector>

#include "gtest/gtest.h"        // gtest lib
#include "list.h"   			// header file for tested functions


// ============================================================================
// TESTING VECTOR AS A CONTAINER OF INTEGERS
// ============================================================================s

// WITH ERRORS
// TEST(IntVector, ErasePos)
// {
//     // Initial vector.
//     sc::vector<int> vec { 1, 2, 3, 4, 5 };

//     // removing a single element.
//     vec = { 1, 2, 3, 4, 5 };
//     auto past_last = vec.erase( vec.begin() );
//     ASSERT_EQ( vec , ( sc::vector<int>{ 2, 3, 4, 5 } ) );
//     ASSERT_EQ( vec.begin() , past_last );
//     ASSERT_EQ( vec.size() , 4 );

//     // removing a single element in the middle.
//     vec = { 1, 2, 3, 4, 5 };
//     past_last = vec.erase( vec.begin()+2 );
//     ASSERT_EQ( vec , ( sc::vector<int>{ 1, 2, 4, 5 } ) );
//     ASSERT_EQ( vec.begin()+2 , past_last );
//     ASSERT_EQ( vec.size() , 4 );

//     // removing a single element at the end.
//     vec = { 1, 2, 3, 4, 5 };
//     past_last = vec.erase( vec.begin()+vec.size()-1 );
//     ASSERT_EQ( vec , ( sc::vector<int>{ 1, 2, 3, 4 } ) );
//     ASSERT_EQ( vec.end() , past_last );
//     ASSERT_EQ( vec.size() , 4 );
// }

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
