add_library(
    TypingMasterLibrary
    TypingMasterWindow.hpp TypingMasterWindow.cpp
    TypingLine.hpp TypingLine.cpp
    TypingSource.hpp TypingSource.cpp
    Stopwatch.hpp Stopwatch.cpp
)
target_link_libraries(TypingMasterLibrary PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(TypingMasterLibrary PUBLIC .)
