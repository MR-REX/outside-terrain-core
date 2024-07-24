class OTC_Mesh
{
	static const int MAX_RESOLUTION = 32;
	static const int MAX_VERTICLES = MAX_RESOLUTION * MAX_RESOLUTION;
	static const int MAX_UVS = MAX_VERTICLES * 2;
	static const int MAX_INDICES = (MAX_VERTICLES * 6) - ((MAX_RESOLUTION - 1) * 6 * 2);
	
	protected vector verticles[MAX_VERTICLES];
	protected int verticlesCount;
	
	protected float uvs[MAX_UVS];
	protected int uvsCount;
	
	protected int indices[MAX_INDICES];
	protected int indicesCount;
	
	void OTC_Mesh(array<float> heights, int resolution, float width, float height)
	{
		if (resolution < 2 || resolution > MAX_RESOLUTION)
		{
			Print("Mesh resolution should be more than 2, but less than " + MAX_RESOLUTION, LogLevel.ERROR);
			return;
		}
		
		if (resolution % 2 != 0)
		{
			Print("Mesh resolution must be multiple of 2", LogLevel.ERROR);
			return;
		}
		
		if (heights.Count() < resolution * resolution)
		{
			Print("Length of heights array is less than mesh resolution", LogLevel.ERROR);
			return;
		}
		
		const int zeroBasedResolution = resolution - 1;
		
		// Create arrays for Verticles and UVs
		
		int verticleIndex, uvIndex;
		float _x, _y, _z;

		for (int y = 0; y < resolution; y++)
		{
			for (int x = 0; x < resolution; x++)
			{
				_x = (x / zeroBasedResolution - 0.5) * height;
				_y = heights[verticleIndex];
				_z = (y / zeroBasedResolution - 0.5) * width;
				
				verticles[verticleIndex++] = Vector(_x, _y, _z);
				
				uvs[uvIndex++] = x / zeroBasedResolution;
				uvs[uvIndex++] = 1 - y / zeroBasedResolution;
			}
		}
		
		verticlesCount = verticleIndex;
		uvsCount = uvIndex;
		
		// Create array of Indices
		
		int indiceIndex;
		int bottomLeft, bottomRight, topLeft, topRight;
		
		for (int s = 0; s < verticleIndex - resolution; s++)
		{
			if (s % resolution == zeroBasedResolution)
			{
				continue;
			}
			
			bottomLeft = s;
			bottomRight = s + 1;
			topLeft = bottomLeft + resolution;
			topRight = bottomRight + resolution;
			
			indices[indiceIndex++] = bottomLeft;
			indices[indiceIndex++] = topLeft;
			indices[indiceIndex++] = topRight;
			
			indices[indiceIndex++] = topRight;
			indices[indiceIndex++] = bottomRight;
			indices[indiceIndex++] = bottomLeft;
		}
		
		indicesCount = indiceIndex;
	}
	
	bool IsValid()
	{
		return (verticlesCount > 0) && (uvsCount > 0) && (indicesCount > 0);
	}
	
	void GetVerticles(out vector _verticles[MAX_VERTICLES], out int _verticlesCount)
	{
		_verticles = verticles;
		_verticlesCount = verticlesCount;
	}
	
	void GetUVs(out float _uvs[MAX_UVS], out int _uvsCount)
	{
		_uvs = uvs;
		_uvsCount = uvsCount;
	}
	
	void GetIndices(out int _indices[MAX_INDICES], out int _indicesCount)
	{
		_indices = indices;
		_indicesCount = indicesCount;
	}
}