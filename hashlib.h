/*
 * hashlib.h
 *
 *  Created on: Jun 30, 2015
 *      Author: lijunhui
 */

#ifndef HASHLIB_H_
#define HASHLIB_H_

#include <string>
#include <boost/unordered_map.hpp>

using namespace std;

typedef boost::unordered_map<std::string, int> MapString2Int;
typedef boost::unordered_map<std::string, int>::iterator IteratorString2Int;
typedef boost::unordered_map<std::string, int>::const_iterator ConstIteratorString2Int;

typedef boost::unordered_map<std::string, double> MapString2Double;
typedef boost::unordered_map<std::string, double>::iterator IteratorString2Double;
typedef boost::unordered_map<std::string, double>::const_iterator ConstIteratorString2Double;

typedef boost::unordered_map<std::string, std::vector<string> > MapString2VecString;
typedef boost::unordered_map<std::string, std::vector<string> >::iterator IteratorString2VecString;

typedef boost::unordered_map<std::string, std::string> MapString2String;
typedef boost::unordered_map<std::string, std::string>::iterator IteratorString2String;
typedef boost::unordered_map<std::string, std::string>::const_iterator ConstIteratorString2String;


/*template <typename keyType, typename valueType>
inline void fnIncrease(std::map<keyType, valueType>& m, keyType& k, valueType v) {
  std::map<keyType, valueType>::iterator iter = m.find(k);
  if (iter == m.end())
    m[k] = v;
  else
    iter->second += v;
}*/


template <class MapClass, class KeyClass, class ValueClass>
inline bool fnMapFind(const MapClass& m, const KeyClass& key, ValueClass* pval) {
  typename MapClass::const_iterator iter = m.find(key);
  if (iter == m.end()) {
    return false;
  } else {
    if (pval) *pval = iter->second;
    return true;
  }
}



template <class MapClass, class KeyClass, class ValueClass>
inline ValueClass fnMapIncrease(MapClass& m, const KeyClass& key, ValueClass val) {
  typename MapClass::iterator iter = m.find(key);
  if (iter == m.end()) {
    m[key] = val;
    return val;
  } else {
    iter->second += val;
    return iter->second;
  }
}

template <class MapClass, class KeyClass, class ValueClass>
inline void fnMapCrossProduct(const MapClass& m1, const MapClass& m2, MapClass& m3) {
  for (typename MapClass::const_iterator iter1 = m1.begin(); iter1 != m1.end(); iter1++) {
    for (typename MapClass::const_iterator iter2 = m2.begin(); iter2 != m2.end(); iter2++) {
      KeyClass k = iter1->first + string("_") + iter2->first;
      ValueClass v = iter1->second * iter2->second;
      m3[k] = v;
    }
  }
}


template <class MapClass, class KeyClass, class ValueClass>
inline bool fnMapRemove(MapClass& m, const KeyClass& key, ValueClass* pval) {
  typename MapClass::const_iterator iter = m.find(key);
    if (iter == m.end()) {
      return false;
    } else {
      if (pval) *pval = iter->second;
      m.erase(iter);
      return true;
    }
}


#endif /* HASHLIB_H_ */
