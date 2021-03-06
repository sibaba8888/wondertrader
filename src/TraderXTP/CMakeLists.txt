
#1. 确定CMake的最低版本需求
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

#2. 确定工程名
PROJECT(TraderXTP LANGUAGES CXX)
SET(CMAKE_CXX_STANDARD 11)


IF (WIN32)
	IF("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
		SET(INCS $ENV{MyX64Deps12}/include)
		SET(LNKS $ENV{MyX64Deps12}/lib)
	ELSE()
		SET(INCS $ENV{MyDepends12}/include)
		SET(LNKS $ENV{MyDepends12}/lib)
	ENDIF()
ELSE (UNIX)
	SET (MyDeps "/home/mydeps")
	SET(INCS ${MyDeps}/include)
	SET(LNKS ${MyDeps}/lib)
ENDIF ()

SET(SRC  
	${PROJECT_SOURCE_DIR}/TraderXTP.cpp
	${PROJECT_SOURCE_DIR}/TraderXTP.h
	
	${PROJECT_SOURCE_DIR}/XTPApi/xoms_api_fund_struct.h
	${PROJECT_SOURCE_DIR}/XTPApi/xoms_api_struct.h
	${PROJECT_SOURCE_DIR}/XTPApi/xquote_api_struct.h
	${PROJECT_SOURCE_DIR}/XTPApi/xtp_api_data_type.h
	${PROJECT_SOURCE_DIR}/XTPApi/xtp_api_struct.h
	${PROJECT_SOURCE_DIR}/XTPApi/xtp_api_struct_common.h
	${PROJECT_SOURCE_DIR}/XTPApi/xtp_trader_api.h
	
)
SET(LNKS "${LNKS} ${PROJECT_SOURCE_DIR}/XTPApi")

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../build/bin)

INCLUDE_DIRECTORIES(${INCS})
LINK_DIRECTORIES(${LNKS})
ADD_LIBRARY(TraderXTP SHARED ${SRC})

IF (WIN32)
	IF ("${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
		TARGET_LINK_LIBRARIES(TraderXTP xtptraderapi64 )
	ELSE ()
		TARGET_LINK_LIBRARIES(TraderXTP xtptraderapi32 )
	ENDIF ()
ELSE (UNIX)
	TARGET_LINK_LIBRARIES(TraderXTP ${PROJECT_SOURCE_DIR}/XTPApi/libxtptraderapi.so)
	SET_TARGET_PROPERTIES(TraderXTP PROPERTIES
		CXX_VISIBILITY_PRESET hidden
		C_VISIBILITY_PRESET hidden
		VISIBILITY_INLINES_HIDDEN 1)
ENDIF ()

