#ifndef LD_TYPES_H_
#define LD_TYPES_H_

#include<ace/Basic_Types.h>

typedef ACE_TCHAR       ld_tchar;
typedef signed char     ld_char;
typedef unsigned char   ld_uchar;
typedef wchar_t         ld_wchar;
typedef ACE_INT16       ld_int16;
typedef ACE_UINT16      ld_uint16;
typedef ACE_INT32       ld_int32;
typedef ACE_UINT32      ld_uint32;
typedef ACE_INT64       ld_int64;
typedef ACE_UINT64      ld_uint64;

const int ld_sizeof_char = sizeof(ld_char);
const int ld_sizeof_wchar = sizeof(ld_wchar);
const int ld_sizeof_tchar = sizeof(ld_tchar);
//ACE_SIZEOF_CHAR
//ACE_SIZEOF_WCHAR
//ACE_SIZEOF_SHORT
//ACE_SIZEOF_INT
//ACE_SIZEOF_LONG
//ACE_SIZEOF_LONG_LONG
//ACE_SIZEOF_VOID_P
//ACE_SIZEOF_FLOAT
//ACE_SIZEOF_DOUBLE
//ACE_SIZEOF_LONG_DOUBLE
//ACE_BYTE_ORDER

#endif
