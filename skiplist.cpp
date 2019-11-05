//
// Created by Yusuf Pisan on 4/26/18.
//

#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

ostream &operator<<(ostream &Out, const SkipList &SkipL) {
  return Out;
}

SkipList::SNode::SNode(int Data) {}

SkipList::SkipList(int Depth) {
}

bool SkipList::alsoHigher() const { return false; }


bool SkipList::add(int Data) {
  return true;
}

void SkipList::addBefore(SNode *NewNode, SNode *NextNode) {
}

SkipList::~SkipList() {
  // need to delete individual nodes
}

bool SkipList::remove(int Data) { return false; }

bool SkipList::contains(int Data) {
  return false;
}
