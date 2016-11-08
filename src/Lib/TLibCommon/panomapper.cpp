#include "panomapper.h"

// antialias filter lookups
float G_AAFILTER_NONE[9]     = {    0.0,     0.0,     0.0,    0.0,    1.0,    0.0,     0.0,     0.0,     0.0};
float G_AAFILTER_9TENTHS[9]  = {-0.0054f,  0.0155f, -0.0411f, 0.0680f, 0.9259f, 0.0680f, -0.0411f,  0.0155f, -0.0054f};
float G_AAFILTER_8TENTHS[9]  = {-0.0064f,  0.0208f, -0.0594f, 0.1024f, 0.8851f, 0.1024f, -0.0594f,  0.0208f, -0.0064f};
float G_AAFILTER_3FOURTHS[9] = {-0.0059f,  0.0228f, -0.0723f, 0.1316f, 0.8475f, 0.1316f, -0.0723f,  0.0228f, -0.0059f};
float G_AAFILTER_7TENTHS[9]  = {-0.0037f,  0.0217f, -0.0822f, 0.1632f, 0.8020f, 0.1632f, -0.0822f,  0.0217f, -0.0037f};
float G_AAFILTER_6TENTHS[9]  = { 0.0037f,  0.0072f, -0.0816f, 0.2215f, 0.6984f, 0.2215f, -0.0816f,  0.0072f,  0.0037f};
float G_AAFILTER_1HALF[9]    = { 0.0060f, -0.0133f, -0.0501f, 0.2598f, 0.5951f, 0.2598f, -0.0501f, -0.0133f,  0.0060f};
float G_AAFILTER_4TENTHS[9]  = { 0.0002f, -0.0227f, -0.0013f, 0.2739f, 0.4998f, 0.2739f, -0.0013f, -0.0227f,  0.0002f};
float G_AAFILTER_3TENTHS[9]  = {-0.0063f, -0.0122f,  0.0549f, 0.2642f, 0.3988f, 0.2642f,  0.0549f, -0.0122f, -0.0063f};
float G_AAFILTER_1FOURTH[9]  = {-0.0055f,  0.0017f,  0.0810f, 0.2498f, 0.3461f, 0.2498f,  0.0810f,  0.0017f, -0.0055f};
float G_AAFILTER_2TENTHS[9]  = { 0.0011f,  0.0215f,  0.1041f, 0.2282f, 0.2902f, 0.2282f,  0.1041f,  0.0215f,  0.0011f};
float G_AAFILTER_ZERO156[9]  = { 0.0181f,  0.0488f,  0.1227f, 0.1967f, 0.2274f, 0.1967f,  0.1227f,  0.0488f,  0.0181f};

panomapper::panomapper(){
}

panomapper::~panomapper(){
}

/*
 * charToSph2Map
 * -------------------------------------
 * Descrp: Reads the input char* and assigns the appropriate sph2map
 * Inputs: (const char*) map representation
 * Return: (sph2map)     assignment
 */
sph2map panomapper::charToSph2Map(const char* s2m){
    if(s2m){
	if(     !strcmp(s2m,"rect"))
	    return sph2rect;
  else if (!strcmp(s2m, "aitoff"))
    return sph2aitoff;
  else if (!strcmp(s2m, "sanson"))
    return sph2sanson;
  else if (!strcmp(s2m, "poletop"))
    return sph2poletop;
  else if (!strcmp(s2m, "poledown"))
    return sph2poledown;
	else if(!strcmp(s2m,"eqar"))
	    return sph2eqar;
	else if(!strcmp(s2m,"dyad"))
	    return sph2dyad;
	else if(!strcmp(s2m,"merc"))
	    return sph2merc;
	else if(!strcmp(s2m,"cos2"))
	    return sph2cos2;
	else if(!strcmp(s2m,"cube"))
	    return sph2cube;
	else if(!strcmp(s2m,"mult"))
	    return sph2mult;
	else if(!strcmp(s2m,"bmul"))
	    return sph2bmul;
	else if(!strcmp(s2m,"trec"))
	    return sph2trec;
	else if(!strcmp(s2m,"brec"))
	    return sph2brec;
	else if(!strcmp(s2m,"grid"))
	    return sph2grid;
	else if(!strcmp(s2m,"beqr"))
	    return sph2beqr;
	else if(!strcmp(s2m,"teqr"))
	    return sph2teqr;
	else
	    fprintf(stderr,"No compatible mapping found: %s\n",s2m);
    }
    return sph2rect;
}

/*
 * charToMap2Sph
 * -------------------------------------
 * Descrp: Reads the input char* and assigns the appropriate map2sph
 * Inputs: (const char*) map representation
 * Return: (map2sph)     assignment
 */
map2sph panomapper::charToMap2Sph(const char* m2s){
    if(m2s){
      if (!strcmp(m2s, "rect"))
        return rect2sph;
      else if (!strcmp(m2s, "aitoff"))
        return aitoff2sph;
      else if (!strcmp(m2s, "sanson"))
        return sanson2sph;
      else if (!strcmp(m2s, "poletop"))
        return poletop2sph;
      else if (!strcmp(m2s, "poledown"))
        return poledown2sph;
      else if (!strcmp(m2s, "rectdown_inv"))
        return rectdown_inv2sph;
      else if (!strcmp(m2s, "recttop_inv"))
        return rect2sph;
      else if (!strcmp(m2s, "two"))
        return two2sph;
      else if (!strcmp(m2s, "eqar"))
        return eqar2sph;
      else if (!strcmp(m2s, "dyad"))
        return dyad2sph;
      else if (!strcmp(m2s, "merc"))
        return merc2sph;
      else if (!strcmp(m2s, "cube"))
        return cube2sph;
      else if (!strcmp(m2s, "cos2"))
        return cos22sph;
      else if (!strcmp(m2s, "view"))
        return view2sph;
      else if (!strcmp(m2s, "trec"))
        return trec2sph;
      else if (!strcmp(m2s, "brec"))
        return brec2sph;
      else if (!strcmp(m2s, "grid"))
        return grid2sph;
      else if (!strcmp(m2s, "beqr"))
        return beqr2sph;
      else if (!strcmp(m2s, "teqr"))
        return teqr2sph;
      else
        fprintf(stderr, "No compatible mapping found: %s\n", m2s);
    }
    return rect2sph;
}

/*
 * charToInterpl
 * -------------------------------------
 * Descrp: Reads the input char* and assigns the appropriate interpolation
 * Inputs: (const char*) interpolation
 * Return: (filter)      assignment
 */
ifilter panomapper::charToInterpl(const char* f){
    if(f){
	if(     !strcmp(f,"nearest"))
	    return filter_nearest;
	else if(!strcmp(f,"linear"))
	    return filter_linear;
	else if(!strcmp(f,"bicubic"))
	    return filter_bicubic;
  else if (!strcmp(f, "lanczos"))
    return filter_lanczos;
    }
    return filter_bicubic;
}

/*
 * charToIntVec
 * -------------------------------------------
 * Descrp: Reads in put char* and generates a vector of corresponding ints
 * Inputs: (const char*) vector of ints as a comma separated list
 * Return: (vector<int>) vector of ints
 */
std::vector<int> panomapper::charToIntVec(const char* v){
    std::string s = std::string(v);
    std::vector<int> vout;
    while(s.size()>0){
	size_t idx = s.rfind(",");
	std::string ss = s.substr(idx+1,s.size()-idx);
	vout.push_back(std::stoi(ss));
	if(idx==std::string::npos)
	    break;
	s.resize(idx);
    }
    std::reverse(vout.begin(),vout.end());
    return vout;
}

/*
 * sph2mapToDim
 * -------------------------------------
 * Descrp: Sets the width/height/pages of the srcW/H/P parameters given the mapping
 *         and the desired img height
 * Inputs: (sph2map) mapping
 *         (int)     height
 * Return: (imgdim)  dimensions  
 */
std::vector<imgdim> panomapper::sph2mapToDim(sph2map s, std::vector<int> h, std::vector<int> w){
    std::vector<imgdim> vout;
    for(int i=0; i < h.size(); i++){
	vout.push_back(sph2mapToDim(s,h[i],w[i]));
    }
    return vout;
}

imgdim panomapper::sph2mapToDim(sph2map s, int h, int w){
    imgdim d;
    d.w = 2*h;
    d.h = h;
    d.p = 1;
    
    // special cases
    if(s == sph2cube || s == sph2mult || s == sph2trec || s == sph2teqr || s == sph2brec || s == sph2beqr || s==sph2bmul){
	d.w = w;
	d.h = h;
	d.p = 6;
    }
    else if (s == sph2grid){
	d.w = w;
	d.h = h;
	d.p = 24;
    }
    else if (w>0)
	d.w = w;

    return d;
}

/*
 * map2sphToDim
 * -------------------------------------
 * Descrp: Sets the width/height/pages of the dstW/H/P parameters given the mapping
 *         and the desired img height
 * Inputs: (map2sph) mapping
 *         (int)     height
 * Return: (none)
 */
imgdim panomapper::map2sphToDim(map2sph s, int h, int w){
    imgdim d;
    d.w = 2*h;
    d.h = h;
    d.p = 1;

    // special cases
    if(s == cube2sph){
	d.w = h;
	d.p = 6;
    }
    else if (s == view2sph)
	d.w = w;
    else if(w>0)
	d.w = w;

    return d;
}

remapper::remapper(){
    sph2src   = sph2rect;
    dst2sph   = rect2sph;
    aBlend    = aBlendBrec;
    fil       = filter_bicubic;
    samp_pat  = &G_CENT_PATTERN;
    numPages  = 1;
    viewFlag  = false;
    trackFlag = false;
    fov.x     = 90;
    fov.y     = 90;
    startXY.x = 0.;
    startXY.y = 0.;
    spanXY.x  = 0.;
    spanXY.y  = 0.;
    dstDim.w  = 1000;
    dstDim.h  = 500;
    dstDim.p  = 1;
    fview     = NULL;
    m_numFrames = 1;
    multFlag  = false;
    blendFlag = false;
}

remapper::~remapper(){
    if(G_INP_LUT)
	free(G_INP_LUT);
    if(G_OUT_LUT)
	free(G_OUT_LUT);
    if(fview)
	fclose(fview);
}

/*
 * init
 * ---------------------------------------------
 * Descrp: Init requires the original/destination mappings, 
z *         the type of interpolation
 * Inputs:
 * Return: (none)
 */
void remapper::init(const char* inp_map, const char* out_map, const char* interpl, const char* m, bool bf,
		    int n, float x, float y, float w, float h, int z, const char* b, int v, float vp, float vt,
        const char* t, const char* a, const char* inp, const char* out, double AngleX, double AngleY, double AngleZ, int isInvRotMapping){

    sph2src   = charToSph2Map (inp_map);
    dst2sph   = charToMap2Sph (out_map);
    fil              = charToInterpl     (interpl);
    m_numFrames = z;

    std::vector<int> srcHgt = charToIntVec(m);
    std::vector<int> srcWid = charToIntVec(b);

    srcDim    = sph2mapToDim(sph2src,srcHgt,srcHgt);
    dstDim    = map2sphToDim(dst2sph,n);
    numPages  = dstDim.p;
 
    // special cases
    if(bf)
    {
      blendFlag = bf;
      setBlend();
    }
    if(b>0)
	srcDim    = sph2mapToDim(sph2src,srcHgt,srcWid);
    if(v>0)
	dstDim    = map2sphToDim(dst2sph,n,v);
    if(dst2sph == cos22sph)
	setupCos2();
    if(dst2sph == view2sph)
    {
      dstDim = map2sphToDim(dst2sph, (int)h, (int)w);
      viewFlag = true;
      clearTrData();
      setRotationMat(vp, vt);
      fov.x = x;
      fov.y = y;
      if (t){
        trackFlag = true;
        fopen_s(&fview, t, "r");
      }
    }
    if(dst2sph == trec2sph || dst2sph == teqr2sph || dst2sph == brec2sph || dst2sph == beqr2sph || dst2sph == grid2sph)
    {
	    startXY.x = x;
	    startXY.y = y;
	    spanXY.x  = w;
	    spanXY.y  = h;
	    setMapOffset(startXY);
	    setMapScalefactor(spanXY);
    }
    if(sph2src == sph2mult || sph2src == sph2trec || sph2src == sph2teqr || sph2src == sph2brec || sph2src == sph2beqr || sph2src == sph2bmul || sph2src == sph2grid)
	multFlag = true;
    if(a)
	G_ACSFLAG = true;

    // file read writers
    srcYuv.init(inp, srcWid, srcHgt, srcDim[0].p, multFlag, AngleX, AngleY, AngleZ, isInvRotMapping);
    dstYuv.init(out, dstDim.w, dstDim.h, dstDim.p);

    // deal with this later
    //if(G_ACSFLAG)
	//acsYuv.init(a, srcWid, srcHgt, srcDim[0].p);
}

/*
 * remapFrames
 * ---------------------------------------------
 * Descrp: Remaps all frames from the source file to the destination
 *         assuming the panomapper has been initialized
 * Inputs: (none)
 * Return: (none)
 */
void remapper::remapFrames(std::map<int, std::vector<double>> rotMap, int isfirstFrameRot, int inputBits, int outputBits, int skipFrameNum){
    int nf = 0;

    double storeX, storeY, storeZ;
    if (skipFrameNum != 0)
    {
      srcYuv.skipSomeFrames(inputBits, skipFrameNum);
    }
    while(nf < m_numFrames && srcYuv.readNextFrame(inputBits)){
	nf++;
	printf("Frame: %d\r", nf); fflush(stdout);

  if (nf == 1 && isfirstFrameRot == 0)
  {
    storeX = srcYuv.getY()->AngleX;
    storeY = srcYuv.getY()->AngleY;
    storeZ = srcYuv.getY()->AngleZ;
    srcYuv.getY()->AngleX = 0.0;
    srcYuv.getY()->AngleY = 0.0;
    srcYuv.getY()->AngleZ = 0.0;
    srcYuv.getU()->AngleX = 0.0;
    srcYuv.getU()->AngleY = 0.0;
    srcYuv.getU()->AngleZ = 0.0;
    srcYuv.getV()->AngleX = 0.0;
    srcYuv.getV()->AngleY = 0.0;
    srcYuv.getV()->AngleZ = 0.0;
  }
  if (rotMap.size() != 0)
  {
    std::map<int, std::vector<double>>::iterator it = rotMap.find(nf - 1);
    storeX = srcYuv.getY()->AngleX;
    storeY = srcYuv.getY()->AngleY;
    storeZ = srcYuv.getY()->AngleZ;
    if (it != rotMap.end())
    {
      srcYuv.getY()->AngleX = it->second[0];
      srcYuv.getY()->AngleY = it->second[1];
      srcYuv.getY()->AngleZ = it->second[2];
      srcYuv.getU()->AngleX = it->second[0];
      srcYuv.getU()->AngleY = it->second[1];
      srcYuv.getU()->AngleZ = it->second[2];
      srcYuv.getV()->AngleX = it->second[0];
      srcYuv.getV()->AngleY = it->second[1];
      srcYuv.getV()->AngleZ = it->second[2];
    }
 
  }
	if(trackFlag)
	    readNextTrData(fview, nf, viewFlag);
	if(G_ACSFLAG)
	    acsYuv.clear();
	dstYuv.clear();

	antialiasFilter();
	remap(srcYuv.getY(), dstYuv.getY(), acsYuv.getY());	
	remap(srcYuv.getU(), dstYuv.getU(), acsYuv.getU());	
	remap(srcYuv.getV(), dstYuv.getV(), acsYuv.getV());	
  if (nf == 1 && isfirstFrameRot == 0)
  {
    srcYuv.getY()->AngleX = storeX;
    srcYuv.getY()->AngleY = storeY;
    srcYuv.getY()->AngleZ = storeZ;
    srcYuv.getU()->AngleX = storeX;
    srcYuv.getU()->AngleY = storeY;
    srcYuv.getU()->AngleZ = storeZ;
    srcYuv.getV()->AngleX = storeX;
    srcYuv.getV()->AngleY = storeY;
    srcYuv.getV()->AngleZ = storeZ;
  }
  if (rotMap.size() != 0)
  {
    srcYuv.getY()->AngleX = storeX;
    srcYuv.getY()->AngleY = storeY;
    srcYuv.getY()->AngleZ = storeZ;
    srcYuv.getU()->AngleX = storeX;
    srcYuv.getU()->AngleY = storeY;
    srcYuv.getU()->AngleZ = storeZ;
    srcYuv.getV()->AngleX = storeX;
    srcYuv.getV()->AngleY = storeY;
    srcYuv.getV()->AngleZ = storeZ;
  }
	dstYuv.writeNextFrame(outputBits);
	if(G_ACSFLAG) 
	    acsYuv.writeNextFrame(outputBits, false);
    }
    printf("Total frames processed: %d\n", nf);
}

/*
 * antialiasFactorX
 * -------------------------------------------------------------
 * Descrp: Calculates the antiliasing factor depending on the src dst mappings and the src dst dim
 *         Note that this does not currently compensate for irregular input images (e.g., cube, mult)
 * Inputs: (none)
 * Return: (int) factor [-1 == turned off antiliasing in x dim]
 */
float remapper::antialiasFactorX(){
    float fac = 1.0f;
    if(sph2src==sph2mult||sph2src==sph2cube||sph2src==sph2bmul)
	fac = 1.0f;
    else if(dst2sph==cube2sph)
	fac = float(dstDim.w)*4.0f/srcDim[0].w;
    else if(dst2sph==view2sph)
	fac = float(dstDim.w)*360.f/fov.x/srcDim[0].w;
    else if(dst2sph==trec2sph)
	fac = float(dstDim.w)/srcDim[0].w;
    else if(dst2sph==teqr2sph)	
	fac = float(dstDim.w)/srcDim[0].w;
    else if(dst2sph==grid2sph)	
	fac = float(dstDim.w)*4.f/srcDim[0].w;
    else
	fac = float(dstDim.w)/srcDim[0].w;
    
    if(fac >= 1.0f)
	return 1.0f;
    return fac;
}

/*
 * antialiasFactorY
 * -------------------------------------------------------------
 * Descrp: Calculates the antiliasing factor depending on the src dst mappings and the src dst dim
 *         Note that this does not currently compensate for irregular input images (e.g., cube, mult)
 * Inputs: (none)
 * Return: (int) factor [-1 == turned off antiliasing in y dim]
 */
float remapper::antialiasFactorY(){
    float fac = 1.0f;
    if(sph2src==sph2mult || sph2src==sph2bmul)
	fac = 1.0f;
    else if(sph2src ==sph2cube)
	fac = 1.0f;
    else if (dst2sph==cube2sph)
	fac = float(dstDim.h)*2.0f/srcDim[0].h;
    else if (dst2sph==view2sph)
	fac = float(dstDim.h)*180.f/fov.y/srcDim[0].h;
    else if (dst2sph==trec2sph||dst2sph==teqr2sph||dst2sph==brec2sph||dst2sph==beqr2sph||dst2sph==grid2sph)
	fac = float(dstDim.h)*6/srcDim[0].h;
    else
	fac = float(dstDim.h)/srcDim[0].h;

    //printf("Fac: %f\n",fac);
    if(fac >= 1.0f)
	return 1.0f;
    return fac;
}

/*
 * antialiasFilter
 * --------------------------------------------------------------------
 * Descrp: Performs antialiasing on srcYuv using the dimensions of dstYuv
 *         Note that this can only operate on the first page of the img data
 *         E.g., this does not currently work for cube/multiplane setups
 * Inputs: (none)
 * Return: (none)
 */
void remapper::antialiasFilter(){
    float fx = antialiasFactorX();
    float fy = antialiasFactorY();
    if(fx == 1.0f && fy == 1.0f){
	printf("Warning: antialiasing turned off\n");
	return;
    }
    
    // frame the img for opencv
    cv::Mat yMat(  srcDim[0].h,  srcDim[0].w, CV_32F, srcYuv.getY()->p);
    cv::Mat uMat(srcDim[0].h/2,srcDim[0].w/2, CV_32F, srcYuv.getU()->p);
    cv::Mat vMat(srcDim[0].h/2,srcDim[0].w/2, CV_32F, srcYuv.getV()->p);
    
    // get antialias filter
    cv::Mat dstY,dstU,dstV;
    float hx[9];
    float hy[9];
    getAntialiasFilter(9,fx,hx);
    getAntialiasFilter(9,fy,hy);

    // perform antiliasing
    cv::Mat hxm = cv::Mat(1,9,CV_32F,hx);
    cv::Mat hym = cv::Mat(1,9,CV_32F,hy);
    cv::sepFilter2D(yMat,dstY,-1,hxm,hym);
    cv::sepFilter2D(uMat,dstU,-1,hxm,hym);
    cv::sepFilter2D(vMat,dstV,-1,hxm,hym);

    // copy data to new src img
    srcYuv.setY((float*)dstY.data);
    srcYuv.setU((float*)dstU.data);
    srcYuv.setV((float*)dstV.data);
    return;
}

/*
 * getAntialiasFilter
 * ---------------------------------------------------------------
 * Descrp: Table lookup to get N tap 1D antialias filter for -3db gain at cutoff freq
 *         Can only handle filter sizes of length 9
 * Inputs: (int)    number of taps
 *         (float)  cutoff freq
 *         (float*) filter with pre-allocated memory
 * Return: (none)
 */
void remapper::getAntialiasFilter(int nTaps, float fc, float* h){
    int reqFilterSize = 9;
    if(!h || nTaps != reqFilterSize || fc < 0)
	fprintf(stderr, "Could not generate antialiasing filter\n");
    //if(fc < .156)
    //printf("Warning: cannot guarantee performance for normalized freq %f < .156\n", fc);

    if(fc>.95)      for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_NONE[i];
    else if(fc>.85) for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_9TENTHS[i];
    else if(fc>.775)for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_8TENTHS[i];
    else if(fc>.725)for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_3FOURTHS[i];
    else if(fc>.65) for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_8TENTHS[i];
    else if(fc>.55) for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_6TENTHS[i];
    else if(fc>.45) for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_1HALF[i];
    else if(fc>.35) for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_4TENTHS[i];
    else if(fc>.275)for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_3TENTHS[i];
    else if(fc>.225)for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_1FOURTH[i];
    else if(fc>.175)for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_2TENTHS[i];
    else            for(int i=0;i<reqFilterSize;i++) h[i] = G_AAFILTER_ZERO156[i];
}

/*
 * supersample
 * -----------------------------------------------
 * Descrp: Sample an image at row i column j using linear bicupic interpolation
 * Inputs: (const image*) src img
 *         (const image*) dst img
 *         (const image*) access img
 *         (int)          page
 *         (int)          row
 *         (int)          column
 * Return: (none)
 */
void remapper::supersample(const image *src, const image *dst, const image *acs,
			     int f, int i, int j){
    int    F,k,c=0;
    float  I,J;
    float *p = dst[f].p + dst[f].c * (dst[f].w * i + j);

    // For each sample of the supersampling pattern ...
    for (k = 0; k < samp_pat->n; k++) {
        const float ii = samp_pat->p[k].i + i;
        const float jj = samp_pat->p[k].j + j;
	
        // Project and unproject giving the source location. Sample there.
        float v[3];
        if (dst2sph(f, ii, jj, dst, dst->h, dst->w, v) && sph2src(&F, &I, &J, src, v, 1)){
          if (sph2src == sph2aitoff)
          {
            image* p = const_cast<image*>(src);
            p->isSpatialFilterBound = 1;
          }
          if (sph2src == sph2sanson)
          {
            image* p = const_cast<image*>(src);
            p->isSpatialFilterBound = 2;
          }
          if (v[0] == 0 && v[1] == 0 && v[2] == 0)
          {
              p[0] = 0;
          }
          else
          {
            fil(src + F, acs + F, I, J, p);
          }
            c++;
        }
    }
    // Normalize the sample.
    for (k = 0; k < dst->c; k++)
        p[k] /= c;
    
}

/*
 * setBlend
 * -----------------------------------------
 * Descrp: Assigns the appropriate blending function based on the input mapping
 * Inputs: (none)
 * Return: (none)
 */
void remapper::setBlend(){
    if(sph2src == sph2brec)
	aBlend = aBlendBrec;
    else if(sph2src == sph2beqr)
	aBlend = aBlendBeqr;
    else if(sph2src == sph2bmul)
	aBlend = aBlendBmul;
    else if(sph2src == sph2grid)
	aBlend = aBlendGrid;
    else
	printf("Warning: attempting to blend an input that does not require blending\n");
}

/*
 * blendSample
 * -----------------------------------------------
 * Descrp: Sample an image at row i column j
 *         Takes into account potential border pictures and blends to remove seams
 * Inputs: (const image*) src img
 *         (const image*) dst img
 *         (const image*) access img
 *         (int)          page
 *         (int)          row
 *         (int)          column
 * Return: (none)
 */
void remapper::blendSample(const image *src, const image *dst, const image *acs,
			     int f, int i, int j){
    int    F;
    float  I,J;
    float *p = dst[f].p + dst[f].c * (dst[f].w * i + j);

    const float ii = samp_pat->p[0].i + i;
    const float jj = samp_pat->p[0].j + j;
	
    // Project and unproject giving the source location. Sample there.
    float v[3];

    if (sph2src == sph2brec || sph2src == sph2beqr || sph2src == sph2bmul || sph2src == sph2grid){
	// find the location that we want on the destination
	if (dst2sph(f, ii, jj, src, dst->h, dst->w, v)){
	    // determine whether its between images or not
	    float a = aBlend(v);
	    if(a==1.0 && sph2src(&F, &I, &J, src, v,1)){
		fil(src + F, acs + F, I, J, p);
	    }
	    else{
		float v1=0,v2=0;
		if(sph2src(&F, &I, &J, src, v,2))
		    fil(src + F, acs + F, I, J, &v1);
		if(sph2src(&F, &I, &J, src, v,3))
		    fil(src + F, acs + F, I, J, &v2);
		*p = a*v1+(1-a)*v2;
	    }
	}
    }
    else{
	if (dst2sph(f, ii, jj, src, dst->h, dst->w, v) && sph2src(&F, &I, &J, src, v,1)){
	    fil(src + F, acs + F, I, J, p);
	}
    }
}

/*
 * remap
 * -----------------------------------------------
 * Descrp: Sample an image at row i column j using li
 * Inputs: (const image*) src img
 *         (const image*) dst img
 *         (const image*) access img
 * Return: (none)
 */
void remapper::remap(const image *src, const image *dst, const image *acs){
    // Compute viewport parameters
    if (viewFlag)
	setIntrMat(dst->w, dst->h, src->w, src->h,fov.x,fov.y);

    // Sample all destination rows, columns, and pages
    int i,j,f;
    #pragma omp parallel for private(j, f)
    for         (i = 0; i < dst->h; i++)
        for     (j = 0; j < dst->w; j++)
            for (f = 0; f < dstDim.p; f++){
		if(blendFlag)
		    blendSample(src,dst,acs,f,i,j);
		else
		    supersample(src, dst, acs, f, i, j);
	    }
}


sphcomparer::sphcomparer(){
    sphData   = NULL;
    sph1      = NULL;
    sph2      = NULL;
    numPts    = 0;
    sph2sr1   = sph2rect;
    sph2sr2   = sph2rect;
    fil       = filter_bicubic;
    samp_pat  = &G_CENT_PATTERN;
    m_numFrames = 1;
    lwFlag    = false;
    swFlag    = false;
    multFlag1 = false;
    multFlag2 = false;
}

sphcomparer::~sphcomparer(){
    if(sphData)
	free(sphData);
    if(sph1)
	free(sph1);
    if(sph2)
	free(sph2);
    if(G_LAT_INP_LUT)
	free(G_LAT_INP_LUT);
    if(G_LAT_OUT_LUT)
	free(G_LAT_OUT_LUT);
}

/*
 * init
 * ---------------------------------------------
 * Descrp: Init requires the original/destination mappings, 
 *         the type of interpolation
 * Inputs:
 * Return: (none)
 */
void sphcomparer::init(const char* srcmap1, const char* srcmap2, const char* interpl,
		       const char* m, const char* n, int z, const char* b, const char* v, const char* wght, bool swflag,
		       const char* inp1, const char* inp2, const char* sph, double AngleX, double AngleY, double AngleZ, char* compareMatrix){
    sph2sr1   = charToSph2Map(srcmap1);
    sph2sr2   = charToSph2Map(srcmap2);
    fil       = charToInterpl(interpl);
    m_numFrames = z;

    std::vector<int> sr1Hgt = charToIntVec(m);
    std::vector<int> sr1Wid = charToIntVec(b);
    std::vector<int> sr2Hgt = charToIntVec(n);
    std::vector<int> sr2Wid = charToIntVec(v);

    sr1Dim    = sph2mapToDim(sph2sr1,sr1Hgt,sr1Wid);
    sr2Dim    = sph2mapToDim(sph2sr2,sr2Hgt,sr2Wid);

    // special cases: not applicable yet because we require that b/v be specified
    if(b>0)
	sr1Dim    = sph2mapToDim(sph2sr1,sr1Hgt,sr1Wid);
    if(v>0)
	sr2Dim    = sph2mapToDim(sph2sr2,sr2Hgt,sr2Wid);
    if(sph2sr1 == sph2mult || sph2sr1 == sph2trec || sph2sr1 == sph2teqr || sph2sr1 == sph2brec || sph2sr1 == sph2beqr || sph2sr1==sph2bmul || sph2sr1==sph2grid)
	multFlag1 = true;
    if(sph2sr2 == sph2mult || sph2sr2 == sph2trec || sph2sr2 == sph2teqr || sph2sr2 == sph2brec || sph2sr2 == sph2beqr || sph2sr2==sph2bmul || sph2sr2==sph2grid)
	multFlag2 = true;
    if(wght){
	setupLatLUT(wght);
	lwFlag = true;
    }
    swFlag = swflag;

    // file read writers
    int invRotFlag = 1;
    sr1Yuv.init(inp1, sr1Wid, sr1Hgt, sr1Dim[0].p, multFlag1);
    sr2Yuv.init(inp2, sr2Wid, sr2Hgt, sr2Dim[0].p, multFlag2, AngleX, AngleY, AngleZ, invRotFlag);
    if (!strcmp(compareMatrix, "spsnr"))
    {
      sphData = readSphData(sph);
    }
}

/*
 * sphcomp
 * ------------------------------
 * Descrp: Generates two spheres from two input images and compares on a set
 *         number of pts
 * Inputs: (none)
 * Return: (float) PSNR
 */
double sphcomparer::sphcomp(std::map<int, std::vector<double>> rotMap, int isFirstFrameRot, char* compareMatrix, int src1Bits, int src2Bits, bool mserFlag){
    int nf = 0;
    float ps = 0;
    double storeX, storeY, storeZ;
    while(nf<m_numFrames)
    {
      bool sr1Flag = sr1Yuv.readNextFrame(src1Bits);
      bool sr2Flag = sr2Yuv.readNextFrame(src2Bits);
	
	      if (sr1Flag && !sr2Flag)
	          fprintf(stderr,"Src1 file longer than src2");
	      else if(!sr1Flag && sr2Flag)
	          fprintf(stderr,"Src2 file longer than src1");
	      if(!sr1Flag || !sr2Flag)
	          break;

	      nf++;
	      printf("Frame: %d\r",nf); fflush(stdout);
        if (nf == 1 && isFirstFrameRot == 0)
        {
          storeX = sr2Yuv.getY()->AngleX;
          storeY = sr2Yuv.getY()->AngleY;
          storeZ = sr2Yuv.getY()->AngleZ;
          sr2Yuv.getY()->AngleX = 0.0;
          sr2Yuv.getY()->AngleY = 0.0;
          sr2Yuv.getY()->AngleZ = 0.0;
          sr2Yuv.getU()->AngleX = 0.0;
          sr2Yuv.getU()->AngleY = 0.0;
          sr2Yuv.getU()->AngleZ = 0.0;
          sr2Yuv.getV()->AngleX = 0.0;
          sr2Yuv.getV()->AngleY = 0.0;
          sr2Yuv.getV()->AngleZ = 0.0;
        }
        if (rotMap.size() != 0)
        {
          std::map<int, std::vector<double>>::iterator it = rotMap.find(nf - 1);
          storeX = sr2Yuv.getY()->AngleX;
          storeY = sr2Yuv.getY()->AngleY;
          storeZ = sr2Yuv.getY()->AngleZ;
          if (it != rotMap.end())
          {
            sr2Yuv.getY()->AngleX = it->second[0];
            sr2Yuv.getY()->AngleY = it->second[1];
            sr2Yuv.getY()->AngleZ = it->second[2];
            sr2Yuv.getU()->AngleX = it->second[0];
            sr2Yuv.getU()->AngleY = it->second[1];
            sr2Yuv.getU()->AngleZ = it->second[2];
            sr2Yuv.getV()->AngleX = it->second[0];
            sr2Yuv.getV()->AngleY = it->second[1];
            sr2Yuv.getV()->AngleZ = it->second[2];
          }
        }
        if (!strcmp(compareMatrix, "spsnr"))
        {
          sph1 = genSphFromImg(sr1Yuv.getY(), sph2sr1);
          sph2 = genSphFromImg(sr2Yuv.getY(), sph2sr2);
          ps += (float)compareTwoSph(sr2Yuv.getY(), mserFlag);
        }
        else if (!strcmp(compareMatrix, "wspsnr"))
        {
          ps += (float)compareWSpsnr(sr1Yuv.getY(), sr2Yuv.getY(), mserFlag);
 
        }
        else
        {
          fprintf(stderr, "compareMatrix must be spsnr or wspsnr");
          exit(0);
        }
        if (nf == 1 && isFirstFrameRot == 0)
        {
          sr2Yuv.getY()->AngleX = storeX;
          sr2Yuv.getY()->AngleY = storeY;
          sr2Yuv.getY()->AngleZ = storeZ;
          sr2Yuv.getU()->AngleX = storeX;
          sr2Yuv.getU()->AngleY = storeY;
          sr2Yuv.getU()->AngleZ = storeZ;
          sr2Yuv.getV()->AngleX = storeX;
          sr2Yuv.getV()->AngleY = storeY;
          sr2Yuv.getV()->AngleZ = storeZ;
        }
        if (rotMap.size() != 0)
        {
          sr2Yuv.getY()->AngleX = storeX;
          sr2Yuv.getY()->AngleY = storeY;
          sr2Yuv.getY()->AngleZ = storeZ;
          sr2Yuv.getU()->AngleX = storeX;
          sr2Yuv.getU()->AngleY = storeY;
          sr2Yuv.getU()->AngleZ = storeZ;
          sr2Yuv.getV()->AngleX = storeX;
          sr2Yuv.getV()->AngleY = storeY;
          sr2Yuv.getV()->AngleZ = storeZ;
        }
    }
    printf("nf: %d\n",nf);
    return ps/nf;
}

/*
 * genSphFromImg
 * ----------------------------------------------------------
 * Descrp: Wrapper to paralellize the computation of a sphere from a given input img
 * Inputs: (image*)   input img
 *         (float2*)  sph pts
 *         (long int) num sph pts
 *         (sph2map)  map to get sph pts from input pts
 *         (ifilter)  interpolation
 * Return: (float3*)  output sph
 */
float3* sphcomparer::genSphFromImg(const image* src, sph2map sph2src){
  float3* outSph = (float3*)malloc(sizeof(float3)*numPts);
  memset(outSph, 0, sizeof(float3)*numPts);

#pragma omp parallel for
  for (long int i = 0; i < numPts; i++)
    sphPointFromImg(src, outSph, i, sph2src);

  return outSph;
}

/*
 * sphPointFromImg
 * ------------------------------------------
 * Descrp: Calculate the color of a point on the sphere given an input img
 * Inputs: (image*)   input img
 *         (float2*)  sph data
 *         (float3*)  output sph
 *         (long int) sph point
 *         (sph2map)  mapping between img and sph
 *         (ifilter)  interpolation
 */
void sphcomparer::sphPointFromImg(const image* src, float3* outSph, long int idx, sph2map sph2src){
    // get the proper indexing from the sphere point
  float v[3];
  float2 sd = { sphData[idx].x, sphData[idx].y };
  float3 pt = sphToCart(sd);
  v[0] = pt.x;
  v[1] = pt.y;
  v[2] = pt.z;

  // find the color of the point (dependent on src)
  int F;
  float I, J;
  float p[3];
  p[0] = 0;
  p[1] = 0;
  p[2] = 0;
  sph2src(&F, &I, &J, src, v, 1);


  fil(src + F, NULL, I, J, p);
  outSph[idx].x = p[0];
  outSph[idx].y = p[1];
  outSph[idx].z = p[2];
}

/*
 * readSphData
 * -----------------------------------
 * Descrp: Reads a sphere file and loads lat/lon data into an array
 * Inputs: (char*)    sphere data filename
 *         (long int) number of points
 * Return: (float2*)  lat, lon data
 */
float3* sphcomparer::readSphData(const char* fName){
    // get number of points from file name
    char fCopy[128];
    char *p = NULL;
    strcpy_s(fCopy,fName);
    strtok_s(fCopy,"._", &p);
    numPts = atol(strtok_s(NULL,"._", &p));

    // allocate memory
    float3* spd = (float3*)malloc(sizeof(float3)*numPts);
    memset(spd,0,sizeof(float3)*numPts);

    // read data
    FILE *fp = NULL;
    fopen_s(&fp, fName, "r");
    for(int z=0; z<numPts; z++){
	if(swFlag)
	    fscanf_s(fp, "%f %f %f", &spd[z].x, &spd[z].y, &spd[z].z);
	else
	    fscanf_s(fp, "%f %f", &spd[z].x, &spd[z].y);
    }
    return spd;
}


/*
 * getLatWeight
 * --------------------------------------------------------------
 * Descrp: Returns a weight that is a function of the input latitude
 * Inputs: (float) latitude
 * Return: (float) weight
 */
float sphcomparer::getLatWeight(float3 sd){
    if(lwFlag)
	return latLUTLookup(sd.x);
    else if(swFlag)
	return sd.z;
    return 1.0;
}

/*
 * compareTwoSph
 * --------------------------------------------------------------
 * Descrp: Calculate various metrics for two spheres (e.g., l2 distance)
 * Inputs: (float3*)  sph1
 *         (float3*)  sph2
 *         (long int) num pts
 *         (float2*)  sph data
 * Return: (float) comparison metric
 */
double sphcomparer::compareTwoSph(const image* src, bool mserFlag){
  double ssdR = 0;
  float latWeight = 0;
  double totWeight = 0;
  for (int i = 0; i < numPts; i++){
    latWeight = getLatWeight(sphData[i]);
    double v = sph1[i].x - sph2[i].x;
    ssdR += 100000 * latWeight*v*v;
    totWeight += latWeight;
  }
  double mseR = ssdR / totWeight / 100000;
  double psrR = 10 * log10(1.0f / mseR);

  if (mserFlag)
    return mseR;
  return psrR;
}

double sphcomparer::compareWSpsnr(const image* src1, const image *src2, bool mserFlag)
{
  double ssdR = 0;
  float latWeight = 1;
  double totWeight = 0;
  map2sph    sr1Tosph = NULL;
  if (sph2sr1 == sph2rect && sph2sr2 == sph2rect)
  {
    sr1Tosph = rect2sph;
  }
  else
  {
    fprintf(stderr, "wspsnr need input and output format are all rect");
  }
  for (int i = 0; i < src1->h; i++)
  {
    for (int j = 0; j < src1->w; j++)
    {
      // find the color of the point (dependent on src)
      const float ii = samp_pat->p[0].i + i;
      const float jj = samp_pat->p[0].j + j;
      int F;
      float I, J;
      float src2Value = 0.0f;
      float *p = &src2Value;
      float v[3];
      sr1Tosph(0, ii, jj, src1, src1->h, src1->w, v);
      sph2sr2(&F, &I, &J, src2, v, 1);
      fil(src2 + F, NULL, I, J, p);
      double dif = p[0] - src1->p[src1->w * i + j];
      latWeight = cos((ii - src1->h / 2) * M_PI / src1->h);
      ssdR += 100000 * latWeight * dif * dif;
      totWeight += latWeight;
    }
  }
  double mseR = ssdR / totWeight / 100000;
  double psrR = 10 * log10(1.0f / mseR);

  if (mserFlag)
    return mseR;
  return psrR;
}


