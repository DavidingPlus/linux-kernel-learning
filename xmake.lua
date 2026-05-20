option ("linux-headers", {showmenu = true, description = "Set linux-headers path."})


target ("hello")
    add_rules ("platform.linux.module")
    add_files ("src/exp1/*.c")
    set_values ("linux.driver.linux-headers", "$(linux-headers)")

    add_cflags ("-O1")

target ("mycall")
    set_kind ("binary")
    add_files ("src/exp2/user/*.c")
    set_languages ("c17")

    add_cflags ("-O0")
