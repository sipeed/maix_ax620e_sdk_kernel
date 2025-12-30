SECTIONS {
    .UtestTcTab : {
        __rt_itest_tc_tab_start = .;
        KEEP (*(.ItestTcTab))
        __rt_itest_tc_tab_end = .;
    }
}
INSERT AFTER .data;
