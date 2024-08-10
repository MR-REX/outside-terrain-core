class OTC_Mesh
{
	static const int MAX_RESOLUTION = 32;
	static const int MAX_VERTICES = MAX_RESOLUTION * MAX_RESOLUTION;
	static const int MAX_UVS = MAX_VERTICES * 2;
	static const int MAX_INDICES = (MAX_VERTICES * 6) - ((MAX_RESOLUTION - 1) * 6 * 2);
	
	protected vector m_aVertices[MAX_VERTICES];
	protected int m_iVerticesCount;
	
	protected float m_aUV[MAX_UVS];
	protected int m_iUVCount;
	
	protected int m_aIndices[MAX_INDICES];
	protected int m_iIndicesCount;
	
	void OTC_Mesh(array<float> heights, int resolution, float width, float height)
	{
		if (resolution < 2 || resolution > MAX_RESOLUTION)
			return;
		
		if (resolution % 2 != 0)
			return;
		
		if (heights.Count() < resolution * resolution)
			return;
		
		const int zeroBasedResolution = resolution - 1;
		
		// Create arrays for Vertices and UVs
		
		int verticeIndex, uvIndex;
		float _x, _y, _z;

		for (int y = 0; y < resolution; y++)
		{
			for (int x = 0; x < resolution; x++)
			{
				_x = (x / zeroBasedResolution - 0.5) * width;
				_y = heights[verticeIndex];
				_z = (y / zeroBasedResolution - 0.5) * height;
				
				m_aVertices[verticeIndex++] = Vector(_x, _y, _z);
				
				m_aUV[uvIndex++] = x / zeroBasedResolution;
				m_aUV[uvIndex++] = 1 - y / zeroBasedResolution;
			}
		}
		
		m_iVerticesCount = verticeIndex;
		m_iUVCount = uvIndex;
		
		// Create array of Indices
		
		int indiceIndex;
		int bottomLeft, bottomRight, topLeft, topRight;
		
		for (int s = 0; s < verticeIndex - resolution; s++)
		{
			if (s % resolution == zeroBasedResolution)
				continue;
			
			bottomLeft = s;
			bottomRight = s + 1;
			topLeft = bottomLeft + resolution;
			topRight = bottomRight + resolution;
			
			m_aIndices[indiceIndex++] = bottomLeft;
			m_aIndices[indiceIndex++] = topLeft;
			m_aIndices[indiceIndex++] = topRight;
			
			m_aIndices[indiceIndex++] = topRight;
			m_aIndices[indiceIndex++] = bottomRight;
			m_aIndices[indiceIndex++] = bottomLeft;
		}
		
		m_iIndicesCount = indiceIndex;
	}
	
	bool IsValid()
	{
		return (m_iVerticesCount > 0) && (m_iUVCount > 0) && (m_iIndicesCount > 0);
	}
	
	void GetVertices(out vector vertices[MAX_VERTICES], out int verticesCount)
	{
		vertices = m_aVertices;
		verticesCount = m_iVerticesCount;
	}
	
	void GetUVs(out float uvs[MAX_UVS], out int uvsCount)
	{
		uvs = m_aUV;
		uvsCount = m_iUVCount;
	}
	
	void GetIndices(out int indices[MAX_INDICES], out int indicesCount)
	{
		indices = m_aIndices;
		indicesCount = m_iIndicesCount;
	}
}