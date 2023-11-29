cmake_minimum_required(VERSION 3.24)
project(get)

set(CMAKE_CXX_STANDARD 17)






set(INC_DIR  ./cbc/include)

file(GLOB CBCSOURCE cbc/src/*.cpp ZteModel.cpp ZteModel.h ZteThread.cpp ZteThread.h ZteStrategy.cpp ZteStrategy.h ZteGeneralDepth.cpp ZteGeneralDepth.h tools.cpp tools.h ZteFeasibilityBase.cpp ZteFeasibilityBase.h ZteBaseModel.cpp ZteBaseModel.h ZteMessageHandler.cpp ZteMessageHandler.h ZteEventHandler.cpp ZteEventHandler.h ZteCglTreeProbingInfo.cpp ZteCglTreeProbingInfo.h ZteCglDuplicateRow.cpp ZteCglDuplicateRow.h)

include_directories(cbc/include)




add_executable(get main.cpp ${CBCSOURCE})
