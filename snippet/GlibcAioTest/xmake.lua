target ("GlibcAioTest1")
    set_kind ("binary")
    add_files ("main1.cpp")

    -- deferences between add_links() and add_syslinks(): https://xmake.io/#/manual/project_target?id=targetadd_syslinks
    add_syslinks ("rt")

target ("GlibcAioTest2")
    set_kind ("binary")
    add_files ("main2.cpp")

    add_syslinks ("rt")

target ("GlibcAioTest3")
    set_kind ("binary")
    add_files ("main3.cpp")

    add_syslinks ("rt")
