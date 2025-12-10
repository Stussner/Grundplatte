



#include <_welt3ds.hpp>



//*****************************************************************************************************************************************************************************************************************
//																W E L T 3 D S O B J E C T 
//*****************************************************************************************************************************************************************************************************************
_welt3DSObject::_welt3DSObject(_welt3DSLoader*l){
																loader = l;
																objectName   = 0;
																numVertices  = 0;
																vertex       = 0;
																texCoord     = 0;
																numFaces     = 0;
																face         = 0;
																faceNormal   = 0;
																/*localX.x   = localX.y   = localX.z   = 0.0f;
																localY.x   = localY.y   = localY.z   = 0.0f;
																localZ.x   = localZ.y   = localZ.z   = 0.0f;
																localPos.x = localPos.y = localPos.z = 0.0f;*/
};
_welt3DSObject::~_welt3DSObject(){
																delete[] objectName;
																delete[] vertex;
																delete[] texCoord;
																for(unsigned short i = 0; i < numFaces; i++)
																delete[] face[i].materialName;
																delete[] face;
																delete[] faceNormal;
};
char **_welt3DSObject::GetName(){ 
																return(&objectName); 
};
unsigned short _welt3DSObject::GetVertexCount(){
																return(numVertices); 
};
unsigned short _welt3DSObject::GetFaceCount(){ 
																return(numFaces); 
};
VERTEX_3DS *_welt3DSObject::GetVertices(){ 
																return(vertex); 
};
TEXCOORD_3DS *_welt3DSObject::GetTexCoords(){ 
																return(texCoord); 
};
FACE_3DS *_welt3DSObject::GetFaces(){ 
																return(face); 
};
_vektor3<_tg> *_welt3DSObject::GetPos(){ 
																return(&localPos); 
};
void _welt3DSObject::ReadVertices(){//  Liest alle Vertices ein
																numVertices = loader->ReadWord();
																vertex      = new VERTEX_3DS[numVertices];
																for(unsigned short i = 0; i < numVertices; i++){
																 loader->ReadFloat(&vertex[i].x);
																 loader->ReadFloat(&vertex[i].z);
																 loader->ReadFloat(&vertex[i].y); 
																 vertex[i].z = -vertex[i].z;  // FIXME?
																 //Engine->LogFile.Print("Vertex = %f, %f, %f\n", vertices[i].x, vertices[i].y, vertices[i].z);
																};
};
void _welt3DSObject::ReadFaces(unsigned int length){//  Liest alle Faces ein
																CHUNK_3DS chunk;
																unsigned short i, f, num;
																char*name=0;
																numFaces=loader->ReadWord();
																face=new FACE_3DS[numFaces];
																for(i = 0; i < numFaces; i++){
																 face[i].v1    = loader->ReadWord();
																 face[i].v2    = loader->ReadWord();
																 face[i].v3    = loader->ReadWord();
																 face[i].flags = loader->ReadWord();
																 face[i].materialName = 0;
																 face[i].material     = 0;
																};
																length -= ((numFaces * sizeof(unsigned short)) << 2) + sizeof(unsigned short);
																// Sub Chunk(s) (0x4130, 0x4150) einlesen
																while(length > 0){
																 switch(loader->ReadChunk(&chunk)){
																  case FACE_MATERIAL_3DS:
																   loader->ReadName(&name);
																   //Engine->LogFile.Print("Material Name: %s\n", name);
																   num = loader->ReadWord();
																   for(i = 0; i < num; i++){
																    f=loader->ReadWord();
																    face[f].materialName = new char[strlen(name) + 1];
																    strcpy(face[f].materialName, name);
																    //Engine->LogFile.Print("Face Name: %s, %u\n", name, i);
																   };
																   delete[] name;
																   break;
																  /*case FACE_SMOOTH_3DS:
																   fseek(loader->file, chunk.len - CHUNKSIZE_3DS, SEEK_CUR);
																   break;*/             
																  default:
																   //Engine->LogFile.Print("Unknown Chunk: id = 0x%x, len = %u, length = %u\n", chunk.id, chunk.len, length);
																   //fseek(loader->file, chunk.len - CHUNKSIZE_3DS, SEEK_CUR);
																   loader->bufferPos += chunk.len - CHUNKSIZE_3DS;
																   break;
																 };
																 // Länge anpassen
																 length-=chunk.len;
																};
};
void _welt3DSObject::ReadTexCoords(unsigned int length){//  Liest Texturkoordinaten ein
																unsigned short  i;
																if(numVertices != loader->ReadWord()){
																 L->l("FEHLER _welt3DSObject::ReadTexCoords() -> Falsche Texturkoordinatenanzahl!");
																 return;
																};
																texCoord = new TEXCOORD_3DS[numVertices];
																for(i = 0; i < numVertices; i++){
																 loader->ReadFloat(&texCoord[i].u);
																 loader->ReadFloat(&texCoord[i].v);
																 texCoord[i].u = -texCoord[i].u;
																 texCoord[i].v = -texCoord[i].v;
																 //Engine->LogFile.Print("U: %f, V: %f\n", texCoord[i].u, texCoord[i].v);
																};
};

void _welt3DSObject::ReadLocalCoordinates(){//  Liest das lokale Koordinatensystem ein
																float         fTemp[3];
																unsigned int  *iTemp = (unsigned int *)&fTemp[0];
																// Lokale X-Achse
																*iTemp       = loader->ReadDword();
																*(iTemp + 2) = loader->ReadDword();
																*(iTemp + 1) = loader->ReadDword();
																localX.x(fTemp[VEC_X]);
																localX.y(fTemp[VEC_Y]);
																localX.z( -fTemp[VEC_Z]);
																// Lokale Z-Achse
																*iTemp       = loader->ReadDword();
																*(iTemp + 2) = loader->ReadDword();
																*(iTemp + 1) = loader->ReadDword();
																localZ.x(fTemp[VEC_X]);
																localZ.y(fTemp[VEC_Y]);
																localZ.z(-fTemp[VEC_Z]);
																// Lokale Y-Achse
																*iTemp       = loader->ReadDword();
																*(iTemp + 2) = loader->ReadDword();
																*(iTemp + 1) = loader->ReadDword();
																localY.x(fTemp[VEC_X]);
																localY.y(fTemp[VEC_Y]);
																localY.z(-fTemp[VEC_Z]);
																// Lokale Position
																*iTemp       = loader->ReadDword();
																*(iTemp + 2) = loader->ReadDword();
																*(iTemp + 1) = loader->ReadDword();
																localPos.x(fTemp[VEC_X]);
																localPos.y(fTemp[VEC_Y]);
																localPos.z(-fTemp[VEC_Z]);
};
void _welt3DSObject::CalcNormals(bool inverse){//  Berechnet die Normalenvektoren
																if(faceNormal)return;
																unsigned short i;
																_tg len;
																VERTEX_3DS vec1, vec2;
																faceNormal=new VERTEX_3DS[numFaces];
																for(i=0;i<numFaces;i++){
																 vec1.x = vertex[face[i].v2].x - vertex[face[i].v1].x;
																 vec1.y = vertex[face[i].v2].y - vertex[face[i].v1].y;
																 vec1.z = vertex[face[i].v2].z - vertex[face[i].v1].z;
																 vec2.x = vertex[face[i].v3].x - vertex[face[i].v1].x;
																 vec2.y = vertex[face[i].v3].y - vertex[face[i].v1].y;
																 vec2.z = vertex[face[i].v3].z - vertex[face[i].v1].z;
																 if(!inverse){
																  faceNormal[i].x = vec1.y * vec2.z - vec1.z * vec2.y;  // y * z - z * y;
																  faceNormal[i].y = vec1.x * vec2.z - vec1.z * vec2.x;  // x * z - z * x;
																  faceNormal[i].z = vec1.x * vec2.y - vec1.y * vec2.x;  // x * y - y * x;
																 }else{
																  faceNormal[i].x = vec2.y * vec1.z - vec2.z * vec1.y;  // y * z - z * y;
																  faceNormal[i].y = vec2.x * vec1.z - vec2.z * vec1.x;  // x * z - z * x;
																  faceNormal[i].z = vec2.x * vec1.y - vec2.y * vec1.x;  // x * y - y * x;
																 };
																 // Normalisieren
																 len = (_tg)(1.0/sqrt(faceNormal[i].x * faceNormal[i].x + faceNormal[i].y * faceNormal[i].y +faceNormal[i].z*faceNormal[i].z));
																 faceNormal[i].x*=float(len);
																 faceNormal[i].y*=float(len);
																 faceNormal[i].z*=float(len);
																};
};

void _welt3DSObject::AssignMaterials(){//  Weist die Materialien zu
																unsigned short  i, num;
																for(i = 0; i < numFaces; i++){
																 num = 0;
																 // FIXME: Endlosschleife verhindern
																 while(num < loader->numMaterials){
																  // Zuerst nur den ersten Buchstaben prüfen
																  if(face[i].materialName[0] == *loader->material[num].GetName()[0]){
																   if(!strcmp(face[i].materialName, *loader->material[num].GetName())){
																    face[i].material = &loader->material[num];
																    break;
																   };
																  };
																  num++;
																 }; 
																 if(num == loader->numMaterials){
																  L->l("FEHLER _welt3DSObject<tg>::AssignMaterials() -> Gesuchtes Material nicht vorhanden!");
																  return;
																 };
																};
}


/*
// ==========================
//  Gibt einen Vertex zurück
// ==========================
template <class tg> VERTEX_3DS *_welt3DSObject<tg>::GetVertex(unsigned short num)
{
   if(num < 0 || num >= numVertices)
     return(0);
     
   return(&vertices[num]);  
}


// =======================
//  Gibt eine Face zurück
// =======================
template <class tg> FACE_3DS *_welt3DSObject<tg>::GetFace(unsigned short num)
{
   if(num < 0 || num >= numFaces)
     return(0);
     
   return(&faces[num]);  
}
*/


/*




// =============================================
//  Konvertiert das Objekt in unser Mesh-Format
// =============================================
template <class tg> void _welt3DSObject<tg>::ConvertToMesh(OoS_Mesh<tg> *mesh)
{
   unsigned short   i;
   OoS_Vertex<tg>   **oos_vertices;
   OoS_Polygon<tg>  *poly;
   
   
   oos_vertices = new OoS_Vertex<tg>*[numVertices];
   
   // Vertices konvertieren
   for(i = 0; i < numVertices; i++)
     {
        oos_vertices[i] = new OoS_Vertex<tg>;
             
        oos_vertices[i]->SetLocal(vertex[i].x, vertex[i].y, vertex[i].z);
        oos_vertices[i]->SetWorld(vertex[i].x, vertex[i].y, vertex[i].z);
     }
     
   // Faces konvertieren
   for(i = 0; i < numFaces; i++)
     {
        poly = new OoS_Polygon<tg>;
             
        poly->InsertVertex(oos_vertices[face[i].v1]);
        poly->InsertVertex(oos_vertices[face[i].v2]);
        poly->InsertVertex(oos_vertices[face[i].v3]);
             
        // Polygon ins Mesh einhängen
        mesh->InsertNode(poly);
     }
   
   delete[] oos_vertices;
}


// ====================
//  Rendert das Objekt
// ====================
template <class tg> void _welt3DSObject<tg>::Render(void)
{
   
   glDisable(GL_TEXTURE_2D);

   for(unsigned short i = 0; i < numFaces; i++)
     {        glBegin(GL_LINE_LOOP);
             glVertex3f(vertex[face[i].v1].x, vertex[face[i].v1].y, vertex[face[i].v1].z);
             glVertex3f(vertex[face[i].v2].x, vertex[face[i].v2].y, vertex[face[i].v2].z);
             glVertex3f(vertex[face[i].v3].x, vertex[face[i].v3].y, vertex[face[i].v3].z);
             glEnd();
    
     }
   
   glEnable(GL_TEXTURE_2D);
   
}
*/
//*****************************************************************************************************************************************************************************************************************
//																W E L T 3 D S M A T E R I A L
//*****************************************************************************************************************************************************************************************************************
_welt3DSMaterial::_welt3DSMaterial(){
																loader = 0;
																materialName = 0;
																ambient[0]  = ambient[1]  = ambient[2]  = 0.0f;
																diffuse[0]  = diffuse[1]  = diffuse[2]  = 0.0f;
																specular[0] = specular[1] = specular[2] = 0.0f;
																memset(texture, 0, sizeof(texture));
};
_welt3DSMaterial::_welt3DSMaterial(_welt3DSLoader*l){
															    loader = l;
															    materialName = 0;
															    memset(texture, 0, sizeof(texture));
};
_welt3DSMaterial::~_welt3DSMaterial(){
															    delete[] materialName;
															    for(unsigned short i=0;i<MAXTEXTURES_3DS;i++) delete[] texture[i].name;
};
char**_welt3DSMaterial::GetName(){ 
																return(&materialName); 
};
TEXTURE_3DS*_welt3DSMaterial::GetTexture(unsigned short num){ 
																return(&texture[num]); 
}
void _welt3DSMaterial::SetLoader(_welt3DSLoader*l){
																loader=l;
};
/*
void _welt3DSMaterial::BindTexture(unsigned short num){
																texture[num].texture.Bind();
};*/
void _welt3DSMaterial::ReadTextureMap(unsigned short num, unsigned int length){//  Liest eine Textur ein
																CHUNK_3DS  chunk;
																texture[num].used = true;
																while(length>0){
																 switch(loader->ReadChunk(&chunk)){
																  case TEXMAP_NAME_3DS:
																   loader->ReadName(&texture[num].name);
																   //Engine->LogFile.Print("3DS-Texture: %s\n", texture[num].name);
																   /*
																   // FIXME
																   char  name[260];
																   int   len;
																   strcpy(name, "data/textures/");
															       strcat(name, texture[num].name);
															       len = strlen(name);
																   name[--len] = 'p';
																   name[--len] = 'm';
																   name[--len] = 'b';
																   texture[num].texture.Load(name);*/
																   break;
																  case TEXMAP_USCALE_3DS:
																   loader->ReadFloat(&texture[num].uScale);
																   break;
																  case TEXMAP_VSCALE_3DS:
																   loader->ReadFloat(&texture[num].vScale);
																   break;
																  case TEXMAP_UOFFSET_3DS:
																   loader->ReadFloat(&texture[num].uOffset);
																   break;
																  case TEXMAP_VOFFSET_3DS:
																   loader->ReadFloat(&texture[num].vOffset);
																   break;
																  default:
																   //Engine->LogFile.Print("Unknown Chunk: id = 0x%x, len = %u, length = %u\n", chunk.id, chunk.len, length);
																   //fseek(loader->file, chunk.len - CHUNKSIZE_3DS, SEEK_CUR);
																   loader->bufferPos += chunk.len - CHUNKSIZE_3DS;
																   break;
																 };
																 // Länge anpassen
																 length-=chunk.len;
																};
																//Engine->LogFile.Print("TexCoords: %f, %f, %f, %f\n", texture[num].uScale, texture[num].vScale,
																//                    texture[num].uOffset, texture[num].vOffset);
};
void _welt3DSMaterial::ReadAmbientColor(unsigned int length){//  Liest die ambiente(n) Farbe(n) ein
																CHUNK_3DS  chunk;
																while(length>0){
																 switch(loader->ReadChunk(&chunk)){
																  case COLOR_FLOAT_3DS:
																   loader->ReadFloat(&ambient[0]);
																   loader->ReadFloat(&ambient[1]);
																   loader->ReadFloat(&ambient[2]);
																   //Engine->LogFile.Print("Ambient = %f, %f, %f\n", ambient[0], ambient[1], ambient[2]);
																   break;
																  case COLOR_BYTE_3DS:
																   ambient[0] = (float)loader->ReadByte() / 255.0f;
																   ambient[1] = (float)loader->ReadByte() / 255.0f;
																   ambient[2] = (float)loader->ReadByte() / 255.0f;
																   //Engine->LogFile.Print("Ambient = %f, %f, %f\n", ambient[0], ambient[1], ambient[2]);
																   break;
																  default:
																   //Engine->LogFile.Print("Unknown Chunk: id = 0x%x, len = %u, length = %u\n", chunk.id, chunk.len, length);
																   //fseek(loader->file, chunk.len - CHUNKSIZE_3DS, SEEK_CUR);
																   loader->bufferPos+=chunk.len - CHUNKSIZE_3DS;
																   break;
																 };
																 // Länge anpassen
																 length-=chunk.len;  
																};
};

void _welt3DSMaterial::ReadDiffuseColor(unsigned int length){//  Liest die diffuse(n) Farbe(n) ein
																CHUNK_3DS  chunk;
																while(length>0){
																 switch(loader->ReadChunk(&chunk)){
																  case COLOR_FLOAT_3DS:
																   loader->ReadFloat(&diffuse[0]);
																   loader->ReadFloat(&diffuse[1]);
																   loader->ReadFloat(&diffuse[2]);
																   //Engine->LogFile.Print("Diffuse = %f, %f, %f\n", diffuse[0], diffuse[1], diffuse[2]);
																   break;
																  case COLOR_BYTE_3DS:
																   diffuse[0] = (float)loader->ReadByte() / 255.0f;
																   diffuse[1] = (float)loader->ReadByte() / 255.0f;
																   diffuse[2] = (float)loader->ReadByte() / 255.0f;
																   //Engine->LogFile.Print("Diffuse = %f, %f, %f\n", diffuse[0], diffuse[1], diffuse[2]);
																   break;
																  default:
																   //Engine->LogFile.Print("Unknown Chunk: id = 0x%x, len = %u, length = %u\n", chunk.id, chunk.len, length);
																   //fseek(loader->file, chunk.len - CHUNKSIZE_3DS, SEEK_CUR);
																   loader->bufferPos += chunk.len - CHUNKSIZE_3DS;
																   break;
																 };
																 // Länge anpassen
																 length -= chunk.len;  
																};
};
void _welt3DSMaterial::ReadSpecularColor(unsigned int length){//  Liest die specular Farbe(n) ein
																CHUNK_3DS  chunk;
																while(length>0){
																 switch(loader->ReadChunk(&chunk)){
																  case COLOR_FLOAT_3DS:
																   loader->ReadFloat(&specular[0]);
																   loader->ReadFloat(&specular[1]);
																   loader->ReadFloat(&specular[2]);
																   //Engine->LogFile.Print("Specular = %f, %f, %f\n", specular[0], specular[1], specular[2]);
																   break;
	 															  case COLOR_BYTE_3DS:
																   specular[0] = (float)loader->ReadByte() / 255.0f;
																   specular[1] = (float)loader->ReadByte() / 255.0f;
																   specular[2] = (float)loader->ReadByte() / 255.0f;
																   //Engine->LogFile.Print("Specular = %f, %f, %f\n", specular[0], specular[1], specular[2]);
																   break;
																  default:
																   //Engine->LogFile.Print("Unknown Chunk: id = 0x%x, len = %u, length = %u\n", chunk.id, chunk.len, length);
																   //fseek(loader->file, chunk.len - CHUNKSIZE_3DS, SEEK_CUR);
																   loader->bufferPos+=chunk.len - CHUNKSIZE_3DS;
																   break;
																 };
																 // Länge anpassen
																 length-=chunk.len;
																};
};
//*****************************************************************************************************************************************************************************************************************
//																W E L T 3 D S L O A D E R
//*****************************************************************************************************************************************************************************************************************
_welt3DSLoader::_welt3DSLoader(){
																buffer = 0;
																bufferPos = 0;
																version_3DS = version_mesh = 0;
																numMaterials = 0;
																//material = 0;
																for(unsigned short i = 0; i < MAXMATERIALS_3DS; i++)material[i].SetLoader(this);  // FIXME
};
_welt3DSLoader::~_welt3DSLoader(){
																//delete[] material;
};
unsigned char  _welt3DSLoader::ReadByte(){
																return(buffer[bufferPos++]); 
};
unsigned short _welt3DSLoader::ReadWord(){ 
																unsigned short temp1 = ReadByte(), temp2 = ReadByte(); return((temp2 << 8) | temp1); 
};
unsigned int   _welt3DSLoader::ReadDword(){ 
																unsigned int temp1 = ReadWord(), temp2 = ReadWord(); return((temp2 << 16) | temp1);
};
void _welt3DSLoader::ReadFloat(float*f){ 
																unsigned int *temp = (unsigned int *)f;  *temp = ReadDword(); 
};
unsigned short _welt3DSLoader::ReadChunk(CHUNK_3DS *chunk){//  Liest einen Chunk ein (big-endian), id wird zurückgegeben
																chunk->id  = ReadWord();
																chunk->len = ReadDword();
																/*
																if(0xFFFF == chunk->id){
																Error("_welt3DSLoader::Load() -> Ende der Datei erreicht! (falscher Dateityp?)");
																return(0);
																};
																*/
																return(chunk->id);
};
unsigned int _welt3DSLoader::ReadName(char **name){//  Liest einen Namen ein
																int           len = 0;
																unsigned int  foo = 0;
																// Den Namen einlesen
																while(ReadByte()) len++;
																name[0] = new char[++len];
																//fseek(file, -len, SEEK_CUR);
																bufferPos -= len;
																while(true){
															 	 name[0][foo] = ReadByte();
																 if(!name[0][foo++])break;
																};
																return(foo);
};
void _welt3DSLoader::ProcessMainChunk(unsigned int length){//  Verarbeitet den Main-Chunk
																CHUNK_3DS  chunk;
																//DemoSys->Log.Print("processing main chunk!\n");
																while(length>0){
																 switch(ReadChunk(&chunk)){
																  case MAIN_VERSION_3DS:
																   version_3DS = ReadDword();
																   break;
																  case MAIN_EDIT_3DS:
																   ProcessEditorChunk(chunk.len - CHUNKSIZE_3DS);
																   break; 
																  default:
																   //DemoSys->Log.Print("Unknown Chunk: id = 0x%x, len = %u, length = %u\n", chunk.id, chunk.len, length);
																   //fseek(file, chunk.len - CHUNKSIZE_3DS, SEEK_CUR);
																   bufferPos += chunk.len - CHUNKSIZE_3DS;
																   break;
																 };
																 // Länge anpassen
																 length -= chunk.len;
																};
};
void _welt3DSLoader::ProcessEditorChunk(unsigned int length){//  Verarbeitet den Editor-Chunk
																CHUNK_3DS  chunk;
																//DemoSys->Log.Print("processing editor chunk!\n");
																while(length > 0){
																 switch(ReadChunk(&chunk)){
																  case EDIT_MESHVERSION_3DS:  // mesh-version
																   version_mesh = ReadDword();
																   break;
																  case EDIT_CONFIG1_3DS:  // I don't know exactly about this, it's one float-value...
																   ReadDword();
																   break;
																  case EDIT_OBJECT_3DS:  // Object-Chunk
																   ProcessObjectChunk(chunk.len - CHUNKSIZE_3DS);
																   break;
																  default:
																   //Engine->LogFile.Print("Unknown Chunk: id = 0x%x, len = %u, length = %u\n", chunk.id, chunk.len, length);
																   //fseek(file, chunk.len - CHUNKSIZE_3DS, SEEK_CUR);
																   bufferPos += chunk.len - CHUNKSIZE_3DS;
																   break;
																 };
																 // Länge anpassen
																 length -= chunk.len;
																};
};
void _welt3DSLoader::ProcessObjectChunk(unsigned int length){//  Verarbeitet den Objekt-Chunk
																CHUNK_3DS chunk;
																_welt3DSObject*object=new _welt3DSObject(this);
																// Den Namen des Objekts einlesen
																length-=ReadName(object->GetName());
																while(length>0){
																 switch(ReadChunk(&chunk)){
																  case OBJECT_TRIMESH_3DS:  // Dreiecks-Mesh
																   ProcessTriangularMesh(object, chunk.len - CHUNKSIZE_3DS);
																   break;
																  default:
																   //Engine->LogFile.Print("Unknown Chunk: id = 0x%x, len = %u, length = %u\n", chunk.id, chunk.len, length);
																   //fseek(file, chunk.len - CHUNKSIZE_3DS, SEEK_CUR);
																   bufferPos += chunk.len - CHUNKSIZE_3DS;
																   break;
																 };
																 // Länge anpassen 
																 length -= chunk.len;
																};
																// Normalenvektoren vorberechnen
																object->CalcNormals(false);
																//DemoSys->Log.Print("3DS-Object: %s, %u vertices, %u faces\n", *object->GetName(), object->GetVertexCount(), object->GetFaceCount());
																objectList->einhaengen(object);
};
void _welt3DSLoader::ProcessTriangularMesh(_welt3DSObject*object, unsigned int length){//  Verarbeitet ein Dreiecks-Mesh
																CHUNK_3DS chunk;
																while(length>0){
																 switch(ReadChunk(&chunk)){
																  case TRIMESH_VERTICES_3DS:
																   object->ReadVertices();
																   break;
																  case TRIMESH_FACES_3DS:
																   object->ReadFaces(chunk.len - CHUNKSIZE_3DS);
																   break;
																  case TRIMESH_TEXCOORDS_3DS:
																   object->ReadTexCoords(chunk.len - CHUNKSIZE_3DS);
																   //Engine->LogFile.Print("FICKENSE!\n");
																   break;
																  case TRIMESH_LOCALCOORDS_3DS:
																   object->ReadLocalCoordinates();
																   break;
																  default:
																   //Engine->LogFile.Print("Unknown Chunk: id = 0x%x, len = %u, length = %u\n", chunk.id, chunk.len, length);
																   //fseek(file, chunk.len - CHUNKSIZE_3DS, SEEK_CUR);
																   bufferPos += chunk.len - CHUNKSIZE_3DS;
																   break;
																 };
																 // Länge anpassen 
																 length -= chunk.len;
																};
};
void _welt3DSLoader::ProcessMaterialChunk(unsigned int length){//  Verarbeitet den Material-Chunk
																CHUNK_3DS chunk;
																while(length>0){
																 switch(ReadChunk(&chunk)){
																  case MATERIAL_NAME_3DS:
																   numMaterials++;
																   ReadName(material[numMaterials].GetName());
																   //DemoSys->Log.Print("3DS-Material: %s\n", *material[numMaterials].GetName());
																   break;
																  case MATERIAL_AMBIENT_3DS:
																   material[numMaterials].ReadAmbientColor(chunk.len - CHUNKSIZE_3DS);
																   break;
																  case MATERIAL_DIFFUSE_3DS:
																   material[numMaterials].ReadDiffuseColor(chunk.len - CHUNKSIZE_3DS);
																   break;
																  case MATERIAL_TEXMAP1_3DS:
																   material[numMaterials].ReadTextureMap(0, chunk.len - CHUNKSIZE_3DS);
																   break;
																  case MATERIAL_TEXMAP2_3DS:
																   material[numMaterials].ReadTextureMap(1, chunk.len - CHUNKSIZE_3DS);
																   break;
																  default:
																   //Engine->LogFile.Print("Unknown Chunk: id = 0x%x, len = %u, length = %u\n", chunk.id, chunk.len, length);
																   //fseek(file, chunk.len - CHUNKSIZE_3DS, SEEK_CUR);
																   bufferPos += chunk.len - CHUNKSIZE_3DS;
																   break;
																 };
																 // Länge anpassen
																 length-=chunk.len;
																};
};
int _welt3DSLoader::Load(const char *name, _liste<_welt3DSObject>*list){//  Lädt ein 3DS-File von der Festplatte (gibt die Größe der Datei zurück)
																unsigned short                i;
																unsigned long                 size;
																CHUNK_3DS                     chunk;
																_listenknoten<_welt3DSObject>*node,*tempNode;
																bufferPos=0;
																#ifdef _USEDATAFILE
																 buffer = LoadData(&size, name);
																#else
																 FILE  *file;
																 // Datei öffnen
																 if(!(file=fopen(name,"rb"))) L->l("FEHLER _welt3DSLoader::Load() -> Konnte Datei nicht öffnen! (%)", name);
																 long  oldpos, newpos;
																 oldpos = ftell(file);
																 fseek(file, 0, SEEK_END);
																 newpos = ftell(file);
																 fseek(file, oldpos, SEEK_SET);
																 size = newpos;
																 buffer = new char[size];
																 if(size != fread(buffer, 1, size, file))  L->l("FEHLER _welt3DSLoader::Load() -> Konnte Datei nicht lesen! (%)", name);
																#endif
																// Falls vorher schon geladen wurde, alte Objekte löschen (Knoten nicht freigeben!)
																objectList = list;
																//DemoSys->Log.Print("Loading 3DS-File: \"%s\"...\n", name);
																// Hauptchunk einlesen und überprüfen
																if(MAIN_3DS!=ReadChunk(&chunk))L->l("FEHLER _welt3DSLoader::Load() -> Unbekanntes Dateiformat!");
																numMaterials = 0xFFFF;
																ProcessMainChunk(chunk.len-CHUNKSIZE_3DS);
																//DemoSys->Log.Print("Num Materials = %u\nDone!\n", ++numMaterials);
																// Speicher wieder freigeben
																delete buffer;
																// Materialien zuweisen
																if(numMaterials){
																 iterierenliste(objectList,node,
																  // Alle Objekte mit 0 Vertices löschen (Kamera, Lichter etc.)
																  if(!node->objekt()->GetVertexCount()){
																   tempNode = node->naechstes();
																   delete node;
																   node = tempNode;
																   continue;
																  };
																  // node->objekt()->AssignMaterials();
																  for(i = 0; i < node->objekt()->numFaces; i++){
																   delete[] node->objekt()->face[i].materialName;
																   node->objekt()->face[i].materialName = 0;
																  };
																 );
																};
																return(size);
};
