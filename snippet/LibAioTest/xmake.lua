target ("LibAioTest")
    set_kind ("binary")
    add_files ("*.c")

    add_syslinks ("aio")
