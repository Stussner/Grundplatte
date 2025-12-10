/*
   Projekt: OoS Software gn9-EnGiNe

   Modul: 3DS-Loader

   (C)oded 2004 by Out of Sync
*/

// NOTE: Bei 3DS-Dateien geht die Z-Achse nach oben! (wir konvertieren hier...)

#ifndef __3DSLOADER_H_INCLUDED
#define __3DSLOADER_H_INCLUDED



#include  <stdio.h>
#include  <string.h>
#include  <math.h>

#include <_struktur.hpp>
#include <_vektor.hpp>
#include <_datei.hpp>



#define CHUNKSIZE_3DS                 6

#define MAXTEXTURES_3DS               8
#define MAXMATERIALS_3DS           1000


#define MAIN_3DS                 0x4D4D
#define MAIN_VERSION_3DS         0x0002
#define MAIN_EDIT_3DS            0x3D3D

#define EDIT_MESHVERSION_3DS     0x3D3E
#define EDIT_CONFIG1_3DS         0x0100
#define EDIT_OBJECT_3DS          0x4000
#define EDIT_MATERIAL_3DS        0xAFFF

#define OBJECT_TRIMESH_3DS       0x4100

#define TRIMESH_VERTICES_3DS     0x4110
#define TRIMESH_FACES_3DS        0x4120
#define TRIMESH_TEXCOORDS_3DS    0x4140
#define TRIMESH_LOCALCOORDS_3DS  0x4160

#define FACE_MATERIAL_3DS        0x4130
#define FACE_SMOOTH_3DS          0x4150

#define MATERIAL_NAME_3DS        0xA000
#define MATERIAL_AMBIENT_3DS     0xA010
#define MATERIAL_DIFFUSE_3DS     0xA020
#define MATERIAL_SPECULAR_3DS    0xA030
#define MATERIAL_TEXMAP1_3DS     0xA200
#define MATERIAL_TEXMAP2_3DS     0xA33A

#define COLOR_FLOAT_3DS          0x0010
#define COLOR_BYTE_3DS           0x0011

#define TEXMAP_NAME_3DS          0xA300
#define TEXMAP_USCALE_3DS        0xA356
#define TEXMAP_VSCALE_3DS        0xA354
#define TEXMAP_UOFFSET_3DS       0xA358
#define TEXMAP_VOFFSET_3DS       0xA35A


#define VEC_X  0
#define VEC_Y  1
#define VEC_Z  2



class _welt3DSLoader;
class _welt3DSObject;
class _welt3DSMaterial;


            
typedef struct{
				unsigned short id;
				unsigned int len;
} CHUNK_3DS;


typedef struct{
				float x, y, z;
} VERTEX_3DS;


typedef struct{
				float u, v;
} TEXCOORD_3DS;


typedef struct{
				unsigned short v1, v2, v3, flags;
				char*materialName;
				_welt3DSMaterial*material;
} FACE_3DS;


typedef struct{
				bool used;  // Gibt an ob die Textur verwendet wird
			    char*name;
				float uScale, vScale;
				float uOffset, vOffset;
} TEXTURE_3DS;


//*****************************************************************************************************************************************************************************************************************
//																W E L T 3 D S M A T E R I A L
//*****************************************************************************************************************************************************************************************************************
class _welt3DSMaterial{
				friend class _welt3DSLoader;
				friend class _welt3DSObject;
		public:
				_welt3DSMaterial();
				_welt3DSMaterial(_welt3DSLoader*l);
				virtual ~_welt3DSMaterial();
				char**GetName();
				TEXTURE_3DS *GetTexture(unsigned short num);
				void SetLoader(_welt3DSLoader*l);
				void ReadTextureMap(unsigned short num, unsigned int length);
				void ReadAmbientColor(unsigned int length);
				void ReadDiffuseColor(unsigned int length);
				void ReadSpecularColor(unsigned int length);
				//void BindTexture(unsigned short num);
		private:
				_welt3DSLoader*loader;
				char*materialName;
				float ambient[3];
				float diffuse[3];
				float specular[3];
				TEXTURE_3DS texture[MAXTEXTURES_3DS];
};
//*****************************************************************************************************************************************************************************************************************
//																W E L T 3 D S O B J E C T 
//*****************************************************************************************************************************************************************************************************************
class _welt3DSObject{
				friend class _welt3DSLoader;
				friend class _welt3DSMaterial;
		public:
				_welt3DSObject(_welt3DSLoader*l);
				virtual ~_welt3DSObject();
   
				char **GetName();
				unsigned short GetVertexCount();
				unsigned short GetFaceCount();
				VERTEX_3DS*GetVertices();
				TEXCOORD_3DS*GetTexCoords();
				FACE_3DS*GetFaces();
				_vektor3<_tg>*GetPos();
     
				void ReadVertices();
				void ReadFaces(unsigned int length);
				void ReadTexCoords(unsigned int length);
				void ReadLocalCoordinates();

				void CalcNormals(bool inverse);
				void AssignMaterials();
				//void Render();
		private:
				_welt3DSLoader*loader;
				char*objectName;
				unsigned short     numVertices;
				VERTEX_3DS         *vertex;
				TEXCOORD_3DS       *texCoord;
				unsigned short     numFaces;
				FACE_3DS           *face;
				VERTEX_3DS         *faceNormal;
				_vektor3<_tg>      localX, localY, localZ, localPos;
};
//*****************************************************************************************************************************************************************************************************************
//																W E L T 3 D S L O A D E R
//*****************************************************************************************************************************************************************************************************************
class _welt3DSLoader{
				friend class _welt3DSObject;
				friend class _welt3DSMaterial; 
	    public:
				_welt3DSLoader();
				virtual ~_welt3DSLoader();
   
				int Load(const char *name,_liste<_welt3DSObject>*list);
		private:
				unsigned char  ReadByte();
				unsigned short ReadWord();
				unsigned int   ReadDword();
				void ReadFloat(float*f);
				unsigned short ReadChunk(CHUNK_3DS *chunk);
				unsigned int ReadName(char **name);
				void ProcessMainChunk(unsigned int length);
				void ProcessEditorChunk(unsigned int length);
				void ProcessObjectChunk(unsigned int length);
				void ProcessTriangularMesh(_welt3DSObject*object, unsigned int length);
				void ProcessMaterialChunk(unsigned int length);
		private:		
			    char*buffer;
				int bufferPos;
			    unsigned int version_3DS, version_mesh;
			    unsigned short numMaterials;
				_welt3DSMaterial material[MAXMATERIALS_3DS];  // FIXME
			    _liste<_welt3DSObject>*objectList;
};









#endif