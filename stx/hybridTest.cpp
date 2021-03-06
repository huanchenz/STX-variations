#include <iostream>
#include "btree.h"
#include "btree_map.h"
#include <stdint.h>

#define TEST_SIZE 1000

typedef stx::btree_map<uint64_t, uint64_t> btree_type;

int main() {
  btree_type btree;
  btree_type::iterator btree_iter;

  uint64_t key = 1;
  uint64_t value = 1;
  while (key < TEST_SIZE) {
    std::pair<btree_type::iterator, bool> retval
      = btree.insert(key, value);
    if (retval.second == false) {
      std::cout << "INSERT FAIL\n";
      return -1;
    }
    key += 2;
    value += 2;
  }

  key = 1;
  while (key < TEST_SIZE) {
    btree_iter = btree.find(key);
    if (btree_iter == btree.end()) {
      std::cout << "READ FAIL " << key << "\n";
      //return -1;
    }
    std::cout << btree_iter->second << " ";
    key += 2;
  }

  std::cout << "\n===========================================================================\n";

  key = 2;
  value = 2;
  while (key < TEST_SIZE) {
    std::pair<btree_type::iterator, bool> retval
      = btree.insert(key, value);
    if (retval.second == false) {
      std::cout << "INSERT FAIL\n";
      return -1;
    }
    key += 2;
    value += 2;
  }

  key = 1;
  while (key < TEST_SIZE) {
    btree_iter = btree.find(key);
    if (btree_iter == btree.end()) {
      std::cout << "READ FAIL " << key << "\n";
      //return -1;
    }
    std::cout << btree_iter->second << " ";
    key++;
  }

  key = 1;
  value = 1;
  while (key < TEST_SIZE) {
    std::pair<btree_type::iterator, bool> retval
      = btree.insert(key, value);
    if (retval.second == true) {
      std::cout << "DUPLICATE CHECK FAIL " << key << "\n";
      //return -1;
    }
    key += 1;
    value += 1;
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

  btree_iter = btree.begin();
  //btree_iter++;
  while (btree_iter != btree.end()) {
    std::cout << btree_iter->second << " ";
    btree_iter++;
  }

  std::cout << "\n===========================================================================\n";

  btree_iter--;
  while (btree_iter != btree.begin()) {
    std::cout << btree_iter->second << " ";
    btree_iter--;
  }

  std::cout << "\n===========================================================================\n";

  //btree_iter++;
  while (btree_iter != btree.end()) {
    std::cout << btree_iter->second << " ";
    btree_iter++;
  }

  std::cout << "\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";

  key = 1;
  while (key < TEST_SIZE) {
    if (!btree.erase_one(key)) {
      std::cout << "DELETE FAIL key = " << key << "\n";
      //return -1;
    }
    key += 2;
  }

  btree_iter = btree.begin();
  btree_iter++;
  while (btree_iter != btree.end()) {
    std::cout << btree_iter->second << " ";
    btree_iter++;
  }

  std::cout << "\n===========================================================================\n";

  key = 1;
  while (key < TEST_SIZE - 1) {
    btree_iter = btree.lower_bound(key);
    if (btree_iter == btree.end()) {
      std::cout << "SCAN FAIL " << key << "\n";
      //return -1;
    }
    std::cout << btree_iter->second << " ";
    key++;
  }

  std::cout << "\n";

  return 0;
}
