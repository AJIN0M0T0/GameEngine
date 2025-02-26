//	ファイル名	：Allocator.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/25 23:01:56
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Allocator_HXX_____
#define _____Allocator_HXX_____

#ifdef DEBUG
#define New(Type) new(0,typeid(Type),__FILE__, __LINE__) Type;
void* operator new(size_t size, size_t pad, const type_info& type, const std::string& FileName, int Line);
void* operator new[](size_t size, size_t pad, const type_info& type,const std::string& FileName, int Line);
void operator delete(void* p, size_t size, const type_info& type, const std::string& FileName, int Line);
#else
#define New(Type) new Type
void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* p, size_t size) noexcept;
#endif // DEBUG

#endif // !_____Allocator_HXX_____
