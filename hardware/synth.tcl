source -notrace ../script/proj_gen.tcl

proc create_target {} {
    #get the current time as a Unix timestamp
    set currentTime [clock seconds]

    #Format the timestamp into the desired format
    set formattedTime [clock format $currentTime -format {%Y%m%d_%H%M%S}]

    set proj_name "kria_pl_uart_gpio${formattedTime}_"
    set origin_dir "."

    #set project info
    ::proj::set_proj_info \
        -force \
        -part "xck26-sfvc784-2LV-c" \
        -board_part "xilinx.com:kr260_som:part0:1.1" \
        -addr "$origin_dir" \
        -name "$proj_name" 

    #generate the project
    ::proj::generate_project

    #function to add the files in the src directory to the project
    ::proj::create_src_filesets -base_folder $origin_dir

    set bd_file_name "system_bd"

    #function to create the block design
    ::proj::create_block_design -bd_file $bd_file_name \
                                -design_name "system"  \
                                -validate 1            \
                                -base_folder $origin_dir

    #function to create the block design wrapper which will contain the top level HDL code
    ::proj::create_bd_wrapper -bd_name "system" -is_top 1

    #function to close the block design
    close_bd_design [get_bd_designs "system"]

    #add constraint files to the project
    ::proj::create_constr_filesets -base_folder $origin_dir
    
    update_compile_order -fileset sources_1

    #build the project
    puts "--- Building project"
    ::proj::build_proj
    #wait for the build to finish
    wait_on_run impl_1

    #export the project bitstream file using the commands
    puts "--- Export bitstream"
    set xil_proj [::proj::get_project_name]
    ::proj::export_proj_bitstream -destination "$origin_dir/build/export_${xil_proj}"

}