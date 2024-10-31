add_rules("mode.debug", "mode.release")

add_requires("libpqxx")

target("ptmk_testex")
    set_kind("binary")
    set_languages("c++20")
    add_files("src/*.cpp")
    add_packages("libpqxx")