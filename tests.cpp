
/*
 Project 5:  myMap 
 File name: test.cpp Author: Arij Khan  NetId: akhan342  Course: CS 251
 System: Visual Studio
*/
#include <gtest/gtest.h>
#include "mymap.h"
#include <map>
#include "myrandom.h"

TEST(mymap, testDefaultConstructor) {
    mymap<int, int> map;
    EXPECT_EQ(map.Size(), 0);
    mymap<string, int> strMap;
    EXPECT_EQ(strMap.Size(), 0);
    mymap<char, int> charMap;
    EXPECT_EQ(charMap.Size(), 0);
}

TEST(mymap, testPut) {
    mymap<int, int> map;
    int n = 10;
    int array[] = {30, 15, 50, 8, 25, 70, 20, 28, 40, 60};

    for (int i = 0; i < n; i++) {
        map.put(array[i], array[i]);
    }

    EXPECT_EQ(map.Size(), 10);

    mymap<string, int> stringMap;
    string words[] = {"lebron", "kobe", "giannis", "blake", "kd", "russ", "kyrie", "pau", "curry", "klay klay"};
    int vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        stringMap.put(words[i], vals[i]);
    }
    EXPECT_EQ(stringMap.Size(), 10);

}

TEST(mymap, testContains) {
    mymap<int, int> map;
    int array[] = {1, 2, 0};
    int notInArray[] = {3, 7, 8, 10};
    for (int i = 0; i < 3; i++) {
        map.put(array[i], array[i]); 
    }
    for (int i = 0; i < 3; i++) {
        EXPECT_TRUE(map.contains(array[i]));
    }
    for (int i = 0; i < 4; i++) {
        EXPECT_FALSE(map.contains(notInArray[i]));
    }
    EXPECT_EQ(map.Size(), 3); 

    //test with strings 
    mymap<string, string> mapTest;
    string lineUp[] = {"dRose", "DWade", "Jimmy", "Pau", "Noah"};
    string trashLineup[] = {"Kyrie", "Jr", "lebron", "love", "thompson"};
    int vals[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        mapTest.put(lineUp[i], lineUp[i]);
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_TRUE(mapTest.contains(lineUp[i]));
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_FALSE(mapTest.contains(trashLineup[i]));
    }
    EXPECT_EQ(mapTest.Size(), 5);
}

TEST(mymap, testGet) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(map.get(arr[i]), arr[i]);
    }

    mymap<string, int> stringMap;
    string strs[] = {"hello", "apple", "box", "tree", "where"};
    int vals[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        stringMap.put(strs[i], vals[i]);
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(stringMap.get(strs[i]), vals[i]);
    }
}

TEST(mymap, testToString) {
    mymap<int, int> map;
    int array[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(array[i], array[i]);
    }

    string check = "key: 1 value: 1\nkey: 2 value: 2\nkey: 3 value: 3\n";
    EXPECT_EQ(check, map.toString());


  mymap<string, int> stringMap;
    string strs[] = {"hello", "apple", "box", "tree", "where"};
    int vals[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        stringMap.put(strs[i], vals[i]);
    }
    string sol2 = "key: apple value: 2\nkey: box value: 3\nkey: hello value: 1\nkey: tree value: 4\nkey: where value: 5\n";
    EXPECT_EQ(sol2, stringMap.toString());
    
}

TEST(mymap, testSquareBrackets) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(map[arr[i]], arr[i]);
    }

    mymap<string, int> stringMap;
    string strs[] = {"hello", "apple", "box", "tree", "where"};
    int vals[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        stringMap.put(strs[i], vals[i]);
    }
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(stringMap[strs[i]], vals[i]);
    }
}

TEST(mymap, testIterators) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    int order[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    int i = 0;
    for (auto key : map) {
        EXPECT_EQ(order[i++], key);
    }
}

TEST(mymap, testRepeatedValues) {
    mymap<int, int> map;
    int keys[] = {5, 6, 4, 3, 8, 9, 2, 1};
    int values[] = {5, 6, 4, 3, 8, 9, 2, 1};
    for (int i = 0; i < 8; i++) {
        map.put(keys[i], values[i]);
    }
    map.put(1, 0);
    EXPECT_EQ(map[1], 0);
}
// netid: arwah
TEST(mymap, testClear) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    map.clear();
    EXPECT_EQ(map.Size(), 0);
}

TEST(mymap, testOperatorEquals) {
    mymap<int, int> map;
    int keys[] = {5, 6, 4, 3, 8, 9, 2, 1};
    int values[] = {5, 6, 4, 3, 8, 9, 2, 1};
    for (int i = 0; i < 8; i++) {
        map.put(keys[i], values[i]);
    }

    mymap<int, int> copyMap;
    copyMap = map;
    EXPECT_EQ(map.Size(), copyMap.Size());
    for (int i = 0; i < 8; i++) {
        EXPECT_TRUE(copyMap.contains(keys[i]));
        EXPECT_EQ(copyMap.get(keys[i]), values[i]);
    }

    string sol = map.toString();
    EXPECT_EQ(copyMap.toString(), sol);
}

TEST(mymap, testCopyConstructor) {
    mymap<int, int> map;
    int keys[] = {5, 6, 4, 3, 8, 9, 2, 1};
    int values[] = {5, 6, 4, 3, 8, 9, 2, 1};
    for (int i = 0; i < 8; i++) {
        map.put(keys[i], values[i]);
    }

    mymap<int, int> copyMap = map;
    EXPECT_EQ(map.Size(), copyMap.Size());
    for (int i = 0; i < 8; i++) {
        EXPECT_TRUE(copyMap.contains(keys[i]));
        EXPECT_EQ(copyMap.get(keys[i]), values[i]);
    }

    string sol = map.toString();
    EXPECT_EQ(copyMap.toString(), sol);
}

TEST(mymap, testToVector) {
    mymap<int, int> map;
    int arr[] = {2, 1, 3};
    for (int i = 0; i < 3; i++) {
        map.put(arr[i], arr[i]);
    }
    vector<pair<int, int>> sol;
    sol.push_back(make_pair(1, 1));
    sol.push_back(make_pair(2,2));
    sol.push_back(make_pair(3, 3));
    EXPECT_EQ(sol, map.toVector());

    mymap<string, int> stringMap;
    string strs[] = {"hello", "apple", "box", "tree", "where"};
    int vals[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        stringMap.put(strs[i], vals[i]);
    }
    vector<pair<string, int>> sol2;
    sol2.push_back(make_pair("apple", 2));
    sol2.push_back(make_pair("box", 3));
    sol2.push_back(make_pair("hello", 1));
    sol2.push_back(make_pair("tree", 4));
    sol2.push_back(make_pair("where", 5));
    EXPECT_EQ(sol2, stringMap.toVector());
}


TEST(mymap, randomNums) {
    map<int, int> mapSol;
    mymap<int, int> map;
    int n = 1000000;
    for (int i = 1; i <= n; i++) {
//        int key = randomInteger(0, 10000);
//        int val = randomInteger(0, 10000);
        int key = rand() % 10000;
        int val = rand() % 10000;
        map.put(key, val);
        mapSol[key] = val;
    }

    EXPECT_EQ(map.Size(), mapSol.size());

    stringstream solution("");
    vector<pair<int, int>> solVector;
    for (auto e : mapSol) {
        solution << "key: " << e.first << " value: " << e.second << endl;
        solVector.push_back(e);
        EXPECT_TRUE(map.contains(e.first));
        EXPECT_EQ(map.get(e.first), e.second);
    }

    EXPECT_EQ(map.toString(), solution.str());
    EXPECT_EQ(solVector, map.toVector());
}



// netid: rshah268
// Copy and Clear Stress Test
TEST(mymap, Copy) {
    
    // Create two mymaps m1 and m2
    mymap<int, int> m1;
    mymap<int, int> m2;
    int n = 10000;
    
    for(int  i = 0; i < n; i++) {

        // Generate two random numbers
        int key = randomInteger(0, 100000);
        int val = randomInteger(0, 100000);

        // Insert them in map1
        m1.put(key, val);

        // Insert different elements in map2
        if(i % 2) {
            m2.put(val, key);
        }
    }

    // At this point they must be unequal
    ASSERT_NE(m1.Size(), m2.Size());

    // Set map2 equals to map1
    m2 = m1;

    // Both should be the same size and contain the same elements
    ASSERT_EQ(m1.Size(), m2.Size());
    ASSERT_EQ(m1.toString(), m2.toString());

    // Clear map1
    m1.clear();

    // Now they are unequal again
    ASSERT_NE(m1.Size(), m2.Size());
    // Map1 must be empty
    ASSERT_EQ(m1.Size(), 0);
}
