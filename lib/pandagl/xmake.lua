target("pandagl")
    set_kind("static")
    add_files("src/*.c")
    add_headerfiles("include/pandagl.h")
    add_headerfiles("include/(pandagl/*.h)")
    add_deps("yutil", "lcui-def")

target("pandagl_test")
    set_default(false)
    set_kind("binary")
    add_files("test/*.c")
    add_deps("ctest", "pandagl")