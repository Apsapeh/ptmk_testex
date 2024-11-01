add_rules("mode.debug", "mode.release")

add_requires("libpqxx")

target("ptmk_testex")
    set_kind("binary")
    set_languages("c++20")
    add_files("src/*.cpp")
    add_packages("libpqxx")

    if is_mode("debug") then
        set_symbols("debug")
        set_optimize("none")
        --set_warnings("everything")
    elseif is_mode("release") then
        --set_policy("build.merge_archive", true)
        set_symbols("hidden")
        set_strip("all")
        set_fpmodels("fast")
        set_optimize("aggressive")
    end