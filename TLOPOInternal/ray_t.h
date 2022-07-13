#pragma once

#define ALIGN16
#define ALIGN16_POST


class ALIGN16 VectorAligned : public Vector
{
public:
	inline VectorAligned(void) {};
	inline VectorAligned(vec_t X, vec_t Y, vec_t Z) 
	{
		Init(X,Y,Z);
	}

#ifdef VECTOR_NO_SLOW_OPERATIONS

private:
	// No copy constructors allowed if we're in optimal mode
	VectorAligned(const VectorAligned& vOther);
	VectorAligned(const Vector &vOther);

#else
public:
	explicit VectorAligned(const Vector &vOther) 
	{
		Init(vOther.x, vOther.y, vOther.z);
	}
	
	VectorAligned& operator=(const Vector &vOther)	
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	VectorAligned& operator=(const VectorAligned &vOther)
	{
		// we know we're aligned, so use simd
		// we can't use the convenient abstract interface coz it gets declared later
#ifdef _X360
		XMStoreVector4A(Base(), XMLoadVector4A(vOther.Base()));
#elif _WIN32
		_mm_store_ps(Base(), _mm_load_ps( vOther.Base() ));
#else
		Init(vOther.x, vOther.y, vOther.z);
#endif
		return *this;
	}

	
#endif
	float w;	// this space is used anyway

#if !defined(NO_MALLOC_OVERRIDE)
	void* operator new[] ( size_t nSize)
	{
		return MemAlloc_AllocAligned(nSize, 16);
	}

	void* operator new[] ( size_t nSize, const char *pFileName, int nLine)
	{
		return MemAlloc_AllocAlignedFileLine(nSize, 16, pFileName, nLine);
	}

	void* operator new[] ( size_t nSize, int /*nBlockUse*/, const char *pFileName, int nLine)
	{
		return MemAlloc_AllocAlignedFileLine(nSize, 16, pFileName, nLine);
	}

	void operator delete[] ( void* p) 
	{
		MemAlloc_FreeAligned(p);
	}

	void operator delete[] ( void* p, const char *pFileName, int nLine)  
	{
		MemAlloc_FreeAligned(p, pFileName, nLine);
	}

	void operator delete[] ( void* p, int /*nBlockUse*/, const char *pFileName, int nLine)  
	{
		MemAlloc_FreeAligned(p, pFileName, nLine);
	}

	// please don't allocate a single quaternion...
	void* operator new   ( size_t nSize )
	{
		return MemAlloc_AllocAligned(nSize, 16);
	}
	void* operator new   ( size_t nSize, const char *pFileName, int nLine )
	{
		return MemAlloc_AllocAlignedFileLine(nSize, 16, pFileName, nLine);
	}
	void* operator new   ( size_t nSize, int /*nBlockUse*/, const char *pFileName, int nLine )
	{
		return MemAlloc_AllocAlignedFileLine(nSize, 16, pFileName, nLine);
	}
	void operator delete ( void* p) 
	{
		MemAlloc_FreeAligned(p);
	}

	void operator delete ( void* p, const char *pFileName, int nLine)  
	{
		MemAlloc_FreeAligned(p, pFileName, nLine);
	}

	void operator delete ( void* p, int /*nBlockUse*/, const char *pFileName, int nLine)  
	{
		MemAlloc_FreeAligned(p, pFileName, nLine);
	}
#endif
} ALIGN16_POST;

struct Ray_t
{
	VectorAligned m_Start;	// starting point, centered within the extents
	VectorAligned m_Delta;	// direction + length of the ray
	VectorAligned m_StartOffset;	// Add this to m_Start to get the actual ray start
	VectorAligned m_Extents;	// Describes an axis aligned box extruded along a ray
	const matrix3x4_t* m_pWorldAxisTransform;
	bool m_IsRay;	// are the extents zero?
	bool m_IsSwept;	// is delta != 0?

	Ray_t() : m_pWorldAxisTransform(NULL) {}

	void Init(Vector const& start, Vector const& end)
	{
		Assert(&end);
		VectorSubtract(end, start, m_Delta);

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		VectorClear(m_Extents);
		m_pWorldAxisTransform = NULL;
		m_IsRay = true;

		// Offset m_Start to be in the center of the box...
		VectorClear(m_StartOffset);
		VectorCopy(start, m_Start);
	}

	void Init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs)
	{
		Assert(&end);
		VectorSubtract(end, start, m_Delta);

		m_pWorldAxisTransform = NULL;
		m_IsSwept = (m_Delta.LengthSqr() != 0);

		VectorSubtract(maxs, mins, m_Extents);
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6);

		Assert(m_Extents.x >= 0 && m_Extents.y >= 0 && m_Extents.z >= 0);
		// Offset m_Start to be in the center of the box...
		VectorAdd(mins, maxs, m_StartOffset);
		m_StartOffset *= 0.5f;
		VectorAdd(start, m_StartOffset, m_Start);
		m_StartOffset *= -1.0f;
	}

	// compute inverse delta
	Vector InvDelta() const
	{
		Vector vecInvDelta;
		for (int iAxis = 0; iAxis < 3; ++iAxis)
		{
			if (m_Delta[iAxis] != 0.0f)
			{
				vecInvDelta[iAxis] = 1.0f / m_Delta[iAxis];
			}
			else
			{
				vecInvDelta[iAxis] = FLT_MAX;
			}
		}
		return vecInvDelta;
	}
};
