#include "getopt.h"
#include "yuv_helper.h"
#include "map_utils.h"
#include "panomapper.h"

static int usage(const char *exe){
    fprintf(stderr,
            "%s [-i input1] [-o input2] [-f filter] [-m m] [-n n] [-z z] [-w w] [-s] src1 src2 sph\n"
            "\t-i ... Input file type: cube, rect  eqarea, merc, dyad          [rect]\n"
            "\t-o ... Input file type: cube, rect, eqarea, merc, dyad          [rect]\n"
            "\t-f ... Filter type: nearest, linear, bicubic                 [bicubic]\n"
            "\t-w ... Latitude weighting function                                 [1]\n"
            "\t-s ... Sphere weighting indicator                              [false]\n"
            "\t-m ... Src1 height                                               [500]\n"
            "\t-b ... Src1 width                                                 [2m]\n"
            "\t-n ... Src2 height                                               [500]\n"
            "\t-v ... Src1 width                                                 [2n]\n"
            "\t-z ... Num frames                                             [INTMAX]\n",
             exe);
    return 0;
}

int main(int argc, char **argv){
    // check cmd inputs
    int c,z=INT_MAX;
    bool swFlag = false, mserFlag=false;
    double AngleX = 0;
    double AngleY = 0;
    const char *rotFile = NULL;
    const char *i = NULL, *o=NULL, *f=NULL, *w=NULL, *m=NULL,*n=NULL, *b=NULL,*v=NULL;
    while ((c = getopt(argc, argv, "i:o:c:d:e:m:n:w:f:z:spv:b:")) != -1){
	switch (c){
	case 'i': i        = optarg;                    break;
	case 'o': o        = optarg;                    break;
	case 'f': f        = optarg;                    break;
	case 'w': w        = optarg;                    break;
  case 'c': AngleX = (double)strtof(optarg, 0);                      break;
  case 'd': AngleY = (double)strtof(optarg, 0);                     break;
  case 'e': rotFile = optarg;          break;
	case 's': swFlag   = true;                      break;
	case 'p': mserFlag = true;                      break;
	case 'm': m        = optarg;                    break;
	case 'n': n        = optarg;                    break;
	case 'b': b        = optarg;                    break;
	case 'v': v        = optarg;                    break;
	case 'z': z        = (int)strtol(optarg, 0, 0); break;
	default: return usage(argv[0]);
        }
    }
    if(argc<=3)
	return usage(argv[0]);

    sphcomparer sc;
    sc.init(i,o,f,m,n,z,b,v,w,swFlag,argv[optind],argv[optind+1],argv[optind+2], AngleX, AngleY);

    FILE *fp;
    std::map<int, std::vector<double>> rotKeyMap;
    if (rotFile != NULL)
    {
      fp = fopen(rotFile, "r");
      if (fp == 0)
      {
        fprintf(stderr, "Error, can not open Rot File \n");
        return 0;
      }
      else
      {
        char Line[256];
        int flagx = 0;
        int flagy = 0;
        int poc = 0;
        double rotx = 0.0;
        double roty = 0.0;

        while (fgets(Line, sizeof(Line), fp))
        {
          std::string strLine(Line);
          size_t posX = strLine.find("currRotX");
          size_t posY = strLine.find("currRotY");
          size_t posPoc = strLine.rfind("POC");
          if (posX != std::string::npos)
          {
            if (flagx != 0)
            {
              std::string tmpStr = strLine.substr(posX + 8, std::string::npos);
              rotx = atof(tmpStr.c_str());
              flagx = 0;
            }
            else flagx = 1;
          }
          if (posY != std::string::npos)
          {
            if (flagy != 0)
            {
              std::string tmpStr = strLine.substr(posY + 8, std::string::npos);
              roty = atof(tmpStr.c_str());
              flagy = 0;
            }
            else flagy = 1;
          }
          if (posPoc != std::string::npos)
          {
            std::vector<double> vecTmp = { rotx, roty };
            poc = atoi(strLine.c_str() + 3);
            rotKeyMap.insert(std::map<int, std::vector<double>>::value_type(poc, vecTmp));
          }
        }
      }
    }

    double t = sc.sphcomp(rotKeyMap, mserFlag);
    printf("PSNR: %.15f\n",t);

    return 0;
}
