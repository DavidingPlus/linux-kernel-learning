option ("linux-headers", {showmenu = true, description = "Set linux-headers path."})


target ("exp1")
    add_rules ("platform.linux.module")
    add_files ("src/exp1/*.c")
    set_values ("linux.driver.linux-headers", "$(linux-headers)")

    set_optimize("fast") -- none, fast, faster, fastest, smallest, aggressive

target ("exp2")
    set_kind ("binary")
    add_files ("src/exp2/user/*.c")
    set_languages ("c17")

    set_optimize("none")

target ("exp3_export")
    add_rules ("platform.linux.module")
    add_files ("src/exp3/export/*.c")
    set_values ("linux.driver.linux-headers", "$(linux-headers)")

    set_optimize("fast")

target ("exp3_call")
    add_rules ("platform.linux.module")
    add_files ("src/exp3/call/*.c")
    set_values ("linux.driver.linux-headers", "$(linux-headers)")

    set_optimize("none")
