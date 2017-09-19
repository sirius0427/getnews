/*
 * stringlib.h
 *
 *  Created on: Jun 25, 2015
 *      Author: junhuili
 */

#ifndef STRINGLIB_H_
#define STRINGLIB_H_

#include <vector>
#include <string>
#include <stdarg.h>
#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include <sstream>


using namespace std;

// trim from start
inline std::string &fnStrLTrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
inline std::string &fnStrRTrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
inline std::string &fnStrTrim(std::string &s) {
        return fnStrLTrim(fnStrRTrim(s));
}

inline int fnSplitOnWhitespace(const std::string& in, std::vector<std::string>* out, bool bAppend = false) {
  if (bAppend == false)
    out->clear();
  unsigned i = 0;
  unsigned start = 0;
  std::string cur;

  while (i < in.size()) {
    while (i < in.size() && (in[i] == ' ' || in[i] == '\t'))
      i++;
    start = i;

    while (i < in.size()) {
      if (in[i] == ' ' || in[i] == '\t') {
        assert(i - start > 0);
        out->push_back(in.substr(start, i - start));
        break;
      }
      ++i;
    }
  }
  if (i > start)
    out->push_back(in.substr(start, i - start));
  return out->size();
}

/*inline int fnSplitOnWhitespace(const std::string& strIn,
    std::vector<std::string>* pvecOut) {
  pvecOut->clear();
  unsigned i = 0;
  unsigned start = 0;
  std::string cur;
  while (i < strIn.size()) {
    if (strIn[i] == ' ' || strIn[i] == '\t') {
      if (i - start > 0)
        pvecOut->push_back(strIn.substr(start, i - start));
      start = i + 1;
    }
    ++i;
  }
  if (i > start)
    pvecOut->push_back(strIn.substr(start, i - start));
  return pvecOut->size();
}*/

inline int fnSplitOnOneChar(const std::string& strIn,
    const std::string& strPattern, std::vector<std::string>* pvecOut, bool bDel) {
  pvecOut->clear();
  unsigned i = 0;
  unsigned start = 0;
  std::string cur;
  while (i < strIn.size()) {
    if (strPattern.find(strIn[i]) != string::npos) {
      if (i - start > 0)
        pvecOut->push_back(strIn.substr(start, i - start));
      if (bDel == true)
        pvecOut->push_back(strIn.substr(i, 1));
      start = i + 1;
    }
    ++i;
  }
  if (i > start)
    pvecOut->push_back(strIn.substr(start, i - start));
  return pvecOut->size();
}

inline std::vector<std::string> fnSplitOnWhitespace(std::string const& strIn) {
  std::vector<std::string> vec;
  fnSplitOnWhitespace(strIn, &vec);
  return vec;
}

inline int fnSplit(std::string const& strIn, std::string const& strPattern,
    std::vector<std::string>* pvecOut) {
  if (pvecOut != NULL)
    pvecOut->clear();

  int len = strPattern.size();
  int pre_pos;
  size_t cur_pos;
  pre_pos = -1 * len;
  int count = 0;
  string seg;
  while ((cur_pos = strIn.find(strPattern.c_str(), pre_pos + len))
      != std::string::npos) {

    seg = strIn.substr(pre_pos + len, cur_pos - pre_pos - len);
    if (pvecOut != NULL && seg.length() > 0)
      pvecOut->push_back(seg);
    count++;
    pre_pos = cur_pos;
  }
  cur_pos = strIn.size();

  seg = strIn.substr(pre_pos + len, cur_pos - pre_pos - len);
  if (pvecOut != NULL && seg.length() > 0)
    pvecOut->push_back(seg);
  count++;
  return count;
  return pvecOut->size();
}

inline std::vector<std::string> fnSplit(std::string const& strIn,
    std::string const& strPattern) {
  std::vector<std::string> vec;
  fnSplit(strIn, strPattern, &vec);
  return vec;
}

inline bool fnEndWith(const std::string& fullString,
    const std::string& ending) {
  if (fullString.length() >= ending.length()) {
    return (0
        == fullString.compare(fullString.length() - ending.length(),
            ending.length(), ending));
  } else {
    return false;
  }
}

inline bool fnStartWith(const std::string& fullString,
    const std::string& prefix) {
  return fullString.substr(0, prefix.size()) == prefix;
}

inline std::string fnLowerCase(const string& str) {
  std::string s;
  std::transform(str.begin(), str.end(), std::back_inserter(s), ::tolower);
  return s;
}

inline std::string fnJoinString(const vector<string>& vec,
    const string& strDelimiter) {
  std::string str = "";
  if (vec.size() == 0)
    return str;

  str = vec[0];
  for (size_t i = 1; i < vec.size(); i++)
    str += strDelimiter + vec[i];
  return str;
}

inline std::string fnPrint2String(const char* format, ...) {
  char dest[1024 * 16];
  va_list argptr;
  va_start(argptr, format);
  vsprintf(dest, format, argptr);
  va_end(argptr);
  string str = string(dest);
  return str;
}

inline std::string fnFindAndReplace(const std::string& source,
    std::string const& find, std::string const& replace) {
  string strTmp = source;
  for (string::size_type i = 0; (i = strTmp.find(find, i)) != string::npos;) {
    strTmp.replace(i, find.length(), replace);
    i += replace.length();
  }

  return strTmp;
}

inline std::string fnGetFileName(const std::string& filepath) {
  size_t i = filepath.find_last_of('/');
  if (i == std::string::npos)
    return filepath;
  else
    return filepath.substr(i + 1);
}

template<class Int>
inline std::string fnNum2String(Int i) {
  std::ostringstream oss;
  oss << i;
  string str = oss.str();
  return str;
}

inline int fnGetNumSubString(const std::string& str, const std::string& strSub) {
  int iCount = 0;
  int iStart = 0;
  size_t iPosi;
  while ((iPosi = str.find(strSub, iStart)) != string::npos) {
    iCount++;
    iStart = iPosi + strSub.length();
  }

  return iCount;
}

#include "hashlib.h"
inline double fnCalculateSimilarity(const std::string& str1, const std::string& str2) {
  vector<string> vec1;
  fnSplitOnWhitespace(str1, &vec1);
  vector<string> vec2;
  fnSplitOnWhitespace(str2, &vec2);

  MapString2Int map1, map2;
  for (size_t i = 0; i < vec1.size(); i++) {
    fnMapIncrease<MapString2Int>(map1, vec1[i], 1);
  }
  for (size_t i = 0; i < vec2.size(); i++) {
    fnMapIncrease<MapString2Int>(map2, vec2[i], 1);
  }

  double fNumerator = 0.0;
  for (IteratorString2Int iter = map1.begin(); iter != map1.end(); iter++) {
    int iCount;
    if (fnMapFind<MapString2Int>(map2, iter->first, &iCount)) {
      fNumerator += iter->second * iCount;
    }
  }
  double fSum1 = 0.0, fSum2 = 0.0;
  for (IteratorString2Int iter = map1.begin(); iter != map1.end(); iter++) {
    fSum1 += iter->second * iter->second;
  }
  for (IteratorString2Int iter = map2.begin(); iter != map2.end(); iter++) {
    fSum2 += iter->second * iter->second;
  }
  double fDenominator = sqrt(fSum1) * sqrt(fSum2);

  if (fDenominator == 0.0)
    return 0.0;
  return fNumerator / fDenominator;
}

#endif /* STRINGLIB_H_ */
