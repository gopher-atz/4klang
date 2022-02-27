set(GO4KVSTI_CXX_SOURCES
    source/common/AudioEffect.cpp
    source/common/audioeffectx.cpp
    source/GoSynth/Go4kVSTi.cpp
    source/GoSynth/Go4kVSTiCore.cpp
    source/GoSynth/Go4kVSTiGUI.cpp
    source/GoSynth/Go4kVSTimain.cpp
    source/GoSynth/Go4kVSTIproc.cpp

    win/Go4kVSTi.rc
)

set_source_files_properties(4klang.obj PROPERTIES EXTERNAL_OBJECT true GENERATED true)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/win"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/common"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/GoSynth"
    )
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/win/library")

add_library(4klang SHARED ${GO4KVSTI_CXX_SOURCES} win/Go4kVSTi.def 4klang.obj)
target_link_libraries(4klang vstgui Comctl32 odbc32 odbccp32)
add_custom_command(TARGET 4klang PRE_BUILD BYPRODUCTS 4klang.obj
    COMMAND ${YASM} ${CMAKE_CURRENT_SOURCE_DIR}/win/4klang.asm ${YASM_OPTIONS} -o 4klang.obj -i "${CMAKE_CURRENT_SOURCE_DIR}/win/"
    COMMENT "Assembling 4klang.asm..."
)

add_library(8klang SHARED ${GO4KVSTI_CXX_SOURCES} win/Go4kVSTi2.def 4klang.obj)
target_compile_definitions(8klang PUBLIC _8KLANG)
target_link_libraries(8klang vstgui Comctl32 odbc32 odbccp32)
