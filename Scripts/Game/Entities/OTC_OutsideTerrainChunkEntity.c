[EntityEditorProps(category: "Outside Terrain Core/Chunk", description: "A simple outside terrain chunk", color: "50 205 50 255", style: "box", dynamicBox: true)]
class OTC_OutsideTerrainChunkEntityClass : GenericEntityClass
{
}

class OTC_OutsideTerrainChunkEntity : GenericEntity
{
	[Attribute(category: "Size", defvalue: "128", params: string.Format("0 %1 1", float.MAX), desc: "Mesh width")]
	protected float m_fWidth;
	
	[Attribute(category: "Size", defvalue: "128", params: string.Format("0 %1 1", float.MAX), desc: "Mesh height")]
	protected float m_fHeight;
	
	[Attribute(category: "Mesh", defvalue: "4", params: string.Format("2 %1 2", OTC_Mesh.MAX_RESOLUTION), uiwidget: UIWidgets.Slider, desc: "Size of heights matrix")]
	protected int m_iResolution;
	
	[Attribute(category: "Mesh", desc: "Array of heights")]
	protected ref array<float> m_aHeights;
	
	[Attribute(category: "Physics", defvalue: "0", uiwidget: UIWidgets.CheckBox, desc: "Generates a physics body for mesh")]
	protected bool m_bEnableCollision;
	
	[Attribute(category: "Physics", defvalue: EPhysicsLayerPresets.Terrain.ToString(), enums: ParamEnumArray.FromEnum(EPhysicsLayerPresets), uiwidget: UIWidgets.ComboBox, desc: "Physics layer mask preset for physics body of mesh")]
	protected EPhysicsLayerPresets m_ePhysicsLayerPreset; 
	
	[Attribute(category: "Texture", defvalue: "{FCDCBAF69074F24C}Common/Textures/OutsideTerrainCore/DefaultMaterial.emat", params: "emat", uiwidget: UIWidgets.ResourcePickerThumbnail, desc: "Material of mesh")]
	protected ResourceName m_Material;
	
	// Enforce Script: Why I can't use constaint values from another class when trying to create static array?
	// It's a bad solution, but I don't know how to do this better yet
	private const int MAX_MESH_VERTICES = OTC_Mesh.MAX_VERTICES;
	private const int MAX_MESH_UVS = OTC_Mesh.MAX_UVS;
	private const int MAX_MESH_INDICES = OTC_Mesh.MAX_INDICES;
	
	void SetMesh(notnull OTC_Mesh mesh, ResourceName material)
	{
		vector vertices[MAX_MESH_VERTICES];
		int verticesCount;
		
		mesh.GetVertices(vertices, verticesCount);
		
		float uvs[MAX_MESH_UVS];
		int uvsCount;
		
		mesh.GetUVs(uvs, uvsCount);
		
		int indices[MAX_MESH_INDICES];
		int indicesCount;
		
		mesh.GetIndices(indices, indicesCount);
		
		int numVerts[] = { verticesCount };
		int numIndices[] = { indicesCount };
		string materials[] = { material };
		
		Resource resource = MeshObject.Create(1, numVerts, numIndices, materials, 0);
		BaseResourceObject baseResourceObject = resource.GetResource();
		
		MeshObject meshObject = baseResourceObject.ToMeshObject();
		
		meshObject.UpdateVerts(0, vertices, uvs);
		meshObject.UpdateIndices(0, indices);
		
		SetObject(meshObject, "");
	}
	
	void SetMeshPhysics(notnull OTC_Mesh mesh, ResourceName material)
	{
		vector vertices[MAX_MESH_VERTICES];
		int verticesCount;
		
		mesh.GetVertices(vertices, verticesCount);
		
		int indices[MAX_MESH_INDICES];
		int indicesCount;
		
		mesh.GetIndices(indices, indicesCount);
		
		PhysicsGeom geometry = PhysicsGeom.CreateTriMesh(vertices, indices, verticesCount, indicesCount);
		PhysicsGeomDef geometryDefinition = new PhysicsGeomDef("Terrain", geometry, material, 0xffffffff);

		PhysicsGeomDef geometryDefinitions[] = { geometryDefinition };
		Physics.CreateStaticEx(this, geometryDefinitions);
	}
	
	bool SetPhysicsLayerMask(EPhysicsLayerPresets physicsLayerPreset)
	{
		Physics physics = GetPhysics();
		
		if (!physics)
			return false;
		
		physics.SetInteractionLayer(physicsLayerPreset);
		
		return true;
	}
	
	void OTC_OutsideTerrainChunkEntity(IEntitySource src, IEntity parent)
	{
		OTC_Mesh mesh = new OTC_Mesh(m_aHeights, m_iResolution, m_fWidth, m_fHeight);
		
		if (!mesh.IsValid() || !m_Material)
			return;
		
		SetMesh(mesh, m_Material);
		
		if (m_bEnableCollision)
		{
			SetMeshPhysics(mesh, m_Material);
			SetPhysicsLayerMask(m_ePhysicsLayerPreset);
		}
	}
}