target("libworker")
    set_default(false)
    set_kind("$(kind)")
    add_files("src/**.c")
    add_deps("yutil", "libthread")
