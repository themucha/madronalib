//
//  MLText.h
//  madronalib
//
//  Created by Randy Jones on 5/21/16.
//

// assignable but otherwise immutable UTF-8 text object class 

#pragma once

#include "../../external/utf/utf.hpp"
#include "MLMemoryUtils.h"
#include <iostream>
#include <vector>

namespace ml
{
	// ----------------------------------------------------------------
	// TextFragment - a minimal, immutable string class. Guaranteed not to allocate heap
	// if the length in bytes is below kShortFragmentSize. 
	
	static constexpr int kShortFragmentSizeInCodePoints = 16;
	static constexpr int kShortFragmentSizeInChars = kShortFragmentSizeInCodePoints*4;
	
	class TextFragment
	{
	public:
		
		TextFragment() noexcept;

		/*
		 this could be a good idea but the (const char*) ctor is taking precedence, revisit
		template<size_t N>
		TextFragment(const char(&p)[N]) noexcept : mSize(N)
		{
			std::cout << "?";
			create();
			if(mpText)
			{
				std::copy(p, p + mSize, mpText);
				nullTerminate();
			}
		}
		 */
		
		// 
		TextFragment(const char* pChars) noexcept;

		// this ctor can be used to save the work of counting the length of the input if we know it already, as with static HashedCharArrays.
		TextFragment(const char* pChars, size_t len) noexcept;
		
		// single code point ctor
		TextFragment(utf::codepoint_type c) noexcept;

		// copy ctor
		TextFragment(const TextFragment& a) noexcept;
		
		// copy assignment operator: TextFragment is assignable but otherwise immutable.
		TextFragment& operator=(const TextFragment& b) noexcept;
		
		// move ctor 
		TextFragment(TextFragment&& b) noexcept;
		
		// move assignment operator
		TextFragment& operator=(TextFragment&& b) noexcept;
		
		// use these ctors instead of operator+.
		TextFragment(const TextFragment& a, const TextFragment& b) noexcept;
		TextFragment(const TextFragment& a, const TextFragment& b, const TextFragment& c) noexcept;
		TextFragment(const TextFragment& a, const TextFragment& b, const TextFragment& c, const TextFragment& d) noexcept;
		
		~TextFragment() noexcept;
		
		explicit operator bool() const { return mSize > 0; }
		
		inline int lengthInBytes() const
		{
			return mSize;
		}
		
		inline int lengthInCodePoints() const
		{
			utf::stringview<const char*> sv(mpText, mpText + mSize);
			return static_cast<int>(sv.codepoints());
		}
		
		inline const char* getText() const { return mpText; }
		
		inline bool beginsWith(const TextFragment& fb) const
		{
			int lenA = lengthInBytes();
			int lenB = fb.lengthInBytes();			
			if(lenB > lenA) return false;
			for(int i=0; i<lenB; ++i)
			{
				if(mpText[i] != fb.mpText[i])
				{
					return false;
				}
			}			
			return true;
		}
		
		inline bool endsWith(const TextFragment& fb) const
		{
			int lenA = lengthInBytes();
			int lenB = fb.lengthInBytes();			
			if(lenB > lenA) return false;
			for(int i=0; i<lenB; ++i)
			{
				if(mpText[lenA - lenB + i] != fb.mpText[i])
				{
					return false;
				}
			}			
			return true;
		}
		
		utf::codepoint_iterator<const char*> begin() const;
		utf::codepoint_iterator<const char*> end() const;
		// deprecated! MLTEST
		inline std::string toString() const { return std::string(mpText); }
		
	private:

		void construct (const char* s1, size_t len1,
			const char* s2 = nullptr, size_t len2 = 0,
			const char* s3 = nullptr, size_t len3 = 0,
			const char* s4 = nullptr, size_t len4 = 0
						) noexcept;
		
		void create(size_t size) noexcept;
		void nullTerminate() noexcept;
		void dispose() noexcept;
		void moveDataFromOther(TextFragment& b);
		
		// TODO these things could share space, as in SmallStackBuffer 
		char* mpText; 
		char mLocalText[kShortFragmentSizeInChars];
		
		// size of data in bytes, without null terminator
		int mSize;
	};

	inline bool compareSizedCharArrays(const char* pA, int lenA, const char* pB, int lenB)
	{
		if(lenA != lenB) return false;
		if((lenA == 0) && (lenB == 0)) return true;
		
		for(int n=0; n<lenA; ++n)
		{
			if(pA[n] != pB[n])
			{
				return false;
			}
		}
		
		return true;		
	}
	
	// TODO made operator== a free function-	do likewise for other classes
	
	inline bool operator==(const TextFragment a, const TextFragment b)
	{
		return compareSizedCharArrays(a.getText(), a.lengthInBytes(), b.getText(), b.lengthInBytes()); 
	}
	
	inline bool operator!=(TextFragment a, TextFragment b)
	{
		return !(a == b);
	}
	
	inline std::ostream& operator<< (std::ostream& out, const TextFragment & r)
	{
		out << r.getText();
		return out;
	}
	
	// ----------------------------------------------------------------
	// Text - a placeholder for more features later like localization
	
	typedef TextFragment Text;

} // namespace ml
