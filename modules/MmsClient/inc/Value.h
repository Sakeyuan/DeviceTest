/************************************************************************/
/* SISCO SOFTWARE MODULE HEADER *****************************************/
/************************************************************************/
/*   (c) Copyright Systems Integration Specialists Company, Inc.,       */
/*	   2006, All Rights Reserved   					*/
/*									*/
/* MODULE NAME : Value.h						*/
/* PRODUCT(S)  : Generic Value class					*/
/*									*/
/* MODULE DESCRIPTION :                                                 */
/*									*/
/* MODIFICATION LOG :                                                   */
/*  Date     Who   Rev      Comments                                    */
/* --------  ---  ------   -------------------------------------------  */
/* 03/12/07  DSF     02    Added ToString (ValType)			*/
/* 10/23/06  DSF     01    Created					*/
/************************************************************************/

#ifndef _VALUE_H
#define _VALUE_H

#if defined (_WIN32)
#if !defined (_CRT_SECURE_NO_DEPRECATE)
#define _CRT_SECURE_NO_DEPRECATE
#endif
#if defined (_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES)
#undef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#endif
#pragma warning(disable : 4786 4800)
#endif

#include <vector>
#include <string>
#include <bitset>
#include <stdexcept>
using namespace std;

#include <time.h>

#include "stdtime.h"
#include "stdtime_cpp_ops.h"

namespace SISCO
{
namespace ValueNS
{

enum ValType
  {
  vtUndefined = 0,
  vtInteger,
  vtUnsigned,
  vtFloat,
  vtDouble,
  vtBoolean,
  vtDateTime,
  vtString,
  vtBitset,
  vtByteArray
  };

const unsigned MAX_BITSET_SIZE		= 256;

typedef bitset<MAX_BITSET_SIZE>		BitSet;
typedef vector<unsigned char>		ByteArray;

class Value
  {
public:
  ValType		valueType;
  struct tagV
    {
    long			intValue;
    unsigned long		uintValue;
    float			floatValue;
    double			doubleValue;
    bool			boolValue;
    STDTIME			dateTimeValue;
    string			stringValue;
    BitSet			bitsetValue;
    ByteArray			byteArrayValue;
    } v;
  
  virtual ~Value () {}
  
  Value ();
  Value (const Value& val);
  Value (const char val);
  Value (const unsigned char val);
  Value (const short val);
  Value (const unsigned short val);
  Value (const int val);
  Value (const unsigned val);
  Value (const long val);
  Value (const unsigned long val);
  Value (const float val);
  Value (const double val);
  Value (const bool val);
  Value (const STDTIME& val);
  Value (const string& val);
  Value (const char *pString);
  Value (const unsigned char *pString);
  template <unsigned Bits> Value (const bitset<Bits>& val)
    {
    if (val.size () > MAX_BITSET_SIZE)
      throw out_of_range ("vtBitset too big");
    valueType = VT_BITSET;
    m_bitCount = val.size ();
    for (int i = 0; i < m_bitCount; ++i)
      v.bitsetValue.set (i) = val.test (i);
    }
  template <unsigned Bits> Value (const bitset<Bits>& val, unsigned int count)
    {
    if (count > MAX_BITSET_SIZE)
      throw out_of_range ("vtBitset too big");
    if (count > val.size ())
      throw invalid_argument ("Count too big");
    valueType = VT_BITSET;
    m_bitCount = count;
    for (int i = 0; i < count; ++i)
      v.bitsetValue.set (i) = val.test (i);
    }
  Value (const ByteArray& val);
  Value (const unsigned char *pByteArray, unsigned int count);
  
  Value& operator= (const Value& val);
  Value& operator= (const char val);
  Value& operator= (const unsigned char val);
  Value& operator= (const short val);
  Value& operator= (const unsigned short val);
  Value& operator= (const int val);
  Value& operator= (const unsigned val);
  Value& operator= (const long val);
  Value& operator= (const unsigned long val);
  Value& operator= (const float val);
  Value& operator= (const double val);
  Value& operator= (const bool val);
  Value& operator= (const STDTIME& val);
  Value& operator= (const string& val);
  Value& operator= (const char *pString);
  Value& operator= (const unsigned char *pString);
  template <unsigned Bits> Value& operator= (const bitset<Bits>& val)
    {
    if (val.size () > MAX_BITSET_SIZE)
      throw out_of_range ("vtBitset too big");
    valueType = vtBitset;
    m_bitCount = val.size ();
    for (int i = 0; i < m_bitCount; ++i)
      v.bitsetValue.set (i) = val.test (i);
    return *this;
    }
  Value& operator= (const ByteArray& val);
    
  bool operator== (const Value& val) const;
  bool operator== (const char val) const;
  bool operator== (const unsigned char val) const;
  bool operator== (const short val) const;
  bool operator== (const unsigned short val) const;
  bool operator== (const int val) const;
  bool operator== (const unsigned val) const;
  bool operator== (const long val) const;
  bool operator== (const unsigned long val) const;
  bool operator== (const float val) const;
  bool operator== (const double val) const;
  bool operator== (const bool val) const;
  bool operator== (const STDTIME& val) const;
  bool operator== (const string& val) const;
  bool operator== (const char *pString) const;
  bool operator== (const unsigned char *pString) const;
  template <unsigned Bits> bool operator== (const bitset<Bits>& val) const
    {
    if (valueType != vtBitset)
      return false;
    if (val.size () != m_bitCount)
      return false;
    return val == v.bitsetValue;
    }
  bool operator== (const ByteArray& val) const;

  bool operator!= (const Value& val) const
    {
    return !operator== (val);
    }
  bool operator!= (const char val) const
    {
    return !operator== (val);
    }
  bool operator!= (const unsigned char val) const
    {
    return !operator== (val);
    }
  bool operator!= (const short val) const
    {
    return !operator== (val);
    }
  bool operator!= (const unsigned short val) const
    {
    return !operator== (val);
    }
  bool operator!= (const int val) const
    {
    return !operator== (val);
    }
  bool operator!= (const unsigned val) const
    {
    return !operator== (val);
    }
  bool operator!= (const long val) const
    {
    return !operator== (val);
    }
  bool operator!= (const unsigned long val) const
    {
    return !operator== (val);
    }
  bool operator!= (const float val) const
    {
    return !operator== (val);
    }
  bool operator!= (const double val) const
    {
    return !operator== (val);
    }
  bool operator!= (const bool val) const
    {
    return !operator== (val);
    }
  bool operator!= (const STDTIME& val) const
    {
    return !operator== (val);
    }
  bool operator!= (const string& val) const
    {
    return !operator== (val);
    }
  bool operator!= (const char *pString) const
    {
    return !operator== (pString);
    }
  bool operator!= (const unsigned char *pString) const
    {
    return !operator== (pString);
    }
  template <unsigned Bits> bool operator!= (const bitset<Bits>& val) const
    {
    return !operator== (val);
    }
  bool operator!= (const ByteArray& val) const
    {
    return !operator== (val);
    }
  
  void SetValueType (const ValType valType) 
    {
    valueType = valType;
    }
  
  void SetValue (const Value& val);
  void SetValue (const char val);
  void SetValue (const unsigned char val);
  void SetValue (const short val);
  void SetValue (const unsigned short val);
  void SetValue (const int val);
  void SetValue (const unsigned val);
  void SetValue (const long val);
  void SetValue (const unsigned long val);
  void SetValue (const float val);
  void SetValue (const double val);
  void SetValue (const bool val);
  void SetValue (const STDTIME& val);
  void SetValue (const string& val);
  void SetValue (const char *pString);
  void SetValue (const unsigned char *pString);
  template <unsigned Bits> void SetValue (const bitset<Bits>& val)
    {
    SetValue (val, (unsigned int) val.size ());
    }
  template <unsigned Bits> void SetValue (const bitset<Bits>& val, unsigned int count)
    {
    if (count > MAX_BITSET_SIZE)
      throw out_of_range ("vtBitset too big");
    if (count > val.size ())
      throw invalid_argument ("Count too big");
      
    switch (valueType)
      {
      case vtUndefined:
        valueType = vtBitset;
        m_bitCount = count;
        for (unsigned int i = 0; i < count; ++i)
          v.bitsetValue.set (i) = val.test (i);
      break;
      case vtInteger:
      case vtUnsigned:
      case vtFloat:
      case vtDouble:
      case vtDateTime:
      case vtByteArray:
        throw out_of_range ("Incompatible types");
      break;
      case vtString:
        v.stringValue = val.template to_string<char, char_traits<char>, allocator<char> > ();
      break;
      case vtBitset:
        m_bitCount = count;
        for (unsigned int i = 0; i < count; ++i)
          v.bitsetValue.set (i) = val.test (i);
      break;
      default:
        throw invalid_argument ("Invalid value type");
      break;
      }
    }
  void SetValue (const ByteArray& val);
  void SetValue (const unsigned char *pByteArray, unsigned int count);
  
  ValType GetValueType () const 
    {
    return valueType;
    }
  
  int GetBitsetSize () const
    {
    if (valueType != vtBitset)
      out_of_range ("Value not bitset");
    return m_bitCount;
    }
  
  long GetValueAsInteger () const;
  unsigned long GetValueAsUnsigned () const;
  float GetValueAsFloat () const;
  double GetValueAsDouble () const;
  bool GetValueAsBool () const;
  STDTIME GetValueAsDateTime () const;
  string GetValueAsString () const;
  BitSet GetValueAsBitset () const;
  ByteArray GetValueAsByteArray (unsigned index = 0, unsigned count = 0xFFFFFFFF) const;
  
  string ToString () const;
  
  void Clear ()
    {
    valueType = vtUndefined;
    v.bitsetValue.reset ();
    v.byteArrayValue.clear ();
    }
    
  void ChangeValueType (ValType valType);
  
private:
  unsigned int		m_bitCount;
  };
typedef vector<Value>		Values;  

string DateTimeToString (const STDTIME& dateTime);
void StringToDateTime (const string& str, STDTIME& dateTime);

string ByteArrayToString (const ByteArray& byteArray);
string ByteArrayToString (const unsigned char *pByteArray, unsigned count);
void StringToByteArray (const string& str, ByteArray& byteArray);

template <unsigned Bits> void BitsetToByteArray (const bitset<Bits>& bitset, unsigned count, ByteArray& byteArray)
  {
  byteArray.clear ();
  
  count = min (count, Bits);
  unsigned bytes = count / 8;
  for (unsigned i = 0; i < bytes; ++i)
    {
    unsigned char byte = 0;
    for (unsigned j = 0; j < 8; ++j)
      {
      if (bitset.test ((i * 8) + j))
        byte |= 1 << (8 - j);
      }
      
    byteArray.push_back (byte);
    }
  }
  
template <unsigned Bits> void ByteArrayToBitset (const ByteArray& byteArray, bitset<Bits>& bitset)
  {
  ByteArrayToBitset (&byteArray[0], byteArray.size (), bitset);
  }
  
template <unsigned Bits> void ByteArrayToBitset (const unsigned char *pByteArray, unsigned count, bitset<Bits>& bitset)
  {
  if ((count * 8) > bitset.size ())
    throw out_of_range ("ByteArray too big");
    
  bitset.reset ();
  for (unsigned i = 0; i < (count * 8); ++i)
    {
    int byte = i / 8;
    unsigned char bit = 1 << (8 - (i % 8));
    if (bit & pByteArray[byte])
      bitset.set (i);
    }
  }
  
inline string ToString (const Value& value)
  {
  return value.ToString ();
  }
  
string ToString (const ValType valType);
  
}
}

#endif
