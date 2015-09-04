#include <iostream>
#include "btree.h"
#include "btree_multimap.h"
#include <stdint.h>

#define TEST_SIZE 1000
#define VALUES_PER_KEY 10

typedef stx::btree_multimap<uint64_t, uint64_t> btree_type;

int main() {
  btree_type btree;
  btree_type::iterator btree_iter;
  std::pair<btree_type::iterator, btree_type::iterator> iter_pair;

  uint64_t key = 1;
  uint64_t value = 1;
  for (int i = 0; i < VALUES_PER_KEY; i++) {
    while (key < TEST_SIZE) {
      btree.insert(key, value);
      key += 2;
    }
    key = 1;
    value++;
  }

  key = 1;
  while (key < TEST_SIZE) {
    iter_pair = btree.equal_range(key);
    if (iter_pair.first == iter_pair.second) {
      std::cout << "READ FAIL " << key << "\n";
      //return -1;
    }
    std::cout << "key = " << key << "\tvalue = ";
    while (iter_pair.first != iter_pair.second) {      
      std::cout << iter_pair.first->second << " ";
      iter_pair.first++;
    }
    std::cout << "\n";
    key += 2;
  }

  std::cout << "\n===========================================================================\n";

  key = 2;
  value = 1;
  for (int i = 0; i < VALUES_PER_KEY; i++) {
    while (key < TEST_SIZE) {
      btree.insert(key, value);
      key += 2;
    }
    key = 2;
    value++;
  }

  key = 1;
  while (key < TEST_SIZE) {
    iter_pair = btree.equal_range(key);
    if (iter_pair.first == iter_pair.second) {
      std::cout << "READ FAIL " << key << "\n";
      //return -1;
    }
    std::cout << "key = " << key << "\tvalue = ";
    while (iter_pair.first != iter_pair.second) {      
      std::cout << iter_pair.first->second << " ";
      iter_pair.first++;
    }
    std::cout << "\n";
    key ++;
  }

  std::cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

  key = 1;
  while (key < TEST_SIZE) {
    btree_iter = btree.lower_bound(key);
    if (btree_iter == btree.end()) {
      std::cout << "SCAN FAIL " << key << "\n";
      //return -1;
    }
    std::cout << btree_iter->second << " ";
    key++;
  }

  std::cout << "\n===========================================================================\n";

  key = 1;
  while (key < TEST_SIZE) {
    btree_iter = btree.upper_bound(key);
    if (btree_iter == btree.end()) {
      std::cout << "SCAN FAIL " << key << "\n";
      //return -1;
    }
    else {
      std::cout << btree_iter->second << " ";
    }
    key++;
  }

  std::cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

  btree_iter = btree.begin();
  int count = 0;
  while (btree_iter != btree.end()) {
    std::cout << btree_iter->second << " ";
    btree_iter++;
    count++;
    if (count >= VALUES_PER_KEY) {
      count = 0;
      std::cout << "\n";
    }
  }

  std::cout << "\n===========================================================================\n";

  btree_iter--;
  count = 0;
  while (btree_iter != btree.begin()) {
    std::cout << btree_iter->second << " ";
    btree_iter--;
    count++;
    if (count >= VALUES_PER_KEY) {
      count = 0;
      std::cout << "\n";
    }
  }

  std::cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

  key = 1;
  count = 0;
  while (key < TEST_SIZE) {
    btree_iter = btree.lower_bound(key);
    while (btree_iter->second != (uint64_t)5) {
      btree_iter++;
    }
    btree.erase(btree_iter);
    key++;
  }

  btree_iter = btree.begin();
  while (btree_iter != btree.end()) {
    std::cout << btree_iter->second << " ";
    btree_iter++;
    count++;
    if (count >= VALUES_PER_KEY - 1) {
      count = 0;
      std::cout << "\n";
    }
  }

  std::cout << "\n===========================================================================\n";

  return 0;
}
