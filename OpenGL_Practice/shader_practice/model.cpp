#include "model.h"

Model::Model(){}

Model::Model(
	std::string const & Path
)
{
// Come back to threading later

	//std::thread Loader(&Model::LoadModel, this, Path);

	//Loader.join();

	LoadModel(Path);
}


void Model::Draw(
	std::shared_ptr<Shader> Shader_
)
{


	for (unsigned int i = 0; i < Meshes.size(); i++)
	{
		Meshes[i].Draw(Shader_);
	}
};

void Model::LoadModel(std::string const & Path)
{
	Assimp::Importer Importer_;

	const aiScene* Scene = Importer_.ReadFile(Path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << Importer_.GetErrorString() << "\n";
		return;
	}

	Directory = Path.substr(0, Path.find_last_of('/'));

	ProcessNode(Scene->mRootNode, Scene);

	std::cout << "Model Loaded!\n";

};

void Model::ProcessNode(aiNode* Node, const aiScene* Scene)
{
	for (unsigned int i = 0; i < Node->mNumMeshes; i++)
	{
		aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
		Meshes.push_back(ProcessMesh(Mesh, Scene));
	}

	for (unsigned int i = 0; i < Node->mNumChildren; i++)
	{
		ProcessNode(Node->mChildren[i], Scene);
	}

}

Mesh Model::ProcessMesh(aiMesh * Mesh_, const aiScene * Scene)
{
	std::vector<Vertex>			Vertices;
	std::vector<unsigned int>	Indices;
	std::vector<Texture>		Textures;

	for (unsigned int i = 0; i < Mesh_->mNumVertices; i++)
	{

		glm::vec3 Vector;
		Vertex Vertex_;

		SetVertexBoneDataToDefault(Vertex_);

		Vertex_.Position = AssimpGLMHelpers::GetGLMVec(Mesh_->mVertices[i]);
		Vertex_.Normal = AssimpGLMHelpers::GetGLMVec(Mesh_->mNormals[i]);

		if (Mesh_->HasNormals())
		{
			Vector.x = Mesh_->mNormals[i].x;
			Vector.y = Mesh_->mNormals[i].y;
			Vector.z = Mesh_->mNormals[i].z;
			Vertex_.Normal = Vector;
		}

		if (Mesh_->mTextureCoords[0])
		{
			glm::vec2 Vec;

			Vec.x = Mesh_->mTextureCoords[0][i].x;
			Vec.y = Mesh_->mTextureCoords[0][i].y;

			Vertex_.TexCoords = Vec;

		}
		else
		{
			Vertex_.TexCoords = glm::vec2(0, 0);
		}

		Vertices.push_back(Vertex_);
	}

	for (unsigned int i = 0; i < Mesh_->mNumFaces; i++)
	{
		aiFace Face = Mesh_->mFaces[i];
		for (unsigned int j = 0; j < Face.mNumIndices; j++)
		{
			Indices.push_back(Face.mIndices[j]);
		}
	}

	if (Mesh_->mMaterialIndex >= 0)
	{
		
		aiMaterial* Material = Scene->mMaterials[Mesh_->mMaterialIndex];
		
		std::vector<Texture> DiffuseMaps = LoadMaterialTextures(Material, aiTextureType_DIFFUSE, Scene, "texture_diffuse");
		
		Textures.insert(Textures.end(), DiffuseMaps.begin(), DiffuseMaps.end());
		
		std::vector<Texture> SpecularMaps = LoadMaterialTextures(Material, aiTextureType_SPECULAR, Scene, "texture_specular");
		
		Textures.insert(Textures.end(), SpecularMaps.begin(), SpecularMaps.end());
	
	}

	ExtractBoneWeightForVertices(Vertices, Mesh_, Scene);

	return Mesh(Vertices, Indices, Textures);

}


std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* Mat, aiTextureType Type,const aiScene * Scene,std::string TypeName)
{
	
	std::vector<Texture> Textures;

	for (unsigned int i = 0; i < Mat->GetTextureCount(Type); i++)
	{
		aiString Str;

		Mat->GetTexture(Type, i, &Str);

		bool Skip = false;

		for (unsigned int j = 0; j < TexturesLoaded.size(); j++)
		{
			if (std::strcmp(TexturesLoaded[j].Path.data(), Str.C_Str()) == 0)
			{
				Textures.push_back(TexturesLoaded[j]);
				Skip = true;
				break;
			}
		}

		if (!Skip)
		{
			Texture Texture_;

			if (Str.C_Str()[0] == '*')
			{

				int TextureIndex = std::atoi(&Str.C_Str()[1]);

				aiTexture* AITex = Scene->mTextures[TextureIndex];

				if (AITex->mHeight == 0)
				{

					int Width, Height, NRComponents;
					unsigned char* Data =
						stbi_load_from_memory(
							reinterpret_cast<unsigned char*>(AITex->pcData),
							AITex->mWidth,
							&Width,
							&Height,
							&NRComponents,
							0
						);

					if (Data)
					{

						GLenum Format;

						if (NRComponents == 1)
						{
							Format = GL_RED;
						}
						else if (NRComponents == 3)
						{
							Format = GL_RGB;
						}
						else if (NRComponents == 4)
						{
							Format = GL_RGBA;
						}

						glGenTextures(1, &Texture_.ID);

						glBindTexture(GL_TEXTURE_2D, Texture_.ID);

						glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format, GL_UNSIGNED_BYTE, Data);

						glGenerateMipmap(GL_TEXTURE_2D);

						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

						stbi_image_free(Data);
					}
					else
					{
						std::cerr << "failed to load compressed texture: " << Str.C_Str() << "\n";
						continue;
					}

				}
				else
				{

					GLenum Format = GL_RGBA;

					glGenTextures(1, &Texture_.ID);

					glBindTexture(GL_TEXTURE_2D, Texture_.ID);

					glTexImage2D(GL_TEXTURE_2D, 0, Format, AITex->mWidth, AITex->mHeight, 0, Format, GL_UNSIGNED_BYTE, AITex->pcData);

					glGenerateMipmap(GL_TEXTURE_2D);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				}
				Texture_.Path = Str.C_Str();

			}
			else
			{

				Texture_.ID = TextureFromFile(Str.C_Str(), Directory, true);

			}
			if (Texture_.ID != 0)
			{

				Texture_.Type = TypeName;
				Texture_.Path = Str.C_Str();
				Textures.push_back(Texture_);
				TexturesLoaded.push_back(Texture_);

			}
			else
			{
				std::cout << "Failed to load texture: " << Str.C_Str() << "\n";
			}
		}


	}
		return Textures;

};

void Model::SetVertexBoneDataToDefault(Vertex& Vertex_)
{

	//for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
	//{
	//	Vertex_.M_BoneIDs[i] = -1;
	//	Vertex_.M_Weights[i] = 0.f;
	//}

};

void Model::SetVertexBoneData(Vertex& Vertex_, int BoneID, float Weight)
{
	//for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
	//{
	//	if (Vertex_.M_BoneIDs[i] < 0)
	//	{
	//		Vertex_.M_Weights[i] = Weight;
	//		Vertex_.M_BoneIDs[i] = BoneID;
	//		break;
	//	}
	//}
};

void Model::ExtractBoneWeightForVertices(std::vector<Vertex>& Vertices, aiMesh* Mesh, const aiScene* Scene)
{

	auto& BoneInfoMap = M_BoneInfoMap;
	int& BoneCount = M_BoneCounter;


	for (int BoneIndex = 0; BoneIndex < Mesh->mNumBones; ++BoneIndex)
	{
		int BoneID = -1;
		std::string BoneName = Mesh->mBones[BoneIndex]->mName.C_Str();
		if (BoneInfoMap.find(BoneName) == BoneInfoMap.end())
		{
			BoneInfo NewBoneInfo;
			NewBoneInfo.ID = BoneCount;
			NewBoneInfo.Offset = AssimpGLMHelpers::ConvertMatrixToGLMFormat(Mesh->mBones[BoneIndex]->mOffsetMatrix);
			M_BoneInfoMap[BoneName] = NewBoneInfo;
			BoneID = BoneCount;
			BoneCount++;
		}
		else
		{
			BoneID = BoneInfoMap[BoneName].ID;
		}

		assert(BoneID != -1);

		auto Weights = Mesh->mBones[BoneIndex]->mWeights;
		int NumWeights = Mesh->mBones[BoneIndex]->mNumWeights;

		for (int WeightIndex = 0; WeightIndex < NumWeights; ++WeightIndex)
		{
			
			int VertexID = Weights[WeightIndex].mVertexId;
			float Weight = Weights[WeightIndex].mWeight;
			assert(VertexID <= Vertices.size());
			SetVertexBoneData(Vertices[VertexID], BoneID, Weight);

		}

	}

}

unsigned int TextureFromFile(const char* Path, const std::string& Directory, bool Gamma)
{

	std::string Filename = std::string(Path);

	Filename = Directory + '/' + Filename;

	unsigned int TextureID;

	glGenTextures(1, &TextureID);

	stbi_set_flip_vertically_on_load(false);

	int Width, Height, NRComponents;

	unsigned char* Data = stbi_load(Filename.c_str(), &Width, &Height, &NRComponents, 0);

	if (Data)
	{
		
		GLenum Format;

		if (NRComponents == 1)
		{
			Format = GL_RED;
		}
		else if (NRComponents == 3)
		{
			Format = GL_RGB;
		}
		else if (NRComponents == 4)
		{
			Format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, TextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format, GL_UNSIGNED_BYTE, Data);

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(Data);

	}
	else
	{
		std::cout << "Texture failed to load at path: " << *Path << "\n";
		//stbi_image_free(Data);
	}

	return TextureID;

}

