add_library(models STATIC
    treemodel.cpp
    topproxy.cpp
    data.cpp
    callercalleemodel.cpp
    disassemblymodel.cpp
    costdelegate.cpp
    highlighter.cpp
    searchdelegate.cpp
    processmodel.cpp
    processfiltermodel.cpp
    processlist_unix.cpp
    timelinedelegate.cpp
    eventmodel.cpp
    filterandzoomstack.cpp
    ../settings.cpp
    ../util.cpp
)

target_link_libraries(models
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    KF5::ItemModels
    KF5::ConfigWidgets
)
