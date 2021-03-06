#include "terrain.hpp"

static const int TERRAIN_SIZE = 256;
static const int TERRAIN_VERTICES_BY_TILE = 6;
static const int TERRAIN_SAMPLE = 4;
static const float TERRAIN_TILE_SIZE = (float)TERRAIN_SIZE/(float)TERRAIN_SAMPLE;
static const float TERRAIN_HEIGHT_SCALING = 0.25f;

Terrain::Terrain(const std::string& heightMapFilename)
{

  sf::Image heightMap;
  heightMap.loadFromFile(heightMapFilename);
       
  m_vertices.reserve(TERRAIN_SIZE * TERRAIN_SIZE);
  for(int x = 0; x < TERRAIN_SIZE; x++)
    for(int y = 0; y < TERRAIN_SIZE; y++)
      m_vertices.push_back(Vertex(glm::vec3(x, y , 0 ), glm::vec2(1024.0f/x, 1024.0/y), glm::vec3(0, 0, 0)));
  //heightMap.getPixel(x,y).r * TERRAIN_HEIGHT_SCALING
  

  m_indices.reserve(TERRAIN_SIZE * TERRAIN_SIZE * TERRAIN_VERTICES_BY_TILE);
  for(int x = 0; x < TERRAIN_SIZE-1; x++)
    {
      for(int y = 0; y < TERRAIN_SIZE-1; y++)
	{
	  unsigned int offset = x * TERRAIN_SIZE + y;
	  m_indices.push_back(offset + 0);
	  m_indices.push_back(offset + 1);
	  m_indices.push_back(offset + TERRAIN_SIZE);
	  m_indices.push_back(offset + 1);
	  m_indices.push_back(offset + TERRAIN_SIZE +1);
	  m_indices.push_back(offset + TERRAIN_SIZE);
	}
    }
    
  for(int i = 0; i < TERRAIN_SIZE * TERRAIN_SIZE * TERRAIN_VERTICES_BY_TILE; i = i+3)
    {      
      //calculate normals
      glm::vec3 v0 = m_vertices[m_indices[i]].GetPos();
      glm::vec3 v1 = m_vertices[m_indices[i + 1]].GetPos();
      glm::vec3 v2 = m_vertices[m_indices[i + 2]].GetPos();
      glm::vec3 u = v1 - v0;
      glm::vec3 v = v2 - v0;
      glm::vec3 n = glm::cross(u, v);
      m_vertices[m_indices[i]].SetNormal(glm::normalize(n + m_vertices[m_indices[i]].GetNormal()));
      m_vertices[m_indices[i+1]].SetNormal(glm::normalize(n + m_vertices[m_indices[i+1]].GetNormal()));
      m_vertices[m_indices[i+2]].SetNormal(glm::normalize(n + m_vertices[m_indices[i+2]].GetNormal()));
    }
  
  m_mesh = std::unique_ptr<Mesh>(new Mesh(m_vertices, m_vertices.size(), m_indices, m_indices.size()));
  
}

Terrain::~Terrain()
{
  
}

void Terrain::Draw()
{
  m_mesh->Draw();  
}
