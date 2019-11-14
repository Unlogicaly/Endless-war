import qbs

CppApplication {
    consoleApplication: true

    cpp.cxxLanguageVersion: "c++14"

    property path graph_lib_dir: "C:/Graph_lib"

    files: [
        "D:\\My\\Source\\landscape.txt",
        "D:\\My\\Source\\terrain.txt",
        "D:\\My\\Source\\units.txt",
        "D:\\My\\Source\\size.txt",
        "myLib.h",
        "myLib.cpp",
        "map.cpp",
        "map.h",
        "node.cpp",
        "node.h",
        "Field.cpp",
        "Field.h",
        "area_bonuses.h",
        "area_define_type.h",
        "area_type_define.cpp",
        "create_window.cpp",
        "create_window.h",
        "editting_files.cpp",
        "editting_files.h",
        "grid.cpp",
        "grid.h",
        "pictures_treatment.cpp",
        "pictures_treatment.h",
        "split.cpp",
        "split.h",
        graph_lib_dir + "/Graph.cpp",
        graph_lib_dir + "/GUI.cpp",
        graph_lib_dir + "/Window.cpp",
        "main.cpp",
    ]

    cpp.includePaths: "C:/fltk_win64/include"
    cpp.libraryPaths: "C:/fltk_win64/lib"
    cpp.cxxFlags: "-Wno-unused-parameter"
    cpp.driverLinkerFlags: "-mwindows"
    cpp.staticLibraries: [
        "fltk_images",
        "fltk",
        "fltk_png",
        "z",
        "fltk_jpeg",
        "ole32",
        "uuid",
        "comctl32",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
