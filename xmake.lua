option ("linux-headers", {showmenu = true, description = "Set linux-headers path."})


target ("timer")
    add_rules ("platform.linux.driver")
    add_files ("src/*.c")
    set_values ("linux.driver.linux-headers", "$(linux-headers)")

    add_cflags ("-O1")
