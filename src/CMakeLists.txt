
set(SRCS 
                Control.cpp
                controlSurface.cpp
                parameter.cpp
)

set(SRCS_TEST main.cpp)

add_executable( effectControlTest
                ${SRCS}
                ${SRCS_TEST}
                )

add_library( effectControl STATIC ${SRCS})

include_directories( 
                            ../include
)

target_compile_options( effectControl PRIVATE
    -std=c++2a
)
target_compile_options( effectControlTest PRIVATE
    -std=c++2a
)

target_link_libraries( effectControlTest fmt::fmt)
target_link_libraries( effectControl fmt::fmt)

set_target_properties( effectControlTest PROPERTIES EXCLUDE_FROM_ALL 1)