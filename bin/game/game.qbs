import qbs

CppApplication {
    consoleApplication: true

    cpp.cxxLanguageVersion: "c++14"

    property path graph_lib_dir: "../graph_lib"
    property path source_dir: "../../source"
    property path fltk_dir: "../fltk"

    files: [
        "A_star.cpp",
        "A_star.h",
        "search_paths.cpp",
        "search_paths.h",
        source_dir + "/landscape.txt",
        source_dir + "/terrain.txt",
        source_dir + "/units.txt",
        source_dir + "/size.txt",
        graph_lib_dir + "/Graph.cpp",
        graph_lib_dir + "/GUI.cpp",
        graph_lib_dir + "/Window.cpp",
        "../myLib/myLib.h",
        "../myLib/myLib.cpp",
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
        "grid.cpp",
        "grid.h",
        "editting_files.cpp",
        "editting_files.h",
        "pictures_treatment.cpp",
        "pictures_treatment.h",
        "split.cpp",
        "split.h",
        "main.cpp",
    ]

    cpp.includePaths: fltk_dir + "/include"
    cpp.libraryPaths: fltk_dir + "/lib"

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
        "comctl32"
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
