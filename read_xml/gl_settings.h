#ifndef GL_VARS
#define GL_VARS

/*
 * Defining XML-tags
 */

#define TAG_ROOT           "root"
#define TAG_DESC           "desc"

#define TAG_MAP_CONTAINER  "map"
#define TAG_MAP_WIDTH      "width"
#define TAG_MAP_HEIGHT     "height"
#define TAG_CELLSIZE       "cellsize"
#define TAG_START_X        "startx"
#define TAG_START_Y        "starty"
#define TAG_FINISH_X       "finishx"
#define TAG_FINISH_Y       "finishy"
#define TAG_GRID           "grid"
#define TAG_GRID_ROW       "row"

#define TAG_ALGO_CONTAINER        "algorithm"
#define TAG_ALGO_TYPE             "searchtype"
#define TAG_ALGO_METRIC           "metrictype"
#define TAG_ALGO_HWEIGHT          "hweight"
#define TAG_ALGO_TIE_BRAKE        "breakingties"
#define TAG_ALGO_LINE_COST        "linecost"
#define TAG_ALGO_DIAG_COST        "diagonalcost"
#define TAG_ALGO_ALLOW_DIAG       "allowdiagonal"
#define TAG_ALGO_ALLOW_SQUEEZE    "allowsqueeze"

#define TAG_OPTIONS_CONTAINER     "options"
#define TAG_OPTIONS_LOG_LEVEL     "loglevel"
#define TAG_OPTIONS_LOG_PATH      "logpath"
#define TAG_OPTIONS_LOG_FILENAME  "logfilename"

#define INPUT_GRID_SEPARATOR      ' '

/*
 * Some default values
 */

#define DEFAULT_CELLSIZE       1
#define ELEMENT_OUT_OF_GRID   -1

/*
 * Output attributes and params
 */

#define TAG_OUTPUT_CONTAINER    "output"
#define TAG_OUTPUT_DENSITY      "density"

#define OUTPUT_LINE_NUMBER_ATTR "number"
#define OUTPUT_MAP_SEPARATOR    " "

#endif // GL_VARS

#ifndef GL_LIBRARIES
#define GL_LIBRARIES

/*
 * Importing general libraries
 */

#include <iostream>
#include  "../tinyxml/tinyxml.h"
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

#endif


#ifndef PROJECT_FILES
#define PROJECT_FILES

#include "errors.cpp"
#include "utils.cpp"
#include "obstacle.cpp"
#include "algorithm.cpp"
#include "options.cpp"
#include "map.cpp"
#include "mapanalyzer.cpp"

#endif
