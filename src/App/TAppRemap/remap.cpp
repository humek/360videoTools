#include "getopt.h"
#include "yuv_helper.h"
#include "map_utils.h"
#include "panomapper.h"
#include <string>
#include <iostream>
#include <map>

static int usage(const char *exe){
    fprintf(stderr,
      "%s [-i input] [-o output] [-f filter] [-m m] [-n n] [-w w] [-h h] [-t tf] [-y] src dst\n"
      " \n"
      "\t-i ... Input  file type, common: rect  eqar  cube                [rect]\n"
      "\t       added: aitoff, sanson(used for mapping)  poletop, poledown(used to get the pole of the top/down of rect) recttop_inv, rectdown_inv (used for inv) \n"
      "\t       not used: dyad, mult, bmul, trec, brec, grid, beqr, teqr, merc, cos2 \n"
      "\t-o ... Output file type: cube, rect, eqar, merc, view             [rect]\n"
      "\t-f ... Filter type: nearest, linear, bicubic                   [bicubic]\n"
      "\t-m ... Input  height list                                          [500]\n"
      "\t-b ... Input  width                                                 [2m]\n"
      "\t-n ... Output height                                               [500]\n"
      "\t-v ... Output width                                                 [2n]\n"
      "\t-w ... Viewport width                                              [200]\n"
      "\t-h ... Viewport height                                             [200]\n"
      "\t-x ... Viewport fov x in degree                                     [90]\n"
      "\t-y ... Viewport fov y in degree                                     [90]\n"
      "\t-p ... Viewport center position phi (degrees)                        [0]\n"
      "\t-l ... Viewport center position theta (degrees)                        [0]\n"
      "\t-t ... Tracking data file                                         [none]\n"
      "\t-y ... Blend data together (only works with orec, etc ...)         [off]\n"
      "\t-z ... Number of frames                                            [MAX]\n"
      "\t-c ... rotation of x                                                       [0]\n"
      "\t-d ... rotation of y                                                       [0]\n"
      "\t-e ... rotation of z                                                       [0]\n"
      "\t-k ... file describe rotation                                         \n"
      "\t-g ... is first frame rotate                                           [0]\n"
      "\t-u ... is inv rotate  mapping                                       [0]\n"
      "\t-j ... ColorFormat(bit)                                                [8-8]\n"
      "\\E.g. (map.exe -i rect -o rect -m 2048 -b 4096 -n 1024 -v 2048 -z 10 InputFile.yuv OutputFile.yuv [-c 0.5 -d 1.0 -e 0.2] [-k d:\\lowdelay_log.txt] [-g 1] [-u 1][-j 10-8]) \n",
            exe);
    return 0;
}

int main(int argc, char **argv){
    // check command line inputs
    int argNum;
    int n = 500;
    int FrameNum = INT_MAX;
    int v = -1;

    float x=90.0, y=90.0, w=200, h=200;
    float p=0.0, l=0.0;
    bool  blendFlag = false;

    double AngleX = 0.0;
    double AngleY = 0.0;
    double AngleZ = 0.0;
    int isFirstFrameRot = 0;
    int isInvRotMapping = 0;
    int inputBits = 8;
    int outputBits = 8;
    char* bits = NULL;
    const char *rotFile = NULL;
    const char *inputType = NULL;
    const char *outputType = NULL;
    const char *filter = NULL;
    const char *t = NULL;
    const char *a = NULL;
    const char *m = NULL;
    const char *b = NULL;

    while ((argNum = getopt(argc, argv, "i:o:m:n:z:t:x:y:w:h:f:a:b:v:p:l:c:d:e:k:j:g:u:r")) != -1)
    {
        switch (argNum){
              case 'i': inputType = optarg;                      break;                    //input file type
	            case 'o': outputType = optarg;                      break;                 //output file type
              case 't': t = optarg;                      break;    // ???
              case 'f': filter = optarg;                      break;                   //filter: linear, double linear, cubic, lanczos
              case 'a': a = optarg;                      break;   //???
              case 'm': m = optarg;                      break;                //height of input, e. g. 2048
              case 'n': n = (int)strtol(optarg, 0, 0);   break;         //height of output e. g. 1024
              case 'z': FrameNum = (int)strtol(optarg, 0, 0);   break;         // frame num
              case 'x': x = (float)strtod(optarg, 0);    break;                          //view port for x degree, only used in viewport
              case 'y': y = (float)strtod(optarg, 0);    break;                         //view port for x degree, only used in viewport
              case 'w': w = (float)strtod(optarg, 0);    break;                       //width of view port, only used in viewport
              case 'h': h = (float)strtod(optarg, 0);    break;                        //height of view port, only used in viewport
              case 'b': b = optarg;                      break;                   //width of input, e. g. 4096
              case 'v': v = (int)strtol(optarg, 0, 0);   break;          //width of output, e. g. 2048
              case 'p': p = (float)strtol(optarg, 0, 0); break;                      //Viewport center position phi (degrees), only used in viewport
	            case 'l': l = (float)strtol(optarg, 0, 0); break;                              //Viewport center position tht (degrees), only used in viewport
              case 'c': AngleX = (double)strtod(optarg, 0);                      break;     //about rotation
              case 'd': AngleY = (double)strtod(optarg, 0);                     break;
              case 'e': AngleZ = (double)strtod(optarg, 0);                     break;
              case 'k': rotFile = optarg;          break;
              case 'j': bits = optarg;          break;
              case 'g': isFirstFrameRot = (int)strtol(optarg, 0, 0);          break;     //is first frame rotate, 0 for no, 1 for yep
              case 'u': isInvRotMapping = (int)strtol(optarg, 0, 0);          break;     //is inv rotate mapping, 0 for no, 1 for yep
	            case 'r': blendFlag = true;                break;        //????
        default : return usage(argv[0]);
        }
    }
    if(argc<=2)
	return usage(argv[0]);

    // mapping / yuv read write init
    remapper PanoMapper;

    if (filter == NULL)
    {
      filter = "lanczos";
    }

    char* tmpBits = NULL;
    if (bits != NULL)
    {
      inputBits = atoi(strtok_s(bits, "-", &tmpBits));
      outputBits = atoi(strtok_s(NULL, "-", &tmpBits));
    }

    PanoMapper.init(inputType, outputType, filter, m, blendFlag, n,
      x, y, w, h,     //view port use, not used
      FrameNum, b, v,   
      p, l,       //view port use
      t, a, argv[optind], argv[optind + 1], //inputFile and outputFile
      AngleX, AngleY, AngleZ, isInvRotMapping);

    FILE *fp = NULL;
    std::map<int, std::vector<double>> rotKeyMap;
    if (rotFile != NULL)
    {
      fopen_s(&fp, rotFile, "r");
      if (fp == NULL)
      {
        fprintf(stderr, "Error, can not open Rot File \n");
        return 0;
      }
      else
      {
        char Line[256];
        int flagx = 0;
        int flagy = 0;
        int flagz = 0;
        int poc = 0;
        double rotx = 0.0;
        double roty = 0.0;
        double rotz = 0.0;
        
        while (fgets(Line, sizeof(Line), fp))
        {
          std::string strLine(Line);
          size_t posX = strLine.find("currRotX");
          size_t posY = strLine.find("currRotY");
          size_t posZ = strLine.find("currRotZ");
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
          if (posZ != std::string::npos)
          {
            if (flagz != 0)
            {
              std::string tmpStr = strLine.substr(posZ + 8, std::string::npos);
              rotz = atof(tmpStr.c_str());
              flagz = 0;
            }
            else flagz = 1;
          }
          if (posPoc != std::string::npos)
          {
            std::vector<double> vecTmp = { rotx, roty, rotz };
            poc = atoi(strLine.c_str() + 3);
            rotKeyMap.insert(std::map<int, std::vector<double>>::value_type(poc, vecTmp));
          }
        }
      }
    }

    PanoMapper.remapFrames(rotKeyMap, isFirstFrameRot, inputBits, outputBits);

    // map all frames
    return 0;
}
