//grundplatte : _druckerwindows.cpp
#include <_global.hpp>
#ifdef GRUNDPLATTE_UNTER_WINDOWS
#include <_druckerwin.hpp>
namespace _win{
//*******************************************************************************************************************************************************************************
//								P R I N T E R
//*******************************************************************************************************************************************************************************
                /*

void table_dlg::printtextversion()
{
    CDC printerdc;
    TEXTMETRIC tx;

    CPrintDialog pdg(FALSE);
    CSize papersize; //extent of paper in millimeters
    DOCINFO docinfo;
    int lineheight;
    int linesperpage;
    int topoffset;
    int bottomoffset;

    pdg.m_pd.hDC = 0;
    pdg.m_pd.hDevMode = 0;
    pdg.m_pd.hDevNames = 0;

    if (pdg.DoModal()==IDOK)
    {
//*************prepare printing begin******************
        printerdc.Attach(pdg.m_pd.hDC);
        memset(&docinfo, 0, sizeof(DOCINFO));
        docinfo.cbSize = sizeof(DOCINFO);
        docinfo.lpszDocName = "AquaDAS";
        docinfo.lpszOutput = pdg.GetPortName();
        papersize.cx = printerdc.GetDeviceCaps(HORZSIZE); //height in mm
        papersize.cy = printerdc.GetDeviceCaps(VERTSIZE); //breite in mm

        printerdc.SetMapMode(MM_LOMETRIC);
        writefont.CreateFont(30, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_MODERN+FIXED_PITCH, "Courier New");
        writefont_underline.CreateFont(30, 0, 0, 0, FW_NORMAL, 0, 1, 0, DEFAULT_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_MODERN+FIXED_PITCH, "Courier New");
        printerdc.SetBkMode(TRANSPARENT);
        printerdc.SelectObject(&writefont);

        printerdc.GetTextMetrics(&tx);
        lineheight = tx.tmHeight+tx.tmExternalLeading+2; //height of one linie in 0.1mm units
        linesperpage = (int)(papersize.cy / (ceil((double)lineheight/10))); //berechnen the number of max. rows per page
        topoffset = -lineheight; //position = erstes linie
        topoffset -= lineheight*4; //subtract 4 lines from top

        bottomoffset = -(linesperpage*lineheight); //position = last linie that fits on a single page
        bottomoffset += lineheight*4; //add 4 lines to bottom
//*************prepare printing end******************
//*************start printing ******************
        printerdc.StartDoc(&docinfo);
        printerdc.StartPage();
        printerdc.SetMapMode(MM_LOMETRIC);
        printerdc.SetBkMode(TRANSPARENT);
        printerdc.SelectObject(&writefont);
        printerdc.SetTextAlign(TA_BOTTOM|TA_LEFT);

        printdataset(&printerdc, topoffset, bottomoffset, lineheight);
        //  char out[50];
        //  sprintf(out, "linesperpage: %i  topoffset: %i  bottomoffset: %i", linesperpage, topoffset, bottomoffset);
        //  MessageBox(out);

        printerdc.EndPage();
        printerdc.EndDoc();
//*************stop printing ******************

        //free automatically allocated resources
        if (pdg.m_pd.hDevMode!=0) GlobalFree(pdg.m_pd.hDevMode);
        if (pdg.m_pd.hDevNames!=0) GlobalFree(pdg.m_pd.hDevNames);
        if (pdg.m_pd.hDC!=0) DeleteDC(printerdc.Detach()); //detach HDC from CDC-objekt and delete it
    }
}

void table_dlg::checkoffset(CDC *dc, int *textpos, int topoffset, int bottomoffset, int lineheight)
{
    if (*textpos < bottomoffset)
    {
        *textpos = topoffset;
        dc->EndPage();
        dc->StartPage();
        dc->SetMapMode(MM_LOMETRIC);
        dc->SetBkMode(TRANSPARENT);
        dc->SelectObject(&writefont);
        dc->SetTextAlign(TA_BOTTOM|TA_LEFT);

    }else *textpos -= lineheight;
}

void table_dlg::printdataset(CDC *dc, int topoffset, int bottomoffset, int lineheight)
{
    int textpos = topoffset;
    int xoffset = 50;
    char out[512];

    SYSTEMTIME time;
    GetLocalTime(&time);

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "                     AquaDAS  Standard-Datensatz  AQUASAFE-08");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "%02u.%02u.%02u,  %02u:%02u Uhr", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Maschinen-Nummer          : %s", serialnumber);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Software-Version          : %s", softwareversion);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Aktuelles Programm        : %s ", std_dset._w17_curprog);
    if (std_dset.w17_1==6) //if current program is setzen to "spülen" anhaengen the counter value
    {
        strcat(out, std_dset._w19);
        strcat(out, " Liter");
    }
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Aktueller Alarmstatus     : %s", std_dset._w17_curalarm);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->SelectObject(&writefont_underline);
    sprintf(out, "Betriebswerte");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    dc->SelectObject(&writefont);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "                             min      aktuell      max");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Permeat LF [µS/cm]        : %5s      %5s      %5s", permeat_conduct_min, std_dset._u3, permeat_conduct_max);
    if (std_dset.w18_7==TRUE) strcat(out, "        < Aktueller Wert ist zu hoch ! >");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Permeat Temp. [°C]        : %5s      %5s      %5s", permeat_temp_min, std_dset._u1, permeat_temp_max);
    if (std_dset.w18_5==TRUE) strcat(out, "        < Aktueller Wert ist zu hoch ! >");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Permeatdruck [bar]        : %5s      %5s      %5s", permeat_pressure_min, std_dset._u4, permeat_pressure_max);
    if (std_dset.w18_8==TRUE) strcat(out, "        < Aktueller Wert ist zu hoch ! >");
    if (std_dset.w18_1==TRUE) strcat(out, "        < Aktueller Wert ist zu niedrig ! >");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Konzentratdruck [bar]     : %5s      %5s      %5s", concentrate_pressure_min, std_dset._u5, concentrate_pressure_max);
    if (std_dset.w18_9==TRUE) strcat(out, "        < Aktueller Wert ist zu hoch ! >");
    if (std_dset.w18_2==TRUE) strcat(out, "        < Aktueller Wert ist zu niedrig ! >");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Rohwasserzulauf [l/min]   : %5s      %5s      %5s", rawwater_in_min, std_dset._u6, rawwater_in_max);
    if (std_dset.w18_3==TRUE) strcat(out, "        < Aktueller Wert ist zu niedrig ! >");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Rohwasser LF [µS/cm]      : %5s      %5s      %5s", rawwater_conduct_min, std_dset._u2, rawwater_conduct_max);
    if (std_dset.w18_6==TRUE) strcat(out, "        < Aktueller Wert ist zu hoch ! >");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Rohwasser Temp. [°C]      : %5s      %5s      %5s", rawwater_temp_min, std_dset._u0, rawwater_temp_max);
    if (std_dset.w18_4==TRUE) strcat(out, "        < Aktueller Wert ist zu hoch ! >");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Rückhalterate [%%]         :            %5s", std_dset._w11);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Ausbeute [%%]              :            %5s", std_dset._w10);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Permeatleistung [l/min]   :            %5s", std_dset._w9);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Konzentratabfluss [l/min] :            %5s", std_dset._u7);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Permeatentnahme [l/min]   :            %5s", std_dset._w8);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Ø Ablauf [l/min]          :            %5s", std_dset._w13);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Ø Zulauf [l/min]          :            %5s", std_dset._w12);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->SelectObject(&writefont_underline);
    sprintf(out, "Aktorsteuerung");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    dc->SelectObject(&writefont);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "V1 : %s  V2 : %s  V3 : %s  V4 : %s  V5 : %s", std_dset._u9_v1, std_dset._u9_v2, std_dset._u9_v3, std_dset._u9_v4, std_dset._u9_v5);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "V6 : %s  V7 : %s  V8 : %s  V9 : %s  Pumpe : %s", std_dset._u9_v6, std_dset._u9_v7, std_dset._u9_v8, std_dset._u9_v9, std_dset._u9_p);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->SelectObject(&writefont_underline);
    sprintf(out, "Niveaustand");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    dc->SelectObject(&writefont);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "%s", std_dset._u8);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->TextOut(xoffset, textpos, " ", 1);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    dc->SelectObject(&writefont_underline);
    sprintf(out, "Zählerstände");
    dc->TextOut(xoffset, textpos, out, strlen(out));
    dc->SelectObject(&writefont);
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Betrieb [h]   : %s", std_dset._w14);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Wasser  [cbm] : %s", std_dset._w15);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed

    sprintf(out, "Permeat [cbm] : %s", std_dset._w16);
    dc->TextOut(xoffset, textpos, out, strlen(out));
    checkoffset(dc, &textpos, topoffset, bottomoffset, lineheight); //check if new page should be printed
}

void table_dlg::printbitmapversion()
{
    CDC memdc;
    RECT rec;
    CBitmap membitmap;
    CBitmap * oldmembitmap;
    CWindowDC dc(this);
    GetWindowRect(&rec);
    UpdateWindow();
    SetFocus();

    //berechnen bitmap extensions
    int cx = rec.right-rec.left;
    int cy = rec.bottom-rec.top;

    membitmap.CreateCompatibleBitmap(&dc, cx, cy);
    memdc.CreateCompatibleDC(&dc);
    oldmembitmap = memdc.SelectObject(&membitmap);
    memdc.BitBlt(0, 0, cx, cy, &dc, 0, 0, SRCCOPY);

    stop_process_for_printing_saving_flag = FALSE; //indicate that new dataset values can be displayed

    //Window content is copied to memory, now handle sending to printer
    CDC printerdc;
    CPrintDialog pdg(FALSE);
    CSize papersize; //extent of paper in millimeters
    DOCINFO docinfo;
    int xlogicalpixelsperinch;
    int ylogicalpixelsperinch;
    int screenxlogicalpixelsperinch;
    int screenylogicalpixelsperinch;
    int paperwidth; //breite in pixels
    int paperheight; //height in pixels
    double bmpratio;
    int outputx; //final output groesse
    int outputy; //final output groesse

    pdg.m_pd.hDC = 0;
    pdg.m_pd.hDevMode = 0;
    pdg.m_pd.hDevNames = 0;
    if (pdg.DoModal()==IDOK)
    {
        printerdc.Attach(pdg.m_pd.hDC);
        if ((printerdc.GetDeviceCaps(RASTERCAPS)&RC_STRETCHBLT)==RC_STRETCHBLT)
        {
            memset(&docinfo, 0, sizeof(DOCINFO));
            docinfo.cbSize = sizeof(DOCINFO);
            docinfo.lpszDocName = "AquaDAS";
            docinfo.lpszOutput = pdg.GetPortName();
            papersize.cx = printerdc.GetDeviceCaps(HORZSIZE);
            papersize.cy = printerdc.GetDeviceCaps(VERTSIZE);
            xlogicalpixelsperinch = printerdc.GetDeviceCaps(LOGPIXELSX);
            ylogicalpixelsperinch = printerdc.GetDeviceCaps(LOGPIXELSY);
            screenxlogicalpixelsperinch = dc.GetDeviceCaps(LOGPIXELSX);
            screenylogicalpixelsperinch = dc.GetDeviceCaps(LOGPIXELSY);

            paperwidth = (int)((double)papersize.cx * (double)xlogicalpixelsperinch / 25.4); //breite of printed page in pixels
            paperheight = (int)((double)papersize.cy * (double)ylogicalpixelsperinch / 25.4);
            bmpratio = (double)cx/(double)cy;

            printerdc.SetMapMode(MM_TEXT); //bild 1:1
            printerdc.StartDoc(&docinfo);
            printerdc.StartPage();

            outputx = (int)(paperwidth*0.85);
            outputy = (int)(outputx/bmpratio);
            printerdc.StretchBlt((paperwidth-outputx)/2, (int)(paperheight*0.05), outputx, outputy, &memdc, 0, 0, cx, cy, SRCCOPY);

            printerdc.EndPage();
            printerdc.EndDoc();
        }else MessageBox("Drucker wird nicht unterstützt!", "AquaDAS Statusmeldung", MB_ICONINFORMATION);
        //free automatically allocated resources
        if (pdg.m_pd.hDevMode!=0) GlobalFree(pdg.m_pd.hDevMode);
        if (pdg.m_pd.hDevNames!=0) GlobalFree(pdg.m_pd.hDevNames);
        if (pdg.m_pd.hDC!=0) DeleteDC(printerdc.Detach()); //detach HDC from CDC-objekt and delete it
    }

    //cleanup resources
    memdc.SelectObject(oldmembitmap);
    memdc.DeleteDC();
}


              */


};
#endif
