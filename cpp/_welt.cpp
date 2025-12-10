//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _welt.cpp
//  Datum        : 09.01.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_welt.hpp>
#include <_weltoptik.hpp>
#include <_weltpolygon.hpp>

//NOCH EINGBUNDEN , weil grafik nicht vollständig:
#include <_grafikopengl.hpp>

void weltaushaengenspeicherung(_listebasis<_speicherbarbinaer>*l){ 
																while(l->erstes()) l->erstes()->aushaengenspeicherung();
};
void welteinhaengenspeicherung(_welt*w,_listebasis<_speicherbarbinaer>*l){
																_kugel*kit;
                                                                _netz*nit;
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_polygon>*lnp;
                                                                _verbindervertexpolygon*cit;
																_partikelquelle*qit;
																//_figur*fit;
																_textur<_tb>*tit;
                                                                _licht<_tg,_to>*lit;
                                                                _gravitation<_tg>*git;
																_feldelektrostatisch<_tg>*feit;
																_feldmagnetostatisch<_tg>*fmit;
                                                                _kamera<_tg>*mit;
                                                                _partition::_zone*zit;
                                                                _partition::_ebene*eit;
                                                                _partition::_sektor*sit;
                                                                _partition::_polygon*ppit;
                                                                _partition::_vertex*pvit;
																//_partition::_ebene*peit;
																unsigned int i=0;
																weltaushaengenspeicherung(l);

																 w->einhaengenspeicherung(l,"w",i++);
																 iterierenliste(w,tit,tit->einhaengenspeicherung(l,"t",i++));
																 iterierenliste(w,nit,
																  nit->markierungvertex(1);
																  nit->einhaengenspeicherung(l,"n",i++);
																  iterierenliste(nit,pit,
																   pit->einhaengenspeicherung(l,"p",i++);
																   iterierenliste(pit,lnvit,
																    vit=lnvit->objekt();
																    if(vit->markierung()==1){
															 		 vit->markierung(0);
																	 vit->einhaengenspeicherung(l,"v",i++);
																	 iterierenliste(vit,lnp,
																	  cit=static_cast<_verbindervertexpolygon*>(lnp);
																	  cit->einhaengenspeicherung(l,"c",i++);
																	 );
																    };
																   );
																  );
																 );
																 iterierenliste(w,kit,kit->einhaengenspeicherung(l,"k",i++));
																 iterierenliste(w,qit,qit->einhaengenspeicherung(l,"q",i++));
																 //iterierenliste(w,fit,fit->einhaengenspeicherung(l,"f",i++));
																 iterierenliste(w,mit,mit->einhaengenspeicherung(l,"m",i++));
																 iterierenliste(w,lit,lit->einhaengenspeicherung(l,"l",i++));
																 iterierenliste(w,git,git->einhaengenspeicherung(l,"g",i++));
																 iterierenliste(w,feit,feit->einhaengenspeicherung(l,"fe",i++));
																 iterierenliste(w,fmit,fmit->einhaengenspeicherung(l,"fm",i++));
																 iterierenliste(w,zit,
																  zit->einhaengenspeicherung(l,"z",i++);
																  iterierenliste(zit,eit,eit->einhaengenspeicherung(l,"e",i++));
																  iterierenliste(zit,sit,
																   sit->einhaengenspeicherung(l,"s",i++);
																   iterierenliste(sit,ppit,
																	ppit->einhaengenspeicherung(l,"pp",i++);
																	iterierenliste(ppit,pvit,
																	 pvit->einhaengenspeicherung(l,"pv",i++);
																	);
																   );
																  );
																 );

};


void weltspeichernbinaer(_zeichenkette<char> fn,_welt*w){
																_dateispeicherbarbinaer d(fn);
																if(d.oeffnen()){
																 d._datei::loeschen();
																 w->erzeugentextur();//alle benutzten texturen lokal instanziieren zum speichern, alle zeiger der welt darauf setzen
																 welteinhaengenspeicherung(w,&d);
																 w->speichern(&d);
																 weltaushaengenspeicherung(&d);
																 w->loeschentextur();//alle zeiger der welt wieder zurücksetzen auf die urspünglichen werte, lokale texturinstanzen löschen
															     d.schliessen();
																};
};
void weltladenbinaer(_zeichenkette<char> fn,_welt*&w,_texturverwaltung<_tb>*tv){
																_dateispeicherbarbinaer d(fn);
																w=0;
																if(d.oeffnennurlesen()){
																 w=new _welt();
																 L->l("welt konstruiert");
																 w->laden(&d);
																 _speicherbarbinaer*sit;
																 iterierenliste((&d),sit,sit->assoziieren());
																 w->aktualisieren();
															     L->l("Welt laden binaer beendet.");
															     L->l("Anzahl der Netze : ",(int)w->_listebasis<_netz>::anzahl());
															     L->l("Anzahl der Polygone : ",(int)w->anzahlpolygon());
																 
																 
																 weltaushaengenspeicherung(&d);
																 w->globalisierentextur(tv);
																 
																 /*
																 _polygon*pit;
																 _netz*nit;
																 iterierenliste(w,nit,iterierenliste(nit,pit,pit->speicherkonversion()));
																 */
																 
																 
															     d.schliessen();
																};
};
void weltspeichern(_zeichenkette<char> fn,_welt*w){
                                                                _dateispeicherbartext datei(fn);
                                                                _speicherbardynamisch<_welt >*sdworld;
                                                                _speicherbardynamisch<_netz >*sdmesh;
                                                                _speicherbardynamisch<_polygon >*sdpolygon;
                                                                _speicherbardynamisch<_vertex >*sdvertex;
                                                                _speicherbardynamisch<_verbindervertexpolygon >*sdconnector;
                                                               // _speicherbardynamisch<_texturvektor<_tg> >*sdtexturevector;
                                                                _speicherbardynamisch<_bild<_tb> >*sdmap;
                                                                //_speicherbardynamisch<_bildtga<_to> >*sdmaptga;
                                                                _speicherbardynamisch<_textur<_tb> >*sdtexture;
                                                                _speicherbardynamisch<_licht<_tg,_to> >*sdlight;
                                                                _speicherbardynamisch<_gravitation<_tg> >*sdgravitation;
                                                                _speicherbardynamisch<_kamera<_tg> >*sdcamera;
                                                                _speicherbardynamisch<_partition::_zone >*sdzone;
                                                                _speicherbardynamisch<_partition::_ebene >*sdplane;
                                                                _speicherbardynamisch<_partition::_sektor >*sdsector;
                                                                _speicherbardynamisch<_partition::_polygon >*sdppolygon;
                                                                _speicherbardynamisch<_partition::_vertex >*sdpvertex;
                                                                _netz*netz;
                                                                _polygon*polygon;
                                                                _vertex*vertex;
                                                                _verbindervertexpolygon*connector;
                                                                _bild<_tb>*bild;
                                                                _textur<_tb>*textur;
                                                                _licht<_tg,_to>*light;
                                                                _gravitation<_tg>*gravitation;
                                                                _kamera<_tg>*camera;
                                                                _partition::_zone*zone;
                                                                _partition::_ebene*ebene;
                                                                _partition::_sektor*sektor;
                                                                _partition::_polygon*ppolygon;
                                                                _partition::_vertex*pvertex;
                                                                unsigned int mi;
                                                                unsigned int pi;
                                                                unsigned int vi;
                                                                unsigned int ci;
                                                                //unsigned int mtgai;
                                                                unsigned int ti;
                                                                unsigned int li;
                                                                unsigned int gi;
                                                                unsigned int cami;
                                                                unsigned int zi;
                                                                unsigned int pli;
                                                                unsigned int si;
                                                                unsigned int ppi;
                                                                unsigned int pvi;
                                                                _zeichenkette<char> worldtype="_welt";
                                                                _zeichenkette<char> meshtype="_netz";
                                                                _zeichenkette<char> polygontype="_polygon";
                                                                _zeichenkette<char> vertextype="_vertex";
                                                                _zeichenkette<char> connectortype="_verbinder";
                                                                _zeichenkette<char> texturevectortype="_texturvektor";
                                                                _zeichenkette<char> maptgatype="_bildtga";
                                                                _zeichenkette<char> texturetype="_textur";
                                                                _zeichenkette<char> lighttype="_licht";
                                                                _zeichenkette<char> gravitationtype="_gravitation";
                                                                _zeichenkette<char> cameratype="_kamera";
                                                                _zeichenkette<char> zonetype="_zone";
                                                                _zeichenkette<char> planetype="_ebene";
                                                                _zeichenkette<char> sectortype="_sektor";
                                                                _zeichenkette<char> ppolygontype="_partitionpolygon";
                                                                _zeichenkette<char> pvertextype="_partitionvertex";
                                                                _zeichenkette<char> worldname="w";
                                                                _zeichenkette<char> meshname="m";
                                                                _zeichenkette<char> polygonname="p";
                                                                _zeichenkette<char> vertexname="v";
                                                                _zeichenkette<char> connectorname="c";
                                                                _zeichenkette<char> texturevectorname="tv";
                                                                _zeichenkette<char> maptganame="mtga";
                                                                _zeichenkette<char> texturename="tx";
                                                                _zeichenkette<char> lightname="l";
                                                                _zeichenkette<char> gravitationname="g";
                                                                _zeichenkette<char> cameraname="cam";
                                                                _zeichenkette<char> zonename="z";
                                                                _zeichenkette<char> planename="pl";
                                                                _zeichenkette<char> sectorname="s";
                                                                _zeichenkette<char> ppolygonname="pp";
                                                                _zeichenkette<char> pvertexname="pv";
                                                                char s[2048];
                                                                //----------------------------------------------------------------------------
                                                                sdworld=new _speicherbardynamisch<_welt >(&datei,w);
                                                                sdworld->typ(worldtype);
                                                                sdworld->name(worldname+"0");
                                                                mi=0;
                                                                
                                                                if(w->anfang(netz))do{
                                                                 sdmesh=new _speicherbardynamisch<_netz >(&datei,sdworld,netz);
                                                                 sdmesh->typ(meshtype);_itoa(mi,s,16);
                                                                 sdmesh->name(meshname+s);
                                                                 pi=0;
                                                                 if(netz->anfang(polygon))do{
                                                                  sdpolygon=new _speicherbardynamisch<_polygon >(&datei,sdmesh,polygon);
                                                                  sdpolygon->typ(polygontype);_itoa(pi,s,16);
                                                                  sdpolygon->name(polygonname+s);
                                                                  pi++;
                                                                 }while(netz->naechstes(polygon));
                                                                 vi=0;
                                                                 netz->markierungvertex(1);
                                                                 if(netz->anfang(polygon))do{
                                                                  _listenknoten<_vertex>*lnv;
                                                                  iterierenliste(polygon,lnv,
                                                                   vertex=lnv->objekt();
                                                                   if(vertex->markierung()==1){
                                                                    sdvertex=new _speicherbardynamisch<_vertex >(&datei,sdmesh,vertex);
                                                                    sdvertex->typ(vertextype);_itoa(vi,s,16);
                                                                    sdvertex->name(vertexname+s);
                                                                    ci=0;
                                                                    _listenknoten<_polygon>*lnp;
                                                                    iterierenliste(vertex,lnp,
                                                                     connector=static_cast<_verbindervertexpolygon*>(lnp);
                                                                     sdconnector=new _speicherbardynamisch<_verbindervertexpolygon >(&datei,sdvertex,connector);
                                                                     sdconnector->typ(connectortype);_itoa(ci,s,16);
                                                                     sdconnector->name(connectorname+s);
                                                                     ci++;
                                                                    );
                                                                    vi++;
                                                                    vertex->markierung(0);
                                                                   };
                                                                  );
                                                                 }while(netz->naechstes(polygon));
                                                                 mi++;
                                                                }while(w->naechstes(netz));
                                                                ti=0;
                                                                if(w->anfang(textur))do{
                                                                 sdtexture=new _speicherbardynamisch<_textur<_tb> >(&datei,sdworld,textur);
                                                                 sdtexture->typ(texturetype);_itoa(ti,s,16);
                                                                 sdtexture->name(texturename+s);
                                                                 
                                                                 _listenknoten<_bild<_tb> >*lnbild;
                                                                 if(textur->bitmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->bitmap()->naechstes(lnbild));
                                                                 if(textur->lightmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->lightmap()->naechstes(lnbild));
                                                                 if(textur->shadowmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->shadowmap()->naechstes(lnbild));
                                                                 if(textur->bumpmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->bumpmap()->naechstes(lnbild));
                                                                 if(textur->translightmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->translightmap()->naechstes(lnbild));
                                                                 if(textur->specularmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->specularmap()->naechstes(lnbild));
                                                                 if(textur->detailmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->detailmap()->naechstes(lnbild));
                                                                 if(textur->maskmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->maskmap()->naechstes(lnbild));
                                                                 
                                                                 ti++;
                                                                }while(w->naechstes(textur));
                                                                
                                                                li=0;
                                                                if(w->anfang(light))do{
                                                                 sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdworld,light);
                                                                 sdlight->typ(lighttype);_itoa(li,s,16);
                                                                 sdlight->name(lightname+s);
                                                                 li++;
                                                                }while(w->naechstes(light));
                                                                
                                                                gi=0;
                                                                if(w->anfang(gravitation))do{
                                                                 sdgravitation=new _speicherbardynamisch<_gravitation<_tg> >(&datei,sdworld,gravitation);
                                                                 sdgravitation->typ(gravitationtype);_itoa(gi,s,16);
                                                                 sdgravitation->name(gravitationname+s);
                                                                 gi++;
                                                                }while(w->naechstes(gravitation));
                                                                cami=0;
                                                                if(w->anfang(camera))do{
                                                                 sdcamera=new _speicherbardynamisch<_kamera<_tg> >(&datei,sdworld,camera);
                                                                 sdcamera->typ(cameratype);_itoa(cami,s,16);
                                                                 sdcamera->name(cameraname+s);
                                                                 cami++;
                                                                }while(w->naechstes(camera));
                                                                zi=0;
                                                                if(w->anfang(zone))do{
                                                                 sdzone=new _speicherbardynamisch<_partition::_zone >(&datei,sdworld,zone);
                                                                 sdzone->typ(zonetype);_itoa(zi,s,16);
                                                                 sdzone->name(zonename+s);
                                                                 si=0;
                                                                 if(zone->anfang(sektor))do{
                                                                  sdsector=new _speicherbardynamisch<_partition::_sektor >(&datei,sdzone,sektor);
                                                                  sdsector->typ(sectortype);_itoa(si,s,16);
                                                                  sdsector->name(sectorname+s);
                                                                  
                                                                  if(sektor->anfang(light))do{
                                                                   sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdsector,light);
                                                                   sdlight->typ(lighttype);
                                                                  }while(sektor->naechstes(light));
                                                                  
                                                                  ppi=0;
                                                                  if(sektor->anfang(ppolygon))do{
                                                                   sdppolygon=new _speicherbardynamisch<_partition::_polygon >(&datei,sdsector,ppolygon);
                                                                   sdppolygon->typ(ppolygontype);_itoa(ppi,s,16);
                                                                   sdppolygon->name(ppolygonname+s);
                                                                   pvi=0;
                                                                   if(ppolygon->anfang(pvertex))do{
                                                                    sdpvertex=new _speicherbardynamisch<_partition::_vertex >(&datei,sdppolygon,pvertex);
                                                                    sdpvertex->typ(pvertextype);_itoa(pvi,s,16);
                                                                    sdpvertex->name(pvertexname+s);
                                                                    pvi++;
                                                                   }while(ppolygon->naechstes(pvertex));
                                                                   ppi++;
                                                                  }while(sektor->naechstes(ppolygon));
                                                                  si++;
                                                                 }while(zone->naechstes(sektor));
                                                                 pli=0;
                                                                 if(zone->anfang(ebene))do{
                                                                  sdplane=new _speicherbardynamisch<_partition::_ebene >(&datei,sdzone,ebene);
                                                                  sdplane->typ(planetype);_itoa(pli,s,16);
                                                                  sdplane->name(planename+s);
                                                                  pli++;
                                                                 }while(zone->naechstes(ebene));
                                                                 zi++;
                                                                }while(w->naechstes(zone));
                                                                datei.speichern();
};

void weltladen(_zeichenkette<char> fn,_liste<_welt >*lw){
                                                                _listenknoten<_welt >*lwit;
                                                                _vektor3<_tg> nullvector;
                                                                _vektor3<_tg> hvg;
                                                                _vektor4<_to> hvo;
                                                                _vektor3<_to> hvo3;
                                                                //_tg hg;
                                                                _dateispeicherbartext datei(fn);
                                                                _welt*welt;
                                                                _netz*netz;
                                                                _polygon*polygon;
                                                                _vertex*vertex;
                                                                _verbindervertexpolygon*connector;
                                                                _bild<_tb>*maptga;
                                                                _textur<_tb>*textur;
                                                                _licht<_tg,_to>*light;
                                                                _gravitation<_tg>*gravitation;
                                                                _kamera<_tg>*camera;
                                                                _partition::_zone*zone;
                                                                _partition::_ebene*ebene;
                                                                _partition::_sektor*sektor;
                                                                _partition::_polygon*ppolygon;
                                                                _partition::_vertex*pvertex;
                                                                _liste<_dateispeicherbarknoten > worldnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*worldnit;
                                                                _liste<_dateispeicherbarknoten > meshnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*meshnit;
                                                                _liste<_dateispeicherbarknoten > polygonnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*polygonnit;
                                                                _liste<_dateispeicherbarknoten > vertexnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*vertexnit;
                                                                _liste<_dateispeicherbarknoten > connectornodes;
                                                                _listenknoten<_dateispeicherbarknoten >*connectornit;
                                                                _liste<_dateispeicherbarknoten > lightnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*lightnit;
                                                                _liste<_dateispeicherbarknoten > maptganodes;
                                                                _listenknoten<_dateispeicherbarknoten >*maptganit;
                                                                _liste<_dateispeicherbarknoten > texturenodes;
                                                                _listenknoten<_dateispeicherbarknoten >*texturenit;
                                                                _liste<_dateispeicherbarknoten > gravitationnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*gravitationnit;
                                                                _liste<_dateispeicherbarknoten > cameranodes;
                                                                _listenknoten<_dateispeicherbarknoten >*cameranit;
                                                                _liste<_dateispeicherbarknoten > zonenodes;
                                                                _listenknoten<_dateispeicherbarknoten >*zonenit;
                                                                _liste<_dateispeicherbarknoten > planenodes;
                                                                _listenknoten<_dateispeicherbarknoten >*planenit;
                                                                _liste<_dateispeicherbarknoten > sectornodes;
                                                                _listenknoten<_dateispeicherbarknoten >*sectornit;
                                                                _liste<_dateispeicherbarknoten > ppolygonnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*ppolygonnit;
                                                                _liste<_dateispeicherbarknoten > pvertexnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*pvertexnit;
                                                                _speicherbardynamisch<_welt >*sdworld;
                                                                _speicherbardynamisch<_netz >*sdmesh;
                                                                _speicherbardynamisch<_polygon >*sdpolygon;
                                                                _speicherbardynamisch<_vertex >*sdvertex;
                                                                _speicherbardynamisch<_verbindervertexpolygon >*sdconnector;
                                                                _speicherbardynamisch<_licht<_tg,_to> >*sdlight;
                                                                _speicherbardynamisch<_bild<_tb> >*sdmap;
                                                                _speicherbardynamisch<_textur<_tb> >*sdtexture;
                                                                _speicherbardynamisch<_gravitation<_tg> >*sdgravitation;
                                                                _speicherbardynamisch<_kamera<_tg> >*sdcamera;
                                                                _speicherbardynamisch<_partition::_zone >*sdzone;
                                                                _speicherbardynamisch<_partition::_ebene >*sdplane;
                                                                _speicherbardynamisch<_partition::_sektor >*sdsector;
                                                                _speicherbardynamisch<_partition::_polygon >*sdppolygon;
                                                                _speicherbardynamisch<_partition::_vertex >*sdpvertex;
                                                                _zeichenkette<char> worldtype="_welt";
                                                                _zeichenkette<char> meshtype="_netz";
                                                                _zeichenkette<char> polygontype="_polygon";
                                                                _zeichenkette<char> vertextype="_vertex";
                                                                _zeichenkette<char> connectortype="_verbinder";
                                                                _zeichenkette<char> texturevectortype="_texturvektor";
                                                                _zeichenkette<char> texturetype="_textur";
                                                                _zeichenkette<char> maptgatype="_bildtga";
                                                                _zeichenkette<char> lighttype="_licht";
                                                                _zeichenkette<char> gravitationtype="_gravitation";
                                                                _zeichenkette<char> cameratype="_kamera";
                                                                _zeichenkette<char> zonetype="_zone";
                                                                _zeichenkette<char> planetype="_ebene";
                                                                _zeichenkette<char> sectortype="_sektor";
                                                                _zeichenkette<char> ppolygontype="_partitionpolygon";
                                                                _zeichenkette<char> pvertextype="_partitionvertex";
                                                                //_win::_zeit tt;
                                                                //tt.anfang();
                                                                //unsigned int t0;
                                                                //unsigned int t1;
                                                                //unsigned int t2;
                                                                //---------------------------
                                                                //t0=tt.system();
                                                                lw->loeschen();
                                                                
                                                                worldnodes.aushaengen();
                                                                datei.holenuebertyp(worldtype,worldnodes);
                                                                if(worldnodes.anfang(worldnit))do{
                                                                 welt=new _welt();
                                                                 sdworld=new _speicherbardynamisch<_welt >(&datei,welt);
                                                                 welt->laden(worldnit->objekt(),sdworld);
                                                                 
                                                                 meshnodes.aushaengen();
                                                                 worldnit->objekt()->holenuebertyp(worldtype+"::"+meshtype,meshnodes);
                                                                 if(meshnodes.anfang(meshnit))do{
                                                                  netz=new _netz();
                                                                  netz->einhaengen(welt);
                                                                  sdmesh=new _speicherbardynamisch<_netz >(&datei,sdworld,netz);
                                                                  netz->laden(meshnit->objekt(),sdmesh);
                                                                  
                                                                  polygonnodes.aushaengen();
                                                                  meshnit->objekt()->holenuebertyp(worldtype+"::"+meshtype+"::"+polygontype,polygonnodes);
                                                                  if(polygonnodes.anfang(polygonnit))do{
                                                                   polygon=new _polygon(netz);
                                                                   sdpolygon=new _speicherbardynamisch<_polygon >(&datei,sdmesh,polygon);
                                                                   polygon->laden(polygonnit->objekt(),sdpolygon);
                                                                  }while(polygonnodes.naechstes(polygonnit));

                                                                  vertexnodes.aushaengen();
                                                                  meshnit->objekt()->holenuebertyp(worldtype+"::"+meshtype+"::"+vertextype,vertexnodes);
                                                                  if(vertexnodes.anfang(vertexnit))do{
                                                                   vertex=new _vertex(netz,nullvector);//pseudo parameter, spätere reassoziation
                                                                   sdvertex=new _speicherbardynamisch<_vertex >(&datei,sdmesh,vertex);
                                                                   vertex->laden(vertexnit->objekt(),sdvertex);
                                                                   
                                                                   connectornodes.aushaengen();
                                                                   vertexnit->objekt()->holenuebertyp(worldtype+"::"+meshtype+"::"+vertextype+"::"+connectortype,connectornodes);
                                                                   if(connectornodes.anfang(connectornit))do{
                                                                    connector=new _verbindervertexpolygon(vertex,polygon/*,vertex*/);//pseudo parameter, spätere reassoziation
                                                                    sdconnector=new _speicherbardynamisch<_verbindervertexpolygon >(&datei,sdvertex,connector);
                                                                    connector->laden(connectornit->objekt(),sdconnector);

                                                                 /*   texturevectornodes.aushaengen();
                                                                    connectornit->objekt()->holenuebertyp(worldtype+"::"+meshtype+"::"+vertextype+"::"+connectortype+"::"+texturevectortype,texturevectornodes);
                                                                    if(texturevectornodes.anfang(texturevectornit)){
                                                                     texturevector=connector;
                                                                     sdtexturevector=new _speicherbardynamisch<_texturvektor<_tg> >(&datei,sdconnector,texturevector);
                                                                     texturevector->laden(texturevectornit->objekt(),sdtexturevector);
                                                                    };*/
                                                                   
                                                                   }while(connectornodes.naechstes(connectornit));
                                                                  }while(vertexnodes.naechstes(vertexnit));
                                                                 }while(meshnodes.naechstes(meshnit));

                                                                 texturenodes.aushaengen();
                                                                 worldnit->objekt()->holenuebertyp(worldtype+"::"+texturetype,texturenodes);
                                                                 if(texturenodes.anfang(texturenit))do{
                                                                  textur=new _textur<_tb>(welt);
                                                                  sdtexture=new _speicherbardynamisch<_textur<_tb> >(&datei,sdworld,textur);
                                                                  textur->laden(texturenit->objekt(),sdtexture);
                                                                  
                                                                  _listebasis<_bild<_tb> > bilder;
                                                                  _bild<_tb>*mit;
                                                                  _bild<_tb>*mitn;
                                                                  unsigned int i;
                                                                  maptganodes.aushaengen();
                                                                  texturenit->objekt()->holenuebertyp(worldtype+"::"+texturetype+"::"+maptgatype,maptganodes);
                                                                  if(maptganodes.anfang(maptganit))do{
                                                                   maptga=new _bild<_tb>(1,1,4);
                                                                   sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,maptga);
                                                                   maptga->laden(maptganit->objekt(),sdmap);
                                                                   maptga->tiefereskalieren(1);
                                                                   maptga->datentausch(0,2);
                                                                   maptga->einhaengen(&bilder);
                                                                  }while(maptganodes.naechstes(maptganit));
                                                                  if(bilder.anfang(mit)){
                                                                   if(mit!=0) for(i=0;i<textur->pc[0];i++){
                                                                    if(mit) mitn=mit->naechstes();
                                                                    if(mit) textur->einfuegenbitmap(mit);
                                                                    if(mitn==mit) mit=0; else mit=mitn;
                                                                   };
                                                                   if(mit!=0) for(i=0;i<textur->pc[1];i++){
                                                                    if(mit) mitn=mit->naechstes();
                                                                    if(mit) textur->einfuegenlightmap(mit);
                                                                    if(mitn==mit) mit=0; else mit=mitn;
                                                                   };
                                                                   if(mit!=0) for(i=0;i<textur->pc[2];i++){
                                                                    if(mit) mitn=mit->naechstes();
                                                                    if(mit) textur->einfuegenshadowmap(mit);
                                                                    if(mitn==mit) mit=0; else mit=mitn;
                                                                   };
                                                                   if(mit!=0) for(i=0;i<textur->pc[3];i++){
                                                                    if(mit) mitn=mit->naechstes();
                                                                    if(mit) textur->einfuegenbumpmap(mit);
                                                                    if(mitn==mit) mit=0; else mit=mitn;
                                                                   };
                                                                   if(mit!=0) for(i=0;i<textur->pc[4];i++){
                                                                    if(mit) mitn=mit->naechstes();
                                                                    if(mit) textur->einfuegentransmissionmap(mit);
                                                                    if(mitn==mit) mit=0; else mit=mitn;
                                                                   };
                                                                   if(mit!=0) for(i=0;i<textur->pc[5];i++){
                                                                    if(mit) mitn=mit->naechstes();
                                                                    if(mit) textur->einfuegenspecularmap(mit);
                                                                    if(mitn==mit) mit=0; else mit=mitn;
                                                                   };
                                                                   if(mit!=0) for(i=0;i<textur->pc[6];i++){
                                                                    if(mit) mitn=mit->naechstes();
                                                                    if(mit) textur->einfuegendetailmap(mit);
                                                                    if(mitn==mit) mit=0; else mit=mitn;
                                                                   };
                                                                   if(mit!=0) for(i=0;i<textur->pc[7];i++){
                                                                    if(mit) mitn=mit->naechstes();
                                                                    if(mit) textur->einfuegenmaskmap(mit);
                                                                    if(mitn==mit) mit=0; else mit=mitn;
                                                                   };
                                                                  };
                                                                  bilder.loeschen();
                                                                  
                                                                 }while(texturenodes.naechstes(texturenit));
                                                                 
                                                                 lightnodes.aushaengen();
                                                                 worldnit->objekt()->holenuebertyp(worldtype+"::"+lighttype,lightnodes);
                                                                 if(lightnodes.anfang(lightnit))do{
                                                                  hvo3.setzen(1,0,0);
                                                                  light=new _licht<_tg,_to>(welt,nullvector,hvo3,10);
                                                                  sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdworld,light);
                                                                  light->laden(lightnit->objekt(),sdlight);
                                                                 }while(lightnodes.naechstes(lightnit));
                                                                 
                                                                 gravitationnodes.aushaengen();
                                                                 worldnit->objekt()->holenuebertyp(worldtype+"::"+gravitationtype,gravitationnodes);
                                                                 if(gravitationnodes.anfang(gravitationnit))do{
                                                                  gravitation=new _gravitation<_tg>(welt,nullvector,10);
                                                                  sdgravitation=new _speicherbardynamisch<_gravitation<_tg> >(&datei,sdworld,gravitation);
                                                                  gravitation->laden(gravitationnit->objekt(),sdgravitation);
                                                                 }while(gravitationnodes.naechstes(gravitationnit));
                                                                 
                                                                 cameranodes.aushaengen();
                                                                 worldnit->objekt()->holenuebertyp(worldtype+"::"+cameratype,cameranodes);
                                                                 if(cameranodes.anfang(cameranit))do{
                                                                  camera=new _kamera<_tg>(welt);
                                                                  sdcamera=new _speicherbardynamisch<_kamera<_tg> >(&datei,sdworld,camera);
                                                                  camera->laden(cameranit->objekt(),sdcamera);
                                                                 }while(cameranodes.naechstes(cameranit));
                                                                 
                                                                 zonenodes.aushaengen();
                                                                 worldnit->objekt()->holenuebertyp(worldtype+"::"+zonetype,zonenodes);
                                                                 if(zonenodes.anfang(zonenit))do{
                                                                  zone=new _partition::_zone(welt);
                                                                  sdzone=new _speicherbardynamisch<_partition::_zone >(&datei,sdworld,zone);
                                                                  zone->laden(zonenit->objekt(),sdzone);
                                                                  
                                                                  sectornodes.aushaengen();
                                                                  zonenit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+sectortype,sectornodes);
                                                                  if(sectornodes.anfang(sectornit))do{
                                                                   sektor=new _partition::_sektor(zone);
                                                                   sdsector=new _speicherbardynamisch<_partition::_sektor >(&datei,sdzone,sektor);
                                                                   sektor->laden(sectornit->objekt(),sdsector);
                                                                   
                                                                   lightnodes.aushaengen();
                                                                   sectornit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+sectortype+"::"+lighttype,lightnodes);
                                                                   if(lightnodes.anfang(lightnit))do{
                                                                    hvo3.setzen(1,0,0);
                                                                    light=new _licht<_tg,_to>(sektor,nullvector,hvo3,10);
                                                                    sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdsector,light);
                                                                    light->laden(lightnit->objekt(),sdlight);
                                                                   }while(lightnodes.naechstes(lightnit));
                                                                   
                                                                   ppolygonnodes.aushaengen();
                                                                   sectornit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+sectortype+"::"+ppolygontype,ppolygonnodes);
                                                                   if(ppolygonnodes.anfang(ppolygonnit))do{
                                                                    ppolygon=new _partition::_polygon((::_polygon*)0);
                                                                    ppolygon->einfuegeninsektor(sektor);
                                                                    sdppolygon=new _speicherbardynamisch<_partition::_polygon >(&datei,sdsector,ppolygon);
                                                                    ppolygon->laden(ppolygonnit->objekt(),sdppolygon);
                                                                    
                                                                    pvertexnodes.aushaengen();
                                                                    ppolygonnit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+sectortype+"::"+ppolygontype+"::"+pvertextype,pvertexnodes);
                                                                    if(pvertexnodes.anfang(pvertexnit))do{
                                                                     pvertex=new _partition::_vertex(ppolygon,nullvector);
                                                                     sdpvertex=new _speicherbardynamisch<_partition::_vertex >(&datei,sdppolygon,pvertex);
                                                                     pvertex->laden(pvertexnit->objekt(),sdpvertex);
                                                                    }while(pvertexnodes.naechstes(pvertexnit));
                                                                   }while(ppolygonnodes.naechstes(ppolygonnit));
                                                                  }while(sectornodes.naechstes(sectornit));
                                                                  
                                                                  planenodes.aushaengen();
                                                                  zonenit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+planetype,planenodes);
                                                                  if(planenodes.anfang(planenit))do{
                                                                   ebene=new _partition::_ebene(zone);
                                                                   sdplane=new _speicherbardynamisch<_partition::_ebene >(&datei,sdzone,ebene);
                                                                   ebene->laden(planenit->objekt(),sdplane);
                                                                  }while(planenodes.naechstes(planenit));

                                                                 }while(zonenodes.naechstes(zonenit));
                                                                 lw->einhaengen(welt);
                                                                }while(worldnodes.naechstes(worldnit));
                                                                //-------------- assoziation
                                                                //t1=tt.system();
                                                                L->schreiben("Dateiobjektsturktur wird assoziiert.");
                                                                datei.assoziieren();
                                                                //t2=tt.system();
                                                                //-------------- statistik
                                                                //L->schreiben("------------------------- Laden einer Szene ------------------");
                                                                //L->schreiben("Zeitdauer des Ladens      [ms] : ",(int)(t1-t0));
                                                                //L->schreiben("Zeitdauer der Assoziation [ms] : ",(int)(t2-t1));
                                                                //-------------- aktualisieren
                                                                if(lw->anfang(lwit))do{
                                                                 if(lwit->objekt()->anfang(netz))do{
                                                                  netz->aktualisieren();
                                                                 }while(lwit->objekt()->naechstes(netz));
                                                                /* if(lwit->objekt()->anfang(zone))do{
                                                                  if(zone->anfang(sektor))do{ 
                                                                   sektor->aktualisieren();
                                                                  }while(zone->naechstes(sektor));
                                                                 }while(lwit->objekt()->naechstes(zone));*/
                                                                }while(lw->naechstes(lwit));
                                                                //-------------- testspeichern
                                                                //fn="weltdatenuebersetzt_test.txt";  
                                                                //datei.dateiname(fn);
                                                                //datei.speichern();
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T 
//******************************************************************************************************************************************************************************************************
_welt::_welt(){
                                                                ptimer=0;
                                                                ptm=0;
                                                                pdbfont=new _weltdebugzeichensatz(this);
                                                                pbrechzahl=1;
                                                                pdispersionsskalierung=0;
                                                                peigenetransformation=true;
                                                                pzyklus=0;
                                                                pzykluszeit=17;
                                                                paltezeit=0;
                                                                pmarkierungkollision=10;
                                                                plichtambient.setzen(0,0,0.6);
                                                                pdbmo=0;
                                                                pdbgra=0;
                                                                pdbtas=0;
                                                                pdbsystem=0;
                                                                pdbintersektion=false;
                                                                pdbsektor=false;
                                                                pdbbsp=false;
                                                                pdbportal=false;
                                                                pdbsichtbarkeit=false;
                                                                //schattenbild=0;

                                                                //------------- ode --------------
                                                                //odewelt=dWorldCreate();
                                                                //odespace=dSimpleSpaceCreate(0);
                                                                
};
_welt::~_welt(){
                                                                unuebersetzen();
                                                                //if(pdbmo) delete pdbmo;
                                                                //if(pdbgra) delete pdbgra;
                                                                delete pdbfont;
                                                                pdbfont=0;
                                                                _listebasis<_partikel>::loeschen();
                                                                //------------- ode --------------
                                                                //dWorldDestroy(odewelt);
};


_vektor3<_to>&_welt::lichtambient(){
                                                                return(plichtambient);
};
void _welt::eigenetransformation(const bool b){
                                                                peigenetransformation=b;
};

void _welt::erzeugentexturliste(_liste<_textur<_tb> >*lt){
																_listenknoten<_netz>*nit;
																_listenknoten<_polygon>*pit;
																_netz*n;
																_polygon*p;
																_partikelquelle*q;
																_partition::_zone*z;
																_partition::_sektor*s;
																_listenknoten<_textur<_tb> >*tit;
																//--------------------------------
																iterieren(n,iterierenliste(n,p,
																 if(p->texturfront()) lt->einhaengenunredundant(p->texturfront());
																 if(p->texturrueck()) lt->einhaengenunredundant(p->texturrueck());
																));
																iterieren(q,
																 iterierenliste(q->listetextur(),tit,lt->einhaengenunredundant(tit->objekt()));
																 iterierenliste(q->listenetz(),nit,iterierenliste(nit->objekt(),p,
																  if(p->texturfront()) lt->einhaengenunredundant(p->texturfront());
																  if(p->texturrueck()) lt->einhaengenunredundant(p->texturrueck());
																 ));
																);
																iterieren(z,iterierenliste(z,s,
																 iterierenliste(s->internepolygonedynamisch(),pit,
																  p=pit->objekt();
																  if(p->texturfront()) lt->einhaengenunredundant(p->texturfront());
																  if(p->texturrueck()) lt->einhaengenunredundant(p->texturrueck());
																 );
																 iterierenliste(s->internenetze(),nit,iterierenliste(nit->objekt(),p,
																  if(p->texturfront()) lt->einhaengenunredundant(p->texturfront());
																  if(p->texturrueck()) lt->einhaengenunredundant(p->texturrueck());
																 ));
																));
																if(ptm) iterierenliste(ptm,p,
																 if(p->texturfront()) lt->einhaengenunredundant(p->texturfront());
																 if(p->texturrueck()) lt->einhaengenunredundant(p->texturrueck());
																);
};																
void _welt::erzeugentextur(){
																//zum speichern:
																//legt eine lokal textur liste in der basis der welt an
																//um diese zu speichern
																_listebasis<_textur<_tb > >::loeschen();
																_listenknoten<_textur<_tb> >*tit;
																_listenknoten<_netz>*nit;
																_listenknoten<_polygon>*pit;
																_netz*n;
																_polygon*p;
																_partikelquelle*q;
																_partition::_zone*z;
																_partition::_sektor*s;
																//zunächst alles abiteriern, das texturen benutzt
																//und alle benützten texturzeiger in eine liste laden
																ptexturliste.aushaengen();
																ptexturlisteneu.aushaengen();																
																erzeugentexturliste(&ptexturliste);
																//jetzt diese liste abiterieren, und neue texturobjekte in der welt anlegen
																_listebasis<_textur<_tb> >::loeschen();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! achtung unbedingt behandeln !!!!!!!!!!!!!!!!!
																//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! texturzeiger die auf die welt liste zeigen, müssen behandelt werden
																iterierenliste((&ptexturliste),tit,
																 _textur<_tb>*tn=new _textur<_tb>(tit->objekt());
																 tn->einhaengen(this);
																 ptexturlisteneu.einhaengen(tn);
																);
																//texturzeiger umbiegen
																iterieren(n,iterierenliste(n,p,
																 if(p->texturfront()) p->texturfront(umbiegentexturzeiger(p->texturfront(),&ptexturliste,&ptexturlisteneu));
																 if(p->texturrueck()) p->texturrueck(umbiegentexturzeiger(p->texturrueck(),&ptexturliste,&ptexturlisteneu));
																));
																iterieren(q,
																 iterierenliste(q->listetextur(),tit,tit->objekt(umbiegentexturzeiger(tit->objekt(),&ptexturliste,&ptexturlisteneu)));
																 iterierenliste(q->listenetz(),nit,iterierenliste(nit->objekt(),p,
																  if(p->texturfront()) p->texturfront(umbiegentexturzeiger(p->texturfront(),&ptexturliste,&ptexturlisteneu));
																  if(p->texturrueck()) p->texturrueck(umbiegentexturzeiger(p->texturrueck(),&ptexturliste,&ptexturlisteneu));
																 ));
																);
																iterieren(z,iterierenliste(z,s,
																 iterierenliste(s->internepolygonedynamisch(),pit,
																  p=pit->objekt();
																  if(p->texturfront()) p->texturfront(umbiegentexturzeiger(p->texturfront(),&ptexturliste,&ptexturlisteneu));
																  if(p->texturrueck()) p->texturrueck(umbiegentexturzeiger(p->texturrueck(),&ptexturliste,&ptexturlisteneu));
																 );
																 iterierenliste(s->internenetze(),nit,iterierenliste(nit->objekt(),p,
																  if(p->texturfront()) p->texturfront(umbiegentexturzeiger(p->texturfront(),&ptexturliste,&ptexturlisteneu));
																  if(p->texturrueck()) p->texturrueck(umbiegentexturzeiger(p->texturrueck(),&ptexturliste,&ptexturlisteneu));
																 ));
																));
																if(ptm) iterierenliste(ptm,p,
																 if(p->texturfront()) p->texturfront(umbiegentexturzeiger(p->texturfront(),&ptexturliste,&ptexturlisteneu));
																 if(p->texturrueck()) p->texturrueck(umbiegentexturzeiger(p->texturrueck(),&ptexturliste,&ptexturlisteneu));
																);
																
};
void _welt::loeschentextur(){
																//alle textur zeiger in welt, die lokal zeigen
																//werden nun wieder auf die texturverwaltung zurpckgelegt
																_listebasis<_textur<_tb > >::loeschen();
																_listenknoten<_textur<_tb> >*tit;
																_listenknoten<_netz>*nit;
																_listenknoten<_polygon>*pit;
																_netz*n;
																_polygon*p;
																_partikelquelle*q;
																_partition::_zone*z;
																_partition::_sektor*s;																
																
																iterieren(n,iterierenliste(n,p,
																 if(p->texturfront()) p->texturfront(umbiegentexturzeiger(p->texturfront(),&ptexturlisteneu,&ptexturliste));
																 if(p->texturrueck()) p->texturrueck(umbiegentexturzeiger(p->texturrueck(),&ptexturlisteneu,&ptexturliste));
																));
																iterieren(q,
																 iterierenliste(q->listetextur(),tit,tit->objekt(umbiegentexturzeiger(tit->objekt(),&ptexturlisteneu,&ptexturliste)));
																 iterierenliste(q->listenetz(),nit,iterierenliste(nit->objekt(),p,
																  if(p->texturfront()) p->texturfront(umbiegentexturzeiger(p->texturfront(),&ptexturlisteneu,&ptexturliste));
																  if(p->texturrueck()) p->texturrueck(umbiegentexturzeiger(p->texturrueck(),&ptexturlisteneu,&ptexturliste));
																 ));
																);
																iterieren(z,iterierenliste(z,s,
																 iterierenliste(s->internepolygonedynamisch(),pit,
																  p=pit->objekt();
																  if(p->texturfront()) p->texturfront(umbiegentexturzeiger(p->texturfront(),&ptexturlisteneu,&ptexturliste));
																  if(p->texturrueck()) p->texturrueck(umbiegentexturzeiger(p->texturrueck(),&ptexturlisteneu,&ptexturliste));
																 );
																 iterierenliste(s->internenetze(),nit,iterierenliste(nit->objekt(),p,
																  if(p->texturfront()) p->texturfront(umbiegentexturzeiger(p->texturfront(),&ptexturlisteneu,&ptexturliste));
																  if(p->texturrueck()) p->texturrueck(umbiegentexturzeiger(p->texturrueck(),&ptexturlisteneu,&ptexturliste));
																 ));
																));
																if(ptm) iterierenliste(ptm,p,
																 if(p->texturfront()) p->texturfront(umbiegentexturzeiger(p->texturfront(),&ptexturlisteneu,&ptexturliste));
																 if(p->texturrueck()) p->texturrueck(umbiegentexturzeiger(p->texturrueck(),&ptexturlisteneu,&ptexturliste));
																);
																
																_listebasis<_textur<_tb> >::loeschen();
																ptexturliste.aushaengen();
																ptexturlisteneu.aushaengen();
};
_textur<_tb>* _welt::umbiegentexturzeiger(_textur<_tb>*t,_liste<_textur<_tb> >*lt,_liste<_textur<_tb> >*ltn){
																_listenknoten<_textur<_tb> >*tit;
																if(lt->suchen(t,tit)){
																 return(ltn->index(tit->indexknoten())->objekt());
																};
																return(t);//konnte nicht umgebogen werden
};


void _welt::globalisierentextur(_texturverwaltung<_tb>*tv){
																//nach dem laden besitzt die welt eine lokale texturliste (basis)
																//alle textur zeiger der welt zeigen darauf
																//alle textur zeiger der welt müssen nun umgeleitet werden 
																//auf ggf. neu zu erzeugende texturobjekte der texturverwaltung
																//anschließend wird die lokale texturliste gelöscht
																ptexturlisteneu.aushaengen();
																ptexturliste.aushaengen();
																erzeugentexturliste(&ptexturlisteneu);
																_listenknoten<_textur<_tb> >*tit;
																iterierenliste((&ptexturlisteneu),tit,ptexturliste.einhaengen(tv->textur(tit->objekt())));
																loeschentextur();
};


_weltdebugzeichensatz*_welt::debugzeichensatz(){
                                                                return(pdbfont);
};
 
void _welt::transformierenglobal(_grafik*grafik,_kamera<_tg>*cam){
                                                                
                                                                
                                                            //    MUSS NOCH EINGEKASPELT WERDEN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                 
                                                                GLfloat m[4][4];
                                                                _vektor3<_tg> v=cam->vektor();
                                                                _vektor3<_tg> a=cam->ebenenormalisiert(0);
                                                                _vektor3<_tg> b=cam->ebenenormalisiert(1);
                                                                                                                                                                                                
                                                                v.normalisieren();
                                                                a.normalisieren();
                                                                b.normalisieren();
                                                                
                                                                m[0][0]=a[0];
                                                                m[1][0]=a[1];
                                                                m[2][0]=a[2];
                                                                m[3][0]=0;
                                                                m[0][1]=b[0];
                                                                m[1][1]=b[1];
                                                                m[2][1]=b[2];
                                                                m[3][1]=0;
                                                                m[0][2]=-v[0];
                                                                m[1][2]=-v[1];
                                                                m[2][2]=-v[2];
                                                                m[3][2]=0;
                                                                m[0][3]=0;
                                                                m[1][3]=0;
                                                                m[2][3]=0;
                                                                m[3][3]=1;
                                                                if(cam->orthonormal()){
                                                                 glMatrixMode(GL_MODELVIEW);  
                                                                 glLoadIdentity();  
                                                                 glLoadMatrixf((GLfloat*)m);
                                                                 glTranslatef((_to)-cam->holen(0),(_to)-cam->holen(1),(_to)-cam->holen(2)); 
                                                                 glMatrixMode(GL_PROJECTION);  
                                                                 glLoadIdentity();  
                                                                
	                                                             glOrtho(0,grafik->groessex(), 0,grafik->groessey(), -2500, 2500);
	                                                             glTranslatef(grafik->groessex()/2.0f,grafik->groessey()/2.0f,0);
	                                                             _tg sx=(grafik->groessex()/2.0f)/cam->groesse(0);
	                                                             _tg sy=(grafik->groessey()/2.0f)/cam->groesse(1);
	                                                             _tg s=maximum<_tg>(sx,sy);
	                                                             glScalef(s,s,1);
	                                                             glMatrixMode(GL_MODELVIEW); 
                                                                 //gluPerspective(65.0f,(GLfloat)800/(GLfloat)600,0.1f,1000.0f);  
                                                                }else{
                                                                // L->schreiben("kamera trans = ",*(cam));
                                                                 glMatrixMode(GL_PROJECTION);  
                                                                 glLoadIdentity();  
                                                                 gluPerspective(65.0f,(GLfloat)800/(GLfloat)600,0.1f,2500.0f);  
                                                                 glMatrixMode(GL_MODELVIEW);  
                                                                 glLoadIdentity();  
                                                                 glLoadMatrixf((GLfloat*)m);
                                                                 glTranslatef((_to)-cam->holen(0),(_to)-cam->holen(1),(_to)-cam->holen(2)); 
                                                                };
                                                                
                                                               
};
/*

void _welt::transformierenglobal(_kamera<_tg>*cam){
                                                                glMatrixMode(GL_PROJECTION); 
                                                                glLoadIdentity(); 
                                                                gluPerspective(65.0f,(GLfloat)800/(GLfloat)600,0.1f,1000.0f); 
                                                                glMatrixMode(GL_MODELVIEW); 
                                                                glLoadIdentity(); 
                                                                glRotatef(cam->yaw(),1,0,0);
                                                                glRotatef(cam->rot(),0,1,0);
                                                                glScalef(1,1,-1);                                                              
                                                                glTranslatef(cam->holen(0),cam->holen(1),cam->holen(2));  
};
*/

void _welt::transformierensektor(_grafik*gra,_kamera<_tg>*cam,_partition::_sektor*sektor){
                                                                _weltdebug*dit;
                                                                //-------------------------
                                                                if(peigenetransformation){
                                                                 if(sektor) sektor->transformieren(gra,cam);
                                                                 if(anfang(dit))do{
                                                                  dit->transformieren(gra,cam);
                                                                 }while(naechstes(dit));
                                                                }else{
                                                                 transformierenglobal(gra,cam);
                                                                };
                                                                
};

void _welt::transformieren(_grafik*gra,_kamera<_tg>*cam,bool backfaceculled){
                                                                _netz*mit;
                                                                _weltdebug*dit;
                                                                //-------------------------
                                                                if(peigenetransformation){
                                                                 if(anfang(mit))do{
                                                                  mit->markierungvertex(0);
                                                                  mit->transformieren(gra,cam,backfaceculled);
                                                                 }while(naechstes(mit));
                                                                 if(anfang(dit))do{
                                                                  dit->transformieren(gra,cam);
                                                                 }while(naechstes(dit));
                                                                }else{
                                                                 transformierenglobal(gra,cam);
                                                                };
};

void _welt::transformieren(_grafik*gra,_kamera<_tg>*cam,_tg xy,_tg wert){
                                                                _netz*mit;
                                                                _weltdebug*dit;
                                                                //-------------------------
                                                                if(peigenetransformation){
                                                                 if(anfang(mit))do{
                                                                  mit->markierungvertex(0);
                                                                  mit->transformieren(gra,cam,xy,wert);
                                                                 }while(naechstes(mit));
                                                                 if(anfang(dit))do{
                                                                  dit->transformieren(gra,cam);
                                                                 }while(naechstes(dit));
                                                                }else{
                                                                 transformierenglobal(gra,cam);
                                                                };
};                                                                

void _welt::transformieren(_grafik*gra,_kamera<_tg>*cam,_tg x,_tg y,_tg z){
                                                                _netz*mit;
                                                                _weltdebug*dit;
                                                                //-------------------------
                                                                if(peigenetransformation){
                                                                 if(anfang(mit))do{
                                                                  mit->markierungvertex(0);
                                                                  mit->transformieren(gra,cam,x,y,z);
                                                                 }while(naechstes(mit));
                                                                 if(anfang(dit))do{
                                                                  dit->transformieren(gra,cam);
                                                                 }while(naechstes(dit));
                                                                }else{
                                                                 transformierenglobal(gra,cam);
                                                                };
};                                                                

void _welt::zeichnensektor(_grafik*gra,_kamera<_tg>*cam,_partition::_sektor*sektor){
                                                                _weltdebug*dit;
                                                                //-------------------------
                                                                if(sektor) sektor->zeichnen(gra,cam);
                                                                if(anfang(dit))do{
                                                                 dit->zeichnen(gra);
                                                                }while(naechstes(dit));
};

void _welt::zeichnensprite(_grafik*gra,_kamera<_tg>*kam){
                                                                _sprite*it;
                                                                //-------------------------
                                                                if(anfang(it))do{
                                                                 it->zeichnen(gra,kam);
                                                                }while(naechstes(it));
};

void _welt::zeichnenfigur(_grafik*gra,_kamera<_tg>*cam){
                                                                _figur*it;
                                                                //-------------------------
                                                                if(anfang(it))do{
                                                                 it->zeichnen(gra,cam);
                                                                }while(naechstes(it));
};
void _welt::zeichnenfeld(_feld<_tg>*feld,_grafik*grafik,bool anwahl,const _zeichenkette<char>&text){
                                                                _weltdebugkugel*wk=new _weltdebugkugel(this,_vektor3<_tg>(0,0,0),1,_vektor4<_to>(1,0,0,1));
                                                                _weltdebugpfeil*wp=new _weltdebugpfeil(this,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),1,0.7,_vektor4<_to>(1,0,0,1));
                                                                _weltdebugtext *wt=new _weltdebugtext (this,text,_vektor3<_tg>(0,0,0),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,0,0.5),_vektor4<_to>(1,0,0,1));
                                                                _listenknoten<_vektor3<_tg> >*oit;
                                                                _listenknoten<_vektor3<_tg> >*ait;
                                                                //_listenknoten<_tg>*sit;
                                                                //_listenknoten<_tg>*rit;
                                                                
                                                                
                                                                _tg z=1;
                                                                if(anwahl) z=2;
																_tg i;
                                                                for(i=0;i<z;i+=1){
                                                                 if(i==0){
                                                                  wk->farbe(_vektor4<_to>(0,1,0,1));
                                                                  wp->farbe(_vektor4<_to>(0,1,0,1));
                                                                  wt->farbe(_vektor4<_to>(0,1,0,1));
                                                                 }else{
                                                                  wk->farbe(_vektor4<_to>(1,0,0,1));
                                                                  wp->farbe(_vektor4<_to>(1,0,0,1));
                                                                  wt->farbe(_vektor4<_to>(1,0,0,1));
                                                                 };
                                                                
                                                                 wp->ort(0,_vektor3<_tg>(0,0,0));       
                                                                 wp->ort(1,feld->homogen()*100);
                                                                 wp->zeichnen(grafik);                                                             
                                                                 wk->ort(feld->ort());
                                                                 wk->radius(0.4+(i*0.1));
                                                                 wk->zeichnen(grafik);    
                                                                 wt->ort(feld->ort()+_vektor3<_tg>(-1,i*0.1,-1));
                                                                 wt->zeichnen(grafik);
                                                                 
                                                                
                                                                 if(feld->divergenzort()->anfang(oit))do{
                                                                  wk->ort(*oit->objekt());
                                                                  wk->radius(0.1+(i*0.1));
                                                                  wk->zeichnen(grafik);                                                                 
                                                                 }while(feld->divergenzort()->naechstes(oit));

                                                                 feld->rotationachse()->anfang(ait);
                                                                 if(feld->rotationort()->anfang(oit))do{
                                                                  wk->ort(*oit->objekt());
                                                                  wk->radius(0.1+(i*0.1));
                                                                  wk->zeichnen(grafik);      
                                                                  wp->ort(0,*oit->objekt());       
                                                                  wp->ort(1,*oit->objekt()+*ait->objekt());
                                                                  wp->zeichnen(grafik);
                                                                  feld->rotationachse()->naechstes(ait);                                                    
                                                                 }while(feld->rotationort()->naechstes(oit));
                                                                };

                                                                if(feld->blaseort()->anfang(oit))do{
                                                                 wk->ort(*oit->objekt());
                                                                 wk->radius(0.1+(i*0.1));
                                                                 wk->zeichnen(grafik);                                                                 
                                                                }while(feld->blaseort()->naechstes(oit));

                                                                
                                                                delete wp;
                                                                delete wk;
                                                                delete wt;
};
void _welt::zeichnenfeld(_feld<_tg>*git,_grafik*grafik,const _tg divi){
                                                                _weltdebugpfeil*wp=new _weltdebugpfeil(this,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),0.1,0.05,_vektor4<_to>(0.1,0.01,0.8,1));
                                                                wp->farbe(_vektor4<_to>(0.1,0.01,0.8,1));
                                                                _tg x,y,z;
                                                                _tg ss=10;
                                                                _tg dx,dy,dz;
                                                                _vektor3<_tg> xx,yy;
                                                                _tg x0,x1,y0,y1,z0,z1;
                                                                //-------------------------
                                                                git->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                                               
                                                                dx=((x1-x0)+ss*2)/divi;
                                                                dy=((y1-y0)+ss*2)/divi;
                                                                dz=((z1-z0)+ss*2)/divi;
                                                                _tg dm=1;
                                                                if(dx<dm) dx=dm;
                                                                if(dy<dm) dy=dm;
                                                                if(dz<dm) dz=dm;
                                                                for(x=x0-ss;x<x1+ss;x+=dx)
                                                                for(y=y0-ss;y<y1+ss;y+=dy)
                                                                for(z=z0-ss;z<z1+ss;z+=dz){
                                                                 xx.setzen(x,y,z);
                                                                 wp->ort(0,xx);
                                                                 git->vektor(xx,yy);
                                                                 yy*=100;
                                                                 wp->ort(1,xx+yy);
                                                                 wp->zeichnen(grafik);
                                                                };
                                                                delete wp;
};                                   


/*
#include "GL/glut.h"
void DrawScene(float angle)
{
	//Display lists for objects
	static GLuint spheresList=0, torusList=0, baseList=0;

	//Create spheres list if necessary
	if(!spheresList)
	{
		spheresList=glGenLists(1);
		glNewList(spheresList, GL_COMPILE);
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glPushMatrix();
			glTranslatef(0.45f, 1.0f, 0.45f);
			glutSolidSphere(0.2, 24, 24);
			glTranslatef(-0.9f, 0.0f, 0.0f);
			glutSolidSphere(0.2, 24, 24);
			glTranslatef(0.0f, 0.0f,-0.9f);
			glutSolidSphere(0.2, 24, 24);
			glTranslatef(0.9f, 0.0f, 0.0f);
			glutSolidSphere(0.2, 24, 24);
			glPopMatrix();
		}
		glEndList();
	}
	//Create torus if necessary
	if(!torusList)
	{
		torusList=glGenLists(1);
		glNewList(torusList, GL_COMPILE);
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glPushMatrix();
			glTranslatef(0.0f, 0.5f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glutSolidTorus(0.2, 0.5, 24, 48);
			glPopMatrix();
		}
		glEndList();
	}
	//Create base if necessary
	if(!baseList)
	{
		baseList=glGenLists(1);
		glNewList(baseList, GL_COMPILE);
		{
			glColor3f(0.0f, 0.0f, 1.0f);
			glPushMatrix();
			glScalef(1.0f, 0.05f, 1.0f);
			glutSolidCube(3.0f);
			glPopMatrix();
		}
		glEndList();
	}


	//Draw objects
	glCallList(baseList);
	glCallList(torusList);
	
	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glCallList(spheresList);
	glPopMatrix();



};
*/

void _welt::zeichnen(_grafik*gra,_kamera<_tg>*kam){
                                                                _netz*nit;
                                                                if(anfang(nit))do{
                                                                 nit->zeichnen(gra);
                                                                }while(naechstes(nit));
/*
                                                                _netz*mit;
                                                                //_partition::_zone*zit;
                                                                //_partition::_sektor*sit;
                                                                //_listenknoten<_polygon>*lnpit;
                                                                _polygon*pit;
                                                                _kugel*kit;
                                                                _weltdebug*dit;
                                                                _licht<_tg,_to>*lit;
                                                                _vektor4<_to> fh(0,0,0,0.5);
                                                                unsigned int is;
                                                                GLfloat lp[4];
                                                                //GLfloat lc[4];
                                                                //GLfloat lv[4];
                                                                //_vertex*vit0; 
                                                                //_vertex*vit1; 
                                                                //_vertex*vit2; 
                                                                //_vertex*vit3; 
                                                                //_vertex*vn; 
                                                                //_verbindervertexpolygon*pvcp; 
                                                                //_verbindervertexpolygon*vcp0; 
                                                                //_verbindervertexpolygon*vcp1; 
                                                                unsigned int li=0,mi=0;
                                                               // VECTOR3D cameraPosition(-2.5f, 3.5f,-2.5f);
                                                               // VECTOR3D lightPosition(sin(pzyklus*_ph*0.3)*50.0f, 40.5f,cos(pzyklus*_ph*0.3)*50.0f);     
                                                                unsigned int shadowmapsize=2048;     
                                                                float angle=pzyklus;                                                      
                                                                //-------------------------
                                                                glClearStencil(0);
                                                           
                                                                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
                                                                
                                                                //--------------------------------------- lichtquellen laden -----------------------------------
                                                                is=0;
                                                                if(anfang(lit))do{
                                                                 lit->binden(gra,is);
                                                                 is++;
                                                                }while(naechstes(lit));
                                                                //----------------------------------- zfail - SCHATTENVOLUMEN -------------------------------------------------------
                                                                //----------------------------------- 1. pass : szene normal zeichnen ohne licht -------------------------------------
                                                                glDisable(GL_STENCIL_TEST);
                                                                glDisable(GL_LIGHTING);
                                                                glEnable(GL_DEPTH_TEST);
                                                                glDepthFunc(GL_LEQUAL);
                                                                is=0;
                                                                if(anfang(mit))do{
                                                                 mit->anfangschatten();
                                                                 if(mit->anfang(pit))do{
                                                                  if((pit->spiegelnd()==false)&&(pit->zeichnenflaeche()==true)) {
                                                                    pit->zeichnen(gra);
                                                                  };
                                                                  if(pit->dynamischschattierend()){
                                                                   pit->anfangschatten();
                                                                  };
                                                                 }while(mit->naechstes(pit));
                                                                }while(naechstes(mit));
                                                                if(anfang(kit))do{
                                                                 kit->zeichnen(gra);
                                                                 kit->anfangschatten();
                                                                }while(naechstes(kit));
                                                                glDisable(GL_LIGHTING);
                                                                //----------------------------------- 2.pass stencil buffer markieren -----------------------------------------------
                                                                is=0;
                                                                if(anfang(lit))do{ 
                                                               // lit=lit->naechstes();
                                                                 //glClearStencil(0);
                                                                 //GL_LIGHT0 laden mit lit
                                                                 //...
                                                                 glClear(GL_STENCIL_BUFFER_BIT);
                                                                 glDepthFunc(GL_LESS);
                                                                 glEnable(GL_POLYGON_OFFSET_FILL);
                                                                 glPolygonOffset(0.1,10);	
                                                                 //glDisable(GL_DEPTH_TEST);
                                                                 glColorMask(0,0,0,0);
                                                                 glDepthMask(0);
                                                                 glEnable(GL_STENCIL_TEST);
                                                                 glEnable(GL_CULL_FACE);
                                                                 glCullFace(GL_FRONT);
                                                                 glShadeModel(GL_FLAT);
                                                                 glStencilFunc(GL_ALWAYS,0,0xff);
                                                                 glStencilMask(~0);
                                                                 glStencilOp(GL_KEEP,GL_INCR,GL_KEEP);
                                                                 //zur kamera backfaced schattenpolygone zeichnen
                                                                 if(anfang(mit))do{
                                                                  if(mit->schatteniterator()){
                                                                   mit->schatteniterator()->zeichnen(gra);
                                                                  };
                                                                  if(mit->anfang(pit))do{
                                                                   if(pit->dynamischschattierend()){
                                                                    pit->schatteniterator()->zeichnen(gra);
                                                                   };
                                                                  }while(mit->naechstes(pit));
                                                                 }while(naechstes(mit));
                                                                 if(anfang(kit))do{
                                                                  kit->zeichnenschatten(gra);
                                                                 }while(naechstes(kit));
                                                                 //zur kamera frontfaced schattenpolygone zeichnen
			                                                     glCullFace(GL_BACK);
                                                      			 glStencilFunc(GL_ALWAYS, 0x0, 0xff);
			                                                     glStencilOp(GL_KEEP,GL_DECR,GL_KEEP);
                                                                 if(anfang(mit))do{
                                                                  if(mit->schatteniterator()){
                                                                   mit->schatteniterator()->zeichnen(gra);
                                                                  };
                                                                  if(mit->anfang(pit))do{
                                                                   if(pit->dynamischschattierend()){
                                                                    pit->schatteniterator()->zeichnen(gra);
                                                                   };
                                                                  }while(mit->naechstes(pit));
                                                                 }while(naechstes(mit));
                                                                 if(anfang(kit))do{
                                                                  kit->zeichnenschatten(gra);
                                                                 }while(naechstes(kit));
                                                                 glDisable(GL_POLYGON_OFFSET_FILL);
                                                                 glShadeModel(GL_SMOOTH);
                                                                 //---------------------------------3. pass : dunkles rechteck zeichnen --------------------------------------------
                                                                 glDepthFunc(GL_EQUAL);
                                                                 glEnable(GL_BLEND);
                                                                 glBlendFunc(GL_ONE,GL_ONE);
                                                                 glEnable(GL_LIGHT0+(GLenum)is);
                                                                 glEnable(GL_LIGHTING);
                                                                 glStencilFunc(GL_EQUAL,0,~0);
                                                                 //szene nochmal zeichnen mit der aktuellen Lichquelle 
                                                                 lp[0]=lit->ort()[0];
                                                                 lp[1]=lit->ort()[1];
                                                                 lp[2]=lit->ort()[2];
                                                                 lp[3]=1;
                                                                 glLightfv(GL_LIGHT0+(GLenum)is,GL_POSITION,lp);
                                                                
                                                                 glEnable(GL_CULL_FACE);
                                                                 glEnable(GL_STENCIL_TEST);
                                                                 glEnable(GL_DEPTH_TEST);
                                                                 glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
                                                                 glColorMask(1,1,1,1);
                                                                 glDepthMask(1);
                                                                 if(anfang(mit))do{
                                                                  if(mit->anfang(pit))do{
                                                                   bool tra=pit->transparent();
                                                                   pit->transparent(true);
                                                                   pit->zeichnen(gra);
                                                                   pit->transparent(tra);
                                                                   if(pit->dynamischschattierend()){
                                                                    pit->naechsterschatten();
                                                                   };
                                                                   
                                                                  }while(mit->naechstes(pit));
                                                                  if(mit->schatteniterator()) mit->naechsterschatten();
                                                                 }while(naechstes(mit));
                                                                 glEnable(GL_BLEND);
                                                                 if(anfang(kit))do{
                                                                  kit->zeichnen(gra);
                                                                  kit->naechsterschatten();
                                                                 }while(naechstes(kit));
                                                                
                                                                 glDepthFunc(GL_LEQUAL);
                                                                 glDisable(GL_LIGHT0+(GLenum)is);
                                                                 glDisable(GL_STENCIL_TEST);                                                                 
			                                                     glDisable(GL_BLEND);
			                                                     is++;
                                                                }while(naechstes(lit));
                                                                 
                                                                 

                                                                
                                                                glDepthFunc(GL_LEQUAL);
                                                                //------------------------------------------------------ sprites und debugs zeichnen --------------------------------------
                                                                glDisable(GL_LIGHTING);
                                                                glEnable(GL_BLEND);
                                                                if(anfang(dit))do{
                                                                 dit->zeichnen(gra);
                                                                }while(naechstes(dit));
                                                                glEnable(GL_LIGHTING);
                                                                glDisable(GL_BLEND);
                                                                zeichnensprite(gra,kam);
                                                                if(anfang(mit))do{
                                                                 if(mit->anfang(pit))do{
                                                                 _polygonschatten*psit;
                                                                  if(pit->anfang(psit))do{
                                                                   //psit->zeichnendebug(gra);
                                                                  }while(pit->naechstes(psit));
                                                                 }while(mit->naechstes(pit));
                                                                 _netzschatten*nsit;
                                                                 if(mit->anfang(nsit))do{
                                                                 // nsit->zeichnendebug(gra);
                                                                 }while(mit->naechstes(nsit));
                                                                }while(naechstes(mit));
                                                                 
                                                                 
                                                                 
                                                                
                                                                
                                                                //---------------------------------------------------------------------------------------------
                                                                
                                                                //--------------------------------------- SCHATTENBILD -------------------------------------
                                                          
                                                                //-------------------------------------------------spiegelnde flächen zeichnen----------------------------------------
                                                                //glClearStencil(0);
                                                                //gra->tiefenbuffertesten(true);
                                                                //gra->stencil(false);                                                                
                                                                if(anfang(mit))do{
                                                                 if(mit->anfang(pit))do{
                                                                  if(pit->spiegelnd()){
                                                                  
                                                                   //1.
                                                                   gra->tiefenbufferschreiben(false);
                                                                   gra->stencil(true);
                                                                   glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
                                                                   glStencilFunc(GL_ALWAYS,1,0xFFFFFFFF);
                                                                   glColorMask(0,0,0,0);
                                                                   pit->zeichnen(gra);
                                                                   //2.
                                                                   glDepthRange(1,1);
                                                                   glDepthFunc(GL_ALWAYS);
                                                                   glStencilFunc(GL_EQUAL,1,0xffffffff);
                                                                   glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
                                                                   pit->zeichnen(gra);
                                                                   //3.
                                                                   glColorMask(1,1,1,1);
                                                                   glDepthRange(0,1);
                                                                   glDepthFunc(GL_LEQUAL); 
                                                                   //4.
                                                                   GLfloat m[4][4];
                                                                   GLdouble clipplane[4];
                                                                   glPushMatrix();
                                                                   pit->normalform((_tg*)&clipplane[0]);
                                                                   glClipPlane(GL_CLIP_PLANE0,&clipplane[0]);
                                                                   glEnable(GL_CLIP_PLANE0);
                                                                   //pit->spiegelmatrix((float*)matrix);
                                                                   _vektor3<_tg>&n=pit->normale();
                                                                   float p[3];
                                                                   float v[3];
                                                                   p[0]=(float)pit->mitte()[0];
                                                                   p[1]=(float)pit->mitte()[1];
                                                                   p[2]=(float)pit->mitte()[2];
                                                                   v[0]=(float)n[0];
                                                                   v[1]=(float)n[1];
                                                                   v[2]=(float)n[2];
                                                                   float dot=v[0]*p[0] + v[1]*p[1] + v[2]*p[2];                                                                
                                                                   m[0][0] =1-2*v[0]*v[0];
                                                                   m[1][0] = -2*v[0]*v[1];
                                                                   m[2][0] = -2*v[0]*v[2];
                                                                   m[3][0] = 2*dot*v[0];
                                                                   m[0][1] = -2*v[1]*v[0];
                                                                   m[1][1] =1-2*v[1]*v[1];
                                                                   m[2][1] = -2*v[1]*v[2];
                                                                   m[3][1] = 2*dot*v[1];
                                                                   m[0][2] = -2*v[2]*v[0];
                                                                   m[1][2] = -2*v[2]*v[1];
                                                                   m[2][2]=1-2*v[2]*v[2];
                                                                   m[3][2]= 2*dot*v[2];
                                                                   m[0][3]=0;
                                                                   m[1][3]=0;
                                                                   m[2][3]=0;
                                                                   m[3][3]=1;
                                                                   glMultMatrixf(&m[0][0]);
                                                                   _netz*miit;
                                                                   _polygon*piit;
                                                                   if(anfang(miit))do{
                                                                    if(miit->anfang(piit))do{
                                                                     if(piit!=pit){
                                                                      if(piit->spiegelnd()==false) piit->zeichnen(gra); else{
                                                                       //andere spiegel mit grau zeichnen
                                                                      };
                                                                     };
                                                                    }while(miit->naechstes(piit));
                                                                   }while(naechstes(miit));
                                                                   if(anfang(dit))do{
                                                                    dit->zeichnen(gra);
                                                                   }while(naechstes(dit));                                                                
                                                                   zeichnensprite(gra,kam);
                                                                   glDisable(GL_CLIP_PLANE0); 
                                                                   glPopMatrix();
                                                                   //5. stencil buffer löschen ?????

                                                                   //6. transparentes polygon drüberzeichnen
                                                                   glEnable(GL_BLEND);
                                                                   //glBlendFunc(GL_ONE,GL_ONE);
                                                                   glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                                                                   gra->tiefenbufferschreiben(true);
                                                                   pit->transparent(true);
                                                                   pit->zeichnen(gra);
                                                                   pit->transparent(false);
                                                                   
                                                                  };
                                                                 }while(mit->naechstes(pit));
                                                                }while(naechstes(mit));
                                                                //------------------------------------------------------------------------------------------------------------------

                                                                //nachbereiten                                                                
                                                                gra->blend(false);
                                                                gra->tiefenbufferschreiben(true);
                                                                gra->tiefenbuffertesten(true);
                                                                gra->maske(false);
                                                                gra->textur(false);
                                                                
                                                               */
};

void _welt::zeichnendebug(_grafik*gra){
                                                                _netz*mit;
                                                                _weltdebug*dit;
                                                                //-------------------------
                                                                if(anfang(mit))do{
                                                                 mit->zeichnendebug(gra);
                                                                }while(naechstes(mit));
                                                                
                                                                gra->textur(false);
                                                                gra->transparenz(true);
                                                                //gra->transparenzadditiv();
                                                                gra->tiefenbufferkondition(false);
                                                                gra->tiefenbufferschreiben(false);
	                                                            gra->ausschussflaeche(false);
	                                                            gra->beleuchtung(false);
	                                                                                                                       
                                                                if(anfang(dit))do{
                                                                 dit->zeichnen(gra);
                                                                }while(naechstes(dit));
};

void _welt::zeichnenlinie(_grafik*gra,bool backfaceculled){
                                                                _netz*mit;
                                                                _weltdebug*dit;
                                                                //-------------------------
                                                                if(anfang(mit))do{
                                                                 mit->zeichnenlinie(gra,backfaceculled);
                                                                }while(naechstes(mit));
                                                                if(anfang(dit))do{
                                                                 dit->zeichnen(gra);
                                                                }while(naechstes(dit));
};

void _welt::animieren(){
                                                                _weltdebug*dit;
                                                                _partikelquelle*pqit;
                                                                _partikel*pait;
                                                                _partition::_zone*zit;
                                                                //-------------------------
                                                                if(ptimer){
                                                                 unsigned int neu=ptimer->system();
                                                                 if(neu>paltezeit) pzykluszeit=neu-paltezeit; //sonst die alte zykluszeit
                                                                 panimationsfaktor=(pzykluszeit)/16.66666f;
                                                                 paltezeit=neu;
                                                                }else{
                                                                 panimationsfaktor=1;
                                                                 pzykluszeit=16.66666f;
                                                                };
                                                                
                                                                if(anfang(zit))do{
                                                                 zit->animieren();
                                                                }while(naechstes(zit));
                                                                if(anfang(pqit))do{
                                                                 pqit->animieren();
                                                                }while(naechstes(pqit));
                                                                _listebasis<_partikelquelle>::loeschenmarkiert();
                                                                if(anfang(pait))do{
                                                                 pait->animieren();
                                                                }while(naechstes(pait));
                                                                _listebasis<_partikel>::loeschenmarkiert();
                                                                if(anfang(dit))do{
                                                                 dit->animieren();
                                                                }while(naechstes(dit));
                                                                
                                                                pzyklus++;
                                                                

};
_tg _welt::animationsfaktor()const{
                                                                return(panimationsfaktor);
};
unsigned int _welt::neuemarkierungkollision(){
                                                                return(pmarkierungkollision++);
};
unsigned int _welt::zyklus()const{
                                                                return(pzyklus);
};
unsigned int _welt::zykluszeit()const{
                                                                return(pzykluszeit);
};
void _welt::initialisierenanimation(){
                                                                if(ptimer)paltezeit=ptimer->system();
};
void _welt::animierenpartikelquelle(){
                                                                _partikelquelle*qit;
                                                                //-------------------------
                                                                if(anfang(qit))do{
                                                                 qit->animieren();
                                                                }while(naechstes(qit));
                                                                _listebasis<_partikelquelle >::loeschenmarkiert();

};

void _welt::animierensprite(){
                                                                _sprite*sit;
                                                                //-------------------------
                                                                if(anfang(sit))do{
                                                                 sit->animieren();
                                                                }while(naechstes(sit));

};

void _welt::animierenfigur(_partition::_zone*z,_tastatur*kb,_maus<_tg>*mo){
                                                                _figur*it;
                                                                //-------------------------
                                                                if(anfang(it))do{
                                                                 it->animieren(z,kb,mo);
                                                                }while(naechstes(it));
                                                                _listebasis<_figur >::loeschenmarkiert();

};
void _welt::aktualisieren(){
																if(ptm) ptm->aktualisieren();
																_netz*n;
																iterieren(n,n->aktualisieren());
};
_vektor3<_tg> _welt::gravitation(const _vektor3<_tg>&x){
                                                                _vektor3<_tg> r;
                                                                _vektor3<_tg> h;
                                                                _gravitation<_tg>*git;
                                                                //--------------------
                                                                r.setzen(0,0,0);
                                                                if(anfang(git))do{
                                                                 git->vektor(x,h);
                                                                 r+=h;
                                                                }while(naechstes(git));
                                                                return(r);
};
void _welt::intersekt(_netz*m,unsigned int op){
                                                                _netz*mit;
                                                                _liste<_netz > mlist;
                                                                _netz*mc;
                                                                _modifikationnetzintersektion mmi;
                                                                //--------------------
                                                                if(anfang(mit))do{
                                                                 //if(m->hatintersektion(mit)){
                                                                  mlist.einhaengen(mit);
                                                                 //}else if((m->innerhalb(mit))||(mit->innerhalb(m))){
                                                                 // mlist.einhaengen(mit);
                                                                 //};
                                                                }while(naechstes(mit));
                                                                if(mlist.anzahl()>0){
                                                                 mc=compileintersection(&mlist);
                                                                 mlist.aushaengen();
                                                                 //mc->invertierenausrichtung();
                                                                 mmi.bearbeiten(m,mc,op);
                                                                 //m->subtraktiv(false);
                                                                 delete mc;
                                                                };
};

void _welt::intersekt(_netz*m){
                                                                intersekt(m,0);
};

void _welt::deintersekt(_netz*m){
                                                                intersekt(m,1);
};

void _welt::vereinigen(_netz*m){
                                                                intersekt(m,2);
};

void _welt::erzeugentexturraum(){
                                                                _netz*m;
                                                                _polygon*p;
                                                                //-----------------------
                                                                if(anfang(m))do{
                                                                 if(m->anfang(p))do{
                                                                  p->erzeugentexturraum();
                                                                 }while(m->naechstes(p));
                                                                }while(naechstes(m));
};

void _welt::loeschentexturraum(){
                                                                _netz*m;
                                                                _polygon*p;
                                                                //-----------------------
                                                                if(anfang(m))do{
                                                                 if(m->anfang(p))do{
                                                                  p->loeschentexturraum();
                                                                 }while(m->naechstes(p));
                                                                }while(naechstes(m));
};

void _welt::erzeugenkante(){
                                                                _netz*m;
                                                                _polygon*p;
                                                                //-----------------------
                                                                if(anfang(m))do{
                                                                 if(m->anfang(p))do{
                                                                  p->erzeugenkante();
                                                                  p->aktualisieren();
                                                                 }while(m->naechstes(p));
                                                                }while(naechstes(m));
};

void _welt::loeschenkante(){
                                                                _netz*m;
                                                                _polygon*p;
                                                                //-----------------------
                                                                if(anfang(m))do{
                                                                 if(m->anfang(p))do{
                                                                  p->loeschenkante();
                                                                  p->aktualisieren();
                                                                 }while(m->naechstes(p));
                                                                }while(naechstes(m));
};
void _welt::anlegenlightmap(_texturverwaltung<_tb>*tv,const _zeichenkette<char>&lightmapname){
                                                                _netz*nit;
                                                                _polygon*p;
                                                                unsigned int index;
                                                                char buf[1024];
                                                                _zeichenkette<char> h;                                                                  
                                                                //---------------------
                                                                index=0;
                                                                if(anfang(nit))do{
                                                                 if(nit->anfang(p))do{
                                                                  //lightmap anlegen wenn das flag verwendentexturdynamisch 
                                                                  //gesetzt ist, vorher ggf vorhandene lightmap löschen
                                                                  //p->loeschenlightmap();
                                                                  if(p->verwendentexturdynamisch()){
                                                                   _itoa(index,buf,10);
                                                                   h=buf;
                                                                   h+=".tga";
                                                                   p->anlegenlightmap(tv,lightmapname+h,p->lightmaptexelgroesse());
                                                                   index++;
                                                                  };
                                                                 }while(nit->naechstes(p));
                                                                }while(naechstes(nit));
};
void _welt::anlegenlightmapzone(_texturverwaltung<_tb>*tv,_zeichenkette<char> name,_tg sk){
                                                                //_polygon*p;
                                                                int i;
                                                                _zeichenkette<char> e;
                                                                _zeichenkette<char> tga=".tga";
                                                                _zeichenkette<char> h;
                                                                char buff[1024];
                                                                _partition::_zone*zit;
                                                                _listenknoten<_polygon >*lnpit;
                                                                _polygon*pit;
                                                                //------------
                                                                i=0;
                                                                
                                                                if(anfang(zit))do{
                                                                 if(zit->anfang(lnpit))do{
                                                                  pit=lnpit->objekt();
                                                                  _itoa(i,buff,16);
                                                                  h=buff;
                                                                  while(h.groesse()<8) h.anhaengenfront("0");
                                                                  e=name;
                                                                  e+=h;
                                                                  e+=tga;                                                                
                                                                  pit->anlegenlightmap(tv,e,sk);
                                                                  i++;
                                                                 }while(zit->naechstes(lnpit)); 
                                                                }while(naechstes(zit));
                                                        
};

void _welt::bestrahlenlightmap(){
                                                                _netz*mit;
                                                                _polygon*pit;
                                                                _bestrahler B;  
                                                                //-----------------------
                                                                if(anfang(mit))do{
                                                                 if(mit->anfang(pit))do{
                                                                  if(pit->texturdynamisch()){
                                                                   B.bestrahlenlightmap(this,pit);
                                                                  };
                                                                 }while(mit->naechstes(pit));
                                                                }while(naechstes(mit));
};

void _welt::bestrahlenlightmapzone(){
                                                                _bestrahler B;  
                                                                //-----------------------
                                                                B.bestrahlenlightmapzone(this);
};

void _welt::uebergebenlightmap(_grafik*gra){
                                                                _netz*mit;
                                                                _polygon*pit;
                                                                //-----------------------
                                                                if(anfang(mit))do{
                                                                 if(mit->anfang(pit))do{
                                                                  if(pit->texturdynamisch()){
                                                                   _listenknoten<_bild<_tb> >*lnlmap;
                                                                   if(pit->texturdynamisch()->lightmap()->anfang(lnlmap)) gra->erzeugenbild(lnlmap->objekt());
                                                                  };
                                                                 }while(mit->naechstes(pit));
                                                                }while(naechstes(mit));
};

void _welt::uebergebenlightmapzone(_grafik*gra){
                                                                _partition::_zone*zit;
                                                                _listenknoten<_polygon >*lnpit;
                                                                _polygon*pit;
                                                                //_bild<_tb>*lmap;
                                                                //----------------
                                                                if(anfang(zit))do{
                                                                 if(zit->anfang(lnpit))do{
                                                                  pit=lnpit->objekt();
                                                                  if(pit->texturdynamisch()){
                                                                   _listenknoten<_bild<_tb> >*lnlmap;
                                                                   if(pit->texturdynamisch()->lightmap()->anfang(lnlmap)) gra->erzeugenbild(lnlmap->objekt());
                                                                   
                                                                  };
                                                                 }while(zit->naechstes(lnpit)); 
                                                                }while(naechstes(zit));
};

//------------------------------------------------------------- PARTITIONIERUNGSSCHNITTSTELLE ----------------------------------------------------------------------------------------------------------

::_liste<_netz > * _welt::uebersetzen(){
                                                                //hauptfunktion zur weltencompilation
                                                                _liste<_netz >*mlist;
                                                                _listenknoten<_netz >*lnmit;
                                                                _netz*mit;
                                                                _liste<_netz> keinbsp;
                                                                int i;
                                                                _partition::_zone*zit;
                                                                _partition::_sektor*sit;
                                                                _partition::_polygon*ppit;
                                                                _listenknoten<_partition::_sektor>*sektor;
                                                                _licht<_tg,_to>*lit;
                                                                _listenknoten<_partition::_sektor>*lnsii;
                                                                _partition::_sektor*sii;
                                                                //-----------------------------------
                                                                //netze die nicht am bsp teilnehmen nun erfasen
                                                                //und isolieren
                                                                if(anfang(mit))do{
                                                                 if(mit->keinbsp()) keinbsp.einhaengen(mit);
                                                                }while(naechstes(mit));
                                                                if(keinbsp.anfang(lnmit))do{
                                                                 lnmit->objekt()->_listenknotenbasis<_netz>::aushaengen();
                                                                }while(keinbsp.naechstes(lnmit));
                                                                
                                                                
                                                                //alle rohnetze in der mlist auffangen
                                                                mlist=new _liste<_netz >();
                                                                for(i=0;i<30;i++) ptime[i]=0;
                                                                if(ptimer) { ptimer->animieren(); ptime[0]=ptimer->system();};
                                                                if(anfang(mit))do{
                                                                 mlist->einhaengen(mit);
                                                                }while(naechstes(mit));
                                                                if(erzeugennetz()){
                                                                 if(mlist->anfang(lnmit))do{
                                                                  lnmit->objekt()->_listenknotenbasis<_netz>::aushaengen();
                                                                 }while(mlist->naechstes(lnmit));
                                                                 //mlist.loeschen();
                                                                 if(ptimer) { ptimer->animieren(); ptime[1]=ptimer->system();};
                                                                 erzeugenzone();
                                                                 L->schreiben("_welt::uebersetzen() : Zonen wurden erzeugt.");
                                                                 if(ptimer) { ptimer->animieren(); ptime[2]=ptimer->system();};
                                                                 erzeugenzonenpartition();
                                                                 L->schreiben("_welt::uebersetzen() : Zonenpartitionen wurden erzeugt.");
                                                                 if(ptimer) { ptimer->animieren(); ptime[3]=ptimer->system();};
                                                                 erzeugenzonensektor();
                                                                 L->schreiben("_welt::uebersetzen() : Sektoren wurden erzeugt.");
                                                                 if(ptimer) { ptimer->animieren(); ptime[4]=ptimer->system();};
                                                                 verbindenzonesektor();
                                                                 L->schreiben("_welt::uebersetzen() : Sektoren wurden verbunden.");
                                                                 if(ptimer) { ptimer->animieren(); ptime[5]=ptimer->system();};
                                                                 
                                                                 //alle netze die nicht am bsp teilnehmen und vorher
                                                                 //isoliert worden sind nun wieder in die weltliste
                                                                 //einhaengen und in die zonen integrieren
                                                                 if(keinbsp.anfang(lnmit))do{
                                                                  lnmit->objekt()->einhaengen(this);
                                                                 
                                                                  if(anfang(zit))do{
                                                                   //********* DEBUG ***********
                                                                   zit->erzeugendebugschirm();
                                                                   //***************************
                                                                   zit->einfuegenintern(lnmit->objekt());
                                                                   //********* DEBUG ***********
                                                                   zit->loeschendebugschirm();
                                                                   //***************************
                                                                  }while(naechstes(zit));
                                                                 }while(keinbsp.naechstes(lnmit));
                                                                 keinbsp.aushaengen();
                                                                 L->schreiben("_welt::uebersetzen() : Netze, die nicht am BSP teilnehmen, in die Zonen bzw. Sektoren eingefügt.");
                                                                 
                                                                 erzeugenzonensichtbarkeit();
                                                                 L->schreiben("_welt::uebersetzen() : Sichtbarkeiten wurden ermittelt.");
                                                                 if(ptimer) { ptimer->animieren(); ptime[6]=ptimer->system();};
                                                                 loeschenzonenichtportalvertex();
                                                                 L->schreiben("_welt::uebersetzen() : Nicht portale Vertex wurden destruiert.");
                                                                 if(ptimer) { ptimer->animieren(); ptime[7]=ptimer->system();};
                                                                 ptm->optimierenpolygonstartvertex();
                                                                 ptm->erzeugenvertexlicht();
                                                               //  ptm->farbeverbinder(_vektor4<_to>(0.51,0.51,1,0.51));
                                                                 einfuegenlichtinsektor();
                                                                 L->schreiben("_welt::uebersetzen() : Lichtquellen wurden in die Sektoren eingefügt.");
                                                                // erzeugenvertexlicht();
                                                                 L->schreiben("_welt::uebersetzen() : Vertexlicht wurde berechnet.");
                                                                 if(ptimer) { ptimer->animieren(); ptime[8]=ptimer->system();};
                                                                 //clearzonepolygon();
                                                                 //mlist.loeschen();
                                                                 
                                                                 //prüfen für welche der eingefügten netze, die nicht am bsp teilgenommen
                                                                 //haben, schattenvolumen generiert werden sollen#
                                                                 _polygon*pit;
                                                                 if(anfang(mit))do{
                                                                  mit->loeschenschatten();
                                                                  if(mit->schattenvolumen()){
                                                                   if(mit->_liste<_partition::_sektor>::anfang(sektor))do{
                                                                    sit=sektor->objekt();
                                                                    if(sit->anfang(lit))do{
                                                                     mit->markierungverbinder(-1);
                                                                     mit->erzeugenschatten(lit,mit->schattenvolumenlaenge());
                                                                    }while(sit->naechstes(lit));
                                                                    //wir brauchen die primäre sichtbarkeit
                                                                    //um schattenvolumen von den lichtern in ihr
                                                                    //anzulegen
                                                                    if(sit->sichtbarkeitsektor()->anfang(lnsii))do{
                                                                     sii=lnsii->objekt();
                                                                     if(sii->anfang(lit))do{
                                                                      mit->markierungverbinder(-1);
                                                                      mit->erzeugenschatten(lit,mit->schattenvolumenlaenge());
                                                                     }while(sii->naechstes(lit));
                                                                    }while(sit->sichtbarkeitsektor()->naechstes(lnsii));
                                                                   }while(mit->_liste<_partition::_sektor>::naechstes(sektor));
                                                                  }else{
                                                                   //prüfen, für welche polygone der eingefügten netze
                                                                   //schattenvolumen angelegt werden müssen
                                                                   if(mit->anfang(pit))do{
                                                                    if(pit->dynamischschattierend()){
                                                                     if(pit->_liste<_partition::_sektor>::anfang(sektor))do{
                                                                      sit=sektor->objekt();
                                                                      if(sit->anfang(lit))do{
                                                                       pit->markierungverbinder(-1);
                                                                       pit->erzeugenschatten(lit,pit->schattenvolumenlaenge());
                                                                      }while(sit->naechstes(lit));
                                                                      if(sit->sichtbarkeitsektor()->anfang(lnsii))do{
                                                                       sii=lnsii->objekt();
                                                                       if(sii->anfang(lit))do{
                                                                        pit->markierungverbinder(-1);
                                                                        pit->erzeugenschatten(lit,pit->schattenvolumenlaenge());
                                                                       }while(sii->naechstes(lit));
                                                                      }while(sit->sichtbarkeitsektor()->naechstes(lnsii));
                                                                     }while(pit->_liste<_partition::_sektor>::naechstes(sektor));
                                                                    };
                                                                   }while(mit->naechstes(pit));
                                                                  };
                                                                 }while(naechstes(mit));
                                                                 //nun werden für alle sektorpolygon ggf. schattenvolumen angelegt
                                                                 if(anfang(zit))do{
                                                                  if(zit->anfang(sit))do{
                                                                   if(sit->anfang(ppit))do{
                                                                    if(ppit->portal()==false){
                                                                     if(ppit->polygon()->dynamischschattierend()){
                                                                      if(sit->anfang(lit))do{
                                                                       ppit->polygon()->erzeugenschatten(lit,ppit->polygon()->schattenvolumenlaenge());
                                                                      }while(sit->naechstes(lit));
                                                                      if(sit->sichtbarkeitsektor2tergrad()->anfang(lnsii))do{
                                                                       if(lnsii->objekt()->anfang(lit))do{
                                                                        ppit->polygon()->erzeugenschatten(lit,ppit->polygon()->schattenvolumenlaenge());
                                                                       }while(lnsii->objekt()->naechstes(lit));
                                                                      }while(sit->sichtbarkeitsektor2tergrad()->naechstes(lnsii));
                                                                     };
                                                                    };
                                                                   }while(sit->naechstes(ppit));
                                                                  }while(zit->naechstes(sit));
                                                                 }while(naechstes(zit));
                                                                 L->schreiben("_welt::uebersetzen() : Schattenvolumen wurden berechnet.");
                                                                 //erzeugenzonensichtbarkeitintern();
                                                                 //L->schreiben("_welt::uebersetzen() : Interne Sichtbarkeiten wurden ermittelt.");
                                                                 
                                                                 
                                                                } else L->schreiben("_welt::uebersetzen() : Das Erzeugen des Zonenmeshes durch Intersektion war erfolglos.");
                                                                L->schreiben("_welt::uebersetzen() : beendet.");
                                                                if(pdbportal){
                                                                 if(anfang(zit))do{
                                                                  if(zit->anfang(sit))do{
                                                                   sit->visualisieren();
                                                                  }while(zit->naechstes(sit));
                                                                 }while(naechstes(zit));
                                                                };
                                                                return(mlist);
};
//*********************** DEBUG *************************

void _welt::uebersetzen0(){
                                                                //hauptfunktion zur weltencompilation
                                                                if(erzeugennetz()){
                                                                };
};

void _welt::uebersetzen1(){
                                                               //hauptfunktion zur weltencompilation
                                                                erzeugenzone();
                                                                erzeugenzonenpartition();
                                                                erzeugenzonensektor();
                                                                verbindenzonesektor();
                                                                erzeugenzonensichtbarkeit();
                                                                loeschenzonenichtportalvertex();
                                                                einfuegenlichtinsektor();
                                                                erzeugenvertexlicht();
                                                               // ptm->farbeverbinder(_vektor4<_to>(1,1,1));
                                                                //clearzonepolygon();
};
void _welt::debuggenintersektion(const bool b){
                                                                pdbintersektion=b;
};
bool _welt::debuggenintersektion()const{
                                                                return(pdbintersektion);
};
void _welt::debuggensektor(const bool b){
                                                                pdbsektor=b;
};
bool _welt::debuggensektor()const{
                                                                return(pdbsektor);
};
void _welt::debuggenbsp(const bool b){
                                                                pdbbsp=b;
};
bool _welt::debuggenbsp()const{ 
                                                                return(pdbbsp);
};
void _welt::debuggenportal(const bool b){
                                                                pdbportal=b;
};
bool _welt::debuggenportal()const{ 
                                                                return(pdbportal);
};
void _welt::debuggensichtbarkeit(const bool b){
                                                                pdbsichtbarkeit=b;
};
bool _welt::debuggensichtbarkeit()const{
                                                                return(pdbsichtbarkeit);
};
void _welt::debugmaus(_maus<_tg>*m){
                                                                pdbmo=m;
};
_maus<_tg>* _welt::debugmaus(){
                                                                return(pdbmo);
};
void _welt::debuggrafik(_grafik*g){
                                                                pdbgra=g;
};
_grafik* _welt::debuggrafik(){
                                                                return(pdbgra);
};
void _welt::debugtastatur(_tastatur*t){
                                                                pdbtas=t;
};
_tastatur* _welt::debugtastatur(){
                                                                return(pdbtas);
};
void _welt::debugsystem(_system*s){
                                                                pdbsystem=s;
};
_system*_welt::debugsystem(){
                                                                return(pdbsystem);
};
//*******************************************************

void _welt::einfuegenpartitionsnetz(){
                                                                if(ptm){
                                                                 ptm->einhaengen(this);
                                                                };
};

void _welt::unuebersetzen(){
                                                                //if(ptm){
                                                                // delete ptm;
                                                                // ptm=0;
                                                                //};
                                                                ptm=0;
                                                                einfuegenlichtaussektor();
                                                                _listebasis<_partition::_zone >::loeschen();
                                                                
                                                                
};

char _welt::erzeugennetz(){
                                                                //funktion vereinigt alle existierenden meshes der welt in ein privates 
                                                                //und temporäres netz ptm, so dass dieses die gesamte welt in sich repräsentiert
                                                                //es kann auch in mehrere zonen aufgeteilt sein. eine zone ist ein zusammenhängender 
                                                                //Weltverbund eines meshes
                                                                _netz*mit;
																::_liste<_netz > mlist;
                                                                //--------------------------------
                                                                if(ptm) delete ptm;
                                                                ptm=0;
                                                                if(anfang(mit))do{
                                                                 mlist.einhaengen(mit);
                                                                }while(naechstes(mit));
                                                                ptm=compileintersection(&mlist);
                                                                if(ptm->anzahlpolygon()==0){
                                                                 delete ptm;
                                                                 ptm=0;
                                                                 return(0);
                                                                }else{
                                                                 //ptm->subtraktiv(true);
                                                                 //ptm->invertierenausrichtung();
                                                                 ptm->optimierenpolygonstartvertex();
                                                                 ptm->einhaengen(this);
                                                                 return(1);
                                                                };
};                                                                
                                                                

_netz* _welt::compileintersection(::_liste<_netz >*mlist){
                                                                
                                                                _vektor3<_tg> o;
                                                                _listenknoten<_netz >*mit;
                                                                _listenknoten<_netz >*mii;
                                                                _netz*mstart;
                                                                _netz*mtemp;
                                                                _modifikationnetzintersektion ism;
                                                                bool valid=true;
                                                                _netz*tm;//dieses netz ist das schnittresultat
                                                                //-----------------------------------------------------------------------

                                                                o.setzen(0,0,0);
                                                                mstart=0;
                                                                
                                                                tm=new _netz();
                                                                tm->subtraktiv(true);
                                                                if(mlist->anzahl()==0) {
                                                                 L->schreiben("Fehler : _welt::kompilierenintersektion() : keine Netze vorhanden");
                                                                 return(tm);
                                                                };
                                                                if(mlist->anzahl()==1) {
                                                                 mlist->anfang(mit);
                                                                 if(mit->objekt()->subtraktiv()){
                                                                  mstart=mit->objekt();
                                                                  mtemp=mstart->duplizieren();
                                                                  tm->vereinigen(mtemp);
                                                                 }else{
                                                                  L->schreiben("Fehler : _welt::kompilierenintersektion() : Es liegt nur ein additives Netz vor");
                                                                  return(tm);
                                                                 };
                                                                }else{
                                                                 if(mlist->anfang(mit))do{
                                                                  if(mit->objekt()->subtraktiv()){
                                                                   //startnetz darf nicht innerhalb eines anderen netzes sein,
                                                                   //untersuchen ob es kontakt hat mit anderen sub-netzen
                                                                   bool startvalid=true;
                                                                   if(mlist->anfang(mii))do{
                                                                    if(mit->objekt()!=mii->objekt()){
                                                                     if(ism.hatintersektion(mit->objekt(),mii->objekt())==false){
                                                                      if(ism.netzinnerhalbnetz(mit->objekt(),mii->objekt())){
                                                                       startvalid=false;
                                                                      };
                                                                     };
                                                                    };
                                                                   }while(mlist->naechstes(mii));
                                                                   if(startvalid){
                                                                    mstart=mit->objekt();
                                                                    mtemp=mstart->duplizieren();
                                                                    tm->vereinigen(mtemp);
                                                                   };
                                                                  };
                                                                 }while((mlist->naechstes(mit))&&(mstart==0));
                                                                };
                                                                //----------------------------------------------------------------------
                                                                if(mstart){
                                                                 //alle netze mit 1 markieren (1 heißt, noch nicht verschnitten
                                                                 if(mlist->anfang(mit))do{
                                                                  if((mit->objekt()==mstart)||(mit->objekt()==tm)){
                                                                   mit->objekt()->markierung(0);
                                                                  }else{
                                                                   mit->objekt()->markierung(1);
                                                                  };
                                                                 }while(mlist->naechstes(mit));
                                                                 //und nun schneiden, alles solange durchgehen, bis in einem durchgang nichts mehr geschnitten wurde
                                                                 bool etwasgeschnitten=true;
                                                                 while(etwasgeschnitten){
                                                                  etwasgeschnitten=false;
                                                                  if(mlist->anfang(mit))do{
                                                                   if(mit->objekt()->markierung()==1){
                                                                    if(mit->objekt()->subtraktiv()){
                                                                     //behandlung für SUB netze, netz darf nicht innerhalb von tm sein ohne schnitt
                                                                     if(ism.hatintersektion(tm,mit->objekt())){
                                                                      if(ism.bearbeiten(tm,mit->objekt(),2)==0) valid=false;                                                                     
																	  mit->objekt()->markierung(0);
                                                                      etwasgeschnitten=true;
                                                                     }else{
                                                                      //sub-netze ausserhalb sind ok, innerhalb von tm nichts machen
                                                                      if(ism.netzinnerhalbnetz(mit->objekt(),tm)==false){
                                                                       if(ism.bearbeiten(tm,mit->objekt(),2)==0) valid=false;
                                                                       mit->objekt()->markierung(0);
                                                                       etwasgeschnitten=true;
                                                                      };
                                                                     };
                                                                    }else{
                                                                     //behandlung für ADD netze, netz darf nicht ausserhalb von tm sein ohne schnitt
                                                                     if(ism.hatintersektion(tm,mit->objekt())){
                                                                      if(ism.bearbeiten(tm,mit->objekt(),0)==0) valid=false;
                                                                      mit->objekt()->markierung(0);
                                                                      etwasgeschnitten=true;
                                                                     }else{
                                                                      //add-netze innerhalb sind ok, ausserhalb von tm nichts machen
                                                                      if(ism.netzinnerhalbnetz(mit->objekt(),tm)){
                                                                       if(ism.bearbeiten(tm,mit->objekt(),0)==0) valid=false;
                                                                       mit->objekt()->markierung(0);
                                                                       etwasgeschnitten=true;
                                                                      };
                                                                     };
                                                                    };
                                                                   };
                                                                  }while((mlist->naechstes(mit))&&(valid==true));
                                                                 };
                                                                 tm->aktualisieren();
                                                                }else{
                                                                 //error : welt besitzt kein subtraktives netz
                                                                 L->schreiben("Fehler : _welt::kompilierenintersektion() : kein Startnetz gefunden.");
                                                                 valid=false;
                                                                };
                                                                return(tm);
};

unsigned int _welt::erzeugenzone(){
                                                                //funktion benutzt ptm als meshargument. sie iteriert es polygonal,rekursiv ab und 
                                                                //markiert die polygone mit einem durchlaufenden zonenindex >0 . funktion liefert 
                                                                //die anzahl der zonen zurück
                                                                _polygon*pit;
                                                                _partition::_zone*z;
                                                                unsigned int cz;
                                                                unsigned int az;
                                                                unsigned int n;
                                                                _vektor3<_tg> start;
                                                                //-----------------------------
                                                                //strukturellen verbund ermitteln
                                                                ptm->markierungpolygon(0);
                                                                ptm->markierungvertex(0);
                                                                cz=0;
                                                                az=1;
                                                                if(ptm->anfang(pit)) do{
                                                                 if(pit->markierung()==0) {
                                                                  pit->markierungrekursiv(az++);
                                                                  cz++;
                                                                 };
                                                                }while(ptm->naechstes(pit));
                                                                L->schreiben("Anzahl der Zonen=",(int)cz);
                                                                //rohe zonen anlegen und mit polygonen füllen
                                                                for(n=0;n<cz;n++){
                                                                 z=new _partition::_zone(this);
                                                                 if(ptm->anfang(pit))do{
                                                                  if(pit->markierung()==int(n+1)){
                                                                   z->einhaengen(pit);
                                                                  };
                                                                 }while(ptm->naechstes(pit));
                                                                };
                                                                //feststellen, welche inneren Zonen zu welchen äusseren Zonen gehören
                                                                markierungzone(0);
                                                                if(anfang(z))do{
                                                                 z->pruefenumgebungszone();
                                                                }while(naechstes(z));
                                                                //leere zonen löschen
                                                                if(anfang(z))do{
																 if(z->_liste<_polygon >::anzahl()==0) z->_listenknotenbasis<_partition::_zone>::loeschmarkierung(true);
                                                                }while(naechstes(z));
                                                                _listebasis<_partition::_zone >::loeschenmarkiert();
                                                                return(_listebasis<_partition::_zone >::anzahl());
};











void _welt::erzeugenzonenpartition(){
                                                                //funktion iteriert die zonen und initialisiert zu jeder zu die dazu-
                                                                //gehörige baumstruktur aus _partition::_ebene - Objekten
                                                                _partition::_zone*zit;
                                                                _listenknoten<_polygon >*lnpit;
                                                                _liste<_partition::_polygon > lp;
                                                                //---------------------------
                                                                if(anfang(zit))do{
                                                                 //liste aller planes der zone 
                                                                 if(zit->anfang(lnpit))do{
                                                                  lp.einhaengen(new _partition::_polygon(lnpit->objekt())); 
                                                                 }while(zit->naechstes(lnpit));
                                                                 //rekursion starten
                                                                 erzeugenzonenpartition(zit,0,true,&lp);
                                                                 //lp.loeschen();
                                                                }while(naechstes(zit));
};

void _welt::erzeugenzonenpartition(_partition::_zone*zit,_partition::_ebene*parent,bool dir,_liste<_partition::_polygon >*lp){
                                                                //partionierungsalgorithmik startet jetzt
                                                                //achtung!: richtungsnomenklatur im baum : true=naechstes=front, false=vorheriges=rueck 
                                                                _liste<_partition::_polygon > lpfront;
                                                                _liste<_partition::_polygon > lpback;
                                                                _listenknoten<_partition::_polygon >*bestnode;
                                                                _partition::_polygon*bestes;
                                                                _partition::_ebene*p;
                                                                //----------------------------------------
                                                                if(lp->anzahl()>0){
                                                                 polygonoptimaleteilung(lp,bestnode);
                                                                 bestes=bestnode->objekt();
                                                                 bestes->polygon()->markierung(0);//!!!!!!!!!!!! brauch man das ?????
                                                                 p=new _partition::_ebene(zit,parent,dir,bestes->polygon());
                                                                 //liste lp übertragen in lpfront und lpback;
                                                                 erzeugenzonenpartition(lp,bestnode,&lpfront,&lpback);
                                                                 //knoten lit und objekt löschen
                                                                 bestnode->loeschmarkierungobjekt(true);
                                                                 delete bestnode;
                                                                 bestnode=0;
                                                                 lp->aushaengen();
                                                                 //frontliste rekursiv bearbeiten
                                                                 erzeugenzonenpartition(zit,p,true,&lpfront);
                                                                 //backliste rekursiv bearbeiten
                                                                 erzeugenzonenpartition(zit,p,false,&lpback);
                                                                }else{
                                                                 //fertig:konvexer sektor ist entstanden
                                                                };
};

void _welt::erzeugenzonenpartition(_liste<_partition::_polygon >*lp,_listenknoten<_partition::_polygon >*bestnode,_liste<_partition::_polygon >*front,_liste<_partition::_polygon >*rueck){
                                                                //funktion überträgt alle polygone ausser lit->objekt() 
                                                                //in die front und/oder rueck-liste (hessesche normalform)
                                                                _polygon*p;
                                                                _listenknoten<_partition::_polygon >*lnpit;
                                                                _partition::_polygon*pit;
                                                                _partition::_polygon*frontpoly;
                                                                _partition::_polygon*backpoly;
                                                                _partition::_vertex*vit;
                                                                _vektor3<_tg> x;
                                                                _tg d;
                                                                int statusmin;
                                                                int statusmax;
                                                                _tg D,D0,D1,alpha;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> pp;
                                                                //--------------------------
                                                                //L->schreiben("erzeugenzonenpartition");
                                                                p=bestnode->objekt()->polygon();
                                                                if(lp->anfang(lnpit))do{
                                                                 if(lnpit!=bestnode){//if(pit->objekt()!=p){
                                                                  pit=lnpit->objekt();
                                                                  //vit=pit->objekt()->vertex();
                                                                  statusmin=0;
                                                                  statusmax=0;
                                                                  if(pit->anfang(vit))do{
                                                                   //d=-((vit->ort()-p->mitte())*p->normale());
                                                                   d=((*vit-p->mitte())*p->normale());
                                                                   if(d>nahenull){//vorne
                                                                    statusmax=+1;
                                                                   };
                                                                   if(d<-nahenull){//hinten
                                                                    statusmin=-1;
                                                                   };
                                                                   if((d>=-nahenull)&&(d<=nahenull)){//koplanar
                                                                    //nichts machen
                                                                   };
                                                                   //vit=vit->naechstes(pit->objekt());
                                                                  }while(pit->naechstes(vit));//!=pit->objekt()->vertex());
                                                                  if((statusmin==0)&&(statusmax==+1)){//front
                                                                   front->einhaengen(pit);
                                                                  }else
                                                                  if((statusmin==-1)&&(statusmax==0)){//rueck
                                                                   rueck->einhaengen(pit);
                                                                  }else
                                                                  if((statusmin==0)&&(statusmax==0)){//komplanar -> normalen entscheiden
                                                                //  L->schreiben("komplanarität geprüft");
                                                                   x=p->normale()+pit->polygon()->normale();
                                                                   d=x.laenge();
                                                                   if(d<1){//entgegengesetzt -> rueck
                                                                    rueck->einhaengen(pit);
                                                                   }else{//gleichgerichtet ->front
                                                                    front->einhaengen(pit);
                                                                   };
                                                                  }else
                                                                  if((statusmin==-1)&&(statusmax==+1)){//front und rueck
                                                                   //achtung zerteilung vornehmen
                                                                   //schnittgerade zwischen poly p -ebene unr pit ebene holen
                                                                   D0=V3.determinieren(p->ebene(0),p->ebene(1),-pit->polygon()->ebene(0));
                                                                   D1=V3.determinieren(p->ebene(0),p->ebene(1),-pit->polygon()->ebene(1));
                                                                   if(fabs(D0)>fabs(D1)){
                                                                    D=D0;
                                                                    pp=pit->polygon()->ebene(0);
                                                                   }else{
                                                                    D=D1;
                                                                    pp=pit->polygon()->ebene(1);
                                                                   };
                                                                   if(fabs(D)>nahenull){
                                                                    e=pit->polygon()->mitte() - p->mitte();
                                                                    alpha=V3.determinieren(p->ebene(0),p->ebene(1),e)/D;
                                                                    o=pit->polygon()->mitte()+pp*alpha;
                                                                    v=p->normale()%pit->polygon()->normale();
                                                                    pit->teilen(o,o+v,p->normale(),pit->polygon()->normale(),frontpoly,backpoly);
                                                                    if(frontpoly) front->einhaengen(frontpoly);
                                                                    if(backpoly) rueck->einhaengen(backpoly);
                                                                   }else{
                                                                    //error,schwerer
                                                                   };
                                                                   //pit objekt löschen
                                                                   lnpit->loeschmarkierungobjekt(true);
                                                                  }else{
                                                                   //nicht möglich
                                                                  };
                                                                 };
                                                                }while(lp->naechstes(lnpit));
                                                                lp->loeschenmarkiert();
};






void _welt::polygonoptimaleteilung(_liste<_partition::_polygon >*lp,_listenknoten<_partition::_polygon >*&lit){
                                                                //funktion sucht aus einer Liste lp ein Polygonobjekt heraus,
                                                                //das die Szene lp in möglichst gleichmäßige Hlften teilt.
                                                                _listenknoten<_partition::_polygon >*lpit;
                                                                _listenknoten<_partition::_polygon >*liit;
                                                                
                                                                //_liste<_tg> lq;
                                                                //_listenknoten<_tg>*qit;
                                                                //_tg*q;
                                                                
                                                                _listebasis<_bewertungpolygonoptimal > lbo;
                                                                _bewertungpolygonoptimal*bit;
                                                                _bewertungpolygonoptimal*bgut;
                                                               // _bewertungpolygonoptimal*bsta;
                                                                
                                                                
                                                                _tg cf,cb,cd;
                                                                _tg d;
                                                                _vektor3<_tg> x;
                                                                _polygon*p;
                                                                _polygon*pi;
                                                                _vertex*v;
                                                                int smin;
                                                                int smax;
                                                                _tg maxcfcb=0;
                                                                _tg maxdc=100000000;
                                                                _listenknoten<_vertex>*lnv;
                                                                //-------------------
                                                                lit=0;
                                                                if(lp->anfang(lpit))do{
                                                                 //für ein polygon
                                                                 //lpit->objekt alle werte cf,cb,cd bestimmen
                                                                 cf=0;
                                                                 cb=0;
                                                                 cd=0;
                                                                 p=lpit->objekt()->polygon();
                                                                 if(lp->anfang(liit))do{
                                                                  if(liit->objekt()!=lpit->objekt()){
                                                                   //uintersuchen, ob liit->objekt() sich
                                                                   //vor oder hinter lpit->objekt() befindet
                                                                   smin=0;
                                                                   smax=0;
                                                                   pi=liit->objekt()->polygon();
                                                                   iterierenliste(pi,lnv,
                                                                    v=lnv->objekt();
                                                                    x=v->ort()-p->mitte();
                                                                    x.normalisieren();
                                                                    d=-(x*p->normale());
                                                                    if(d>nahenull){//vorne
                                                                     //cf+=1;
                                                                     smax=+1;
                                                                    };
                                                                    if(d<-nahenull){//hinten
                                                                     //cb+=1;
                                                                     smin=-1;
                                                                    };
                                                                   );
                                                                   if((smin==0)&&(smax==+1)) cf+=1; else
                                                                   if((smin==-1)&&(smax==0)) cb+=1; else
                                                                   if((smin==-1)&&(smax==+1)) {cf+=1;cb+=1;cd+=1;};
                                                                  };
                                                                 }while(lp->naechstes(liit));
                                                                 
                                                                 
                                                                 //q=new _tg[1];
                                                                 //q[0]=fabs(cf-cb);
                                                                 //lq.einhaengen(q);
                                                                 
                                                                 //new _bewertungpolygonoptimal(&lbo,fabs(cf-cb),lpit,cf,cb,cd);
                                                                 new _bewertungpolygonoptimal(&lbo,cd/*fabs(cf-cb)*/,lpit,cf,cb,cd);
                                                                 if(maxcfcb<(cf+cb)) maxcfcb=cf+cb;
                                                                 if(maxdc<abs(cf-cb)) maxdc=abs(cf-cb);
                                                                 
                                                                }while(lp->naechstes(lpit));
                                                                //untersuchen , welches der Listenknoten ein cf-cb wert besitzt
                                                                //,das am nächsten an 0 liegt.
                                                                _tg l=0;
                                                                if(lbo.anfang(bit)){
                                                                 bgut=bit;
                                                                 _tg sdm=maxcfcb-_tg(bit->anzahlvorne+bit->anzahlhinten);
                                                                 _tg sdd=fabs(_tg(bit->anzahlvorne-bit->anzahlhinten));
                                                                 l=sqrt(sdm*sdm+sdd*sdd);
                                                                 
                                                                 do{
                                                                  //if(fabs(bit->pkriterium-bsta->pkriterium)<=1){
                                                                   if(bit!=bgut){
                                                                    //nach anzahl bewerten
                                                                    //if((bit->anzahlvorne+bit->anzahlhinten)<(bgut->anzahlvorne+bgut->anzahlhinten)){
                                                                    // bgut=bit;
                                                                    //};
                                                                    //nach minimaler zerteilung bewerten
                                                                    _tg dm=maxcfcb-_tg(bit->anzahlvorne+bit->anzahlhinten);
                                                                    _tg dd=fabs(_tg(bit->anzahlvorne-bit->anzahlhinten));
                                                                    _tg hl=sqrt(dm*dm+dd*dd);
                                                                    
                                                                    
                                                                    if(hl<l){ //bit->zerteilung<bgut->zerteilung){
                                                                     bgut=bit;
                                                                     l=hl;
                                                                    };
                                                                   };
                                                                  //};
                                                                 }while(lbo.naechstes(bit));
                                                                 lit=bgut->listnode;
                                                                };
                                                            
                                                                
                                                                /*lq.anfang(qit);
                                                                if(lp->anfang(lpit))do{
                                                                 if(lit==0){
                                                                  lit=lpit;
                                                                  aq=*qit->objekt();
                                                                 }else{
                                                                  if(*qit->objekt()<aq){
                                                                   lit=lpit;
                                                                   aq=*qit->objekt();
                                                                  };
                                                                 };
                                                                 lq.naechstes(qit);
                                                                }while(lp->naechstes(lpit));
                                                                
                                                                lq.loeschen();*/
};                                                                

void _welt::erzeugenzonensektor(){
                                                                //erzeugt sektoren für jede zone
                                                                _partition::_zone*zit;
                                                                //--------------------------------------
                                                                if(anfang(zit))do{
                                                                 zit->erzeugensektor();
                                                                }while(naechstes(zit));
};

void _welt::verbindenzonesektor(){
                                                                //erzeugt sektoren für jede zone
                                                                _partition::_zone*zit;
                                                                //--------------------------------------
                                                                if(anfang(zit))do{
                                                                 zit->verbindensektor();
                                                                }while(naechstes(zit));
};

void _welt::erzeugenzonensichtbarkeit(){
                                                                //sichtbarkeit für jede zone bestimmen
                                                                _partition::_zone*zit;
                                                                //--------------------------------------
                                                                if(anfang(zit))do{
                                                                 zit->erzeugensichtbarkeit();
                                                                }while(naechstes(zit));
};

void _welt::loeschenzonenichtportalvertex(){
                                                                //alle nicht portalen vertex löschen
                                                                _partition::_zone*zit;
                                                                //--------------------------------------
                                                                if(anfang(zit))do{
                                                                 zit->loeschenvertexnichtportal();
                                                                }while(naechstes(zit));
};

void _welt::einfuegenlichtinsektor(){
                                                                //alle lichter der welt ihren sektoren zuordnen
                                                                _partition::_zone*zit;
                                                                _partition::_sektor*s;
                                                                _licht<_tg,_to>*lit;
                                                                _liste<_licht<_tg,_to> > llist;
                                                                _liste<_partition::_sektor > slist;
                                                                _listenknoten<_licht<_tg,_to> >*lnit;
                                                                _listenknoten<_partition::_sektor >*snit;
                                                                //--------------------------------------
                                                                if(anfang(lit))do{
                                                                 s=0;
                                                                 if(anfang(zit))do{
                                                                  s=zit->sektor(lit->ort());
                                                                 }while((naechstes(zit))&&(s==0));
                                                                 if(s){
                                                                  llist.einhaengen(lit);
                                                                  slist.einhaengen(s);
                                                                 };
                                                                }while(naechstes(lit));
                                                                if(llist.anfang(lnit)){
                                                                 slist.anfang(snit);
                                                                 do{
                                                                  lnit->objekt()->_listenknotenbasis<_licht<_tg,_to> >::aushaengen();
                                                                  lnit->objekt()->_listenknotenbasis<_licht<_tg,_to> >::einhaengen(snit->objekt());
                                                                  slist.naechstes(snit);
                                                                 }while(llist.naechstes(lnit));
                                                                };
                                                                
};
void _welt::einfuegenlichtaussektor(){  
                                                                //alle lichter der zonen bzw sektoren der welt zuurückführen
                                                                _partition::_zone*zit;
                                                                _partition::_sektor*sit;
                                                                _liste<_licht<_tg,_to> > llist;
                                                                _licht<_tg,_to>*lit;
                                                                _listenknoten<_licht<_tg,_to> >*lnlit;
                                                                //-------------------------------------
                                                                if(anfang(zit))do{
                                                                 if(zit->anfang(sit))do{
                                                                  if(sit->anfang(lit))do{
                                                                   llist.einhaengen(lit);
                                                                  }while(sit->naechstes(lit));
                                                                 }while(zit->naechstes(sit));
                                                                }while(naechstes(zit));
                                                                if(llist.anfang(lnlit))do{
                                                                 lnlit->objekt()->_listenknotenbasis<_licht<_tg,_to> >::aushaengen();
                                                                 lnlit->objekt()->_listenknotenbasis<_licht<_tg,_to> >::einhaengen(this);
                                                                }while(llist.naechstes(lnlit));
};

void _welt::erzeugenvertexlicht(){
                                                                //statisches vertexlight aller zonen bestimmen
                                                                _partition::_zone*zit;
                                                                //--------------------------------------
                                                                if(anfang(zit)){
                                                                 do{
                                                                  zit->erzeugenvertexlicht();
                                                                 }while(naechstes(zit));
                                                                }else{
                                                                 
                                                                };
};

void _welt::markierungnetz(int f){
                                                                _netz*it;
                                                                //------
                                                                if(anfang(it))do{
                                                                 it->markierung(f);
                                                                }while(naechstes(it));
};

void _welt::markierungzone(int f){
                                                                _partition::_zone*it;
                                                                //------
                                                                if(anfang(it))do{
                                                                 it->markierung(f);
                                                                }while(naechstes(it));
};

void _welt::markierunggeometrie(int f){
                                                                _geometrie*it;
                                                                //------
                                                                if(anfang(it))do{
                                                                 it->markierung(f);
                                                                }while(naechstes(it));
};

void _welt::markierungkamera(int f){
                                                                _kamera<_tg>*it;
                                                                //------
                                                                if(anfang(it))do{
                                                                 it->markierung(f);
                                                                }while(naechstes(it));
};
//-------------------------------------------------------------- Elementschnittstelle --------------------------------------------------------------------

void _welt::textur(_textur<_tb>*t){              //textur setzen
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->textur(t);
                                                                }while(naechstes(m));
};

void _welt::verwendentextur(bool b){              //textur verwenden ein,aus
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->verwendentextur(b);
                                                                }while(naechstes(m));
};

void _welt::verwendentexturdynamisch(bool b){     //dynamische textur verwenden ein,aus
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->verwendentexturdynamisch(b);
                                                                }while(naechstes(m));
};

void _welt::verwendenverbinderfarbe(bool b){      //connectorfarbe verwenden ein,aus
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->verwendenverbinderfarbe(b);
                                                                }while(naechstes(m));
};

void _welt::zeichnenflaeche(bool b){              //flaeche zeichnen ein,aus
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->zeichnenflaeche(b);
                                                                }while(naechstes(m));
};

void _welt::zeichnenkante(bool b){                //kanten zeichnen ein aus,
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->zeichnenkante(b);
                                                                }while(naechstes(m));
};

void _welt::zeichnennormale(bool b){              //normale zeichnen ein,aus
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->zeichnennormale(b);
                                                                }while(naechstes(m));
};

void _welt::zweiseitig(bool b){                   //zweiseitig zeichnen ein,aus
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->zweiseitig(b);
                                                                }while(naechstes(m));
};

void _welt::maskiert(bool b){                     //maskiert zeichnen ein,aus
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->maskiert(b);
                                                                }while(naechstes(m));
};

void _welt::transparenz(bool b){                  //transparent zeichnen ein,aus
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->transparenz(b);
                                                                }while(naechstes(m));
};

void _welt::transparenzfaktor(_tg f){             //transparentsfaktor setzen 0..1
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->transparenzfaktor(f);
                                                                }while(naechstes(m));
};

void _welt::farbe(const _vektor4<_to> c){          //farbe aller polygone setzen
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->farbe(c);
                                                                }while(naechstes(m));
};

void _welt::farbekante(const _vektor4<_to> c){     //farbe aller kanten setzen
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->farbekante(c);
                                                                }while(naechstes(m));
};

void _welt::farbeverbinder(const _vektor4<_to> c){ //farbe aller verbundelemente im netz setzen
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->farbeverbinder(c);
                                                                }while(naechstes(m));
};

void _welt::anwahl(int i){                     //selektionsstatus setzen
                                                                _netz*m;
                                                                //-------------------
                                                                if(anfang(m))do{
                                                                 m->anwahl(i);
                                                                }while(naechstes(m));
};

void _welt::visualisierensektor(bool b){            //sektoren visualisierung ein/aus
                                                                _partition::_zone*z;
                                                                _partition::_sektor*s;
                                                                //-------------------
                                                                if(anfang(z))do{
                                                                 if(z->anfang(s))do{
                                                                  if(b) s->visualisieren(); else s->unvisualisieren();
                                                                 }while(z->naechstes(s));
                                                                }while(naechstes(z));
};

void _welt::brechzahl(const _tg z){               //brechzahl der subtraktiven weltatmosphäre setzen
                                                                if(z<1) pbrechzahl=1; else pbrechzahl=z;
};

void _welt::dispersionsskalierung(const _tg z){               //brechzahl der subtraktiven weltatmosphäre setzen
                                                                pdispersionsskalierung=z;
};

_tg _welt::brechzahl()const{                      //brechzahl der subtraktiven weltatmosphäre lesen
                                                                return(pbrechzahl);
};

_tg _welt::brechzahldispersiv(const _tg nm)const{     
                                                                _tg lnm=nm;
                                                                if(lnm<350) lnm=350;
                                                                if(lnm>750) lnm=750;
                                                                lnm-=350;
                                                                lnm=lnm/_tg(750-350);
                                                                lnm+=1.5;
                                                                lnm=1.0f/lnm;
                                                                lnm-=0.5;
                                                                lnm*=pdispersionsskalierung;
                                                                lnm+=pbrechzahl;
                                                                if(lnm<1) lnm=1;
                                                                return(lnm);
};
//-------------------------------------------------------------- Zählfunktionen --------------------------------------------------------------------------

unsigned int _welt::anzahlnetz()const{
                                                                return(_listebasis<_netz >::anzahl());
};

unsigned int _welt::anzahlpolygon()const{
                                                                unsigned int i;
                                                                _netz*m;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(m))do{
                                                                 i+=m->anzahlpolygon();
                                                                }while(naechstes(m));
                                                                return(i);
};

unsigned int _welt::anzahlvertex()const{
                                                                unsigned int i;
                                                                _netz*m;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(m))do{
                                                                 i+=m->anzahlvertex();
                                                                }while(naechstes(m));
                                                                return(i);
};                                                                

unsigned int _welt::anzahlverbindervertexpolygon()const{
                                                                unsigned int i;
                                                                _netz*m;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(m))do{
                                                                 i+=m->anzahlverbindervertexpolygon();
                                                                }while(naechstes(m));
                                                                return(i);
};                                                                

unsigned int _welt::anzahlbildvektor()const{
                                                                unsigned int i;
                                                                _netz*m;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(m))do{
                                                                 i+=m->anzahlbildvektor();
                                                                }while(naechstes(m));
                                                                return(i);
};                                                                

unsigned int _welt::anzahlzone()const{
                                                                return(_listebasis<_partition::_zone >::anzahl());
};

unsigned int _welt::anzahlbaumknoten()const{
                                                                unsigned int i;
                                                                _partition::_zone*z;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(z))do{
                                                                 
                                                                 anzahlbaumknoten(z->root(),i);

                                                                }while(naechstes(z));
                                                                return(i);
};

void _welt::anzahlbaumknoten(_partition::_ebene*p,unsigned int &i)const{
                                                                if(p){
                                                                 i++;
                                                                 anzahlbaumknoten(p->naechstes(),i);
                                                                 anzahlbaumknoten(p->vorheriges(),i);
                                                                };
};

unsigned int _welt::anzahlsektor()const{
                                                                unsigned int i;
                                                                _partition::_zone*z;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(z))do{
                                                                 i+=z->_listebasis<_partition::_sektor >::anzahl();
                                                                }while(naechstes(z));
                                                                return(i);
};

unsigned int _welt::anzahlsektorpolygon()const{
                                                                unsigned int i;
                                                                _partition::_zone*z;
                                                                _partition::_sektor*s;
                                                                _partition::_polygon*p;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(z))do{
                                                                 if(z->anfang(s))do{
                                                                  if(s->anfang(p))do{
                                                                   if(p->portal()==false) i+=1;
                                                                  }while(s->naechstes(p));
                                                                 }while(z->naechstes(s));
                                                                }while(naechstes(z));
                                                                return(i);
};

unsigned int _welt::anzahlsektorportal()const{
                                                                unsigned int i;
                                                                _partition::_zone*z;
                                                                _partition::_sektor*s;
                                                                _partition::_polygon*p;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(z))do{
                                                                 if(z->anfang(s))do{
                                                                  if(s->anfang(p))do{
                                                                   if(p->portal()) i+=1;
                                                                  }while(s->naechstes(p));
                                                                 }while(z->naechstes(s));
                                                                }while(naechstes(z));
                                                                return(i);
};

unsigned int _welt::anzahlsektorportalvertex()const{
                                                                unsigned int i;
                                                                _partition::_zone*z;
                                                                _partition::_sektor*s;
                                                                _partition::_polygon*p;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(z))do{
                                                                 if(z->anfang(s))do{
                                                                  if(s->anfang(p))do{
                                                                   if(p->portal()) i+=p->_listebasis<_partition::_vertex >::anzahl();
                                                                  }while(s->naechstes(p));
                                                                 }while(z->naechstes(s));
                                                                }while(naechstes(z));
                                                                return(i);
};

unsigned int _welt::anzahlsektorsichtbarkeitpolygon()const{
                                                                unsigned int i;
                                                                _partition::_zone*z;
                                                                _partition::_sektor*s;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(z))do{
                                                                 if(z->anfang(s))do{
                                                                  i+=s->sichtbarkeitextern()->anzahl();
                                                                 }while(z->naechstes(s));
                                                                }while(naechstes(z));
                                                                return(i);
};

unsigned int _welt::anzahlsektorsichtbarkeitsektor()const{
                                                                unsigned int i;
                                                                _partition::_zone*z;
                                                                _partition::_sektor*s;
                                                                //--------------
                                                                i=0;
                                                                if(anfang(z))do{
                                                                 if(z->anfang(s))do{
                                                                  i+=s->sichtbarkeitsektor()->anzahl();
                                                                 }while(z->naechstes(s));
                                                                }while(naechstes(z));
                                                                return(i);
};

//-------------------------------------------------------------- Zeitfunktionen---------------------------------------------------------------------------


void _welt::zeit(_zeit*t){
                                                                ptimer=t;
};

unsigned int _welt::zeitintersektion() const{
                                                                if(ptimer) return(ptime[1]-ptime[0]); else return(0);
};

unsigned int _welt::zeitzonenerzeugung() const{
                                                                if(ptimer) return(ptime[2]-ptime[1]); else return(0);
};

unsigned int _welt::zeitbinaerehalbraumteilung() const{
                                                                if(ptimer) return(ptime[3]-ptime[2]); else return(0);
};

unsigned int _welt::zeitsektorerzeugung() const{
                                                                if(ptimer) return(ptime[4]-ptime[3]); else return(0);
};

unsigned int _welt::zeitsektorverbindung() const{
                                                                if(ptimer) return(ptime[5]-ptime[4]); else return(0);
};

unsigned int _welt::zeitsichtbarkeit() const{
                                                                if(ptimer) return(ptime[6]-ptime[5]); else return(0);
};

unsigned int _welt::zeitloeschennichtportalvertex() const{
                                                                if(ptimer) return(ptime[7]-ptime[6]); else return(0);
};

unsigned int _welt::zeitbestrahlung() const{
                                                                if(ptimer) return(ptime[8]-ptime[7]); else return(0);
};

char _welt::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_welt>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(peigenetransformation);
                                                                //r^=sd->ladenwert(f);
                                                                //r^=sd->ladenassoziation();
                                                                sd->ladenende();
                                                                return(r);
};

void _welt::speichern(_speicherbardynamisch<_welt>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(peigenetransformation);
                                                                //sd->speichernwert(f);
                                                                //saveassociationargument(sd->datei(),sd,d);
                                                                sd->speichernendeblock();
                                                                
};

char _welt::assoziieren(_speicherbardynamisch<_welt>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
bool _welt::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																ladenzeiger(d);
																for(int i=0;i<30;i++) d->laden(ptime[i]);
																d->laden(pzyklus);
																d->laden(paltezeit);
																d->laden(pzykluszeit);
																d->laden(pmarkierungkollision);
																d->laden(plichtambient);
																d->laden(pbrechzahl);
																d->laden(pdispersionsskalierung);
																d->laden(peigenetransformation);
																d->laden(panimationsfaktor);
																d->laden(pdbintersektion);
																d->laden(pdbsektor);
																d->laden(pdbbsp);
																d->laden(pdbportal);
																d->laden(pdbsichtbarkeit);   
																ladenmaterial(d);

																ptm=0;
																unsigned int a;
																unsigned int i;
																_vektor3<_tg> vn(0,0,0);
																_vektor3<_to> cn3(1,1,1);
																_vektor4<_to> cn(1,1,1,1);
																
																_textur<_tb>*tit;
																_listebasis<_textur<_tb> >::loeschen();
																d->laden(a);
																L->l("texturen werden geladen : anzahl ",(int)a);
																for(i=0;i<a;i++){
																 tit=new _textur<_tb>(this);
																 tit->laden(d);
															    };
															    L->l("Texturen wurden geladen");

																_netz*nit;
																_listebasis<_netz>::loeschen();
																d->laden(a);
																L->l("Netze werden geladen : anzahl=",(int)a);
																for(i=0;i<a;i++){
																 nit=new _netz();
																 nit->einhaengen(this);
																 nit->welt(this);
																 nit->laden(d);
																 L->l("Netz wurde geladen.");
															    };
															    L->l("Netze wurden geladen.");

																_kugel*kit;
																_listebasis<_kugel>::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 kit=new _kugel(this,this,vn,0,cn,4);
																 kit->laden(d);
															    };

																_partikelquelle*qit;
																_listebasis<_partikelquelle>::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 qit=new _partikelquelle(this,0,this,this);
																 qit->laden(d);
															    };

																/*_figur*fit;
																_listebasis<_figur>::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 fit=new _figur(this,this,vn,0);
																 fit->laden(d);
															    };*/

																_kamera<_tg>*mit;
																_listebasis<_kamera<_tg> >::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 mit=new _kamera<_tg>(this);
																 mit->laden(d);
															    };

																_licht<_tg,_to>*lit;
																_listebasis<_licht<_tg,_to> >::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 lit=new _licht<_tg,_to>(this,vn,cn3,0);
																 lit->laden(d);
															    };

																_gravitation<_tg>*git;
																_listebasis<_gravitation<_tg> >::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 git=new _gravitation<_tg>(this,vn,0);
																 git->laden(d);
															    };

														    	_feldelektrostatisch<_tg>*feit;
																_listebasis<_feldelektrostatisch<_tg> >::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 feit=new _feldelektrostatisch<_tg>(this,vn,vn);
																 feit->laden(d);
															    };

														    	_feldmagnetostatisch<_tg>*fmit;
																_listebasis<_feldmagnetostatisch<_tg> >::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 fmit=new _feldmagnetostatisch<_tg>(this,vn,vn);
																 fmit->laden(d);
															    };

																_partition::_zone*zit;
																_listebasis<_partition::_zone>::loeschen();
																d->laden(a);
																for(i=0;i<a;i++){
																 zit=new _partition::_zone(this);
																 zit->laden(d);
															    };
															    


																return(true);

};
void _welt::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																speichernzeiger(d,ptm);
																for(int i=0;i<30;i++) d->speichern(ptime[i]);
																d->speichern(pzyklus);
																d->speichern(paltezeit);
																d->speichern(pzykluszeit);
																d->speichern(pmarkierungkollision);
																d->speichern(plichtambient);
																d->speichern(pbrechzahl);
																d->speichern(pdispersionsskalierung);
																d->speichern(peigenetransformation);
																d->speichern(panimationsfaktor);
																d->speichern(pdbintersektion);
																d->speichern(pdbsektor);
																d->speichern(pdbbsp);
																d->speichern(pdbportal);
																d->speichern(pdbsichtbarkeit); 
																speichernmaterial(d);


																_textur<_tb> *tit;
																d->speichern(_listebasis<_textur<_tb> >::anzahl());
																iterieren(tit,tit->speichern(d));


																_netz*nit;
																d->speichern(_listebasis<_netz>::anzahl());
																iterieren(nit,nit->speichern(d));

																_kugel*kit;
																d->speichern(_listebasis<_kugel>::anzahl());
																iterieren(kit,kit->speichern(d));

																_partikelquelle*qit;
																d->speichern(_listebasis<_partikelquelle>::anzahl());
																iterieren(qit,qit->speichern(d));

																/*_figur*fit;
																d->speichern(_listebasis<_figur>::anzahl());
																iterieren(fit,fit->speichern(d));*/

																_kamera<_tg>*mit;
																d->speichern(_listebasis<_kamera<_tg> >::anzahl());
																iterieren(mit,mit->speichern(d));

																_licht<_tg,_to>*lit;
																d->speichern(_listebasis<_licht<_tg,_to> >::anzahl());
																iterieren(lit,lit->speichern(d));

																_gravitation<_tg>*git;
																d->speichern(_listebasis<_gravitation<_tg> >::anzahl());
																iterieren(git,git->speichern(d));

																_feldelektrostatisch<_tg>*feit;
																d->speichern(_listebasis<_feldelektrostatisch<_tg> >::anzahl());
																iterieren(feit,feit->speichern(d));

																_feldmagnetostatisch<_tg>*fmit;
																d->speichern(_listebasis<_feldelektrostatisch<_tg> >::anzahl());
																iterieren(fmit,fmit->speichern(d));

																_partition::_zone*zit;
																d->speichern(_listebasis<_partition::_zone>::anzahl());
																iterieren(zit,zit->speichern(d));

};
bool _welt::assoziieren(){
																if(zeigergeladen()){
																 assoziierenzeiger(ptm);
																 loeschenzeiger();
																};
																return(true);
																
};
//******************************************************************************************************************************************************************************************************
//                                                              B E W E R T U N G P O L Y G O N O P T I M A L 
//******************************************************************************************************************************************************************************************************
_bewertungpolygonoptimal::_bewertungpolygonoptimal(_listebasis<_bewertungpolygonoptimal >*l,_tg s,_listenknoten<_partition::_polygon >*ln,_tg av,_tg ah,_tg az):_listenknotenbasissortiert<_bewertungpolygonoptimal,_tg >(l,s){
                                                                pkriterium=s;
                                                                anzahlvorne=av;
                                                                anzahlhinten=ah;
                                                                zerteilung=az;
                                                                listnode=ln;
};

_bewertungpolygonoptimal::~_bewertungpolygonoptimal(){
};
//******************************************************************************************************************************************************************************************************
//                                                              D R E I E C K
//******************************************************************************************************************************************************************************************************

_dreieck::_dreieck(_polygon*p,_vertex*v0,_vertex*v1,_vertex*v2){
                                                                ppolygon=p;
                                                                pvertex[0]=v0;
                                                                pvertex[1]=v1;
                                                                pvertex[2]=v2;
                                                                pflag=0;
};

_dreieck::~_dreieck(){
};

void _dreieck::markierung(int f){
                                                                pflag=f;
};

int _dreieck::markierung() const{
                                                                return(pflag);
};

void _dreieck::aktualisieren(){
};

//******************************************************************************************************************************************************************************************************
//                                                              K A N T E D R E I E C K
//******************************************************************************************************************************************************************************************************

_kantedreieck::_kantedreieck(_dreieck*t0,_dreieck*t1,_vertex*v0,_vertex*v1){
                                                                ptriangle[0]=t0;
                                                                ptriangle[1]=t1;
                                                                pvertex[0]=v0;
                                                                pvertex[1]=v1;
                                                                pvector=v1->ort()-v0->ort();
                                                                pflag=0;
};

_kantedreieck::~_kantedreieck(){
};

void _kantedreieck::markierung(int f){
                                                                pflag=f;
};

int _kantedreieck::markierung() const{
                                                                return(pflag);
};

void _kantedreieck::invertierenvertex(){
                                                                _vertex*v;
                                                                //--------------------
                                                                v=pvertex[0];
                                                                pvertex[0]=pvertex[1];
                                                                pvertex[1]=v;
                                                                pvector*=-1;
};

void _kantedreieck::invertierendreieck(){
                                                                _dreieck*p;
                                                                //----------------------
                                                                p=ptriangle[0];
                                                                ptriangle[0]=ptriangle[1];
                                                                ptriangle[1]=p;
                                                                pflag=0;

};

_vertex*_kantedreieck::vertex(int i){
                                                                if((i>=0)&&(i<2)){
                                                                 return(pvertex[i]);
                                                                }else{
                                                                 return(0);
                                                                };
};

_dreieck*_kantedreieck::dreieck(int i){
                                                                if((i>=0)&&(i<2)){
                                                                 return(ptriangle[i]);
                                                                }else{
                                                                 return(0);
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              V E R T E X 
//******************************************************************************************************************************************************************************************************

_vertex::_vertex(_netz*n,_vektor3<_tg>&v):_listenknotenbasis<_vertex>(n),_vektor3<_tg>(v){
                                                                //ppolygon=p;
                                                               // if(p) if(p->vertex()==0) p->vertex(this);
                                                                pflag=0;
                                                                pintersection=0;
                                                                //firstisintroconnector=0;
                                                                pstatus=0;
                                                                ptransformed.setzen(0,0,0);
                                                                pparameter.setzen(0,0,0);
                                                                pnormale.setzen(1,0,0);
                                                                //pblockposition=0;
                                                                //pblocknormale=0;
};

_vertex::~_vertex(){
                                                                plistisintroconnector.loeschen();
};

_netz*_vertex::netz(){
                                                                _listenknoten<_polygon>*it;
                                                                if(anfang(it)){
                                                                 return(it->objekt()->netz());
                                                                };
                                                                return(0);
                                                               
};
void _vertex::rotierenx(const _tg w){
																_vektor3<_tg>::rotx(w);
};
void _vertex::rotiereny(const _tg w){
																_vektor3<_tg>::roty(w);
};
void _vertex::rotierenz(const _tg w){
																_vektor3<_tg>::rotz(w);
};

void _vertex::aktualisierenblocknormale(){ 
                                                                _verbindervertexpolygon*cit;
                                                                _listenknoten<_polygon>*pit;
                                                                if(anfang(pit))do{
                                                                 cit=static_cast<_verbindervertexpolygon*>(pit);
                                                                 cit->blocknormale(pnormale);
                                                                }while(naechstes(pit));
};
void _vertex::aktualisierenblockort(){
                                                                _verbindervertexpolygon*cit;
                                                                _listenknoten<_polygon>*pit;
                                                                if(anfang(pit))do{
                                                                 cit=static_cast<_verbindervertexpolygon*>(pit);
                                                                 cit->blockort(*this);
                                                                }while(naechstes(pit));
};
void _vertex::aktualisiereninterpoliertenormale(){
                                                                _verbindervertexpolygon*cit;
                                                                _listenknoten<_polygon>*pit;
                                                                //_tg c=0;
                                                                //------
                                                                pnormale.setzen(0,0,0);
                                                                if(anfang(pit)){
                                                                 do{
                                                                  cit=static_cast<_verbindervertexpolygon*>(pit);
                                                                  pnormale+=cit->polygon()->normale();
                                                                 }while(naechstes(pit));
                                                                 pnormale.normalisieren();
                                                                 if(anfang(pit))do{
                                                                  cit=static_cast<_verbindervertexpolygon*>(pit);
                                                                  cit->blocknormale(pnormale);
                                                                 }while(naechstes(pit));
                                                                };
};
void _vertex::opazitaetverbinder(const _to o){
                                                                _verbindervertexpolygon*cit;
                                                                _listenknoten<_polygon>*pit;
                                                                if(anfang(pit))do{
                                                                 cit=static_cast<_verbindervertexpolygon*>(pit);
                                                                 cit->opazitaet(o);
                                                                }while(naechstes(pit));
};
_verbindervertexpolygon* _vertex::verbinder(const _polygon*p){
                                                                _verbindervertexpolygon*cit;
                                                                _listenknoten<_polygon>*pit;
                                                                if(anfang(pit))do{
                                                                 cit=static_cast<_verbindervertexpolygon*>(pit);
                                                                 if(cit->polygon()==p) return(cit);
                                                                }while(naechstes(pit));
                                                                return(0);
};
void _vertex::markierungverbinder(int i){
                                                                _verbindervertexpolygon*cit;
                                                                _listenknoten<_polygon>*pit;
                                                                if(anfang(pit))do{
                                                                 cit=static_cast<_verbindervertexpolygon*>(pit);
                                                                 cit->markierung(i);
                                                                }while(naechstes(pit));
};
void _vertex::erzeugenintersektionsverbinder(_netz*m,_polygon*cp){
                                                                if(plistisintroconnector.anzahl()==0){
                                                                 if(pintersection==0){
                                                                  //add(o,m->ort->o,ao);
                                                                  pintersection=new _intersektion(*this,this);//virtuelle intersektion
                                                                 };
                                                                };
};
void _vertex::loeschenintersektionsverbinder(){
                                                                if(pintersection){
                                                                 delete pintersection;
                                                                 pintersection=0;
                                                                };
};
_intersektion*_vertex::intersektion(){
                                                                return(pintersection);
};
_listebasis<_verbinderisintro >*_vertex::verbinderisintroliste(){
                                                                return(&plistisintroconnector);
};
char _vertex::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_vertex>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(*this);
                                                                r^=sd->ladenwert(pflag);
                                                                r^=sd->ladenwert(pnormale);
                                                                sd->ladenende();
                                                                return(r);
};
void _vertex::speichern(_speicherbardynamisch<_vertex>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(*this);
                                                                sd->speichernwert(pflag);
                                                                sd->speichernwert(pnormale);
                                                                sd->speichernendeblock();
};
char _vertex::assoziieren(_speicherbardynamisch<_vertex>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                return(1);
};
bool _vertex::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																//L->l("Vertex wird geladen.");
																d->laden(speichername());
																_vektor3<_tg> v;
																d->laden(v);
																setzen(v);
																//L->l("  Vertexort =",_vektor3<_tg>(*this));
															    d->laden(pflag);
																d->laden(ptransformed);
																d->laden(pparameter);
																d->laden(pnormale);
																d->laden(pstatus);
																
																/*unsigned int i,a;

																//_listebasis<_verbindervertexpolygon>::loeschen();
																_verbindervertexpolygon*cit;
																d->laden(a);
																//L->l("  Es sollen Verbinder geladen werden : anzahl=",(int)a);
																for(i=0;i<a;i++){
																 cit=new _verbindervertexpolygon(this,0);
																 cit->laden(d);
																};*/
																																

																return(true);
};
void _vertex::speichern(_dateispeicherbarbinaer*d){
																//L->l("Vertex wird gespeichert.");
																d->speichern(speichername());
																_vektor3<_tg> v=*this;
																d->speichern(v);
																//L->l("  Vertexort =",v);
															    d->speichern(pflag);
																d->speichern(ptransformed);
																d->speichern(pparameter);
																d->speichern(pnormale);
																d->speichern(pstatus);
																//verbinder werden nicht vom vertex gespeichert, sondern von poly, wegen der reihenfolge


};
bool _vertex::assoziieren(){
																if(zeigergeladen()){
																 loeschenzeiger();
																};
																return(true);
};
void _vertex::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->loeschensektion();
                                                                d->addierensektion(L"Allgemein");

                                                                d->einhaengen(L"Allgemein",L"Position",*this);
                                                                d->einhaengen(L"Allgemein",L"Markierung",pflag);
                                                                _vektor4<_to> c;
                                                                _verbindervertexpolygon*v;
                                                                _listenknoten<_polygon>*lnp;
                                                                _tg cc=0;
                                                                iterieren(lnp,
                                                                 v=static_cast<_verbindervertexpolygon*>(lnp);
                                                                 c+=v->farbe();
                                                                 cc+=1;
                                                                );
                                                                if(cc>0){
                                                                 c*=1.0f/cc;
                                                                };
                                                                d->einhaengen(L"Allgemein",L"Verbinderfarbe (alle)",c);
                                                                new _editionskopplungort(d,L"Allgemein",L"Position");
                                                                
};
void _vertex::auslesendialog(_dynamischerdialog*d){
                                                                _vektor3<_tg> v;
                                                                d->auslesen(L"Allgemein",L"Position",v);
                                                                this->setzen(v);
                                                                d->auslesen(L"Allgemein",L"Markierung",pflag);
                                                                if(d->beruehrt(L"Allgemein",L"Verbinderfarbe (alle)")){
                                                                 _vektor4<_to> c;
                                                                 d->auslesen(L"Allgemein",L"Verbinderfarbe (alle)",c);
                                                                 _verbindervertexpolygon*v;
                                                                 _listenknoten<_polygon>*lnp;
                                                                 iterieren(lnp,
                                                                  v=static_cast<_verbindervertexpolygon*>(lnp);
                                                                  v->farbe(c);
                                                                 );
                                                                };
                                                                
};
//******************************************************************************************************************************************************************************************************
//                                                              V E R B I N D E R V E R T E X P O L Y G O N 
//******************************************************************************************************************************************************************************************************

_verbindervertexpolygon::_verbindervertexpolygon(_vertex*v,_polygon*p):_verbinder<_vertex,_polygon>(p,v,v,p){
                                                                pflag=0;
                                                                pcolor.setzen(1,0,0,1);
                                                                pgegenkante=0;
                                                                pblockzeiger=0;
                                                                pkollisionszaehler=0;
                                                                pnextvertex=0;
                                                              
};
_verbindervertexpolygon::~_verbindervertexpolygon(){
                                                                //if(pgegenkante) pgegenkante->pgegenkante=0;
};


/*
void _verbindervertexpolygon::polygon(_polygon*p){
                                                                ppolygon=p;
};
*/
void _verbindervertexpolygon::multiplizierenfarbe(const _to f){
                                                                pcolor.x(pcolor.x()*f);
                                                                pcolor.y(pcolor.y()*f);
                                                                pcolor.z(pcolor.z()*f);
                                                                if(pblockzeiger){
                                                                 *(pblockzeiger+6+0)=begrenzen<_to>(pcolor[0],0,1);
                                                                 *(pblockzeiger+6+1)=begrenzen<_to>(pcolor[1],0,1);
                                                                 *(pblockzeiger+6+2)=begrenzen<_to>(pcolor[2],0,1);
                                                                };
};
void _verbindervertexpolygon::berechnenlicht(_licht<_tg,_to>*l,_polygon*poly){
                                                                _vertex*v=vertex();//dynamic_cast<_vertex*>(_listenknotenbasis<_verbindervertexpolygon>::liste());
                                                                if(v){
                                                                 _vektor4<_to> hf;
                                                                 _vektor3<_tg> hh=l->ort()- v->ort();
				                                                 _tg d=hh.laengelaenge();
				                                                 _tg i=l->intensitaetdynamisch()/(1+d);
				                                                 hh*=(_tg(1)/sqrt(d));
				                                                //Local f#=Abs(hh.product(normal))'*poly.sigmadiffuse
				                                                 _tg w=hh.winkel(poly->normale());
				                                                 if(w>90) w=180-w;
				                                                 w/=90;
				                                                 _tg f=gauss<_tg>(w,poly->glanzbreite());
				                                                 _vektor3<_to> ho=l->farbedynamisch()*i*f;
				                                                 hf.setzen(ho[0],ho[1],ho[2],0);
				                                                 pcolor+=hf;
				                                                };
};
void _verbindervertexpolygon::aktualisierenlichtergebnis(){
                                                                if(pblockzeiger){
                                                                 *(pblockzeiger+6+0)=pcolor[0];
                                                                 *(pblockzeiger+6+1)=pcolor[1];
                                                                 *(pblockzeiger+6+2)=pcolor[2];
                                                                };
};
void _verbindervertexpolygon::farbe(const _vektor4<_to>&c){
                                                                pcolor=c;
                                                                if(pblockzeiger){
                                                                 *(pblockzeiger+6+0)=c[0];
                                                                 *(pblockzeiger+6+1)=c[1];
                                                                 *(pblockzeiger+6+2)=c[2];
                                                                 *(pblockzeiger+6+3)=c[3];
                                                                };
};         
void _verbindervertexpolygon::farbe(const _vektor3<_to>&c){
                                                                pcolor.setzen(c[0],c[1],c[2],pcolor.w());
                                                                if(pblockzeiger){
                                                                 *(pblockzeiger+6+0)=c[0];
                                                                 *(pblockzeiger+6+1)=c[1];
                                                                 *(pblockzeiger+6+2)=c[2];
                                                                 // *(pblockzeiger+6+3)=c[3];
                                                                };
};                                                     
void _verbindervertexpolygon::opazitaet(const _tg o){
                                                                pcolor.w(o);
                                                                if(pblockzeiger){
                                                                 *(pblockzeiger+6+3)=o;
                                                                };
                                                                
};    
_vektor4<_to> _verbindervertexpolygon::farbe()const{
                                                                return(pcolor);
};
void _verbindervertexpolygon::blockzeiger(_tg*pb){
                                                                pblockzeiger=pb;
};
void _verbindervertexpolygon::blockort(const _vektor3<_tg>&o){
                                                                if(pblockzeiger){
                                                                 *(pblockzeiger+0+0)=o[0];
                                                                 *(pblockzeiger+0+1)=o[1];
                                                                 *(pblockzeiger+0+2)=o[2];
                                                                };
};
void _verbindervertexpolygon::blocknormale(const _vektor3<_tg>&n){
                                                                if(pblockzeiger){
                                                                 *(pblockzeiger+3+0)=n[0];
                                                                 *(pblockzeiger+3+1)=n[1];
                                                                 *(pblockzeiger+3+2)=n[2];
                                                                };
};

bool _verbindervertexpolygon::verknuepfen(){
                                                                //sucht die gegenkante zu this und verknüpft mit dem entsprechendem
                                                                //verbinderelement, welches entweder an v hängt oder an pvertexnext 
                                                                //oder nicht existent ist (return false)
                                                                _verbindervertexpolygon*cit;
                                                                _listenknoten<_polygon>*vit;
                                                                _vertex*v=vertex();//dynamic_cast<_vertex*>(_listenknotenbasis<_verbindervertexpolygon>::liste());
                                                                _vertex*nv=naechstervertex();
                                                                if(v){
                                                                 //ist gegenkante an v?
                                                                 if(v->anfang(vit))do{
                                                                  cit=static_cast<_verbindervertexpolygon*>(vit);
                                                                  if(cit!=this){
                                                                   if(cit->naechstervertex()==nv){
                                                                    pgegenkante=cit;
                                                                    cit->pgegenkante=this;
                                                                    return(true);
                                                                   };
                                                                  };
                                                                 }while(v->naechstes(vit));
                                                                 //ist gegenkante an pnextvertex?
                                                                 if(nv->anfang(vit))do{
                                                                  cit=static_cast<_verbindervertexpolygon*>(vit);
                                                                  if(cit->naechstervertex()==v){
                                                                   pgegenkante=cit;
                                                                   cit->pgegenkante=this;
                                                                   return(true);
                                                                  };
                                                                 }while(nv->naechstes(vit));
                                                                };
                                                                return(false);
};
_verbindervertexpolygon* _verbindervertexpolygon::gegenkante(){
                                                                return(pgegenkante);
};
/*
_vertex*_verbindervertexpolygon::vertex(){
                                                                _vertex*v=dynamic_cast<_vertex*>(_listenknotenbasis<_verbindervertexpolygon>::liste());
                                                                return(v);
};
*/
char _verbindervertexpolygon::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_verbindervertexpolygon>*sd){
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(pflag);
                                                                r^=sd->ladenwert(pcolor);
                                                                r^=sd->ladenassoziation();
                                                          // r^=sd->ladenassoziation();
                                                                r^=sd->ladenassoziation();
                                                                //texturvektor laden
                                                                _vektor2<_tg> v;
                                                                for(unsigned int i=0;i<listenanzahl();i++){
                                                                 unsigned int n;
                                                                 r^=sd->ladenwert(n);
                                                                 //L->schreiben("n=",(int)n);
                                                                 for(unsigned int z=0;z<n;z++){
                                                                  r^=sd->ladenwert(v);
                                                                  einfuegenvektor(i,v);
                                                                 };
                                                                };
                                                                sd->ladenende();
                                                                return(r);
};
void _verbindervertexpolygon::speichern(_speicherbardynamisch<_verbindervertexpolygon>*sd){
                                                                sd->speichernbeginn();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(pflag);
                                                                sd->speichernwert(pcolor);
                                                                saveassociationargument(sd->datei(),sd,pgegenkante);
                                                                saveassociationargument(sd->datei(),sd,vertex());
                                                                //saveassociationargument(sd->datei(),sd,naechstervertex());
                                                                //saveassociationargument(sd->datei(),sd,polygon());
                                                                //texturvektor speichern
                                                                for(unsigned int i=0;i<listenanzahl();i++){
                                                                 if(_texturvektor<_tg>::liste(i)){
                                                                  sd->speichernwert(_texturvektor<_tg>::liste(i)->anzahl());
                                                                  _bildvektor<_tg>*mit;
                                                                  if(_texturvektor<_tg>::liste(i)->anfang(mit))do{
                                                                   sd->speichernwert(*mit);
                                                                  }while(_texturvektor<_tg>::liste(i)->naechstes(mit));
                                                                 }else{
                                                                  sd->speichernwert(0);
                                                                 };
                                                                };
                                                                sd->speichernende();
};
char _verbindervertexpolygon::assoziieren(_speicherbardynamisch<_verbindervertexpolygon>*sd){
                                                                sd->assoziierenverschachtelung();
                                                                
                                                                
                                                                _vertex*v;
                                                                associateassociationargument(sd->datei(),sd->assoziation(),pgegenkante);
                                                                associateassociationargument(sd->datei(),sd->assoziation(),v);
                                                                _polygon*p=dynamic_cast<_polygon*>(_listenknoten<_vertex>::liste());//das ist der poly, zu dem es gehört
																 _listenknoten<_vertex>::objekt(v);
																 _listenknoten<_polygon>::einhaengen(v);
																 _listenknoten<_polygon>::objekt(p);
                                                                
                                                                
                                                                //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! KONVERSION
                                                          /*  _polygon*p;
                                                            associateassociationargument(sd->datei(),sd->assoziation(),pgegenkante);
                                                            associateassociationargument(sd->datei(),sd->assoziation(),pnextvertex);
                                                            associateassociationargument(sd->datei(),sd->assoziation(),p);
															_vertex*v=dynamic_cast<_vertex*>(_listenknoten<_polygon>::liste());//das ist der vertex, zu dem es gehört
															// if(v==0) L->l("   SCHEISSE");
															_listenknoten<_polygon>::objekt(p);
															_listenknoten<_vertex>::einhaengen(p);
															_listenknoten<_vertex>::objekt(v);*/
                                                               
                                                                return(1);
};
bool _verbindervertexpolygon::laden(_dateispeicherbarbinaer*d){
																//deletesecure(pblockzeiger);
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																ladentexturvektor(d);
																ladenzeiger(d);
														//ladenzeiger(d);
																ladenzeiger(d);
																d->laden(pcolor);
																d->laden(pflag);
																d->laden(pkollisionszaehler);
																return(true);
};
void _verbindervertexpolygon::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																speicherntexturvektor(d);
																speichernzeiger(d,vertex());
																//speichernzeiger(d,naechstervertex());
																speichernzeiger(d,pgegenkante);
																d->speichern(pcolor);
																d->speichern(pflag);
																d->speichern(pkollisionszaehler);
};
bool _verbindervertexpolygon::assoziieren(){
																//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! KONVERSION
                                                                
                                                                
																//L->l("_verbindervertexpolygon wird assoziiert:");
																if(zeigergeladen()){
																
															/*_polygon*p;
															assoziierenzeiger(p);
															if(p) L->l("  polygon wurde assoziiert");
															assoziierenzeiger(pnextvertex);
															if(pnextvertex) L->l("  nextvertex wurde assoziiert");
															assoziierenzeiger(pgegenkante);
															if(pgegenkante) L->l("  gegenkante wurde assoziiert");
															_vertex*v=dynamic_cast<_vertex*>(_listenknoten<_polygon>::liste());//das ist der vertex, zu dem es gehört
															_listenknoten<_polygon>::objekt(p);
															_listenknoten<_vertex>::einhaengen(p);
															_listenknoten<_vertex>::objekt(v);
																 */
																 
																 
																  _vertex*v;
																  assoziierenzeiger(v);
																  assoziierenzeiger(pgegenkante);
																 _polygon*p=dynamic_cast<_polygon*>(_listenknoten<_vertex>::liste());//das ist der vertex, zu dem es gehört
																 _listenknoten<_vertex>::objekt(v);
																 _listenknoten<_polygon>::einhaengen(v);
																 _listenknoten<_polygon>::objekt(p);
																 
																 
																 
																 
																 
																 
																 loeschenzeiger();
																};
																return(true);
};
//******************************************************************************************************************************************************************************************************
//                                                              K U G E L S C H A T T E N
//******************************************************************************************************************************************************************************************************
_kugelschatten::_kugelschatten(_kugel*k,_listebasis<_schatten<_tg,_to> >*schattenliste,_licht<_tg,_to>*l,_tg laenge):_schatten<_tg,_to>(schattenliste,l,laenge),_listenknotenbasis<_kugelschatten>(k){
                                                                pkugel=k;
                                                                aktualisieren();
};
_kugelschatten::~_kugelschatten(){
                                                                pquado.loeschen();
                                                                pquadu.loeschen();
};
void _kugelschatten::opazitaet(const _to o){
};
void _kugelschatten::zeichnen(_grafik*g){
                                                                _licht<_tg,_to>*plicht=licht();
                                                                if(plicht){
                                                                 if(geaendert()) aktualisieren();
                                                                 _listenknoten<_vektor3<_tg> >*ito;
                                                                 _listenknoten<_vektor3<_tg> >*itu;
                                                                 if((pquado.anfang(ito))&&(pquadu.anfang(itu))){
                                                                  g->polygon(&pquado);
                                                                  /*
                                                                  glBegin(GL_POLYGON);
                                                                  do{
                                                                   glVertex3dv(ito->objekt()->daten());
                                                                  }while(pquado.vorheriges(ito));
                                                                  glEnd();
                                                                  */
                                                                  g->rechteckstreifenzyklisch(&pquado,&pquadu);
                                                                  /*
                                                                  pquado.anfang(ito);
                                                                  pquadu.anfang(itu);
                                                                  glBegin(GL_QUAD_STRIP);
                                                                  do{
                                                                   glVertex3dv(itu->objekt()->daten());
                                                                   glVertex3dv(ito->objekt()->daten());
                                                                   pquadu.naechstes(itu);
                                                                  }while(pquado.naechstes(ito));
                                                                  glVertex3dv(itu->objekt()->daten());
                                                                  glVertex3dv(ito->objekt()->daten());
                                                                  glEnd();
                                                                  */
                                                                  g->polygon(&pquadu);
                                                                   /*
                                                                  pquadu.anfang(itu);
                                                                  glBegin(GL_POLYGON);
                                                                  do{
                                                                   glVertex3dv(itu->objekt()->daten());
                                                                  }while(pquadu.naechstes(itu));
                                                                  glEnd();
                                                                  */
                                                                 };
                                                                 
                                                                };
};
void _kugelschatten::zeichnendebug(_grafik*){
};
void _kugelschatten::aktualisieren(){
                                                                _licht<_tg,_to>*plicht=licht();
                                                                if(plicht){
                                                                 _tg plaenge=laenge();
                                                                 pquado.loeschen();
                                                                 pquadu.loeschen();
                                                                 _vektor3<_tg> v=pkugel->ort()-plicht->ort();
                                                                 v.normalisieren();
                                                                 _vektor3<_tg> a;
                                                                 _vektor3<_tg> b;
                                                                 _vektor3<_tg> x;
                                                                 _vektoranalysis3<_tg> V3;
                                                                 V3.berechnenorthogonalenvektor(v,a);
                                                                 a.normalisieren();
                                                                 b=v%a;
                                                                 for(double alpha=0;alpha<360;alpha+=360.0f/double(pkugel->aufloesung())){
                                                                  x=pkugel->ort()+a*sin(alpha*_ph)*pkugel->radius()+b*cos(alpha*_ph)*pkugel->radius();
                                                                  v=x-plicht->ort();
                                                                  v.normalisieren();
                                                                  v*=plaenge;
                                                                  pquado.einhaengen(new _vektor3<_tg>(x));
                                                                  pquadu.einhaengen(new _vektor3<_tg>(x+v));
                                                                 };
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              K U G E L 
//******************************************************************************************************************************************************************************************************
_kugel::_kugel(_welt*w,_listebasis<_kugel>*l,const _vektor3<_tg> o,const _tg r,const _vektor4<_to> f,unsigned int res):_listenknotenbasis<_kugel>(l){
                                                                pschatteniterator=0;
                                                                pwelt=w;
                                                                pradius=r;
                                                                port=o;
                                                                pfarbe=f;
                                                                paufloesung=res;
                                                                pvektor[0].setzen(1,0,0);
                                                                pvektor[1].setzen(0,1,0);
                                                                pvektor[2].setzen(0,0,1);
                                                                vl0.setzen(-100,20,100);
                                                                vl1.setzen(100,-100,-100);
                                                                plicht[0]=new _licht<_tg,_to>(0,port+vl0,_vektor3<_to>(1,1,1),5);
                                                                plicht[1]=new _licht<_tg,_to>(0,port+vl1,_vektor3<_to>(1,1,1),5);
                                                                plicht[0]->farbeglanz(_vektor3<_to>(0.05,0.05,0.05));
                                                                plicht[1]->farbeglanz(_vektor3<_to>(0.05,0.05,0.05));
};
_kugel::~_kugel(){
                                                                delete plicht[0];
                                                                delete plicht[1];
};
_vektor3<_tg> _kugel::transformieren(const _vektor3<_tg>&v){
                                                                return(pvektor[0]*v[0] + pvektor[1]*v[1] + pvektor[2]*v[2]);
};
void _kugel::setzenstandardausrichtung(){
                                                                pvektor[0].setzen(1,0,0);
                                                                pvektor[1].setzen(0,1,0);
                                                                pvektor[2].setzen(0,0,1);
                                                                
};
void _kugel::rotierenabsolut(const _vektor3<_tg>&a,const _tg winkel){
                                                                pvektor[0].setzen(1,0,0);
                                                                pvektor[1].setzen(0,1,0);
                                                                pvektor[2].setzen(0,0,1);
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> e;
                                                                V3.rotieren(a,pvektor[0],winkel,e);
                                                                pvektor[0]=e;
                                                                V3.rotieren(a,pvektor[1],winkel,e);
                                                                pvektor[1]=e;
                                                                V3.rotieren(a,pvektor[2],winkel,e);
                                                                pvektor[2]=e;
};
void _kugel::rotieren(const _vektor3<_tg>&a,const _tg winkel){
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> e;
                                                                V3.rotieren(a,pvektor[0],winkel,e);
                                                                pvektor[0]=e;
                                                                V3.rotieren(a,pvektor[1],winkel,e);
                                                                pvektor[1]=e;
                                                                V3.rotieren(a,pvektor[2],winkel,e);
                                                                pvektor[2]=e;
};
void _kugel::erzeugenschatten(_licht<_tg,_to>*licht,_tg laenge){
                                                                
                                                                _kugelschatten*it;
                                                                if(licht->schattenvolumen()){
                                                                 if(anfang(it))do{
                                                                  if(it->licht()==licht) return;
                                                                 }while(naechstes(it));
														 		 new _kugelschatten(this,pwelt,licht,laenge);
																};                                                                
};
void _kugel::loeschenschatten(){
                                                                this->_listebasis<_kugelschatten>::loeschen();
};
void _kugel::anfangschatten(){
                                                                _listebasis<_kugelschatten>::anfang(pschatteniterator);
};
void _kugel::naechsterschatten(){
                                                                if(pschatteniterator)pschatteniterator=pschatteniterator->_listenknotenbasis<_kugelschatten>::naechstes();
};
void _kugel::zeichnenschatten(_grafik*gra){
                                                                if(pschatteniterator)pschatteniterator->zeichnen(gra);
};
void _kugel::zeichnenschatten(_grafik*gra,_licht<_tg,_to>*lit){
                                                                _kugelschatten*it;
                                                                //------------------
                                                                if(anfang(it))do{
                                                                 if(it->licht()==lit) {
                                                                  it->zeichnen(gra);
                                                                  return;
                                                                 };
                                                                }while(naechstes(it));
};
void _kugel::zeichnen(_grafik*g){
			                                                   
			                                                    g->licht(1,true);//glEnable(GL_LIGHT1);
			                                                    g->licht(2,true);//glEnable(GL_LIGHT2);
			                                                    bool b=g->beleuchtung();//::glIsEnabled(GL_LIGHTING);
			                                                    g->beleuchtung(true);//glEnable(GL_LIGHTING);
			                                                    g->textur(false);//glDisable(GL_TEXTURE_2D);
			                                                    plicht[0]->ort(vl0);
			                                                    plicht[1]->ort(vl1);
			                                                    plicht[0]->binden(g,1);
			                                                    plicht[1]->binden(g,2);
			                                                    _vektor4<_to> col(15,15,15,1);
			                                                    /*float lc[4];
                                                                lc[0]=15;
                                                                lc[1]=15;
                                                                lc[2]=15;
                                                                lc[3]=1;
                                                                glMaterialfv(GL_FRONT,GL_SPECULAR,lc);	
                                                                */
                                                                g->materialglanz(col);
                                                                /*lc[0]=pfarbe[0];
                                                                lc[1]=pfarbe[1];
                                                                lc[2]=pfarbe[2];
                                                                lc[3]=1;
                                                                glMaterialfv(GL_FRONT,GL_DIFFUSE,lc);*/
                                                                g->materialfarbe(pfarbe);
                                                                g->materialglanzbreite(35);//glMaterialf(GL_FRONT,GL_SHININESS,(GLfloat)35.0f);
                                                                
                                                                
                                                                /*
                                                                glColor4f(pfarbe[0],pfarbe[1],pfarbe[2],1);
			                                                    glPushMatrix();
			                                                    //glFrontFace(GL_CW);
			                                                    glTranslatef(port[0],port[1],port[2]);
			                                                    glutSolidSphere(pradius, paufloesung, paufloesung);
			                                                    //glutSolidCylinder
			                                                    //glutSolidCylinder(pradius,2,paufloesung,1);
			                                                    */
			                                                    g->kugel(port,pfarbe,pradius,paufloesung,paufloesung);
			                                                    
			                                                    
			                                                    g->licht(1,false);//glDisable(GL_LIGHT1);
			                                                    g->licht(2,false);//glDisable(GL_LIGHT2);
			                                                    //if(b) glEnable(GL_LIGHTING); else glDisable(GL_LIGHTING);
			                                                    if(b) g->beleuchtung(true); else g->beleuchtung(false);
                                                                g->textur(true);//glEnable(GL_TEXTURE_2D);
			                                                    
			                                                    col.setzen(0,0,0,1);
			                                                    /*
                                                                lc[0]=0;
                                                                lc[1]=0;
                                                                lc[2]=0;
                                                                lc[3]=1;
                                                                glMaterialfv(GL_FRONT,GL_SPECULAR,lc);			                                                   
                                                                glMaterialfv(GL_FRONT,GL_DIFFUSE,lc);			                               
                                                                */
                                                                g->materialfarbe(col);
                                                                g->materialglanz(col);                    
                                                                g->materialglanzbreite(20);//glMaterialf(GL_FRONT,GL_SHININESS,(GLfloat)20.0f);
			                                                    //glFrontFace(GL_CCW);
			                                                    //glPopMatrix();                                     
			                                                    //*** DEBUG ***
			                                                    //g->zeichnen(port,port+pvektor[0],_vektor4<_to>(1,0,0,1));
			                                                    //g->zeichnen(port,port+pvektor[1],_vektor4<_to>(0,1,0,1));
			                                                    //g->zeichnen(port,port+pvektor[2],_vektor4<_to>(0,0,1,1));
			                                                    //*************
			                                                                                  
};
void _kugel::ort(const _vektor3<_tg>&o){
                                                                port=o;
                                                                aktualisieren();
};
_vektor3<_tg> _kugel::ort()const {
                                                                return(port);
};
_vektor4<_to> _kugel::farbe()const{
                                                                return(pfarbe);
};
void _kugel::farbe(const _vektor4<_to>&f){
                                                                pfarbe=f;
};
void _kugel::radius(const _tg r){
                                                                pradius=r;
                                                                aktualisieren();
};
_tg _kugel::radius()const{
                                                                return(pradius);
};
unsigned int _kugel::aufloesung()const{
                                                                return(paufloesung);
};
void _kugel::aktualisieren(){
                                                                _kugelschatten*kit;
                                                                //------------------ 
                                                                if(anfang(kit))do{
                                                                 kit->aktualisieren();
                                                                }while(naechstes(kit));
};
bool _kugel::laden(_dateispeicherbarbinaer*d){
																einhaengenspeicherung(d);
																ladenbeginn();
																d->laden(speichername());
																d->laden(pradius);
																d->laden(port);      
																d->laden(pvektor[0]);
																d->laden(pvektor[1]);
																d->laden(pvektor[2]);
																d->laden(pfarbe);     
																d->laden(vl0);
																d->laden(vl1);
																d->laden(paufloesung);
																return(true);
};
void _kugel::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																d->speichern(pradius);
																d->speichern(port);      
																d->speichern(pvektor[0]);
																d->speichern(pvektor[1]);
																d->speichern(pvektor[2]);
																d->speichern(pfarbe);     
																d->speichern(vl0);
																d->speichern(vl1);
																d->speichern(paufloesung);
};
bool _kugel::assoziieren(){
																if(zeigergeladen()){
																 loeschenzeiger();
																};
																return(true);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G 
//******************************************************************************************************************************************************************************************************
_weltdebug::_weltdebug(_welt*w,const _vektor4<_to> c):_listenknotenbasis<_weltdebug >(w){
                                                                pcolor=c;
                                                                pworld=w;
                                                                
};

_weltdebug::~_weltdebug(){
};

void _weltdebug::farbe(const _vektor4<_to> c){
                                                                pcolor=c;
};

_vektor4<_to> _weltdebug::farbe() const{
                                                                return(pcolor);
};

_welt* _weltdebug::welt(){
                                                                return(pworld);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G P U N K T
//******************************************************************************************************************************************************************************************************

_weltdebugpunkt::_weltdebugpunkt(_welt*w,const _vektor3<_tg> x,const _vektor4<_to> c):_weltdebug(w,c){
};

_weltdebugpunkt::~_weltdebugpunkt(){
};

void _weltdebugpunkt::transformieren(_grafik*gra,_kamera<_tg>*cam){
                                                                plocusperspective=plocus;
                                                                cam->transformierenparallel(plocusperspective);
                                                                //cam->transformierenperspektive(plocuspersective);
                                                                //gra->transformieren(plocuspersective);
};

void _weltdebugpunkt::zeichnen(_grafik*gra){
                                                                if(welt()->eigenetransformation()){
                                                                 gra->zeichnen(plocusperspective,farbe());
                                                                }else{
                                                                 gra->zeichnen(plocus,farbe());
                                                                };
};                                                                

void _weltdebugpunkt::animieren(){
};

void _weltdebugpunkt::ort(const _vektor3<_tg> p){
                                                                plocus=p;
};

_vektor3<_tg> _weltdebugpunkt::ort() const{
                                                                return(plocus);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G L I N I E 
//******************************************************************************************************************************************************************************************************

_weltdebuglinie::_weltdebuglinie(_welt*w,const _vektor3<_tg> x0,const _vektor3<_tg> x1,const _vektor4<_to> c):_weltdebug(w,c){
                                                                plocus[0]=x0;
                                                                plocus[1]=x1;
};

_weltdebuglinie::~_weltdebuglinie(){
};

void _weltdebuglinie::transformieren(_grafik*gra,_kamera<_tg>*cam){
                                                                unsigned int i;
                                                                //--------------
                                                                for(i=0;i<2;i++){
                                                                 plocusperspective[i]=plocus[i];
                                                                 cam->transformierenparallel(plocusperspective[i]);
                                                                 //cam->transformierenperspektive(plocusperspective[i]);
                                                                 //gra->transformieren(plocusperspective[i]);
                                                                };
};

void _weltdebuglinie::zeichnen(_grafik*gra){
                                                               // gra->textur(false);
                                                               // gra->transparenzadditiv();
                                                                if(welt()->eigenetransformation()){
                                                                 gra->zeichnen(plocusperspective[0],plocusperspective[1],farbe());
                                                                }else{
                                                                 gra->zeichnen(plocus[0],plocus[1],farbe());
                                                                };
};                                                                

void _weltdebuglinie::animieren(){
};

void _weltdebuglinie::ort(const unsigned int i,const _vektor3<_tg> p){
                                                                if(i==0) plocus[0]=p; else plocus[1]=p;
};

_vektor3<_tg> _weltdebuglinie::ort(const unsigned int i) const{
                                                                if(i==0) return(plocus[0]); else return(plocus[1]);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G E B E N E
//******************************************************************************************************************************************************************************************************

_weltdebugebene::_weltdebugebene(_welt*w,const _vektor3<_tg> o,const _vektor3<_tg> v0,const _vektor3<_tg> v1,const _tg ilen,const _vektor4<_to> c):_weltdebug(w,c){
                                                                _vektor3<_tg> h;
                                                                //-------------
                                                                plocus=o;
                                                                pvec0=v0;
                                                                pvec1=v1;
                                                                plen=ilen;
                                                                h=o - v0*plen - v1*plen;
                                                                plist.einhaengen(new _vektor3<_tg>(h));
                                                                h=o + v0*plen - v1*plen;
                                                                plist.einhaengen(new _vektor3<_tg>(h));
                                                                h=o + v0*plen + v1*plen;
                                                                plist.einhaengen(new _vektor3<_tg>(h));
                                                                h=o - v0*plen + v1*plen;
                                                                plist.einhaengen(new _vektor3<_tg>(h));
                                                                
};

_weltdebugebene::~_weltdebugebene(){
                                                                pplist.loeschen();
                                                                plist.loeschen();
};

void _weltdebugebene::transformieren(_grafik*gra,_kamera<_tg>*cam){
                                                                //unsigned int i;
                                                                _listenknoten<_vektor3<_tg> >*vit;
                                                                _vektor3<_tg>*vn;
                                                                //--------------
                                                                pplist.loeschen();
                                                                if(plist.anfang(vit))do{
                                                                 vn=new _vektor3<_tg>(*vit->objekt());
                                                                 pplist.einhaengen(vn);
                                                                 cam->transformierenparallel(*vn);
                                                                }while(plist.naechstes(vit));
                                                                //for(i=0;i<2;i++){
                                                                 //plocusperspective[i]=plocus[i];
                                                                 //cam->transformierenparallel(plocusperspective[i]);
                                                                 //cam->transformierenperspektive(plocusperspective[i]);
                                                                 //gra->transformieren(plocusperspective[i]);
                                                                //};
};

void _weltdebugebene::zeichnen(_grafik*gra){
                                                                _listenknoten<_vektor3<_tg> >*vit0;
                                                                _listenknoten<_vektor3<_tg> >*vstart;
                                                                _listenknoten<_vektor3<_tg> >*vit1;
                                                                //---------------------------
                                                                if(welt()->eigenetransformation()){
                                                                 if(pplist.anfang(vstart)){
                                                                  vit0=vstart->naechstes();
                                                                  vit1=vit0->naechstes();
                                                                  do{
                                                                   gra->zeichnen(*vstart->objekt(),*vit0->objekt(),*vit1->objekt(),farbe(),farbe(),farbe());
                                                                   vit0=vit1;
                                                                   vit1=vit1->naechstes();
                                                                  }while(vit0!=vstart);
                                                                 };
                                                                }else{
                                                                 if(plist.anfang(vstart)){
                                                                  vit0=vstart->naechstes();
                                                                  vit1=vit0->naechstes();
                                                                  do{
                                                                   gra->zeichnen(*vstart->objekt(),*vit0->objekt(),*vit1->objekt(),farbe(),farbe(),farbe());
                                                                   vit0=vit1;
                                                                   vit1=vit1->naechstes();
                                                                  }while(vit0!=vstart);
                                                                 };
                                                                };
                                                                
                                                                //gra->zeichnen(plocusperspective[0],plocusperspective[1],farbe());
};                                                                

void _weltdebugebene::animieren(){
};

void _weltdebugebene::ort(const _vektor3<_tg> p){
                                                                plocus=p;
};

_vektor3<_tg> _weltdebugebene::ort() const{
                                                                return(plocus);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G K U G E L 
//******************************************************************************************************************************************************************************************************

_weltdebugkugel::_weltdebugkugel(_welt*w,const _vektor3<_tg> x,const _tg rad,const _vektor4<_to> c):_weltdebug(w,c){
                                                                pradius=rad;
                                                                ::setzen(plocus,x);
                                                                ::setzen(pnormale,0.0,1.0,0.0);
                                                                ::setzen(prichtung[0],1.0,0.0,0.0);
                                                                ::kreuzprodukt(prichtung[1],prichtung[0],pnormale);
                                                                ::setzen(pdrehimpuls,2.0,0.0,0.0);
                                                                
                                                                ppunktanzahl=0;
                                                                aktualisieren();
                                                                
};

_weltdebugkugel::~_weltdebugkugel(){
};
void _weltdebugkugel::aktualisieren(){
                                                                _tg e[3];
                                                                _tg a,b;
                                                                int i=0;
                                                                _tg tb=40.0f;
                                                                _tg db=1.0f/tb;
                                                                //----------------
                                                                for(a=0;a<1;a+=1.0f/20.0f){
                                                                 for(b=-0.25;b<0.25;b+=db){
                                                                  if(i<4000) {
                                                                   ppunkt[i][0]=cos(a*360*_ph);
                                                                   ppunkt[i][1]=0;
                                                                   ppunkt[i][2]=sin(a*360*_ph);
                                                                   ::rotieren(prichtung[0],ppunkt[i],b*360,e);
                                                                   ::multiplizieren(e,pradius);
                                                                   ::setzen(ppunkt[i],e);
                                                                   i++;
                                                                   ppunktanzahl++;
                                                                  };
                                                                 };
                                                                };
};
void _weltdebugkugel::transformieren(_grafik*gra,_kamera<_tg>*cam){
                                                                unsigned int i;
                                                                //-----------------
                                                                for(i=0;i<ppunktanzahl;i++){
                                                                // ppunktpers[i]=ppunkt[i]+plocus;
                                                                // cam->transformierenparallel(ppunktpers[i]);
                                                                };
                                                                //cam->transformierenperspektive(plocuspersective);
                                                                //gra->transformieren(plocuspersective);
};

void _weltdebugkugel::animieren(){
                                                                _tg e[3];
                                                                _tg l=::magnitude(pdrehimpuls);
                                                                ::rotieren(pdrehimpuls,prichtung[0],l,e);
                                                                ::normalisieren(e);
                                                                ::setzen(prichtung[0],e);
                                                                ::rotieren(pdrehimpuls,pnormale,l,e);
                                                                ::normalisieren(e);
                                                                ::setzen(pnormale,e);
                                                                ::kreuzprodukt(prichtung[1],prichtung[0],pnormale);
                                                             //   ::kreuzprodukt(prichtung[0],prichtung[1],pnormale);
};

void _weltdebugkugel::zeichnen(_grafik*gra){
                                                                unsigned int i,j;
                                                                _to c[3];
                                                                _tg e[3];
                                                                _tg r[3];
                                                                //-------------
                                                                c[0]=farbe()[0];
                                                                c[1]=farbe()[1];
                                                                c[2]=farbe()[2];
                                                                if(welt()->eigenetransformation()){
                                                                 for(i=0;i<ppunktanzahl;i++){
                                                                  gra->zeichnen(ppunktpers[i],c);
                                                                 };
                                                                }else{
                                                                 i=0;
                                                                 for(i=0;i<ppunktanzahl;i++){
                                                                  j=i+1;
                                                                  if(j==ppunktanzahl) j=0;
                                                                  e[0]=plocus[0]+ppunkt[i][0]*prichtung[0][0]+ppunkt[i][1]*pnormale[0]+ppunkt[i][2]*prichtung[1][0];
                                                                  e[1]=plocus[1]+ppunkt[i][0]*prichtung[0][1]+ppunkt[i][1]*pnormale[1]+ppunkt[i][2]*prichtung[1][1];
                                                                  e[2]=plocus[2]+ppunkt[i][0]*prichtung[0][2]+ppunkt[i][1]*pnormale[2]+ppunkt[i][2]*prichtung[1][2];
                                                                  r[0]=plocus[0]+ppunkt[j][0]*prichtung[0][0]+ppunkt[j][1]*pnormale[0]+ppunkt[j][2]*prichtung[1][0];
                                                                  r[1]=plocus[1]+ppunkt[j][0]*prichtung[0][1]+ppunkt[j][1]*pnormale[1]+ppunkt[j][2]*prichtung[1][1];
                                                                  r[2]=plocus[2]+ppunkt[j][0]*prichtung[0][2]+ppunkt[j][1]*pnormale[2]+ppunkt[j][2]*prichtung[1][2];
                                                                  gra->zeichnen(e,r,c);
                                                                  
                                                                 };
                                                                 _vektor3<_tg> pl0;
                                                                 _vektor3<_tg> pl1;
                                                                 pl0.setzen(plocus[0],plocus[1],plocus[2]);
                                                                 pl1.setzen(plocus[0]+pdrehimpuls[0],plocus[1]+pdrehimpuls[1],plocus[2]+pdrehimpuls[2]);
                                                                 gra->zeichnen(pl0,pl1,farbe());
                                                                };
                                                                
};                                                                

void _weltdebugkugel::ort(const _vektor3<_tg> p){
                                                                ::setzen(plocus,p);
};

_vektor3<_tg> _weltdebugkugel::ort() const{
                                                                _vektor3<_tg> p;
                                                                p.setzen(plocus[0],plocus[1],plocus[2]);
                                                                return(p);
};
void _weltdebugkugel::radius(const _tg r){
                                                                pradius=r;
                                                                aktualisieren();
};
_tg _weltdebugkugel::radius()const{
                                                                return(pradius);
};

void _weltdebugkugel::drehimpuls(const _vektor3<_tg> a){
                                                                ::setzen(pdrehimpuls,a);
};

void _weltdebugkugel::addierendrehimpuls(const _vektor3<_tg> a){
                                                                ::addieren<_tg>(pdrehimpuls,a);
};

void _weltdebugkugel::multiplizierendrehimpuls(const _tg a){
                                                                ::multiplizieren(pdrehimpuls,a);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G Z Y L I N D E R
//******************************************************************************************************************************************************************************************************
_weltdebugzylinder::_weltdebugzylinder(_welt*w,const _vektor3<_tg> x,const _vektor3<_tg> v,const _tg rad,const _vektor4<_to> c):_weltdebug(w,c){
                                                                pradius=rad;
                                                                pvektor=v;
                                                                plocus=x;
                                                                pnormale.setzen(0,1,0);
                                                                prichtung[0].setzen(1,0,0);
                                                                prichtung[1].setzen(0,0,1);
                                                                ppunktanzahl=0;
                                                                aktualisieren();
};




_weltdebugzylinder::~_weltdebugzylinder(){
};

void _weltdebugzylinder::aktualisieren(){
                                                                
                                                                _vektor3<_tg> e;
                                                                _tg a,b;
                                                                int i=0;
                                                                //----------------
                                                                for(a=0;a<1;a+=1.0f/40.0f){
                                                                 for(b=0;b<1;b+=1.0f/80.0f){
                                                                  if(i<4000) {
                                                                   ppunkt[i].setzen(cos(a*360*_ph)*pradius,0,sin(a*360*_ph)*pradius);
                                                                   ppunkt[i]+=pvektor*b;
                                                                   i++;
                                                                   ppunktanzahl++;
                                                                  };
                                                                 };
                                                                };

};
void _weltdebugzylinder::transformieren(_grafik*gra,_kamera<_tg>*cam){
                                                                unsigned int i;
                                                                //-----------------
                                                                for(i=0;i<ppunktanzahl;i++){
                                                                 ppunktpers[i]=ppunkt[i]+plocus;
                                                                 cam->transformierenparallel(ppunktpers[i]);
                                                                };
                                                                //cam->transformierenperspektive(plocuspersective);
                                                                //gra->transformieren(plocuspersective);
};

void _weltdebugzylinder::zeichnen(_grafik*gra){
                                                                unsigned int i;
                                                                //-----------------
                                                                if(welt()->eigenetransformation()){
                                                                 for(i=0;i<ppunktanzahl;i++){
                                                                  gra->zeichnen(ppunktpers[i],farbe());
                                                                 };
                                                                }else{
                                                                 for(i=0;i<ppunktanzahl;i++){
                                                                  gra->zeichnen(plocus+ppunkt[i],farbe());
                                                                 };
                                                                };
};                                                                

void _weltdebugzylinder::animieren(){
};

void _weltdebugzylinder::ort(const _vektor3<_tg> p){
                                                                plocus=p;
};

_vektor3<_tg> _weltdebugzylinder::ort() const{
                                                                return(pvektor);
};
void _weltdebugzylinder::vektor(const _vektor3<_tg> p){
                                                                pvektor=p;
                                                                aktualisieren();
};

_vektor3<_tg> _weltdebugzylinder::vektor() const{
                                                                return(plocus);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G P F E I L
//******************************************************************************************************************************************************************************************************

_weltdebugpfeil::_weltdebugpfeil(_welt*w,const _vektor3<_tg> x0,const _vektor3<_tg> x1,const _tg l,const _tg b,const _vektor4<_to> c):_weltdebug(w,c){
                                                                plocus[0]=x0;
                                                                plocus[1]=x1;
                                                                plaenge=l;
                                                                pbreite=b;
                                                                pcolor2=farbe()*0.5;
                                                                aktualisieren();
                                                                
                                                                
};

_weltdebugpfeil::~_weltdebugpfeil(){
};

void _weltdebugpfeil::aktualisieren(){
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> vo;
                                                                _vektor3<_tg> vu;
                                                                _vektor3<_tg> vi;
                                                                _vektoranalysis3<_tg> V3;
                                                                v=plocus[1]-plocus[0];
                                                                v.normalisieren();
                                                                V3.berechnenorthogonalenvektor(v,vo);
                                                                vu=vo%v;
                                                                vi=-v;
                                                                parrs[0]=plocus[1]+(vi*plaenge)+(vo*pbreite);
                                                                parrs[1]=plocus[1]+(vi*plaenge)-(vo*pbreite);
                                                                parrs[2]=plocus[1]+(vi*plaenge)+(vu*pbreite);
                                                                parrs[3]=plocus[1]+(vi*plaenge)-(vu*pbreite);
};

void _weltdebugpfeil::transformieren(_grafik*gra,_kamera<_tg>*cam){
                                                                unsigned int i;
                                                                //--------------
                                                                for(i=0;i<2;i++){
                                                                 plocusperspective[i]=plocus[i];
                                                                 cam->transformierenparallel(plocusperspective[i]);
                                                               //  cam->transformierenperspektive(plocusperspective[i]);
                                                               //  gra->transformieren(plocusperspective[i]);
                                                                };
                                                                for(i=0;i<4;i++){
                                                                 parrsperspective[i]=parrs[i];
                                                                 cam->transformierenparallel(parrsperspective[i]);
                                                                // cam->transformierenperspektive(parrsperspective[i]);
                                                                // gra->transformieren(parrsperspective[i]);
                                                                };

};

void _weltdebugpfeil::zeichnen(_grafik*gra){
                                            
                                                                pcol1=pcolor2;        
                                                                
                                                                if(welt()->eigenetransformation()){
                                                                 gra->zeichnen(plocusperspective[0],plocusperspective[1],farbe(),pcol1);
                                                                 gra->zeichnen(plocusperspective[1],parrsperspective[0],farbe(),pcol1);
                                                                 gra->zeichnen(plocusperspective[1],parrsperspective[1],farbe(),pcol1);
                                                                 gra->zeichnen(plocusperspective[1],parrsperspective[2],farbe(),pcol1);
                                                                 gra->zeichnen(plocusperspective[1],parrsperspective[3],farbe(),pcol1);
                                                                }else{
                                                                 gra->zeichnen(plocus[0],plocus[1],farbe(),pcol1);
                                                                 gra->zeichnen(plocus[1],parrs[0],farbe(),pcol1);
                                                                 gra->zeichnen(plocus[1],parrs[1],farbe(),pcol1);
                                                                 gra->zeichnen(plocus[1],parrs[2],farbe(),pcol1);
                                                                 gra->zeichnen(plocus[1],parrs[3],farbe(),pcol1);
                                                                };
};                                                                

void _weltdebugpfeil::animieren(){
};

void _weltdebugpfeil::ort(const unsigned int i,const _vektor3<_tg>&p){
                                                                if(i==0) plocus[0]=p; else plocus[1]=p;
                                                                aktualisieren();
};
void _weltdebugpfeil::ort(const _vektor3<_tg>&p0,const _vektor3<_tg>&p1){
                                                                plocus[0]=p0; 
                                                                plocus[1]=p1;
                                                                aktualisieren();
};

_vektor3<_tg> _weltdebugpfeil::ort(const unsigned int i) const{
                                                                if(i==0) return(plocus[0]); else return(plocus[1]);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G K R E U Z
//******************************************************************************************************************************************************************************************************

_weltdebugkreuz::_weltdebugkreuz(_welt*w,const _vektor3<_tg> x,const _tg rad,const _vektor4<_to> c):_weltdebug(w,c){
                                                                plocus=x;
                                                                pradius=rad;
                                                                aktualisieren();
                                                                
                                                               // 
};

_weltdebugkreuz::~_weltdebugkreuz(){
};

void _weltdebugkreuz::aktualisieren(){
                                                                _vektor3<_tg> h;
                                                                //unten links,vorne  ---  oben,rechts,hinten
                                                                h.setzen(-1,-1,-1);h.normalisieren();
                                                                h*=pradius;
                                                                pnetz[0]=h+plocus;
                                                                h.setzen(+1,+1,+1);h.normalisieren();
                                                                h*=pradius;
                                                                pnetz[1]=h+plocus;
                                                                //unten,rechts,vorne ---  oben,links,hinten
                                                                h.setzen(+1,-1,-1);h.normalisieren();
                                                                h*=pradius;
                                                                pnetz[2]=h+plocus;
                                                                h.setzen(-1,+1,+1);h.normalisieren();
                                                                h*=pradius;
                                                                pnetz[3]=h+plocus;
                                                                //unten,rechts,hinten ---  oben,links,vorne
                                                                h.setzen(+1,-1,+1);h.normalisieren();
                                                                h*=pradius;
                                                                pnetz[4]=h+plocus;
                                                                h.setzen(-1,+1,-1);h.normalisieren();
                                                                h*=pradius;
                                                                pnetz[5]=h+plocus;
                                                                //unten,links,hinten ---  oben,rechts,vorne
                                                                h.setzen(-1,-1,+1);h.normalisieren();
                                                                h*=pradius;
                                                                pnetz[6]=h+plocus;
                                                                h.setzen(+1,+1,-1);h.normalisieren();
                                                                h*=pradius;
                                                                pnetz[7]=h+plocus;
};

void _weltdebugkreuz::transformieren(_grafik*gra,_kamera<_tg>*cam){
                                                                unsigned int i;
                                                                //--------------
                                                                plocusperspective=plocus;
                                                                cam->transformierenparallel(plocusperspective);
                                                                //cam->transformierenperspektive(plocusperspective);
                                                                //gra->transformieren(plocusperspective);
                                                                for(i=0;i<8;i++){
                                                                 pnetzperspective[i]=pnetz[i];
                                                                 cam->transformierenparallel(pnetzperspective[i]);
                                                                 //cam->transformierenperspektive(pnetzperspective[i]);
                                                                 //gra->transformieren(pnetzperspective[i]);
                                                                };
};

void _weltdebugkreuz::zeichnen(_grafik*gra){
                                                                if(welt()->eigenetransformation()){
                                                                 gra->zeichnen(pnetzperspective[0],pnetzperspective[1],farbe());
                                                                 gra->zeichnen(pnetzperspective[2],pnetzperspective[3],farbe());
                                                                 gra->zeichnen(pnetzperspective[4],pnetzperspective[5],farbe());
                                                                 gra->zeichnen(pnetzperspective[6],pnetzperspective[7],farbe());
                                                                }else{
                                                                 gra->zeichnen(pnetz[0],pnetz[1],farbe());
                                                                 gra->zeichnen(pnetz[2],pnetz[3],farbe());
                                                                 gra->zeichnen(pnetz[4],pnetz[5],farbe());
                                                                 gra->zeichnen(pnetz[6],pnetz[7],farbe());
                                                                 //L->l("dddddddddddd ");
                                                                };
};                                                                

void _weltdebugkreuz::animieren(){
};

void _weltdebugkreuz::ort(const _vektor3<_tg> p){
                                                                plocus=p;
                                                                aktualisieren();
};

_vektor3<_tg> _weltdebugkreuz::ort() const{
                                                                return(plocus);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G T E X T 
//******************************************************************************************************************************************************************************************************
_weltdebugtext::_weltdebugtext(_welt*w,const _zeichenkette<char> s,const _vektor2<_tg> x0,const _vektor4<_to> c):_weltdebug(w,c){
                                                                pzeichnen2d=true;
                                                                plocus.setzen(x0[0],x0[1],0);
                                                                ptext=s;
};

_weltdebugtext::_weltdebugtext(_welt*w,const _zeichenkette<char> s,const _vektor3<_tg> x0,const _vektor3<_tg> a,const _vektor3<_tg> b,const _vektor4<_to> c):_weltdebug(w,c){
                                                                pzeichnen2d=false;
                                                                plocus=x0;
                                                                pa=a;
                                                                pb=b;
                                                                ptext=s;
};

_weltdebugtext::~_weltdebugtext(){
                                                                clearlocusperspectivelist();
};

void _weltdebugtext::clearlocusperspectivelist(){
                                                                _listenknoten<_liste<_vektor3<_tg> > >*lit;
                                                                //--------------------------
                                                                if(plocuspers.anfang(lit))do{
                                                                 lit->objekt()->loeschen();
                                                                }while(plocuspers.naechstes(lit));
                                                                plocuspers.loeschen();
};


void _weltdebugtext::transformieren(_grafik*gra,_kamera<_tg>*cam){
                                                                unsigned int i;
                                                                _vektor3<_tg>*v;
                                                                _vektor3<_tg> o;
                                                                _weltdebugzeichensatzchar*c;
                                                                _weltdebugzeichensatzseg*sit;
                                                                _tg w;
                                                                _vektor3<_tg> pos;
                                                                _vektor3<_tg> ac;
                                                                _vektor3<_tg> bc;
                                                                _liste<_vektor2<_tg> >*vlist;
                                                                _listenknoten<_vektor2<_tg> >*vit;
                                                                _liste<_vektor3<_tg> >*il;
                                                                //--------------
                                                                clearlocusperspectivelist();
                                                                w=0;
                                                                for(i=0;i<ptext.groesse();i++){
                                                                 c=welt()->debugzeichensatz()->character(int(ptext[i]));
                                                                 if(c){
                                                                  w+=c->breite()+3;
                                                                 };
                                                                };
                                                                
                                                                pos=plocus;
                                                                for(i=0;i<ptext.groesse();i++){
                                                                 c=welt()->debugzeichensatz()->character(int(ptext[i]));
                                                                 if(c){
                                                                  ac=pa* ((c->breite()+3.0f)/w) * _tg(1.0f/(c->breite()+3));
                                                                  bc=pb* _tg(1.0f/27.0f);
                                                                  if(c->anfang(sit))do{
                                                                   vlist=sit->liste();
                                                                   il=new _liste<_vektor3<_tg> >();
                                                                   plocuspers.einhaengen(il);
                                                                   if(vlist->anfang(vit))do{
                                                                    o=pos + ac* (*vit->objekt())[0] + bc* (*vit->objekt())[1];
                                                                    //cam->transformierenparallel(o);
                                                                    v=new _vektor3<_tg>(o);
                                                                    il->einhaengen(v);
                                                                   }while(vlist->naechstes(vit));
                                                                  }while(c->naechstes(sit));
                                                                 
                                                                  pos+=pa*((c->breite()+3.0f)/w);
                                                                 };
                                                                };
};

void _weltdebugtext::zeichnen(_grafik*gra){
                                                                if(pzeichnen2d) zeichnen2d(gra); else {
                                                                _listenknoten<_vektor3<_tg> >*vit;
                                                                _listenknoten<_vektor3<_tg> >*vin;
                                                                _listenknoten<_vektor3<_tg> >*start;
                                                                _listenknoten<_liste<_vektor3<_tg> > >*lit;
                                                                _liste<_vektor3<_tg> >*il;
                                                                //---------------------------
                                                                if(welt()->eigenetransformation()){
                                                                 if(plocuspers.anfang(lit))do{
                                                                  il=lit->objekt();
                                                                  il->anfang(start);
                                                                  if(il->anfang(vit))do{
                                                                   vin=vit->naechstes();
                                                                   if(vin!=start){
                                                                    gra->zeichnen(*vit->objekt(),*vin->objekt(),farbe());
                                                                   };
                                                                  }while(il->naechstes(vit));
                                                                 }while(plocuspers.naechstes(lit));
                                                                }else{
                                                               
                                                                 unsigned int i;
                                                                 _vektor3<_tg>*v;
                                                                 _vektor3<_tg> o;
                                                                 _weltdebugzeichensatzchar*c;
                                                                 _weltdebugzeichensatzseg*sit;
                                                                 _tg w;
                                                                 _vektor3<_tg> pos;
                                                                 _vektor3<_tg> ac;
                                                                 _vektor3<_tg> bc;
                                                                 _liste<_vektor2<_tg> >*vlist;
                                                                 _listenknoten<_vektor2<_tg> >*vit;
                                                                 _listenknoten<_vektor3<_tg> >*vit3;
                                                                 _liste<_vektor3<_tg> >*il;
                                                                 //--------------
                                                                 clearlocusperspectivelist();
                                                                 w=0;
                                                                 for(i=0;i<ptext.groesse();i++){
                                                                  c=welt()->debugzeichensatz()->character(int(ptext[i]));
                                                                  if(c){
                                                                   w+=c->breite()+3;
                                                                  };
                                                                 };
                                                                 pos=plocus;
                                                                 for(i=0;i<ptext.groesse();i++){
                                                                  c=welt()->debugzeichensatz()->character(int(ptext[i]));
                                                                  if(c){
                                                                   ac=pa* ((c->breite()+3.0f)/w) * _tg(1.0f/(c->breite()+3));
                                                                   bc=pb* _tg(1.0f/27.0f);
                                                                   if(c->anfang(sit))do{
                                                                    vlist=sit->liste();
                                                                    il=new _liste<_vektor3<_tg> >();
                                                                    plocuspers.einhaengen(il);
                                                                    if(vlist->anfang(vit))do{
                                                                     o=pos + ac* (*vit->objekt())[0] + bc* (*vit->objekt())[1];
                                                                     v=new _vektor3<_tg>(o);
                                                                     il->einhaengen(v);
                                                                    }while(vlist->naechstes(vit));
                                                                   }while(c->naechstes(sit));
                                                                  
                                                                   pos+=pa*((c->breite()+3.0f)/w);
                                                                  };
                                                                 };
                                                                 if(plocuspers.anfang(lit))do{
                                                                  il=lit->objekt();
                                                                  il->anfang(start);
                                                                  if(il->anfang(vit3))do{
                                                                   vin=vit3->naechstes();
                                                                   if(vin!=start){
                                                                    gra->zeichnen(*vit3->objekt(),*vin->objekt(),farbe());
                                                                   };
                                                                  }while(il->naechstes(vit3));
                                                                 }while(plocuspers.naechstes(lit));
                                                                };
                                                                };
};                                                              
void _weltdebugtext::zeichnen2d(_grafik*gra){/*
                                                                _vektor4<_to> col;
                                                                _vektor3<_tg> ac;
                                                                _vektor3<_tg> bc;
                                                                _weltdebugzeichensatzchar*c;
                                                                _weltdebugzeichensatzseg*sit;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> pos;
                                                                _liste<_vektor2<_tg> >*vlist;
                                                                _listenknoten<_vektor2<_tg> >*vit;
                                                                //-----------------------------------------
                                glMatrixMode(GL_PROJECTION);                                  
                                glPushMatrix();
                                glLoadIdentity();         
                                glMatrixMode(GL_MODELVIEW);  
                                glPushMatrix();
                                glLoadIdentity();  
	                                                            glOrtho(0, gra->groessex(), 0,gra->groessey(), -100, 100);
                                                                glDisable(GL_DEPTH_TEST);
	                                                            glDisable(GL_STENCIL_TEST);
	                                                            glDisable(GL_BLEND);
	                                                            glDisable(GL_CULL_FACE);
	                                                            glDisable(GL_LIGHTING);
                                	                            glDisable(GL_TEXTURE_2D);	                                                            
		                                                        pos=plocus;
		                                                        _tg s=1;//0.0007;
		                                                        ac.setzen(s,0,0);
                                                                for(unsigned int i=0;i<ptext.groesse();i++){
                                                                 c=welt()->debugzeichensatz()->character(int(ptext[i]));
                                                                 if(c){
                          
                                                                 if(c->anfang(sit))do{
                                                                 glBegin(GL_LINE_STRIP);
                                                                  vlist=sit->liste();
                                                                  if(vlist->anfang(vit))do{
                                                                   o.setzen((*vit->objekt())[0]*s,(*vit->objekt())[1]*s,0);
                                                                   o+=pos;
                                                                   glColor4fv(farbe().daten());
                                                                   glVertex3dv(o.daten());
                                                                  }while(vlist->naechstes(vit));
                                                                  glEnd();
                                                                 }while(c->naechstes(sit));
                                                                 pos+=ac*(c->breite()+s);
                                                                 };
                                                                };		                                                        
	                                                            glDisable(GL_BLEND);
	                                                            glEnable(GL_CULL_FACE);
                                glMatrixMode(GL_PROJECTION);                                  
                                glPopMatrix();
                                glMatrixMode(GL_MODELVIEW);  
                                glPopMatrix();*/
};
void _weltdebugtext::animieren(){
};

void _weltdebugtext::ort(const _vektor3<_tg> p){
                                                                plocus=p;
};
void _weltdebugtext::text(const _zeichenkette<char>&t){
                                                                ptext=t;
};
void _weltdebugtext::text(const int i){
                                                                char buf[128];
                                                                _itoa(i,buf,10);
                                                                ptext=buf;
};

_vektor3<_tg> _weltdebugtext::ort() const{
                                                                return(plocus);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G S C H I R M
//******************************************************************************************************************************************************************************************************

_weltdebugschirm::_weltdebugschirm(_welt*w,const _vektor3<_tg> x0,const _vektor3<_tg> x1,_tg sx,_tg sy,const _vektor4<_to> c):_weltdebug(w,c){
                                                                plocus[0]=x0;//screenkoordinaten fenster
                                                                plocus[1]=x1;
                                                                psx=sx;//zeichenskalierung
                                                                psy=sy;
                                                                pxoffs=4;
                                                                pyoffs=4;
};

_weltdebugschirm::~_weltdebugschirm(){
};

void _weltdebugschirm::loeschen(){
                                                                ptextlist.loeschen();
};
void _weltdebugschirm::schreiben(const _zeichenkette<char> t){
                                                                _vektor4<_to> col(1,1,1,1);
                                                                schreiben(t,col);
};
void _weltdebugschirm::schreiben(const _zeichenkette<char> t,const double f){
                                                                _vektor4<_to> col(1,1,1,1);
                                                                schreiben(t,f,col);
};
void _weltdebugschirm::schreiben(const _zeichenkette<char> t,const int i){
                                                                _vektor4<_to> col(1,1,1,1);
                                                                schreiben(t,i,col);
};
void _weltdebugschirm::schreiben(const _zeichenkette<char> t,_vektor3<double> v){
                                                                _vektor4<_to> col(1,1,1,1);
                                                                schreiben(t,v,col);
};
void _weltdebugschirm::schreiben(const _zeichenkette<char> t,const _vektor4<_to> col){
                                                                _tg h;
                                                                _vektor3<_tg> d;
                                                                _tg bc;
                                                                _weltdebugschirmtext*tit;
                                                                //-------
                                                                //bc=1.setzen(0,1,0);
                                                                d=plocus[0]-plocus[1];
                                                                bc=fabs(d[1]);
                                                                bc*=(1.0f/(psy*(29.0f+pyoffs)));
                                                                new _weltdebugschirmtext(this,&ptextlist,t,col);
                                                                if(ptextlist.anzahl()>0){
                                                                 h=bc*(29+pyoffs)*_tg(ptextlist.anzahl());
                                                                 while(h>fabs(d[1])){
                                                                  //L->schreiben("dbnsdfdsmnnfsdn h=",h);
                                                                  //L->schreiben("dbnsdfdsmnnfsdn d1=",fabs(d[1]));
                                                                  ptextlist.anfang(tit);
                                                                  tit->loeschmarkierung(true);
                                                                  ptextlist.rotierennaechstes();
                                                                  ptextlist.loeschenmarkiert();
                                                                  h=bc*(29+pyoffs)*_tg(ptextlist.anzahl());
                                                                 };
                                                                };
                                                                
};

void _weltdebugschirm::schreiben(const _zeichenkette<char> t,const double f,const _vektor4<_to> col){
                                                                char c[128];
                                                                _zeichenkette<char> h;
                                                                //----------
                                                                _gcvt(f,100,c);
                                                                h=t+c;
                                                                schreiben(h,col);
};

void _weltdebugschirm::schreiben(const _zeichenkette<char> t,const int i,const _vektor4<_to> col){
                                                                _zeichenkette<char> h;
                                                                char c[128];
                                                                //-------------
                                                                _itoa(i,c,10);
                                                                h+=t;
                                                                h+=c;
                                                                schreiben(h,col);
};
void _weltdebugschirm::schreiben(const _zeichenkette<char> t,_vektor3<double> v,const _vektor4<_to> col){
                                                                _zeichenkette<char> h;
                                                                char c[128];
                                                                unsigned int i;
                                                                //-------------
                                                          
                                                                h=t;
                                                                h+="[";
                                                                for(i=0;i<3;i++){
                                                                 _gcvt(v[i],10,c);
                                                                 h+=c;
                                                                 if(i<(3-1)){
                                                                  h+="; ";
                                                                 };
                                                                };
                                                                h+="]";
                                                                schreiben(h,col);
};



void _weltdebugschirm::transformieren(_grafik*gra,_kamera<_tg>*cam){
                                                                _vektor3<_tg> pos;
                                                                _weltdebugschirmtext*tit;
                                                                _vektor3<_tg> yo;
                                                                //--------------
                                                                yo.setzen(0,1,0);
                                                                yo*=fabs(plocus[0][1]-plocus[1][1]);
                                                                yo*=pyoffs/(2+pyoffs+psy*(29.0f+pyoffs));
                                                                pos.setzen(plocus[0][0],plocus[1][1],1);
                                                                pos-=yo;
                                                                if(ptextlist.anfang(tit))do{
                                                                 tit->transformieren(gra,cam,pos);
                                                                 //pos-=yo*(27+pyoffs);
                                                                }while(ptextlist.naechstes(tit));
                                                                
};

void _weltdebugschirm::zeichnen(_grafik*gra){
                                                                _matrix44<float> mw;
                                                                _matrix44<float> mm;
                                                                _matrix44<float> mp;
                                                                _weltdebugschirmtext*tit;
                                                                _vektor4<_to> col;
                                                                _vektor3<_tg> l0;
                                                                _vektor3<_tg> l1;
                                                                _vektor3<_tg> l2;
                                                                _vektor3<_tg> l3;
                                                                //_tg ax,bx;
                                                                //-----------------------------------------
                                                                gra->ladenmatrixwelt(&mw);
                                                                gra->ladenmatrixmodell(&mm);
                                                                gra->ladenmatrixprojektion(&mp);
                                                                
																gra->orthonormal();//0, 100, 0,100, 0, 100);;
	                                                  
                                                              //  gra->tiefenbufferkondition(false);
	                                                          //  gra->schablonenbufferkondition(false);
	                                                          //  gra->transparenz(true);
	                                                            

	                                                            gra->rechteck(0,0,gra->breite(),gra->hoehe()*0.1,_vektor4<_to>(0.5,0.5,0.5,0.5));
	                                                            
		                                                        
		                                                        _vektor3<_tg> ort;
		                                                        _vektor3<_tg> yoffs;
		                                                        ort.setzen(0.01,20,10);
		                                                        yoffs.setzen(0,+20,0);
		                                                        
                                                                if(ptextlist.anfang(tit))do{
                                                                 tit->zeichnen(gra,ort);
                                                                 ort+=yoffs;
                                                                }while(ptextlist.naechstes(tit));
	                                                            
	                                                          //  gra->transparenz(false);
                                                                gra->matrixwelt(&mw);
                                                                gra->matrixmodell(&mm);
                                                                gra->matrixprojektion(&mp);
};                                                              

void _weltdebugschirm::animieren(){
};

void _weltdebugschirm::ort(const _vektor3<_tg> l0,const _vektor3<_tg> l1){
                                                                if(plocus[0].laenge()<plocus[1].laenge()){
                                                                 plocus[0]=l0;
                                                                 plocus[1]=l1;
                                                                }else{
                                                                 plocus[0]=l1;
                                                                 plocus[1]=l0;
                                                                };
};

_vektor3<_tg> _weltdebugschirm::ort(const unsigned int i) const{
                                                                if(i==0) return(plocus[0]); else return(plocus[1]);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G S C H I R M T E X T 
//******************************************************************************************************************************************************************************************************

_weltdebugschirmtext::_weltdebugschirmtext(_weltdebugschirm*s,_listebasis<_weltdebugschirmtext >*l,_zeichenkette<char> t,_vektor4<_to> c):_listenknotenbasis<_weltdebugschirmtext >(l){
                                                                ptext=t;
                                                                pcolor=c;
                                                                pscreen=s;
};

_weltdebugschirmtext::~_weltdebugschirmtext(){
                                                                clearlocusperspectivelist();
};

void _weltdebugschirmtext::clearlocusperspectivelist(){
                                                                _listenknoten<_liste<_vektor3<_tg> > >*lit;
                                                                //--------------------------
                                                                if(plocuspers.anfang(lit))do{
                                                                 lit->objekt()->loeschen();
                                                                }while(plocuspers.naechstes(lit));
                                                                plocuspers.loeschen();
};

void _weltdebugschirmtext::transformieren(_grafik*gra,_kamera<_tg>*cam,_vektor3<_tg>&plocus){
                                                              /*  unsigned int i;
                                                                _vektor3<_tg>*v;
                                                                _vektor3<_tg> o;
                                                                _weltdebugzeichensatzchar*c;
                                                                _weltdebugzeichensatzseg*sit;
                                                                _vektor3<_tg> pos;
                                                                _vektor3<_tg> ac;
                                                                _vektor3<_tg> bc;
                                                                _liste<_vektor2<_tg> >*vlist;
                                                                _listenknoten<_vektor2<_tg> >*vit;
                                                                _liste<_vektor3<_tg> >*il;
                                                                _vektor3<_tg> d;
                                                                _vektor3<_tg> stauch;
                                                                //--------------
                                                                clearlocusperspectivelist();
                                                                d=pscreen->plocus[0]-pscreen->plocus[1];
                                                                //stauch.setzen(0,1,0);
                                                                //stauch*=fabs(d[1]);
                                                                //stauch*=pscreen->pyoffs/gra->groessey();
                                                                //stauch*=1.0f/(pscreen->psy);
                                                                ac.setzen(1,0,0);
                                                                ac*=fabs(d[0]);
                                                                ac*=(1.0f/(pscreen->psx*(15.0f+pscreen->pxoffs)));
                                                                bc.setzen(0,1,0);
                                                                bc*=fabs(d[1]);
                                                                bc*=(1.0f/(2+pscreen->pyoffs+pscreen->psy*(29.0f+pscreen->pyoffs)));
                                                                plocus-=bc*(29+pscreen->pyoffs);
                                                                
                                                                pos=plocus+ac*pscreen->pxoffs+bc*pscreen->pyoffs;
                                                                for(i=0;i<ptext.groesse();i++){
                                                                 c=pscreen->welt()->debugzeichensatz()->character(int(ptext[i]));
                                                                 if(c){
                          
                                                                 if(c->anfang(sit))do{
                                                                  vlist=sit->liste();
                                                                  il=new _liste<_vektor3<_tg> >();
                                                                  plocuspers.einhaengen(il);
                                                                  if(vlist->anfang(vit))do{
                                                                   o=pos + ac* (*vit->objekt())[0] + bc* (*vit->objekt())[1]*1;
                                                                   v=new _vektor3<_tg>(o);
                                                                   il->einhaengen(v);
                                                                  }while(vlist->naechstes(vit));
                                                                 }while(c->naechstes(sit));
                                                            
                                                                 pos+=ac*(c->breite()+pscreen->pxoffs);
                                                                 };
                                                                };*/
};

void _weltdebugschirmtext::zeichnen(_grafik*gra,const _vektor3<_tg>&ort){
                                                               /* _listenknoten<_vektor3<_tg> >*vit;
                                                                _listenknoten<_vektor3<_tg> >*vin;
                                                                _listenknoten<_vektor3<_tg> >*start;
                                                                _listenknoten<_liste<_vektor3<_tg> > >*lit;
                                                                _liste<_vektor3<_tg> >*il;
                                                                //---------------------------
                                                                if(plocuspers.anfang(lit))do{
                                                                 il=lit->objekt();
                                                                 il->anfang(start);
                                                                 if(il->anfang(vit))do{
                                                                  vin=vit->naechstes();
                                                                  if(vin!=start){
                                                                   gra->zeichnen(*vit->objekt(),*vin->objekt(),pcolor);
                                                                  };
                                                                 }while(il->naechstes(vit));
                                                                }while(plocuspers.naechstes(lit));*/
                                                                _vektor4<_to> col;
                                                                //_tg ax,bx;
                                                                _vektor3<_tg> ac;
                                                                _vektor3<_tg> bc;
                                                                _weltdebugzeichensatzchar*c;
                                                                _weltdebugzeichensatzseg*sit;
                                                                _vektor3<_tg> o0;
                                                                _vektor3<_tg> o1;
                                                                _vektor3<_tg> pos;
                                                                _liste<_vektor2<_tg> >*vlist;
                                                                _listenknoten<_vektor2<_tg> >*vit;
                                                                //_listenknoten<_vektor2<_tg> >*vin;
                                                                //_liste<_vektor3<_tg> >*il;
/*
                                                                //-----------------------------------------
                                                                glPushMatrix();
                                                                glLoadIdentity();
	                                                            glOrtho(0,1,0,1, 0, 100);
                                                                glDisable(GL_DEPTH_TEST);
	                                                            glDisable(GL_STENCIL_TEST);
	                                                            glDisable(GL_BLEND);
	                                                            glDisable(GL_CULL_FACE);
	                                                            glDisable(GL_LIGHTING);
                                                                
		                                                        */
		                                                        pos=ort;//.setzen(0,0.5,0);
		                                                        ac.setzen(0.7,0,0);
		                                                        
		                                                        
                                                            //    pos=pscreen->pxoffs+pscreen->pyoffs;
                                                                for(unsigned int i=0;i<ptext.groesse();i++){
                                                                 c=pscreen->welt()->debugzeichensatz()->character(int(ptext[i]));
                                                                 if(c){
                          
                                                                 if(c->anfang(sit))do{
                                                                
                                                                  vlist=sit->liste();
                                                                  //il=new _liste<_vektor3<_tg> >();
                                                                  //plocuspers.einhaengen(il);
                                                                  if(vlist->anfang(vit))do{
                                                                   o0.setzen((*vit->objekt())[0]*0.7,-(*vit->objekt())[1]*0.7,0);
                                                                   o0+=pos;
                                                                   if(vit->naechstes()!=vlist->erstes()){
                                                                    o1.setzen((*vit->naechstes()->objekt())[0]*0.7,-(*vit->naechstes()->objekt())[1]*0.7,0);
                                                                    o1+=pos;
                                                                    gra->linie(o0,o1,pcolor);
                                                                    
                                                                   };
                                                                   //glColor4fv(pcolor.daten());
                                                                   //glVertex3dv(o.daten());
                                                                   // o=pos + ac* (*vit->objekt())[0] + bc* (*vit->objekt())[1]*1;
                                                                   // v=new _vektor3<_tg>(o);
                                                                   // il->einhaengen(v);
                                                                  }while(vlist->naechstes(vit));
                                                                  //glEnd();
                                                                 }while(c->naechstes(sit));
                                                            
                                                                 pos+=ac*(c->breite()+pscreen->pxoffs);
                                                                 };
                                                                };		                                                        
		                                                        
		                                                        
		                                                        
	                                                            /*	                                                            
	                                                            glDisable(GL_BLEND);
	                                                            glEnable(GL_CULL_FACE);
	                                                            
	                                                            
	                                                      
                                                                glPopMatrix();                                                                */
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G Z E I C H E N S A T Z
//******************************************************************************************************************************************************************************************************

_weltdebugzeichensatz::_weltdebugzeichensatz(_welt*w){
                                                                int i;
                                                                //-------------
                                                                pworld=w;
                                                                height=32;
                                                                scale=0.5;
                                                                for(i=0;i<256;i++) cot[i]=0;
                                                                init();
};

_weltdebugzeichensatz::~_weltdebugzeichensatz(){
                                                                loeschen();
                                                                
};

void _weltdebugzeichensatz::loeschen(){
                                                                int i;
                                                                //-------------
                                                                for(i=0;i<256;i++) if(cot[i]){
                                                                 delete cot[i];
                                                                 cot[i]=0;
                                                                };
};

_weltdebugzeichensatzchar*_weltdebugzeichensatz::character(int i){
                                                                if((i>=0)&&(i<256)){
                                                                 return(cot[i]);
                                                                }else{
                                                                 return(0);
                                                                };
};

void _weltdebugzeichensatz::init(){
                                                                _weltdebugzeichensatzchar*c;
                                                                _weltdebugzeichensatzseg*s0;
                                                                _weltdebugzeichensatzseg*s1;
                                                                _weltdebugzeichensatzseg*s2;
                                                                _weltdebugzeichensatzseg*s[6];
                                                                int j;
                                                                //*************************************  STANDART FONT  *********************************
                                                                //A
                                                                c=new _weltdebugzeichensatzchar(this,65,18);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,9,27,18,0);
                                                                s1->einhaengen(5,14,13,14);
                                                                //B
                                                                c=new _weltdebugzeichensatzchar(this,66,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,0,27,12,27,15,24);
                                                                s0->einhaengen(15,17, 12,14, 15,11, 15,3);
                                                                s0->einhaengen(12,0, 0,0);
                                                                s1->einhaengen(0,14,12,14);
                                                                //C
                                                                c=new _weltdebugzeichensatzchar(this,67,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(15,3,12,0,3,0,0,3);
                                                                s0->einhaengen(0,24,3,27,12,27,15,24);
                                                                //D
                                                                c=new _weltdebugzeichensatzchar(this,68,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0, 0,27, 12,27, 15,24);
                                                                s0->einhaengen(15,3,12,0,0,0);
                                                                //E
                                                                c=new _weltdebugzeichensatzchar(this,69,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(15,0,0,0,0,27,15,27);
                                                                s1->einhaengen(0,14,12,14);
                                                                //F
                                                                c=new _weltdebugzeichensatzchar(this,70,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,0,27,15,27);
                                                                s1->einhaengen(0,14,12,14);
                                                                //G
                                                                c=new _weltdebugzeichensatzchar(this,71,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(15,3, 12,0, 3,0, 0,3);
                                                                s0->einhaengen(0,24, 3,27, 12,27, 15,24);
                                                                s1->einhaengen(15,3, 15,11, 9,11);
                                                                //H
                                                                c=new _weltdebugzeichensatzchar(this,72,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s2=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,0,27);
                                                                s1->einhaengen(15,0,15,27);
                                                                s2->einhaengen(0,14,15,14);
                                                                //I
                                                                c=new _weltdebugzeichensatzchar(this,73,6);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s2=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(3,0,3,27);
                                                                s1->einhaengen(0,0,6,0);
                                                                s2->einhaengen(0,27,6,27);
                                                                //J
                                                                c=new _weltdebugzeichensatzchar(this,74,6);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s2=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(3,0,3,27);
                                                                s1->einhaengen(3,0,0,-3);
                                                                s2->einhaengen(0,27,6,27);
                                                                //K
                                                                c=new _weltdebugzeichensatzchar(this,75,14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s2=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,0,27);
                                                                s1->einhaengen(0,14,13,27);
                                                                s2->einhaengen(0,14,14,0);
                                                                //L
                                                                c=new _weltdebugzeichensatzchar(this,76,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,27,0,0,15,0);
                                                                //M
                                                                c=new _weltdebugzeichensatzchar(this,77,16);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0, 0,27, 8,19, 16,27);
                                                                s0->einhaengen(16,0);
                                                                //N
                                                                c=new _weltdebugzeichensatzchar(this,78,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,0,27,15,0,15,27);
                                                                //O
                                                                c=new _weltdebugzeichensatzchar(this,79,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(3,0, 0,3, 0,24,  3,27);
                                                                s0->einhaengen(12,27, 15,24, 15,3, 12,0);
                                                                s0->einhaengen(3,0);
                                                                //P
                                                                c=new _weltdebugzeichensatzchar(this,80,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0, 0,27, 12,27, 15,24);
                                                                s0->einhaengen(15,17, 12,14, 0,14);
                                                                //Q
                                                                c=new _weltdebugzeichensatzchar(this,81,18);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(3,0, 0,3, 0,24, 3,27);
                                                                s0->einhaengen(12,27, 15,24, 15,3, 12,0);
                                                                s0->einhaengen(3,0);
                                                                s1->einhaengen(12,6,18,0);
                                                                //R
                                                                c=new _weltdebugzeichensatzchar(this,82,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0, 0,27, 12,27, 15,24);
                                                                s0->einhaengen(15,17, 12,14, 0,14);
                                                                s1->einhaengen(1,14,15,0);
                                                                //S
                                                                c=new _weltdebugzeichensatzchar(this,83,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(15,24, 12,27, 3,27, 0,24);
                                                                s0->einhaengen(0,17, 3,14, 12,14, 15,11);
                                                                s0->einhaengen(15,3, 12,0, 3,0, 0,3);
                                                                //T
                                                                c=new _weltdebugzeichensatzchar(this,84,14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(7,0,7,27);
                                                                s1->einhaengen(0,27,14,27);
                                                                //U
                                                                c=new _weltdebugzeichensatzchar(this,85,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,27, 0,3, 3,0, 12,0);
                                                                s0->einhaengen(15,3, 15,27);
                                                                //V
                                                                c=new _weltdebugzeichensatzchar(this,86,14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,27, 7,0, 14,27);
                                                                //W
                                                                c=new _weltdebugzeichensatzchar(this,87,16);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,27, 3,0, 8,8, 13,0);
                                                                s0->einhaengen(16,27);
                                                                //X
                                                                c=new _weltdebugzeichensatzchar(this,88,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,15,27);
                                                                s1->einhaengen(15,0,0,27);
                                                                //Y
                                                                c=new _weltdebugzeichensatzchar(this,89,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,15,27);
                                                                s1->einhaengen(8,14,0,27);
                                                                //Z
                                                                c=new _weltdebugzeichensatzchar(this,90,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,27,15,27,0,0,15,0);
                                                                //leer
                                                                c=new _weltdebugzeichensatzchar(this,32,15);
                                                                //!
                                                                c=new _weltdebugzeichensatzchar(this,33,6);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(3,27,3,5);
                                                                s1->einhaengen(3,2,3,0);
                                                                //"
                                                                c=new _weltdebugzeichensatzchar(this,34,7);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(2,27,2,24);
                                                                s1->einhaengen(5,27,5,24);
                                                                //#
                                                                c=new _weltdebugzeichensatzchar(this,35,15);
                                                                //$
                                                                c=new _weltdebugzeichensatzchar(this,36,15);
                                                                //%
                                                                c=new _weltdebugzeichensatzchar(this,37,15);
                                                                //&
                                                                c=new _weltdebugzeichensatzchar(this,38,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                //'
                                                                c=new _weltdebugzeichensatzchar(this,39,15);
                                                                //(
                                                                c=new _weltdebugzeichensatzchar(this,40,4);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(3,31, 0,26, 0,1, 5,-4);
                                                                //)
                                                                c=new _weltdebugzeichensatzchar(this,41,4);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,31, 5,26, 5,1, 0,-4);
                                                                //*
                                                                c=new _weltdebugzeichensatzchar(this,42,15);
                                                                for(j=0;j<6;j++){
                                                                 s[j]=new _weltdebugzeichensatzseg(c);
                                                                 s[j]->einhaengen(7,13,7+cos(_ph*_tg(j*60))*6,13+sin(_ph*_tg(j*60))*6);
                                                                };
                                                                //+
                                                                c=new _weltdebugzeichensatzchar(this,43,15);
                                                                //,
                                                                c=new _weltdebugzeichensatzchar(this,44,2);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,2,2,2,2,0,0,-2);
                                                                //-
                                                                c=new _weltdebugzeichensatzchar(this,45,12);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,14,12,14);
                                                                //.
                                                                c=new _weltdebugzeichensatzchar(this,46,6);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(2,0, 4,0, 4,2, 2,2);
                                                                s0->einhaengen(2,0);
                                                                //0
                                                                c=new _weltdebugzeichensatzchar(this,48,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(3,0, 0,3, 0,24, 3,27);
                                                                s0->einhaengen(12,27, 15,24, 15,3, 12,0);
                                                                s0->einhaengen(3,0);
                                                                s1->einhaengen(12,27,3,0);
                                                                //1
                                                                c=new _weltdebugzeichensatzchar(this,49,6);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,6,0);
                                                                s0->einhaengen(3,0,3,27,0,24);
                                                                //2
                                                                c=new _weltdebugzeichensatzchar(this,50,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,24, 3,27, 12,27, 15,24);
                                                                s0->einhaengen(15,17, 0,0, 15,0);
                                                                //3
                                                                c=new _weltdebugzeichensatzchar(this,51,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,24,3,27, 12,27, 15,24);
                                                                s0->einhaengen(15,17, 12,14, 15,11, 15,3);
                                                                s0->einhaengen(12,0, 3,0, 0,3);
                                                                s1->einhaengen(12,14,5,14);
                                                                //4
                                                                c=new _weltdebugzeichensatzchar(this,52,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(12,27,0,6,15,6);
                                                                s1->einhaengen(12,0,12,12);
                                                                //5
                                                                c=new _weltdebugzeichensatzchar(this,53,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(15,27, 3,27, 0,14, 12,14);
                                                                s0->einhaengen(15,11, 15,3, 12,0, 3,0);
                                                                s0->einhaengen(0,3);
                                                                //6
                                                                c=new _weltdebugzeichensatzchar(this,54,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(12,27,0,14, 0,3, 3,0);
                                                                s0->einhaengen(12,0, 15,3, 15,11, 12,14);
                                                                s0->einhaengen(0,14);
                                                                //7
                                                                c=new _weltdebugzeichensatzchar(this,55,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,27,15,27,0,0);
                                                                //8
                                                                c=new _weltdebugzeichensatzchar(this,56,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(3,0,0,3, 0,11, 3,14);
                                                                s0->einhaengen(0,17, 0,24, 3,27, 12,27);
                                                                s0->einhaengen(15,24, 15,17, 12,14, 15,11);
                                                                s0->einhaengen(15,3,12,0,3,0);
                                                                s1->einhaengen(12,14,3,14);
                                                                //9
                                                                c=new _weltdebugzeichensatzchar(this,57,15);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(15,14, 3,14, 0,17, 0,24);
                                                                s0->einhaengen(3,27, 12,27, 15,24, 15,13);
                                                                s0->einhaengen(0,0);
                                                                //:
                                                                c=new _weltdebugzeichensatzchar(this,int(':'),6);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(2,0, 4,0, 4,2, 2,2);
                                                                s0->einhaengen(2,0);
                                                                s1->einhaengen(2,6, 4,6, 4,8, 2,8);
                                                                s1->einhaengen(2,6);
                                                                //;
                                                                c=new _weltdebugzeichensatzchar(this,int(';'),6);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(2,2, 4,2, 4,0, 2,-2);
                                                                s1->einhaengen(2,6, 4,6, 4,8, 2,8);
                                                                s1->einhaengen(2,6);
                                                                //<
                                                                c=new _weltdebugzeichensatzchar(this,int('<'),7);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(9,0, 0,9, 9,18);
                                                                //=
                                                                c=new _weltdebugzeichensatzchar(this,int('='),13);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,16,12,16);
                                                                s1->einhaengen(0,12,12,12);
                                                                //>
                                                                c=new _weltdebugzeichensatzchar(this,int('>'),7);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0, 9,9, 0,18);
                                                                //?
                                                                c=new _weltdebugzeichensatzchar(this,int('?'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,15, 4,19, 9,19, 13,15);
                                                                s0->einhaengen(13,12, 7,6, 7,0);
                                                                s1->einhaengen(7,-2, 7,-4);
                                                                //_
                                                                c=new _weltdebugzeichensatzchar(this,95,14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(1,0,13,0);
                                                                //a
                                                                c=new _weltdebugzeichensatzchar(this,int('a'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,15, 4,19, 10,19, 14,15);
                                                                s0->einhaengen(14,0);
                                                                s1->einhaengen(14,4, 10,0, 4,0, 0,4);
                                                                s1->einhaengen(0,9, 14,11);
                                                                //b
                                                                c=new _weltdebugzeichensatzchar(this,int('b'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,0,27);
                                                                s1->einhaengen(0,15, 4,19, 10,19, 14,15);
                                                                s1->einhaengen(14,4, 10,0, 4,0, 0,4);
                                                                //c
                                                                c=new _weltdebugzeichensatzchar(this,int('c'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(14,4,10,0,4,0,0,4);
                                                                s0->einhaengen(0,15,4,19,10,19,14,15);
                                                                //d
                                                                c=new _weltdebugzeichensatzchar(this,int('d'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(14,0,14,27);
                                                                s1->einhaengen(14,4, 10,0, 4,0, 0,4);
                                                                s1->einhaengen(0,15, 4,19, 10,19, 14,15);
                                                                //e
                                                                c=new _weltdebugzeichensatzchar(this,int('e'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(14,4, 10,0, 4,0, 0,4);
                                                                s0->einhaengen(0,15, 4,19, 10,19, 14,15);
                                                                s0->einhaengen(14,10, 0,10);
                                                                //f
                                                                c=new _weltdebugzeichensatzchar(this,int('f'),9);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(9,25, 9,26, 8,27, 6,27);
                                                                s0->einhaengen(4,25, 4,0);
                                                                s1->einhaengen(0,19,8,19);
                                                                //g
                                                                c=new _weltdebugzeichensatzchar(this,int('g'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(14,19,14,-1, 10,-5, 4,-5);
                                                                s0->einhaengen(0,-1);
                                                                s1->einhaengen(14,4, 10,0, 4,0, 0,4);
                                                                s1->einhaengen(0,15, 4,19, 10,19, 14,15);
                                                                //h
                                                                c=new _weltdebugzeichensatzchar(this,int('h'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,0,27);
                                                                s1->einhaengen(0,15, 4,19, 10,19, 14,15);
                                                                s1->einhaengen(14,0);
                                                                //i
                                                                c=new _weltdebugzeichensatzchar(this,int('i'),4);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s2=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(2,0,2,19,0,19);
                                                                s1->einhaengen(2,23,2,26,0,26);
                                                                s2->einhaengen(0,0,4,0);
                                                                //j
                                                                c=new _weltdebugzeichensatzchar(this,int('j'),5);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,-4,3,-1,3,19,1,19);
                                                                s1->einhaengen(3,23,3,26,1,26);
                                                                //k
                                                                c=new _weltdebugzeichensatzchar(this,int('k'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s2=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0,0,27);
                                                                s1->einhaengen(0,9,14,19);
                                                                s2->einhaengen(5,11,14,0);
                                                                //l
                                                                c=new _weltdebugzeichensatzchar(this,int('l'),4);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,27, 0,1, 1,0, 3,0);
                                                                s0->einhaengen(4,1);
                                                                //m
                                                                c=new _weltdebugzeichensatzchar(this,int('m'),16);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s2=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0, 0,19);
                                                                s1->einhaengen(0,16, 3,19,5,19, 8,16);
                                                                s2->einhaengen(8,0, 8,16, 11,19, 13,19);
                                                                s2->einhaengen(16,16,16,0);
                                                                //n
                                                                c=new _weltdebugzeichensatzchar(this,int('n'),13);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,0, 0,19);
                                                                s1->einhaengen(0,15, 4,19, 9,19, 13,15);
                                                                s1->einhaengen(13,0);
                                                                //o
                                                                c=new _weltdebugzeichensatzchar(this,int('o'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,15, 4,19, 10,19, 14,15);
                                                                s0->einhaengen(14,4, 10,0, 4,0, 0,4);
                                                                s0->einhaengen(0,15);
                                                                //p
                                                                c=new _weltdebugzeichensatzchar(this,int('p'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,15, 4,19, 10,19, 14,15);
                                                                s0->einhaengen(14,4, 10,0, 4,0, 0,4);
                                                                s1->einhaengen(0,19, 0,-5);
                                                                //q
                                                                c=new _weltdebugzeichensatzchar(this,int('q'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(14,4, 10,0, 4,0, 0,4);
                                                                s0->einhaengen(0,15, 4,19, 10,19, 14,15);
                                                                s1->einhaengen(14,19, 14,-5);
                                                                //r
                                                                c=new _weltdebugzeichensatzchar(this,int('r'),13);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,15,4,19,9,19,13,15);
                                                                s1->einhaengen(0,0,0,19);
                                                                //s
                                                                c=new _weltdebugzeichensatzchar(this,int('s'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(14,15,10,19,4,19,0,15);
                                                                s0->einhaengen(0,11,14,9,14,4,10,0);
                                                                s0->einhaengen(4,0,0,4);
                                                                //t
                                                                c=new _weltdebugzeichensatzchar(this,int('t'),7);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(3,27, 3,1, 4,0, 6,0);
                                                                s0->einhaengen(7,1);
                                                                s1->einhaengen(0,19,7,19);
                                                                //u
                                                                c=new _weltdebugzeichensatzchar(this,int('u'),13);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,19,0,4, 4,0, 9,0);
                                                                s0->einhaengen(13,4);
                                                                s1->einhaengen(14,19,14,0);
                                                                //v
                                                                c=new _weltdebugzeichensatzchar(this,int('v'),12);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,19,6,0,12,19);
                                                                //w
                                                                c=new _weltdebugzeichensatzchar(this,int('w'),16);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,19,4,0,8,19,12,0);
                                                                s0->einhaengen(16,19);
                                                                //x
                                                                c=new _weltdebugzeichensatzchar(this,int('x'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,19,14,0);
                                                                s1->einhaengen(0,0,14,19);
                                                                //y
                                                                c=new _weltdebugzeichensatzchar(this,int('y'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s1=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,19,7,0);
                                                                s1->einhaengen(14,19, 7,-2, 4,-5, 2,-5);
                                                                s1->einhaengen(0,-3);
                                                                //z
                                                                c=new _weltdebugzeichensatzchar(this,int('z'),14);
                                                                s0=new _weltdebugzeichensatzseg(c);
                                                                s0->einhaengen(0,19, 14,19, 0,0, 14,0);
                                                                
                                                                
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G Z E I C H E N S A T Z C H A R
//******************************************************************************************************************************************************************************************************

_weltdebugzeichensatzchar::_weltdebugzeichensatzchar(_weltdebugzeichensatz*f,int index,_tg wx){
                                                                pfont=f;
                                                                pindex=index;
                                                                pwx=wx;
                                                                if((pindex>=0)&&(pindex<256)){
                                                                 if(f->cot[pindex]) delete f->cot[pindex];
                                                                 f->cot[pindex]=this;
                                                                }else{
                                                                 pindex=69;
                                                                };
};

_weltdebugzeichensatzchar::~_weltdebugzeichensatzchar(){
                                                                pfont->cot[pindex]=0;
};

_tg _weltdebugzeichensatzchar::breite()const{
                                                                return(pwx);
};
//******************************************************************************************************************************************************************************************************
//                                                              W E L T D E B U G Z E I C H E N S A T Z S E G
//******************************************************************************************************************************************************************************************************

_weltdebugzeichensatzseg::_weltdebugzeichensatzseg(_weltdebugzeichensatzchar*c):_listenknotenbasis<_weltdebugzeichensatzseg >(c){
                                                                pchar=c;
};

_weltdebugzeichensatzseg::~_weltdebugzeichensatzseg(){
                                                                plist.loeschen();
};

_liste<_vektor2<_tg> >*_weltdebugzeichensatzseg::liste(){
                                                                return(&plist);
};

void _weltdebugzeichensatzseg::einhaengen(_tg x,_tg y){
                                                                _vektor2<_tg>*v;
                                                                //--------------
                                                                v=new _vektor2<_tg>(x,y);
                                                                plist.einhaengen(v);
};

void _weltdebugzeichensatzseg::einhaengen(_tg x,_tg y,_tg a,_tg b){
                                                                _vektor2<_tg>*v;
                                                                //--------------
                                                                v=new _vektor2<_tg>(x,y);
                                                                plist.einhaengen(v);
                                                                v=new _vektor2<_tg>(a,b);
                                                                plist.einhaengen(v);
};

void _weltdebugzeichensatzseg::einhaengen(_tg x,_tg y,_tg a,_tg b,_tg c,_tg d){
                                                                _vektor2<_tg>*v;
                                                                //--------------
                                                                v=new _vektor2<_tg>(x,y);
                                                                plist.einhaengen(v);
                                                                v=new _vektor2<_tg>(a,b);
                                                                plist.einhaengen(v);
                                                                v=new _vektor2<_tg>(c,d);
                                                                plist.einhaengen(v);
};

void _weltdebugzeichensatzseg::einhaengen(_tg x,_tg y,_tg a,_tg b,_tg c,_tg d,_tg e,_tg f){
                                                                _vektor2<_tg>*v;
                                                                //--------------
                                                                v=new _vektor2<_tg>(x,y);
                                                                plist.einhaengen(v);
                                                                v=new _vektor2<_tg>(a,b);
                                                                plist.einhaengen(v);
                                                                v=new _vektor2<_tg>(c,d);
                                                                plist.einhaengen(v);
                                                                v=new _vektor2<_tg>(e,f);
                                                                plist.einhaengen(v);
};
