################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
hardware/adc.obj: D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/hardware/adc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/project/ccs" --include_path="D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --include_path="../../../msp432p4xx_lib" --include_path="../../../msp432p4xx_lib/CMSIS/Include" --include_path="../../../sys/inc" --include_path="../../../hardware/inc" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="hardware/$(basename $(<F)).d_raw" --obj_directory="hardware" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

hardware/key.obj: D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/hardware/key.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/project/ccs" --include_path="D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --include_path="../../../msp432p4xx_lib" --include_path="../../../msp432p4xx_lib/CMSIS/Include" --include_path="../../../sys/inc" --include_path="../../../hardware/inc" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="hardware/$(basename $(<F)).d_raw" --obj_directory="hardware" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

hardware/key4x4.obj: D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/hardware/key4x4.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/project/ccs" --include_path="D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --include_path="../../../msp432p4xx_lib" --include_path="../../../msp432p4xx_lib/CMSIS/Include" --include_path="../../../sys/inc" --include_path="../../../hardware/inc" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="hardware/$(basename $(<F)).d_raw" --obj_directory="hardware" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

hardware/led.obj: D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/hardware/led.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/project/ccs" --include_path="D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --include_path="../../../msp432p4xx_lib" --include_path="../../../msp432p4xx_lib/CMSIS/Include" --include_path="../../../sys/inc" --include_path="../../../hardware/inc" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="hardware/$(basename $(<F)).d_raw" --obj_directory="hardware" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

hardware/oled.obj: D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/hardware/oled.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/project/ccs" --include_path="D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --include_path="../../../msp432p4xx_lib" --include_path="../../../msp432p4xx_lib/CMSIS/Include" --include_path="../../../sys/inc" --include_path="../../../hardware/inc" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="hardware/$(basename $(<F)).d_raw" --obj_directory="hardware" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

hardware/tim32.obj: D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/hardware/tim32.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/project/ccs" --include_path="D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --include_path="../../../msp432p4xx_lib" --include_path="../../../msp432p4xx_lib/CMSIS/Include" --include_path="../../../sys/inc" --include_path="../../../hardware/inc" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="hardware/$(basename $(<F)).d_raw" --obj_directory="hardware" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

hardware/timA.obj: D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/hardware/timA.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/ti/MSP432_Quick_entry-master/00_RNA_Empty(traditional)/project/ccs" --include_path="D:/ti/ccs1040/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --include_path="../../../msp432p4xx_lib" --include_path="../../../msp432p4xx_lib/CMSIS/Include" --include_path="../../../sys/inc" --include_path="../../../hardware/inc" --define=__MSP432P401R__ --define=DeviceFamily_MSP432P401x -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="hardware/$(basename $(<F)).d_raw" --obj_directory="hardware" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


