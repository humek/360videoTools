#ifndef _PANOMAPPER_H_
#define _PANOMAPPER_H_

#include "map_utils.h"
#include <opencv2/opencv.hpp>
#include <vector>

// antialias filter lookups
extern float G_AAFILTER_NONE[9];
extern float G_AAFILTER_9TENTHS[9];
extern float G_AAFILTER_8TENTHS[9];
extern float G_AAFILTER_3FOURTHS[9];
extern float G_AAFILTER_7TENTHS[9];
extern float G_AAFILTER_6TENTHS[9];
extern float G_AAFILTER_1HALF[9];
extern float G_AAFILTER_4TENTHS[9];
extern float G_AAFILTER_3TENTHS[9];
extern float G_AAFILTER_1FOURTH[9];
extern float G_AAFILTER_2TENTHS[9];
extern float G_AAFILTER_ZERO156[9];

class panomapper{
 protected:
    ifilter        fil;
    const pattern* samp_pat;
    int            m_numFrames;

 public:
    panomapper();
    ~panomapper();
    sph2map charToSph2Map(const char* s2m);
    map2sph charToMap2Sph(const char* m2s);
    ifilter charToInterpl(const char* f);
    imgdim  sph2mapToDim(sph2map s, int h, int w);
    imgdim  map2sphToDim(map2sph s, int h, int w=0);
    std::vector<imgdim> sph2mapToDim(sph2map s, std::vector<int> h, std::vector<int> w);
    std::vector<int>    charToIntVec(const char* v);
};

class remapper: public panomapper{
 private:
    sph2map    sph2src;
    map2sph    dst2sph;
    aBlendMap  aBlend;
    cYuvReader srcYuv;
    cYuvWriter dstYuv;
    cYuvWriter acsYuv;
    cYuv       filYuv;
    int        numPages;
    float2     fov;
    float2     startXY;
    float2     spanXY;
    imgdim     dstDim;
    FILE*      fview;
    bool       viewFlag;
    bool       trackFlag;
    bool       multFlag;
    bool       blendFlag;
    std::vector<imgdim> srcDim;

 public:
    remapper();
    ~remapper();
    void  init(const char* inp_map, const char* out_map, const char* interpl,const char* m, bool bf,
	      int n, float x, float y, float w, float h, int z, const char* b, int v, float vp, float vt,
        const char* t, const char* a, const char* inp, const char* out, double AngleX, double AngleY, double AngleZ, int isInvRotMapping);
    void  remapFrames(std::map<int, std::vector<double>> rotMap, int isfirstFrameRot, int inputBits, int outputBits);
    float antialiasFactorX();
    float antialiasFactorY();
    void  antialiasFilter();
    void  getAntialiasFilter(int nTaps, float fc, float* h);
    void  remap(const image *src, const image *dst, const image *acs);
    void  supersample(const image *src, const image *dst, const image *acs,
		     int f, int i, int j);
    void  setBlend();
    void  blendSample(const image *src, const image *dst, const image *acs,
		     int f, int i, int j);

};

class sphcomparer: public panomapper{
 private:
    sph2map    sph2sr1;
    sph2map    sph2sr2;
    cYuvReader sr1Yuv;
    cYuvReader sr2Yuv;
    long int   numPts;
    float3*    sphData;
    float3*    sph1;
    float3*    sph2;
    bool       lwFlag;
    bool       swFlag;
    bool       multFlag1;
    bool       multFlag2;
    std::vector<imgdim> sr1Dim;
    std::vector<imgdim> sr2Dim;

 public:
    sphcomparer();
    ~sphcomparer();
    void init(const char* srcmap1, const char* srcmap2, const char* interpl, const char* m, 
	      const char* n, int z, const char* b, const char* v, const char* wght, bool swflag,
	      const char* inp1, const char* inp2, const char* sph, double AngleX, double AngleY, double AngleZ, char *compareMatrix);
    float3* genSphFromImg(const image* src, sph2map sph2src);
    float3* readSphData(const char* fName);
    double sphcomp(std::map<int, std::vector<double>> rotMap, int isFirstFrameRot, char* compareMatrix, int inputBits, int outputBits, bool mserFlag = false);
    float getLatWeight(float3 sd);
    double compareTwoSph(const image* src, bool mserFlag = false);
    double compareWSpsnr(const image* src1, const image *src2, bool mserFlag = false);
    void sphPointFromImg(const image* src, float3* outSph, long int idx, sph2map sph2src);
};




#endif
