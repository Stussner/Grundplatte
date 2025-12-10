//******************************************************************************************************************************************************************************************************
//  Projekt      : grundplatte
//  Bibliothek   : _grundplatte.lib
//  Modul        : _weltpolygon.cpp
//  Datum        : 09.01.2006
//  Beschreibung : 
//******************************************************************************************************************************************************************************************************
#include <_weltpolygon.hpp>
//#include <_grafikopengl.hpp>


//******************************************************************************************************************************************************************************************************
//                                                              P O L Y G O N 
//******************************************************************************************************************************************************************************************************
_polygon::_polygon(_netz*m):_listenknotenbasis<_polygon >(m){
																pstatusbit=0;
                                                                ptextur=0;
                                                                ptexturrueck=0;
                                                                ptexturdynamisch=0;
                                                                ptexturstring="ni";
                                                                ptexturdynamischstring="ni";
                                                                verwendentextur(true);
                                                                verwendentexturdynamisch(false);
                                                                plightmaptexelgroesse=1;
                                                                verwendenverbinderfarbe(true);
                                                                zeichnenflaeche(true);
                                                                zeichnenkante(false);
                                                                zeichnennormale(false);
                                                                normaleinterpoliert(false);
                                                                zweiseitig(false); 
                                                                spiegelnd(false);
                                                                maskiert(false);
                                                                aufgehellt(false);
                                                                kollision(true);
                                                                lightmapschattierung(true);
                                                                transparenz(false);
                                                                transparenzadditiv(true);
                                                                debuggen(false);
                                                                nurkollisionskopplung(false);
                                                                dynamischschattierend(false);
                                                                dynamischschattiert(true);
                                                                ptransparentfaktor=0.5f;
                                                                pfarbe.setzen(0.35f,0.7f,0.45f,1);
                                                                pfarbekante.setzen(0,1,0,1);
                                                                pglanz.setzen(1,1,1,1);
                                                                pemission.setzen(0,0,0,1);
                                                                pglanzbreite=20;
                                                                //pvertex=0;
                                                                pflag=0;
                                                                pmesh=m;
                                                                pschatteniterator=0;
                                                                pschattenvolumenlaenge=50;
                                                                //pflip=+1;
                                                                pcomponent.setzen(0,1,2);
                                                                ptexturespace=0;
                                                                pstatus=0;
                                                                pselection=0;
                                                                markierungkollisionobjekt=0;
                                                                markierungkollisionrekursion=0;
                                                                markierungkollisionzyklus=0;
                                                                markierungzeichnenzyklus=0;
                                                                markierungzeichnenpass=0;
                                                                markierungzeichnenrueckseitigzyklus=0;
                                                                pindexbuffer=0;
                                                                pindexanzahl=0;
                                                             //   pknotenzeichnung=0;
                                                               // L->schreiben("_polygon wurde konstruiert.");
};

_polygon::_polygon(_polygon*p):_listenknotenbasis<_polygon >(p->pmesh){
                                                                ptextur=p->ptextur;
                                                                ptexturrueck=p->ptexturrueck;
                                                                ptexturdynamisch=p->ptexturdynamisch;
                                                                ptexturstring=p->ptexturstring;
                                                                ptexturdynamischstring=p->ptexturdynamischstring;
                                                                plightmaptexelgroesse=p->plightmaptexelgroesse;
                                                                ptransparentfaktor=p->ptransparentfaktor;
																pstatusbit=p->pstatusbit;
                                                                pfarbe=p->pfarbe;
                                                                pfarbekante=p->pfarbekante;
                                                                pglanz=p->pglanz;
                                                                pemission=p->pemission;
                                                                pglanzbreite=p->pglanzbreite;
                                                                //pvertex=0;
                                                                pflag=p->pflag;
                                                                pmesh=p->pmesh;
                                                                pschattenvolumenlaenge=p->pschattenvolumenlaenge;
                                                                pschatteniterator=0;
                                                                //pflip=p->pflip;
                                                                pcomponent=p->pcomponent;
                                                                ptexturespace=0;
                                                                pstatus=p->pstatus;
                                                                pselection=p->pselection;
                                                                _oberflaeche<_tg>::kopieren(p);
                                                                markierungkollisionobjekt=0;
                                                                markierungkollisionrekursion=0;
                                                                markierungzeichnenzyklus=0;
                                                                markierungzeichnenpass=0;
                                                                markierungkollisionzyklus=0;
                                                                markierungzeichnenrueckseitigzyklus=0;
                                                                pindexbuffer=0;
                                                                pindexanzahl=0;
                                                             //   pknotenzeichnung=0;
                                                               // if(p->pknotenzeichnung) pknotenzeichnung=p->pknotenzeichnung->liste()->einhaengen(this);
                                                               // L->schreiben("_polygon wurde konstruiert mit Kopierkonstruktor.");
};


_polygon::~_polygon(){
                                                                _liste<_vertex > liv;
                                                                _listenknoten<_vertex >*lvit;
                                                                //_vertex*vit;
                                                                //-----------------
                                                                unvisualisieren();
                                                                loeschenkante();
                                                                plistringpartition.loeschen();
                                                                plistisintroconnector.loeschen();
                                                                if(ptexturespace) delete ptexturespace;
                                                                ptexturespace=0;
                                                                _listebasis<_dreieck >::loeschen();
                                                                iterieren(lvit,liv.einhaengen(lvit->objekt()));
                                                                iterierenliste(&liv,lvit,delete lvit->objekt()->verbinder(this));
                                                                iterierenliste(&liv,lvit,if(lvit->objekt()->_liste<_polygon>::anzahl()==0) lvit->loeschmarkierungobjekt(true));
                                                                liv.loeschenmarkiert();
                                                                liv.aushaengen();
                                                                loeschenindex();
                                                                //L->l("Polygon wurde gelöscht");
																//deletesecure(pknotenzeichnung);
};
void _polygon::transformieren(_grafik*gra,_kamera<_tg>*cam){
                                                                _vertex*vit;
                                                                _vektor3<_tg> x;
                                                                _vektor3<_tg> y;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //-----------
                                                                x=pmiddle;
                                                                cam->transformierenparallel(x);
                                                                pmiddleparallel=x;
                                                                cam->transformierenperspektive(x);
                                                                gra->transformieren(x);
                                                                pmiddleperspective=x;
                                                                x=pmiddle+ normale();
                                                                cam->transformierenparallel(x);
                                                                pmiddlenormalparallel=x;
                                                                cam->transformierenperspektive(x);
                                                                gra->transformieren(x);
                                                                pmiddlenormalperspective=x; 
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 if(vit->markierung()==0){
                                                                  y=vit->ort();
                                                                  cam->transformierenparallel(y);
                                                                  vit->orttransformation(y);
                                                                  vit->markierung(1);
                                                                 };
                                                                );
};

void _polygon::transformieren(_grafik*gra,_kamera<_tg>*cam,_tg xyskalierung,_tg zwert){
                                                                _vertex*vit;
                                                                _vektor3<_tg> x;
                                                                _vektor3<_tg> y;
                                                                unsigned int i;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //-----------
                                                                i=2;//da die letzte komponente immer als z-buffer genutzt wird
                                                                x=pmiddle;
                                                                cam->transformierenparallel(x);
                                                                pmiddleparallel=x*xyskalierung;
                                                                cam->transformierenperspektive(x);
                                                                gra->transformieren(x);
                                                                pmiddleperspective=x*xyskalierung;
                                                                x=pmiddle+ normale();
                                                                cam->transformierenparallel(x);
                                                                pmiddlenormalparallel=x*xyskalierung;
                                                                cam->transformierenperspektive(x);
                                                                gra->transformieren(x);
                                                                pmiddlenormalperspective=x*xyskalierung; 
                                                                pmiddleparallel.setzenkomponente(i,zwert);
                                                                pmiddleperspective.setzenkomponente(i,zwert);
                                                                pmiddlenormalparallel.setzenkomponente(i,zwert);
                                                                pmiddlenormalperspective.setzenkomponente(i,zwert);
                                                              //  pmiddleparallel.tauschen(i,2);
                                                              //  pmiddleperspective.tauschen(i,2);
                                                              //  pmiddlenormalparallel.tauschen(i,2);
                                                              //  pmiddlenormalperspective.tauschen(i,2);
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 if(vit->markierung()==0){
                                                                  y=vit->ort();
                                                                  cam->transformierenparallel(y);
                                                                  y*=xyskalierung;
                                                                  y.setzenkomponente(i,zwert);
                                                                  vit->orttransformation(y);
                                                                  vit->markierung(1);
                                                                 };
                                                                );
};

void _polygon::transformieren(_grafik*gra,_kamera<_tg>*cam,_tg xs,_tg ys,_tg zs){
                                                                _vertex*vit;
                                                                _vektor3<_tg> x;
                                                                _vektor3<_tg> y;
                                                                _vektor3<_tg> scale;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //-----------
                                                                scale.setzen(xs,ys,zs);

                                                                x=pmiddle;
                                                                cam->transformierenparallel(x);
                                                                x.produkt(scale);
                                                                pmiddleparallel=x;
                                                                
                                                                cam->transformierenperspektive(x);
                                                                gra->transformieren(x);
                                                                x.produkt(scale);
                                                                pmiddleperspective=x;
                                                                
                                                                x=pmiddle+ normale();
                                                                cam->transformierenparallel(x);
                                                                x.produkt(scale);
                                                                pmiddlenormalparallel=x;
                                                                
                                                                cam->transformierenperspektive(x);
                                                                gra->transformieren(x);
                                                                x.produkt(scale);
                                                                pmiddlenormalperspective=x; 
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 if(vit->markierung()==0){
                                                                  y=vit->ort();
                                                                  cam->transformierenparallel(y);
                                                                  y.produkt(scale);
                                                                  vit->orttransformation(y);
                                                                  vit->markierung(1);
                                                                 };
                                                                );
};
void _polygon::zeichnendebug(_grafik*g){
                                                                //DEBUG - polygon zeichen
                                                                _vektor4<_to> c;
                                                                _vektor4<_to> cc;
                                                                //_vertex*vn;
                                                                //-----------
                                                                g->textur(false);
                                                                g->tiefenbufferkondition(true);
                                                                g->tiefenbufferschreiben(true);
                                                                g->transparenz(true);
                                                                g->ausschussflaeche(false);//glDisable(GL_CULL_FACE);
                                                                if(pmesh->welt()->eigenetransformation()){
                                                                 iterierendreieck(this,,g->zeichnendebug(vit0->orttransformation(),vit1->orttransformation(),vit2->orttransformation(),pfarbe,pfarbe,pfarbe));
                                                                 //linien zeichen
                                                                 phc.setzen(1,1,1,0);
                                                                 _listenknoten<_vertex>*lnvit;
                                                                 iterieren(lnvit,g->zeichnen(lnvit->objekt()->orttransformation(),lnvit->naechstes()->objekt()->orttransformation(),phc));
                                                                 //normale zeichen
                                                                 if(pflag!=0) {
                                                                  c.setzen(1,0,0,0.5f); 
                                                                  cc.setzen(0.3f,0,0,0.5f);
                                                                 }else{
                                                                  c.setzen(0,1,0,0.5f);
                                                                  cc.setzen(0,0.3f,0,0.5f);
                                                                 };
                                                                 g->zeichnen(pmiddleparallel,pmiddlenormalparallel,c,cc);
                                                                }else{//---------------------------------------------------------------------------------------------------
                                                                 iterierendreieck(this,,g->zeichnendebug(vit0->ort(),vit1->ort(),vit2->ort(),pfarbe,pfarbe,pfarbe));
                                                                 //linien zeichen
                                                                 phc.setzen(0.5,0.5,0.5,0.5f);
                                                                 _listenknoten<_vertex>*lnvit;
                                                                 iterieren(lnvit,g->zeichnen(lnvit->objekt()->ort(),lnvit->naechstes()->objekt()->ort(),phc));
                                                                 //normale zeichen
                                                                 if(pflag!=0) {
                                                                  c.setzen(1,0,0,0.5f); 
                                                                  cc.setzen(0.3f,0,0,0.5f);
                                                                 }else{
                                                                  c.setzen(0,1,0,0.5f);
                                                                  cc.setzen(0,0.3f,0,0.5f);
                                                                 };
                                                                 anfang(lnvit);
                                                                 g->zeichnen(pmiddle,pmiddle+normale(),c,cc);
                                                                 g->zeichnen(pmiddle,lnvit->objekt()->ort(),phc);
                                                                };
                                                                g->ausschussflaeche(true);//glEnable(GL_CULL_FACE);
};

void _polygon::zeichnenlinie(_grafik*g){
                                                                //lined - polygon zeichen
                                                                _vektor4<_to> c;
                                                                _vektor4<_to> cc;
                                                                //-----------
                                                                g->textur(false);
                                                                g->tiefenbufferkondition(true);
                                                                g->tiefenbufferschreiben(true);
                                                                g->transparenz(true);
                                                                
                                                                if(pmesh->welt()->eigenetransformation()){
                                                                 iterierendreieck(this,,g->zeichnendebug(vit0->orttransformation(),vit1->orttransformation(),vit2->orttransformation(),pfarbe,pfarbe,pfarbe));
                                                                 //linien zeichen
                                                                 phc.setzen(1,1,1,0.5f);
                                                                 _listenknoten<_vertex>*lnvit;
                                                                 iterieren(lnvit,g->zeichnen(lnvit->objekt()->orttransformation(),lnvit->naechstes()->objekt()->orttransformation(),pfarbekante));
                                                                 //normale zeichen
                                                                 if(pflag!=0) {
                                                                  c.setzen(1,0,0,0.5f); 
                                                                  cc.setzen(0.3f,0,0,0.5f);
                                                                 }else{
                                                                  c.setzen(0,1,0,0.5f);
                                                                  cc.setzen(0,0.3f,0,0.5f);
                                                                 };
                                                                 g->zeichnen(pmiddleparallel,pmiddlenormalparallel,c,cc);
                                                                }else{//-----------------------------------------------------------------------
                                                                 iterierendreieck(this,,g->zeichnendebug(vit0->ort(),vit1->ort(),vit2->ort(),pfarbe,pfarbe,pfarbe));
                                                                 //linien zeichen
                                                                 phc.setzen(0.5,0.5,0.5,0.5f);
                                                                 _listenknoten<_vertex>*lnvit;
                                                                 iterieren(lnvit,g->zeichnen(lnvit->objekt()->ort(),lnvit->naechstes()->objekt()->ort(),phc));
                                                                 //normale zeichen
                                                                 if(pflag!=0) {
                                                                  c.setzen(1,0,0,0.5f); 
                                                                  cc.setzen(0.3f,0,0,0.5f);
                                                                 }else{
                                                                  c.setzen(0,1,0,0.5f);
                                                                  cc.setzen(0,0.3f,0,0.5f);
                                                                 };
                                                                 g->zeichnen(pmiddle,pmiddle+normale(),c,cc);
                                                                };
};
void _polygon::bindentextur(_grafik*g,_bild<_tb>*&bild,_bild<_tb>*&lmap,_bild<_tb>*&smap){
                                                                bild=0;
                                                                lmap=0;
                                                                smap=0;
                                                                _listenknoten<_bild<_tb> >*lnbild;
                                                                _listenknoten<_bild<_tb> >*lnlmap;
                                                                _listenknoten<_bild<_tb> >*lnsmap;
                                                                if(verwendentextur()){
                                                                 if(verwendentexturdynamisch()) if(texturdynamisch()) {
                                                                  ptexturdynamisch->lightmap()->anfang(lnlmap);
                                                                  lmap=lnlmap->objekt();
                                                                 };
                                                                 //lmap=0;
                                                                 if(ptextur){ 
                                                                  if(ptextur->bitmap()->anfang(lnbild)) {
                                                                   bild=lnbild->objekt();
                                                                   g->textureinheit(0);//glActiveTextureARB(GL_TEXTURE0_ARB);
                                                                   if(lmap==0) g->texturoperationmultiplikativ();//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//GL_DECAL);
                                                                   else g->texturoperationadditiv();//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	                                                               g->textur(true);//glEnable(GL_TEXTURE_2D);
                                                                   g->bindenbild(bild); 
                                                                  };
                                                                  if(ptextur->specularmap()->anfang(lnsmap)) {
                                                                   smap=lnsmap->objekt();
                                                                   g->textureinheit(2);//glActiveTextureARB(GL_TEXTURE2_ARB);
                                                                   g->texturoperationadditiv();//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	                                                               g->textur(true);//glEnable(GL_TEXTURE_2D);
                                                                   g->bindenbild(smap); 
                                                                  };
                                                                 };
                                                                 if(lmap){
                                                                   g->textureinheit(1);//glActiveTextureARB(GL_TEXTURE1_ARB);
                                                                   g->texturoperationmultiplikativ();//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);//voher : GL_MODULATE (std einstelllung)
                                                                   g->textur(true);//glEnable(GL_TEXTURE_2D);
                                                                   g->bindenbild(lmap);
                                                                 };
                                                                 //g->textur(true); 
                                                                } else g->textur(false);
};
void _polygon::bindentransparenz(_grafik*g){
                                                                if(transparenz()){
                                                                 g->transparenz(true); 
                                                                 if(transparenzadditiv()) g->transparenzadditiv(); else g->transparenzmultiplikativ();
                                                                 g->tiefenbufferschreiben(false); 
                                                                }else{
                                                                 g->transparenz(false); 
                                                                 g->tiefenbufferschreiben(true); 
                                                                };
};
void _polygon::bindenmaskierung(_grafik*g){
                                                                if(maskiert()){
                                                                 g->maske(true);
                                                                }else{
                                                                 g->maske(false);
                                                                };
};
void _polygon::bindenzweiseitigkeit(_grafik*g){
                                                                if(zweiseitig()){
                                                                 g->ausschussflaeche(false);
                                                                }else{
                                                                 g->ausschussflaeche(true);
                                                                };
};
void _polygon::bindenmaterialoptik(_grafik*g){
                                                                g->materialglanz(pglanz);
                                                                g->materialfarbe(pfarbe);
                                                                g->materialemission(pemission);
                                                                g->materialglanzbreite(pglanzbreite);
};
void _polygon::zeichnen(_grafik*g){ 
                                                                //polygon zeichnen 
                                                                
                                                                //_vertex*vit0; 
                                                                //_vertex*vit1; 
                                                                //_vertex*vn; 
                                                                //_vektor3<_tg>&n=*this;
                                                                //_vektor3<_tg> n0=n;
                                                                //_vektor3<_tg> n1=n;
                                                                //_vektor3<_tg> n2=n;
                                                                //_verbindervertexpolygon*pvcp; 
                                                                //_verbindervertexpolygon*vcp0; 
                                                                //_verbindervertexpolygon*vcp1; 
                                                                //_vektor4<_to> ptc; 
                                                                _listenknoten<_vertex>*lnvit;
                                                                _bild<_tb>*bild=0; 
                                                                _bild<_tb>*lmap=0; 
                                                                _bild<_tb>*smap=0; 
                                                                unsigned int li=0; 
                                                                unsigned int mi=0; 
                                                                unsigned int lli=1;
                                                                unsigned int lmi=0;
                                                                unsigned int sli=5;
                                                                unsigned int smi=0;
                                                                //textur einbinden
                                                                bindentextur(g,bild,lmap,smap);
                                                                //maskierung einstellen
                                                                //transparenz einstellen
                                                                bool eigenetransformation=false;
                                                                if(pmesh->welt()) eigenetransformation=pmesh->welt()->eigenetransformation();
                                                                if(eigenetransformation){
                                                                 if(zeichnenflaeche()){
                                                                  
                                                                  iterierendreieckverbindernormaleinterpoliert(this,
                                                                   if(lmap){
                                                                    if(smap){
                                                                     g->zeichnen(//----------------- bitmap, lightmap und specularmap 
                                                                     vit0->orttransformation(), 
                                                                     vit1->orttransformation(), 
                                                                     vit2->orttransformation(), 
                                                                     cit0->farbe(), 
                                                                     cit1->farbe(), 
                                                                     cit2->farbe(), 
                                                                     cit0->holenvektor(li,mi), 
                                                                     cit1->holenvektor(li,mi), 
                                                                     cit2->holenvektor(li,mi),
                                                                     cit0->holenvektor(lli,lmi), 
                                                                     cit1->holenvektor(lli,lmi), 
                                                                     cit2->holenvektor(lli,lmi), 
                                                                     cit0->holenvektor(sli,smi), 
                                                                     cit1->holenvektor(sli,smi), 
                                                                     cit2->holenvektor(sli,smi)); 
                                                                    }else{//-------------------nur bitmap und lightmap
                                                                     g->zeichnen( 
                                                                     vit0->orttransformation(), 
                                                                     vit1->orttransformation(), 
                                                                     vit2->orttransformation(), 
                                                                     cit0->farbe(), 
                                                                     cit1->farbe(), 
                                                                     cit2->farbe(), 
                                                                     cit0->holenvektor(li,mi), 
                                                                     cit1->holenvektor(li,mi), 
                                                                     cit2->holenvektor(li,mi),
                                                                     cit0->holenvektor(lli,lmi), 
                                                                     cit1->holenvektor(lli,lmi), 
                                                                     cit2->holenvektor(lli,lmi)); 
                                                                    };
                                                                   }else{
                                                                    g->zeichnen( 
                                                                    vit0->orttransformation(), 
                                                                    vit1->orttransformation(), 
                                                                    vit2->orttransformation(), 
                                                                    cit0->farbe(), 
                                                                    cit1->farbe(), 
                                                                    cit2->farbe(), 
                                                                    cit0->holenvektor(li,mi), 
                                                                    cit1->holenvektor(li,mi), 
                                                                    cit2->holenvektor(li,mi)); 
                                                                   };
                                                                  );
                                                                 };//if zeichnenflaeche()
                                                                }else{//------------------------ zeichnen mit hardwaretransformation -----------------------------------------------------------------------------------
                                                                 if(zeichnenflaeche()){
                                                                  iterierendreieckverbindernormaleinterpoliert(this,
                                                                   if(lmap){
                                                                    if(smap){
                                                                     g->zeichnen(//----------------- bitmap, lightmap und specularmap 
                                                                     vit0->ort(), 
                                                                     vit1->ort(), 
                                                                     vit2->ort(), 
                                                                     cit0->farbe(), 
                                                                     cit1->farbe(), 
                                                                     cit2->farbe(), 
                                                                     cit0->holenvektor(li,mi), 
                                                                     cit1->holenvektor(li,mi), 
                                                                     cit2->holenvektor(li,mi),
                                                                     cit0->holenvektor(lli,lmi), 
                                                                     cit1->holenvektor(lli,lmi), 
                                                                     cit2->holenvektor(lli,lmi), 
                                                                     cit0->holenvektor(sli,smi), 
                                                                     cit1->holenvektor(sli,smi), 
                                                                     cit2->holenvektor(sli,smi)); 
                                                                    }else{//-------------------nur bitmap und lightmap
                                                                     g->zeichnen( 
                                                                     vit0->ort(), 
                                                                     vit1->ort(), 
                                                                     vit2->ort(), 
                                                                     n0,n1,n2,
                                                                     cit0->farbe(), 
                                                                     cit1->farbe(), 
                                                                     cit2->farbe(), 
                                                                     cit0->holenvektor(li,mi), 
                                                                     cit1->holenvektor(li,mi), 
                                                                     cit2->holenvektor(li,mi),
                                                                     cit0->holenvektor(lli,lmi), 
                                                                     cit1->holenvektor(lli,lmi), 
                                                                     cit2->holenvektor(lli,lmi)); 
                                                                    };
                                                                   }else{//-------------------nur bitmap
                                                                    g->zeichnen( 
                                                                    vit0->ort(), 
                                                                    vit1->ort(), 
                                                                    vit2->ort(), 
                                                                    n0,n1,n2,
                                                                    cit0->farbe(), 
                                                                    cit1->farbe(), 
                                                                    cit2->farbe(), 
                                                                    cit0->holenvektor(li,mi), 
                                                                    cit1->holenvektor(li,mi), 
                                                                    cit2->holenvektor(li,mi)); 
                                                                   };
                                                                  );
                                                                  g->textur(false);
                                                                  g->transparenzadditiv();
                                                                  g->textureinheit(2);//glActiveTextureARB(GL_TEXTURE2_ARB);
                                                                  g->textur(false);//glDisable(GL_TEXTURE_2D);
                                                                  g->textureinheit(1);//glActiveTextureARB(GL_TEXTURE1_ARB);
                                                                  g->textur(false);//glDisable(GL_TEXTURE_2D);
                                                                  g->textureinheit(0);//glActiveTextureARB(GL_TEXTURE0_ARB);
                                                                  g->texturoperationmultiplikativ();//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                                                                 };//if zeichnenflaeche
                                                                };//if eigenetransformation==false
                                                                
                                                                if(eigenetransformation){//----------------------------------------------------------------------------------
                                                                 //kanten zeichnen
                                                                 if(zeichnenkante()){
                                                                  g->tiefenbufferkondition(false);
                                                                  g->tiefenbufferschreiben(false);
                                                                  iterieren(lnvit,g->zeichnen(lnvit->objekt()->orttransformation(),lnvit->naechstes()->objekt()->orttransformation(),pfarbekante));
                                                                  g->tiefenbufferkondition(true);
                                                                  g->tiefenbufferschreiben(true);
                                                                 };
                                                                 //normale zeichnen
                                                                 if(zeichnennormale()){
                                                                  g->tiefenbufferkondition(false);
                                                                  g->tiefenbufferschreiben(false);
                                                                  _vektor4<_to> c(0,1,0,0.5f);
                                                                  _vektor4<_to> cc(0,0.3f,0,0.5f);
                                                                  if(pflag!=0){
                                                                   c.setzen(1,0,0,0.5f); 
                                                                   cc.setzen(0.3f,0,0,0.5f);
                                                                  };
                                                                  g->textur(false);
                                                                  g->zeichnen(pmiddleparallel,pmiddlenormalparallel,c,cc);
                                                                  g->tiefenbufferkondition(true);
                                                                  g->tiefenbufferschreiben(true);
                                                                  
                                                                 };
                                                                }else{
                                                                 //kanten zeichnen
                                                                 if(zeichnenkante()){
                                                                  g->tiefenbufferkondition(false);
                                                                  g->tiefenbufferschreiben(false);
                                                                  iterieren(lnvit,g->zeichnen(lnvit->objekt()->ort(),lnvit->naechstes()->objekt()->ort(),pfarbekante));
                                                                  g->tiefenbufferkondition(true);
                                                                  g->tiefenbufferschreiben(true);
                                                                 };
                                                                 //normale zeichnen
                                                                 if(zeichnennormale()){
                                                                  g->tiefenbufferkondition(false);
                                                                  g->tiefenbufferschreiben(false);
                                                                  _vektor4<_to> c(1,1,0,0.5f);
                                                                  _vektor4<_to> cc(0,0.3f,0.5f,0.5f);
                                                                  if(pflag!=0){
                                                                   c.setzen(1,0,0,0.5f); 
                                                                   cc.setzen(0.3f,0,0,0.5f);
                                                                  };
                                                                  g->textur(false);
                                                                  g->zeichnen(pmiddle,pmiddle+normale(),c,cc);
                                                                  g->tiefenbufferkondition(true);
                                                                  g->tiefenbufferschreiben(true);
                                                                 };
                                                                };
                                                                
                                                                
};
void _polygon::zeichnen(_grafik*g,const _vektor4<_to>&col,int markverb){ //------------------------ für editonsdarstellung , mit farbe -----------------------------------------------------------------------------------
                                                                //polygon zeichnen 
                                                                //_vertex*vit0; 
                                                                //_vertex*vit1; 
                                                                //_vertex*vn; 
                                                                const _vektor3<_tg>&n=normale();
                                                                //_verbindervertexpolygon*pvcp; 
                                                                //_verbindervertexpolygon*vcp0; 
                                                                //_verbindervertexpolygon*vcp1; 
                                                                _vektor4<_to> ptc; 
                                                                _vektor2<_tg> tvn;
                                                                _bild<_tb>*bild=0; 
                                                                _bild<_tb>*lmap=0; 
                                                                _bild<_tb>*smap=0; 
                                                                unsigned int li=0; 
                                                                unsigned int mi=0; 
                                                                unsigned int lli=1;
                                                                unsigned int lmi=0;
                                                                unsigned int sli=5;
                                                                unsigned int smi=0;
                                                                bool zk=zeichnenkante();
                                                                bindentextur(g,bild,lmap,smap);
                                                                //------------------------ zeichnen mit hardwaretransformation -----------------------------------------------------------------------------------
                                                                if(zeichnenflaeche()){
                                                                 iterierendreieckverbinder(this,
                                                                  if(lmap){
                                                                   if(smap){
                                                                    g->zeichnen(//----------------- bitmap, lightmap und specularmap 
                                                                    vit0->ort(), 
                                                                    vit1->ort(), 
                                                                    vit2->ort(), 
                                                                    col, 
                                                                    col, 
                                                                    col, 
                                                                    cit0->holenvektor(li,mi), 
                                                                    cit1->holenvektor(li,mi), 
                                                                    cit2->holenvektor(li,mi),
                                                                    cit0->holenvektor(lli,lmi), 
                                                                    cit1->holenvektor(lli,lmi), 
                                                                    cit2->holenvektor(lli,lmi), 
                                                                    cit0->holenvektor(sli,smi), 
                                                                    cit1->holenvektor(sli,smi), 
                                                                    cit2->holenvektor(sli,smi)); 
                                                                   }else{//-------------------nur bitmap und lightmap
                                                                    g->zeichnen( 
                                                                    vit0->ort(), 
                                                                    vit1->ort(), 
                                                                    vit2->ort(), 
                                                                    n,n,n,
                                                                    col, 
                                                                    col, 
                                                                    col, 
                                                                    cit0->holenvektor(li,mi), 
                                                                    cit1->holenvektor(li,mi), 
                                                                    cit2->holenvektor(li,mi),
                                                                    cit0->holenvektor(lli,lmi), 
                                                                    cit1->holenvektor(lli,lmi), 
                                                                    cit1->holenvektor(lli,lmi)); 
                                                                   };
                                                                  }else{//-------------------nur bitmap
                                                                   if(bild){
                                                                   g->zeichnen( 
                                                                   vit0->ort(), 
                                                                   vit1->ort(), 
                                                                   vit2->ort(), 
                                                                   n,n,n,
                                                                   col, 
                                                                   col, 
                                                                   col, 
                                                                   cit0->holenvektor(li,mi), 
                                                                   cit1->holenvektor(li,mi), 
                                                                   cit2->holenvektor(li,mi)); 
                                                                   }else{
                                                                    g->zeichnen( 
                                                                    vit0->ort(), 
                                                                    vit1->ort(), 
                                                                    vit2->ort(), 
                                                                    col, 
                                                                    col, 
                                                                    col); 
                                                                   };
                                                                  };
                                                                 );
                                                                };
                                                                /*
                                                                g->textureinheit(2);//glActiveTextureARB(GL_TEXTURE2_ARB);
                                                                g->textur(false);//glDisable(GL_TEXTURE_2D);
                                                                g->textureinheit(1);//glActiveTextureARB(GL_TEXTURE1_ARB);
                                                                g->textur(false);//glDisable(GL_TEXTURE_2D);
                                                                g->textureinheit(0);//glActiveTextureARB(GL_TEXTURE0_ARB);
                                                                g->texturoperationmultiplikativ();//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
                                                                g->transparenz(true);
                                                                */
                                                                g->textur(false);
                                                                //kanten zeichnen
                                                                if(zk){
                                                                 _listenknoten<_vertex>*vit;
                                                                 _verbindervertexpolygon*cit;
                                                                 iterieren(vit,
                                                                  cit=static_cast<_verbindervertexpolygon*>(vit);
                                                                  if(markverb==cit->markierung()){
                                                                   cit->markierung(1-markverb);
                                                                   if(cit->gegenkante()) cit->gegenkante()->markierung(1-markverb);
                                                                   g->zeichnen(vit->objekt()->ort(),vit->naechstes()->objekt()->ort(),pfarbekante);
                                                                  };
                                                                 );
                                                                };
                                                                //normale zeichnen
                                                                if(zeichnennormale()){
                                                                 _vektor4<_to> c=col;
                                                                 _vektor4<_to> cc=c*0.5;
                                                                 if(pflag!=0){
                                                                  c.setzen(1,0,0,0.5f); 
                                                                  cc.setzen(0.3f,0,0,0.5f);
                                                                 };
                                                                 g->zeichnen(pmiddle,pmiddle+normale(),c,cc);
                                                                };                                                               


};
void _polygon::zeichnen(_grafik*g,const _vektor3<_to>&col,int markverb){ //------------------------ für editonsdarstellung , mit farbe -----------------------------------------------------------------------------------
                                                                _listenknoten<_vertex>*vit;
                                                                
                                                                if(anfang(vit)){
                                                                 _verbindervertexpolygon*cit=static_cast<_verbindervertexpolygon*>(vit);//vit->verbinder(this);
                                                                 _vektor4<_to> col4(col[0],col[1],col[2],cit->farbe()[3]);
                                                                 zeichnen(g,col4,markverb);
                                                                };
};

void _polygon::knotenzeichnung(_liste<_polygon>*l){
                                                                //deletesecure(pknotenzeichnung);
                                                                // pknotenzeichnung=
																l->einhaengen(this);
};
void _polygon::loeschenknotenzeichnung(){
                                                                //deletesecure(pknotenzeichnung);
};
void _polygon::netz(_netz*m){
                                                                pmesh=m;
};

bool _polygon::vergleichen(_polygon*p){
				                                                if(p){
				                                                 _tg x=pmiddle.x();
				                                                 _tg y=pmiddle.y();
				                                                 _tg z=pmiddle.z();
				                                                 _tg ox=p->pmiddle.x();
				                                                 _tg oy=p->pmiddle.y();
				                                                 _tg oz=p->pmiddle.z();
				                                                 _tg c=z+sqrt(x*x+y*y)*0.000005;
				                                                 _tg co=oz+sqrt(ox*ox+oy*oy)*0.000005;
	 			                                                 if(c<co) return(true);
				                                                };
				                                                return(false);
};

bool _polygon::hatintersektion(_polygon*p){
                                                                //funktion muss prüfen, ob this mit p einem schnittpunkt ergibt,
                                                                //dazu werden zunächst die Geraden von this mit der fläche von p geschnitten
                                                                //und dann umgekehrt
                                                                bool hasint;
                                                                bool invalid;
                                                             //   _vertex*vit;
                                                                //-----------
                                                                hasint=false;
                                                                invalid=false;
                                                                hasint=hatintersektionschraeg(p,invalid);
                                                                if(invalid==false){
                                                               //  hasint=hasintersectionparallel(p);
                                                                };
                                                                return(hasint);
};

bool _polygon::hatintersektionschraeg(_polygon*pp,bool&invalid){
                                                                //funktion determiniert intersektion, es wird zunächst von einer schräglage(unparallelität->oblizität)
                                                                //ausgegangen (wenn parallel gibt die funktion null zurück, um anzudeuten, dass parallel untersucht werden muss):
                                                                //1. es erfolgt eine 3x3 - determinante,um schnittpunkt mit der p-ebene zu bestimmen
                                                                //2. sequenzielle p-kante - mitte 2x2 determinante zur bestimmung der p-flächenkoherenz
                                                                _vektor3<_tg> ort;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> va;
                                                                _vektor3<_tg> vb;
                                                                _vektor3<_tg> vc;
                                                                _vektor3<_tg> mr;//relativer mittelpunkt
                                                                _vektor3<_tg> s;//schnittpunkt
                                                                _tg c;//determinanten vektorenparameter
                                                                _tg D;//hauptdeterminante
                                                                _vektor3<_tg> de;//2D - punktvektor
                                                                _vektor3<_tg> da;//2D - ebenevektor 1
                                                                _vektor3<_tg> db;//2D - ebenevektor 2
                                                                _vektor2<_tg> de2;//2D - punktvektor
                                                                _vektor2<_tg> da2;//2D - ebenevektor 1
                                                                _vektor2<_tg> db2;//2D - ebenevektor 2
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _verbindervertexpolygon*con;
                                                                _vektoranalysis2<_tg> V2;
                                                                _vektoranalysis3<_tg> V3;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //-------------------------
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vin=lnvit->naechstes()->objekt();
                                                                 con=static_cast<_verbindervertexpolygon*>(lnvit);//vit->connector(this);
                                                                 //if(con->markierung()==0){
                                                                 con->markierung(1);
                                                                 vc= vin->ort()- vit->ort();//vc=-kante->vektor();//vc= *kante->vertex(0) - *kante->vertex(1);//sub(kante->vertex[0]->o,kante->vertex[1]->o,vc);
                                                                 va=pp->ebene(0);//bewegen(pp->ebene[0]->o,va);
                                                                 vb=pp->ebene(1);//bewegen(pp->ebene[1]->o,vb);
                                                                 D=V3.determinieren(va,vb,-vc);
                                                                 if(D){//--------------------------------------------------------------schräglage
                                                                  e=vit->ort()-pp->mitte();//sub(kante->vertex[0]->ort,pp->mitte->o,e);
                                                                  c=V3.determinieren(va,vb,e)/D;
                                                                  if((c>=0)&&(c<=1)){
                                                                   s=vit->ort()+vc*c;
                                                                   //new _weltdebugkreuz(dynamic_cast<_netz*>(_listenknotenbasis<_polygon>::liste())->welt(),s,0.1,_vektor4<_to>(1,1,0,1));
                                                                   if(pp->innerhalbpunkt(s/*,0,v[0],v[1],v[2],pa,pb*/)) return(true);
                                                                  };
                                                                  invalid=false;
                                                                 }else{
                                                                  invalid=true;//parallel
                                                                 };
                                                                 //};//conector markierung==0;
                                                                );
                                                                return(false);
};
bool _polygon::innerhalbpunkt(const _vektor3<_tg>&p,const _tg nz,_vertex*&v0,_vertex*&v1,_vertex*&v2,_tg&a,_tg&b){
                                                                _tg alpha;
                                                                _tg beta;
                                                                _tg D;
                                                                //_vertex*vit1; //3 vertex iteratoren zum aufspalten von polys in triangles
                                                                //_vertex*vit2;
                                                                //_vertex*vit3;
                                                                _vektor2<_tg> dv0;
                                                                _vektor2<_tg> dv1;
                                                                _vektor2<_tg> e;
                                                                //_vektor2<_tg> invrd;
                                                                unsigned int c0=pcomponent[0];
                                                                unsigned int c1=pcomponent[1];
                                                                //-------------------------------
                                                                iterierendreieck(this,e.setzen(p[c0]- vit0->ort()[c0] , p[c1]- vit0->ort()[c1]),
                                                                 dv0.setzen(vit2->ort()[c0]-vit0->ort()[c0] , vit2->ort()[c1]-vit0->ort()[c1]);
                                                                 dv1.setzen(vit1->ort()[c0]-vit0->ort()[c0] , vit1->ort()[c1]-vit0->ort()[c1]);
                                                                 D=V2.determinieren(dv0,dv1);
                                                                 if((D>nz)||(D<-nz)){
                                                                  alpha=V2.determinieren(e,dv1)/D;
                                                                  if((alpha>-nz)&&(alpha<(1+nz))){
                                                                   beta=V2.determinieren(dv0,e)/D;
                                                                   if((beta>-nz)&&(beta<((1-alpha)+nz))){
                                                                    a=alpha;
                                                                    b=beta;
                                                                    v0=vit0;
                                                                    v1=vit1;
                                                                    v2=vit2;
                                                                    return(true);
                                                                   };
                                                                  };
                                                                 };
                                                                );
                                                                return(false);
};
bool _polygon::innerhalbpunkt(const _vektor3<_tg>&p){
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _vektor3<_tg> vn;
                                                                _vektor3<_tg> pn;
                                                                _vektor3<_tg> en;
                                                                _vektor3<_tg> h;
                                                                _tg D,c;
                                                                //-----------------
                                                                pn=normale();
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vin=lnvit->naechstes()->objekt();
                                                                 vn=vin->ort()-vit->ort();
                                                                 h=p-(vit->ort()+vn*0.5);
                                                                 vn.normalisieren();
                                                                 en=normale(vit->ort(),vin->ort());
                                                                 D=V3.determinieren(vn,pn,en);
                                                                 c=V3.determinieren(vn,pn,h)/D;
                                                                 if(c<0) return(false);
                                                                );
                                                                return(true);
};

bool _polygon::innerhalbkugel(_vektor3<_tg> kugelmitte,_tg radius){
                                                                _vektor3<_tg> lot;
                                                                _vektor3<_tg> lotebene;
                                                                _tg normalenparameter;
                                                                _tg kantenparameter;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //--------
                                                                //1. abstand kugelmitte und ebene : wenn größer radius außerhalb, raus
                                                                V3.lotpunktebene(kugelmitte,mitte(),normale(),lotebene,normalenparameter);
                                                                if(fabs(normalenparameter)>radius) return false;//außerhalb
                                                                //2./3. abstand kugelmitte und vertex und gültiges kantenlot: wenn kleiner radius innerhalb, raus
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vin=lnvit->naechstes()->objekt();
                                                                 lot=vit->ort()-kugelmitte;
                                                                 if(lot.laenge()<=radius) return(true);//innerhalb
                                                                 V3.lotpunktgerade(kugelmitte,vit->ort(),vin->ort()-vit->ort(),lot,kantenparameter);
                                                                 if((kantenparameter>=0)&&(kantenparameter<=1)) if(lot.laenge()<=radius) return(true);//innerhalb
                                                                );
                                                                //4. ebenenlotpunkt prüfen, ob er innerhalb von this ist : wenn ja innerhalb sonst außerhalb
                                                                return(innerhalbpunkt(kugelmitte+lotebene));
};

bool _polygon::innerhalbkugeltranslation(const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,_tg r,bool bewegungsculling){
                                                                if(vektor.laenge()<=0) return(false);
                                                                _tg ds,de,para,hl,hn,vvv;
                                                                unsigned int i0,i1;
                                                                //_tg m[3];
                                                                //_tg n[3];
                                                                //----------------------
                                                                if((bewegungsculling)&&(zweiseitig()==false))if((vektor* normale())>0) return(false);
                                                                _vektor3<_tg> ende;
                                                                ende=start;
                                                                ende+=vektor;
                                                                //-------------------------------------- ebenensabstand untersuchen----------------------------------------
                                                                _tg nx=normale()[0];
                                                                _tg ny=normale()[1];
                                                                _tg nz=normale()[2];
                                                                ds=((start[0]-pmiddle[0])*nx + (start[1]-pmiddle[1])*ny + (start[2]-pmiddle[2])*nz);
                                                                de=(( ende[0]-pmiddle[0])*nx + ( ende[1]-pmiddle[1])*ny + ( ende[2]-pmiddle[2])*nz);
                                                                if((ds>+r)&&(de>+r)) return(false);//kein schnitt
                                                                if((ds<-r)&&(de<-r)) return(false);//kein schnitt
                                                                //--------------------------------------genauer untersuchen -----------------------------------------------
                                                                _vektor3<_tg> vertexkante;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _tg vix,viy,viz;
                                                                _tg vnx,vny,vnz;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> lot;
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vin=lnvit->naechstes()->objekt();
                                                                 
                                                                 //-------------------------------------vertexabstand betrachten--------------------------------------------
                                                                 //l=vit->ort()-ende;
                                                                 //if(l.laenge()<r) return(true);//Schnitt
                                                                 vix=vit->ort()[0];
                                                                 viy=vit->ort()[1];
                                                                 viz=vit->ort()[2];
                                                                 lot.setzen(vix-ende[0],viy-ende[1],viz-ende[2]);
                                                                 if(lot.laenge()<=r) return(true);//schnitt an polyecke
                                                                 //V3.lotpunktgerade(vit->ort(),start,vektor,l,para);//p ist achsen parameter, ist nur gültig von 0 bis 1
                                                                 //if(l.laenge()<r) if((para>=0)&&(para<=1)) return(true);//schnitt
                                                                // vvv=vektor[0]*vektor[0] + vektor[1]*vektor[1] + vektor[2]*vektor[2];
                                                                 vvv=vektor.laengelaenge();
                                                                 
                                                                 
                                                                 h.setzen(vix-start[0],viy-start[1],viz-start[2]);
                                                                 para=(h*vektor)/vvv;
                                                                 if((para>=0)&&(para<=1)) {
                                                                  lot.setzen(-h[0]+vektor[0]*para,-h[1]+vektor[1]*para,-h[2]+vektor[2]*para);
                                                                  if(lot.laenge()<=r) return(true);
                                                                 };
                                                                 //---------------------------------vertexkantenabstand betrachten------------------------------------------
                                                                 
                                                                 vnx=vin->ort()[0];
                                                                 vny=vin->ort()[1];
                                                                 vnz=vin->ort()[2];
                                                                 vertexkante.setzen(vnx-vix,vny-viy,vnz-viz);
                                                                 //geradenparallelität abfangen
                                                                 lot=vektor%vertexkante;//::kreuzprodukt<_tg>(l,vektor.daten(),vertexkante);
                                                                 
                                                                 if(lot.laenge()>nahenull) {
                                                                  
                                                                  h=vertexkante%vektor;//::kreuzprodukt<_tg>(h,vertexkante,vektor.daten());
                                                                  hl=h.laenge();
                                                                  para=((start[0]-vix)*h[0] + (start[1]-viy)*h[1] + (start[2]-viz)*h[2])/hl;
                                                                  if(fabs(para)<=r){
                                                                   
                                                                   
                                                                   hn=para/hl;
                                                                   lot.setzen(h[0]*hn,h[1]*hn,h[2]*hn);
                                                                   unsigned int li=lot.groessterindex();
                                                                   
                                                                   if(li==0) {i0=1;i1=2;} else
                                                                   if(li==1) {i0=2;i1=0;} else
                                                                   if(li==2) {i0=0;i1=1;};
                                                                   
                                                                   _tg v0x=vektor[i0];
                                                                   _tg v0y=vektor[i1];
                                                                   _tg v1x=vertexkante[i0];
                                                                   _tg v1y=vertexkante[i1];
                                                                   _tg D2=v1x*-v0y - v1y*-v0x;
                                                                   
                                                                   
                                                                   if(fabs(D2)>nahenull){
                                                                    _tg ex=start[i0]-(*vit)[i0];
                                                                    _tg ey=start[i1]-(*vit)[i1];
                                                                    _tg gamma0=(v1x*ey -  v1y*ex )/D2;
                                                                    if((gamma0>=0)&&(gamma0<=1)){
                                                                     _tg gamma1=(ex*-v0y - ey*-v0x)/D2;
                                                                     if((gamma1>=0)&&(gamma1<=1)) return(true);//schnitt
                                                                    };
                                                                   }else{
                                                                    //parallelität
                                                                    //kann nicht sein, wird vorher abgefangen
                                                                   };
                                                                   
                                                                  };
                                                                  
                                                                 }else{
                                                                  //wird schon vorher gemacht : 
                                                                  //V3.lotpunktgerade(*vit,start,vektor,l,para);
                                                                  //if((para>=0)&&(para<=1)) if(l.laenge()<r) return(true);
                                                                 };
                                                                 
                                                                 //nun kugel ende auf vertexkanten loten
                                                                 //V3.lotpunktgerade(ende,vit->ort(),vertexkante,l,para);
                                                                 //if((para>=0)&&(para<=1)) if(l.laenge()<=r) return(true);//innerhalb
                                                                 vvv=vertexkante.laengelaenge();//vertexkante[0]*vertexkante[0] + vertexkante[1]*vertexkante[1] + vertexkante[2]*vertexkante[2];
                                                                 h.setzen(ende[0]-vix,ende[1]-viy,ende[2]-viz);
                                                                 para=(h*vertexkante)/vvv;
                                                                 if((para>=0)&&(para<=1)){
                                                                  lot.setzen(-h[0]+vertexkante[0]*para,-h[1]+vertexkante[1]*para,-h[2]+vertexkante[2]*para);
                                                                  if(lot.laenge()<=r) return(true);
                                                                 };
                                                                );
                                                                
                                                                //----------------------------- diskretion des reinen ebenenschnitts prüfen ---------------------------
                                                                //Es liegt unbedingt ein schnitt mit der ebene vor , es muss diskretion mit der polygonfläche geprüft werden
                                                                if(fabs(ds)<fabs(de)){
                                                                 if(ds<=r){
                                                                  //startlot[0]=start[0]+nx*-ds;
                                                                  //startlot[1]=start[1]+ny*-ds;
                                                                  //startlot[2]=start[2]+nz*-ds;
                                                                  _vektor3<_tg> startlot;
                                                                  startlot.setzen(start[0]+nx*-ds,start[1]+ny*-ds,start[2]+nz*-ds);
                                                                  if(innerhalbpunkt(startlot)) return(true);
                                                                 };
                                                                }else{
                                                                 if(de<=r){
                                                                  //endlot[0]=ende[0]+nx*-de;
                                                                  //endlot[1]=ende[1]+ny*-de;
                                                                  //endlot[2]=ende[2]+nz*-de;
                                                                  _vektor3<_tg> endlot;
                                                                  endlot.setzen(ende[0]+nx*-de,ende[1]+ny*-de,ende[2]+nz*-de);
                                                                  if(innerhalbpunkt(endlot)) return(true);
                                                                 };
                                                                };
                                                                if(((ds<-r)&&(de>+r))||((de<-r)&&(ds>+r))){
                                                                 //es liegt ein ebenen schnitt vor, 
                                                                 //diskretion prüfen
                                                                 _tg inv[3];
                                                                 inv[0]=-vektor[0];
                                                                 inv[1]=-vektor[1];
                                                                 inv[2]=-vektor[2];
                                                                 _tg HD=::determinieren(pplane[0].daten(),pplane[1].daten(),inv); 
                                                                 if(fabs(HD)>nahenull){//nicht parallel, schnittpunkt holen
                                                                  _tg erg[3];
                                                                  erg[0]=start[0]-pmiddle[0];
                                                                  erg[1]=start[1]-pmiddle[1];
                                                                  erg[2]=start[2]-pmiddle[2];
                                                                  //::subtrahieren(erg,start.daten(),m);
                                                                  _tg gamma=::determinieren(pplane[0].daten(),pplane[1].daten(),erg)/HD;
                                                                  if((gamma>=0)&&(gamma<=1)){
                                                                   _vektor3<_tg> schnitt(start[0]+vektor[0]*gamma,start[1]+vektor[1]*gamma,start[2]+vektor[2]*gamma);
                                                                   //schnitt[0]=start[0]+vektor[0]*gamma;
                                                                   //schnitt[1]=start[1]+vektor[1]*gamma;
                                                                   //schnitt[2]=start[2]+vektor[2]*gamma;
                                                                   if(innerhalbpunkt(schnitt)) return(true);//SCHNITT!!!
                                                                  };
                                                                 }else{
                                                                  //kann eigentlich nicht sein:
                                                                  //parallelität zwischen vektor und polygonebene liegt vor
                                                                  //es reicht EINEN PUNKT ZU PRÜFEN, da vorher keine kanten oder punkteschnitt auftrat !:
                                                                  //V3.lotpunktebene(start,pmiddle,ppoly->normale(),l,para);
                                                                  //if(innerhalbpunkt(start+l)) return(true);//SCHNITT !!
                                                                 };
                                                                };
                                                                
                                                                return(false);//KEIN SCHNITT
                                                                
};
bool _polygon::innerhalbpolygontranslation(_polygon*polygon,const _vektor3<_tg>&start,_liste<_vektor3<_tg> >*orte,const _vektor3<_tg>&vektor,bool bewegungsculling){
                                                                //das polygon this wird als statisch betrachtet
                                                                //das bewegte polygon wird repräsentiert durch polygon,start, orte und vektor
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_vektor3<_tg> >*it;
                                                                _listenknoten<_vektor3<_tg> >*itstart;
                                                                if(bewegungsculling)if((vektor* normale())>0) return(false);
                                                                //-------------------------------------- ebenensabstand untersuchen----------------------------------------
                                                                int smin,smax;
                                                                unsigned int ortanzahl=orte->anzahl();
                                                                unsigned int i;
                                                                _tg ds,de;
                                                                _tg nx=normale()[0];
                                                                _tg ny=normale()[1];
                                                                _tg nz=normale()[2];
                                                                _vektor3<_tg> ende;
                                                                _vektor3<_tg> startx;
                                                                orte->anfang(itstart);
                                                                smin=smax=0;
                                                                it=itstart;
                                                                startx=start;
                                                                for(i=0;i<ortanzahl+1;i++){
                                                                 ende=startx+vektor;
                                                                 ds=((startx[0]-pmiddle[0])*nx + (startx[1]-pmiddle[1])*ny + (startx[2]-pmiddle[2])*nz);
                                                                 de=((  ende[0]-pmiddle[0])*nx + (  ende[1]-pmiddle[1])*ny + (  ende[2]-pmiddle[2])*nz);
                                                                 if((ds>0)&&(de>0)) smax=+1;//return(false);//kein schnitt
                                                                 if((ds<0)&&(de<0)) smin=-1;//return(false);//kein schnitt
                                                                 startx=start+*it->objekt();
                                                                 it=it->naechstes();
                                                                };
                                                                if((smin<0)&&(smax==0)) return(false);//alle punkte hinter der ebene von this
                                                                if((smin==0)&&(smax>0)) return(false);//alle punkte vor der ebene von this
                                                                //-------------------------------------- schnittpunkte holen ----------------------------------------------
                                                                _tg D;
                                                                _tg g;
                                                                _vektoranalysis3<_tg> V3;
                                                                if(fabs(polygon->normale()*vektor)>nahenull){//--------- bewegung ist nicht senkrecht zur normale -----------------
                                                                 //prüfen, ob eine vertexbewegung des 
                                                                 //bewegten poly einen diskreten schnittpunkt ergibt
                                                                 D=V3.determinieren(pplane[0],pplane[1],-vektor);
                                                                 it=itstart;
                                                                 startx=start;
                                                                 for(i=0;i<ortanzahl+1;i++){
                                                                  g=V3.determinieren(pplane[0],pplane[1],startx-pmiddle)/D;
                                                                  if(g>=0){
                                                                   if(g<=1){
                                                                    if(innerhalbpunkt(startx+vektor*g)){
                                                                     return(true);
                                                                    };
                                                                   };
                                                                  };
                                                                  startx=start+*it->objekt();
                                                                  it=it->naechstes();
                                                                 };
                                                                 //prüfen, ob eine vertexbewegung des 
                                                                 //statischen poly einen diskreten schnittpunkt ergibt
                                                                 D=V3.determinieren(polygon->pplane[0],polygon->pplane[1],vektor);
                                                                 iterieren(lnvit,
                                                                  vit=lnvit->objekt();
                                                                  g=V3.determinieren(polygon->pplane[0],polygon->pplane[1],vit->ort()-*itstart->objekt())/D;
                                                                  if(g>=0){
                                                                   if(g<=1){
                                                                    if(polygon->innerhalbpunkt((vit->ort()-vektor*g)-(*itstart->objekt()-polygon->vertex()->ort()))){
                                                                     return(true);
                                                                    };
                                                                   };
                                                                  };
                                                                 );
                                                                 //kanten als ebenen darstellen und den
                                                                 //schnittpunkt prüfen mit den ebenen des
                                                                 //bewegten polygons
                                                                 _vektor3<_tg> kante;
                                                                 _vektor3<_tg> kantethis;
                                                                 startx=start;
                                                                 it=itstart;
                                                                 for(i=0;i<ortanzahl+1;i++){
                                                                  if(i==0){
                                                                   kante=*it->objekt();
                                                                  }else{
                                                                   if(i==ortanzahl){
                                                                    kante=-*it->objekt();
                                                                   }else{
                                                                    kante=(*it->objekt()+start)-startx;
                                                                   };
                                                                  };
                                                                  iterieren(lnvit,
                                                                   vit=lnvit->objekt();
                                                                   vin=lnvit->naechstes()->objekt();
                                                                   kantethis=vin->ort()-vit->ort();
                                                                   D=V3.determinieren(kante,vektor,-kantethis);
                                                                   if(fabs(D)>nahenull){
                                                                    g=V3.determinieren(kante,vektor,vit->ort()-startx)/D;
                                                                    if(g>=0){
                                                                     if(g<=1){
                                                                      _tg a=V3.determinieren(vit->ort()-startx,vektor,-kantethis)/D;
                                                                      if(a>=0){
                                                                       if(a<=1){
                                                                        _tg b=V3.determinieren(kante,vit->ort()-startx,-kantethis)/D;
                                                                        if(b>=0){
                                                                         if(b<=1){
                                                                          return(true);
                                                                         };
                                                                        };
                                                                       };
                                                                      };
                                                                     };
                                                                    };
                                                                   };
                                                                  );
                                                                  startx=start+*it->objekt();
                                                                  it=it->naechstes();
                                                                 };
                                                                 /*if(orte->anfang(it))do{
                                                                  if(it!=itstart) startx=*itstart->objekt() + *it->objekt();
                                                                  ende=start+vektor;
                                                                  if(it->naechstes()==itstart) kante=*itstart->objekt() - start; else kante=(*it->naechstes()->objekt()+*itstart->objekt()) -start;
                                                                 }while(orte->naechstes(it));*/
                                                                }else{//--------------------------------- bewegung ist senkrecht zur normale -----------------------------
                                                                };
                                                                return(false);
};
bool _polygon::innerhalbnetztranslation(_netz*netz,const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,bool bewegungsculling){
                                                                _polygon*pit;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                netz->anfang(pit);
                                                                _vektor3<_tg> ortschieb=start-pit->vertex()->ort();
                                                                int smin,smax;
                                                                //-----
                                                                smin=smax=0;
                                                                 if(bewegungsculling)if((vektor* normale())>0) return(false);
                                                                 //if( fabs(pit->normale()*normale())>1-nahenull) return(false);
                                                                 //-------------------------------------- ebenensabstand untersuchen----------------------------------------
                                                                 //smin=0;
                                                                 //smax=0;
                                                                 _tg ds,de;
                                                                 _tg nx=normale()[0];
                                                                 _tg ny=normale()[1];
                                                                 _tg nz=normale()[2];
                                                                 _vektor3<_tg> ende;
                                                                 _vektor3<_tg> startx;                                                                
                                                                iterierenliste(netz,pit,
                                                                 iterierenliste(pit,lnvit,
                                                                  vit=lnvit->objekt();
                                                                  startx=vit->ort() + ortschieb;
                                                                  ende=startx+vektor;
                                                                  ds=((startx[0]-pmiddle[0])*nx + (startx[1]-pmiddle[1])*ny + (startx[2]-pmiddle[2])*nz);
                                                                  de=((  ende[0]-pmiddle[0])*nx + (  ende[1]-pmiddle[1])*ny + (  ende[2]-pmiddle[2])*nz);
                                                                  if((ds>0)&&(de>0)) smax=+1;//return(false);//kein schnitt
                                                                  if((ds<0)&&(de<0)) smin=-1;//return(false);//kein schnitt
                                                                  vit->markierung(2);
                                                                  vit->markierungverbinder(2);
                                                                 );
                                                                );
                                                                if((smin<0)&&(smax==0)) return(false);
                                                                if((smin==0)&&(smax>0)) return(false);
                                                                //-------------------------------------- gegenseitige vertexgeraden prüfungen -------------------
                                                                netz->anfang(pit);
                                                                if(innerhalbnetztranslationrekursiv(pit->vertex(),ortschieb,vektor)) return(true);
                                                                //_vertex*vit;
                                                                _tg D;
                                                                iterieren(lnvit,
                                                                 iterierenliste(netz,pit,
                                                                  //nun werden alle vertexen von this, die durch
                                                                  //vt beschrieben werden, in die entgegengesetzte richtung
                                                                  //bewet und mit dem polygon pit des netzes geschnitten
                                                                  
                                                                  D=V3.determinieren(pit->pplane[0], pit->pplane[1],vektor);
                                                                  if(fabs(D)>nahenull){
                                                                   _tg g=V3.determinieren(pit->pplane[0],pit->pplane[1],vit->ort()-(pit->pmiddle+ortschieb))/D;
                                                                   if(g>=0){
                                                                    if(g<=1){
                                                                     if(pit->innerhalbpunkt((vit->ort()-vektor*g)-ortschieb)) return(true);
                                                                    };
                                                                   };
                                                                  };
                                                                 );
                                                                );
                                                                
                                                                //--------------------------------- vertexkanten ebenenprüfung ----------------------------------
                                                                netz->anfang(pit);
                                                                if(innerhalbnetztranslationebenerekursiv(pit->vertex(),ortschieb,vektor)) return(true);
                                                                return(false);
};                                                                
bool _polygon::innerhalbnetztranslationrekursiv(_vertex*vit,const _vektor3<_tg>&ortschieb,const _vektor3<_tg>&vektor){
                                                                _tg D;
                                                                //---------------------------
                                                                if(vit->markierung()==2){
                                                                 vit->markierung(1);
                                                                 D=V3.determinieren(pplane[0],pplane[1],-vektor);
                                                                 if(fabs(D)>nahenull){
                                                                  _vektor3<_tg> start=(vit->ort()+ortschieb);
                                                                  _tg g=V3.determinieren(pplane[0],pplane[1],start-pmiddle)/D;
                                                                  if(g>=0){
                                                                   if(g<=1){
                                                                    if(innerhalbpunkt(start+vektor*g)) return(true);
                                                                   };
                                                                  };
                                                                 };
                                                                 _verbindervertexpolygon*cit;
                                                                 _listenknoten<_polygon>*lnpit;
                                                                 iterierenliste(vit,lnpit,
                                                                  cit=static_cast<_verbindervertexpolygon*>(lnpit);
                                                                  if(cit->markierung()==2){
                                                                   cit->markierung(1);
                                                                   if(innerhalbnetztranslationrekursiv(cit->naechstervertex(),ortschieb,vektor)) return(true);
                                                                  };
                                                                 );
                                                                };
                                                                return(false);
};
bool _polygon::innerhalbnetztranslationebenerekursiv(_vertex*vertex,const _vektor3<_tg>&ortschieb,const _vektor3<_tg>&vektor){
                                                                _verbindervertexpolygon*cit;
                                                                _vektor3<_tg> kante;
                                                                _vektor3<_tg> kantethis;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_polygon>*lnpit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //-------------------
                                                                iterierenliste(vertex,lnpit,
                                                                 cit=static_cast<_verbindervertexpolygon*>(lnpit);
                                                                 if(cit->markierung()==1){
                                                                  cit->markierung(0);
                                                                  cit->gegenkante()->markierung(0);
                                                                  kante=cit->naechstervertex()->ort() - vertex->ort();
                                                                  iterieren(lnvit,
                                                                   vit=lnvit->objekt();
                                                                   vin=lnvit->naechstes()->objekt();
                                                                   kantethis=vin->ort()-vit->ort();
                                                                   _tg D=V3.determinieren(kante,vektor,-kantethis);
                                                                   if(fabs(D)>nahenull){
                                                                    _vektor3<_tg> h=vit->ort()-(vertex->ort()+ortschieb);
                                                                    _tg g=V3.determinieren(kante,vektor,h)/D;
                                                                    if(g>=0){
                                                                     if(g<=1){
                                                                      _tg a=V3.determinieren(h,vektor,-kantethis)/D;
                                                                      if(a>=0){
                                                                       if(a<=1){
                                                                        _tg b=V3.determinieren(kante,h,-kantethis)/D;
                                                                        if(b>=0){
                                                                         if(b<=1){
                                                                          return(true);
                                                                         };
                                                                        };
                                                                       };
                                                                      };
                                                                     };
                                                                    };
                                                                   };
                                                                  );
                                                                  if(innerhalbnetztranslationebenerekursiv(cit->naechstervertex(),ortschieb,vektor)) return(true);
                                                                 };
                                                                );
                                                                return(false);
};
bool _polygon::innerhalbpunktrotation(const _vektor3<_tg>&punkt,const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt){
                                                                _vektor3<_tg> a=achse;
                                                                a.normalisieren();
                                                                if(fabs(normale()*a)<(1-nahenull)){
                                                                 _vektor3<_tg> lot;
                                                                 _vektor3<_tg> gv;
                                                                 _vektor3<_tg> go;
                                                                 _vektor3<_tg> pe;
                                                                 _vektor3<_tg> re;
                                                                 _vektoranalysis3<_tg> va;
                                                                 _tg D,c,para,radius,l;
                                                                 //schnittgerade go,gv bestimmen
                                                                 gv=a%normale();
                                                                 if(fabs(pplane[0]*gv)<fabs(pplane[1]*gv)){
                                                                  pe=pplane[0];
                                                                 }else{
                                                                  pe=pplane[1];
                                                                 };
                                                                 re=a%gv;
                                                                 D=va.determinieren(gv,re,-pe);
                                                                 if(fabs(D)>nahenull){
                                                                  c=va.determinieren(gv,re,pmiddle-punkt)/D;
                                                                  go=pmiddle+pe*c;
                                                                  //loten auf schnittgerade
                                                                  _vektor3<_tg> pv=punkt-achsenort;//eine andere art zu loten
                                                                  pv.projizierenebene(achse);
                                                                  va.lotpunktgerade(punkt-pv,go,gv,lot,para);
                                                                  l=lot.laenge();
                                                                  radius=pv.laenge();//lotlänge ist radius
                                                                  //L->schreiben("gv=",gv);
                                                                  //L->schreiben("go",go);
                                                                  //L->schreiben("lot",lot);
                                                                  //L->schreiben("punkt=",punkt);
                                                                  //radial culling
                                                                  if(l>((1*radius)+nahenull)) return(false);
                                                                  //schnitte mit kreis holen 
                                                                  _vektor3<_tg> v[2];
                                                                  _vektor3<_tg> r90;
                                                                  _tg ank=sqrt((radius*radius)-(l*l));
                                                                  v[0]=lot+gv*ank;
                                                                  v[1]=lot-gv*ank;
                                                                  //für folgende werte wird ein 360°-gültiger winkel
                                                                  //benötigt : pv(=0), v0,v1
                                                                  //wir wählen den ursprung des polaren koordinatensystems
                                                                  //mit pv. r90 ist der um +90° dazu gedrehte richtvektor 
                                                                  _tg ws[2];
                                                                  ws[0]=pv.winkel(v[0]);
                                                                  ws[1]=pv.winkel(v[1]);
                                                                  //folgende zeilen sind dasgleiche wie:
                                                                  //va.rotieren(achse,pv,-90,r90) .
                                                                  _vektor3<_tg> pvn=pv;
                                                                  pvn.normalisieren();
                                                                  r90=achse%pvn;
                                                                  if((v[0]*r90)<0) ws[0]=(180-ws[0])+180;
                                                                  if((v[1]*r90)<0) ws[1]=(180-ws[1])+180;
                                                                  //kreisbahnabschnittsdiskretion prüfen
                                                                  _tg wr;//relevanter schnittwinkel
                                                                  _vektor3<_tg> vr;//relevanter vektor
                                                                  bool diskret=false;
                                                                  if(ws[0]<=fabs(winkelschritt)){
                                                                   wr=ws[0];
                                                                   vr=v[0];
                                                                   diskret=true;
                                                                  };
                                                                  if(ws[1]<=fabs(winkelschritt)){
                                                                   if(diskret){
                                                                    if(ws[1]<wr){
                                                                     wr=ws[1]; 
                                                                     vr=v[1];
                                                                    };
                                                                   }else{
                                                                    wr=ws[1];
                                                                    vr=v[1];
                                                                    diskret=true;
                                                                   };
                                                                  };
                                                                  //L->schreiben("ws0=",ws[0]);
                                                                  //L->schreiben("ws1=",ws[1]);
                                                                  //L->schreiben("ws=",winkelschritt);
                                                                  //L->schreiben("pv=",pv);
                                                                  //L->schreiben("v0=",v[0]);
                                                                  //L->schreiben("v1=",v[1]);
                                                                  //L->schreiben(".");
                                                                  if(diskret==false) return(false);
                                                                  //L->schreiben("v0=",v[0]);
                                                                  //L->schreiben("v1=",v[1]);
                                                                  //L->schreiben("vr=",vr);
                                                                  //L->schreiben("punkt=",punkt);
                                                                  //L->schreiben("pv=",pv);
                                                                  //L->schreiben("achsenort=",achsenort);
                                                                  //polygondiskretion prüfen
                                                                  if(innerhalbpunkt((punkt-pv)+vr)) return(true);
                                                                 };
                                                                };
                                                                return(false);
};
bool _polygon::innerhalbkugelrotation(const _vektor3<_tg>&ort,const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt,const _tg radius){
                                                                _vektoranalysis3<_tg> va;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //-----------------------
                                                                //schneidet die kreisbahn von ort die
                                                                //um radius entlang der normale vorgeschobenen polygonebene diskret ?
                                                                //....wie oben
                                                                //schneidet die kreisbahn von ort den 
                                                                //um radius verbreiterten vertex von this?
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 if(va.kugelinnerhalbpunktrotation(vit->ort(),radius,ort,achsenort,achse,winkelschritt)) return(true);
                                                                );
                                                                //schneidet die kreisbahn von ort den 
                                                                //um radius verbreiterte kante von *vit-*vin?
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vin=lnvit->naechstes()->objekt();
                                                                 if(va.zylinderinnerhalbpunktrotation(vit->ort(),vit->ort()+(vin->ort()-vit->ort()),radius,ort,achsenort,achse,winkelschritt)) return(true);
                                                                );
                                                                return(false);
};

bool _polygon::schnittpunkt(_vektor3<_tg>&ort,_vektor3<_tg>&vektor,_tg nz,_tg gammamin,_tg gammamax,_tg&a,_tg&b,_tg&c){
                                                                //beschleunigte kollisionsfunktion
                                                                //folgende komponenten werden benötigt:
                                                                // * _vektoranalysis3<_tg> V2
                                                                // * _vektoranalysis3<_tg> V3
                                                                // * pcomponent
                                                                // * mittelpunkt und planevektoren
                                                                // * ph
                                                                _tg D;
                                                                //---------
                                                                D= -vektor*ph;
                                                                if((D>nz)||(D<nz)){
                                                                 _tg gamma;
                                                                 _vektor3<_tg> e;
                                                                 e=ort-pmiddle;
                                                                 gamma=(e*ph)/D;
                                                                 if((gamma>=gammamin)&&(gamma<=gammamax)){
                                                                  _listenknoten<_kantepolygon >*eit;
                                                                  _kantepolygon*kante;
                                                                  if(pedges.anfang(eit)){
                                                                   _vektor3<_tg> s;
                                                                   _vektor2<_tg> s2;
                                                                   s=(ort+vektor*gamma);//-pmiddle;
                                                                   s2.setzen(s[pcomponent[0]],s[pcomponent[1]]);
                                                                   bool innen=true;
                                                                   _tg para;
                                                                   do{
                                                                    kante=eit->objekt();
                                                                    para=V2.determinieren(kante->vektor2d(this),s2-kante->mitte2d(this))/kante->determinante2d(this);
                                                                    if(para<0) innen=false;
                                                                   }while((pedges.naechstes(eit))&&(innen));
                                                                   if(innen){
                                                                    a=V3.determinieren(-vektor,e,pplane[1])/D;
                                                                    b=V3.determinieren(-vektor,pplane[0],e)/D;
                                                                    c=gamma;
                                                                    return(true);
                                                                   }else return(false);//nicht innerhalb
                                                                  }else return(false);//error : keine kanten vorhanden
                                                                 }else return(false);//schnittpunkt nicht innerhalb der diskreten gerade
                                                                }else return(false);//zu parallel
};


bool _polygon::schnittpunkt(_vektor3<_tg>&ort,_vektor3<_tg>&vektor,_tg nz,bool nurpositive,_tg&a,_tg&b,_tg&c){
                                                                //beschleunigte kollisionsfunktion
                                                                //folgende komponenten werden benötigt:
                                                                // * _vektoranalysis3<_tg> V3
                                                                // * pcomponent
                                                                // * mittelpunkt und planevektoren
                                                                // * ph
                                                                _tg D;
                                                                //---------
                                                                D= -vektor*ph;
                                                                if((D>nz)||(D<nz)){
                                                                 _tg gamma;
                                                                 _vektor3<_tg> e;
                                                                 e=ort-pmiddle;
                                                                 gamma=(e*ph)/D;
                                                                 if((  (nurpositive)&&(gamma>nz)   )||(nurpositive==false)){
                                                                  _listenknoten<_kantepolygon >*eit;
                                                                  _kantepolygon*kante;
                                                                  if(pedges.anfang(eit)){
                                                                   _vektor3<_tg> s;
                                                                   _vektor2<_tg> s2;
                                                                   s=(ort+vektor*gamma);//-pmiddle;
                                                                   s2.setzen(s[pcomponent[0]],s[pcomponent[1]]);
                                                                   bool innen=true;
                                                                   _tg para;
                                                                   do{
                                                                    kante=eit->objekt();
                                                                    para=V2.determinieren(kante->vektor2d(this),s2-kante->mitte2d(this))/kante->determinante2d(this);
                                                                    if(para<0) innen=false;
                                                                   }while((pedges.naechstes(eit))&&(innen));
                                                                   if(innen){
                                                                    a=V3.determinieren(-vektor,e,pplane[1])/D;
                                                                    b=V3.determinieren(-vektor,pplane[0],e)/D;
                                                                    c=gamma;
                                                                    return(true);
                                                                   }else return(false);//nicht innerhalb
                                                                  }else return(false);//error : keine kanten vorhanden
                                                                 }else return(false);//schnittpunkt nicht innerhalb der diskreten gerade
                                                                }else return(false);//zu parallel
};

bool _polygon::schnittpunkt(_vektor3<_tg>&ort,_vektor3<_tg>&vektor,_tg nz,bool nurpositive,_vertex*&v0,_vertex*&v1,_vertex*&v2,_tg&a,_tg&b,_tg&c){
                                                                _tg alpha;
                                                                _tg beta;
                                                                _tg gamma;
                                                                _vektor3<_tg> dv0;
                                                                _vektor3<_tg> dv1;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> invrd;
                                                                _tg D;
                                                                //-------------------------
                                                                invrd=vektor*-1;
                                                                iterierendreieck(this,e=ort-vit0->ort(),
                                                                 dv0=vit2->ort()-vit0->ort();
                                                                 dv1=vit1->ort()-vit0->ort();
                                                                 D=V3.determinieren(dv0, dv1, invrd);
                                                                 if((D>nz)||(D<nz)){
                                                                  if(nurpositive){
                                                                   gamma=V3.determinieren(dv0, dv1, e)/D;
                                                                   if(gamma>0){
                                                                    alpha=V3.determinieren(e,dv1,invrd)/D;
                                                                    beta=V3.determinieren(dv0,e,invrd)/D;
                                                                    if((alpha>0)&&(alpha<1)&&(beta>0)&&(beta<1-alpha)){
                                                                     a=alpha;
                                                                     b=beta;
                                                                     c=gamma;
                                                                     v0=vit0;
                                                                     v1=vit1;
                                                                     v2=vit2;
                                                                     return(true);
                                                                    };
                                                                   };
                                                                  }else{
                                                                   gamma=V3.determinieren(dv0, dv1, e)/D;
                                                                   alpha=V3.determinieren(e,dv1,invrd)/D;
                                                                   beta=V3.determinieren(dv0,e,invrd)/D;
                                                                   if((alpha>0)&&(alpha<1)&&(beta>0)&&(beta<1-alpha)){
                                                                    a=alpha;
                                                                    b=beta;
                                                                    c=gamma;
                                                                    v0=vit0;
                                                                    v1=vit1;
                                                                    v2=vit2;
                                                                    return(true);
                                                                   };
                                                                  };
                                                                 };
                                                                );
                                                                return(false);
};                                                                  

bool _polygon::schnittpunkt(_vektor3<_tg>&ort,_vektor3<_tg>&vektor,_tg nz,_tg gammamin,_tg gammamax,_vertex*&v0,_vertex*&v1,_vertex*&v2,_tg&a,_tg&b,_tg&c){
                                                                //bestimmt den schnittpunkt der gearden ort,vektor mit dem poly, läd alle parameter
                                                                //wird zB vom lightmapbestrahlung genutzt
                                                                //-------------------------
                                                                _vektor3<_tg> ende=ort;
                                                                ende+=vektor;
                                                                if(gammamin==0)if(gammamax==1){
                                                                 const _vektor3<_tg>&n=normale();
                                                                 _tg d1=((ort[0]-pmiddle[0])* n[0] + (ort[1]-pmiddle[1])*n[1] + (ort[2]-pmiddle[2])*n[2]);
                                                                 _tg d2=((ende[0]-pmiddle[0])*n[0] + (ende[1]-pmiddle[1])*n[1] + (ende[2]-pmiddle[2])*n[2]);
                                                                 if((d1>nahenull)&&(d2>nahenull)) return(false);//kein schnitt
                                                                 if((d1<nahenull)&&(d2<nahenull)) return(false);//kein schnitt
                                                                };
                                                                
                                                                _tg D=V3.determinieren(pplane[0], pplane[1], -vektor);
                                                                if(fabs(D)>nz){
                                                                 c=V3.determinieren(pplane[0],pplane[1],ort-pmiddle)/D;
                                                                  if((c>gammamin)&&(c<gammamax)){
                                                                  _vektor3<_tg> schnitt=vektor;
                                                                  schnitt*=c;
                                                                  schnitt+=ort;
                                                                  if(innerhalbpunkt(schnitt,nz,v0,v1,v2,a,b)) return(true);
                                                                 }; 
                                                                }else{
                                                                 //parallel
                                                                };
                                                                return(false);
};                                                                  

bool _polygon::schnittpunkt(_vektor3<_tg>&ort,_vektor3<_tg>&vektor,_tg nz,_tg gammamin,_tg gammamax){
                                                                _tg alpha;
                                                                _tg beta;
                                                                _tg gamma;
                                                                _vektor3<_tg> dv0;
                                                                _vektor3<_tg> dv1;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> invrd;
                                                                _tg D;
                                                                //-------------------------
                                                                invrd=vektor*-1;
                                                                iterierendreieck(this,e=ort- vit0->ort(),
                                                                 dv0=vit2->ort()-vit0->ort();
                                                                 dv1=vit1->ort()-vit0->ort();
                                                                 D=V3.determinieren(dv0, dv1, invrd);
                                                                 if((D>nz)||(D<nz)){
                                                                  gamma=V3.determinieren(dv0, dv1, e)/D;
                                                                  if((gamma>=gammamin)&&(gamma<=gammamax)){
                                                                   alpha=V3.determinieren(e,dv1,invrd)/D;
                                                                   beta=V3.determinieren(dv0,e,invrd)/D;
                                                                   if((alpha>0)&&(alpha<1)&&(beta>0)&&(beta<1-alpha)){
                                                                    return(true);
                                                                   };
                                                                  };
                                                                 };
                                                                );
                                                                return(false);
};                                     

bool _polygon::schnittpunktkugeltranslation(const _vektor3<_tg>&ort,const _vektor3<_tg>&vektor,const _tg radius,_vektor3<_tg>&pnormale,_vektor3<_tg>&schnittpunkt,_tg&parameter){
                                                                _vektor3<_tg> ortrad;
                                                                _tg D;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _tg parameterg,parameterz;
                                                                _tg gamma;
                                                                _polygon*nb;
                                                                _vektor3<_tg> lot;
                                                                //--------------------------- Schnitt mit der Polygonenbene prüfen ------------
                                                                //ortrad=ort - *this*radius;
                                                                if(zweiseitig()==false) if((vektor* normale())>0) return(false);
                                                                D=V3.determinieren(pplane[0],pplane[1],-vektor);
                                                                if(fabs(D)>nahenull){
                                                                 
                                                                 gamma=V3.determinieren(pplane[0],pplane[1],ort-(pmiddle+normale()*(radius/*+nahenull*/)))/D;
                                                                 if((gamma>=0)&&(gamma<=1)){
                                                                  schnittpunkt=ort + vektor*gamma;
                                                                  
                                                                  if(innerhalbpunkt(schnittpunkt- normale() * radius)){
                                                                   pnormale=normale();
                                                                   parameter=gamma;
                                                                  // new _weltdebugpfeil(pmesh->welt(),schnittpunkt-normale()*radius,schnittpunkt,0.01,0.005,_vektor4<_to>(1,0,1));
                                                                  // L->schreiben("Ebenenkollision radial verbreitert");
                                                                   return(true);//schnitt mit der ebene is aufgetreten
                                                                  };
                                                                 };
                                                                 //-------------------------- Schnittmit den Kantenzylindern & Eckkugeln prüfen ----------
                                                                 if(anfang(lnvit))do{
                                                                  vit=lnvit->objekt();
                                                                  vin=lnvit->naechstes()->objekt();
                                                                  nb=nachbar(vit,vin);
                                                                  bool machen=false;
                                                                  if(nb){
                                                                   if(((nb->pmiddle - pmiddle)* normale())<0) machen=true;
                                                                  }else machen=true;
                                                                  if(machen){
                                                                  
                                                                   if(V3.schnittpunktgeradezylinder(ort,vektor,vit->ort(),vin->ort()-vit->ort(),radius,parameter,parameterz,pnormale,schnittpunkt)){
                                                                    parameterg=parameter;
                                                                    if((parameterg>=0)&&(parameterg<=1)){
                                                                     
                                                                     V3.lotpunktgerade(schnittpunkt,vit->ort(),vin->ort()-vit->ort(),lot,parameterz);
                                                                     if((parameterz>=0)&&(parameterz<=1)) {
                                                                      pnormale=-lot;
                                                                      pnormale.normalisieren();
                                                                     // new _weltdebugpfeil(pmesh->welt(),schnittpunkt,schnittpunkt+pnormale,0.01,0.005,_vektor4<_to>(1,0,0));
                                                                     // L->schreiben("Zylinderkollision radial verbreitert");
                                                                      return(true);//schnitt mit der Kante ist aufgetreten
                                                                     };
                                                                    };
                                                                   };
                                                                  };
                                                                  if(V3.schnittpunktgeradekugel(ort,vektor,vit->ort(),radius,schnittpunkt,parameter)){
                                                                   pnormale=schnittpunkt-vit->ort();
                                                                   pnormale.normalisieren();
                                                                   //L->schreiben("Kugelkollision radial verbreitert");
                                                                   return(true);
                                                                  };
                                                                 }while(naechstes(lnvit));
                                                                }else{
                                                                 //parallelität von gerade und ebene
                                                                };
                                                                return(false);
};
bool _polygon::schnittpunktpolygontranslation(_polygon*polygon,const _vektor3<_tg>&start,_liste<_vektor3<_tg> >*orte,const _vektor3<_tg>&vektor,_vektor3<_tg>&pnormale,_vektor3<_tg>&schnittpunkt,_tg&parameter){
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_vektor3<_tg> >*it;
                                                                _listenknoten<_vektor3<_tg> >*itstart;
                                                                _tg D;
                                                                _tg g;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> ende;
                                                                _vektor3<_tg> startx;
                                                                _vektor3<_tg> h;
                                                                unsigned int ortanzahl=orte->anzahl();
                                                                unsigned int i;
                                                                bool r=false;
                                                                //------------------------------------
                                                                parameter=+2;
                                                                orte->anfang(itstart);
                                                                it=itstart;
                                                                if(fabs(polygon->normale()*vektor)>nahenull){//--------- bewegung ist nicht senkrecht zur normale -----------------
                                                                 //prüfen, ob eine vertexbewegung des 
                                                                 //bewegten poly einen diskreten schnittpunkt ergibt
                                                                 D=V3.determinieren(pplane[0],pplane[1],-vektor);
                                                                 it=itstart;
                                                                 startx=start;
                                                                 for(i=0;i<ortanzahl+1;i++){
                                                                  g=V3.determinieren(pplane[0],pplane[1],startx-pmiddle)/D;
                                                                  if(g>=0){
                                                                   if(g<=1){
                                                                    if(innerhalbpunkt(startx+vektor*g)){
                                                                     if(g<parameter) {
                                                                      parameter=g;
                                                                      pnormale=normale();
                                                                      schnittpunkt=startx+vektor*parameter;
                                                                      r=true;
                                                                     };
                                                                    };
                                                                   };
                                                                  };
                                                                  startx=start+*it->objekt();
                                                                  it=it->naechstes();
                                                                 };
                                                                 //prüfen, ob eine vertexbewegung des 
                                                                 //statischen poly einen diskreten schnittpunkt ergibt
                                                                 D=V3.determinieren(polygon->pplane[0],polygon->pplane[1],vektor);
                                                                 iterieren(lnvit,
                                                                  vit=lnvit->objekt();
                                                                  g=V3.determinieren(polygon->pplane[0],polygon->pplane[1],vit->ort()-*itstart->objekt())/D;
                                                                  if(g>=0){
                                                                   if(g<=1){
                                                                    h=(vit->ort()-vektor*g)-(*itstart->objekt()-polygon->vertex()->ort());
                                                                    if(polygon->innerhalbpunkt(h)){
                                                                     g=1-g;
                                                                     if(g<parameter){
                                                                      parameter=g;
                                                                      pnormale=normale();
                                                                      schnittpunkt=startx+vektor*parameter;
                                                                      r=true;
                                                                     };
                                                                    };
                                                                   };
                                                                  };
                                                                 );
                                                                 //kanten als ebenen darstellen und den
                                                                 //schnittpunkt prüfen mit den ebenen des
                                                                 //bewegten polygons
                                                                 _vektor3<_tg> kante;
                                                                 _vektor3<_tg> kantethis;
                                                                 startx=start;
                                                                 it=itstart;
                                                                 for(i=0;i<ortanzahl+1;i++){
                                                                  if(i==0){
                                                                   kante=*it->objekt();
                                                                  }else{
                                                                   if(i==ortanzahl){
                                                                    kante=-*it->objekt();
                                                                   }else{
                                                                    kante=(*it->objekt()+start)-startx;
                                                                   };
                                                                  };
                                                                  iterieren(lnvit,
                                                                   vit=lnvit->objekt();
                                                                   vin=lnvit->naechstes()->objekt();
                                                                   kantethis=vin->ort()-vit->ort();
                                                                   D=V3.determinieren(kante,vektor,-kantethis);
                                                                   if(fabs(D)>nahenull){
                                                                    g=V3.determinieren(kante,vektor,vit->ort()-startx)/D;
                                                                    if(g>=0){
                                                                     if(g<=1){
                                                                      _tg a=V3.determinieren(vit->ort()-startx,vektor,-kantethis)/D;
                                                                      if(a>=0){
                                                                       if(a<=1){
                                                                        _tg b=V3.determinieren(kante,vit->ort()-startx,-kantethis)/D;
                                                                        if(b>=0){
                                                                         if(a<=1){
                                                                          if(b<parameter){
                                                                           parameter=b;
                                                                           pnormale=normale();
                                                                           schnittpunkt=startx+vektor*parameter;
                                                                           r=true;
                                                                          };
                                                                         };
                                                                        };
                                                                       };
                                                                      };
                                                                     };
                                                                    };
                                                                   };
                                                                  );
                                                                  startx=start+*it->objekt();
                                                                  it=it->naechstes();
                                                                 };
                                                                };
                                                                return(r);
};
bool _polygon::schnittpunktnetztranslation(_kollidierbarnetztranslation*kollnetz,const _vektor3<_tg>&start,const _vektor3<_tg>&vektor){//
                                                                _netz*netz=kollnetz->netz();
                                                                bool r=false;
                                                                _polygon*pit;
                                                                netz->anfang(pit);
                                                                _vektor3<_tg> ortschieb=start-pit->vertex()->ort();
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _tg D;
                                                                //-------------------------------------- markierung initialisieren ------------------------------
                                                                iterierenliste(netz,pit,
                                                                 iterierenliste(pit,lnvit,
                                                                  vit=lnvit->objekt();
                                                                  vit->markierung(2);
                                                                  vit->markierungverbinder(2);
                                                                 );
                                                                );
                                                                //-------------------------------------- die bewegten vertex des netz auf die this fläche schnittprüfung -------
                                                                schnittpunktnetztranslationrekursiv(kollnetz,netz->erstervertex(),ortschieb,start,vektor,r);
                                                                //-------------------------------------- gegenseitige vertexgeraden prüfungen ----------------------------------
                                                                //-------------------- die statischen this vertex (vit) auf alle polygone von netz schnittprüfung -------------
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 iterierenliste(netz,pit,
                                                                  D=V3.determinieren(pit->pplane[0], pit->pplane[1],vektor);
                                                                  if(fabs(D)>nahenull){
                                                                   _tg g=V3.determinieren(pit->pplane[0],pit->pplane[1],vit->ort()-(pit->pmiddle+ortschieb))/D;
                                                                   if(g>=0){
                                                                    if(g<=1){
                                                                    
                                                                     if(kollnetz->schnittpunktgleich(g)){
                                                                      if(pit->innerhalbpunkt((vit->ort()-vektor*g)-ortschieb)){
                                                                       kollnetz->erzeugenschnittpunkt(this,0,start,vektor,g,vit->ort(),(vit->ort()-vektor*g)-start,-pit->normale());
                                                                       L->schreiben("Verursacher vertex gleich");
                                                                       r=true;
                                                                      };
                                                                     }else if(kollnetz->schnittpunktentfernter(g)){
                                                                      if(pit->innerhalbpunkt((vit->ort()-vektor*g)-ortschieb)){
                                                                       kollnetz->loeschenschnittpunkt();
                                                                       kollnetz->erzeugenschnittpunkt(this,0,start,vektor,g,vit->ort(),(vit->ort()-vektor*g)-start,-pit->normale());
                                                                       L->schreiben("Verursacher vertex neu");
                                                                       r=true;
                                                                      };
                                                                     };
                                                                     
                                                                    };
                                                                   };
                                                                  };
                                                                 );
                                                                );
                                                                //--------------------------------- vertexkanten ebenenprüfung ----------------------------------
                                                                schnittpunktnetztranslationebenerekursiv(kollnetz,netz->erstervertex(),ortschieb,start,vektor,r); 
                                                                return(r);
};
void _polygon::schnittpunktnetztranslationrekursiv(_kollidierbarnetztranslation*kollnetz,_vertex*vertex,const _vektor3<_tg>&ortschieb,const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,bool&r){
                                                                //this ist das statische polygon
                                                                //vertex ist der bewegte vertex
                                                                _tg D;
                                                                //---------------------------
                                                                _netz*netz=kollnetz->netz();
                                                                if(vertex->markierung()==2){
                                                                 vertex->markierung(1);
                                                                 D=V3.determinieren(pplane[0],pplane[1],-vektor);
                                                                 if(fabs(D)>nahenull){
                                                                  _vektor3<_tg> sv=(vertex->ort()+ortschieb);
                                                                  _tg g=V3.determinieren(pplane[0],pplane[1],sv-pmiddle)/D;
                                                                  if(g>=0){
                                                                   if(g<=1){
                                                                    
                                                                    if(kollnetz->schnittpunktgleich(g)){
                                                                     if(innerhalbpunkt(sv+vektor*g)){
                                                                      kollnetz->erzeugenschnittpunkt(this,0,start,vektor,g,sv+vektor*g,(vertex->ort()+ortschieb)-netz->erstervertex()->ort(),normale());
                                                                      L->schreiben("Verursacher poly gleich");
                                                                      r=true;
                                                                     };
                                                                    }else if(kollnetz->schnittpunktentfernter(g)){
                                                                     if(innerhalbpunkt(sv+vektor*g)){
                                                                      kollnetz->loeschenschnittpunkt();
                                                                      kollnetz->erzeugenschnittpunkt(this,0,start,vektor,g,sv+vektor*g,(vertex->ort()+ortschieb)-netz->erstervertex()->ort(),normale());
                                                                      L->schreiben("Verursacher poly neu");

                                                                      r=true;
                                                                     };
                                                                    };

                                                                   };
                                                                  };
                                                                 };
                                                                 _verbindervertexpolygon*cit;
                                                                 _listenknoten<_polygon>*lnpit;
                                                                 iterierenliste(vertex,lnpit,
                                                                  cit=static_cast<_verbindervertexpolygon*>(lnpit);
                                                                  if(cit->markierung()==2){
                                                                   cit->markierung(1);
                                                                   schnittpunktnetztranslationrekursiv(kollnetz,cit->naechstervertex(),ortschieb,start,vektor,r);
                                                                  };
                                                                 );
                                                                };
};
void _polygon::schnittpunktnetztranslationebenerekursiv(_kollidierbarnetztranslation*kollnetz,_vertex*vertex,const _vektor3<_tg>&ortschieb,const _vektor3<_tg>&start,const _vektor3<_tg>&vektor,bool&r){
                                                                //this ist das statische polygon
                                                                //vit ist statishcer vertex von this
                                                                //vertex ist der bewegte vertex

                                                                _verbindervertexpolygon*cit;
                                                                _verbindervertexpolygon*citthis;
                                                                _vektor3<_tg> kante;
                                                                _vektor3<_tg> kantethis;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_polygon>*lnpit;
                                                                _netz*netz=kollnetz->netz();
                                                                //-------------------
                                                                iterierenliste(vertex,lnpit,//if(vertex->anfang(cit))do{
                                                                 cit=static_cast<_verbindervertexpolygon*>(lnpit);
                                                                 if(cit->markierung()==1){
                                                                  cit->markierung(0);
                                                                  cit->gegenkante()->markierung(0);
                                                                  kante=cit->naechstervertex()->ort() - vertex->ort();
                                                                  iterieren(lnvit,
                                                                   vit=lnvit->objekt();
                                                                   citthis=vit->verbinder(this);
                                                                   vin=citthis->naechstervertex();
                                                                   kantethis=vin->ort()-vit->ort();
                                                                   _tg D=V3.determinieren(kante,vektor,-kantethis);
                                                                   if(fabs(D)>nahenull){
                                                                    _vektor3<_tg> h=vit->ort()-(vertex->ort()+ortschieb);
                                                                    _tg g=V3.determinieren(kante,vektor,h)/D;
                                                                    if(g>=0){
                                                                     if(g<=1){
                                                                      _tg a=V3.determinieren(h,vektor,-kantethis)/D;
                                                                      if(a>=0){
                                                                       if(a<=1){
                                                                        _tg b=V3.determinieren(kante,h,-kantethis)/D;
                                                                        if(b>=0){
                                                                         if(b<=1){
                                                                         
                                                                          h=(vertex->ort()+kante*a) - netz->erstervertex()->ort();
                                                                          if(kollnetz->schnittpunktgleich(b)){
                                                                           kollnetz->erzeugenschnittpunkt(this,citthis,start,vektor,b,vit->ort()+kantethis*g,h,normale());
                                                                           kollnetz->erzeugenschnittpunkt(this,citthis->gegenkante(),start,vektor,b,vit->ort()+kantethis*g,h,citthis->gegenkante()->polygon()->normale());
                                                                           cit->kollisionszaehler(cit->kollisionszaehler()+1);
                                                                           cit->gegenkante()->kollisionszaehler(cit->gegenkante()->kollisionszaehler()+1);
                                                                           kollnetz->inkrementierenkollisionszaehlerkante();
                                                                           L->schreiben("Verursacher Kante gleich");
                                                                           r=true;
                                                                          }else if(kollnetz->schnittpunktentfernter(b)){
                                                                           kollnetz->loeschenschnittpunkt();
                                                                           netz->kollisionszaehlerverbinder(0);
                                                                           kollnetz->ruecksetzenkollisionszaehlerkante();
                                                                           kollnetz->erzeugenschnittpunkt(this,citthis,start,vektor,b,vit->ort()+kantethis*g,h,normale());
                                                                           kollnetz->erzeugenschnittpunkt(this,citthis->gegenkante(),start,vektor,b,vit->ort()+kantethis*g,h,citthis->gegenkante()->polygon()->normale());
                                                                           cit->kollisionszaehler(cit->kollisionszaehler()+1);
                                                                           cit->gegenkante()->kollisionszaehler(cit->gegenkante()->kollisionszaehler()+1);
                                                                           kollnetz->inkrementierenkollisionszaehlerkante();
                                                                           L->schreiben("Verursacher Kante neu");
                                                                           r=true;
                                                                          };
                                                                         };
                                                                        };
                                                                       };
                                                                      };
                                                                     };
                                                                    };
                                                                   };
                                                                  );
                                                                  schnittpunktnetztranslationebenerekursiv(kollnetz,cit->naechstervertex(),ortschieb,start,vektor,r);
                                                                 };
                                                                );//}while(vertex->naechstes(cit));
};
bool _polygon::schnittpunktpunktrotation(const _vektor3<_tg>&ort,const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt,_vektor3<_tg>&normale,_vektor3<_tg>&schnittpunkt,_tg&parameter){
                                                                return(false);
};
bool _polygon::schnittpunktkugelrotation(const _vektor3<_tg>&ort,const _vektor3<_tg>&achsenort,const _vektor3<_tg>&achse,const _tg winkelschritt,const _tg radius,_vektor3<_tg>&normale,_vektor3<_tg>&schnittpunkt,_tg&parameter){
                                                                return(false);
};

_tg _polygon::flaeche()const{
                                                                _tg A;
                                                                _vektor3<_tg> k;
                                                                _vektor3<_tg> e;
                                                                _vektor3<_tg> v2;
                                                                _vektor3<_tg> v1;
                                                                _vektor3<_tg> v0;
                                                                //---------------------------
                                                                A=0;
                                                                iterierendreieck(this,v0=vit0->ort(),
                                                                 v1=vit1->ort();
                                                                 v2=vit2->ort();
                                                                 k=v2-v1;
                                                                 V3.lotpunktgerade(v0,v1,k,e);
                                                                 A+=k.laenge()*e.laenge()*0.5f;
                                                                );
                                                                return(A);
};
void _polygon::spiegelmatrix(float*m){ //lädt eine spiegelmatrix
                                                                const _vektor3<_tg>&n=normale();
                                                                float p[3];
                                                                float v[3];
                                                                p[0]=(float)pmiddle[0];
                                                                p[1]=(float)pmiddle[1];
                                                                p[2]=(float)pmiddle[2];
                                                                v[0]=(float)n[0];
                                                                v[1]=(float)n[1];
                                                                v[2]=(float)n[2];
                                                                
                                                                float dot=v[0]*p[0] + v[1]*p[1] + v[2]*p[2];
                                                                
                                                                
                                                                m[0] =1-2*v[0]*v[0];
                                                                m[4] = -2*v[0]*v[1];
                                                                m[8] = -2*v[0]*v[2];
                                                                m[12] = 2*dot*v[0];
                                                                
                                                                m[1] = -2*v[1]*v[0];
                                                                m[1] =1-2*v[1]*v[1];
                                                                m[2] = -2*v[1]*v[2];
                                                                m[3] = 2*dot*v[1];
                                                                
                                                                m[0] = -2*v[2]*v[0];
                                                                m[1] = -2*v[2]*v[1];
                                                                m[2]=1-2*v[2]*v[2];
                                                                m[3]= 2*dot*v[2];
                                                                
                                                                m[0]=0;
                                                                m[1]=0;
                                                                m[2]=0;
                                                                m[3]=1;
                                                                /*
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
                                                                */
};
void _polygon::normalform(_tg*nf){//lädt die normalform der ebene
                                                                const _vektor3<_tg>&n=normale();
                                                                nf[0]=-n[0];
                                                                nf[1]=-n[1];
                                                                nf[2]=-n[2];
                                                                nf[3]=(n*pmiddle);
                                                                
};
bool _polygon::polygondavor(const _polygon*p)const{
                                                                const _vektor3<_tg>&n=normale();
                                                                _vektor3<_tg> h=p->pmiddle;
                                                                h-=pmiddle;
                                                                h.normalisieren();
                                                                if((h*n)>=0) return(true); else return(false);
                                                                return(false);
};
bool _polygon::abgedeckt(_polygon*p){//ist es komplanar und sind alle punkte innerhalb
                                                                _vektoranalysis3<_tg> V3;
                                                                aktualisieren();
                                                                p->aktualisieren();
                                                                if (fabs(p->normale()* normale())<(1-(nahenull/4.0f))) {
                                                                // L->schreiben("Noramle=" , normale());
                                                                // L->schreiben("Aufgrund des parallelen false");
                                                                 return(false);
                                                                };
                                                                _vektor3<_tg> lot;
                                                                _tg para;
                                                                
                                                                V3.lotpunktebene(p->mitte(),mitte(),normale(),lot,para);
                                                                if(lot.laenge()>nahenull) {
                                                               //  L->schreiben("Noramle=" , normale());
                                                               //  L->schreiben("Aufgrund des lotes false");
                                                                 return(false);
                                                                };
                                                                if(p->innerhalbpunkt(mitte())==false){
                                                                 L->schreiben("Noramle=" , normale());
                                                                 L->schreiben("Aufgrund des innerhalbs false");
                                                                 return(false);
                                                                };
                                                                
                                                                
                                                                /*
                                                                
                                                                _vertex*vit;
                                                                vit=pvertex;
                                                                if(vit)do{

                                                                 //bool drin;
                                                                 _vertex*vt;
                                                                 _vertex*vin;
                                                                 _vektor3<_tg> vn;
                                                                 _vektor3<_tg> pn;
                                                                 _vektor3<_tg> en;
                                                                 _vektor3<_tg> h;
                                                                 _tg D,c;
                                                                 //-----------------
                                                                // drin=true;
                                                                 pn=p->normale();
                                                                 vt=p->vertex();
                                                                 if(vt)do{
                                                                  vin=vt->naechstes(p);
                                                                  vn=vin->ort()-vt->ort();
                                                                  h=*vit-(vt->ort()+vn*0.5);
                                                                  vn.normalisieren();
                                                                  en=p->normale(vt->ort(),vin->ort());
                                                                  D=V3.determinieren(vn,pn,en);
                                                                  c=V3.determinieren(vn,pn,h)/D;
                                                               //   if(c<-nahenull) return(false);
                                                                  vt=vin;
                                                                 }while(vt!=p->vertex());
                                                                // if(drin==false) return(false);
                                                                 
                                                                 
                                                                 vit=vit->naechstes(this);
                                                                }while(vit!=pvertex);*/
                                                                return(true);
};
void _polygon::umgrenzungsquader(_tg&x0,_tg&x1,_tg&y0,_tg&y1,_tg&z0,_tg&z1)const{
                                                                bool init=true;
                                                                _vertex*v;
                                                                _listenknoten<_vertex>*lnvit;
                                                                iterieren(lnvit,
                                                                 v=lnvit->objekt();
                                                                 if(init){
                                                                  init=false;
                                                                  x0=x1=(*v)[0];
                                                                  y0=y1=(*v)[1];
                                                                  z0=z1=(*v)[2];
                                                                 }else{
                                                                  if((*v)[0]<x0) x0=(*v)[0];
                                                                  if((*v)[1]<y0) y0=(*v)[1];
                                                                  if((*v)[2]<z0) z0=(*v)[2];
                                                                  if((*v)[0]>x1) x1=(*v)[0];
                                                                  if((*v)[1]>y1) y1=(*v)[1];
                                                                  if((*v)[2]>z1) z1=(*v)[2];
                                                                 };
                                                                );
                                                                //}else L->schreiben("Fehler : _polygonumgrenzungsquader, keine Vertexen vorhanden.");
                                                                
};
bool _polygon::rueckseitig(_kamera<_tg>*kam,unsigned int zyklus){
                                                                if(zweiseitig()) return(false);
                                                                if(markierungzeichnenrueckseitigzyklus==zyklus) return(true);
                                                                if(((pmiddle- *kam)* normale())>0){
                                                                 markierungzeichnenrueckseitigzyklus=zyklus;
                                                                 return(true);
                                                                };
                                                                return(false);
};
bool _polygon::invarianteintegritaet()const{
                                                                //liefert true, wenn die strukturelle interität gegeben ist,
                                                                //d.h. ringsequenz aus vertex
                                                                unsigned long int vc;
                                                                _listenknoten<_vertex>*lnvit;
                                                                unsigned long int max=100000;
                                                                //---------------
                                                                if(anfang(lnvit)==false) return(false);
                                                                vc=0;
                                                                if(anfang(lnvit))do{
                                                                 vc++;
                                                                }while((naechstes(lnvit))&&(vc<max));
                                                                if(vc>=max) return(false);
                                                                return(true);
};

bool _polygon::invarianteanzahl()const{
                                                                unsigned int vc;
                                                                _listenknoten<_vertex>*vit;
                                                                //---------------
                                                                if(anfang(vit)==false) return(false);
                                                                //liefert true, wenn die punktanzahl>2 beträgt
                                                                vc=0;
                                                                iterieren(vit,vc++);
                                                                if(vc>2) return(true); else return(false);
};

bool _polygon::invariantenichtkolinearitaet()const{
                                                                //liefert true, wenn die punkte eine diskrete fläche aufspannen und 
                                                                //keine kante darf mit einer anderen kante des polygons kolinear und diskret schneidend sein
                                                                _vertex*vit;
                                                                _vertex*vii;
                                                                _vertex*vnn;
                                                                _vertex*vin;
                                                                _vertex*pvertex;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _listenknoten<_vertex>*lnvii;
                                                                _vektor3<_tg> e0;
                                                                _vektor3<_tg> e1;
                                                                _vektor3<_tg> o0;
                                                                _vektor3<_tg> o1;
                                                                _vektor3<_tg> h0;
                                                                _vektor3<_tg> h1;
                                                                bool bad;
                                                                //_vektoranalysis3<_tg> V;
                                                                _tg nahenull=0.00001;
                                                                unsigned int c;
                                                                _tg a0,a1,am;
                                                                //----------------------------
                                                                bad=false;
                                                                if(anfang(lnvit)){
                                                                 pvertex=lnvit->objekt();
                                                                 vit=pvertex;
                                                                 do{
                                                                  vin=lnvit->naechstes()->objekt();
                                                                  o0=vit->ort();
                                                                  e0=vin->ort()-vit->ort();
                                                                  if(e0.laenge()>0){
                                                                   if(vin!=pvertex){
                                                                    lnvii=lnvit->naechstes();
                                                                    vii=lnvii->objekt();
                                                                    do{
                                                                     vnn=lnvii->naechstes()->objekt();
                                                                     o1=vii->ort();
                                                                     e1=vnn->ort()-vii->ort();
                                                                     if(e1.laenge()>0){
                                                                      //kreuzprodukt prüfen
                                                                      h0=e0;
                                                                      h0.normalisieren();
                                                                      h1=e1;
                                                                      h1.normalisieren();
                                                                      h0%=h1;
                                                                      if(h0.laenge()<=nahenull){//kolinear->schnittpunkt prüfen
                                                                       c=e0.groessterindex();
                                                                       if(e0[c]!=0){
                                                                        a0=( o1[c]         -o0[c])/e0[c];
                                                                        am=((o1[c]+e1[c]/2)-o0[c])/e0[c];
                                                                        a1=((o1[c]+e1[c])  -o0[c])/e0[c];
                                                                        if((a0>+nahenull)&&(a0<(1-nahenull))) bad=true;
                                                                        if((a1>+nahenull)&&(a1<(1-nahenull))) bad=true;
                                                                        if((a0<-nahenull)&&(a1>(1+nahenull))) bad=true;
                                                                        if((a1<-nahenull)&&(a0>(1+nahenull))) bad=true;
                                                                       }else{
                                                                        L->fehler("bool _polygon::invariantenichtkolinearitaet()const","Der Wert des groessterindex von e0 war null.");
                                                                        bad=true;
                                                                       };
                                                                      };
                                                                     }else{
                                                                      //vnn=pvertex;
                                                                      //vin=pvertex;
                                                                      L->fehler("bool _polygon::invariantenichtkolinearitaet()const","Polygon besitzt zwei kolokale Vertexobjekte in e1.");
                                                                      bad=true;
                                                                     };
                                                                     vii=vnn;
                                                                     lnvii=lnvii->naechstes();
                                                                    }while((vii!=pvertex)&&(bad==false));
                                                                   };
                                                                  }else{
                                                                   //vin=pvertex;
                                                                   L->fehler("bool _polygon::invariantenichtkolinearitaet()const","Polygon besitzt zwei kolokale Vertexobjekte in e0.");
                                                                   bad=true;
                                                                  };
                                                                  vit=vin;
                                                                  lnvit=lnvit->naechstes();
                                                                 }while((vit!=pvertex)&&(bad==false));
                                                                 if(bad) L->fehler("bool _polygon::invariantenichtkolinearitaet()const","Es wurde Kolinearität festgestellt.");
                                                                 if(bad) return(false); else return(true);
                                                                }else{
                                                                 L->fehler("bool _polygon::invariantenichtkolinearitaet()const","Polygon besitzt keinen Vertex.");
                                                                 return(false);
                                                                };
};

bool _polygon::invarianteplanaritaet()const{
                                                                //liefert true, wenn alle punkte sich in einer ebene befinden
                                                                //die ersten drei vertex suchen, die eine ebene E aufspannen 
                                                                //anschiessend prüfen: alle vertex müssen in der ebene liegen
                                                                _listenknoten<_vertex>*lnvit;
                                                                _vektor3<_tg> e0;
                                                                _vektor3<_tg> e1;
                                                                _vektor3<_tg> h0;
                                                                _vektor3<_tg> h1;
                                                                _vektor3<_tg> n;
                                                                bool found;
                                                                bool bad;
                                                                _tg nahenull=0.00001;
                                                                _tg best;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> a;
                                                                _vektor3<_tg> b;
                                                                _vektor3<_tg> e;
                                                                _tg D;
                                                                _tg Dn;
                                                                _vektoranalysis3<_tg> V;
                                                                _vertex*vb;
                                                                //--------------------
                                                                if(anfang(lnvit)){
                                                                 //winkel suchen
                                                                 found=false;
                                                                 best=0;
                                                                 vb=0;
                                                                 iterierendreieck(this,,
                                                                  if(found==false){
                                                                   e0=vit1->ort()-vit0->ort();
                                                                   e1=vit2->ort()-vit1->ort();
                                                                   if((e0.laenge()>0)&&(e1.laenge()>0)){
                                                                    h0=e0;
                                                                    h1=e1;
                                                                    h0.normalisieren();
                                                                    h1.normalisieren();
                                                                    h0%=h1;          
                                                                    if(h0.laenge()>=nahenull){
                                                                     if(h0.laenge()>best){
                                                                      best=h0.laenge();
                                                                      found=true;
                                                                      vb=vit0;
                                                                      n=h0;
                                                                      n.normalisieren();
                                                                      o=vit1->ort();
                                                                      a=vit1->ort()-vit0->ort();
                                                                      b=vit2->ort()-vit1->ort();
                                                                      a.normalisieren();
                                                                      b.normalisieren();
                                                                      D=V.determinieren(a,b,n);
                                                                     };
                                                                    };
                                                                   };
                                                                  };
                                                                 );
                                                                 if(found){
                                                                  bad=false;
                                                                  iterieren(lnvit,
                                                                   e=lnvit->objekt()->ort()-o;
                                                                   Dn=V.determinieren(a,b,e);
                                                                   if(D!=0){
                                                                    if(fabs(Dn/D)>nahenull) bad=true;
                                                                   }else{
                                                                    //kann nicht sein
                                                                    L->fehler("bool _polygon::invarianteplanaritaet()const","kann nicht sein");
                                                                   };
                                                                  );
                                                                  if(bad) L->fehler("bool _polygon::invarianteplanaritaet()const","Polygon- unpanarität wurde festgestellt. ");
                                                                  if(bad) return(false); else return(true);
                                                                 }else{
                                                                  //ebene wurde nicht gefunden
                                                                   L->fehler("bool _polygon::invarianteplanaritaet()const","ebene nicht gefunden");
                                                                  return(false); 
                                                                 };
                                                                }else{
                                                                 //kein vertex
                                                                 L->fehler("bool _polygon::invarianteplanaritaet()const","Kein Vertex vorhanden.");
                                                                 return(false);
                                                                };
};

bool _polygon::invarianteconvexitaet()const{
                                                                //liefert true, wenn alle punkte eine konvexe sequenz ergeben
                                                                //-------------------
                                                                _vektor3<_tg> n;
                                                                bool found;
                                                                _tg nahenull=0.00001;
                                                                _tg best;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> a;
                                                                _vektor3<_tg> b;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _vertex*vb;
                                                                //--------------------
                                                                if(anfang(lnvit)){
                                                                 //winkel suchen
                                                                 found=false;
                                                                 best=0;
                                                                 vb=0;
                                                                 iterierendreieck(this,,
                                                                  a=vit0->ort()-vit1->ort();
                                                                  b=vit2->ort()-vit1->ort();
                                                                  if((a.laenge()>0)&&(b.laenge()>0)){
                                                                   a.normalisieren();
                                                                   b.normalisieren();
                                                                   a%=b;          
                                                                   if(a.laenge()>=nahenull){
                                                                    if(a.laenge()>best){
                                                                     best=a.laenge();
                                                                     found=true;
                                                                     vb=vit0;
                                                                     n=a;
                                                                     n.normalisieren();
                                                                    };
                                                                   };
                                                                  };
                                                                 );
                                                                 if(found){
                                                                 }else{
                                                                  //ebene wurde nicht gefunden
                                                                  return(false); 
                                                                 };
                                                                }else{
                                                                 //kein vertex
                                                                 return(false);
                                                                };
                                                                return(true);
};
bool _polygon::invariantetexturkoordinaten()const{
                                                                //liefert true, wenn texturemaps und texturevectors übereinstimmen
                                                                return(true);
};
bool _polygon::invariant()const {
                                                                //funktion prüft die gesamte gültigkeit eines polygon
                                                                if(invarianteintegritaet()==false) {
                                                                 L->fehler("bool _polygon::invariant()const","Polygon weist fehlerhafte strukturelle Integrität auf.");
                                                                 return(false);
                                                                };
                                                                if(invarianteanzahl()==false) {
                                                                 L->fehler("bool _polygon::invariant()const","Polygon besitzt weniger als drei Vertex-Objekte.");
                                                                 return(false);
                                                                };
                                                                if(invariantenichtkolinearitaet()==false) {
                                                                 L->fehler("bool _polygon::invariant()const","Polygon besitzt kolineare bereiche.");
                                                                 return(false);
                                                                };
                                                                if(invarianteplanaritaet()==false) {
                                                                 L->fehler("bool _polygon::invariant()const","Polygon ist nicht planar.");
                                                                 return(false);
                                                                };
                                                                if(invarianteconvexitaet()==false) {
                                                                 L->fehler("bool _polygon::invariant()const","Polygon ist nicht konvex.");
                                                                 return(false);
                                                                };
                                                                if(invariantetexturkoordinaten()==false) {
                                                                 L->fehler("bool _polygon::invariant()const","Polygon besitzt ungültigt textur-vektor-konfiguration");
                                                                 return(false);
                                                                };
                                                                return(true);
};


bool _polygon::erzwingeninvarianz(){
                                                                //wenn diese funktion false zurückgibt, dann kann die invarianz von hier aus nicht mehr hergestellt werden
                                                                //, ist dies der fall dann sollte das poly von aussen gelöscht werden
                                                                if(invarianteintegritaet()==false){
                                                                 return(false);//nichts zu machen
                                                                }else 
                                                                if(invarianteanzahl()==false){
                                                                 return(false);//nichts zu machen
                                                                }else 
                                                                if(invariantenichtkolinearitaet()==false){
                                                                 return(false);//wohin auch verschieben  
                                                                }else{
                                                                 if(invarianteplanaritaet()==false){
                                                                  //triangulare zerteilung vornehmen
                                                                  erzwingeninvarianzplanaritaet();
                                                                 };
                                                                 if(invarianteconvexitaet()==false){
                                                                  //triangulare zerteilung vornahmen
                                                                  erzwingeninvarianzkonvexitaet();
                                                                 };
                                                                 if(invariantetexturkoordinaten()==false){
                                                                  //texturevectoren auf die textur anpassen
                                                                  erzwingeninvarianztexturkoorindaten();
                                                                 };
                                                                };
                                                                return(true);
};
void _polygon::erzwingeninvarianzplanaritaet(){
                                                                //erzwingt durch polygonale zerteilung 
                                                                //planarität im polygon, d.h polygon kann reduziert werden
                                                                //und es entstehen neue polygone
};
void _polygon::erzwingeninvarianzkonvexitaet(){
                                                                //erzwingt triangulare zerteilung bei auftreten
                                                                //einer konkavität, so dass das polygon zerlegt 
                                                                //wird in mehrere polygone
};
void _polygon::erzwingeninvarianztexturkoorindaten(){
};
void _polygon::markierungrekursiv(int f){
                                                                _polygon*ps;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //-------------------------
                                                                pflag=f;
                                                                iterieren(lnvit,
                                                                 if(nachbar(lnvit->objekt(),lnvit->naechstes()->objekt(),ps)){
                                                                  if(ps->markierung()!=f) ps->markierungrekursiv(f);
                                                                 };
                                                                );
};
void _polygon::markierungkante(int f){
                                                                _listenknoten<_kantepolygon >*eit;
                                                                //----------------------
                                                                if(pedges.anfang(eit))do{
                                                                 eit->objekt()->markierung(f);
                                                                }while(pedges.naechstes(eit));
};
void _polygon::markierungvertex(int f){
                                                                _listenknoten<_vertex>*lnvit;
                                                                iterieren(lnvit,lnvit->objekt()->markierung(f));
};

void _polygon::markierungvertex(int cntpolys,int f){
                                                                //Setzt die Flags aller Vertices in der naechstes-polygonsequenz,
                                                                //die furch f begranzt ist,auf f
                                                                _polygon*pit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                int i;
                                                                //------------
                                                                pit=this;
                                                                for(i=0;i<cntpolys;i++){
                                                                 iterierenliste(pit,lnvit,lnvit->objekt()->markierung(f));
                                                                 pit=pit->naechstes();
                                                                };
};
void _polygon::markierungvertexstatus(int s){
                                                                _listenknoten<_vertex>*v;
                                                                iterieren(v,v->objekt()->status(s));
};
void _polygon::markierungverbinder(int f){
                                                                _listenknoten<_vertex>*vit;
                                                                _verbindervertexpolygon*con;
                                                                //------------------------
                                                                iterieren(vit,
                                                                 con=static_cast<_verbindervertexpolygon*>(vit);
                                                                 con->markierung(f);
																);
};
//-------------------------------------------------------------- ELEMENTSCHNITTSTELLE -------------------------------------------------------------------
void _polygon::loeschentextur(){
                                                                if(ptextur){
                                                                 ptextur->loeschen();
                                                                 deletesecure(ptextur);
                                                                };
                                                                if(ptexturrueck){
                                                                 ptexturrueck->loeschen();
                                                                 deletesecure(ptexturrueck);
                                                                };
};
_zeichenkette<char> _polygon::texturstring() const{
                                                                return(ptexturstring);
};
_zeichenkette<char> _polygon::texturdynamischstring() const{
                                                                return(ptexturdynamischstring);
};
void _polygon::farbe(const _vektor4<_to> f){        //polygonfarbe setzen
                                                                pfarbe=f;
};
void _polygon::farbekante(const _vektor4<_to> f){   //kantenfarbe setzen
                                                                pfarbekante=f;
};
/*
_vektor4<_to>& _polygon::farbekante(){              //kantenfarbe zurückgeben       
                                                                return(pfarbekante);
};*/
void _polygon::farbeverbinder(const _vektor4<_to>&cc){      //verbinderfarbesetzen  
                                                                _listenknoten<_vertex>*vit;
                                                                _verbindervertexpolygon*cit;
                                                                //------------------------
                                                                iterieren(vit,
                                                                 cit=static_cast<_verbindervertexpolygon*>(vit);
                                                                 cit->farbe(cc);
																);
};
void _polygon::glanz(const _vektor4<_to>&f){                //polygonglanz setzen
                                                                pglanz=f;
};
void _polygon::emission(const _vektor4<_to>&f){             //polygonemission setzen
                                                                pemission=f;
};
void _polygon::glanzbreite(const _to f){               //polygonglanzbreite setzen
                                                                pglanzbreite=f;
};
_vektor3<_tg> _polygon::normale(const _vektor3<_tg> v0,const _vektor3<_tg> v1){
                                                                //edgenormale berechnen
                                                                //edgenormalen liegen in der polygonebene 
                                                                //und zeigen immer ins innere
                                                                _vektor3<_tg> n;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> dp;
                                                                _vektor3<_tg> dn;
                                                                //-------------
                                                                n.setzen(0,0,0);
                                                                v=v1-v0;
                                                                h=mitte()-(v0 + v*0.5);
                                                                v.normalisieren();
                                                                h.normalisieren();
                                                                n=v % normale();
                                                                n.normalisieren();
                                                                dp=(n* +1)+h;
                                                                dn=(n* -1)+h;
                                                                if(dn.laenge()>dp.laenge()) n*=-1;
                                                                return(n);
};
//-------------------------------------------------------------- Index Operationen ----------------------------------------------------------------------
void _polygon::erzeugenindex(){
                                                                _listenknoten<_vertex>*vit;
                                                                _verbindervertexpolygon*cit;
                                                                unsigned int c=anzahlvertex();
                                                                unsigned int ci=0;
                                                                loeschenindex();
                                                                pindexanzahl=c;
                                                                pindexbuffer=new unsigned short int[pindexanzahl];
                                                                iterieren(vit,
                                                                 cit=static_cast<_verbindervertexpolygon*>(vit);
                                                                 int vi=pmesh->indexverbinder(cit);
                                                                 if(vi!=-1){
                                                                  pindexbuffer[ci++]=unsigned short int(vi);
                                                                 }else{
                                                                  pindexbuffer[ci++]=0;//fehler
                                                                 };
                                                                );
                                                                
};
void _polygon::loeschenindex(){
                                                                if(pindexbuffer){
                                                                 delete[] pindexbuffer;
                                                                 pindexanzahl=0;
                                                                };
};
unsigned int _polygon::anzahlvertex()const{
                                                                return(_liste<_vertex>::anzahl());
};
//-------------------------------------------------------------- AKTUALISIERUNG ----------------------------------------------------------------------
void _polygon::aktualisieren(){
                                                                //mitte, ebene[2]  und normale initialisieren
                                                                //dreiecke (falls vorhanden) initialisieren
                                                                _dreieck*it;
                                                                _listenknoten<_kantepolygon >*eit;
                                                                //------------------------
                                                                aktualisierenmitte();
                                                                aktualisierenebene();
                                                                if(anfang(it))do{
                                                                 it->aktualisieren();
                                                                }while(naechstes(it));
                                                                if(pedges.anfang(eit))do{
                                                                 eit->objekt()->aktualisieren();
                                                                }while(pedges.naechstes(eit));
                                                                aktualisierendeterminante();
};
void _polygon::aktualisierenmitte(){
                                                                //absolute mittelpunktskoordinate des polygon ermitteln
                                                                _listenknoten<_vertex>*v;
                                                                _tg c=0;
                                                                //--------------
                                                                pmiddle.setzen(0,0,0);
                                                                iterieren(v,
                                                                 pmiddle+=v->objekt()->ort();
                                                                 c+=1;
                                                                );
                                                                if(c>0) pmiddle*=_tg(1.0)/c;
};
void _polygon::aktualisierenebene(){
                                                                _vertex*vit;
                                                                _vertex*vf;
                                                                _listenknoten<_vertex>*v;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> n;
                                                                //-------------
                                                                if(anfang(v)){
                                                                 vf=v->objekt();
                                                                 v=v->naechstes();
                                                                 vit=v->objekt();
                                                                 pplane[0]=pmiddle;
                                                                 pplane[0]-=vit->ort();//sub(vit->ort,ebene[0]->o);
                                                               //  printf("aktualisieren : ebene[0].laenge()=%f\n",pplane[0].laenge());
                                                                 pplane[0].normalisieren();
                                                                 v=v->naechstes();
                                                                 vit=v->objekt();
                                                                 h=vit->ort()-vf->ort();//sub(vit->o,vf->o,h);
                                                                 h.normalisieren();
                                                                 n=pplane[0]%h;//xproduct(pplane[0]->o,h,n);
                                                                 n.normalisieren();
                                                                 kopieren(n);//.setzen(n[0],n[1],n[2]);
                                                                 //mul(pflip);//operator*=pnflip;//normale->mul(-1*nflip);
                                                                 pplane[1]=pplane[0] % normale();//ebene[1].xproduct(ebene[0],normale);
                                                                 pplane[1].normalisieren();
                                                                };
};

void _polygon::aktualisierendeterminante(){
                                                                ph.setzen(
                                                                ( pplane[0][1]*pplane[1][2] - pplane[1][1]*pplane[0][2]),
                                                                (-pplane[0][0]*pplane[1][2] + pplane[1][0]*pplane[0][2]),
                                                                ( pplane[0][0]*pplane[1][1] - pplane[1][0]*pplane[0][1]));
                                                                
                                                                //+a[0]* 
                                                                //+a[1]* (-pplane[0][0]*pplane[1][2] + pplane[1][0]*pplane[0][2])
                                                                //+a[2]* );
                                                                
                                                                pdeterminante=normale() * ph;
                                                                //V3.determinieren(*this,pplane[0],pplane[1]);
};
void _polygon::aktualisierenschatten(){
                                                                _polygonschatten*psit;
                                                                if(anfang(psit))do{
                                                                 psit->aktualisieren();
                                                                }while(naechstes(psit));
};
void _polygon::aktualisierenvertexinterpoliertenormale(){
                                                                _listenknoten<_vertex>*v;
                                                                iterieren(v,v->objekt()->aktualisiereninterpoliertenormale());
};
void _polygon::optimierenstartvertex(){
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _vertex*vs;
                                                                _vektor3<_tg> v,h;
                                                                _tg p,a;
                                                                _vektoranalysis3<_tg> va;
                                                                _listenknoten<_vertex>*lnv;
                                                                //-------------------------------------
                                                                //vit=pvertex;
                                                                if(anfang(lnv)){
                                                                 iterieren(lnv,lnv->objekt()->markierung(0));
                                                                 //-----------------------------------
                                                                 _listenknoten<_vertex>*lnvit;
                                                                 _listenknoten<_vertex>*lnvin;
                                                                 _listenknoten<_vertex>*lnvs;
                                                                 if(anfang(lnvs))do{
                                                                  vs=lnvs->objekt();
                                                                  lnvit=lnvs->naechstes();
                                                                  lnvin=lnvit->naechstes();
                                                                  do{//vs,vit,vin definiert das dreieck
                                                                   vit=lnvit->objekt();
                                                                   vin=lnvin->objekt();
                                                                   v=vin->ort()-vit->ort();
                                                                   va.lotpunktgerade(vs->ort(),vit->ort(),v,h,p);
                                                                   a=(v.laenge()*h.laenge())*0.5;
                                                                   if(a<nahenull*100) vs->markierung(vs->markierung()+1);
                                                                   lnvit=lnvin;
                                                                   lnvin=lnvin->naechstes();
                                                                  }while(lnvin!=lnvs);
                                                                 }while(naechstes(lnvs));
                                                                 //-------------------------------------
                                                                 int min=(int)10e+8;
                                                                 anfang(lnv);
                                                                 lnvs=lnv;
                                                                 do{
                                                                  if(lnv->objekt()->markierung()<min) {
                                                                   lnvs=lnv;
                                                                   min=lnv->objekt()->markierung();
                                                                  };
                                                                 }while(naechstes(lnv));
                                                                 _liste<_vertex>::erstes(lnvs);//pvertex=vs;
                                                                 iterieren(lnv,lnv->objekt()->markierung(0));
                                                                };
};
void _polygon::einhaengen(_netz*m){
                                                                _listenknotenbasis<_polygon >::aushaengen();
                                                                pmesh=m;
                                                                _listenknotenbasis<_polygon >::einhaengen(m);
};
_polygon*_polygon::nachbar(_vertex*v0,_vertex*v1){
                                                                _verbindervertexpolygon*cit0;
                                                                _verbindervertexpolygon*cit1;
                                                                _listenknoten<_polygon>*lnp0;
                                                                _listenknoten<_polygon>*lnp1;
                                                                //---------------
                                                                iterierenliste(v0,lnp0,//if(v0->anfang(vit0))do{
                                                                 cit0=static_cast<_verbindervertexpolygon*>(lnp0);
                                                                 iterierenliste(v1,lnp1,//if(v1->anfang(vit1))do{
                                                                  cit1=static_cast<_verbindervertexpolygon*>(lnp1);
                                                                  if(cit0->polygon()!=this) if(cit0->polygon()==cit1->polygon()) return(cit0->polygon());
                                                                 );
                                                                );
                                                                return(0);
};

bool _polygon::nachbar(_vertex*v0,_vertex*v1,_polygon*&ps){
                                                                ps=nachbar(v0,v1);
                                                                if(ps)return(true); else return(false);
};

_polygon*_polygon::nachbar(_kantepolygon*e){
                                                                _polygon*ps;
                                                                //------------------------
                                                                if(e->polygon(0)==this){
                                                                 ps=e->polygon(1);
                                                                 return(ps);
                                                                }else
                                                                if(e->polygon(1)==this){
                                                                 ps=e->polygon(0);
                                                                 return(ps);
                                                                };
                                                               // L->schreiben("_poly::nachfolger(_pedge*,_poly*&)","kante ist fehlerhaft");
                                                                return(0);
};

bool _polygon::nachbar(_kantepolygon*e,_polygon*&p){
                                                                p=nachbar(e);
                                                                if(p)return(true); else return(false);
};/*
void _polygon::anpassenvertexreihenfolge(bool uhrzeiger){
                                                                //richtet die vertexreihenfolge anhand der normale neu aus
                                                                //normal bleibt konstant
};*/
bool _polygon::optimieren(_polygon*p){
                                                                //funktion untersucht, ob polygon this mit polygon p 
                                                                //vereinigt werden kann. wenn ja, wird die vereinigung durchgeführt
                                                                //und es wird true zurückgegeben
                                                                _vertex*vit;
                                                                _vertex*l0;
                                                                _vertex*l1;
                                                                _vertex*v0;
                                                                _vertex*v1;
                                                                _vertex*ln;
                                                                _vertex*vip;
                                                                _liste<_vertex > lv;
                                                                _listenknoten<_vertex >*lvit;
                                                                _listenknoten<_vertex >*lvii;
                                                                _listenknoten<_vertex >*lnv;
                                                                _liste<_vertex > lvseq;
                                                                bool konvex;
                                                                _verbindervertexpolygon*vcp0t;
                                                                _verbindervertexpolygon*vcp0p;
                                                                _verbindervertexpolygon*vcp1t;
                                                                _verbindervertexpolygon*vcp1p;
                                                                _verbindervertexpolygon*nvcp;
                                                                _verbindervertexpolygon*vcp0;
                                                                _verbindervertexpolygon*vcp1;
                                                                _vektor3<_tg> mid;
                                                                _vektor3<_tg> n;
                                                                _vektor3<_tg> v;
                                                                _vektor3<_tg> h;
                                                                _vektor3<_tg> oldnormal;
                                                                _tg c;
                                                                //----------------------------
                                                                c=normale()*p->normale();
                                                                if(c>(1-nahenull)){
                                                                 //gemeinsame kanten holen
                                                                 iterieren(lnv,
                                                                  iterierenliste(p,lvii,
                                                                   if(lnv->objekt()==lvii->objekt()){
                                                                    lv.einhaengen(lnv->objekt());
                                                                   };
                                                                  );
                                                                 );
                                                                 if(lv.anzahl()>1){
                                                                  //kantenverbund liegt vor, nähere untersuchung 
                                                                  //auf richtung und konvexität vornehm
                                                                  //lvseq initialisieren
                                                                  lv.anfang(lvit);
                                                                  l0=lvit->objekt();
                                                                  lv.vorheriges(lvit);
                                                                  l1=lvit->objekt();
                                                                  lv.anfang(lvit);
                                                                  lv.naechstes(lvit);
                                                                  ln=lvit->objekt();
                                                                
                                                                  //richtung von this testen
                                                                  vit=l1;
                                                                  vip=l0->verbinder(this)->naechstervertex();//l0->naechstes(this);
                                                                  if(vip==ln){
                                                                   do{
                                                                    lvseq.einhaengen(vit);
                                                                    vit=vit->verbinder(this)->naechstervertex();
                                                                   }while(vit!=l0);
                                                                   lvseq.einhaengen(vit);
                                                                  }else{
                                                                   do{
                                                                    lvseq.einhaengen(vit);
                                                                    vit=vit->verbinder(this)->vorherigervertex();
                                                                   }while(vit!=l0);
                                                                   lvseq.einhaengen(vit);
                                                                   //L->schreiben("polygon<>::optimieren(..) : this ist invers");
                                                                  };
                                                                  //L->schreiben("polygon<>::optimieren(..) : anzahl lvseq nach this it",(int)lvseq.anzahl());
                                                                  //richtung von p testen
                                                                  vit=l0; 
                                                                  vip=l0->verbinder(p)->naechstervertex();//l0->naechstes(p);
                                                                  if(vip==ln){
                                                                   //richtung von p ist l0..l1, vorheriges iteration von l0 nach l1 
                                                                   vit=vit->verbinder(p)->vorherigervertex();
                                                                   do{
                                                                    lvseq.einhaengen(vit);
                                                                    vit=vit->verbinder(p)->vorherigervertex();
                                                                   }while(vit!=l1);
                                                                  }else{
                                                                   //richtung von p ist l1..l0, naechstes iteration von l0 nach l1
                                                                   vit=vit->verbinder(p)->naechstervertex();
                                                                   do{
                                                                    lvseq.einhaengen(vit);
                                                                    vit=vit->verbinder(p)->naechstervertex();
                                                                   }while(vit!=l1);
                                                                  };
                                                                  
                                                                  //lvseq (äussere vertexsequenz zweier benachbarter polygone) untersuchen
                                                                  //auf konvexität prüfen
                                                                 // mid=(mitte()+p->mitte())*0.5;
                                                                  konvex=true;
                                                                  if(lvseq.anfang(lvit))do{
                                                                   v0=lvit->objekt();
                                                                   v1=lvit->naechstes()->objekt();
                                                                   vcp0t=v0->verbinder(this);
                                                                   vcp0p=v0->verbinder(p);
                                                                   vcp1t=v1->verbinder(this);
                                                                   vcp1p=v1->verbinder(p);
                                                                   if((vcp0t)&&(vcp1t)) mid=mitte(); else
                                                                   if((vcp0p)&&(vcp1p)) mid=p->mitte();
                                                                   v=v1->ort()-v0->ort();
                                                                   n=normale()%v;
                                                                   n.normalisieren();
                                                                   h=(v0->ort()+(v*0.5))-mid;
                                                                   if((h*n)>0) n*=-1;
                                                                   
                                                                   
                                                                   if(lvseq.anfang(lvii))do{
                                                                    vit=lvii->objekt();
                                                                    if((vit!=v0)&&(vit!=v1)){
                                                                     //halbraum püfen, wenn ausser
                                                                     //halb, dann konvex = false, abbruch
                                                                     h=vit->ort()-v0->ort();
                                                                     h.normalisieren();
                                                                     c=h*n;
                                                                     if(c<-nahenull){
                                                                      konvex=false;
                                                                     };
                                                                    };
                                                                   }while((lvseq.naechstes(lvii))&&(konvex==true));
                                                                   
                                                                   
                                                                  }while((lvseq.naechstes(lvit))&&(konvex==true));
                                                                  //L->schreiben("polygon<>::optimieren(..) : benachbarte Polygone liegen vor.",(int)lvseq.anzahl());
                                                                  if(konvex){
                                                                   //L->schreiben("polygon<>::optimieren(..) : konvex-pruefung bestanden.",(int)lvseq.anzahl());
                                                                   //polygone vereinigen 
                                                                   //zwischen l0 und l1 befindliche vertex löschen
                                                                   //polygon this neu verketten, pvertex von this setzen
                                                                   //polygon p löschen 
                                                                   oldnormal=normale();
                                                                   //pvertex=l1;
                                                                   _liste<_vertex>::erstes(static_cast<_listenknoten<_vertex>*>(l1->verbinder(this)));
                                                                   //verkettung vornehmen
                                                                   //alle vp löschen, die mit p und this verknüpft sind
                                                                   if(lvseq.anfang(lvit))do{
                                                                    vcp0=lvit->objekt()->verbinder(this);
                                                                    vcp1=lvit->objekt()->verbinder(p);
                                                                    nvcp=new _verbindervertexpolygon(lvit->objekt(),this);
                                                                    if(vcp0) nvcp->kopieren(vcp0); else if(vcp1) nvcp->kopieren(vcp1);
                                                                    if(vcp0) delete vcp0;
                                                                    if(vcp1) delete vcp1;
                                                                   }while(lvseq.naechstes(lvit));
                                                                   //vertexsequenz lvseq neu aufrüsten mit vcp
                                                                   //if(lvseq.anfang(lvit))do{
                                                                   //}while(lvseq.naechstes(lvit));
                                                                   //mittlere vertex löschen
                                                                   if(lv.anfang(lvit)){
                                                                    if((lvit->objekt()!=l0)&&(lvit->objekt()!=l1)){
                                                                     lvit->loeschmarkierungobjekt(true);
                                                                    };
                                                                   }while(lv.naechstes(lvit));
                                                                   lv.loeschenmarkiert();
                                                                   //poly p löschen
                                                                   //p->_liste<_vertex>::aushaengen();//p->pvertex=0;
                                                                   delete p;
                                                                   p=0;
                                                                   //normale prüfen
                                                                   aktualisieren();
                                                                   if((normale()*oldnormal)<0) {
                                                                    //pflip*=-1;
                                                                    invertieren();
                                                                   };
                                                                   //exit,true
                                                                   lv.aushaengen();
                                                                   lvseq.aushaengen();
                                                                   return(true);
                                                                  };
                                                                  lv.aushaengen();
                                                                  lvseq.aushaengen();
                                                                  return(false);
                                                                 };//gemeinsame kante
                                                                };//gemeinsame normale
                                                                return(false);
};

void _polygon::anlegentexturkoordinaten(unsigned int li){
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //_verbindervertexpolygon*c[4];
                                                                _texturvektor<_tg>*t[4];
                                                                unsigned int i;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                                                                
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                                                                
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                                                                
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                                                                
//!!!!                 KEINE ALLGEMEINGÜLTIGE FORMULIERUNG                                                  !!!!!!!!!!!!!!!!                                                                
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                                                                
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                                                                
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                                                                
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                                                                
                                                                //----------
                                                                L->schreiben("Es werden Texturkoordinaten angelegt.");
                                                                i=0;
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 t[i++]=static_cast<_texturvektor<_tg>*>(static_cast<_verbindervertexpolygon*>(lnvit));
                                                                );
                                                                _vektor2<_tg> h;
                                                                h.setzen(0,0);
                                                                t[0]->einfuegenvektor(li,h);
                                                                h.setzen(1,0);
                                                                t[1]->einfuegenvektor(li,h);
                                                                h.setzen(1,1);
                                                                t[2]->einfuegenvektor(li,h);
                                                                h.setzen(0,1);
                                                                t[3]->einfuegenvektor(li,h);
                                                                L->schreiben("Es wurden Texturkoordinaten angelegt.");
};
void _polygon::loeschentexturkoordinaten(unsigned int li){
                                                                _texturvektor<_tg>*t;
                                                                _listenknoten<_vertex>*vit;
                                                                //--------------------------
                                                                iterieren(vit,
                                                                 t=static_cast<_texturvektor<_tg>* >(static_cast<_verbindervertexpolygon*>(vit));
                                                                 t->loeschen(li);
                                                                );
                                                                
};
void _polygon::verschiebentexturkoordinaten(const _vektor2<_tg>&v,unsigned int li){
                                                                _texturvektor<_tg>*t;
                                                                _listenknoten<_vertex>*vit;
                                                                //--------------------------
                                                                iterieren(vit,
                                                                 t=static_cast<_texturvektor<_tg>* >(static_cast<_verbindervertexpolygon*>(vit));
                                                                 t->holenvektor(li,0)+=v;
                                                                );
};
void _polygon::skalierentexturkoordinaten(const _vektor2<_tg>&v,unsigned int li){
                                                                _texturvektor<_tg>*t;
                                                                _listenknoten<_vertex>*vit;
                                                                //--------------------------
                                                                iterieren(vit,
                                                                 t=static_cast<_texturvektor<_tg>* >(static_cast<_verbindervertexpolygon*>(vit));
                                                                 t->holenvektor(li,0).setzenkomponente(0,t->holenvektor(li,0)[0]*v[0]);
                                                                 t->holenvektor(li,0).setzenkomponente(1,t->holenvektor(li,0)[1]*v[1]);
                                                                );
};
void _polygon::rotierentexturkoordinaten(const _tg w,unsigned int li){
                                                                _texturvektor<_tg>*t;
                                                                _listenknoten<_vertex>*vit;
                                                                _vektor3<_tg> v;
                                                                //--------------------------
                                                                iterieren(vit,
                                                                 t=static_cast<_texturvektor<_tg>* >(static_cast<_verbindervertexpolygon*>(vit));
                                                                 v.setzen(t->holenvektor(li,0)[0],0,t->holenvektor(li,0)[1]);
                                                                 v.roty(w);
                                                                 t->holenvektor(li,0).setzen(v[0],v[2]);
                                                                );
};
void _polygon::spiegelntexturkoordinatenx(unsigned int li){
                                                                _texturvektor<_tg>*t;
                                                                _listenknoten<_vertex>*vit;
                                                                _vektor2<_tg> m;
                                                                _vektor2<_tg> h;
                                                                _tg c=0;
                                                                //---------------------
                                                                iterieren(vit,
                                                                 t=static_cast<_texturvektor<_tg>* >(static_cast<_verbindervertexpolygon*>(vit));
                                                                 m+=t->holenvektor(li,0);
                                                                 c+=1;
                                                                 //t->holenvektor(li,0).setzenkomponente(0,-t->holenvektor(li,0)[0]);
                                                                );
                                                                if(c>0){
                                                                 m.mul(1.0f/c);
                                                                 iterieren(vit,
                                                                  t=static_cast<_texturvektor<_tg>* >(static_cast<_verbindervertexpolygon*>(vit));
                                                                  h=t->holenvektor(li,0);
                                                                  _tg dx=(m.x()-h.x())*2;
                                                                  h.x(h.x()+dx);
                                                                  t->holenvektor(li,0).setzenkomponente(0,h.x());
                                                                 );
                                                                };
                                                                
};
void _polygon::spiegelntexturkoordinateny(unsigned int li){
                                                                _texturvektor<_tg>*t;
                                                                _listenknoten<_vertex>*vit;
                                                                //---------------------
                                                                iterieren(vit,
                                                                 t=static_cast<_texturvektor<_tg>* >(static_cast<_verbindervertexpolygon*>(vit));
                                                                 t->holenvektor(li,0).setzenkomponente(1,-t->holenvektor(li,0)[1]);
                                                                );
};

void _polygon::neusetzentexturkoordinatennormalisiert(unsigned int li){
                                                                //umgrenzungrechteck ermitteln
                                                                //=> zwei vektoren mit orthonoramlbasis bestimmen;
                                                                _vektor2<_tg> va;
                                                                _vektor2<_tg> vb;
                                                                _vektor2<_tg> vo;
                                                                _vektor2<_tg> h;
                                                                _tg x0,y0,x1,y1,x,y;
                                                                _tg a,b,D;
                                                                _vektoranalysis2<_tg> V2;
                                                                _texturvektor<_tg>*t;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _vertex*vit;
                                                                //---------------------
                                                                berechnengroessterindex();
                                                                if(anfang(lnvit)){
                                                                 vit=lnvit->objekt();
                                                                 x0=x1=(vit->ort())[pcomponent[0]];
                                                                 y0=y1=(vit->ort())[pcomponent[1]];
                                                                };
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 x=(vit->ort())[pcomponent[0]];
                                                                 y=(vit->ort())[pcomponent[1]];
                                                                 if(x<x0) x0=x;
                                                                 if(x>x1) x1=x;
                                                                 if(y<y0) y0=y;
                                                                 if(y>y1) y1=y;
                                                                );
                                                                //parameter a,b für jeden punkt des polys bestimmen
                                                                //parameter liegt in der umgrenzungsfläche
                                                                va.setzen(x1-x0,0);
                                                                vb.setzen(0,y1-y0);
                                                                vo.setzen(x0,y0);
                                                                D=V2.determinieren(va,vb);
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 h.setzen((vit->ort())[pcomponent[0]],(vit->ort())[pcomponent[1]]);
                                                                 if(D){
                                                                  a=V2.determinieren(h-vo,vb)/D;
                                                                  b=V2.determinieren(va,h-vo)/D;
                                                                  t=static_cast<_texturvektor<_tg>*>(static_cast<_verbindervertexpolygon*>(lnvit));
                                                                  t->holenvektor(li,0).setzen(a,b);
                                                                 };
                                                                );
};
void _polygon::neusetzentexturkoordinatenskaliert(unsigned int li){
                                                                //umgrenzungrechteck ermitteln
                                                                //=> zwei vektoren mit orthonoramlbasis bestimmen;
                                                                _vektor2<_tg> va;
                                                                _vektor2<_tg> vb;
                                                                _vektor2<_tg> vo;
                                                                _vektor2<_tg> h;
                                                                _tg x0,y0,x1,y1,x,y;
                                                                _tg a,b,D;
                                                                _vektoranalysis2<_tg> V2;
                                                                _texturvektor<_tg>*t;
                                                                _vertex*vit;
                                                                _listenknoten<_vertex>*lnvit;
                                                                //---------------------
                                                                berechnengroessterindex();
                                                                if(anfang(lnvit)){
                                                                 vit=lnvit->objekt();
                                                                 x0=x1=(vit->ort())[pcomponent[0]];
                                                                 y0=y1=(vit->ort())[pcomponent[1]];
                                                                };
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 x=(vit->ort())[pcomponent[0]];
                                                                 y=(vit->ort())[pcomponent[1]];
                                                                 if(x<x0) x0=x;
                                                                 if(x>x1) x1=x;
                                                                 if(y<y0) y0=y;
                                                                 if(y>y1) y1=y;
                                                                );
                                                                //parameter a,b für jeden punkt des polys bestimmen
                                                                //parameter liegt in der umgrenzungsfläche
                                                                va.setzen(x1-x0,0);
                                                                vb.setzen(0,y1-y0);
                                                                vo.setzen(x0,y0);
                                                                D=V2.determinieren(va,vb);
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 h.setzen((vit->ort())[pcomponent[0]],(vit->ort())[pcomponent[1]]);
                                                                 if(D){
                                                                  a=V2.determinieren(h-vo,vb)/D;
                                                                  b=V2.determinieren(va,h-vo)/D;
                                                                  t=static_cast<_texturvektor<_tg>*>(static_cast<_verbindervertexpolygon*>(lnvit));
                                                                  t->holenvektor(li,0).setzen(a*va.laenge(),b*vb.laenge());
                                                                 };
                                                                );
};

void _polygon::anlegenlightmap(_texturverwaltung<_tb>*tv,_zeichenkette<char> pname,unsigned int wx,unsigned int wy){
                                                                _bild<_tb>*lmap;
                                                                //-------------------
                                                                //diejenige textur, die genauso heißt, aus der verwaltung herauslöschen
                                                                ptexturdynamischstring=pname;
                                                                tv->loeschentexturdynamisch(pname);                                                                
                                                                ptexturdynamisch=new _textur<_tb>(tv,pname);
                                                                lmap=new _bild<_tb>(pname,wx,wy);
                                                                lmap->einhaengen(tv);
                                                                lmap->groesse(wx,wy);
                                                                lmap->tiefereskalieren(1);
                                                                lmap->wiederholung(0,false);
                                                                lmap->wiederholung(1,false);
                                                                lmap->mipmap(false);
                                                                ptexturdynamisch->einfuegenlightmap(lmap);
};

void _polygon::anlegenlightmap(_texturverwaltung<_tb>*tev,_zeichenkette<char> pname,_tg skalierung){
                                                                //gewünschte lightmaptexelgröße wird als argument übergeben
                                                                _bild<_tb>*lmap;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _vektor3<_tg> v;
                                                                _tg maxkante;
                                                                _vertex*maxkantev0;
                                                                _vertex*maxkantev1;
                                                                _vektoranalysis3<_tg> V3;
                                                                _vektor3<_tg> e;
                                                                _tg pa;
                                                                _tg pamin;
                                                                _tg pamax;
                                                                _tg homax;
                                                                _vektor3<_tg> homaxvector;
                                                                _vertex*maxhoehev;
                                                                unsigned int wx,wy;
                                                                _vektor3<_tg> ro;
                                                                _vektor3<_tg> rv0;
                                                                _vektor3<_tg> rv1;
                                                                _texturvektor<_tg>*tv;
                                                                _tg a,b,D;
                                                                _vektor2<_tg> h;
                                                                //-------------------
                                                                aktualisieren();
                                                                aktualisierendeterminante();
                                                                //diejenige textur, die genauso heißt, aus der verwaltung herauslöschen
                                                                ptexturdynamischstring=pname;
                                                                tev->loeschentexturdynamisch(pname);
                                                                ptexturdynamisch=new _textur<_tb>(tev,pname);
                                                                //--------------------- längste kante suchen -------------------------
                                                                maxkante=0;
                                                                maxkantev0=0;
                                                                maxkantev1=0;
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vin=lnvit->naechstes()->objekt();                                                                 
                                                                 /*e=vit->ort()-pmiddle();
                                                                 a=V3.determinieren(*this,e,pplane[1])/pdeterminante;
                                                                 b=V3.determinieren(*this,pplane[0],e)/pdeterminante;*/
                                                                 v=vin->ort()-vit->ort();
                                                                 if(v.laenge()>maxkante){
                                                                  maxkante=v.laenge();
                                                                  maxkantev0=vit;
                                                                  maxkantev1=vin;
                                                                 };
                                                                );
                                                                //-------------------- ausdehnung der längsten kanten holen ------------
                                                                pamin=0;
                                                                pamax=1;
                                                                homax=0;
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 if((vit!=maxkantev0)&&(vit!=maxkantev1)){
                                                                  V3.lotpunktgerade(vit->ort(),maxkantev0->ort(),maxkantev1->ort()- maxkantev0->ort(),e,pa);
                                                                  if(pa>pamax) pamax=pa;
                                                                  if(pa<pamin) pamin=pa;
                                                                  if(e.laenge()>homax) {
                                                                   homax=e.laenge();
                                                                   maxhoehev=vit;
                                                                   homaxvector=e;
                                                                  };
                                                                 };
                                                                );
                                                                //-------------------- umgrenzungrechteck definieren ------------------
                                                                ro=maxkantev0->ort()+ (maxkantev1->ort()- maxkantev0->ort())*pamin;
                                                                rv0=(maxkantev1->ort()- maxkantev0->ort())*(pamax - pamin);
                                                                rv1=-homaxvector;
                                                                //------------------- autolightmapkoordinaten anlegen ----------------
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 D=V3.determinieren(normale(),rv0,rv1);
                                                                 if(D){
                                                                  a=V3.determinieren(normale(),vit->ort()-ro,rv1)/D;
                                                                  b=V3.determinieren(normale(),rv0,vit->ort()-ro)/D;
                                                                  h.setzen(a,b);
                                                                  tv=static_cast<_texturvektor<_tg>*>(static_cast<_verbindervertexpolygon*>(lnvit));//->connector(this);
                                                                  tv->einfuegenlightmapvektor(h);
                                                                 }else{
                                                                  //error : notfallkorrdinaten legen
                                                                 };
                                                                );
                                                                //-------------------- groesse der lightmap ermitteln --------------------
                                                                wx=int(rv0.laenge()/skalierung);
                                                                wy=int(rv1.laenge()/skalierung);
                                                                anpassenlightmapsize(wx);
                                                                anpassenlightmapsize(wy);
                                                                //-------------------- lightmap anlegen -------------------------------
                                                                lmap=new _bild<_tb>(pname,wx,wy);
                                                                lmap->einhaengen(tev);
                                                                lmap->groesse(wx,wy);
                                                                lmap->tiefereskalieren(1);
                                                                lmap->wiederholung(0,false);
                                                                lmap->wiederholung(1,false);
                                                                lmap->mipmap(false);                                                                
                                                                lmap->schreiben(_vektor<_tb>(128,0,0));
                                                                ptexturdynamisch->einfuegenlightmap(lmap);
};
/*
void _polygon::loeschenlightmap(){
                                                                if(ptexturdynamisch) {
                                                                 ptexturdynamisch->loeschen();
                                                                 delete ptexturdynamisch;
                                                                };
                                                                ptexturdynamisch=0;
};
*/
void _polygon::anpassenlightmapsize(unsigned int&w){
                                                                if(w<4) w=4; else{
                                                                 if(w>256) w=256; else{
                                                                  if(w<7) w=4; else{
                                                                   if(w<12) w=8; else{
                                                                    if(w<26) w=16; else{
                                                                     if(w<48) w=32; else{
                                                                      if(w<96) w=64; else{
                                                                       if(w<176) w=128; else{
                                                                        if(w<384) w=256; else w=512;
                                                                       };
                                                                      };
                                                                     };
                                                                    };
                                                                   };
                                                                  };
                                                                 };
                                                                };
};

_liste<_kantepolygon >* _polygon::kanten(){
                                                                return(&pedges);
};
//-------------------------------------------------------------- schattenvolumen ---------------------------------------------------------------------------------
void _polygon::schattenvolumenlaenge(const _tg t){
                                                                pschattenvolumenlaenge=t;
};
_tg _polygon::schattenvolumenlaenge(){
                                                                return(pschattenvolumenlaenge);
};

void _polygon::erzeugenschatten(_licht<_tg,_to>*l,_tg laenge){
                                                                _polygonschatten*it;
                                                                //-----------------
                                                                if(l->schattenvolumen()){
                                                                 if(anfang(it))do{
                                                                  if(it->licht()==l) return;
                                                                 }while(naechstes(it));
                                                                 new _polygonschatten(this,netz()->welt(),l,laenge);
                                                                };
};
void _polygon::loeschenschatten(){
                                                                this->_listebasis<_polygonschatten>::loeschen();
};
void _polygon::anfangschatten(){
                                                                anfang(pschatteniterator);                      
};
void _polygon::naechsterschatten(){
                                                                naechstes(pschatteniterator);
};
_polygonschatten*_polygon::schatteniterator(){
                                                                return(pschatteniterator);
};
void _polygon::zeichnenschatten(_grafik*gra,_licht<_tg,_to>*lit){
                                                                _polygonschatten*it;
                                                                //----------------
                                                                if(anfang(it))do{
                                                                 if(it->licht()==lit) {
                                                                  it->zeichnen(gra);
                                                                  return;
                                                                 };
                                                                }while(naechstes(it));
};  
//-------------------------------------------------------------- kanten ------------------------------------------------------------------------------------------
bool _polygon::hatkante()const{
                                                                //funktion liefert true, wenn alle listnodes<_kantepolygon> vorhanden sind
                                                                _vertex*vit;
                                                                _vertex*vn;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _kantepolygon*es;
                                                                //---------
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vn=lnvit->naechstes()->objekt();
                                                                 if(holenkante(vit,vn,es)==0) return(false);
                                                                );
                                                                return(true);
};

void _polygon::erzeugenkante(){
                                                                //listnode - objekte polyspezifisch anlegen
                                                                //jede kante darf nur einmal existieren
                                                                _vertex*vit;
                                                                _vertex*vn;
                                                                _listenknoten<_vertex>*lnvit;
                                                                _kantepolygon*ne;
                                                                _polygon*ps;
                                                                _kantepolygon*es;
                                                                //-------------------
                                                                berechnengroessterindex();
                                                                iterieren(lnvit,
                                                                 vit=lnvit->objekt();
                                                                 vn=lnvit->naechstes()->objekt();
                                                                 if(holenkante(vit,vn,es)==0){
                                                                  ps=nachbar(vit,vn);
                                                                  if(ps==0) {
                                                                   //L->schreiben("FEHLER : void _polygon::erzeugenkante : NACHFOLGER IST NULL");
                                                                   pedges.einhaengen(new _kantepolygon(this,0,vit,vn));
                                                                  }else{
                                                                   ps->berechnengroessterindex();
                                                                   if(ps->holenkante(vit,vn,es)==0){//dann hat sie der nachfolger auch nicht
                                                                    ne=new _kantepolygon(this,ps,vit,vn);
                                                                    pedges.einhaengen(ne);//new_pce(this,ne);
                                                                   }else{//dann für dieses poly nur pce anlegen
                                                                    pedges.einhaengen(es);//new _pce(this,es);
                                                                   };
                                                                  };
                                                                 };
                                                                );
};
void _polygon::loeschenkante(){
                                                                _listenknoten<_kantepolygon >*it;
                                                                _listenknoten<_kantepolygon >*ites;
                                                                _polygon*ps;
                                                                //------------
                                                                if(pedges.anfang(it))do{//pit=firstpce;if(pit)do{
                                                                 if(nachbar(it->objekt(),ps)){
                                                                  if(ps->kanten()->suchen(it->objekt(),ites)){
                                                                   delete ites;//loeschen(pces);
                                                                   ites=0;
                                                                  };
                                                                 };
                                                                 //delete it->objekt();//loeschen(pit->kante);
                                                                 it->loeschmarkierungobjekt(true);
                                                                 
                                                                 //pit=pit->naechstes;
                                                                }while(pedges.naechstes(it));//while(pit!=firstpce);
                                                                pedges.loeschenmarkiert();
                                                                pedges.aushaengen();//clear_ring(firstpce);
};

char _polygon::holenkante(_vertex*v0,_vertex*v1,_kantepolygon*&pe)const{
                                                                _listenknoten<_kantepolygon >*it;//_pce*pit;
                                                                char r;
                                                                _kantepolygon*e;
                                                                //----------
                                                                r=0;
                                                                pe=0;
                                                                if(pedges.anfang(it))do{
                                                                 e=it->objekt();
                                                                 if(((e->vertex(0)==v0)&&(e->vertex(1)==v1)) || ((e->vertex(1)==v0)&&(e->vertex(0)==v1))){
                                                                  pe=e;
                                                                  r=1;
                                                                 };
                                                                }while((r==0)&&(pedges.naechstes(it)));
                                                                return(r);
};

void _polygon::erzeugendreieck(){
};

void _polygon::loeschendreieck(){
};

bool _polygon::hatdreieck()const{
                                                                return(false);
};

void _polygon::vorbereitenintersektion(){
                                                                aktualisieren();
                                                                berechnengroessterindex();
                                                               // determinedirection();
};

_vektor<unsigned int> _polygon::berechnengroessterindex(){
                                                                //ermittelt die bestmöglichen komponenten der ebenenvektoren im poly p
                                                                /*_tg x;
                                                                _tg y;
                                                                _tg z;
                                                                //_vektor3<_tg> max;
                                                                //_vektor3<_tg> min;
                                                                _vektor3<_tg> xx;
                                                                _tg min[3];
                                                                _tg max[3];*/
                                                                int c0;
                                                                int c1;
                                                                int c2;
                                                                //_vertex*v;
                                                                //_vertex*v0;
                                                                //_vertex*v1;
                                                                int i;
                                                                _tg A[3];
                                                                _vektor3<_tg> a;
                                                                _vektor3<_tg> o;
                                                                _vektor3<_tg> p;
                                                                _vektor3<_tg> h;
                                                                //------------------
                                                                //L->schreiben("L");
                                                                //bewegen(pmiddle->o,max);
                                                                //bewegen(pmiddle->o,min);
                                                                A[0]=0;
                                                                A[1]=0;
                                                                A[2]=0;
                                                                
                                                                iterierendreieck(this,,
                                                                 for(i=0;i<3;i++){
                                                                  p=vit0->ort();
                                                                  a=vit2->ort()-vit1->ort();
                                                                  o=vit1->ort();
                                                                  p.setzenkomponente(i,0);
                                                                  a.setzenkomponente(i,0);
                                                                  o.setzenkomponente(i,0);
                                                                  V3.lotpunktgerade(p,o,a,h);
                                                                  A[i]+=0.5*h.laenge()*a.laenge();
                                                                 };
                                                                );
                                                                if(A[0]>A[1]){
                                                                 if(A[0]>A[2]){//A0
                                                                  c0=1;
                                                                  c1=2;
                                                                  c2=0;
                                                                 }else{//A2
                                                                  c0=0;
                                                                  c1=1;
                                                                  c2=2;
                                                                 };
                                                                }else{
                                                                 if(A[1]>A[2]){//A1
                                                                  c0=0;
                                                                  c1=2;
                                                                  c2=1;
                                                                 }else{//A2
                                                                  c0=0;
                                                                  c1=1;
                                                                  c2=2;
                                                                 };
                                                                };
                                                                pcomponent.setzen(c0,c1,c2);
                                                                return(pcomponent);
};

int _polygon::groessterindex(unsigned int i)const{
                                                                if(i==0) return(pcomponent[0]);
                                                                if(i==1) return(pcomponent[1]);
                                                                if(i==2) return(pcomponent[2]);
                                                                return(-1);
};                                    
_tg _polygon::berechnenalpha(const _vektor3<_tg>&v)const{
                                                                _tg alpha;
                                                                _tg beta;
                                                                _vektor3<_tg> a0;
                                                                _vektor3<_tg> a1;
                                                                //---------------
                                                                 a0=pplane[0];
                                                                 a1=v;
                                                                 a0.normalisieren();
                                                                 a1.normalisieren();
                                                                 alpha=a0.winkel(a1);
                                                                 a0=pplane[1];
                                                                 a0.normalisieren();
                                                                 beta=a0.winkel(a1);
                                                                 if(beta>90) alpha=(180-alpha)+180;
                                                                //berechnet den absoluten degradwinkel (0..360°) mit Hilfe der c0 und c1 - achse
                                                                //im Pseudozweidimensionalen; das argument wird explizit in 2D konvertiert
                                                                //----------
                                                                 return(alpha);
};
void _polygon::status(int s){
                                                                pstatus=s;
};
int _polygon::status() const{
                                                                return(pstatus);
};
void _polygon::erzeugentexturraum(){
                                                                loeschentexturraum();
                                                                ptexturespace=new _polygontexturraum(this);
};
void _polygon::loeschentexturraum(){
                                                                if(ptexturespace) delete ptexturespace;
                                                                ptexturespace=0;
};
void _polygon::verschiebennormal(_tg s){
                                                                //verschiebt vertex entlang der normale 
                                                                //um s, vorsicht, invalidierungsgefahr
                                                                _listenknoten<_vertex>*vit;
                                                                iterieren(vit,vit->objekt()->ort(vit->objekt()->ort() + normale()*s));
                                                                aktualisieren();
};
char _polygon::laden(_dateispeicherbarknoten*fn,_speicherbardynamisch<_polygon>*sd){
																bool b;
                                                                char r=1;
                                                                r^=sd->ladenbeginn(fn);
                                                                r^=sd->ladenverschachtelung(fn);
                                                                r^=sd->ladenwert(*this);
                                                                r^=sd->ladenwert(pfarbe);
                                                                r^=sd->ladenwert(pmiddle);
                                                                r^=sd->ladenwert(pplane[0]);
                                                                r^=sd->ladenwert(pplane[1]);
                                                                r^=sd->ladenwert(pdeterminante);
                                                                r^=sd->ladenwert(pflag);
                                                                r^=sd->ladenwert(ptexturstring);
                                                                r^=sd->ladenwert(b);verwendentextur(b);
                                                                r^=sd->ladenwert(ptexturdynamischstring);
                                                                r^=sd->ladenwert(b);verwendentexturdynamisch(b);
                                                                r^=sd->ladenwert(plightmaptexelgroesse);
                                                                r^=sd->ladenwert(b);verwendenverbinderfarbe(b);
                                                                r^=sd->ladenwert(b);zeichnenflaeche(b);
                                                                r^=sd->ladenwert(b);zeichnenkante(b);
                                                                r^=sd->ladenwert(b);zeichnennormale(b);
                                                                r^=sd->ladenwert(b);normaleinterpoliert(b);
                                                                r^=sd->ladenwert(b);zweiseitig(b);
                                                                r^=sd->ladenwert(b);spiegelnd(b);
                                                                r^=sd->ladenwert(b);dynamischschattierend(b);
                                                                r^=sd->ladenwert(b);dynamischschattiert(b);
                                                                r^=sd->ladenwert(b);maskiert(b);
                                                                r^=sd->ladenwert(b);aufgehellt(b);
                                                                r^=sd->ladenwert(b);kollision(b);
                                                                r^=sd->ladenwert(b);lightmapschattierung(b);
                                                                r^=sd->ladenwert(b);transparenz(b);                             
                                                                r^=sd->ladenwert(b);transparenzadditiv(b);                             
                                                                r^=sd->ladenwert(b);debuggen(b);
                                                                r^=sd->ladenwert(ptransparentfaktor);                       
                                                                r^=sd->ladenwert(pfarbekante);     
                                                                r^=sd->ladenwert(pglanz);                  
                                                                r^=sd->ladenwert(pglanzbreite);                  
                                                                r^=sd->ladenwert(pemission);
                                                                r^=sd->ladenwert(pselection);                       
                                                                r^=sd->ladenwert(b);nurkollisionskopplung(b);
                                                                r^=sd->ladenwert(pschattenvolumenlaenge);
                                                       //  r^=sd->ladenassoziation();
                                                                sd->ladenende();
                                                                return(r);
};

void _polygon::speichern(_speicherbardynamisch<_polygon>*sd){
                                                                sd->speichernbeginnblock();
                                                                sd->speichernverschachtelung();
                                                                sd->speichernwert(*this);
                                                                sd->speichernwert(pfarbe);
                                                                sd->speichernwert(pmiddle);
                                                                sd->speichernwert(pplane[0]);
                                                                sd->speichernwert(pplane[1]);
                                                                sd->speichernwert(pdeterminante);
                                                                sd->speichernwert(pflag);
                                                                if(ptextur==0) ptexturstring="null"; else ptexturstring=ptextur->name(); 
                                                                if(ptexturdynamisch==0) ptexturdynamischstring="null"; else ptexturdynamischstring=ptexturdynamisch->name();
                                                                sd->speichernwert(ptexturstring);
                                                                sd->speichernwert(verwendentextur());
                                                                sd->speichernwert(ptexturdynamischstring);
                                                                sd->speichernwert(verwendentexturdynamisch());
                                                                sd->speichernwert(plightmaptexelgroesse);
                                                                sd->speichernwert(verwendenverbinderfarbe());
                                                                sd->speichernwert(zeichnenflaeche());
                                                                sd->speichernwert(zeichnenkante());
                                                                sd->speichernwert(zeichnennormale());
                                                                sd->speichernwert(normaleinterpoliert());
                                                                sd->speichernwert(zweiseitig());
                                                                sd->speichernwert(spiegelnd());
                                                                sd->speichernwert(dynamischschattierend());
                                                                sd->speichernwert(dynamischschattiert());
                                                                sd->speichernwert(maskiert());
                                                                sd->speichernwert(aufgehellt());
                                                                sd->speichernwert(kollision());
                                                                sd->speichernwert(lightmapschattierung());
                                                                sd->speichernwert(transparenz());                             
                                                                sd->speichernwert(transparenzadditiv());                             
                                                                sd->speichernwert(debuggen());
                                                                sd->speichernwert(ptransparentfaktor);                       
                                                                sd->speichernwert(pfarbekante);    
                                                                sd->speichernwert(pglanz);                  
                                                                sd->speichernwert(pglanzbreite);                  
                                                                sd->speichernwert(pemission);
                                                                sd->speichernwert(pselection);                       
                                                                sd->speichernwert(nurkollisionskopplung());
                                                                sd->speichernwert(pschattenvolumenlaenge);
                                                               // saveassociationargument(sd->datei(),sd,pvertex);
                                                                sd->speichernendeblock();
};
char _polygon::assoziieren(_speicherbardynamisch<_polygon>*sd){
                                                                sd->assoziierenverschachtelung();
                                                         // _vertex*pvertex;
                                                        // associateassociationargument(sd->datei(),sd->assoziation(),pvertex);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!! KONVERSION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                                                return(1);
};
bool _polygon::laden(_dateispeicherbarbinaer*d){
																
                                                                if(ptextur==0) ptexturstring="null"; else ptexturstring=ptextur->name(); 
                                                                if(ptexturdynamisch==0) ptexturdynamischstring="null"; else ptexturdynamischstring=ptexturdynamisch->name();
                                                                einhaengenspeicherung(d);

																ladenbeginn();
																d->laden(speichername());
																_vektor3<_tg> v;
																d->laden(v);
																_vektor3<_tg>::setzen(v);
																d->laden(pstatusbit);
																//ladenzeiger(d);
																ladenzeiger(d);
																ladenzeiger(d);
																ladenzeiger(d);
																//_textur<_tb>*ptextur;
																//_textur<_tb>*ptexturrueck;
																//d->laden(ptexturstring);
																//d->laden(b);verwendentextur(b);
																//_textur<_tb>*ptexturdynamisch;
																//d->laden(ptexturdynamischstring);
																//d->laden(b);verwendentexturdynamisch(b);
																d->laden(plightmaptexelgroesse);
																//d->laden(b);verwendenverbinderfarbe(b);
																//d->laden(b);zeichnenflaeche(b);
																//d->laden(b);zeichnenkante(b);
																//d->laden(b);zeichnennormale(b);
																//d->laden(b);normaleinterpoliert(b);
																//d->laden(b);zweiseitig(b);
																//d->laden(b);spiegelnd(b);
																//d->laden(b);dynamischschattierend(b);
																//d->laden(b);dynamischschattiert(b);
																//d->laden(b);maskiert(b);
																//d->laden(b);aufgehellt(b);
																//d->laden(b);kollision(b);
																//d->laden(b);lightmapschattierung(b);
																//d->laden(b);transparenz(b);
																//d->laden(b);transparenzadditiv(b);
																//d->laden(b);debuggen(b);    
																//d->laden(b);nurkollisionskopplung(b);
																d->laden(ptransparentfaktor);
																d->laden(pfarbe);
																d->laden(pglanz);
																d->laden(pemission);
																d->laden(pglanzbreite);
																d->laden(pfarbekante);
																//d->laden(pmiddle);
																//d->laden(pplane[0]);
																//d->laden(pplane[1]);
																d->laden(pdeterminante);
																d->laden(pflag);
																d->laden(pselection);
																//d->laden(phc);
																d->laden(pschattenvolumenlaenge);
																d->laden(pcomponent);
																d->laden(pstatus);
																//d->laden(ph);
																//d->laden(pmiddleparallel);
																//d->laden(pmiddleperspective);
																//d->laden(pmiddlenormalparallel);
																//d->laden(pmiddlenormalperspective);
																ladenoberflaeche(d);
																unsigned int i,a;

																_liste<_vertex>::aushaengen();
																_verbindervertexpolygon*cit;
																d->laden(a);
																//L->l("  Es sollen Verbinder geladen werden : anzahl=",(int)a);
																for(i=0;i<a;i++){
																 cit=new _verbindervertexpolygon(0,this);
																 cit->laden(d);
																};
																
																
																
																_liste<_partition::_sektor>::aushaengen();
																a=ladenanzahl(d);
																for(i=0;i<a;i++) ladenzeiger(d);
																return(true);
};
void _polygon::speichern(_dateispeicherbarbinaer*d){
																d->speichern(speichername());
																_vektor3<_tg> v=normale();
																d->speichern(v);
																d->speichern(pstatusbit);
																//speichernzeiger(d,pvertex);
																speichernzeiger(d,ptextur);
																speichernzeiger(d,ptexturrueck);
																speichernzeiger(d,ptexturdynamisch);
																//_textur<_tb>*ptextur;
																//_textur<_tb>*ptexturrueck;
															//d->speichern((int)1);//d->speichern(ptexturstring);
																//d->speichern(verwendentextur());
																//_textur<_tb>*ptexturdynamisch;
															//d->speichern((int)1);//d->speichern(ptexturdynamischstring);
																//d->speichern(verwendentexturdynamisch());
																d->speichern(plightmaptexelgroesse);
																//d->speichern(verwendenverbinderfarbe());
																//d->speichern(zeichnenflaeche());
																//d->speichern(zeichnenkante());
																//d->speichern(zeichnennormale());
																//d->speichern(normaleinterpoliert());
																//d->speichern(zweiseitig());
																//d->speichern(spiegelnd());
																//d->speichern(dynamischschattierend());
																//d->speichern(dynamischschattiert());
																//d->speichern(maskiert());
																//d->speichern(aufgehellt());
																//d->speichern(kollision());
																//d->speichern(lightmapschattierung());
																//d->speichern(transparenz());
																//d->speichern(transparenzadditiv());
																//d->speichern(debuggen());         
																//d->speichern(nurkollisionskopplung());
																d->speichern(ptransparentfaktor);
																d->speichern(pfarbe);
																d->speichern(pglanz);
																d->speichern(pemission);
																d->speichern(pglanzbreite);
																d->speichern(pfarbekante);
																//d->speichern(pmiddle);
																//d->speichern(pplane[0]);
																//d->speichern(pplane[1]);
																d->speichern(pdeterminante);
																d->speichern(pflag);
																d->speichern(pselection);
																//d->speichern(phc);
																d->speichern(pschattenvolumenlaenge);
																d->speichern(pcomponent);
																d->speichern(pstatus);
																//d->speichern(ph);
																//d->speichern(pmiddleparallel);
																//d->speichern(pmiddleperspective);
																//d->speichern(pmiddlenormalparallel);
																//d->speichern(pmiddlenormalperspective);
																speichernoberflaeche(d);
																//verbinderspeicherung erhält an dieser stelle die  vertex reihenfolge
																_verbindervertexpolygon*cit;
																_listenknoten<_vertex>*vit;
																d->speichern(_liste<_vertex>::anzahl());
																iterieren(vit,
																 cit=static_cast<_verbindervertexpolygon*>(vit);
																 cit->speichern(d);
																);

																_listenknoten<_partition::_sektor>*lnsit;
																d->speichern(_liste<_partition::_sektor>::anzahl());
																iterieren(lnsit,speichernzeiger(d,lnsit->objekt()));
};
bool _polygon::assoziieren(){	
																//L->l("Polygon wird assoziiert:");
																if(zeigergeladen()){
																 //_vertex*pvertex;
																 //assoziierenzeiger(pvertex);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! KONVERSION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
																 //if(pvertex==0) L->l("  Fehler beim assoziieren von vertex"); //else L->l("  Erster Vertex wurde assoziiert.");
																 assoziierenzeiger(ptextur);
																 //if(ptextur) L->l("  Textur wurde assoziiert.");
																 assoziierenzeiger(ptexturrueck);
																 //if(ptexturrueck) L->l("  Texturrueck wurde assoziiert.");
																 assoziierenzeiger(ptexturdynamisch);
																 //if(ptexturdynamisch) L->l("  Texturdynamisch wurde assoziiert.");
																 unsigned int a=ladenanzahl();
																 unsigned int i;
																 for(i=0;i<a;i++) {
															      _partition::_sektor*sit;
																  assoziierenzeiger(sit);
                                                                  if(netz()->dynamisch()) 
                                                                   new _verbinder<_polygon,_partition::_sektor>(sit->internepolygonedynamisch(),this,this,sit); 
                                                                  else 
                                                                   new _verbinder<_polygon,_partition::_sektor>(sit->internepolygonestatisch(),this,this,sit);
																 };
																 loeschenzeiger();loeschenanzahl();
																};
																return(true);
};
void _polygon::einhaengendialog(_dynamischerdialog*d){
                                                                d->editierbar(this);
                                                                d->loeschensektion();
                                                                _oberflaeche<_tg>::einhaengendialog(d);
                                                                d->addierensektion(L"Polygon");
                                                                d->sektion(L"Polygon")->offen(true);
                                                                d->einhaengen(L"Polygon",L"Statische Textur",ptexturstring);
                                                                d->einhaengen(L"Polygon",L"Dynamische Textur",ptexturdynamischstring);
                                                                d->einhaengen(L"Polygon",L"Dynamische Textur verwenden",verwendentexturdynamisch());
                                                                d->einhaengen(L"Polygon",L"Größe der Lightmaptexel",plightmaptexelgroesse);
                                                                d->einhaengen(L"Polygon",L"Länge des Schattenvolumens",pschattenvolumenlaenge);
                                                                d->einhaengen(L"Polygon",L"Verbinderfarbe verwenden",verwendenverbinderfarbe());
                                                                d->einhaengen(L"Polygon",L"Fläche zeichnen",zeichnenflaeche());
                                                                d->einhaengen(L"Polygon",L"Kanten zeichnen",zeichnenkante());
                                                                d->einhaengen(L"Polygon",L"Normale zeichnen",zeichnennormale());
                                                                d->einhaengen(L"Polygon",L"Normale interpolieren",normaleinterpoliert());
                                                                d->einhaengen(L"Polygon",L"Zweiseitig",zweiseitig());
                                                                d->einhaengen(L"Polygon",L"Spiegelnd",spiegelnd());
                                                                d->einhaengen(L"Polygon",L"Dynamisch schattierend",dynamischschattierend());
                                                                d->einhaengen(L"Polygon",L"Dynamisch schattiert",dynamischschattiert());
                                                                d->einhaengen(L"Polygon",L"Maskiert",maskiert());
                                                                d->einhaengen(L"Polygon",L"Aufgehellt",aufgehellt());
                                                                d->einhaengen(L"Polygon",L"Kollisionsteilnahme",kollision());
                                                                d->einhaengen(L"Polygon",L"Schattierung von Lightmaps",lightmapschattierung());
                                                                d->einhaengen(L"Polygon",L"Transparenz",transparenz());                              
                                                                d->einhaengen(L"Polygon",L"Additive Transparenz [falsch=multiplikativ]",transparenzadditiv());                              
                                                                d->einhaengen(L"Polygon",L"Debugschalter",debuggen());
                                                                d->einhaengen(L"Polygon",L"Nur Kollisionskopplung aufrufen",nurkollisionskopplung());
                                                                d->einhaengen(L"Polygon",L"Transparentfaktor",ptransparentfaktor);                        //transparenzfaktor 0..1
                                                                d->einhaengen(L"Polygon",L"Farbe",pfarbe);                            //zeichenfarbe der fläche
                                                                d->einhaengen(L"Polygon",L"Kantenfarbe",pfarbekante);                       //zeichenfarbe der kante
                                                                d->einhaengen(L"Polygon",L"Glanz",pglanz);                     
                                                                d->einhaengen(L"Polygon",L"Glanzbreite",pglanzbreite);                     
                                                                d->einhaengen(L"Polygon",L"Emission",pemission);                     
                                                                d->einhaengen(L"Polygon",L"Markierung",pflag);                                      //markierung
                                                                d->einhaengen(L"Polygon",L"Anwahl",pselection);   //selektion        
};
void _polygon::auslesendialog(_dynamischerdialog*d){
                                                                _oberflaeche<_tg>::auslesendialog(d);
																bool b;
                                                                d->auslesen(L"Polygon",L"Statische Textur",ptexturstring);
                                                                d->auslesen(L"Polygon",L"Dynamische Textur",ptexturdynamischstring);
                                                                d->auslesen(L"Polygon",L"Dynamische Textur verwenden",b);verwendentexturdynamisch(b);
                                                                d->auslesen(L"Polygon",L"Größe der Lightmaptexel",plightmaptexelgroesse);
                                                                d->auslesen(L"Polygon",L"Länge des Schattenvolumens",pschattenvolumenlaenge);
                                                                d->auslesen(L"Polygon",L"Verbinderfarbe verwenden",b);verwendenverbinderfarbe(b);
                                                                d->auslesen(L"Polygon",L"Fläche zeichnen",b);zeichnenflaeche(b);
                                                                d->auslesen(L"Polygon",L"Kanten zeichnen",b);zeichnenkante(b);
                                                                d->auslesen(L"Polygon",L"Normale zeichnen",b);zeichnennormale(b);
                                                                d->auslesen(L"Polygon",L"Normale interpolieren",b);normaleinterpoliert(b);
                                                                d->auslesen(L"Polygon",L"Zweiseitig",b);zweiseitig(b);
                                                                d->auslesen(L"Polygon",L"Spiegelnd",b);spiegelnd(b);
                                                                d->auslesen(L"Polygon",L"Dynamisch schattierend",b);dynamischschattierend(b);
                                                                d->auslesen(L"Polygon",L"Dynamisch schattiert",b);dynamischschattiert(b);
                                                                d->auslesen(L"Polygon",L"Maskiert",b);maskiert(b);
                                                                d->auslesen(L"Polygon",L"Aufgehellt",b);aufgehellt(b);
                                                                d->auslesen(L"Polygon",L"Kollisionsteilnahme",b);kollision(b);
                                                                d->auslesen(L"Polygon",L"Schattierung von Lightmaps",b);lightmapschattierung(b);
                                                                d->auslesen(L"Polygon",L"Transparenz",b);transparenz(b);                              
                                                                d->auslesen(L"Polygon",L"Additive Transparenz [falsch=multiplikativ]",b);transparenzadditiv(b);  
                                                                d->auslesen(L"Polygon",L"Debugschalter",b);debuggen(b);
                                                                d->auslesen(L"Polygon",L"Nur Kollisionskopplung aufrufen",b);nurkollisionskopplung(b);
                                                                d->auslesen(L"Polygon",L"Transparentfaktor",ptransparentfaktor);                        //transparenzfaktor 0..1
                                                                d->auslesen(L"Polygon",L"Farbe",pfarbe);                            //zeichenfarbe der fläche
                                                                d->auslesen(L"Polygon",L"Kantenfarbe",pfarbekante);                       //zeichenfarbe der kante
                                                                d->auslesen(L"Polygon",L"Glanz",pglanz);                     
                                                                d->auslesen(L"Polygon",L"Glanzbreite",pglanzbreite);                     
                                                                d->auslesen(L"Polygon",L"Emission",pemission);                     
                                                                d->auslesen(L"Polygon",L"Markierung",pflag);                                      //markierung
                                                                d->auslesen(L"Polygon",L"Anwahl",pselection);                                 //selektion        
};
void _polygon::visualisieren(){
                                                                _vektor4<_to> col;
                                                                //---------------
                                                                col.setzen(0,0.3f,1,0);
                                                                visualisieren(col);
                                                                
};
void _polygon::visualisieren(_vektor4<_to> col){
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*v;
                                                                _vektor4<_to> pcol;
                                                                _vektor3<_tg> vt;
                                                                _vektor3<_tg> vn;
                                                                //-------------
                                                                unvisualisieren();
                                                                iterieren(v,
                                                                 vit=v->objekt();
                                                                 vin=v->naechstes()->objekt();
                                                                 //naechstes(vin);
                                                                 vt=mitte()-vit->ort();
                                                                 vt.normalisieren();
                                                                 vt*=0.05;
                                                                 vn=mitte()-vin->ort();
                                                                 vn.normalisieren();
                                                                 vn*=0.05;
                                                                 pdbarrows.einhaengen(new _weltdebugpfeil(pmesh->welt(),vit->ort()+vt,vin->ort()+vn,0.03,0.01,col));
                                                                 //pdbcrosses.einhaengen(new _weltdebugkreuz(W,*vit,0.1,pcol));
                                                                );
                                                                if(markierung()<0) pcol.setzen(0,0,1,0);
                                                                if(markierung()==0) pcol.setzen(0.5,0.5,0.5,0);
                                                                if(markierung()>0) pcol.setzen(1,0,0,0);
                                                                pdbcrosses.einhaengen(new _weltdebugkreuz(pmesh->welt(),mitte(),0.1,pcol));
};
void _polygon::unvisualisieren(){
                                                                pdbarrows.loeschen();
                                                                pdbcrosses.loeschen();
};
void _polygon::speicherkonversion(){
																//knoten sortieren
																_liste<_verbindervertexpolygon> lc;
																_verbindervertexpolygon*c;
																_vertex*v;
																_vertex*vs;
																_listenknoten<_vertex>*lnvit;
																iterieren(lnvit,lc.einhaengen(static_cast<_verbindervertexpolygon*>(lnvit)));
																
																_listenknoten<_verbindervertexpolygon>*lncit;
																iterierenliste(&lc,lncit,
																 c=lncit->objekt();
																 if(c->pnextvertex==0) {
																  L->l("EEEEEEEEEEEERRRRRRRRRRRRRRRRRRR");
																  return;
																 };
																);
																iterierenliste(&lc,lncit,
																 c=lncit->objekt();
																 c->_listenknoten<_vertex>::aushaengen();
																);
																L->schreiben("lc ANZAHL =",(int)lc.anzahl());
																if(lc.anfang(lncit)){
																 c=lncit->objekt();
																 vs=c->vertex();
																 v=vs;
																 
																 do{
																  c->_listenknoten<_vertex>::einhaengen(this);
																  L->l("neuer vertex v=",(int)c->pnextvertex);
																  v=c->pnextvertex;
																 
																  c=v->verbinder(this);
																  L->schreiben("Neu iterierter verbinder c=",(int)c);
																 
																 }while(v!=vs);
																 aktualisieren();
																};
};
//******************************************************************************************************************************************************************************************************
//                                                              P O L Y G O N T E X T U R E S P A C E 
//******************************************************************************************************************************************************************************************************
_polygontexturraum::_polygontexturraum(_polygon*p){
                                                                int c0,c1;
                                                                _vertex*v;
                                                                _listenknoten<_vertex>*lnv;
                                                                _verbindervertexpolygon*vcp;
                                                                _tg c;
                                                                //-----------
                                                                poly=p;
                                                                poly->berechnengroessterindex();
                                                                c0=poly->groessterindex(0);
                                                                c1=poly->groessterindex(1);
                                                                //va,vb,mitte bestimmen weltkoordinatensystem des poly p
                                                                mitte.setzen(poly->mitte()[c0],poly->mitte()[c1]);
                                                                v=poly->vertex();
                                                                va.setzen(v->ort()[c0],v->ort()[c1]);
                                                                va-=mitte;
                                                                v=v->naechstes(poly);
                                                                vb.setzen(v->ort()[c0],v->ort()[c1]);
                                                                vb-=mitte;
                                                               // vpa.setzen(poly->ebene(0)[c0],poly->ebene(0)[c1]);
                                                              //  vpb.setzen(poly->ebene(1)[c0],poly->ebene(1)[c1]);
                                                                Dv=V2.determinieren(va,vb);
                                                                //texturegeometrischen mittelpunkt tvm ermitteln
                                                                c=0;
                                                                if(poly->anfang(lnv)){
                                                                 //v=lnv->objekt();
                                                                 tvm.kopieren(static_cast<_texturvektor<_tg>*>(static_cast<_verbindervertexpolygon*>(lnv)));
                                                                 lnv=lnv->naechstes();
                                                                 c+=1;
                                                                 do{
                                                                  vcp=static_cast<_verbindervertexpolygon*>(lnv);
                                                                  tvm.add(vcp);
                                                                  c+=1;
                                                                 }while(poly->naechstes(lnv));
                                                                };
                                                                if(c==0){
                                                                // fehler("_polygontexturraum::_polygontexturraum(_polygon*p)","Poly->vertex()==0");
                                                                }else{
                                                                 tvm.mul(1/c);
                                                                };
                                                                //texturgeometrische vectoren a und b ermitteln
                                                                v=poly->vertex();
                                                                vcp=v->verbinder(poly);
                                                                tva.kopieren(vcp);
                                                                tva.sub(&tvm);
                                                                v=v->naechstes(p);
                                                                vcp=v->verbinder(poly);
                                                                tvb.kopieren(vcp);
                                                                tvb.sub(&tvm);
                                                                 
                                                                //ebenenparameter im ts::weltkoordinaten errechnen
                                                                _vektor3<_tg> xx;
                                                                _vektor2<_tg> e;
                                                                _texturvektor<_tg> ptva;
                                                                _texturvektor<_tg> ptvb;
                                                                _tg a,b;
                                                                unsigned int i;
                                                                for(i=0;i<2;i++){
                                                                 xx=poly->mitte()+poly->ebene(i);
                                                                 e.setzen(xx[c0],xx[c1]);
                                                                 e-=mitte;
                                                                 a=V2.determinieren(e,vb)/Dv;
                                                                 b=V2.determinieren(va,e)/Dv;
                                                                 ptva.kopieren(&tva);
                                                                 ptvb.kopieren(&tvb);
                                                                 ptva.mul(a);
                                                                 ptvb.mul(b);
                                                                 ptva.add(&ptvb);
                                                                 ptva.add(&tvm);
                                                                 tvplane[i].kopieren(&ptva);
                                                                 tvplane[i].sub(&tvm);
                                                                };
                                                                vbvi=0;
                                                                vbli=0;
};

_polygontexturraum::~_polygontexturraum(){
                                                                ox.loeschen();
                                                                oy.loeschen();
                                                                nx.loeschen();
                                                                ny.loeschen();
                                                                
};

void _polygontexturraum::interpolieren(unsigned int li,unsigned int vi,_tg a,_tg b,_vektor2<_tg>&ve){
                                                                //wandelt die geometrischen ebenenparameter a,b in texturkoordinaten um
                                                                //------------------
                                                                _vektor2<_tg>&vm=tvm.holenvektor(li,vi);
                                                                _vektor2<_tg>&vp0=tvplane[0].holenvektor(li,vi);
                                                                _vektor2<_tg>&vp1=tvplane[1].holenvektor(li,vi);
                                                                ve=vm+vp0*a+vp1*b;
};

void _polygontexturraum::konvertierentexturwelt(unsigned int li,unsigned int vi,_tg tx,_tg ty,_vektor3<_tg>&ve){
                                                                //wandelt die texturkoordinaten tx,ty in einen geometrischen raumpunkt um
                                                                _vektoranalysis2<_tg> V2;
                                                                _tg D;
                                                                _tg a,b;
                                                                _vektor2<_tg> e;
                                                                _vektor3<_tg> va;
                                                                _vektor3<_tg> vb;
                                                                _vertex*vit;
                                                                //------------------
                                                                _vektor2<_tg>&vm=tvm.holenvektor(li,vi);
                                                                _vektor2<_tg>&vp0=tva.holenvektor(li,vi);
                                                                _vektor2<_tg>&vp1=tvb.holenvektor(li,vi);
                                                                //a,b ermitteln mit hilfe von ve=(tx,ty)
                                                                D=V2.determinieren(vp0,vp1);
                                                                e.setzen(tx,ty);
                                                                e=e-vm;
                                                                a=V2.determinieren(e,vp1)/D;
                                                                b=V2.determinieren(vp0,e)/D;
                                                                //ebenevektoren va,vb ermitteln
                                                                va=poly->vertex()->ort()-poly->mitte();
                                                                vit=poly->vertex();
                                                                vit=vit->verbinder(poly)->naechstervertex();
                                                                vb=vit->ort()-poly->mitte();
                                                                ve=poly->mitte()+va*a+vb*b;
};
bool _polygontexturraum::innerhalb(unsigned int li,unsigned int vi,_tg x,_tg y){
                                                                //liefert true zurück, wenn der angegeben punkt x,y
                                                                //im texturraum innerhalb des vom polygon bereitgestellten
                                                                //texturpolygons sich befindet
                                                                bool innen=true;
                                                                
                                                                _tg hx,hy;
                                                                //--------------
                                                               // vorberechnenpolygon(li,vi);
                                                                if(ox.anfang(iox)==false) vorberechnenpolygon(li,vi); else{
                                                                 //untersuchen ob die existierende vorberechnung 
                                                                 //mit den indizes li,vi übereinstimmt, ggf. löschen neuerzeugen
                                                                 if((vbli!=li)||(vbvi!=vi)) vorberechnenpolygon(li,vi);
                                                                };
                                                                ny.anfang(iny);
                                                                oy.anfang(ioy);
                                                                nx.anfang(inx);
                                                                if(ox.anfang(iox))do{
                                                                 hx=x-*iox->objekt();
                                                                 hy=y-*ioy->objekt();
                                                              //   _tg l=sqrt(hx*hx+hy*hy);
                                                              //   hx/=l;
                                                              //   hy/=l;
                                                                 
                                                                 //::bewegen(hx,hy,x,y);
                                                                 //::sub(hx,hy,,*ioy->objekt());
                                                                 if(::multiplizieren(hx,hy,*inx->objekt(),*iny->objekt())<=0) innen=false; 
                                                                 oy.naechstes(ioy);
                                                                 nx.naechstes(inx);
                                                                 ny.naechstes(iny); 
                                                                }while((ox.naechstes(iox))&&(innen));
                                                                return(innen);
};                                                               

void _polygontexturraum::vorberechnenpolygon(unsigned int li,unsigned int vi){
                                                                _tg*oox;
                                                                _tg*ooy;
                                                                _tg*nnx;
                                                                _tg*nny;
                                                                _vertex*vit;
                                                                _vertex*vin;
                                                                _listenknoten<_vertex>*lnv;
                                                                _verbindervertexpolygon*c;
                                                                _vektor2<_tg> v;
                                                                _vektor2<_tg> n;
                                                                _vektor2<_tg> o;
                                                                //------------------------
                                                                v.setzen(0,0);
                                                                o.setzen(0,0);
                                                                n.setzen(0,0);
                                                                ox.loeschen();
                                                                oy.loeschen();
                                                                nx.loeschen();
                                                                ny.loeschen();
                                                                vbli=li;
                                                                vbvi=vi;
                                                                _vektor2<_tg>&vm=tvm.holenvektor(li,vi);
                                                                iterierenliste(poly,lnv,
                                                                 vit=lnv->objekt();
                                                                 vin=lnv->naechstes()->objekt();
                                                                 c=static_cast<_verbindervertexpolygon*>(lnv);
                                                                 _vektor2<_tg>&o0=c->holenvektor(li,vi);
                                                                 c=static_cast<_verbindervertexpolygon*>(lnv->naechstes());
                                                                 _vektor2<_tg>&o1=c->holenvektor(li,vi);
                                                                 o=(o0+o1)*0.5;
                                                                 oox=new _tg;
                                                                 *oox=o[0];
                                                                 ox.einhaengen(oox);
                                                                 ooy=new _tg;
                                                                 *ooy=o[1];
                                                                 oy.einhaengen(ooy);
                                                                 n=o1-o0;
                                                                 //V2.berechnenorthogonalenvektor(v,n);
                                                                 n.normalisieren();
                                                                 n.rot(90);
                                                                 if( (n*(vm-o))<=0) n*=-1;
                                                                 nnx=new _tg;
                                                                 *nnx=n[0];
                                                                 nx.einhaengen(nnx);
                                                                 nny=new _tg;
                                                                 *nny=n[1];
                                                                 ny.einhaengen(nny);
                                                                );
};
//******************************************************************************************************************************************************************************************************
//                                                              P O L Y G O N S C H A T T E N 
//******************************************************************************************************************************************************************************************************
_polygonschatten::_polygonschatten(_polygon*p,_listebasis<_schatten<_tg,_to> >*schattenliste,_licht<_tg,_to>*l,_tg s):_schatten<_tg,_to>(schattenliste,l,s),_listenknotenbasis<_polygonschatten>(p){
                                                                ppolygon=p;
                                                                aktualisieren();
                                                                
};
_polygonschatten::~_polygonschatten(){
                                                                pquadstrip.loeschen();
                                                                pquado.loeschen();
                                                                pquadu.loeschen();
};
void _polygonschatten::opazitaet(const _to){
};
void _polygonschatten::zeichnen(_grafik*gra){
                                                                _licht<_tg,_to>*plicht=licht();
                                                                if(plicht){
                                                                 if(geaendert()) aktualisieren();
                                                                 gra->polygon(&pquado);
                                                                 gra->rechteckstreifenzyklisch(&pquadstrip);
                                                                 gra->polygon(&pquadu);
                                                                };
};
void _polygonschatten::zeichnendebug(_grafik*gra){
                                                                _licht<_tg,_to>*plicht=licht();
                                                                if(plicht){
                                                                 if(geaendert()) aktualisieren();
                                                                 _vektor4<_to> col(plicht->farbedynamisch()[0],plicht->farbedynamisch()[1],plicht->farbedynamisch()[2],(_to)0.1f);
                                                                 gra->transparenz(true);//glEnable(GL_BLEND);
                                                                 gra->transparenzmultiplikativ();//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                                                                 gra->textur(false);//glDisable(GL_TEXTURE_2D);
                                                                 gra->beleuchtung(false);//glDisable(GL_LIGHTING);
                                                                 gra->ausschussflaeche(false);//glDisable(GL_CULL_FACE);
                                                                 gra->rechteckstreifenzyklisch(&pquadstrip,col);
                                                                 col.setzen(0,0,(_to)0.5f,(_to)0.1f);
                                                                 gra->polygon(&pquadu,col);
                                                                 gra->transparenz(false);//glDisable(GL_BLEND);
                                                                 gra->textur(true);//glEnable(GL_TEXTURE_2D);
                                                                 gra->beleuchtung(true);//glEnable(GL_LIGHTING);
                                                                 gra->ausschussflaeche(true);//glEnable(GL_CULL_FACE);
                                                                 gra->transparenzadditiv();//glBlendFunc(GL_ONE,GL_ONE);
                                                                };
};
void _polygonschatten::aktualisieren(){
                                                                _licht<_tg,_to>*plicht=licht();
                                                                if(plicht){
                                                                 _tg plaenge=laenge();
                                                                 pquadstrip.loeschen();
                                                                 pquado.loeschen();
                                                                 pquadu.loeschen();
                                                                 _vektor3<_tg> v=ppolygon->mitte()-plicht->ort();
                                                                 _vertex*vit;
                                                                 _vertex*vin;
                                                                 _listenknoten<_vertex>*lnv;
                                                                 ppolygon->anfang(lnv);
                                                                 vit=lnv->objekt();
                                                                 vin=lnv->naechstes()->objekt();
                                                                 if((((ppolygon->mitte()-vit->ort()) % (vin->ort()-vit->ort())) * v)<0) {
                                                                  do{
                                                                   vit=lnv->objekt();
                                                                   v=vit->ort()-plicht->ort();
                                                                   v.normalisieren();
                                                                   v*=plaenge;
                                                                   pquadstrip.einhaengen(new _vektor3<_tg>(vit->ort()));
                                                                   pquadstrip.einhaengen(new _vektor3<_tg>(vit->ort() + v));
                                                                   pquado.einhaengen(new _vektor3<_tg>(vit->ort()));
                                                                   pquadu.einhaengen(new _vektor3<_tg>(vit->ort() + v));
                                                                  }while(ppolygon->naechstes(lnv));
                                                                  pquadu.invertieren();
                                                                 }else{
                                                                  do{
                                                                   vit=lnv->objekt();
                                                                   v=vit->ort()-plicht->ort();
                                                                   v.normalisieren();
                                                                   v*=plaenge;
                                                                   pquadstrip.einhaengen(new _vektor3<_tg>(vit->ort() + v));
                                                                   pquadstrip.einhaengen(new _vektor3<_tg>(vit->ort()));
                                                                   pquadu.einhaengen(new _vektor3<_tg>(vit->ort() + v));
                                                                   pquado.einhaengen(new _vektor3<_tg>(vit->ort()));
                                                                  }while(ppolygon->naechstes(lnv));
                                                                  pquado.invertieren();
                                                                 };
                                                                };
};
//******************************************************************************************************************************************************************************************************
//                                                              K A N T E P O L Y G O N
//******************************************************************************************************************************************************************************************************

_kantepolygon::_kantepolygon(_polygon*p0,_polygon*p1,_vertex*v0,_vertex*v1){
                                                                ppolygon[0]=p0;
                                                                ppolygon[1]=p1;//ACHTUNG:kann auch 0 sein            
                                                                pvertex[0]=v0;
                                                                pvertex[1]=v1;
                                                                pvertexstart=0;
                                                                aktualisieren();
                                                                pflag=0;
                                                                pisintroconnectorcount=0;
                                                                pintersectioncount=0;
};
_kantepolygon::~_kantepolygon(){
                                                                plistisintroconnector.loeschen();
};
void _kantepolygon::aktualisieren(){

                                                                pvector=pvertex[1]->ort()-pvertex[0]->ort();
                                                                pmiddle=pvertex[0]->ort()+pvector*0.5f;
                                                                _vektor3<_tg> h;
                                                                unsigned int i;
                                                                unsigned int z;
                                                                _vektoranalysis2<_tg> V2;
                                                                z=2;
                                                                if(ppolygon[1]==0) z=1;
                                                                for(i=0;i<z;i++){
                                                                 pvector2d[i].setzen(
                                                                 pvector[ppolygon[i]->groessterindex(0)],
                                                                 pvector[ppolygon[i]->groessterindex(1)]);
                                                                 pmiddle2d[i].setzen(
                                                                 pmiddle[ppolygon[i]->groessterindex(0)],
                                                                 pmiddle[ppolygon[i]->groessterindex(1)]);
                                                                 pnormal[i]=ppolygon[i]->normale() % pvector;
                                                                 pnormal[i].normalisieren();
                                                                 h=ppolygon[i]->mitte() - pmiddle;
                                                                 if((h*pnormal[i])<0) pnormal[i]*=-1;
                                                                 pnormal2d[i].setzen(
                                                                 pnormal[i][ppolygon[i]->groessterindex(0)],
                                                                 pnormal[i][ppolygon[i]->groessterindex(1)]);
                                                                 pdeterminante2d[i]=V2.determinieren(pvector2d[i],pnormal2d[i]);
                                                                };
};
void _kantepolygon::invertierenvertex(){
                                                                _vertex*v;
                                                                //--------------------
                                                                v=pvertex[0];
                                                                pvertex[0]=pvertex[1];
                                                                pvertex[1]=v;
                                                                pvector*=-1;
                                                                //pvector2d[0]*=-1;
                                                                //pvector2d[1]*=-1;
                                                                //ACHTUNG !!!!!!!!!!!!!!!!!!!!! neue datenelemente nacharbeiten
};
void _kantepolygon::invertierenpolygon(){
                                                                _polygon*p;
                                                                //----------------------
                                                                if(ppolygon[1]!=0){
                                                                 p=ppolygon[0];
                                                                 ppolygon[0]=ppolygon[1];
                                                                 ppolygon[1]=p;
                                                                };

                                                                //ACHTUNG !!!!!!!!!!!!!!!!!!!!! neue datenelemente nacharbeiten
};
void _kantepolygon::start(_vertex*v){
                                                                if((v==pvertex[0])||(v==pvertex[1])){
                                                                 pvertexstart=v;
                                                                };
};
void _kantepolygon::invertieren(){
                                                                _vertex*h;
                                                                //------------
                                                                plistisintroconnector.invertieren();
                                                                // invert_ring(firstisintroconnector);
                                                                h=pvertex[0];
                                                                pvertex[0]=pvertex[1];
                                                                pvertex[1]=h;
                                                                pvector*=-1;//mul(-1.0f,vektor);
                                                                //ACHTUNG !!!!!!!!!!!!!!!!!!!!! neue datenelemente nacharbeiten
};
_listebasis<_verbinderisintro >*_kantepolygon::verbinderisintroliste(){
                                                                return(&plistisintroconnector);
};
void _kantepolygon::inkrementierenanzahlverbinderisintro(){
                                                                pisintroconnectorcount++;
};
void _kantepolygon::dekrementierenanzahlverbinderisintro(){
                                                                pisintroconnectorcount--;
};