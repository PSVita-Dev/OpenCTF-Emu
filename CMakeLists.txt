cmake_minimum_required(VERSION 3.10)

project(CCR)

include_directories(${PROJECT_SOURCE_DIR})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu17 -g") #-fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g") #-fsanitize=address")


set(SRC_FILES
    "src/CFrame.cpp"
    "src/COIList.cpp"
    "src/CRender.cpp"
    "src/CLOList.cpp"
    "src/COI.cpp"
    "src/CImageBank.cpp"
    "src/CObjectCommon.cpp"
    "src/CAnimHeader.cpp"
    "src/CAnim.cpp"
    "src/CAnimDir.cpp"
    "src/CRun.cpp"
    "src/main.cpp"
)

include_directories("src/include")
include_directories("nanovg")

add_executable(${PROJECT_NAME} ${SRC_FILES})


if(NOT PSP)
target_link_libraries(${PROJECT_NAME} 
    SDL2
    SDL2_image
    SDL2_mixer
    z
    libnanovg.a
    GL
    glfw
    glew
)
endif()
if(PSP)
    target_link_libraries(${PROJECT_NAME} 
        png
        osl
        jpeg 
        z 
        pspgu 
        pspge
        pspdisplay
        psppower
        psphprm
        pspaudio
        pspctrl
        m 
        pspvram
    )
    create_pbp_file(TARGET ${PROJECT_NAME} TITLE "${CMAKE_PROJECT_NAME}" 
    ICON_PATH ICON0.png
    BACKGROUND_PATH ICON1.png 
    )
endif()
